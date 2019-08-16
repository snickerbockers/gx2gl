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

#include <GL/gl.h>
#include <GL/gx2gl.h>

static void render_tv(void);
static void render_drc(void);

int main(int argc, char **argv) {
    WHBProcInit();

    gx2glInit();

    gx2glContext drc_ctx = gx2glCreateContext();
    gx2glContext tv_ctx = gx2glCreateContext();

    gx2glScreen drc_screen = gx2glCreateScreen(GX2GL_GAMEPAD, NULL);
    gx2glScreen tv_screen = gx2glCreateScreen(GX2GL_TV, NULL);

    while (WHBProcIsRunning()) {
        gx2glMakeCurrent(drc_ctx, drc_screen);
        gx2glBeginRender();
        render_drc();
        gx2glEndRender();

        gx2glMakeCurrent(tv_ctx, tv_screen);
        gx2glBeginRender();
        render_tv();
        gx2glEndRender();

        gx2glSwapBuffers();
    }

    gx2glCleanup();

    WHBGfxShutdown();
    WHBProcShutdown();

    return 0;
}

static void render_tv(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

static void render_drc(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();
}
