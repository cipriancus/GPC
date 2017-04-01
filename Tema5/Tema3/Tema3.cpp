#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "gl\glut.h"
using namespace std;

//#define n 10
#define SIZE 400
#define E 0.5

unsigned char prevKey;

class GrilaCarteziana {
	int n = 5;
public: 
	void setn(int value) {
		n = value;
	}
	void writePixel(int x, int y)
	{
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float ratio = float(width) / float(height);
		glColor3f(0.76, 0.76, 0.76);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		if (ratio < 1) {
			for (int i = 0; i <= 360; i += 5)
				glVertex2f((x*(2 - 2 * E) + sin(i)*0.25) / (n + E), ((y*(2 - 2 * E) + cos(i)*0.25) / (n + E))*ratio);
		}
		else {
			ratio = float(height) / float(width);
			for (int i = 0; i <= 360; i += 5)
				glVertex2f((x*(2 - 2 * E) + sin(i)*0.25) / (n + E)*ratio, ((y*(2 - 2 * E) + cos(i)*0.25) / (n + E)));
		}
		glEnd();
	}

	void Pixels(int x, int y, int t, int d)
	{
		t /= 2;
		if (d == 0)
			for (int i = -t; i <= t; i++) writePixel(x + i, y);
		for (int i = -t; i <= t; i++) writePixel(x, y + i);
	}

	void AfisareSegmentDreapta3(int fromX, int fromY, int toX, int toY, unsigned int bolded = 0)
	{
		int dx = toX - fromX, x = fromX, y = fromY, dy = toY - fromY;
		if (fromY < toY) {
			int d = 2 * dy - dx, dE = 2 * dy, dNE = 2 * (dy - dx);
			Pixels(x, y, bolded, 1);
			while (x < toX) {
				if (d <= 0) { d += dE; x++; }
				else { d += dNE; x++; y++; }
				Pixels(x, y, bolded, 1);
			}
		}
		else {
			if (toY < fromY) {
				int dy = fromY - toY, d = 2 * dy - dx, dE = 2 * dy, dNE = 2 * (dy - dx);
				Pixels(x, y, bolded, 1);
				while (x < toX) {
					if (d <= 0) { d += dE; x++; }
					else { d += dNE; x++; y--; }
					Pixels(x, y, bolded, 1);
				}
			}
		}
	}

	void DisplayGrid()
	{
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float ratio = float(width) / float(height);
		float i;
		glColor3f(0.0, 0.0, 0.0);
		if (ratio < 1) {
			for (i = -n; i <= n; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((n) / (n + E), (float)(i*ratio / (n + E)));
				glVertex2f((-n) / (n + E), (float)(i*ratio / (n + E)));
				glEnd();
			}

			for (i = -n; i <= n; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((float)(i / (n + E)), (-n)*ratio / (n + E));
				glVertex2f((float)(i / (n + E)), (n)*ratio / (n + E));
				glEnd();
			}
		}
		else {
			ratio = float(height) / float(width);

			for (i = -n; i <= n; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((n)*ratio / (n + E), (float)(i / (n + E)));
				glVertex2f((-n)*ratio / (n + E), (float)(i / (n + E)));
				glEnd();
			}

			for (i = -n; i <= n; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((float)(i*ratio / (n + E)), (-n) / (n + E));
				glVertex2f((float)(i*ratio / (n + E)), (n) / (n + E));
				glEnd();
			}
		}
	}

	void DrawLine(int x1, int y1, int x2, int y2, int w)
	{
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float ratio = float(width) / float(height);

		glLineWidth(3.0);

		glColor3f(1.0, 0.0, 0.0);
		if (ratio < 1) {
			glBegin(GL_LINES);
			glVertex2f(x1 / (n + E), y1*ratio / (n + E));
			glVertex2f(x2 / (n + E), y2* ratio / (n + E));
			glEnd();
		}
		else {
			ratio = float(height) / float(width);
			glBegin(GL_LINES);
			glVertex2f(x1 / (n + E)*ratio, y1 / (n + E));
			glVertex2f(x2 / (n + E)*ratio, y2 / (n + E));
			glEnd();
		}

		AfisareSegmentDreapta3(x1, y1, x2, y2, w);
	}
};

void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(1);
	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void)
{
	GrilaCarteziana grilaCarteziana;
	int n = 10;
	glClear(GL_COLOR_BUFFER_BIT);
	switch (prevKey)
	{
	case '1':
		grilaCarteziana.setn(n);
		grilaCarteziana.DisplayGrid();
		grilaCarteziana.DrawLine(n, 3, -n, n, 3);
		grilaCarteziana.DrawLine(-n, -n, n, -1, 1);
		break;
	default:
		break;
	}
	glFlush();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	prevKey = key;
	if (key == 27)
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(SIZE, SIZE);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow(argv[0]);
	Init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}
