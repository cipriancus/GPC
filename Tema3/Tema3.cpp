#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <list>
#include "glut.h"
using namespace std;
unsigned char prevKey;

#define nrLinii 10
#define nrColoane 10

class Punct
{
	private:
		int X,Y;
	public:
		Punct(int x, int y)
		{
			this->X = x;
			this->Y = y;
		}

		int getX() { return this->X;}
		int getY(){ return this->Y;}

		void setX(int x) { this->X = x;}
		void setY(int y) { this->Y = y;}
};

list<Punct*> M; //lista de puncte
class Dreapta
{
	private:
		int fromX, fromY, toX, toY;
		float m,n;
		int dX, dY, a, b, c;
	public:
		Dreapta(int fromX, int fromY, int toX, int toY)
		{
			this->fromX = fromX;
			this->fromY = fromY;
			this->toX = toX;
			this->toY = toY;
			dX = abs(toX - fromX);
			dY = abs(toY - fromY);
			a = dY;
			b = -dX;
			c = dX*fromY - dY*fromX;
			m = dY/(dX+0.0f);
			n = fromY - (dY*fromX)/(dX+0.0f);
		}

		float getM() const { return m; }
		float getN() const { return n; }
		int getDX() const { return dX; }
		int getDY() const { return dY; }
		int getA() const { return a; }
		int getB() const { return b; }
		int getC() const { return c; }

		void setM(float val) { m = val; }
		void setN(float val) { n = val; }
		void setDX(int val) { dX = val; }
		void setDY(int val) { dY = val; }
		void setA(int val) { a = val; }
		void setB(int val) { b = val; }
		void setC(int val) { c = val; }
};

class GrilaCarteziana{
	private:
		int mLinii, mColoane, mDeltaPixeliPerLinie, mDeltaPixeliPerColoana;
	public:
		GrilaCarteziana()
		{
			this->mLinii = nrLinii;
			this->mColoane = nrColoane;
			this->initializari();
		}

		GrilaCarteziana(int pLinii, int pColoane)
		{
			this->mLinii = pLinii;
			this->mColoane = pColoane;
			this->initializari();
		}

		void initializari()
		{
			mDeltaPixeliPerLinie = 600/(mLinii+1);
			mDeltaPixeliPerColoana = 600/(mColoane+1);
		}

		void writePixel(int atX, int atY)
		{
			float x,y;
			float PI = 4*atan(1.0);
			float radius = 10;
			float delta_theta = 0.01;
			glColor3f(0.76,0.76,0.76);
			glBegin( GL_POLYGON );
			{
				for( float angle = 0; angle < 2*PI; angle += delta_theta )
				glVertex2f( atX+radius*cos(angle),atY+radius*sin(angle));
			}
			glEnd();
		}

		void writePixels(list<Punct*> m)
		{
			list<Punct*>::const_iterator iterator;
			for(iterator = m.begin(); iterator!=m.end(); iterator++)
				this->writePixel((*iterator)->getX()*mDeltaPixeliPerLinie, (*iterator)->getY()* mDeltaPixeliPerColoana);
		}

		void writeRedLine(int fromX, int fromY, int toX, int toY)
		{
			glColor3f(1,0,0);
			glBegin(GL_LINES);
			{
				glVertex2i(fromX*mDeltaPixeliPerLinie, fromY*mDeltaPixeliPerColoana);
				glVertex2i(toX*mDeltaPixeliPerLinie, toY*mDeltaPixeliPerColoana);
			}
			glEnd();
		}

		void draw()
		{
			glColor3f(0,0,0);
			for(int i = -mLinii-1 ; i<=mLinii; i++)
			{
				glBegin(GL_LINES);
				{
					glVertex2i(-600*mDeltaPixeliPerLinie,i*mDeltaPixeliPerLinie);
					glVertex2i(600+mDeltaPixeliPerLinie,i*mDeltaPixeliPerLinie);
				}
				glEnd();
			}
			for(int i = -mLinii-1 ; i<=mLinii; i++)
			{
				glBegin(GL_LINES);
				{
					glVertex2i(i*mDeltaPixeliPerColoana,-600+mDeltaPixeliPerColoana);
					glVertex2i(i*mDeltaPixeliPerColoana, 600+mDeltaPixeliPerColoana);
				}
				glEnd();
			}
		}
};

	void AfisareSegmentDreapta3 (int fromX, int fromY, int toX, int toY, bool bolded)
	{
		GrilaCarteziana* grila = new GrilaCarteziana();
		grila->draw();
		Dreapta* dreapta = new Dreapta(fromX, fromY, toX, toY);
		int d = 2*dreapta->getDY()-dreapta->getDX(), dE = 2*dreapta->getDY(), dNE = 2*(dreapta->getDY()-dreapta->getDX()), x = fromX, y = fromY;
		M.push_back(new Punct(0,0));

		grila->writeRedLine(fromX, fromY, toX, toY);
		grila->writePixels(M);
		//free memory
		while(M.size()>0)
		{
			Punct* p = M.back();
			M.pop_back();
			delete(p);
		}
		delete(dreapta);
		delete(grila);
	}

	void Init(void) 
	{
		glClearColor(1.0,1.0,1.0,1.0);
		glLineWidth(1);
		// glPointSize(4);
		glPolygonMode(GL_FRONT, GL_FILL);
		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-600*0.9f, 600*0.9f,-600*0.9f, 600*0.9f);
	}

	void Display(void) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		switch(prevKey) 
		{
			case '1':
			{
				AfisareSegmentDreapta3(-nrLinii,nrColoane,nrLinii,nrColoane/4, true);
				AfisareSegmentDreapta3(-nrLinii,-nrColoane,nrLinii,-nrColoane/4, true);
			}
				break;
			default:
				break;
		}
		glFlush();
	}

	void Reshape(int w, int h) 
	{
		glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	}

	void KeyboardFunc(unsigned char key, int x, int y)
	{
		prevKey = key;
		if (key == 27) // escape
			exit(0);
		glutPostRedisplay();
	}

	void MouseFunc(int button, int state, int x, int y) 
	{

	}

	int main(int argc, char** argv) 
	{
		glutInit(&argc, argv);
		glutInitWindowSize(600, 600);
		glutInitWindowPosition(100, 100);
		glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
		glutCreateWindow (argv[0]);
		Init();
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(KeyboardFunc);
		glutMouseFunc(MouseFunc);
		glutDisplayFunc(Display);
		glutMainLoop();
		return 0;
	}