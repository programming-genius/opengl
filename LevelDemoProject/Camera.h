/* 3D OpenGL Computer Graphics Lectures by Alessandro Zoia - 2017

 This software is provided 'as-is', without any express or
 implied warranty. In no event will the author be held
 liable for any damages arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute
 it freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented;
	you must not claim that you wrote the original software.
	If you use this software in a product, an acknowledgment
	in the product documentation would be appreciated but
	is not required.

 2. Altered source versions must be plainly marked as such,
	and must not be misrepresented as being the original software.

 3. This notice may not be removed or altered from any
	source distribution.
*/

#ifndef CAMERA_H
#define CAMERA_H

#ifndef PI_180
#define PI_180 (3.14159265359 / 180.0) 
#endif

#include <gl/glut.h>
#include "Geometry.h"
#include "vector3.h"

class Camera {

public:

	Camera();
	~Camera();

	void setPosition(GLdouble xPos, GLdouble yPos, GLdouble zPos);
	void setOrientation(GLdouble rollAngle, GLdouble pitchAngle, GLdouble yawAngle);
	/* View direction of the Camera */
	Vector3 getDirection();
	/* Description: Executes the view trasformation */
	void viewTransform();

private:

	/*Note : in the default behavior the camera is located on the z positive axis and
			 look the negative z axis*/

	/* Orientation */
	GLdouble roll = 0;
	GLdouble pitch = 0;
	GLdouble yaw = 0;

	/* Position */
	GLdouble x = 0;
	GLdouble y = 0;
	GLdouble z = 0;

	/* Homogeneous Trasformation Matrix in array form */
	/* 1 column  a0 a1 a2 a3
	   2 column  a4 a5 a6 a7
	   3 column  a8 a9 a10 a11
	   4 column  a12 a13 a14 a15 */
	GLdouble* hTransformInverse = nullptr;

};
#endif