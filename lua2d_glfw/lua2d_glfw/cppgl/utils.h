//
//  utils.h
//  common utilities for cppgl
//
//  Created by chenbingfeng on 15/5/2.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __lua2d_glfw__utils__
#define __lua2d_glfw__utils__

#include <stdio.h>

#define NS_CPPGL_BEGIN namespace cppgl {
#define NS_CPPGL_END   }

// use glm as math lib, which is a header only library
#include "glm/glm.hpp"

// opengl lib is a common
#include <OpenGL/gl3.h>

NS_CPPGL_BEGIN

typedef glm::vec4 Color;

NS_CPPGL_END

#endif /* defined(__lua2d_glfw__utils__) */
