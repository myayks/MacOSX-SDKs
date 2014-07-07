/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
 * @header IODVDMedia
 * @abstract
 * This header contains the IODVDMedia class definition.
 */

#ifndef _IODVDMEDIA_H
#define _IODVDMEDIA_H

/*!
 * @defined kIODVDMediaClass
 * @abstract
 * kIODVDMediaClass is the name of the IODVDMedia class.
 * @discussion
 * kIODVDMediaClass is the name of the IODVDMedia class.
 */

#define kIODVDMediaClass "IODVDMedia"

/*!
 * @defined kIODVDMediaTypeKey
 * @abstract
 * kIODVDMediaTypeKey is a property of IODVDMedia objects.  It has an OSString
 * value.
 * @discussion
 * The kIODVDMediaTypeKey property identifies the DVD media type (DVD-ROM,
 * DVD-R, DVD-RW, DVD+RW, DVD-RAM, etc).  See the kIODVDMediaType contants
 * for possible values.
 */

#define kIODVDMediaTypeKey "Type"

/*!
 * @defined kIODVDMediaTypeROM
 * The kIODVDMediaTypeKey constant for DVD-ROM media.
 */

#define kIODVDMediaTypeROM "DVD-ROM"

/*!
 * @defined kIODVDMediaTypeR
 * The kIODVDMediaTypeKey constant for DVD Recordable (DVD-R) media.
 */

#define kIODVDMediaTypeR "DVD-R"

/*!
 * @defined kIODVDMediaTypeRW
 * The kIODVDMediaTypeKey constant for DVD ReWritable (DVD-RW) media.
 */

#define kIODVDMediaTypeRW "DVD-RW"

/*!
 * @defined kIODVDMediaTypePlusRW
 * The kIODVDMediaTypeKey constant for DVD "Plus" ReWritable (DVD+RW) media.
 */

#define kIODVDMediaTypePlusRW "DVD+RW"

/*!
 * @defined kIODVDMediaTypeRAM
 * The kIODVDMediaTypeKey constant for DVD-RAM media.
 */

#define kIODVDMediaTypeRAM "DVD-RAM"

#endif /* !_IODVDMEDIA_H */
