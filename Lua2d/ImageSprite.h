//
//  ImageSprite.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__ImageSprite__
#define __Lua2d__ImageSprite__

#include <stdio.h>
#include <string>
#include "Sprite.h"
 
namespace l2d
{
    class ImageSprite :public Sprite
    {
    private:
        // image display size, could be different from raw size
        int _w; // image width
        int _h; // image height
        
    public:
        ImageSprite(const std::string& fileName, const int& width, const int& height);

        void draw();
    };
}

#endif /* defined(__Lua2d__ImageSprite__) */
