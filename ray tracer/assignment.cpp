/*========================================================================
* COSC 363  Computer Graphics (2017)
* Ray tracer 
* See Lab07.pdf for details.
*=========================================================================
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "SceneObject.h"
#include "Ray.h"
#include "Plane.h"
#include "TextureBMP.h"
#include <GL/glut.h>
using namespace std;

const float WIDTH = 20.0;  
const float HEIGHT = 20.0;
const float EDIST = 40.0;
const int NUMDIV = 500;
const int MAX_STEPS = 5;
const float XMIN = -WIDTH * 0.5;
const float XMAX =  WIDTH * 0.5;
const float YMIN = -HEIGHT * 0.5;
const float YMAX =  HEIGHT * 0.5;
TextureBMP texture;
TextureBMP texture1;

vector<SceneObject*> sceneObjects;  //A global list containing pointers to objects in the scene

//---The most important function in a ray tracer! ---------------------------------- 
//   Computes the colour value obtained by tracing a ray and finding its 
//     closest point of intersection with objects in the scene.
//----------------------------------------------------------------------------------

/*struct Light {
    glm::vec4 position;
    glm::vec3 intensities; //the color of the light
    float attenuation;
    float ambientCoefficient;
    float coneAngle;
    glm::vec3 coneDirection;
};*/

glm::vec3 trace(Ray ray, int step)
{
	
	glm::vec3 backgroundCol(0.2);
	glm::vec3 light(-10, 50, -3); // light1
	
	glm::vec3 light1(25, 10, -3); // light2
	
	glm::vec3 specular(1, 1, 1);
	float ambientTerm = 0.2;

    ray.closestPt(sceneObjects);		//Compute the closest point of intersetion of objects with the ray

    if(ray.xindex == -1) return backgroundCol;      //If there is no intersection return background colour
	glm::vec3 col = sceneObjects[ray.xindex]->getColor();
	glm::vec3 normalVector = sceneObjects[ray.xindex]->normal(ray.xpt);
	//===================================light1=======================
	glm::vec3 lightVector = light - ray.xpt;
	float lightDist = glm::length(lightVector);
	lightVector = glm::normalize(lightVector);
	Ray shadow(ray.xpt, lightVector);
	shadow.closestPt(sceneObjects);
	glm::vec3 reflVector = glm::reflect(-lightVector, normalVector);
	reflVector = glm::normalize(reflVector);
	//====================================light2=======================
	glm::vec3 lightVector1 = light1 - ray.xpt;
	float lightDist1 = glm::length(lightVector1);
	lightVector1 = glm::normalize(lightVector1);
	Ray shadow1(ray.xpt, lightVector1);
	shadow1.closestPt(sceneObjects);
	glm::vec3 reflVector1 = glm::reflect(-lightVector1, normalVector);
	reflVector1 = glm::normalize(reflVector1);
	

	
	if(ray.xindex == 1){
		float a = asin(normalVector.x) / M_PI + 0.5;
		float b = asin(normalVector.y) / M_PI + 0.5;
		col = texture.getColorAt(a, b);
	}
	if (ray.xindex == 6){
		float texcoords = (ray.xpt.x + 20) / 40;
		float texcoordt = -(ray.xpt.z + 40)/ 160;
		col = texture1.getColorAt(texcoords, texcoordt);
	}
	//==========================light1=======================
	float lDotn = glm::dot(lightVector, normalVector);
	float f = 30;
	glm::vec3 colorSum;
	
	if (lDotn <= 0 || (shadow.xindex > -1 && shadow.xdist < lightDist)){
		col = ambientTerm * col;
	}
	else{
		col = ambientTerm*col + lDotn*col + pow(lDotn, f)*specular;
		
	}
	//===========================light2=======================
	float lDotn1 = glm::dot(lightVector1, normalVector);
	if (lDotn1 <= 0 || (shadow1.xindex > -1 && shadow1.xdist < lightDist1)){
		col = ambientTerm * col;
	}
	else{
		col = ambientTerm*col + lDotn1*col + pow(lDotn1, f)*specular;
	}
	
	float refract_rgb = 0.2;
	//===========================Transparent=======================
	if(ray.xindex == 2 && step < MAX_STEPS){
		float eta = 1/1.01;
		//ray in
		glm::vec3 n = sceneObjects[ray.xindex]->normal(ray.xpt);
		glm::vec3 g = glm::refract(ray.dir, n, eta);
		Ray tranRay1(ray.xpt, g);
		tranRay1.closestPt(sceneObjects);
		if(tranRay1.xindex == -1) return backgroundCol; 
		glm::vec3 m = sceneObjects[tranRay1.xindex]->normal(tranRay1.xpt);
		glm::vec3 h = glm::refract(g, -m, 1.0f/eta);
		//ray out
		Ray Rayout(tranRay1.xpt, h);
		Rayout.closestPt(sceneObjects);
		if(Rayout.xindex == -1) return backgroundCol; 
		glm::vec3 tranCol = trace(Rayout, step+1);
		colorSum = colorSum * refract_rgb + tranCol*(1 - refract_rgb);
		return colorSum;
	
	}
	
	//===========================Refraction=======================
	if(ray.xindex == 3 && step < MAX_STEPS){
		float eta = 1/1.5;
		//ray in
		glm::vec3 fn = sceneObjects[ray.xindex]->normal(ray.xpt);
		glm::vec3 fg = glm::refract(ray.dir, fn, eta);
		Ray refrRay1(ray.xpt, fg);
		refrRay1.closestPt(sceneObjects);
		if(refrRay1.xindex == -1) return backgroundCol; 
		glm::vec3 fm = sceneObjects[refrRay1.xindex]->normal(refrRay1.xpt);
		glm::vec3 fh = glm::refract(fg, -fm, 1.0f/eta);
		//ray out
		Ray Rayout1(refrRay1.xpt, fh);
		Rayout1.closestPt(sceneObjects);
		if(Rayout1.xindex == -1) return backgroundCol; 
		glm::vec3 refractedCol = trace(Rayout1, step+1);
		colorSum = colorSum * glm::vec3(0.2) + refractedCol;
		return colorSum;
	
	}

	//===========================reflection=======================
	if(ray.xindex == 0 && step < MAX_STEPS)
	{
	glm::vec3 reflectedDir = glm::reflect(ray.dir, normalVector);
	Ray reflectedRay(ray.xpt, reflectedDir);
	glm::vec3 reflectedCol = trace(reflectedRay, step+1); //Recursion!
	col = col + (0.8f*reflectedCol);
	}
	
	colorSum = col;
	
	return colorSum;
}

