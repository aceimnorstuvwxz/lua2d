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


#include "utils.h"
#include "Node.h"
#include "Sprite.h"
#include "ImageSprite.h"
#include "Renderer.h"

NS_L2D_BEGIN

class Layer;
class Sprite;
class Renderer;
class ImageSprite;
typedef std::shared_ptr<Layer> SPLayer;
typedef std::shared_ptr<Sprite> SPSprite;
typedef std::shared_ptr<Renderer> SPRenderer;
typedef std::shared_ptr<ImageSprite> SPImageSprite;

class Layer :public Node
{
public:
    static SPLayer create();

    void resume();
    void pause();
    void addSprite(SPSprite& sprite);
    void addSprite(SPImageSprite& sprite);
    void draw(SPRenderer& renderer);

private:
    Layer();
    std::vector<SPSprite> _sprites;
    std::vector<SPImageSprite> _imageSprites;
};

NS_L2D_END
#endif /* defined(__Lua2d__Layer__) */
