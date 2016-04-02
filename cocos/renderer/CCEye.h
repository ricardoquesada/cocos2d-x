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


#ifndef __CardboardSDK_iOS__Eye__
#define __CardboardSDK_iOS__Eye__

#include "platform/CCPlatformMacros.h"
#include "math/Mat4.h"


NS_CC_BEGIN

class FieldOfView;
class Viewport;

class Eye
{
  public:

    typedef enum
    {
        TypeMonocular = 0,
        TypeLeft = 1,
        TypeRight = 2
    } Type;

    Eye(Type eye);
    ~Eye();

    Type type();

    Mat4 eyeView();
    void setEyeView(const Mat4& eyeView);
    Mat4 perspective(float zNear, float zFar);
    
    Viewport *viewport();
    FieldOfView *fov();
    
    void setProjectionChanged();
    
private:
    Type _type;
    Mat4 _eyeView;
    Viewport *_viewport;
    FieldOfView *_fov;
    bool _projectionChanged;
    Mat4 _perspective;
    float _lastZNear;
    float _lastZFar;
};

NS_CC_END

#endif
