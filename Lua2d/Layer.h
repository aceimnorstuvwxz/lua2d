//
//  Layer.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Layer__
#define __Lua2d__Layer__

#include <stdio.h>
#include "Node.h"
#include "Sprite.h"

namespace l2d
{
    class Layer :public Node
    {
    public:
        void resume();
        void pause();
        void addSprite(const Sprite& sprite);
    };
}
#endif /* defined(__Lua2d__Layer__) */
