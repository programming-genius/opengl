/* 3D OpenGL Computer Graphics Lectures by Alessandro Zoia - 2017

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

#include "Pawn.h"
#ifndef PLANE_H
#define PLANE_H
class Plane : public virtual Pawn {

	void draw();
public:
	void setSize(GLint width, GLint height);
private:
	GLint width;
	GLint height;
	void setVertexCoordinates(Vector3& p1, Vector3& p2, Vector3& p3, Vector3& p4, int& i, int& j);
	void setFaceNormal(Vector3& p1, Vector3& p2, Vector3& p3);
	void addVertexes(Vector3& p1, Vector3& p2, Vector3& p3, Vector3& p4);
};
#endif