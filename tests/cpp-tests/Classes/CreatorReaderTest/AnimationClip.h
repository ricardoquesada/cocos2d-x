/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

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

#pragma once

#include "cocos2d.h"

#include "AnimationClipProperties.h"

#ifdef __cplusplus
#define NS_CCR_BEGIN                     namespace creator {
#define NS_CCR_END                       }
#define USING_NS_CCR                     using namespace creator
#else
#define NS_CC_BEGIN
#define NS_CC_END
#define USING_NS_CC
#define NS_CC
#endif

NS_CCR_BEGIN

class AnimationClip: public cocos2d::Ref
{
public:
    enum class WrapMode {Default, Normal, Loop, PingPong, Reverse, LoopReverse, PingPongReverse};

    static AnimationClip* create();
    bool init();

    void setName(const std::string& name);
    void setUUID(const std::string& uuid);
    void setDuration(float duration);
    void setSample(float sample);
    void setSpeed(float speed);
    void setWrapMode(WrapMode wrapMode);
    void setAnimProperties(const AnimProperties& properties);

protected:
    AnimationClip();
    virtual ~AnimationClip();

    std::string _name;
    std::string _uuid;
    float _duration;
    float _sample;
    float _speed;
    WrapMode _wrapMode;
    AnimProperties _animProperties;
    int _objFlags;
//    AnimEvents _events;       // FIXME: neede ?
};

NS_CCR_END
