// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

int COUNT = 0;
int NUM = 0;
vector< vec3 > pts;
vec3 lastPoint;


void bezier(vector< vec3 > &points)
{
		//GLfloat L = (1 - t)*((1-t)*P0 + t*P1) + t((1-t)*P1 + t*P2);
		
		

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 800, 0, 800, -1, 1);
		// Restore the default matrix mode
		glMatrixMode(GL_MODELVIEW);

				
		glBegin(GL_LINES);
		glColor3f(0.0f, 1.0f, 0.0f);
		
		for(GLfloat t = 0.0; t <=1.0; t += 0.05)
		{
			vec3 L1;
			
			L1 = (1 - t) * ( (1-t)*points[0] + t*points[1] ) + t * ((1-t)*points[1] + t*points[2]);
	
			//vec3 L2 = t * ((1-t)*points[1] + t*points[2]);
			//lastPoint = L2;
			
			glVertex2f(L1[0], L1[1]);
			
			GLfloat r = 0.05;
			vec3 L2 = (1 - (t + r)) * ( (1-(t + r))*points[0] + (t+r)*points[1] ) + (t+r) * ((1-(t+r))*points[1] + (t+r)*points[2]);
			
			glVertex2f(L2[0], L2[1]);
		
			//glVertex2f(points[1][0], points[1][1]);
			//glVertex2f(points[2][0], points[2][1]);
		}
		
		
		
		glEnd();
		
		points.clear();
		
		glFlush();
		
		
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    // just for example, remove if desired
	
	
    glVertex2f(-.5f,-.5f);
    glVertex2f(.5f,-.5f);
	
    glVertex2f(.5f,.5f);
    glVertex2f(-.5f,.5f);
	
    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);
	

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
		
		//cout << "Hello" << endl;
		vec3 temp(x,y,1);
		pts.push_back(temp);
		COUNT++;
	
		if(COUNT == 3)
		{
			//cout << "Hellooo" << endl;
			bezier(pts);
			COUNT = 0;
		}
		
		
		
		
        //glutPostRedisplay();
		

		

    }

}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