//---The main display module -----------------------------------------------------------
// In a ray tracing application, it just displays the ray traced image by drawing
// each cell as a quad.
//---------------------------------------------------------------------------------------
void display()
{
	float xp, yp;  //grid point
	float cellX = (XMAX-XMIN)/NUMDIV;  //cell width
	float cellY = (YMAX-YMIN)/NUMDIV;  //cell height

	glm::vec3 eye(0., -10., 0.);  //The eye position (source of primary rays) is the origin

	glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBegin(GL_QUADS);  //Each cell is a quad.

	for(int i = 0; i < NUMDIV; i++)  	//For each grid point xp, yp
	{
		xp = XMIN + i*cellX;
		for(int j = 0; j < NUMDIV; j++)
		{
			yp = YMIN + j*cellY;
			
			//===========================non-anti aliasing=======================
			/*glm::vec3 dir(xp+0.5*cellX, yp+0.5*cellY, -EDIST);	//direction of the primary ray

		    Ray ray = Ray(eye, dir);		//Create a ray originating from the camera in the direction 'dir'
			ray.normalize();				//Normalize the direction of the ray to a unit vector
		    glm::vec3 col = trace (ray, 1); //Trace the primary ray and get the colour value

			glColor3f(col.r, col.g, col.b);*/
			//===========================anti_aliasing=======================
		    glm::vec3 dir1(xp+0.25*cellX, yp+0.25*cellY, -EDIST);	//direction of the primary ray
			glm::vec3 dir2(xp+0.75*cellX, yp+0.75*cellY, -EDIST);
			glm::vec3 dir3(xp+0.75*cellX, yp+0.25*cellY, -EDIST);
			glm::vec3 dir4(xp+0.25*cellX, yp+0.75*cellY, -EDIST);
		    Ray ray1 = Ray(eye, dir1);		//Create a ray originating from the camera in the direction 'dir'
		    Ray ray2 = Ray(eye, dir2);
		    Ray ray3 = Ray(eye, dir3);
		    Ray ray4 = Ray(eye, dir4);
			ray1.normalize();				//Normalize the direction of the ray to a unit vector
			ray2.normalize();
			ray3.normalize();
			ray4.normalize();
		    glm::vec3 col1 = trace (ray1, 1); //Trace the primary ray and get the colour value
		    glm::vec3 col2 = trace (ray2, 1);
		    glm::vec3 col3 = trace (ray3, 1);
		    glm::vec3 col4 = trace (ray4, 1);

			float R = (col1.r + col2.r + col3.r + col4.r) / 4;
			float G = (col1.g + col2.g + col3.g + col4.g) / 4;
			float B = (col1.b + col2.b + col3.b + col4.b) / 4;
			glColor3f(R, G, B);
			glVertex2f(xp, yp);				//Draw each cell with its color value
			glVertex2f(xp+cellX, yp);
			glVertex2f(xp+cellX, yp+cellY);
			glVertex2f(xp, yp+cellY);
        }
    }

    glEnd();
    glFlush();
}


