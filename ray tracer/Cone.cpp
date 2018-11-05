/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The Cylinder class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cone.h"
#include <math.h>

/**
* Cone's intersection method.  The input is a ray (pos, dir). 
*/
float Cone::intersect(glm::vec3 posn, glm::vec3 dir)
{
    float x = posn.x - center.x;
    float y = height - posn.y + center.y;
    float z = posn.z - center.z;
    
    float tan_theta = (radius/height) * (radius/height);
    
    float a = dir.x * dir.x + dir.z * dir.z - tan_theta*(dir.y * dir.y);
    float b = 2 * dir.x * x + 2 * dir.z* z + 2*tan_theta*y*dir.y;
    float c = x * x + z * z - tan_theta*y*y;
    float delta = b*b - 4*a*c;
    
	//if(fabs(delta) < 0.001) return -1.0; 
    //if(delta < 0.0) return -1.0;

    float t1 = (-b - sqrt(delta)) / (2 * a);
    float t2 = (-b + sqrt(delta)) / (2 * a);
    
    if(fabs(t1) < 0.001 )
    {
        if (t2 > 0){
			return t2;
		}
		
        else{
			t1 = -1;
		}
    }
	if(fabs(t2) < 0.001 ){
		t2 = -1;
	}
    
    float max;
    float min;

	if(t1 < t2){
		min = t1;
		max = t2;
	}
	else {
		min = t2;
		max = t1;
	}
	
	float y1 = (posn.y + min * dir.y) - center.y;
	float y2 = (posn.y + max * dir.y) - center.y;
	
	if(not (y1 < 0 || y1 > height) && min != -1){
		return min;
	}
	
	else if(not (y2 < 0 || y2 > height) && max != -1){
		return max;
	}
	else{
		return -1;
	}
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the Cone.
*/
glm::vec3 Cone::normal(glm::vec3 p)
{
	float r = sqrt((p.x -center.x) * (p.x -center.x) + (p.z -center.z) * (p.z -center.z));
    glm::vec3 n = glm::vec3 (p.x-center.x, r*(radius/height), p.z - center.z);
    n = glm::normalize(n);
    return n;
}
