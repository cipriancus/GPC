#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "gl\glut.h"
using namespace std;

#define SIZE 500
#define M 0.5 //margin

unsigned char prevKey;

class GrilaCarteziana {
	int gridSize = 10;
public: 
	void setGridSize(int value) {
		gridSize = value/2;
	}
	void writePixel(int x, int y)
	{
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float ratio = float(width) / float(height);
		glColor3f(0.5, 0.5, 0.5);
		glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
		if (ratio < 1) {
			for (int i = 0; i <= 360; i += 5)
				glVertex2f((x*(2 - 2 * M) + sin(i)*0.3) / (gridSize + M), ((y*(2 - 2 * M) + cos(i)*0.3) / (gridSize + M))*ratio);
		}
		else {
			ratio = float(height) / float(width);
			for (int i = 0; i <= 360; i += 5)
				glVertex2f((x*(2 - 2 * M) + sin(i)*0.3) / (gridSize + M)*ratio, ((y*(2 - 2 * M) + cos(i)*0.3) / (gridSize + M)));
		}
		glEnd();
	}

	void pixelLine(int x, int y, int t, int d)
	{
		t /= 2;
		if (d == 0)
			for (int i = -t; i <= t; i++) 
				if (x+i <= gridSize && x+i >= -gridSize && y <= gridSize && y >= -gridSize)
					writePixel(x + i, y);
		for (int i = -t; i <= t; i++) 
			if (x <= gridSize && x >= -gridSize && y+i <= gridSize && y+i >= -gridSize)
				writePixel(x, y + i);
	}

	void AfisareSegmentDreapta3(int x1, int y1, int x2, int y2, unsigned int thickness = 0)
	{
		int dx = x2 - x1, x = x1, y = y1, dy = y2 - y1;
		if (y1 < y2) {
			if (x1 < x2) {
				int d = 2 * dy - dx, dE = 2 * dy, dNE = 2 * (dy - dx);
					pixelLine(x, y, thickness, 1);
				while (x < x2) {
					if (d <= 0) { d += dE; x++; }
					else { d += dNE; x++; y++; }
						pixelLine(x, y, thickness, 1);
				}
			}
			else {
				int dx = x1 - x2, d = 2 * dy - dx, dE = 2 * dy, dNE = 2 * (dy - dx);
					pixelLine(x, y, thickness, 1);
				while (x > x2) {
					if (d <= 0) { d += dE; x--; }
					else { d += dNE; x--; y++; }
						pixelLine(x, y, thickness, 1);
				}
			}
		}
		else {
			if (x1 < x2) {
				int dy = y1 - y2, d = 2 * dy - dx, dE = 2 * dy, dNE = 2 * (dy - dx);
				pixelLine(x, y, thickness, 1);
				while (x < x2) {
					if (d <= 0) { d += dE; x++; }
					else { d += dNE; x++; y--; }
						pixelLine(x, y, thickness, 1);
				}
			}
			else {
				int dx = x1 - x2, dy = y1 - y2, d = 2 * dy - dx, dE = 2 * dy, dNE = 2 * (dy - dx);
					pixelLine(x, y, thickness, 1);
				while (x > x2) {
					if (d <= 0) { d += dE; x--; }
					else { d += dNE; x--; y--; }
						pixelLine(x, y, thickness, 1);
				}
			}
		}
	}

	void DisplayGrid()
	{
		glLineWidth(1.0);
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float ratio = float(width) / float(height);
		float i;
		glColor3f(0.0, 0.0, 0.0);
		if (ratio < 1) {
			for (i = -gridSize; i <= gridSize; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((gridSize) / (gridSize + M), (float)(i*ratio / (gridSize + M)));
				glVertex2f((-gridSize) / (gridSize + M), (float)(i*ratio / (gridSize + M)));
				glEnd();
			}

			for (i = -gridSize; i <= gridSize; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((float)(i / (gridSize + M)), (-gridSize)*ratio / (gridSize + M));
				glVertex2f((float)(i / (gridSize + M)), (gridSize)*ratio / (gridSize + M));
				glEnd();
			}
		}
		else {
			ratio = float(height) / float(width);

			for (i = -gridSize; i <= gridSize; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((gridSize)*ratio / (gridSize + M), (float)(i / (gridSize + M)));
				glVertex2f((-gridSize)*ratio / (gridSize + M), (float)(i / (gridSize + M)));
				glEnd();
			}

			for (i = -gridSize; i <= gridSize; i++)
			{
				glBegin(GL_LINES);
				glVertex2f((float)(i*ratio / (gridSize + M)), (-gridSize) / (gridSize + M));
				glVertex2f((float)(i*ratio / (gridSize + M)), (gridSize) / (gridSize + M));
				glEnd();
			}
		}
	}

	void DrawLine(int x1, int y1, int x2, int y2, int w)
	{
		x1 -= gridSize; x2 -= gridSize; y1 -= gridSize; y2 -= gridSize;
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		float ratio = float(width) / float(height);

		glLineWidth(3.0);

		glColor3f(1.0, 0.0, 0.0);
		if (ratio < 1) {
			glBegin(GL_LINES);
			glVertex2f(x1 / (gridSize + M), y1*ratio / (gridSize + M));
			glVertex2f(x2 / (gridSize + M), y2* ratio / (gridSize + M));
			glEnd();
		}
		else {
			ratio = float(height) / float(width);
			glBegin(GL_LINES);
			glVertex2f(x1 / (gridSize + M)*ratio, y1 / (gridSize + M));
			glVertex2f(x2 / (gridSize + M)*ratio, y2 / (gridSize + M));
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
	int n = 20;
	glClear(GL_COLOR_BUFFER_BIT);
	switch (prevKey)
	{
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		grilaCarteziana.setGridSize(n);
		grilaCarteziana.DisplayGrid();
		grilaCarteziana.DrawLine(0, n, n, 3*n/4, 3);
		grilaCarteziana.DrawLine(0, 0, n, n / 2-1, 1);
		grilaCarteziana.DrawLine(n, n, 0, n / 2, 1);
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
