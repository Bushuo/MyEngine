#include <GL\glew.h>
#include "MyGlWindow.h"
#include <cassert>
#include <Qt\qdebug.h>
#include <QtGui\QKeyEvent>
#include <Math\Vector2D.h>
#include <Math\Matrix2D.h>
#include <Timing\Clock.h>

using Math::Vector2D;
using Math::Matrix2D;
using Timing::Clock;
// unnamed namespace make it private to the file
namespace
{
	Vector2D verts[] =
	{
		//sqrt(0.02)
		Vector2D(+0.0f, +0.14142135623f),
		Vector2D(-0.1f, -0.1f),
		Vector2D(+0.1f, -0.1f),
	};

	// devide the total amount of bytes by the amount of bytes of the first entry = number of entries
	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector2D shipPosition;
	Vector2D shipVelocity;
	float shipOrientation = 0.0f;
	Clock clock;
}

void MyGlWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), NULL, GL_DYNAMIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	myTimer.start(0);

}

bool MyGlWindow::initialize()
{
	return clock.initialize();
}

void MyGlWindow::myUpdate()
{
	clock.newFrame();
	rotateShip();
	updateVelocity();
	shipPosition +=	shipVelocity * clock.timeElapsedLastFrame();
	repaint();
}

void MyGlWindow::paintGL()
{
	int minSize = min(width(), height());
	Vector2D viewportLocation;
	viewportLocation.x = width() / 2 - minSize / 2;
	viewportLocation.y = height() / 2 - minSize / 2;
	glViewport(viewportLocation.x, viewportLocation.y, minSize, minSize);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	Vector2D transformedVerts[NUM_VERTS];
	Matrix2D op = Matrix2D::rotate(shipOrientation);
	for (unsigned int i = 0; i < NUM_VERTS; i++)
		transformedVerts[i] = shipPosition + op * verts[i] ;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool MyGlWindow::shutdown()
{
	return clock.shutdown();
}

void MyGlWindow::rotateShip()
{
	const float ANGULAR_MOVEMENT = 2.f * clock.timeElapsedLastFrame();
	if (GetAsyncKeyState(VK_RIGHT))
		shipOrientation -= ANGULAR_MOVEMENT;
	if (GetAsyncKeyState(VK_LEFT))
		shipOrientation += ANGULAR_MOVEMENT;
	
}

void MyGlWindow::updateVelocity()
{
	const float ACCELERATION = 0.3f * clock.timeElapsedLastFrame();
	Vector2D directionToAccelerate(-sin(shipOrientation), cos(shipOrientation));

	//other way to implement
	/*Vector2D straightUpForShip(0, 1);
	Matrix2D op = Matrix2D::rotate(shipOrientation);
	Vector2D directionToAccelerate = op * straightUpForShip;*/

	if (GetAsyncKeyState(VK_UP))
		shipVelocity += directionToAccelerate * ACCELERATION;
}

