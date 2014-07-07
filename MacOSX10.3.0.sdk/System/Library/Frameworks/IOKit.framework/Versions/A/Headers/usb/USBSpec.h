/*
 * Copyright (c) 1998-2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


#ifndef __OPEN_SOURCE__
/*
 *
 *	$Id: USBSpec.h,v 1.15 2003/08/20 19:41:41 nano Exp $
 *
 *	$Log: USBSpec.h,v $
 *	Revision 1.15  2003/08/20 19:41:41  nano
 *	
 *	Bug #:
 *	New version's of Nima's USB Prober (2.2b17)
 *	3382540  Panther: Ejecting a USB CardBus card can freeze a machine
 *	3358482  Device Busy message with Modems and IOUSBFamily 201.2.14 after sleep
 *	3385948  Need to implement device recovery on High Speed Transaction errors to full speed devices
 *	3377037  USB EHCI: returnTransactions can cause unstable queue if transactions are aborted
 *	
 *	Also, updated most files to use the id/log functions of cvs
 *	
 *	Submitted by: nano
 *	Reviewed by: rhoads/barryt/nano
 *	
 */
#endif

/*
 * Constants that both OS9 and OSX want to define, and whose values are
 * specified by the USB Standard.
 * Put in a seperate file so they can be included if the OS9 include file isn't already
 * included.
 */
#ifndef _USBSPEC_H
#define _USBSPEC_H

