// tutorial06.cpp

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

class Light
{
	private:
		int id;
		float pos[4];
		float ambient[4];
		float diffuse[4];
		float specular[4];
		float attenuation[3];
		float spot_dir[3];
		float spot_exp;
		float spot_cutoff;
	public:
		Light(int);
		Light & setPos(float, float, float);
		Light & setSpotDir(float, float, float);
		void init();
		void set();
		void draw();
};

Light::Light(int id)
	: id(id)
{
	pos[0] = 0.0;
	pos[1] = 0.0;
	pos[2] = 5.0;
	pos[3] = 1.0;
	
	ambient[0] = 0.2;
	ambient[1] = 0.0;
	ambient[2] = 0.0;
	ambient[3] = 1.0;
	
	diffuse[0] = 0.8;
	diffuse[1] = 0.0;
	diffuse[2] = 0.0;
	diffuse[3] = 1.0;
	
	specular[0] = 0.4;
	specular[1] = 0.0;
	specular[2] = 0.0;
	specular[3] = 1.0;
	
	attenuation[0] = 1.0;
	attenuation[1] = 0.0;
	attenuation[2] = 0.0;

	spot_dir[0] = 0.0;
	spot_dir[1] = -1.0;
	spot_dir[2] = -1.0;
	spot_exp = 10.0;
	spot_cutoff = 60.0;
}

Light & Light::setPos(float p0, float p1, float p2)
{
	pos[0] = p0;
	pos[1] = p1;
	pos[2] = p2;
	return *this;
}

Light & Light::setSpotDir(float p0, float p1, float p2)
{
	spot_dir[0] = p0;
	spot_dir[1] = p1;
	spot_dir[2] = p2;
	return *this;
}

void Light::init()
{
	glEnable(id);
	glLightfv(id, GL_AMBIENT, ambient);
	glLightfv(id, GL_DIFFUSE, diffuse);
	glLightfv(id, GL_SPECULAR, specular);
	glLightf(id, GL_SPOT_EXPONENT, spot_exp);
	glLightf(id, GL_SPOT_CUTOFF, spot_cutoff);
	glLightf(id, GL_CONSTANT_ATTENUATION, attenuation[0]);
	glLightf(id, GL_LINEAR_ATTENUATION, attenuation[1]);
	glLightf(id, GL_QUADRATIC_ATTENUATION, attenuation[2]);
}

void Light::set()
{
	glPushMatrix();
	glLightfv(id, GL_POSITION, pos);
	glLightfv(id, GL_SPOT_DIRECTION, spot_dir);
	glPopMatrix();
}

void Light::draw()
{
	float p[3];

	for (int i = 0; i < 3; ++i) p[i] = pos[i] + 10.0 * spot_dir[i];
	
	glLineWidth(1.0);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3fv(pos);
		glVertex3fv(p);
	glEnd();
}

static const float width = 20.0;
static const float height = 20.0;
static const int nx = 16;
static const int ny = 16;

float h[nx+1][ny+1][3];
float n[nx+1][ny+1][3];

Light light0(GL_LIGHT0);
int fullscreen = 0;

static float modelAmb[4] = {0.2, 0.2, 0.7, 1.0};
static float matAmb[4] = {0.2, 0.2, 0.3, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};

void calc_heightfield(void)
{
	float dw = width / nx;
	float dh = height / ny;
	for (int x = 0; x <= nx; ++x)
	{
		for (int y = 0; y <= ny; ++y)
		{
			h[x][y][0] = x * dw;
			h[x][y][1] = y * dh;
			h[x][y][2] = 0.0;

			n[x][y][0] = 0.0;
			n[x][y][1] = 0.0;
			n[x][y][2] = 1.0;
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'f':
			if (fullscreen)
			{
				glutReshapeWindow(800, 600);
				glutPositionWindow(0, 0);
			}
			else glutFullScreen();
			fullscreen = !fullscreen;
			break;
		case 27: exit(0);
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(20.0, -20.0, 20.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
	light0.set();

	// surface
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	glPushMatrix();
	glLineWidth(1.0);
	glTranslatef(-width/2.0, -height/2.0, 0.0);
	for (int x = 0; x < nx; ++x)
	{
		glBegin(GL_TRIANGLES);
		for (int y = 0; y < ny; ++y)
		{
			glNormal3fv(n[x][y]);		glVertex3fv(h[x][y]);
			glNormal3fv(n[x+1][y]);		glVertex3fv(h[x+1][y]);
			glNormal3fv(n[x+1][y+1]);	glVertex3fv(h[x+1][y+1]);

			glNormal3fv(n[x][y]);		glVertex3fv(h[x][y]);
			glNormal3fv(n[x+1][y+1]);	glVertex3fv(h[x+1][y+1]);
			glNormal3fv(n[x][y+1]);		glVertex3fv(h[x][y+1]);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_LIGHTING);

	// bounding box
	glLineWidth(3.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glBegin(GL_QUADS);
		glVertex3f(-width/2.0, -height/2.0, 0.0);
		glVertex3f( width/2.0, -height/2.0, 0.0);
		glVertex3f( width/2.0,  height/2.0, 0.0);
		glVertex3f(-width/2.0,  height/2.0, 0.0);
	glEnd();

	// light ray
	light0.draw();
	
	glFlush();
	glutSwapBuffers();
}

void idle(void)
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Tutorial 06: Spotlight and Heightmap");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

	calc_heightfield();
	
	light0.init();
	
	glutMainLoop();
	return 0;
}

