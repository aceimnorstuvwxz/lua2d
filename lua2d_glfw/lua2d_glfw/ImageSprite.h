//
//  ImageSprite.h
//  Lua2d
//
//  Created by chenbingfeng on 15/4/27.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __Lua2d__ImageSprite__
#define __Lua2d__ImageSprite__

#include <memory>

#include "utils.h"
#include <string>
#include "Sprite.h"
#include "Renderer.h"
#include "cppgl/cppgl.h"

NS_L2D_BEGIN

class ImageSprite;
typedef std::shared_ptr<ImageSprite> SPImageSprite;

class ImageSprite :public Sprite
{
public:
    static SPImageSprite create(const std::string& fileName, int width, int height);
    virtual void load() override;
    virtual void draw(SPRenderer& renderer) override;

private:
    ImageSprite(const std::string& fileName, int width, int height);

    // image display size, could be different from raw size
    int _width; // image width
    int _height; // image height

    std::string _fileName;
    bool _loaded = false;

    // drawing data
    cppgl::SPTexture _texture;

    // ImageSprite share the same VAO and VBO
    static cppgl::SPVertexArray _vao;
    static cppgl::SPVertexBuffer _vbo;
    static cppgl::SPProgram _program;
    
    static void initStatic();
    static bool _initedStatic;
};

NS_L2D_END

#endif /* defined(__Lua2d__ImageSprite__) */