//---This function initializes the scene ------------------------------------------- 
//   Specifically, it creates scene objects (spheres, planes, cones, cylinders etc)
//     and add them to the list of scene objects.
//   It also initializes the OpenGL orthographc projection matrix for drawing the
//     the ray traced image.
//----------------------------------------------------------------------------------
void initialize()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(XMIN, XMAX, YMIN, YMAX);
    glClearColor(0, 0, 0, 1);

	//-- Create a pointer to a sphere object
	Sphere *sphere1 = new Sphere(glm::vec3(-5.0, -5.0, -100.0), 15.0, glm::vec3(0, 0, 1));
	Sphere *sphere2 = new Sphere(glm::vec3(3.0, 3.0, -80.0), 3.0, glm::vec3(1, 0, 0));
	Sphere *sphere3 = new Sphere(glm::vec3(6.0, -13.0, -65.0), 3.0, glm::vec3(0, 1, 0));
	Sphere *sphere4 = new Sphere(glm::vec3(-9, -15, -55.0), 3.0, glm::vec3(0, 1, 0));
	
	Cylinder *cylinder1 = new Cylinder(glm::vec3(-5, -18, -65.0), 2, 6, glm::vec3(0, 1, 1));
	
	Cone *cone1 = new Cone(glm::vec3(0, -18, -70.0), 2, 6, glm::vec3(1, 0, 1));
	//--Add the above to the list of scene objects.
	sceneObjects.push_back(sphere1);
	sceneObjects.push_back(sphere2);
	sceneObjects.push_back(sphere3);
	sceneObjects.push_back(sphere4);
	
	sceneObjects.push_back(cylinder1);
	
	sceneObjects.push_back(cone1);
	
	Plane *plane = new Plane (glm::vec3(-20., -20, -40),//Point A
	glm::vec3(20., -20, -40),//Point B
	glm::vec3(20., -20, -200),//Point C
	glm::vec3(-20., -20, -200),//Point D
	glm::vec3(0.5, 0.5, 0));//Colour
	
	sceneObjects.push_back(plane);
	
	//============================planes of box========================
	//top
	Plane *plane1 = new Plane(glm::vec3(3, -15, -40),
	glm::vec3(8, -15, -40),
	glm::vec3(8, -15, -44),
	glm::vec3(3, -15, -44),
	glm::vec3(1, 1, 0));
	
	//bottom
	Plane *plane2 = new Plane(glm::vec3(3, -19, -40),
	glm::vec3(8, -19, -40),
	glm::vec3(8, -19, -44),
	glm::vec3(3, -19, -44),
	glm::vec3(4, 1, 0));
	
	//left
	Plane *plane4 = new Plane(glm::vec3(3, -15, -40),
	glm::vec3(3, -19, -40),
	glm::vec3(3, -19, -44),
	glm::vec3(3, -15, -44),
	glm::vec3(1, 1, 0));
	
	//right
	Plane *plane3 = new Plane(glm::vec3(8, -15, -40),
	glm::vec3(8, -19, -40),
	glm::vec3(8, -19, -44),
	glm::vec3(8, -15, -44),
	glm::vec3(1, 1, 0));

	//back
	Plane *plane5 = new Plane(glm::vec3(3, -19, -44),
	glm::vec3(8, -19, -44),
	glm::vec3(8, -15, -44),
	glm::vec3(3, -15, -44),
	glm::vec3(1, 1, 0));
	
	//front
	Plane *plane6 = new Plane(glm::vec3(3, -19, -40),
	glm::vec3(8, -19, -40),
	glm::vec3(8, -15, -40),
	glm::vec3(3, -15, -40),
	glm::vec3(1, 1, 0));
	
	
	sceneObjects.push_back(plane1);
	sceneObjects.push_back(plane2);
	sceneObjects.push_back(plane3);
	sceneObjects.push_back(plane4);
	sceneObjects.push_back(plane5);
	sceneObjects.push_back(plane6);
	//=================================================================
	/*Light spotlight;
    spotlight.position = glm::vec4(-4,0,10,1);
    spotlight.intensities = glm::vec3(2,2,2); //strong white light
    spotlight.attenuation = 0.1f;
    spotlight.ambientCoefficient = 0.0f; //no ambient light
    spotlight.coneAngle = 15.0f;
    spotlight.coneDirection = glm::vec3(0,0,-1);
    sceneObjects.push_back(spotlight);*/
	
	texture = TextureBMP((char*)"line.bmp");
	texture1 = TextureBMP((char*)"floor.bmp");

}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Raytracer");

    glutDisplayFunc(display);
    initialize();

    glutMainLoop();
    return 0;
}
