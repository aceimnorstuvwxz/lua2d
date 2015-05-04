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
#include "Renderer.h"
#include "utils.h"

NS_L2D_BEGIN

class Layer;
typedef std::shared_ptr<Layer> SPLayer;

class Layer :public Node
{
public:
    static SPLayer create();

    void resume();
    void pause();
    void addSprite(SPSprite& sprite);
    void draw(SPRenderer& renderer);

private:
    Layer();
    std::vector<SPSprite> _sprites;
};

NS_L2D_END
#endif /* defined(__Lua2d__Layer__) */
