//
//  Renderer.cpp
//  Lua2d
//
//  Created by chenbingfeng on 15/4/30.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "Renderer.h"

NS_L2D_BEGIN

SPRenderer Renderer::create()
{
    return SPRenderer(new Renderer());
}

Renderer::Renderer(){}

void Renderer::init(int width, int height, const std::string& title)
{
    _width = width;
    _height = height;

    _context = cppgl::Context::Create();
    _context->clearColor({1.0f, 1.0f, 1.0f, 1.0f});
    _context->enable(cppgl::Capability::Blend);
    _context->blendFunc(cppgl::BlendFactor::SRC_ALPHA, cppgl::BlendFactor::ONE_MINUS_SRC_ALPHA);
}

cppgl::SPContext Renderer::getContext()
{
    return _context;
}

NS_L2D_END