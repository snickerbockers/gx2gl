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

#include <string.h>

#include <GL/gl.h>
#include <GL/gx2gl.h>

#define GX2GL_PROC(procName) { #procName, procName }

static struct gx2glProcTableEntry {
    char const *name;
    void *proc;
} const gx2glProcTable[] = {
    GX2GL_PROC(glShadeModel),
    GX2GL_PROC(glViewport),
    GX2GL_PROC(glClear),
    GX2GL_PROC(glBegin),
    GX2GL_PROC(glEnd),
    GX2GL_PROC(glNormal3f),
    GX2GL_PROC(glVertex3f),
    GX2GL_PROC(glMatrixMode),
    GX2GL_PROC(glTranslatef),
    GX2GL_PROC(glLoadIdentity),
    GX2GL_PROC(glEnable),
    GX2GL_PROC(glClearDepth),
    GX2GL_PROC(glClearColor),
    GX2GL_PROC(glHint),
    GX2GL_PROC(glDepthFunc),

    { NULL, NULL }
};

void *gx2glGetProcAddress(char const *procName) {
    struct gx2glProcTableEntry const *cursor = gx2glProcTable;
    while (cursor->name) {
        if (strcmp(procName, cursor->name) == 0)
            return cursor->proc;
        cursor++;
    }

    // procedure not found
    return NULL;
}
