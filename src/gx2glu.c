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
#include <GL/glu.h>
#include <math.h>

void gluPerspective(GLdouble fovy, GLdouble aspect,
                    GLdouble near, GLdouble far) {
    GLdouble bottom = sin(fovy * (M_PI / 180.0) * 0.5) * near;
    GLdouble right = bottom * aspect;

    GLfloat mat[16];

    mat[0] = near / right;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = near / bottom;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = -(far + near) / (far - near);
    mat[11] = -1.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = -2.0 * far * near / (far - near);
    mat[15] = 0.0f;

    glMultMatrixf(mat);
}
