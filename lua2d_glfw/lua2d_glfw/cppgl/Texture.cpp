//
//  Texture.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Texture.h"

#define PUSH_STATE() GLint restoreId; glGetIntegerv(GL_TEXTURE_BINDING_2D, &restoreId)
#define POP_STATE() glBindTexture(GL_TEXTURE_2D, restoreId)

NS_CPPGL_BEGIN

Texture::Texture()
{
    _gc.create(_obj, glGenTextures, glDeleteTextures);
}

Texture::Texture(const Texture& other)
{
    _gc.copy(other._obj, _obj);
}

Texture::Texture(const Image& image, InternalFormat::internal_format_t internalFormat)
{
    PUSH_STATE();

    gc.create(_obj, glGenTextures, glDeleteTextures);
    glBindTexture(GL_TEXTURE_2D, _obj);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.getWidth(), image.getHeight(), 0, Format::RGBA, DataType::UnsignedByte, image.getPixels());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glGenerateMipmap( GL_TEXTURE_2D );

    POP_STATE();
}

Texture::~Texture()
{
    _gc.destroy(_obj);
}

Texture::operator GLuint() const
{
    return _obj;
}

const Texture& Texture::operator=(const Texture& other)
{
    gc.Copy(o)
}


NS_CPPGL_END