//
//  main.cpp
//  luaformac
//
//  Created by chenbingfeng on 15/4/22.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//
#include <math.h>
//#include <unistd.h>

#include <iostream>
#include <chrono>


#include "cppgl/cppgl.h"
#include "utils.h"
#include "lua2d.h"

extern "C" {

#include "lua53/lua.h"
#include "lua53/lauxlib.h"
#include "lua53/lualib.h"

}



int main(int argc, const char * argv[])
{
    std::cout << "hello world!" << std::endl;
    cppgl::cppgl_test();
    return 0;
}