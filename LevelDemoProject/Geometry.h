/* 3D OpenGL Computer Graphics Lectures  by Alessandro Zoia - 2017

This software is provided 'as-is', without any express or
implied warranty.In no event will the author be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions :

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

#ifndef Geometry_H
#define Geometry_H
#ifndef PI_180
#define PI_180 (3.14159265359 / 180.0) 
#endif
#include <math.h>
#include "vector3.h"
class Geometry {
public:
	/*
	Description :  Trasformation between spherical coordinates to cartesian coordinates
	Parameters : radius,polarAngle,azimuthAngle are the spherical coordinates input,
				 the output will be a vector position that identifies a point
				 in cartesian space. The frame considered
				 is a right handed frame as defined in OpenGL. The polar angle
				 is the angle between the radius and the y axis, while the azimuth angle
				 is the angle between the projection of the radius on the z-x plane and
				 the z-axis. Note : Input Angles are in degree
	*/
	static inline Vector3 sphericalToCartesian(GLdouble radius, GLdouble polarAngle, GLdouble azimuthAngle)
	{
		GLdouble z = radius * sin(polarAngle * PI_180) * cos(azimuthAngle * PI_180);
		GLdouble x = radius * sin(polarAngle * PI_180) * sin(azimuthAngle * PI_180);
		GLdouble y = radius * cos(polarAngle * PI_180);

		Vector3 point(x, y, z);
		return point;
	}

	/* Compute Triangle face normal */
	static inline Vector3 triangleNormal(Vector3 p1, Vector3 p2, Vector3 p3)
	{
		Vector3 v1;
		Vector3 v2;
		Vector3 vn;

		v1.x = p2.x - p1.x;
		v1.y = p2.y - p1.y;
		v1.z = p2.z - p1.z;

		v2.x = p3.x - p1.x;
		v2.y = p3.y - p1.y;
		v2.z = p3.z - p1.z;

		vn = v1 ^ v2;

		return vn.Normalize();
	}
};
#endif

