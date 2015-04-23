//
//  main.cpp
//  luaformac
//
//  Created by chenbingfeng on 15/4/22.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include <iostream>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
    
}
static const char s_luachuck[] = "print(\"I am inside chunk!\")\
return 123";
static bool s_hasReaded = false;

const char * myChunkReader(lua_State* L, void* data, size_t* size)
{
    if (s_hasReaded) {
        *size = 0;
        return NULL;
    } else {
        s_hasReaded = true;
        *size = sizeof(s_luachuck) - 1;
        std::cout << *size << std::endl;
        return s_luachuck;
    }
}


int main(int argc, const char * argv[]) {
    
    lua_State * L = luaL_newstate();
    if (L == NULL) {
        std::cerr << "cannot create state: not enough memory." << std::endl;
        return EXIT_FAILURE;
    }
    // load standard libraries
    luaL_openlibs(L);
    
    // load the chunk
    if (lua_load(L, myChunkReader, NULL, "my chunk", NULL) != LUA_OK){
        std::cerr << "load chunk failed."<<std::endl;
        return EXIT_FAILURE;
    }
    if (lua_isfunction(L, -1 )) {
        std:: cout << "top is function"<<std::endl;
    } else {
        std::cout << "top is not function"  <<std::endl;
    }
    
    //call the chunk
    lua_call(L, 0, 1);
    lua_Integer res = lua_tointeger(L, -1);
    std::cout << res<< std::endl;
    
    lua_close(L);
    return 0;
}
