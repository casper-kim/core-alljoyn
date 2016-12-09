////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright 2016 Open Connectivity Foundation and Contributors to
//    AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <alljoyn/Status.h>
#import <alljoyn/PermissionConfigurator.h>
#import "AJNBusAttachment.h"
#import "AJNGUID.h"
#import "AJNCertificateX509.h"
#import "AJNKeyInfoECC.h"
#import "AJNCryptoECC.h"

using namespace ajn;

typedef enum {
    NOT_CLAIMABLE = 0, ///< The application is not claimed and not accepting claim requests.
    CLAIMABLE = 1,     ///< The application is not claimed and is accepting claim requests.
    CLAIMED = 2,       ///< The application is claimed and can be configured.
    NEED_UPDATE = 3    ///< The application is claimed, but requires a configuration update (after a software upgrade).
} AJNApplicationState;

typedef uint16_t AJNClaimCapabilities;
typedef enum {
    CAPABLE_ECDHE_NULL = 0x01,
    CAPABLE_ECDHE_PSK = 0x02,   ///< Deprecated, will be removed in a future release.
    CAPABLE_ECDHE_ECDSA = 0x04,
    CAPABLE_ECDHE_SPEKE = 0x08
} AJNClaimCapabilityMasks;

typedef uint16_t AJNClaimCapabilityAdditionalInfo;
typedef enum {
    PSK_GENERATED_BY_SECURITY_MANAGER = 0x01,   ///< The pre-shared key or password is generated by the security manager
    PSK_GENERATED_BY_APPLICATION      = 0x02    ///< The pre-shared key or password is generated by the application
} AJNClaimCapabilityAdditionalInfoMasks;


/**
 * Class to allow the application to manage some limited permission feature.
 */
@interface AJNPermissionConfigurator : AJNObject

- (id)init:(AJNBusAttachment*)withBus;

/**
 * Retrieve the state of the application.
 * @param[out] applicationState the application state
 * @return
 *      - #ER_OK if successful
 *      - #ER_NOT_IMPLEMENTED if the method is not implemented
 *      - #ER_FEATURE_NOT_AVAILABLE if the value is not known
 */
- (QStatus)getApplicationState:(AJNApplicationState*)applicationState;

/**
 * Set the application state.  The state can't be changed from CLAIMED to
 * CLAIMABLE.
 * @param newState The new application state
 * @return
 *      - #ER_OK if action is allowed.
 *      - #ER_INVALID_APPLICATION_STATE if the state can't be changed
 *      - #ER_NOT_IMPLEMENTED if the method is not implemented
 */
- (QStatus)setApplicationState:(AJNApplicationState)withApplicationState;

/**
 * Get the manifest template for the application as XML.
 *
 * @param[out] fromManifestTemplateXml NSString to receive the manifest template as XML.
 *
 * @return ER_OK if successful; otherwise, an error code.
 */
- (QStatus)getManifestTemplateAsXml:(NSString**)fromManifestTemplateXml;

/**
 * Set the manifest template for the application from an XML.
 *
 * @param[in] manifestTemplateXml XML containing the manifest template.
 *
 * @return ER_OK if successful; otherwise, an error code.
 */
- (QStatus)setManifestTemplateFromXml:(NSString*)manifestTemplateXml;

/**
 * Get the authentication mechanisms the application supports for the
 * claim process.
 *
 * @param[out] claimCapabilities The authentication mechanisms the application supports
 *
 * @return
 *  - #ER_OK if successful
 *  - an error status indicating failure
 */
- (QStatus)getClaimCapabilities:(AJNClaimCapabilities*)claimCapabilities;

/**
 * Set the authentication mechanisms the application supports for the
 * claim process.  It is a bit mask.
 *
 * | Mask                | Description              |
 * |---------------------|--------------------------|
 * | CAPABLE_ECDHE_NULL  | claiming via ECDHE_NULL  |
 * | CAPABLE_ECDHE_PSK   | claiming via ECDHE_PSK   |
 * | CAPABLE_ECDHE_ECDSA | claiming via ECDHE_ECDSA |
 *
 * @param[in] claimCapabilities The authentication mechanisms the application supports
 *
 * @return
 *  - #ER_OK if successful
 *  - an error status indicating failure
 */
- (QStatus)setClaimCapabilities:(AJNClaimCapabilities)claimCapabilities;

/**
 * Get the additional information on the claim capabilities.
 * @param[out] additionalInfo The additional info
 *
 * @return
 *  - #ER_OK if successful
 *  - an error status indicating failure
 */
- (QStatus)getClaimCapabilityAdditionalInfo:(AJNClaimCapabilityAdditionalInfo*)additionalInfo;

/**
 * Set the additional information on the claim capabilities.
 * It is a bit mask.
 *
 * | Mask                              | Description                       |
 * |-----------------------------------|-----------------------------------|
 * | PSK_GENERATED_BY_SECURITY_MANAGER | PSK generated by Security Manager |
 * | PSK_GENERATED_BY_APPLICATION      | PSK generated by application      |
 *
 * @param[in] additionalInfo The additional info
 *
 * @return
 *  - #ER_OK if successful
 *  - an error status indicating failure
 */
- (QStatus)setClaimCapabilityAdditionalInfo:(AJNClaimCapabilityAdditionalInfo)additionalInfo;

/**
 * Reset the permission settings by removing the manifest, all the
 * trust anchors, installed policy and certificates. This call
 * must be invoked after the bus attachment has enable peer security.
 * @return ER_OK if successful; otherwise, an error code.
 * @see BusAttachment::EnablePeerSecurity
 */
