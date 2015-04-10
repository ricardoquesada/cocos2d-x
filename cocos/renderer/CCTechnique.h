/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.

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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#ifndef __cocos2d_libs__CCTechnique__
#define __cocos2d_libs__CCTechnique__

#include <string>
#include "platform/CCPlatformMacros.h"
#include "renderer/CCRenderState.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Pass;
class GLProgramState;

/// Technique
class CC_DLL Technique : public RenderState
{
    friend class Renderer;

public:
    /** Creates a new Technique with a GLProgramState.
     Method added to support legacy code
     */
    static Technique* createWithGLProgramState(GLProgramState* state);

    /** Adds a new pass to the Technique.
     Order matters. First added, first rendered
     */
    void addPass(Pass* pass);

    /** Returns the name of the Technique */
    std::string getName() const;

    /** Returns the Pass at given index */
    Pass* getPassByIndex(ssize_t index) const;

    /** Returns the number of Passes in the Technique */
    ssize_t getPassCount() const;

protected:
    Technique();
    ~Technique();

    std::string _name;

    Vector<Pass*> _passes;
};

NS_CC_END

#endif /* defined(__cocos2d_libs__CCTechnique__) */
