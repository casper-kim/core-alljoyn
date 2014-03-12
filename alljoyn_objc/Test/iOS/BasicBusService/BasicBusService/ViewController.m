////////////////////////////////////////////////////////////////////////////////
// //    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
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

#import "ViewController.h"
#import "PingService.h"

@interface ViewController () <PingServiceDelegate>

@property (nonatomic) BOOL isStarted;

@end

@implementation ViewController

@synthesize advertisedNameTextField = _advertisedNameTextField;
@synthesize eventsTextView = _eventsTextView;
@synthesize startButton = _startButton;
@synthesize isStarted = _isStarted;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [PingService.sharedInstance setDelegate:self];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)didTouchStartButton:(id)sender
{
    if (self.isStarted) {
        [PingService.sharedInstance stop];
        [self.startButton setTitle:@"Start" forState:UIControlStateNormal];
    }
    else {
        [PingService.sharedInstance start:self.advertisedNameTextField.text];
        [self.startButton setTitle:@"Stop" forState:UIControlStateNormal];
    }
    self.isStarted = !self.isStarted;
}

#pragma mark - PingServiceDelegate implementation

- (AJNTransportMask)transportType
{
    AJNTransportMask transportMask;
    switch (self.transportTypeSegmentedControl.selectedSegmentIndex) {
        case 0:
            transportMask = kAJNTransportMaskAny;
            break;
            
        case 1:
            transportMask = kAJNTransportMaskICE;
            break;

        case 2:
            transportMask = kAJNTransportMaskAny ^ kAJNTransportMaskICE;
            break;

        default:
            break;
    }
    return transportMask;    
}

// The delegate is called once a client joins a session with the service
//
- (void)client:(NSString *)clientName didJoinSession:(AJNSessionId)sessionId
{
    [self receivedStatusMessage:[NSString stringWithFormat:@"Client %@ joined session %u", clientName, sessionId]];
}

// The delegate is called when a client leaves a session
//
- (void)client:(NSString *)clientName didLeaveSession:(AJNSessionId)sessionId
{
    [self receivedStatusMessage:[NSString stringWithFormat:@"Client %@ left session %u", clientName, sessionId]];    
}

// Send updates on internal state of Ping Service
//
- (void)receivedStatusMessage:(NSString*)message
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSMutableString *string = self.eventsTextView.text.length ? [self.eventsTextView.text mutableCopy] : [[NSMutableString alloc] init];
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        [formatter setTimeStyle:NSDateFormatterMediumStyle];
        [formatter setDateStyle:NSDateFormatterShortStyle];
        [string appendFormat:@"[%@]\n",[formatter stringFromDate:[NSDate date]]];
        [string appendString:message];
        [string appendString:@"\n\n"];
        [self.eventsTextView setText:string];
        NSLog(@"%@",message);
        [self.eventsTextView scrollRangeToVisible:NSMakeRange([self.eventsTextView.text length], 0)];
    });    
}

@end