#ifdef __cplusplus
extern "C" {
#endif

    /*!
    @header     USBSpec.h
     @abstract  Constants and definitions of parameters that are used in communcating with USB devices and interfaces.
     @discussion    
     */

    /*!
    @enum Endpoint type
    @discussion Used in IOUSBFindEndpointRequest's type field
    */
enum {
    kUSBControl     = 0,
    kUSBIsoc        = 1,
    kUSBBulk        = 2,
    kUSBInterrupt   = 3,
    kUSBAnyType     = 0xFF
};

    /*!
    @enum Endpoint direction
    @discussion Used in IOUSBFindEndpointRequest's direction field
    */
enum {
    kUSBOut         = 0,
    kUSBIn          = 1,
    kUSBNone        = 2,
    kUSBAnyDirn     = 3
};

    /*!
    @enum Device Request Type
    @discussion This type is encoded in the bmRequestType field of a Device Request.  It specifies the type of request: standard, class or vendor specific.
    */
enum {
    kUSBStandard    = 0,
    kUSBClass       = 1,
    kUSBVendor      = 2
};

    /*!
    @enum Device Request Recipient
    @discussion This recipient is encoded in the bmRequestType field of a Device Request.  It specifies the type of recipient for a request:  the device, the interface, or an endpoint.
    */
enum {
    kUSBDevice      = 0,
    kUSBInterface   = 1,
    kUSBEndpoint    = 2,
    kUSBOther       = 3
};

    /*!
    @enum Device Request
    @discussion Specifies values for the bRequest field of a Device Request.
    */
enum {
    kUSBRqGetStatus     = 0,
    kUSBRqClearFeature  = 1,
    kUSBRqGetState      = 2,
    kUSBRqSetFeature    = 3,
    kUSBRqReserved2     = 4,
    kUSBRqSetAddress    = 5,
    kUSBRqGetDescriptor = 6,
    kUSBRqSetDescriptor = 7,
    kUSBRqGetConfig     = 8,
    kUSBRqSetConfig     = 9,
    kUSBRqGetInterface  = 10,
    kUSBRqSetInterface  = 11,
    kUSBRqSyncFrame     = 12
};

    /*!
    @enum USB Descriptors
    @discussion Specifies values for diffent descriptor types.
    */
enum {
    kUSBAnyDesc             = 0,    // Wildcard for searches
    kUSBDeviceDesc          = 1,
    kUSBConfDesc            = 2,
    kUSBStringDesc          = 3,
    kUSBInterfaceDesc       = 4,
    kUSBEndpointDesc        = 5,
    kUSBDeviceQualifierDesc = 6,
    kUSBOtherSpeedConfDesc  = 7,
    kUSBInterfacePowerDesc  = 8,
    kUSBOnTheGoDesc	    = 9,
    kUSDebugDesc	    = 10,
    kUSBInterfaceAssociationDesc 	= 11,
    kUSBHIDDesc             		= 0x21,
    kUSBReportDesc          		= 0x22,
    kUSBPhysicalDesc        		= 0x23,
    kUSBHUBDesc             		= 0x29
};

    /*!
    @enum Feature Selectors
    @discussion Used with SET/CLEAR_FEATURE requests.
    */
enum {
        kUSBFeatureEndpointStall = 0,
        kUSBFeatureDeviceRemoteWakeup = 1
}; 

    /*!
    @enum USB Power constants
    @discussion Constants relating to USB Power.
    */
enum {
    kUSB100mAAvailable  = 50,
    kUSB500mAAvailable  = 250,
    kUSB100mA           = 50,
    kUSBAtrBusPowered   = 0x80,
    kUSBAtrSelfPowered  = 0x40,
    kUSBAtrRemoteWakeup = 0x20
};

    /*!
    @enum USB Release constants
    @discussion Constants relating to USB releases as found in the bcdUSB field of the Device Descriptor.
    */
enum {
    kUSBRel10       = 0x0100,
    kUSBRel11       = 0x0110,
    kUSBRel20       = 0x0200
};


    /*!
    @enum HID requests
    @discussion Constants for HID requests.
    */
enum {
    kHIDRqGetReport     = 1,
    kHIDRqGetIdle       = 2,
    kHIDRqGetProtocol   = 3,
    kHIDRqSetReport     = 9,
    kHIDRqSetIdle       = 10,
    kHIDRqSetProtocol   = 11
};

    /*!
    @enum HID report types
    @discussion Constants for the three kinds of HID reports.
    */
enum {
    kHIDRtInputReport       = 1,
    kHIDRtOutputReport      = 2,
    kHIDRtFeatureReport     = 3
};


    /*!
    @enum HID Protocol
    @discussion  Used in the SET_PROTOCOL device request
    */
enum {
    kHIDBootProtocolValue   = 0,
    kHIDReportProtocolValue = 1
};


    /*!
    @enum HID Interface Protocol
    @discussion Reported in the bInterfaceProtocol field of the Interface Descriptor.
    */
enum {
    kHIDNoInterfaceProtocol         = 0,
    kHIDKeyboardInterfaceProtocol   = 1,
    kHIDMouseInterfaceProtocol      = 2,
    kUSBVendorSpecificProtocol      = 0xff
};


enum {
    kUSBCapsLockKey         = 0x39,
    kUSBNumLockKey          = 0x53,
    kUSBScrollLockKey       = 0x47
};

    /*!
    @enum Device and Interface Class
    @discussion Constants for USB Device and Interface classes (bDeviceClass and bInterfaceClass).
    */
enum {
    kUSBCompositeClass          = 0,
    kUSBAudioClass              = 1,
    kUSBCommClass               = 2,
    kUSBHIDClass                = 3,
    kUSBDisplayClass            = 4,
    kUSBPrintingClass           = 7,
    kUSBMassStorageClass        = 8,
    kUSBHubClass                = 9,
    kUSBDataClass               = 10,
    kUSBApplicationSpecificClass = 0xFE,
    kUSBVendorSpecificClass     = 0xFF
};

    /*!
    @enum Device and Interface SubClass
    @discussion Constants for USB Device and Interface SubClasses (bDeviceSubClass and bInterfaceSubClass).
*/
enum {
    kUSBCompositeSubClass               = 0,
    kUSBHubSubClass                     = 0,
    kUSBDFUSubClass                     = 0x01,
    kUSBIrDABridgeSubClass              = 0x02,
    kUSBMassStorageRBCSubClass          = 0x01,
    kUSBMassStorageATAPISubClass        = 0x02,
    kUSBMassStorageQIC157SubClass       = 0x03,
    kUSBMassStorageUFISubClass          = 0x04,
    kUSBMassStorageSFF8070iSubClass     = 0x05,
    kUSBMassStorageSCSISubClass         = 0x06,
    kUSBHIDBootInterfaceSubClass        = 0x01,
    kUSBCommDirectLineSubClass          = 0x01,
    kUSBCommAbstractSubClass            = 0x02,
    kUSBCommTelephoneSubClass           = 0x03,
    kUSBCommMultiChannelSubClass        = 0x04,
    kUSBCommCAPISubClass                = 0x05,
    kUSBCommEthernetNetworkingSubClass  = 0x06,
    kUSBATMNetworkingSubClass           = 0x07
};

    /*!
    @enum DFU Class Attributes
    @discussion 
*/
enum {
    kUSBDFUAttributesMask       = 0x07,
    kUSBDFUCanDownloadBit       = 0,
    kUSBDFUCanUploadBit         = 1,
    kUSBDFUManifestationTolerantBit     = 2
};


    /*!
    @enum Property Names
    @discussion USB property names taken from the field names in various descriptors
*/
#define kUSBDeviceClass             "bDeviceClass"
#define kUSBDeviceSubClass          "bDeviceSubClass"
#define kUSBDeviceProtocol          "bDeviceProtocol"
#define kUSBDeviceMaxPacketSize     "bMaxPacketSize0"
#define kUSBVendorID                "idVendor"          // good name
#define kUSBVendorName              kUSBVendorID        // bad name - keep for backward compatibility
#define kUSBProductID               "idProduct"         // good name
#define kUSBProductName             kUSBProductID       // bad name - keep for backward compatibility
#define kUSBDeviceReleaseNumber     "bcdDevice"
#define kUSBManufacturerStringIndex "iManufacturer"
#define kUSBProductStringIndex      "iProduct"
#define kUSBSerialNumberStringIndex "iSerialNumber"
#define kUSBDeviceNumConfigs        "bNumConfigurations"
#define kUSBInterfaceNumber         "bInterfaceNumber"
#define kUSBAlternateSetting        "bAlternateSetting"
#define kUSBNumEndpoints            "bNumEndpoints"
#define kUSBInterfaceClass          "bInterfaceClass"
#define kUSBInterfaceSubClass       "bInterfaceSubClass"
#define kUSBInterfaceProtocol       "bInterfaceProtocol"
#define kUSBInterfaceStringIndex    "iInterface"
#define kUSBConfigurationValue      "bConfigurationValue"

#ifdef __cplusplus
}       
#endif

#endif /* _USBSPEC_H */
