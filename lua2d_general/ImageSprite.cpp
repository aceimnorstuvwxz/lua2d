//
//  ImageSprite.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "ImageSprite.h"
#include "utils.h"

namespace l2d
{
    ImageSprite::ImageSprite(const std::string& fileName, const int& width, const int& height):_fileName(fileName), _w(width),_h(height)
    {
        //nothing to do
    }

    void ImageSprite::draw()
    {
        LOG("ImageSprite::draw()");
    }

}
