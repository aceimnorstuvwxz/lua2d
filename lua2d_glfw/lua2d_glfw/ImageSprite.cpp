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

#include "ImageSprite.h"
#include "Director.h"
#include <iostream>

NS_L2D_BEGIN

SPImageSprite ImageSprite::create(const std::string &fileName, int width, int height)
{
    if (!_staticInited) initStatic();
    return SPImageSprite(new ImageSprite(fileName, width, height));
}

ImageSprite::ImageSprite(const std::string& fileName, int width, int height):
_fileName(fileName), _width(width),_height(height){/*empty*/}

void ImageSprite::load()
{
    if (_loaded) LOG("ImageSprite", _fileName, "already loaded.");
    assert(!_loaded);
    _loaded = true;
    auto image = cppgl::Image::create(_fileName);
    image->load();
    _texture = cppgl::Texture::create(image);
    _texture->setWrapping(cppgl::Wrapping::Repeat, cppgl::Wrapping::Repeat);
    _texture->setFilters(cppgl::Filter::Linear, cppgl::Filter::Linear);
}

void ImageSprite::draw(SPRenderer renderer)
{
    auto context = renderer->getContext();
    context->useProgram(_program);
    // setUniform must after useProgram
    _program->setUniform(_program->getUniform("view"), Director::getInstance().getView());
    _program->setUniform(_program->getUniform("proj"), Director::getInstance().getProj());
    _program->setUniform(_program->getUniform("model"), getModel());
    context->bindTexture(_texture, 0);
    context->drawArrays(*_vao, cppgl::Primitive::Triangles, 0, 6);
}

//static area
bool ImageSprite::_staticInited = false;

void ImageSprite::initStatic()
{
    _staticInited = true;
    const char* vertexSource =
    "#version 150\n"
    "\n"
    "in vec2 position;\n"
    "in vec2 texcoord;\n"
    "out vec2 Texcoord;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 proj;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    Texcoord = vec2(texcoord.x, -texcoord.y);\n"
    "    gl_Position = proj * view * model * vec4(position, 0.0, 1.0);\n"
    "}\n";

    const char* fragmentSource =
    "#version 150\n"
    "\n"
    "in vec2 Texcoord;\n"
    "\n"
    "out vec4 outColor;\n"
    "uniform sampler2D tex;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    outColor = texture(tex, Texcoord);\n"
    "}\n";

    auto vert = cppgl::Shader::create(cppgl::ShaderType::Vertex, vertexSource);
    auto frag = cppgl::Shader::create(cppgl::ShaderType::Fragment, fragmentSource);
    _program = cppgl::Program::create(vert, frag);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f
    };
    _vbo = cppgl::VertexBuffer::create(vertices, sizeof(vertices), cppgl::BufferUsage::StaticDraw);
    _vao = cppgl::VertexArray::create();
    _vao->bindAttribute(_program->getAttribute("position"), *_vbo, cppgl::Type::Float, 2, 4*sizeof(float), NULL);
    _vao->bindAttribute(_program->getAttribute("texcoord"), *_vbo, cppgl::Type::Float, 2, 4*sizeof(float), 2*sizeof(float));
}

cppgl::SPVertexArray ImageSprite::_vao;
cppgl::SPVertexBuffer ImageSprite::_vbo;
cppgl::SPProgram ImageSprite::_program;

NS_L2D_END
