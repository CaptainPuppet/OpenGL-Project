#ifndef __utils_h__
#define __utils_h__

#include <gl/glut.h>
#include <windows.h>
#include <math.h>


/*
void vecsub(GLfloat* a, GLfloat* b, GLfloat* c) {

	c[0] = b[0] - a[0];
	c[1] = b[1] - a[1];
	c[2] = b[2] - a[2];
}

void vecadd(GLfloat* a, GLfloat* b, GLfloat* c) {

	c[0] = b[0] + a[0];
	c[1] = b[1] + a[1];
	c[2] = b[2] + a[2];
}

void vecmult(GLfloat s, GLfloat* a) {

	a[0] *= s;
	a[1] *= s;
	a[2] *= s;
}



void normalize(GLfloat* vec) {
	GLfloat length = sqrt((double)(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]));

	if (length == 0)
		return;
	vec[0] = vec[0] / length;
	vec[1] = vec[1] / length;
	vec[2] = vec[2] / length;

}


void dotproduct(GLfloat* a, GLfloat* b, GLfloat* c) {

	*c = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];

}

void crossproduct(GLfloat* u, GLfloat* v, GLfloat* uv) {

	uv[0] = u[1] * v[2] - u[2] * v[1];
	uv[1] = u[2] * v[0] - u[0] * v[2];
	uv[2] = u[0] * v[1] - u[1] * v[0];
	normalize(uv);

}


void matrixvectormult(GLfloat* m, GLfloat* v, GLfloat* mv) {
	GLfloat w = m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15];
	mv[0] = (m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3]) / w;
	mv[1] = (m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7]) / w;
	mv[2] = (m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11]) / w;
}


#endif
*/



#include <gl/glut.h>
#include <windows.h>


int ReadVRML(const char* filename,
	GLfloat* coordinates, GLfloat* normals,
	GLint* indices, GLint* nindices,
	GLint* noofpoly, int maxshapes, int maxcoords);
#endif

