/*******************************************************************************
 *
 * Copyright (c) 2019, snickerbockers <snickerbockers@washemu.org>
 * All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are
 *    met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#include <whb/proc.h>
#include <whb/gfx.h>
#include <coreinit/debug.h>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/gx2gl.h>

/*
 * Random fact to keep in mind:
 * OpenGL's normalized device coordinates run from -1.0 to 1.0.
 * Anything <= 1.0 or >=-1.0 will be drawn, and anything >1.0 or <-1.0 will be
 * clipped.
 *
 * GX2's normalized device coordinates appear to be similar, except it clips
 * anything >= 1.0.  It does not clip -1.0, which means it's slightly
 * asymmetrical.
 */

static void glutDoCleanup(void);

static void (*gx2glutDisplayFunc)(void);
static void (*gx2glutReshapeFunc)(int, int);

static gx2glContext gx2glutCtxHandle = -1;
static gx2glScreen gx2glutDrc = -1;

#define DRC_WIDTH 854
#define DRC_HEIGHT 480

void glutInitWindowSize(int width, int height) {
}

void glutInit(int *argcp, char **argv) {
    WHBProcInit();

    gx2glInit();
    gx2glutCtxHandle = gx2glCreateContext();
    gx2glutDrc = gx2glCreateScreen(GX2GL_GAMEPAD, NULL);
    gx2glMakeCurrent(gx2glutCtxHandle, gx2glutDrc);
}

void glutInitDisplayMode(unsigned mode) {
}

int glutCreateWindow(char const *title) {
    return 0; // TODO
}

void glutDisplayFunc(void (*func)(void)) {
    gx2glutDisplayFunc = func;
}

void glutReshapeFunc(void (*func)(int, int)) {
    gx2glutReshapeFunc = func;
}

void glutKeyboardFunc(void (*func)(unsigned char, int, int)) {
}

void glutSpecialFunc(void (*func)(int, int, int)) {
}

void glutVisibilityFunc(void (*func)(int)) {
}

void glutMainLoop(void) {
    if (gx2glutReshapeFunc)
        gx2glutReshapeFunc(DRC_WIDTH, DRC_HEIGHT);

    while (WHBProcIsRunning()) {
        gx2glBeginRender();

        if (gx2glutDisplayFunc)
            gx2glutDisplayFunc();

        gx2glEndRender();
    }

    glutDoCleanup();
}

void glutDestroyWindow(int win) {
    glutDoCleanup();
}

void glutSwapBuffers(void){
}

GLint glutGet(int state) {
    return 0; // TODO
}

void glutPostRedisplay() {
}

void glutIdleFunc(void (*func)(void)) {
}

static void glutDoCleanup(void) {
    gx2glDestroyContext(gx2glutCtxHandle);
    gx2glCleanup();

    WHBGfxShutdown();
    WHBProcShutdown();
}

void glutFullScreen(void) {
}

void glutReshapeWindow(int width, int height) {
}
