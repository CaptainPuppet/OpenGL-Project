#include <windows.h> //the windows include file, required by all windows applications
#include <gl/glut.h> //the glut file for windows operations
// it also includes gl.h and glu.h for the openGL library calls
#include "utils.h"

#define PI 3.1415926535898

GLfloat centerX = 0.5;
GLfloat centerZ = 0.5;
GLfloat radius;

GLfloat ang = 0.;
GLfloat angleRobot = 90;
GLfloat fang = 40.;
GLfloat lens = 3., zmove = 1;

GLfloat aspect;


GLfloat P1[3] = { 0.5,0.,0.5 };
GLfloat P2[3] = { 0.,0.,-0.5 };
GLfloat P3[3] = { -0.5,0.,0.5 };
GLfloat u[3], v[3], uv[3];

#define MAXSHAPES 25
#define MAXCOORDS  3000

GLfloat   coords[MAXSHAPES][3 * MAXCOORDS];
GLint     indices[MAXSHAPES][3 * MAXCOORDS];
GLfloat   normals[MAXSHAPES][3 * MAXCOORDS];
GLint     nindices[MAXSHAPES][3 * MAXCOORDS];
GLint     noofpoly[MAXSHAPES];


GLint     noofshapes;



void myRobot() {
	int i, j;
	
	for (j = 0; j < noofshapes; j++) {
		for (i = 0; i < noofpoly[j] * 3; i = i + 3) {
			glBegin(GL_TRIANGLES);
			glVertex3fv(&(coords[j][3 * indices[j][i]]));
			glVertex3fv(&(coords[j][3 * indices[j][i + 1]]));
			glVertex3fv(&(coords[j][3 * indices[j][i + 2]]));
			glEnd();
		}
	}
	
}
/*
void myPyramid() {

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(P1);
	glVertex3fv(uv);
	glVertex3fv(P3);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(P1);
	glVertex3fv(P2);
	glVertex3fv(uv);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(P3);
	glVertex3fv(uv);
	glVertex3fv(P2);
	glEnd();

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(P3);
	glVertex3fv(P2);
	glVertex3fv(P1);
	glEnd();
}
*/
void Display(void)
{
	// swap the buffers
	glutSwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(0., 1., -5.);
	
	
	
	
	glFrustum(-1.0 * lens, 1.0 * lens, -1.0 * lens, 1.0 * lens, 1., 20);

	//ang = 2 * PI / lens;
	
	GLfloat eyX = (centerX * cos(ang));
	GLfloat eyZ = (centerZ * sin(ang));
	gluLookAt(eyX, 0., eyZ, 0, 0, 0, 0., 1., 0.);
	//if (eyez > 20) zmove = -1;
	//if (eyez < 0) zmove = 1;
	

	
	
	
	

	// rotate the robot
	glRotatef(angleRobot, 0., 1., 0.);
	if (angleRobot >= 360) angleRobot = 0; else angleRobot += 0.01;
	
	myRobot();
	glFlush();
	glutPostRedisplay();

}





void reshape(int w, int h)
{
	// on reshape and on startup, keep the viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1., 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 1, 0, 0, 0, 0., 1., 0.);

}


void init(void) {

	//set the clear color to be black
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/*
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_LINE);
	*/
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_LINE);
	//vecsub(P1, P2, u);
	//vecsub(P1, P3, v);
	//crossproduct(u, v, uv);
}


void main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Displaying 3D shapes");

	noofshapes = ReadVRML("robot.wrl", &coords[0][0], &normals[0][0], &indices[0][0], &nindices[0][0], &(noofpoly[0]), MAXSHAPES, MAXCOORDS);
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}