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

#include "vr/CCVRCardboardRenderer.h"
#include "vr/CCVRCardboardHeadTracker.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/ccGLStateCache.h"
#include "base/CCDirector.h"
#include "2d/CCScene.h"
#include "2d/CCCamera.h"
#include "2d/CCSprite.h"
#include "platform/CCGLView.h"
#include "platform/android/jni/JniHelper.h"
#include "vr/cardboard/CbApi_Helpers.h"


NS_CC_BEGIN

VRCardboardRenderer::VRCardboardRenderer()
{
    _headTracker = new VRCardboardHeadTracker;
}

VRCardboardRenderer::~VRCardboardRenderer()
{
    CC_SAFE_DELETE(_headTracker);
}

void VRCardboardRenderer::setup(GLView* glview)
{
    cbJava java;
    java.ActivityObject = JniHelper::getEnv()->NewGlobalRef(JniHelper::getActivity());
    java.Env = JniHelper::getEnv();
    JniHelper::getEnv()->GetJavaVM(&java.Vm);
    if (cbapi_Initialize(&java, &_hmd)){
        _eyes = cbapi_GetEyes();
    }
    
    for (unsigned short i = 0; i < CB_EYE_NUM; ++i){
        float suggestedEyeFovDegreesX = _eyes.eyeParams[i].fov.left + _eyes.eyeParams[i].fov.right;
        float suggestedEyeFovDegreesY = _eyes.eyeParams[i].fov.bottom + _eyes.eyeParams[i].fov.top;
        auto projection = cbMatrix4_CreateProjectionFov(suggestedEyeFovDegreesX, suggestedEyeFovDegreesY, 0.0f, 0.0f, CBAPI_ZNEAR, 5000.0f);
        _eyeProjections[i].set((const GLfloat *)(cbMatrix4_Transpose(&projection).M[0]));
    }
    cbapi_EnterVrMode();
}

void VRCardboardRenderer::cleanup()
{
    cbapi_LeaveVrMode();
}

VRIHeadTracker* VRCardboardRenderer::getHeadTracker()
{
    return _headTracker;
}

void VRCardboardRenderer::render(Scene* scene, Renderer* renderer)
{
    Mat4 headView = _headTracker->getLocalRotation();
    Mat4 transform;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    cbapi_beforeDrawFrame();
    glEnable(GL_SCISSOR_TEST);
    for (unsigned short i = 0; i < CB_EYE_NUM; ++i){
        auto vp = _eyes.eyeParams[i].viewport;
        Camera::setDefaultViewport(experimental::Viewport(vp.x, vp.y, vp.width, vp.height));
        glScissor(vp.x, vp.y, vp.width, vp.height);
        glClearColor(0.125f, 0.125f, 0.125f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        const float eyeOffset = ( i ? -0.5f : 0.5f ) * _hmd.device.interLensDistance;
        Mat4::createTranslation(eyeOffset, 0, 0, &transform);
        transform *= headView;
        scene->render(renderer, transform.getInversed(), &_eyeProjections[i]);
        
        // Explicitly clear the border texels to black because OpenGL-ES does not support GL_CLAMP_TO_BORDER.
        {
            // Clear to fully opaque black.
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            // bottom
            glScissor(vp.x, vp.y, vp.width, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            // top
            glScissor(vp.x, vp.height - 1, vp.width, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            // left
            glScissor(vp.x, vp.y, 1, vp.height);
            glClear(GL_COLOR_BUFFER_BIT);
            // right
            glScissor(vp.x + vp.width - 1, vp.y, 1, vp.height);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }
    glDisable(GL_SCISSOR_TEST);
    cbapi_afterDrawFrame();
    
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
