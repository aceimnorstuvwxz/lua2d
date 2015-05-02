//
//  main.cpp
//  luaformac
//
//  Created by chenbingfeng on 15/4/22.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//
#include <math.h>
#include <unistd.h>

#include <iostream>
#include <chrono>

#include <OpenGL/gl3.h>

#include "lua2d.h"

extern "C" {

#include "lua53/lua.h"
#include "lua53/lauxlib.h"
#include "lua53/lualib.h"

}

#include "utils.h"

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

float vertices[] = {
    0.0f, 0.5f, 1.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.3f,
    1.0f, 0.5f, 0.8f,
};

GLuint elements[] = {
    0,1,2,
    0,1,3
};

static const char* vertexSource =
"#version 150\n"
"\n"
"in vec2 position;\n"
"in float color;\n"
"out vec3 Color;\n"
"\n"
"\n"
"void main()\n"
"{\n"
"    Color = vec3(color);\n"
"    gl_Position = vec4(position.x, -position.y, 0.0, 1.0);\n"
"}\n";

static const char* fragmentSource =
"#version 150\n"
"\n"
"in vec3 Color;\n"
"uniform vec3 triangleColor;\n"
"\n"
"out vec4 outColor;\n"
"\n"
"void main()\n"
"{\n"
"    outColor = vec4(vec3(1.0f,1.0f,1.0f) - Color, 1.0);\n"
"}\n";
char clog[2014];
GLuint vbo;
GLuint vao;
GLuint ebo;
GLint uniColor;
GLuint textureId;
decltype(std::chrono::high_resolution_clock::now()) t_start;
void init()
{
    LOG("GL_RENDERER", glGetString(GL_RENDERER),  " GL_VERSION = ",glGetString(GL_VERSION));
    
    //vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    //shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        LOG("vertex shader compile failed.");
        glGetShaderInfoLog(vertexShader, 1024, NULL, clog);
        LOG(clog);
        exit(1);
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        LOG("fragment shader compile failed.");
        glGetShaderInfoLog(fragmentShader, 1024, NULL, clog);
        LOG(clog);
        exit(1);
    }
    
    //as program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    //attributes
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (GLvoid*)(2*sizeof(float)));
    
    uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
    
    
//    glGenTextures(1, &textureId);
//    glBindTexture(GL_TEXTURE_2D, textureId);
    t_start = std::chrono::high_resolution_clock::now();
    
}

void display()
{
    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
    glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void reshape(int w, int h)
{
}

bool lua_test()
{
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
    
    return EXIT_SUCCESS;
}

static void lua2d_demo()
{
    auto scene = std::make_shared<l2d::Scene>();
    auto layer = std::make_shared<l2d::Layer>();
    auto imageSprite = std::make_shared<l2d::ImageSprite>("shooting_arrow.png",71, 98);
    auto director = l2d::Director::getInstance();
    layer->addSprite(imageSprite);
    scene->addLayer(layer, 0);
    director.init(800, 400);
    director.runWithScene(scene);
    director.mainLoop();
}

int main(int argc, const char * argv[])
{

    std::cout << "hello world!" << std::endl;
    lua2d_demo();

    return 0;
}