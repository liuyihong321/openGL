#include <iostream>
#include <cmath>
#include <climits>
#include <math.h>
#include <fstream>
#include <GL/freeglut.h>
#include "loadTGA.h"
#include <math.h>
using namespace std;
//--Globals ---------------------------------------------------------------
float angle = 10.0;  //Rotation angle for viewing
float theta = 15.0;
float cam_hgt = 30;
float flagTime = 1;
float shift = 0.0f;
float eye_x = -20, eye_y = 20, eye_z = 150;    //Initial camera position
float look_x = 12, look_y = 1, look_z = 12;    //"Look-at" point along -z direction
float  degree = 0;
float circle = 0;
float crystal_angle = 0;
float move_robot = 0;
float robot_time = 0;

float ship_x= 0.0;
float ship_y= 0.0;
float ship_z= 0.0;

int step = 0;
int moving = 0;
int box_move = 0;
int ball = 0;

bool first_person_view = false;

GLUquadricObj*	q;
GLuint txId[13];

void loadTexture(void)
{
	glGenTextures(13, txId);
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, txId[1]);
	loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D,  txId[2]);
	loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, txId[3]);
	loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, txId[4]);
	loadTGA("up.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, txId[5]);
	loadTGA("down.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_CLAMP);

	glBindTexture(GL_TEXTURE_2D, txId[6]);
	loadTGA("flag.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[7]);
	loadTGA("frame.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[8]);
	loadTGA("glass.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[9]);
	loadTGA("glass_texture.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, txId[10]);
	loadTGA("roof.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[11]);
	loadTGA("wall.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
    glBindTexture(GL_TEXTURE_2D, txId[12]);
	loadTGA("spaceship.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
}


//	Create the skybox
void skybox() {

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPushMatrix();

		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		// Back
		glBindTexture(GL_TEXTURE_2D, txId[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);		glVertex3f(-256.0, -256.0, -256.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f( 256.0, -256.0, -256.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f( 256.0,  256.0, -256.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(-256.0,  256.0, -256.0);
		glEnd();
		// Right
		glBindTexture(GL_TEXTURE_2D, txId[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);		glVertex3f(256.0, -256.0, -256.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f(256.0, -256.0,  256.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(256.0,  256.0,  256.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(256.0,  256.0, -256.0);
		glEnd();
		// Front
		glBindTexture(GL_TEXTURE_2D, txId[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);		glVertex3f( 256.0, -256.0, 256.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f(-256.0, -256.0, 256.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(-256.0,  256.0, 256.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f( 256.0,  256.0, 256.0);
		glEnd();
		// Left
		glBindTexture(GL_TEXTURE_2D, txId[3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);		glVertex3f(-256.0, -256.0,  256.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f(-256.0, -256.0, -256.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(-256.0,  256.0, -256.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(-256.0,  256.0,  256.0);
		glEnd();
		// Up
		glBindTexture(GL_TEXTURE_2D, txId[4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);		glVertex3f( 256.0,  256.0, -256.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f( 256.0,  256.0,  256.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(-256.0,  256.0,  256.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(-256.0,  256.0, -256.0);
		glEnd();
		// Down
		glBindTexture(GL_TEXTURE_2D, txId[5]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);		glVertex3f( 256.0,  -0.1, -256.0);
			glTexCoord2f(1.0, 0.0);		glVertex3f( 256.0,  -0.1,  256.0);
			glTexCoord2f(1.0, 1.0);		glVertex3f(-256.0,  -0.1,  256.0);
			glTexCoord2f(0.0, 1.0);		glVertex3f(-256.0,  -0.1, -256.0);
		glEnd();

	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void drawstar(){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[12]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    glEnable(GL_LIGHTING);
    gluQuadricTexture(q, GL_TRUE);
    gluQuadricNormals(q, GLU_SMOOTH);
    gluSphere(q, 9, 15, 15);
	glPopMatrix();
	
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glRotatef(90, 1, 0, 0);
	gluDisk(q, 10, 15, 100, 100);
	gluQuadricDrawStyle(q, GLU_FILL);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, ball, 0);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(3, 30, 15);
	glPopMatrix();
	
}

void drawOctahedron(){
	glPushMatrix();
	glEnable(GL_LIGHTING);
		glColor3f(0.85, 0.92, 0.96);
		glRotatef(circle, 0, 1, 0);
	    glTranslatef(-10.0f, 20.0f, -40.0f);
	    glRotatef(circle, 0, 1, 0);
	    glRotatef(-10., 1.0, 0., 0.0);
	    glutSolidOctahedron();
    glPopMatrix();
    glDisable(GL_LIGHTING);

}

void drawrobot()
{
	
	glEnable(GL_LIGHTING);
	glTranslatef(20.0f, 0.0f, 30.0f);
	glColor3f(1., 0.78, 0.06);		//Head
	glPushMatrix();
	  glTranslatef(0, 7.7, 0);
	  glutSolidSphere(1.5, 10, 5);
	glPopMatrix();
	
	glColor3f(1., 0.0 ,0.0);		
	glPushMatrix();             //eye
        glTranslatef(-0.3, 8, 1.5);
        glutSolidCube(0.3);
        glTranslatef(0.6, 0, 0);
        glutSolidCube(0.3);
	glPopMatrix();
	
	glColor3f(1., 0.0 ,0.0);		
	glPushMatrix();             //mouth
        glTranslatef(-0.1, 7, 1.5);
        glutSolidCube(0.3);
        glTranslatef(0.2, 0, 0);
        glutSolidCube(0.3);
	glPopMatrix();
	glColor3f(1., 0., 0.);			//Torso
	glPushMatrix();
	  glTranslatef(0, 5.5, 0);
	  glScalef(3, 3, 1.4);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right leg
	glPushMatrix();
	  glTranslatef(-0.8, 4, 0);
	  glRotatef(-theta, 1, 0, 0);
	  glTranslatef(0.8, -4, 0);
	  glTranslatef(-0.8, 2.2, 0);
	  glScalef(1, 4.4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left leg
	glPushMatrix();
	  glTranslatef(0.8, 4, 0);
	  glRotatef(theta, 1, 0, 0);
	  glTranslatef(0, -1.8, 0);
	  glScalef(1, 4.4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Right arm
	glPushMatrix();
	  glTranslatef(0.8, 4, 0);
	  glRotatef(theta, 1, 0, 0);
	  glTranslatef(-0.8, -4, 0);
	  glTranslatef(-2, 5, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();

	glColor3f(0., 0., 1.);			//Left arm
	glPushMatrix();
	  glTranslatef(2, 6.5, 0);
	  glRotatef(-theta, 1, 0, 0);
	  glTranslatef(-2, -6.5, 0);
	  glTranslatef(2, 5, 0);
	  glScalef(1, 4, 1);
	  glutSolidCube(1);
	glPopMatrix();
	
}

void shadow(){
	//shadow
	float shadowMat[16] = {80,0,0,0, -80,0,-80,-1, 0,0,80,0, 0,0,0,80};
	glDisable(GL_LIGHTING);
	glTranslatef(-20,0,-30);
	glPushMatrix();
		glMultMatrixf(shadowMat);
		glTranslatef(20.0f, 0.0f, 30.0f);
		glColor3f(0, 0, 0);		//Head
		glPushMatrix();
		  glTranslatef(0, 7.7, 0);
		  glutSolidSphere(1.5, 10, 5);
		glPopMatrix();
		
		glColor3f(0, 0, 0);		
		glPushMatrix();             //eye
			glTranslatef(-0.3, 8, 1.5);
			glutSolidCube(0.3);
			glTranslatef(0.6, 0, 0);
			glutSolidCube(0.3);
		glPopMatrix();
		
		glColor3f(0, 0, 0);		
		glPushMatrix();             //mouth
			glTranslatef(-0.1, 7, 1.5);
			glutSolidCube(0.3);
			glTranslatef(0.2, 0, 0);
			glutSolidCube(0.3);
		glPopMatrix();
		glColor3f(0, 0, 0);			//Torso
		glPushMatrix();
		  glTranslatef(0, 5.5, 0);
		  glScalef(3, 3, 1.4);
		  glutSolidCube(1);
		glPopMatrix();

		glColor3f(0, 0, 0);			//Right leg
		glPushMatrix();
		  glTranslatef(-0.8, 4, 0);
		  glRotatef(-theta, 1, 0, 0);
		  glTranslatef(0.8, -4, 0);
		  glTranslatef(-0.8, 2.2, 0);
		  glScalef(1, 4.4, 1);
		  glutSolidCube(1);
		glPopMatrix();

		glColor3f(0, 0, 0);			//Left leg
		glPushMatrix();
		  glTranslatef(0.8, 4, 0);
		  glRotatef(theta, 1, 0, 0);
		  glTranslatef(0, -1.8, 0);
		  glScalef(1, 4.4, 1);
		  glutSolidCube(1);
		glPopMatrix();

		glColor3f(0, 0, 0);			//Right arm
		glPushMatrix();
		  glTranslatef(0.8, 4, 0);
		  glRotatef(theta, 1, 0, 0);
		  glTranslatef(-0.8, -4, 0);
		  glTranslatef(-2, 5, 0);
		  glScalef(1, 4, 1);
		  glutSolidCube(1);
		glPopMatrix();

		glColor3f(0, 0, 0);			//Left arm
		glPushMatrix();
		  glTranslatef(2, 6.5, 0);
		  glRotatef(-theta, 1, 0, 0);
		  glTranslatef(-2, -6.5, 0);
		  glTranslatef(2, 5, 0);
		  glScalef(1, 4, 1);
		  glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawhouse()
{
		glPushMatrix();
		{
		glTranslatef(-10.0f, 0.0f, 0.0f);

		glEnable(GL_LIGHTING);

		glEnable(GL_TEXTURE_2D);
		//chimney
		glBindTexture(GL_TEXTURE_2D, txId[8]);

		glBegin(GL_QUADS ); {
			glNormal3f(0, 1, 0);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(-2.4f, -12.0f, 26.4f);
			glTexCoord2d(0.0, 6.0 ); glVertex3f(-2.4f, 26.4f, 26.4f);
			glTexCoord2d(1.0, 6.0 ); glVertex3f(-2.4f, 26.4f, 21.6f);
			glTexCoord2d(1.0, 0.0 ); glVertex3f(-2.4f, -12.0f, 21.6f);

			glTexCoord2d(1.0, 0.0 ); glVertex3f(-2.4f, -12.0f, 21.6f);
			glTexCoord2d(1.0, 6.0 ); glVertex3f(-2.4f, 26.4f, 21.6f);
			glTexCoord2d(0.0, 6.0 ); glVertex3f(2.4f, 26.4f, 21.6f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(2.4f, -12.0f, 21.6f);

			glTexCoord2d(0.0, 0.0 ); glVertex3f(2.4f, -12.0f, 21.6f);
			glTexCoord2d(0.0, 6.0 ); glVertex3f(2.4f, 26.4f, 21.6f);
			glTexCoord2d(1.0, 6.0 ); glVertex3f(2.4f, 26.4f, 26.4f);
			glTexCoord2d(1.0, 0.0 ); glVertex3f(2.4f, -12.0f, 26.4f);

			glTexCoord2d(1.0, 0.0 ); glVertex3f(2.4f, -12.0f, 26.4f);
			glTexCoord2d(1.0, 6.0 ); glVertex3f(2.4f, 26.4f, 26.4f);
			glTexCoord2d(0.0, 6.0 ); glVertex3f(-2.4f, 26.4f, 26.4f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(-2.4f, -12.0f, 26.4f);

			glTexCoord2d(0.0, 0.0 ); glVertex3f(-2.4f, 26.4f, 26.4f);
			glTexCoord2d(0.0, 1.0 ); glVertex3f(-2.4f, 26.4f, 21.6f);
			glTexCoord2d(1.0, 1.0 ); glVertex3f(2.4f, 26.4f, 21.6f);
			glTexCoord2d(1.0, 0.0 ); glVertex3f(2.4f, 26.4f, 26.4f);
		}
		glEnd();
		//wall
		glBindTexture(GL_TEXTURE_2D, txId[11]);

		glBegin(GL_QUADS ); {
			glNormal3f(0, 1, 0);
			glTexCoord2d(0.0, 0.0 ); glVertex3f( -18.0f, -12.0f, 24.0f);
			glTexCoord2d(0.0, 5.0 ); glVertex3f( -18.0f,  18.0f, 24.0f);
			glTexCoord2d(8.0, 5.0 ); glVertex3f( -18.0f,  18.0f, -24.0f);
			glTexCoord2d(8.0, 0.0 ); glVertex3f( -18.0f, -12.0f, -24.0f);

			glTexCoord2d(8.0, 0.0 ); glVertex3f( -18.0f, -12.0f, -24.0f);
			glTexCoord2d(8.0, 5.0 ); glVertex3f( -18.0f,  18.0f, -24.0f);
			glTexCoord2d(2.0, 5.0 ); glVertex3f(  18.0f,  18.0f, -24.0f);
			glTexCoord2d(2.0, 0.0 ); glVertex3f(  18.0f, -12.0f, -24.0f);

			glTexCoord2d(2.0, 0.0 ); glVertex3f(  18.0f, -12.0f, -24.0f);
			glTexCoord2d(2.0, 5.0 ); glVertex3f(  18.0f,  18.0f, -24.0f);
			glTexCoord2d(10.0, 5.0 ); glVertex3f(  18.0f,  18.0f, 24.0f);
			glTexCoord2d(10.0, 0.0 ); glVertex3f(  18.0f, -12.0f, 24.0f);

			glTexCoord2d(10.0, 0.0 ); glVertex3f(  18.0f, -12.0f, 24.0f);
			glTexCoord2d(10.0, 5.0 ); glVertex3f(  18.0f,  18.0f, 24.0f);
			glTexCoord2d(4.0, 5.0 ); glVertex3f( -18.0f,  18.0f, 24.0f);
			glTexCoord2d(4.0, 0.0 ); glVertex3f( -18.0f, -12.0f, 24.0f);

		}
		glEnd();

		glBegin(GL_TRIANGLES ); {
			glNormal3f(0, 1, 0);
			glTexCoord2d(0.0, 0.0 ); glVertex3f( -18.0f, 18.0f, 24.0f);
			glTexCoord2d(3.0, 0.0 ); glVertex3f(   0.0f, 18.0f, 24.0f);
			glTexCoord2d(3.0, 1.0 ); glVertex3f(   0.0f, 24.0f, 24.0f);

			glTexCoord2d(3.0, 1.0 ); glVertex3f(   0.0f, 24.0f, 24.0f);
			glTexCoord2d(3.0, 0.0 ); glVertex3f(   0.0f, 18.0f, 24.0f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(  18.0f, 18.0f, 24.0f);
		}
		glEnd();

		glBegin(GL_TRIANGLES ); {
			glNormal3f(0, 1, 0);
			glTexCoord2d(3.0, 0.0 ); glVertex3f(   0.0f, 18.0f, -24.0f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f( -18.0f, 18.0f, -24.0f);
			glTexCoord2d(3.0, 1.0 ); glVertex3f(   0.0f, 24.0f, -24.0f);

			glTexCoord2d(3.0, 0.0 ); glVertex3f(   0.0f, 18.0f, -24.0f);
			glTexCoord2d(3.0, 1.0 ); glVertex3f(   0.0f, 24.0f, -24.0f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(  18.0f, 18.0f, -24.0f);
		}
		glEnd();

		glBegin(GL_QUADS ); {
			glNormal3f(0, 1, 0);
			glTexCoord2d(0.0, 0.0 ); glVertex3f( 18.0f, -12.0f, 12.0f);
			glTexCoord2d(0.0, 5.0 ); glVertex3f( 18.0f,  18.0f, 12.0f);
			glTexCoord2d(4.0, 5.0 ); glVertex3f( 18.0f,  18.0f, -12.0f);
			glTexCoord2d(4.0, 0.0 ); glVertex3f( 18.0f, -12.0f, -12.0f);

			glTexCoord2d(4.0, 0.0 ); glVertex3f( 18.0f, -12.0f, -12.0f);
			glTexCoord2d(4.0, 5.0 ); glVertex3f( 18.0f,  18.0f, -12.0f);
			glTexCoord2d(2.0, 5.0 ); glVertex3f( 24.0f,  18.0f, -12.0f);
			glTexCoord2d(2.0, 0.0 ); glVertex3f( 24.0f, -12.0f, -12.0f);

			glTexCoord2d(4.0, 0.0 ); glVertex3f( 24.0f, -12.0f, -12.0f);
			glTexCoord2d(4.0, 5.0 ); glVertex3f( 24.0f, 18.0f, -12.0f);
			glTexCoord2d(6.0, 5.0 ); glVertex3f( 24.0f, 18.0f, 12.0f);
			glTexCoord2d(6.0, 0.0 ); glVertex3f( 24.0f, -12.0f, 12.0f);

			glTexCoord2d(6.0, 0.0 ); glVertex3f( 24.0f, -12.0f, 12.0f);
			glTexCoord2d(6.0, 5.0 ); glVertex3f( 24.0f,  18.0f, 12.0f);
			glTexCoord2d(4.0, 5.0 ); glVertex3f( 18.0f,  18.0f, 12.0f);
			glTexCoord2d(4.0, 0.0 ); glVertex3f( 18.0f, -12.0f, 12.0f);
		}
		glEnd();

		glBegin(GL_TRIANGLES ); {
			glNormal3f(0, 1, 0);
			glTexCoord2d(0.0, 0.0); glVertex3f( 24.0f, 18.0f, 12.0f);
			glTexCoord2d(2.0, 0.0); glVertex3f( 24.0f, 18.0f, 0.0f);
			glTexCoord2d(2.0, 1.0); glVertex3f( 24.0f, 24.0f, 0.0f);

			glTexCoord2d(2.0, 1.0); glVertex3f(24.0f, 24.0f, 0.0f);
			glTexCoord2d(2.0, 0.0); glVertex3f(24.0f, 18.0f, 0.0f);
			glTexCoord2d(0.0, 0.0); glVertex3f(24.0f, 18.0f, -12.0f);
		}
		glEnd();

		//roof
		glBindTexture(GL_TEXTURE_2D, txId[10]);

		glBegin(GL_QUADS); {
			glNormal3f(-25.0f, 35.0f, 0.0f );
			glTexCoord2d(0.0, 0.0 ); glVertex3f( -18.0f, 18.0f, -24.0f);
			glTexCoord2d(0.0, 8.0 ); glVertex3f( -18.0f, 18.0f,  24.0f);
			glTexCoord2d(3.0, 8.0 ); glVertex3f(   0.0f, 24.0f,  24.0f);
			glTexCoord2d(3.0, 0.0 ); glVertex3f(   0.0f, 24.0f, -24.0f);

			glNormal3f(25.0f, 35.0f, 0.0f );
			glTexCoord2d(3.0, 0.0 ); glVertex3f(   0.0f, 24.0f, -24.0f);
			glTexCoord2d(3.0, 8.0 ); glVertex3f(   0.0f, 24.0f,  24.0f);
			glTexCoord2d(0.0, 8.0 ); glVertex3f(  18.0f, 18.0f,  24.0f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(  18.0f, 18.0f, -24.0f);
		}
		glEnd();
		glBegin(GL_QUADS); {
			glNormal3f(15.0f, 35.0f, -30.0f );
			glTexCoord2d(0.0, 0.0 ); glVertex3f(  24.0f, 18.0f, -12.0f);
			glTexCoord2d(5.0, 0.0 ); glVertex3f(   0.0f, 18.0f, -12.0f);
			glTexCoord2d(5.0, 2.0 ); glVertex3f(   0.0f, 24.0f,   0.0f);
			glTexCoord2d(0.0, 2.0 ); glVertex3f(  24.0f, 24.0f,   0.0f);

			glNormal3f(15.0f, 35.0f, 30.0f );
			glTexCoord2d(0.0, 2.0 ); glVertex3f(  24.0f, 24.0f,   0.0f);
			glTexCoord2d(5.0, 2.0 ); glVertex3f(   0.0f, 24.0f,   0.0f);
			glTexCoord2d(5.0, 0.0 ); glVertex3f(   0.0f, 18.0f,  12.0f);
			glTexCoord2d(0.0, 0.0 ); glVertex3f(  24.0f, 18.0f,  12.0f);
		}
		glEnd();
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}

void flag()
{
	glPushMatrix(); 
	glTranslatef(-10.0f, 0.0f, -30.0f);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, txId[7]);
	glBegin(GL_QUADS); {
		glVertex3f(0.5f,  0.0f,  0.5f );
		glVertex3f(0.5f, 45.0f,  0.5f );
		glVertex3f(-0.5f, 45.0f,  0.5f );
		glVertex3f(-0.5f,  0.0f,  0.5f );
		glVertex3f(-0.5f,  0.0f,  0.5f );
		glVertex3f(-0.5f, 45.0f,  0.5f );
		glVertex3f(-0.5f, 45.0f, -0.5f );
		glVertex3f(-0.5f,  0.0f, -0.5f );
		glVertex3f(-0.5f,  0.0f, -0.5f );
		glVertex3f(-0.5f, 45.0f, -0.5f );
		glVertex3f(0.5f, 45.0f, -0.5f );
		glVertex3f(0.5f,  0.0f, -0.5f );
		glVertex3f(0.5f,  0.0f, -0.5f );
		glVertex3f(0.5f, 45.0f, -0.5f );
		glVertex3f(0.5f, 45.0f,  0.5f );
		glVertex3f(0.5f,  0.0f,  0.5f );
	} 
	glEnd();
	glTranslatef( 0.0f, 30.0f, 0.0f );
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[6]);
	glBegin(GL_QUADS);{
		for(float i = 0; i < 10; i += 1) {
			for(float j = 0; j < 14; j += 1) {
				glTexCoord2f((j + 0) / 15.0f, (i + 0) / 10.0f); glVertex3f(sin(i + 0 + shift) + cos(j + 0 + shift), 1.5f * (i + 0), 1.5f * (j + 0));
				glTexCoord2f((j + 0) / 15.0f, (i + 1) / 10.0f); glVertex3f(sin(i + 1 + shift) + cos(j + 0 + shift), 1.5f * (i + 1), 1.5f * (j + 0));
				glTexCoord2f((j + 1) / 15.0f, (i + 1) / 10.0f); glVertex3f(sin(i + 1 + shift) + cos(j + 1 + shift), 1.5f * (i + 1), 1.5f * (j + 1));
				glTexCoord2f((j + 1) / 15.0f, (i + 0) / 10.0f); glVertex3f(sin(i + 0 + shift) + cos(j + 1 + shift), 1.5f * (i + 0), 1.5f * (j + 1));
			}
		}
		shift += 5.0f * flagTime;
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void crystal(){
	glEnable(GL_LIGHTING);
	glPushMatrix();
	
	glTranslatef(-150,0,0);
	glColor3f(0.54, 0.81, 0.94);
	glTranslatef(0,35,0);
	glScalef(15,20,15);
	
	glRotatef(crystal_angle*2, 0, 1, 0);
	glColor3f(0.54, 0.81, 0.94);
	glutSolidOctahedron();
	
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-150,0,0);
	glTranslatef(0,35,0);
	glRotatef(90, 1, 0, 0);
	glRotatef(crystal_angle*2, 0, 1, 0);
	gluDisk(q, 23, 25, 100, 100);
	gluQuadricDrawStyle(q, GLU_FILL);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-150,0,0);
	glTranslatef(0,35,0);
	glRotatef(crystal_angle*2, 0, 1, 0);
	gluDisk(q, 23, 25, 100, 100);
	gluQuadricDrawStyle(q, GLU_FILL);
	glPopMatrix();
}
		
void temple()
{ 
	glPushMatrix();
	glColor3f(0.78, 1, 0.99);
	glEnable(GL_TEXTURE_2D);
	
	
	glPushMatrix();
	glTranslatef(-150,0,0);
	glColor4f(1.0, 1.0, 1.0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, txId[9]);
	glScalef(100,5,100);
	glutSolidCube(1);
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(-150,0,0);
	glColor4f(1.0, 1.0, 1.0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, txId[9]);
	glTranslatef(0,3,0);
	glScalef(80,5,80);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-150,0,0);
	glColor4f(1.0, 1.0, 1.0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, txId[9]);
	glTranslatef(0,6,0);
	glScalef(60,5,60);
	glutSolidCube(1);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
}

void myTimer (int value)
{
	move_robot ++;
	theta = -theta;
	circle ++;
	if(circle > 360) circle = 0;
	
	crystal_angle += 0.5;
	if(crystal_angle > 360) crystal_angle = 0;
	
	glutPostRedisplay();
	glutTimerFunc(100, myTimer, value);
}

void robot_walk(int value){
	moving++;
	if(moving>=320)
	{
		moving=320;
		}
	glutTimerFunc(50, robot_walk, 0);
}

void box_moving(int value){
	box_move++;
	if(box_move>=320)
	{
		box_move=320;
		}
	glutTimerFunc(50, box_moving, value);
}

void ball_drop(int value){
	ball--;
	glutTimerFunc(50, ball_drop, 0);
}
	
void display()
{
	float lpos[4] = {-100., 100., 100., 1.0};
	float light[] = {0, 25, 0, 1};
	float spot_dir[]={0, 1.0, 1.0};
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	
	float dir_x = -sin(degree), dir_y = 0,  dir_z = -cos(degree);
	
	if(step == 1 || step == -1){
	eye_x += step * 1 * dir_x;
	eye_z += step * 1 * dir_z;
	step = 0;
	}
	if (first_person_view != true){
		if (eye_x >= 210){
			eye_x = 210;
		}
		if(eye_x <= -210){
			eye_x = -210;
		}

		if (eye_z >= 220){
			eye_z = 220;
		}
		if(eye_z <= -220){
			eye_z = -220;
		}
		look_x = eye_x + 2 * dir_x;
		look_y = eye_y + 2 * dir_y;
		look_z = eye_z + 2 * dir_z;
		gluLookAt(eye_x, eye_y, eye_z,  look_x, look_y, look_z, 0, 1, 0);
	}
	else{
		glTranslatef(0,-10,0);
		glTranslatef(0,0,30);
		glRotatef(move_robot+10,0,-1,0);
		glTranslatef(0,0,100);
		
	}
	
	
	
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);   //set light position
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT,0.01);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	skybox();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(moving,0,0);
	glPushMatrix();
	glTranslatef(-150,0,70);
	glRotatef(90,0,1,0);
	glPushMatrix();
	glTranslatef(5,0,5);
	drawrobot();
	shadow();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(box_move,0,0);
	glPushMatrix();
	glColor3f(0.51, 0.32, 0.004);
	glTranslatef(-113,10,50);
	glRotatef(90,0,1,0);
	glPushMatrix();
	glTranslatef(5,0,5);
	glutSolidCube(10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
    glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(-move_robot-10,0,1,0);
    glTranslatef(0,0,-60);
    glRotatef(90,0,1,0);
    drawrobot();
    shadow();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(-move_robot-10*5,0,1,0);
    glTranslatef(0,0,-60);
    glRotatef(90,0,1,0);
    drawrobot();
    shadow();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(-move_robot-10*10,0,1,0);
    glTranslatef(0,0,-60);
    glRotatef(90,0,1,0);
    drawrobot();
    shadow();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(-move_robot-10*15,0,1,0);
    glTranslatef(0,0,-60);
    glRotatef(90,0,1,0);
    drawrobot();
    shadow();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(-move_robot-10*20,0,1,0);
    glTranslatef(0,0,-60);
    glRotatef(90,0,1,0);
    drawrobot();
    shadow();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0,-10);
    glRotatef(-move_robot-10*25,0,1,0);
    glTranslatef(0,0,-60);
    glRotatef(90,0,1,0);
    drawrobot();
    shadow();
    glPopMatrix();

	glPushMatrix();
	glTranslatef(-150,0,0);
	
	for (int i =1; i < 12; i ++){
		
		
		glRotatef(-100, 0, 1, 0);
		glRotatef(5, 1, 0, 0);
		glRotatef(circle*i, 0, 1, 0);
		drawOctahedron();
	}

	
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	glPushMatrix();
	flag();
	glPopMatrix();
	
	glPushMatrix();
	drawhouse();
	glPopMatrix();
	
	glPushMatrix();
	temple();
	glPopMatrix();
	
	glPushMatrix();
	crystal();
	glPopMatrix();
	
	glPushMatrix();
	
	glTranslatef(0, 60, 0);
	glTranslatef(ship_x, ship_y, ship_z);
	
	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, light); 
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);
	drawstar();
	glPopMatrix();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glFlush();
	glutSwapBuffers();
}

void initialize()
{
	loadTexture();
	
	glEnable(GL_TEXTURE_2D);
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
	glClearColor(1.0, 1.0, 1.0, 1.0);
	q = gluNewQuadric();
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);


    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 1.0, 20.0, 1000.0);
}

void special(int key, int x, int y)
{
	step = 0;
	if(key == GLUT_KEY_LEFT) degree += 0.1;   //in radians
	else if(key == GLUT_KEY_RIGHT) degree -= 0.1;
	else if(key == GLUT_KEY_DOWN) step = -1;
	else if(key == GLUT_KEY_UP) step = 1;
	

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		
		case '6': ship_x += 3; break;
		case '4': ship_x -= 3; break;
		case '9': ship_y += 3; break;
		case '3': ship_y -= 3; break;
		case '2': ship_z += 3; break;
		case '8': ship_z -= 3; break;
		case ' ': first_person_view = not first_person_view; break;
		case 'f': glutTimerFunc(50, ball_drop, 0);
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (20, 20);
   glutCreateWindow ("Yihong Liu 49118489");
   initialize();
   glutKeyboardUpFunc(keyboard);
   glutTimerFunc(50, myTimer, 0);
   glutTimerFunc(50, robot_walk, 0);
   glutTimerFunc(50, box_moving, 0);
   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
