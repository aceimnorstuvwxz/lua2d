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

#ifndef __Lua2d__ImageSprite__
#define __Lua2d__ImageSprite__

#include <memory>
#include <string>

#include "Sprite.h"
#include "utils.h"
#include "Renderer.h"
#include "cppgl/cppgl.h"

NS_L2D_BEGIN

class ImageSprite;
typedef std::shared_ptr<ImageSprite> SPImageSprite;
class Renderer;
typedef std::shared_ptr<Renderer> SPRenderer;

class ImageSprite: public Sprite
{
public:
    static SPImageSprite create(const std::string& fileName, int width, int height);
    virtual void load() override;
    virtual void draw(SPRenderer renderer) override;

private:
    ImageSprite(const std::string& fileName, int width, int height);

    // image display size, could be different from raw size
    int _width; // image width
    int _height; // image height

    std::string _fileName;
    bool _loaded = false;

    // drawing data
    cppgl::SPTexture _texture;

    // ImageSprite share same VAO VBO and Program
    static cppgl::SPVertexArray _vao;
    static cppgl::SPVertexBuffer _vbo;
    static cppgl::SPProgram _program;
    
    static void initStatic();
    static bool _staticInited;
};

NS_L2D_END

#endif /* defined(__Lua2d__ImageSprite__) */
