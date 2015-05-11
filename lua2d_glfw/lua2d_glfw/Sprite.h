/*
 Copyright (c) 2015 chenbingfeng (iichenbf#gmail.com)

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
 */

#ifndef __Lua2d__Sprite__
#define __Lua2d__Sprite__

#include <memory>

#include "utils.h"
#include "Node.h"
#include "cppgl/cppgl.h"

NS_L2D_BEGIN

class Renderer;
typedef std::shared_ptr<Renderer> SPRenderer;

class Sprite :public Node
{
public:
    void hide();
    void show();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void rotate(float degree);
    void setAlpha(float alpha);
    void scale(float scaler);

    // load resource and init GL things, make ready for draw
    // it may cost some time.
    virtual void load() = 0;

    // draw in GL context.
    virtual void draw(SPRenderer renderer) = 0;


    virtual glm::mat4& getModel();
protected:
    bool _isVisible = true;
    float _alpha = 1.0f; //[0.0f, 1.0f]

    float _x = 0.0f; // x position in parent
    float _y = 0.0f; // y position in parent
    float _z = 0.0f; // z position in parent, [0, 99]

    // anchor is the center of rotating and scaling
    float _anchorX = 0.0f; // anchor position x in self
    float _anchorY = 0.0f; // anchor position y in self
    float _rotate = 0.0f; // rotate degree in clockwise
    float _scale = 1.0f; //default 1

    glm::mat4 _model;
    bool _isDirty = true;
};

NS_L2D_END

#endif /* defined(__Lua2d__Sprite__) */