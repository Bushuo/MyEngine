#include "GL\glew.h"
#include "MyGlWindow.h"
#include <cassert>
#include <Math\Vector2D.h>
#include <Qt\qdebug.h>
#include <Timing\Clock.h>
using Math::Vector2D;
using Timing::Clock;
// unnamed namespace make it private to the file
namespace
{
	Vector2D verts[] =
	{
		Vector2D(+0.0f, +0.1f),
		Vector2D(-0.1f, -0.1f),
		Vector2D(+0.1f, -0.1f),
	};

	// devide the total amount of bytes by the amount of bytes of the first entry = number of entries
	const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	Vector2D shipPosition(0.0f, 0.0f);
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
int debugInt = 1;
void MyGlWindow::myUpdate()
{
	clock.newFrame();
	/*if (debugInt++ % 20 == 0)
		for (int i = 0; i < 500; i++)
			qDebug() << "Hello";*/
	Vector2D velocity(0.5f, 0.5f);
	shipPosition = shipPosition + velocity * clock.timeElapsedLastFrame();
	repaint();
}

void MyGlWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	Vector2D translatedVerts[NUM_VERTS];
	for (unsigned int i = 0; i < NUM_VERTS; i++)
		translatedVerts[i] = verts[i] + shipPosition;

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(translatedVerts), translatedVerts);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool MyGlWindow::initialize()
{
	return clock.initialize();
}

bool MyGlWindow::shutdown()
{
	return clock.shutdown();
}