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

#include <GL/gl.h>

#include "matrix.h"
#include "context.h"

static GLfloat *gx2gl_get_cur_matrix(void);

GLAPI void APIENTRY glMatrixMode(GLenum mode) {
    switch (mode) {
    case GL_MODELVIEW:
        cur_ctx->matrixContext.cur_mat = GX2GL_MATRIX_MODELVIEW;
        break;
    case GL_PROJECTION:
        cur_ctx->matrixContext.cur_mat = GX2GL_MATRIX_PROJECTION;
        break;
    case GL_TEXTURE:
        cur_ctx->matrixContext.cur_mat = GX2GL_MATRIX_TEXTURE;
    default:
        cur_ctx->error = GL_INVALID_ENUM;
    }
}

GLAPI void APIENTRY glLoadIdentity(void) {
    GLfloat *mat = gx2gl_get_cur_matrix();

    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = 1.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

float gx2glDot4fv(float const src1[4], float const src2[4]) {
    return src1[0] * src2[0] + src1[1] * src2[1] +
        src1[2] * src2[2] + src1[3] * src2[3];
}

// column-major matrix multiplication
void gx2glMatMult4fv(float dst[16],
                     float const src1[16], float const src2[16]) {
    assert(dst != src1 && dst != src2);

    float src1_rows[4][4] = {
        { src1[0], src1[4], src1[8],  src1[12] },
        { src1[1], src1[5], src1[9],  src1[13] },
        { src1[2], src1[6], src1[10], src1[14] },
        { src1[3], src1[7], src1[11], src1[15] }
    };

    dst[0]  = gx2glDot4fv(src1_rows[0], src2 + 0);
    dst[4]  = gx2glDot4fv(src1_rows[0], src2 + 4);
    dst[8]  = gx2glDot4fv(src1_rows[0], src2 + 8);
    dst[12]  = gx2glDot4fv(src1_rows[0], src2 + 12);

    dst[1]  = gx2glDot4fv(src1_rows[1], src2 + 0);
    dst[5]  = gx2glDot4fv(src1_rows[1], src2 + 4);
    dst[9]  = gx2glDot4fv(src1_rows[1], src2 + 8);
    dst[13]  = gx2glDot4fv(src1_rows[1], src2 + 12);

    dst[2]  = gx2glDot4fv(src1_rows[2], src2 + 0);
    dst[6]  = gx2glDot4fv(src1_rows[2], src2 + 4);
    dst[10] = gx2glDot4fv(src1_rows[2], src2 + 8);
    dst[14] = gx2glDot4fv(src1_rows[2], src2 + 12);

    dst[3] = gx2glDot4fv(src1_rows[3], src2 + 0);
    dst[7] = gx2glDot4fv(src1_rows[3], src2 + 4);
    dst[11] = gx2glDot4fv(src1_rows[3], src2 + 8);
    dst[15] = gx2glDot4fv(src1_rows[3], src2 + 12);
}

static GLfloat *gx2gl_get_cur_matrix(void) {
    return cur_ctx->matrixContext.stack[cur_ctx->matrixContext.cur_mat][0];
}

void gx2gl_get_mvp(float mvp_out[16]) {
    gx2glMatMult4fv(mvp_out,
                    cur_ctx->matrixContext.stack[GX2GL_MATRIX_PROJECTION][0],
                    cur_ctx->matrixContext.stack[GX2GL_MATRIX_MODELVIEW][0]);
}
