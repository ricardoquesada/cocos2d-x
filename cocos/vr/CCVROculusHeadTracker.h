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

#include "vr/CCVRProtocol.h"
#include "oculus/ovr/OVR_CAPI.h"
#include "math/Vec3.h"
#include "math/Mat4.h"

NS_CC_BEGIN

class CC_DLL VROculusHeadTracker : public VRIHeadTracker
{
public:
    VROculusHeadTracker();
    virtual ~VROculusHeadTracker();

    virtual Vec3 getLocalPosition() override;
    virtual Mat4 getLocalRotation() override;
    
    void setHMD(const ovrHmd &hmd) { _HMD = hmd; }
    void applyTracking(double predictedDisplayTime);
    const ovrTrackingState& getTracking() const { return _tracking; }

protected:
    
    ovrHmd           _HMD;
    ovrTrackingState _tracking;
};

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
