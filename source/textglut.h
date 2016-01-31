#include <string>
#include <glut.h>
using namespace std;



//Text function
void text(string s, float x, float y)
{
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 500, 0.0, 500);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0); // Green
	glRasterPos2i(x, y);
	void * font = GLUT_BITMAP_9_BY_15;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}