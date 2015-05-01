//
//  MyOpenGLView.m
//  lua2d_mac
//
//  Created by chenbingfeng on 15/5/1.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#import "MyOpenGLView.h"
#include <OpenGL/gl.h>

@implementation MyOpenGLView
static void drawAnObject ()
{
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
}
-(void) drawRect:(NSRect)dirtyRect
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawAnObject();
    glFlush();
}
@end
