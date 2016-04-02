/****************************************************************************
 Copyright (c) 2016 Google
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

#ifndef __CC_DISTORTION_RENDERER_H_
#define __CC_DISTORTION_RENDERER_H_

#include "platform/CCPlatformMacros.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

class Distortion;

class DistortionRenderer
{
  public:
    DistortionRenderer();
    ~DistortionRenderer();
    
    void beforeDrawFrame();
    void afterDrawFrame();
    
    void setResolutionScale(float scale);
    
    bool restoreGLStateEnabled();
    void setRestoreGLStateEnabled(bool enabled);
    
    bool chromaticAberrationEnabled();
    void setChromaticAberrationEnabled(bool enabled);
    
    bool vignetteEnabled();
    void setVignetteEnabled(bool enabled);
    
    bool viewportsChanged();

    
private:
    class DistortionMesh
    {
      public:
        int _indices;
        int _arrayBufferID;
        int _elementBufferID;

        DistortionMesh();
        DistortionMesh(Distortion *distortionRed,
                       Distortion *distortionGreen,
                       Distortion *distortionBlue,
                       float screenWidth, float screenHeight,
                       float xEyeOffsetScreen, float yEyeOffsetScreen,
                       float textureWidth, float textureHeight,
                       float xEyeOffsetTexture, float yEyeOffsetTexture,
                       float viewportXTexture, float viewportYTexture,
                       float viewportWidthTexture,
                       float viewportHeightTexture,
                       bool vignetteEnabled);
    };
    
    struct EyeViewport
    {
      public:
        float x;
        float y;
        float width;
        float height;
        float eyeX;
        float eyeY;

        std::string toString() const;
    };
    
    struct ProgramHolder
    {
      public:
        ProgramHolder() :
        program(-1),
        positionLocation(-1),
        vignetteLocation(-1),
        redTextureCoordLocation(-1),
        greenTextureCoordLocation(-1),
        blueTextureCoordLocation(-1),
        uTextureCoordScaleLocation(-1),
        uTextureSamplerLocation(-1) {}
        
        GLint program;
        GLint positionLocation;
        GLint vignetteLocation;
        GLint redTextureCoordLocation;
        GLint greenTextureCoordLocation;
        GLint blueTextureCoordLocation;
        GLint uTextureCoordScaleLocation;
        GLint uTextureSamplerLocation;
    };
    
    GLuint _textureID;
    GLuint _renderbufferID;
    GLuint _framebufferID;
    // int _originalFramebufferID;
    GLenum _textureFormat;
    GLenum _textureType;
    float _resolutionScale;
    bool _restoreGLStateEnabled;
    bool _chromaticAberrationCorrectionEnabled;
    bool _vignetteEnabled;
    DistortionMesh *_leftEyeDistortionMesh;
    DistortionMesh *_rightEyeDistortionMesh;
    EyeViewport *_leftEyeViewport;
    EyeViewport *_rightEyeViewport;
    bool _fovsChanged;
    bool _viewportsChanged;
    bool _textureFormatChanged;
    bool _drawingFrame;
    float _xPxPerTanAngle;
    float _yPxPerTanAngle;
    float _metersPerTanAngle;
    
    ProgramHolder *_programHolder;
    ProgramHolder *_programHolderAberration;
    
    void setTextureFormat(GLint textureFormat, GLint textureType);
    void updateTextureAndDistortionMesh();
    void undistortTexture(GLint textureID);

    DistortionMesh *createDistortionMesh(EyeViewport *eyeViewport,
                                         float textureWidthTanAngle,
                                         float textureHeightTanAngle,
                                         float xEyeOffsetTanAngleScreen,
                                         float yEyeOffsetTanAngleScreen);
    void renderDistortionMesh(DistortionMesh *mesh, GLint textureID);
    float computeDistortionScale(Distortion *distortion,
                                 float screenWidthM,
                                 float interpupillaryDistanceM);
    int createTexture(GLint width, GLint height, GLint textureFormat, GLint textureType);
    int setupRenderTextureAndRenderbuffer(int width, int height);
    ProgramHolder *createProgramHolder(bool aberrationCorrected);
};

NS_CC_END

#endif // __CC_DISTORTION_RENDERER_H_
