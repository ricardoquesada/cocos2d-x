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

#include "renderer/CCEye.h"
#include "renderer/CCFieldOfView.h"
#include "renderer/CCViewport.h"

NS_CC_BEGIN

Eye::Eye(Type eyeType) :
    _type(eyeType),
    _eyeView(Mat4::IDENTITY),
    _projectionChanged(true),
    _perspective(Mat4::IDENTITY),
    _lastZNear(0),
    _lastZFar(0)
{
    _viewport = new Viewport();
    _fov = new FieldOfView();
}

Eye::~Eye()
{
    if (_viewport != nullptr) { delete _viewport; }
    if (_fov != nullptr) { delete _fov; }
}

Eye::Type Eye::type()
{
    return _type;
}

Mat4 Eye::eyeView()
{
    return _eyeView;
}

void Eye::setEyeView(const Mat4& eyeView)
{
    _eyeView = eyeView;
}

Mat4 Eye::perspective(float zNear, float zFar)
{
    if (!_projectionChanged && _lastZNear == zNear && _lastZFar == zFar)
    {
        return _perspective;
    }
    _perspective = fov()->toPerspectiveMatrix(zNear, zFar);
    _lastZNear = zNear;
    _lastZFar = zFar;
    _projectionChanged = false;
    return _perspective;
}

Viewport *Eye::viewport()
{
    return _viewport;
}

FieldOfView *Eye::fov()
{
    return _fov;
}

void Eye::setProjectionChanged()
{
    _projectionChanged = true;
}

NS_CC_END
