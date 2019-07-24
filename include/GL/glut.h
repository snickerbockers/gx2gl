#ifndef GX2GLUT_H_
#define GX2GLUT_H_

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef __cplusplus
extern "C" {
#endif

void glutInitWindowSize(int width, int height);
void glutInit(int *argcp, char **argv);
void glutInitDisplayMode(unsigned mode);
int glutCreateWindow(char const *title);
void glutDisplayFunc(void (*func)(void));
void glutReshapeFunc(void (*func)(int, int));
void glutKeyboardFunc(void (*func)(unsigned char, int, int));
void glutSpecialFunc(void (*func)(int, int, int));
void glutVisibilityFunc(void (*func)(int));
void glutMainLoop(void);
void glutDestroyWindow(int win);
void glutSwapBuffers(void);
GLint glutGet(int state);
void glutPostRedisplay();
void glutIdleFunc(void (*func)(void));
void glutFullScreen(void);
void glutReshapeWindow(int width, int height);

// flags for glutInitDisplayMode
#define GLUT_RGBA (1 << 0)
#define GLUT_RGB GLUT_RGBA
#define GLUT_INDEX (1 << 1)
#define GLUT_SINGLE (1 << 2)
#define GLUT_DOUBLE (1 << 3)
#define GLUT_ACCUM (1 << 4)
#define GLUT_ALPHA (1 << 5)
#define GLUT_DEPTH (1 << 6)
#define GLUT_STENCIL (1 << 7)
#define GLUT_MULTISAMPLE (1 << 8)
#define GLUT_STEREO (1 << 9)
#define GLUT_LIUMINANCE (1 << 10)

// flags for glutGet
#define GLUT_ELAPSED_TIME (1 << 0)

// key flags
#define GLUT_KEY_UP (1 << 0)
#define GLUT_KEY_DOWN (1 << 1)
#define GLUT_KEY_LEFT (1 << 2)
#define GLUT_KEY_RIGHT (1 << 3)

#ifdef __cplusplus
}
#endif

#endif
