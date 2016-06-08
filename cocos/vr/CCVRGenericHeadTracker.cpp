/****************************************************************************
 Copyright (c) 2016 Google Inc.
 Copyright (c) 2016 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

// IMPORTANT
// For iOS/Mac, this file is treated as an "Objective-C++" file.
// To change this behvior, use the File Inspector from Xcode

#include "vr/CCVRGenericHeadTracker.h"
#include "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import <CoreMotion/CoreMotion.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

NS_CC_BEGIN

//////

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static Mat4 matrixFromRotationMatrix(const CMRotationMatrix& rotationMatrix)
{
    return Mat4(rotationMatrix.m11,
                rotationMatrix.m21,
                rotationMatrix.m31,
                0.0f,

                rotationMatrix.m12,
                rotationMatrix.m22,
                rotationMatrix.m32,
                0.0f,

                rotationMatrix.m13,
                rotationMatrix.m23,
                rotationMatrix.m33,
                0.0f,

                0.0f,
                0.0f,
                0.0f,
                1.0f);
}
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

static Mat4 getRotateEulerMatrix(float x, float y, float z)
{
    x *= (float)(M_PI / 180.0f);
    y *= (float)(M_PI / 180.0f);
    z *= (float)(M_PI / 180.0f);
    float cx = (float) cos(x);
    float sx = (float) sin(x);
    float cy = (float) cos(y);
    float sy = (float) sin(y);
    float cz = (float) cos(z);
    float sz = (float) sin(z);
    float cxsy = cx * sy;
    float sxsy = sx * sy;
    Mat4 matrix;
    matrix.m[0] = cy * cz;
    matrix.m[1] = -cy * sz;
    matrix.m[2] = sy;
    matrix.m[3] = 0.0f;
    matrix.m[4] = cxsy * cz + cx * sz;
    matrix.m[5] = -cxsy * sz + cx * cz;
    matrix.m[6] = -sx * cy;
    matrix.m[7] = 0.0f;
    matrix.m[8] = -sxsy * cz + sx * sz;
    matrix.m[9] = sxsy * sz + sx * cz;
    matrix.m[10] = cx * cy;
    matrix.m[11] = 0.0f;
    matrix.m[12] = 0.0f;
    matrix.m[13] = 0.0f;
    matrix.m[14] = 0.0f;
    matrix.m[15] = 1.0f;
    return matrix;
}

VRGenericHeadTracker::VRGenericHeadTracker()
: _localPosition(Vec3::ZERO)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _motionMgr = [[CMMotionManager alloc] init];
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    startTracking();
#endif
}

VRGenericHeadTracker::~VRGenericHeadTracker()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    stopTracking();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [(CMMotionManager*)_motionMgr release];
#endif
}

void VRGenericHeadTracker::startTracking()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CMMotionManager* motionMgr = (CMMotionManager*)_motionMgr;
    if (motionMgr.isDeviceMotionAvailable && !motionMgr.isDeviceMotionActive)
    {
        [motionMgr startDeviceMotionUpdatesUsingReferenceFrame:CMAttitudeReferenceFrameXArbitraryZVertical];
    }

    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIInterfaceOrientationLandscapeLeft)
    {
        _deviceToDisplay = getRotateEulerMatrix(0.f, 0.f, 90.f);
    }
    else if (orientation == UIInterfaceOrientationLandscapeRight)
    {
        _deviceToDisplay = getRotateEulerMatrix(0.f, 0.f, -90.f);
    }

    // the inertial reference frame has z up and x forward, while the world has z out and x right
    _worldToInertialReferenceFrame = getRotateEulerMatrix(-90.f, 0.f, 90.f);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _deviceToDisplay = getRotateEulerMatrix(0.f, 0.f, -90.f);
    _worldToInertialReferenceFrame = getRotateEulerMatrix(-90.f, 0.f, 90.f);
#endif
}

void VRGenericHeadTracker::stopTracking()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [(CMMotionManager*)_motionMgr stopDeviceMotionUpdates];
#endif
}

Vec3 VRGenericHeadTracker::getLocalPosition()
{
    return _localPosition;
}

Mat4 VRGenericHeadTracker::getLocalRotation()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CMMotionManager* motionMgr = (CMMotionManager*)_motionMgr;
    CMDeviceMotion *motion = motionMgr.deviceMotion;

    CMRotationMatrix rotationMatrix = motion.attitude.rotationMatrix;
    Mat4 inertialReferenceFrameToDevice0 = matrixFromRotationMatrix(rotationMatrix); // note the matrix inversion
    Mat4 inertialReferenceFrameToDevice = inertialReferenceFrameToDevice0.getTransposed();
    Mat4 worldToDevice =  inertialReferenceFrameToDevice * _worldToInertialReferenceFrame;
    return  _deviceToDisplay * worldToDevice;

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static const std::string helperClassName = "org/cocos2dx/lib/Cocos2dxHelper";
    auto rotMatrix = JniHelper::callStaticFloatArrayMethod(helperClassName, "getSensorRotationMatrix");

    Mat4 inertialReferenceFrameToDevice(rotMatrix);
    Mat4 worldToDevice =  inertialReferenceFrameToDevice * _worldToInertialReferenceFrame;
    return  _deviceToDisplay * worldToDevice;
#else
    return Mat4::IDENTITY;
#endif
}

NS_CC_END
