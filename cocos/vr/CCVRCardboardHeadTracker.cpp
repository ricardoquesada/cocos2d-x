/****************************************************************************
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

#include "platform/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/CCPlatformMacros.h"
#include "vr/CCVRCardboardHeadTracker.h"
#include "vr/cardboard/CbApi_Helpers.h"


NS_CC_BEGIN

VRCardboardHeadTracker::VRCardboardHeadTracker()
{
}

VRCardboardHeadTracker::~VRCardboardHeadTracker()
{
}

Vec3 VRCardboardHeadTracker::getLocalPosition()
{
    auto headView = cbapi_getLastHeadView();
    headView = cbMatrix4_Inverse(&headView);
    return Vec3(headView.M[0][3], headView.M[1][3], headView.M[2][3]);
}

Mat4 VRCardboardHeadTracker::getLocalRotation()
{
    auto headView = cbapi_getLastHeadView();
    headView.M[0][3] = headView.M[1][3] = headView.M[2][3] = 0.0f;
    Mat4 viewMat;
    viewMat.set((const GLfloat *)(cbMatrix4_Transpose(&headView).M[0]));
    viewMat.inverse();
    return viewMat;
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
