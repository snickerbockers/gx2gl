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
#include <stdlib.h>
#include <gx2/draw.h>
#include <gx2r/draw.h>
#include <gx2r/buffer.h>
#include <whb/gfx.h>

#include <GL/gl.h>
#include <GL/gx2gl.h>

#include "context.h"

#define MAX_CONTEXTS 4

static struct gx2gl_context gx2gl_ctx_arr[MAX_CONTEXTS];
struct gx2gl_context *cur_ctx;

gx2glContext gx2glCreateContext(void) {
    gx2glContext handle;
    for (handle = 0; handle < MAX_CONTEXTS; handle++)
        if (gx2gl_ctx_arr[handle].valid == 0)
            break;
    if (handle == MAX_CONTEXTS)
        return -1;

    struct gx2gl_context *ctx = gx2gl_ctx_arr + handle;

    ctx->maxVerts = 1024;
    ctx->immedBuf = malloc(ctx->maxVerts * sizeof(float) * 4);

    ctx->vertImmedPos.flags = (GX2RResourceFlags)(GX2R_RESOURCE_BIND_VERTEX_BUFFER |
                                                  GX2R_RESOURCE_USAGE_CPU_READ |
                                                  GX2R_RESOURCE_USAGE_CPU_WRITE |
                                                  GX2R_RESOURCE_USAGE_GPU_READ);
    ctx->vertImmedPos.elemSize = 4 * sizeof(float);
    ctx->vertImmedPos.elemCount = 4;
    GX2RCreateBuffer(&ctx->vertImmedPos);

    WHBGfxClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    ctx->valid = 1;

    return handle;
}

void gx2glDestroyContext(gx2glContext handle) {
    if (handle < 0)
        return;
    struct gx2gl_context *ctx = gx2gl_ctx_arr + handle;
    if (!ctx->valid)
        return;
    if (cur_ctx == ctx)
        cur_ctx = NULL;

    ctx->valid = 0;

    GX2RDestroyBufferEx(&ctx->vertImmedPos, 0);
    free(ctx->immedBuf);

    memset(ctx, 0, sizeof(*ctx));
}

void gx2glMakeCurrent(gx2glContext ctx) {
    if (ctx < MAX_CONTEXTS && gx2gl_ctx_arr[ctx].valid)
        cur_ctx = gx2gl_ctx_arr + ctx;
}

GLAPI void APIENTRY glShadeModel(GLenum mode) {
}

GLAPI void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
}

GLAPI void APIENTRY glClear(GLbitfield mask) {
}

GLAPI void APIENTRY glBegin(GLenum mode) {
    cur_ctx->nVerts = 0;
    cur_ctx->polyMode = mode;
    cur_ctx->immedMode = GL_TRUE;
}

GLAPI void APIENTRY glEnd(void) {
    cur_ctx->immedMode = GL_FALSE;

    if (cur_ctx->nVerts) {
        void *copydst = GX2RLockBufferEx(&cur_ctx->vertImmedPos, (GX2RResourceFlags)0);
        memcpy(copydst, cur_ctx->immedBuf, cur_ctx->nVerts * 4 * sizeof(float));
        GX2RUnlockBufferEx(&cur_ctx->vertImmedPos, (GX2RResourceFlags)0);

        float mvp[16];
        gx2gl_get_mvp(mvp);
        float row0[4] = { mvp[0], mvp[4], mvp[8], mvp[12] };
        float row1[4] = { mvp[1], mvp[5], mvp[9], mvp[13] };
        float row2[4] = { mvp[2], mvp[6], mvp[10], mvp[14] };
        float row3[4] = { mvp[4], mvp[7], mvp[11], mvp[15] };
        uint32_t row0i[4], row1i[4], row2i[4], row3i[4];
        memcpy(row0i, row0, sizeof(row0i));
        memcpy(row1i, row1, sizeof(row1i));
        memcpy(row2i, row2, sizeof(row2i));
        memcpy(row3i, row3, sizeof(row3i));

        GX2SetVertexUniformReg(0, 4, row0i);
        GX2SetVertexUniformReg(4, 4, row1i);
        GX2SetVertexUniformReg(8, 4, row2i);
        GX2SetVertexUniformReg(12, 4, row3i);

        GX2RSetAttributeBuffer(&cur_ctx->vertImmedPos, 0,
                               cur_ctx->vertImmedPos.elemSize, 0);
        // TODO: mvp
        GX2DrawEx(GX2_PRIMITIVE_MODE_TRIANGLES, cur_ctx->nVerts, 0, 1);
    }
}

GLAPI void APIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    if (cur_ctx->immedMode == GL_TRUE && cur_ctx->polyMode == GL_TRIANGLES) {
        float *vout = cur_ctx->immedBuf + 4 * cur_ctx->nVerts++;
        vout[0] = x;
        vout[1] = y;
        vout[2] = z;
        vout[3] = 1.0f;
    }
}

GLAPI void APIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat mat[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        x, y, z, 1.0f
    };
    glMultMatrixf(mat);
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
