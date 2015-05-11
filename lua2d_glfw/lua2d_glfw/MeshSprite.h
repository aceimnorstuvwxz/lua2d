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

#ifndef __lua2d_glfw__MeshSprite__
#define __lua2d_glfw__MeshSprite__

#include <memory>
#include <string>

#include "utils.h"
#include "Sprite.h"
#include "Renderer.h"
#include "cppgl/cppgl.h"

NS_L2D_BEGIN

class MeshSprite;
typedef std::shared_ptr<MeshSprite> SPMeshSprite;

class MeshSprite: public Sprite
{
public:
    static SPMeshSprite create(const std::string& obj_file, const std::string& tex_file);
    virtual void load() override;
    virtual void draw(SPRenderer renderer) override;

private:
    MeshSprite(const std::string& obj_file, const std::string& tex_file);

    std::string _objFile;
    std::string _texFile;
    bool _loaded = false;
    size_t _vertexCount;

    cppgl::SPTexture _texture;
    cppgl::SPVertexBuffer _vbo;
    cppgl::SPVertexArray _vao;

    // MeshSprite share same VAO VBO and Program
    static cppgl::SPProgram  _program;

    static void initStatic();
    static bool _staticInited;
};

NS_L2D_END

#endif /* defined(__lua2d_glfw__MeshSprite__) */
