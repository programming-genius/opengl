#include "Plane.h"

void Plane::setSize(GLint width, GLint height)
{
	this->width = width;
	this->height = height;
}

void Plane::draw()
{
	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;

	for (int i = -width; i < width; i += 1)
	{
		for (int j = -height; j < height; j += 1)
		{
			glBegin(GL_QUADS);
			setVertexCoordinates(p1, p2, p3, p4, i, j);
			setFaceNormal(p1, p2, p3);
			addVertexes(p1, p2, p3, p4);
			glEnd();
		}
	}
}

void Plane::setVertexCoordinates(Vector3& p1, Vector3& p2, Vector3& p3, Vector3& p4, int& i, int& j)
{
	p1.x = j;
	p1.y = 0;
	p1.z = i + 1;

	p2.x = j + 1;
	p2.y = 0;
	p2.z = i + 1;

	p3.x = j + 1;
	p3.y = 0;
	p3.z = i;

	p4.x = j;
	p4.y = 0;
	p4.z = i;

}

void Plane::addVertexes(Vector3& p1, Vector3& p2, Vector3& p3, Vector3& p4)
{
	glTexCoord2d(0, 0);
	glVertex3d(p1.x, p1.y, p1.z);
	glTexCoord2d(1, 0);
	glVertex3d(p4.x, p4.y, p4.z);
	glTexCoord2d(1, 1);
	glVertex3d(p3.x, p3.y, p3.z);
	glTexCoord2d(0, 1);
	glVertex3d(p2.x, p2.y, p2.z);
}

void Plane::setFaceNormal(Vector3& p1, Vector3& p2, Vector3& p3)
{
	Vector3 normal = Geometry::triangleNormal(p1, p2, p3);
	glNormal3d(normal.x, normal.y, normal.z);
}