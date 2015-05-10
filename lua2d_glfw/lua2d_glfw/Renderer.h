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

#ifndef __Lua2d__Renderer__
#define __Lua2d__Renderer__

#include <memory>
#include <string>

#include "utils.h"

#include <stdio.h>
#include "Scene.h"
#include "cppgl/cppgl.h"


NS_L2D_BEGIN

class Renderer;
typedef std::shared_ptr<Renderer> SPRenderer;

class Renderer
{
public:
    static SPRenderer create();

    void init(int width, int height, const std::string& titile);
    int getWidth();
    int getHeight();
    cppgl::SPContext getContext();

private:
    Renderer();
    int _width;
    int _height;
    cppgl::SPContext _context;
};

NS_L2D_END

#endif /* defined(__Lua2d__Renderer__) */