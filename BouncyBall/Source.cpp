//Example2_4.cpp : A bouncing ball 

#include <windows.h> //the windows include file, required by all windows applications
#include <gl\glut.h> //the glut file for windows operations
					 // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.1415926535898 



double xpos, ypos, ydir, xdir;         // x and y position for house to be drawn
double sx, sy, squash;          // xy scale factors
double rot, rdir;             // rotation 
double SPEED = 0.02;
int score = 0;
int score2 = 0;

static GLint paddleBoundary = 200, paddleHeight = 40, paddleVel = 10;
static GLint p1_PaddleY = 50, p2_PaddleY = 50, p1_PaddleX = 140,p2_PaddleX = 20;

/*
GLfloat T1[16] = {1.,0.,0.,0.,\
				  0.,1.,0.,0.,\
				  0.,0.,1.,0.,\
				  0.,0.,0.,1. };
GLfloat S[16] = { 1.,0.,0.,0.,\
				 0.,1.,0.,0.,\
				 0.,0.,1.,0.,\
				 0.,0.,0.,1. };
GLfloat T[16] = { 1.,0.,0.,0.,\
				 0., 1., 0., 0.,\
				 0.,0.,1.,0.,\
				 0.,0.,0.,1. };
*/


#define PI 3.1415926535898 
GLint circle_points = 100;
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius) {
	GLint i;
	GLdouble angle;
	glBegin(GL_POLYGON);
	for (i = 0; i < circle_points; i++) {
		angle = 2 * PI * i / circle_points;
		glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));
	}
	glEnd();
}

void drawPaddle(int x, int y) {
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0);
	//cout << "\nx " << x << " y " << y;
	 


	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	int height = paddleHeight / 2;
	glVertex2f(-5, height);
	glVertex2f(5, height);
	glVertex2f(5, -height);
	glVertex2f(-5, -height);
	glEnd();

	glPopMatrix();
}

void keyboard(unsigned char key, int x, int y) {


	switch (key) {
		// move player 1 paddile up
	case 'o':
		if (p1_PaddleY < paddleBoundary) 
		{
			p1_PaddleY += paddleVel;
			//cout << "si se esta enviando";
		}
		//cout << "hola: w pressed";
		break;
		// move player 1 paddile down
	case 'l':
		if (p1_PaddleY > -paddleBoundary)
			p1_PaddleY -= paddleVel;
		
		break;
		// move player 2 paddile up
	case 'w':
		if (p2_PaddleY < paddleBoundary)
			p2_PaddleY += paddleVel;
		
		break;
		// move player 2 paddile down
	case 's':
		if (p2_PaddleY > -paddleBoundary)
			p2_PaddleY -= paddleVel;
		
		break;
		// exit on esc
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void drawPaddle2(int x, int y) {
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(x, y, 0);
	

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	int height = paddleHeight / 2;
	glVertex2f(-5, height);
	glVertex2f(5, height);
	glVertex2f(5, -height);
	glVertex2f(-5, -height);
	glEnd();

	glPopMatrix();
}

GLfloat RadiusOfBall = 7.;
// Draw the ball, centered at the origin
void draw_ball() {
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0.);
	glColor3f(0.6, 0.3, 0.);
	MyCircle2f(0., 0., RadiusOfBall);
	

}


void ball_Update()
{
	//glLoadIdentity();
	glTranslatef(xpos, ypos, 0.);
	xpos = xpos + xdir * SPEED;
	ypos = ypos + ydir * SPEED;

	// If ball touches the top, change direction of ball downwards
	if (ypos >= 120 - RadiusOfBall)
		ydir = -1;
	// If ball touches the bottom, change direction of ball upwards
	else if (ypos < RadiusOfBall)
		ydir = 1;

	if (xpos >= 160 - RadiusOfBall)
	{
		xdir = -1;
		score += 1;
		cout << "\n Player 1 Score: " << score;
	}
		

	else if (xpos < RadiusOfBall) 
	{
		xdir = 1;
		score2 += 1;
		cout << "\n Player 2 Score: " << score2;
	}
		

	
	if (xpos + RadiusOfBall >= p1_PaddleX)
	{
		if (ypos < p1_PaddleY + paddleHeight && ypos > p1_PaddleY - paddleHeight ) 
		{
			xdir = -1;
		}
		
	}

	else if (xpos - RadiusOfBall <= p2_PaddleX)
	{
		if (ypos < p2_PaddleY + paddleHeight && ypos > p2_PaddleY - paddleHeight)
		{
			xdir = 1;
		}
		
	}
	
}


void Display(void)
{

ball_Update();
	/*
	//Translate the bouncing ball to its new position
	T[12] = xpos;
	T[13] = ypos;
	glLoadMatrixf(T);

	T1[13] = -RadiusOfBall;
	// Translate ball back to center
	glMultMatrixf(T1);
	S[0] = sx;
	S[5] = sy;
	// Scale the ball about its bottom
	glMultMatrixf(S);
	T1[13] = RadiusOfBall;
	// Translate ball up so bottom is at the origin
	glMultMatrixf(T1);
	*/
	
	// swap the buffers
glutSwapBuffers();

//clear all pixels with the specified clear color
glClear(GL_COLOR_BUFFER_BIT);
draw_ball();

drawPaddle(p1_PaddleX, p1_PaddleY);
drawPaddle2(p2_PaddleX, p2_PaddleY);
	



glutPostRedisplay();



}


void reshape(int w, int h)
{
	// on reshape and on startup, keep the viewport to be the entire size of the window
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// keep our logical coordinate system constant
	gluOrtho2D(0.0, 160.0, 0.0, 120.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void init(void) {
	//set the clear color to be white
	glClearColor(0.0, 0.8, 0.0, 1.0);
	// initial house position set to 0,0
	xpos = 60; ypos = RadiusOfBall; xdir = 1; ydir = 1;
	
	sx = 1.; sy = 1.; squash = 0.9;
	rot = 0;




}


void main(int argc, char* argv[])
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(320, 240);
	glutCreateWindow("Bouncing Ball");
	init();
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	
	
	
}