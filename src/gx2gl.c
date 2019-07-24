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

#include <stddef.h>
#include <string.h>
#include <gx2/draw.h>
#include <gx2r/draw.h>
#include <gx2r/buffer.h>
#include <whb/gfx.h>

#include <GL/gl.h>

#define MAX_VERTS 1024

static float immed_buf[MAX_VERTS * 4];

static unsigned n_verts;
static GLenum poly_mode;
static GLboolean immed_mode = GL_FALSE;

static GX2RBuffer vertImmedPos;

void gx2glInit(void) {
    vertImmedPos.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER |
                                             GX2R_RESOURCE_USAGE_CPU_READ |
                                             GX2R_RESOURCE_USAGE_CPU_WRITE |
                                             GX2R_RESOURCE_USAGE_GPU_READ);
    vertImmedPos.elemSize = 4 * sizeof(float);
    vertImmedPos.elemCount = 4;
    GX2RCreateBuffer(&vertImmedPos);

    WHBGfxClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

GLAPI void APIENTRY glShadeModel(GLenum mode) {
}

GLAPI void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
}

GLAPI void APIENTRY glClear(GLbitfield mask) {
}

GLAPI void APIENTRY glBegin(GLenum mode) {
    n_verts = 0;
    poly_mode = mode;
    immed_mode = GL_TRUE;
}

GLAPI void APIENTRY glEnd(void) {
    immed_mode = GL_FALSE;

    if (n_verts) {
        void *copydst = GX2RLockBufferEx(&vertImmedPos, (GX2RResourceFlags)0);
        memcpy(copydst, immed_buf, n_verts * 4 * sizeof(float));
        GX2RUnlockBufferEx(&vertImmedPos, (GX2RResourceFlags)0);

        GX2RSetAttributeBuffer(&vertImmedPos, 0, vertImmedPos.elemSize, 0);
        GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLES, n_verts, 0, 1);
    }
}

GLAPI void APIENTRY glNormal3f(GLfloat x, GLfloat y, GLfloat z) {
}

GLAPI void APIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    if (immed_mode == GL_TRUE && poly_mode == GL_TRIANGLES) {
        float *vout = immed_buf + 4 * n_verts++;
        vout[0] = x;
        vout[1] = y;
        vout[2] = z;
        vout[3] = 1.0f;
    }
}

GLAPI void APIENTRY glMatrixMode(GLenum mode) {
}

GLAPI void APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
}

GLAPI void APIENTRY glLoadIdentity(void) {
}

GLAPI void APIENTRY glClearDepth(double depth) {
}

GLAPI void APIENTRY glClearColor(GLclampf red, GLclampf green,
                                 GLclampf blue, GLclampf alpha) {
    WHBGfxClearColor(red, green, blue, alpha);
}

GLAPI void APIENTRY glHint(GLenum target, GLenum mode) {
}

GLAPI void APIENTRY glDepthFunc(GLenum func) {
}

GLAPI void APIENTRY glEnable(GLenum cap) {
}
