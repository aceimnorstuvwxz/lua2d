//
//  Layer.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__Layer__
#define __Lua2d__Layer__

#include <vector>
#include <memory>

#include <stdio.h>
#include "Node.h"
#include "Sprite.h"
#include "utils.h"

NS_L2D_BEGIN

class Layer :public Node
{
public:
    void resume();
    void pause();
    void addSprite(std::shared_ptr<Sprite> sprite);
    void draw();

private:
    std::vector<std::shared_ptr<Sprite>> _sprites;
};

NS_L2D_END
#endif /* defined(__Lua2d__Layer__) */
