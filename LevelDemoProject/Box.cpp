#include "Box.h"

void Box::setSize(GLdouble width, GLdouble height, GLdouble lenght)
{
	this->width = width;
	this->height = height;
	this->lenght = lenght;
}

void Box::draw()
{
	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;

	// Front
	glBegin(GL_QUADS);
	setVertexCoordinates(p1, -1, 1, 1);
	setVertexCoordinates(p2, -1, -1, 1);
	setVertexCoordinates(p3, 1, -1, 1);
	setVertexCoordinates(p4, 1, 1, 1);
	setFaceNormal(p1, p2, p3);
	addVertexes(p1, p2, p3, p4);
	glEnd();

	// Right
	glBegin(GL_QUADS);
	setVertexCoordinates(p1, -1, 1, -1);
	setVertexCoordinates(p2, -1, -1, -1);
	setVertexCoordinates(p3, -1, -1, 1);
	setVertexCoordinates(p4, -1, 1, 1);
	setFaceNormal(p1, p2, p3);
	addVertexes(p1, p2, p3, p4);
	glEnd();

	// Back
	glBegin(GL_QUADS);
	setVertexCoordinates(p1, -1, 1, -1);
	setVertexCoordinates(p2, -1, -1, -1);
	setVertexCoordinates(p3, 1, -1, -1);
	setVertexCoordinates(p4, 1, 1, -1);
	setFaceNormal(p1, p2, p3);
	addVertexes(p1, p2, p3, p4);
	glEnd();

	// Left
	glBegin(GL_QUADS);
	setVertexCoordinates(p1, 1, 1, 1);
	setVertexCoordinates(p2, 1, -1, 1);
	setVertexCoordinates(p3, 1, -1, -1);
	setVertexCoordinates(p4, 1, 1, -1);
	setFaceNormal(p1, p2, p3);
	addVertexes(p1, p2, p3, p4);
	glEnd();

	// Top
	glBegin(GL_QUADS);
	setVertexCoordinates(p1, -1, 1, -1);
	setVertexCoordinates(p2, -1, 1, 1);
	setVertexCoordinates(p3, 1, 1, 1);
	setVertexCoordinates(p4, 1, 1, -1);
	setFaceNormal(p1, p2, p3);
	addVertexes(p1, p2, p3, p4);
	glEnd();

	// Bottom
	glBegin(GL_QUADS);
	setVertexCoordinates(p1, -1, -1, 1);
	setVertexCoordinates(p2, -1, -1, -1);
	setVertexCoordinates(p3, 1, -1, -1);
	setVertexCoordinates(p4, 1, -1, 1);
	setFaceNormal(p1, p2, p3);
	addVertexes(p1, p2, p3, p4);
	glEnd();
}

void Box::setVertexCoordinates(Vector3& p, int xSign, int ySign, int zSign)
{
	p.x = xSign * width / 2;
	p.y = ySign * height / 2;
	p.z = zSign * lenght / 2;
}

void Box::addVertexes(Vector3& p1, Vector3& p2, Vector3& p3, Vector3& p4)
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

void Box::setFaceNormal(Vector3& p1, Vector3& p2, Vector3& p3)
{
	Vector3 normal = Geometry::triangleNormal(p1, p2, p3);
	glNormal3d(normal.x, normal.y, normal.z);
}