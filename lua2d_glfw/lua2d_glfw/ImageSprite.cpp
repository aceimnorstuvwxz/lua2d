//
//  ImageSprite.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "ImageSprite.h"

#include <OpenGl/gl3.h>

#include "utils.h"

NS_L2D_BEGIN

ImageSprite::ImageSprite(const std::string& fileName, const int& width, const int& height):_fileName(fileName), _w(width),_h(height)
{
    //nothing to do
}

void ImageSprite::load()
{


}

void ImageSprite::draw()
{
    LOG("ImageSprite::draw()");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

NS_L2D_END