- (QStatus)reset;

/**
 * Perform claiming of this app locally/offline.
 *
 * @param[in] certificateAuthority Certificate authority public key
 * @param[in] adminGroupGuid Admin group GUID
 * @param[in] adminGroupAuthority Admin group authority public key
 * @param[in] identityCertChain An array of AJNCertificateX509 containing the identity cert chain
 * @param[in] manifestsXmls An array of NSString containing signed manifests in XML format
 *
 * @return
 *    - #ER_OK if the app was successfully claimed
 *    - #ER_FAIL if the app could not be claimed, but could not then be reset back to original state.
 *               App will be in unknown state in this case.
 *    - other error code indicating failure, but app is returned to reset state
 */
- (QStatus)claim:(AJNKeyInfoNISTP256*)certificateAuthority adminGroupGuid:(AJNGUID128*)adminGroupGuid adminGroupAuthority:(AJNKeyInfoNISTP256*)adminGroupAuthority identityCertChain:(NSArray*)identityCertChain manifestsXmls:(NSArray*)manifestsXmls;

/**
 * Perform a local UpdateIdentity to replace the identity certificate chain and
 * the signed manifests. If successful, already-installed certificates and signed
 * manifests are cleared; on failure, the state of both are unchanged.
 *
 * @param[in] certs Identity cert chain to be installed
 * @param[in] manifestsXmls An array of NSStrings containing Signed manifests in XML format
 *
 * @return
 *    - #ER_OK if the identity was successfully updated
 *    - other error code indicating failure
 */
- (QStatus)updateIdentity:(NSArray*)certs manifestsXmls:(NSArray*)manifestsXmls;

/**
 * Retrieve the local app's identity certificate chain.
 *
 * @param[out] certChain An array of AJNCertificateX509 containing the identity certificate chain
 *
 * @return
 *    - #ER_OK if the chain is successfully stored in certChain
 *    - other error indicating failure
 */
- (QStatus)getIdentity:(NSMutableArray*)certChain;

/**
 * Install signed manifests to the local app.
 *
 * @param[in] manifestsXmls An array of NSStrings containing signed manifests to install in XML format
 * @param[in] append True to append the manifests to any already installed, or false to clear manifests out first
 *
 * On failure, the installed set of manifests is unchanged.
 *
 * @return
 *    - #ER_OK if manifests are successfully installed
 *    - #ER_DIGEST_MISMATCH if none of the manifests have been signed
 *    - other error code indicating failure
 */
- (QStatus)installManifests:(NSMutableArray*)manifestsXmls append:(BOOL)append;

/**
 * Retrieve the local app's identity certificate information.
 *
 * @param[out] serial Identity certificate's serial
 * @param[out] keyInfo Identity certificate's KeyInfoNISTP256 structure
 *
 * @return
 *    - #ER_OK if the identity certificate information is placed in the parameters
 *    - #ER_CERTIFICATE_NOT_FOUND if no identity certificate is installed
 *    - other error code indicating failure
 */
- (QStatus)getIdentityCertificateId:(NSString**)serial issuerKeyInfo:(AJNKeyInfoNISTP256*)issuerKeyInfo;

/**
 * Reset the local app's policy to the default policy.
 *
 * @return
 *    - #ER_OK if the policy was successfully reset
 *    - other error code indicating failure
 */
- (QStatus)resetPolicy;

/**
 * Get the membership certificate summaries.
 *
 * @param[out] serials A mutable array of NSString to receive all the serial numbers
 * @param[out] keyInfos A mutable array of AJNKeyInfoNISTP256 to receive all the issuer key information structures
 *
 * @remarks Existing contents of serials and keyInfos will be overwritten. If this method fails, or
 *          there are no membership certificates installed, both will be returned empty.
 *
 * @return
 *    - #ER_OK if the membership summaries are successfully retrieved
 *    - other error indicating failure
 */
- (QStatus)getMembershipSummaries:(NSMutableArray*)serials keyInfos:(NSMutableArray*)keyInfos;

/**
 * Install a membership certificate chain.
 *
 * @param[in] certChain An array of AJNCertificateX509 containing the certificate chain
 *
 * @return
 *    - #ER_OK if the membership certificate chain is successfully installed
 *    - other error code indicating failure
 */
- (QStatus)installMembership:(NSArray*)certChain;

/**
 * Remove a membership certificate chain.
 *
 * @param[in] serial Serial number of the certificate
 * @param[in] issuerPubKey Pointer to certificate issuer's public key
 * @param[in] issuerAki Certificate issuer's AKI
 *
 * @return
 *    - #ER_OK if the certificate was found and removed
 *    - #ER_CERTIFICATE_NOT_FOUND if the certificate was not found
 *    - other error code indicating failure
 */
- (QStatus)removeMembership:(NSString*)serial issuerPubKey:(AJNECCPublicKey*)issuerPubKey issuerAki:(NSString*)issuerAki;

/**
 * Signal the app locally that management is starting.
 *
 * @return
 *    - #ER_OK if the start management signal was sent
 *    - #ER_MANAGEMENT_ALREADY_STARTED if the app is already in this state
 */
- (QStatus)startManagement;

/**
 * Signal the app locally that management is ending.
 *
 * @return
 *    - #ER_OK if the start management signal was sent
 *    - #ER_MANAGEMENT_NOT_STARTED if the app was not in the management state
 */
- (QStatus)endManagement;

@end