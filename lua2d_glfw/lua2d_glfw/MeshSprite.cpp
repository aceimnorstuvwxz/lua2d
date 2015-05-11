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

#include "MeshSprite.h"
#include "Director.h"

NS_L2D_BEGIN

SPMeshSprite MeshSprite::create(const std::string &obj_file, const std::string &tex_file)
{
    if (!_staticInited) initStatic();
    return SPMeshSprite(new MeshSprite(obj_file, tex_file));
}

MeshSprite::MeshSprite(const std::string& obj_file, const std::string& tex_file):_objFile(obj_file), _texFile(tex_file){/*empty*/}

void MeshSprite::load()
{
    if (_loaded) LOG("MeshSprite", _objFile, "already loaded.");
    assert(!_loaded);
    _loaded = true;

    auto mesh = cppgl::Mesh::create(_objFile);
    _vertexCount = mesh->vertexCount();
    _vbo = cppgl::VertexBuffer::create(mesh->vertices(), sizeof(cppgl::Vertex) * mesh->vertexCount(), cppgl::BufferUsage::StaticDraw);
    LOG(_objFile, "vertex count", mesh->vertexCount());
    _vao = cppgl::VertexArray::create();
    _vao->bindAttribute(_program->getAttribute("position"), *_vbo, cppgl::Type::Float, 3, 8*sizeof(float), 0);
    _vao->bindAttribute(_program->getAttribute("texcoord"), *_vbo, cppgl::Type::Float, 2, 8*sizeof(float), 3*sizeof(float));

    auto image = cppgl::Image::create(_texFile);
    image->load();
    _texture = cppgl::Texture::create(image);
    _texture->setWrapping(cppgl::Wrapping::Repeat, cppgl::Wrapping::Repeat);
    _texture->setFilters(cppgl::Filter::Linear, cppgl::Filter::Linear);
}

void MeshSprite::draw(SPRenderer renderer)
{
    auto context = renderer->getContext();
    context->useProgram(_program);
    _program->setUniform(_program->getUniform("view"), Director::getInstance().getView());
    _program->setUniform(_program->getUniform("proj"), Director::getInstance().getProj());
    _program->setUniform(_program->getUniform("model"), getModel());
    context->bindTexture(_texture, 0);
    context->drawArrays(*_vao, cppgl::Primitive::Triangles, 0, (unsigned int)_vertexCount);
}

bool MeshSprite::_staticInited = false;

void MeshSprite::initStatic()
{
    _staticInited = true;
    const char* vertexSource =
    "#version 150\n"
    "\n"
    "in vec3 position;\n"
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
    "    gl_Position = proj * view * model * vec4(position, 1.0);\n"
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
}

cppgl::SPProgram MeshSprite::_program;
NS_L2D_END