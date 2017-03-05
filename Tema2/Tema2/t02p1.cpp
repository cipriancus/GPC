
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display3() {
	// functia cu distante
	double xmax = 100;
	double ymax = 1.01;
	double ratia = 0.5;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		if (x == 0)
			y1 = 1 / ymax;
		else
			y1 = ((fabs(floor(x + ratia) - x)) / x) / ymax;
		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display4() {
	// melcul lui Pascal
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double a = 0.3;
	double b = 0.2;

	double xmax=a - b - 1;
	double xmin=a + b + 1;
	double ymin=0;
	double ymax=0;

	for (double t = -pi + ratia; t < pi; t += ratia) {
		double x, y;

		x = 2 * (a*cos(b) + b)*cos(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = 2 * (a*cos(t) + b)*sin(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;

	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	ymax = ymax*1.6;
	xmax = xmax*1.2;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi + ratia; t < pi; t += ratia) {
		double x =( 2 * (a*cos(t) + b)*cos(t))/xmax;
		double y = (2 * (a*cos(t) + b)*sin(t))/ymax;
		glVertex2d(x, y);
	}
	glEnd();
}

void Display5() {
	// trisectoarea lui Longchamps
	double scale = 1.35;
	double ymax = 0;
	double xmin = 0;
	double a = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t, x, y, x1, y1;

	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t != pi / 6, t != -pi / 6) {
			x = a / (4 * cos(t)*cos(t) - 3);
			y = a*tan(t) / (4 * cos(t)*cos(t) - 3);
		}
		if (x < 0 && y>0) {
			xmin = (xmin > x) ? x : xmin;
			ymax = (ymax < y) ? y : ymax;
		}
	}
	xmin = xmin*1.01;
	ymax = ymax*1.01;

	//triangles
	bool ok = 0;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_TRIANGLES);
	for (t = -pi / 2 + (2 / 5)*ratia; t < pi / 2; t += ratia / 5) {
		x1 = x;
		y1 = y;
		if (t != pi / 6, t != -pi / 6) {
			x = a / (4 * cos(t)*cos(t) - 3) / -xmin;
			y = a*tan(t) / (4 * cos(t)*cos(t) - 3) / ymax;
		}
		if (ok && x < 0 && y>0) {
			glVertex3f(x, y, 0);
			glVertex3f(x1, y1, 0);
			glVertex3f(-0.99, 0.99, 0);
			ok = 0;
		}
		else
			ok = 1;
	}
	glEnd();


	glColor3f(0.1, 0.1, 1); // albastru
	glBegin(GL_LINE_LOOP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t != pi / 6, t != -pi / 6) {
			x = a / (4 * cos(t)*cos(t) - 3) / -xmin;
			y = a*tan(t) / (4 * cos(t)*cos(t) - 3) / ymax;
		}
		if (x < 0 && y>0) {
			glVertex2f(x, y);
		}
	}
	glVertex2f(-0.99, 0.99);
	glEnd();
}

void Display6() {
	// cicloida
	double pi = 4 * atan(1.0);

	double interval_inf=-3*pi;//cate spirale punem pe cerc
	double interval_sup=3*pi;

	double ratia = 0.05;
	double a = 0.1;
	double b = 0.2;

	double xmax = a - b - 1;
	double xmin = a + b + 1;
	double ymin = 0;
	double ymax = 0;

	for (double t = interval_inf + ratia; t < interval_sup; t += ratia) {
		double x, y;

		x = a*t - b*sin(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;

		y = a - b*cos(t);
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;

	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	ymax *= 3;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = interval_inf + ratia; t < interval_sup; t += ratia) {
		double x = (a*t - b*sin(t)) / xmax;
		double y = (a - b*cos(t)) / ymax;
		glVertex2d(x, y);
	}
	glEnd();
}

void Display7() {
	// epicicloida
	double r = 0.3;
	double R = 0.1;
	double pi = 4 * atan(1.0);
	double xmax = 2 * pi;
	double ratia = 0.05;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t < xmax; t += ratia) {
		double x, y;
		x = (R + r)*cos(r*t / R) - r*cos(t + r*t / R);
		y = (R + r)*sin(r*t / R) - r*sin(t + r*t / R);

		glVertex2f(x, y);
	}
	glEnd();
}

void Display8() {
	// hipocicloida
	double r = 0.3;
	double R = 0.1;
	double pi = 4 * atan(1.0);
	double xmax = 2 * pi;
	double ratia = 0.05;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t < xmax; t += ratia) {
		double x, y;
		x = (R - r)*cos(r*t / R) - r*cos(t - r*t / R);
		y = (R - r)*sin(r*t / R) - r*sin(t - r*t / R);

		glVertex2f(x, y);
	}
	glEnd();
}

void Display9() {
	// lemniscata lui Bernoulli
	double r = 0.3;
	double R = 0.1;
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double xmax = 2 * pi;
	double ratia = 0.005;
	double x, y;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = pi / 4 - ratia; t > -pi / 4; t -= ratia) {

		r = a*(sqrt(2 * cos(2 * t)));
		x = r*cos(t);
		y = r*sin(t);

		glVertex2f(x, y);
	}
	for (double t = -pi / 4 + ratia; t < pi / 4; t += ratia) {

		r = -a*(sqrt(2 * cos(2 * t)));
		x = r*cos(t);
		y = r*sin(t);

		glVertex2f(x, y);
	}
	glEnd();
}

void Display10() {
	double a = 0.02;
	double ratia = 0.05;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0 + ratia; t < 5; t += ratia) {
		double r = a*exp(1 + t);
		double x = r*cos(t);
		double y = r*sin(t);
		glVertex2f(x, y);
	}
	glEnd();
}

void Init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPolygonMode(GL_FRONT, GL_FILL);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display10();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

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
