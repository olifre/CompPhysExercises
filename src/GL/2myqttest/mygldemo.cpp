#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);
  glLoadIdentity();
  gluLookAt(
	    0.0, 10.0, 10.0,
	    0.0,  0.0,  0.0,
	    0.0,  1.0,  0.0);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 1.0);
  glEnd();
  glTranslatef(0.0, 0.0, 2.0);
  glBegin(GL_TRIANGLES);
  glVertex3f( 0.0, 0.0, 0.0);
  glVertex3f( 1.0, 1.0, 0.0);
  glVertex3f(-1.0, 1.0, 0.0);
  glVertex3f( 0.0,  0.0, 0.0);
  glVertex3f( 1.0, -1.0, 0.0);
  glVertex3f(-1.0, -1.0, 0.0);
  glEnd();
  glTranslatef(0.0, 0.0, -7.0);
  glutWireSphere(1.0, 16, 16);
  glFlush();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(300, 300);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("OpenGL Demo 1");
  glutDisplayFunc(display);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glutMainLoop();

  return 0;
}
