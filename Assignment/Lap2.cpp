#include "stdafx.h"
//#include "stdafx.h"
//
//#include <math.h>
//#include <iostream>
//#include "supportClass.h"
//#include "Mesh.h"
//
//using namespace std;
//
//int		screenWidth = 800;
//int		screenHeight= 600;
//
//Mesh	tetrahedron;
//Mesh	cube;
//Mesh	cuboid;
//Mesh	hinhtru;
//Mesh	hinhcau;
//Mesh	hinhovan;
//Mesh	hinhbannguyet;
//Mesh	bienthehinhtru;
//
//int		nChoice = 1;
//
//void drawAxis()
//{
//	glColor3f(0, 0, 1);
//	glBegin(GL_LINES);
//		glVertex3f(0, 0, 0);
//		glVertex3f(4, 0, 0);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(-4, 0, 0);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(0, 4, 0);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(0, -4, 0);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(0, 0, 4);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(0, 0, -4);
//	glEnd();
//}
//void myDisplay()
//{
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
//	glViewport(0, 0, screenWidth/2, screenHeight);   // x,y,w,h
//	
//	drawAxis();
//
//	glColor3f(0, 0, 0);
//	if(nChoice == 1)
//		tetrahedron.DrawWireframe();
//	else if(nChoice == 2)
//		cube.DrawWireframe();
//	else if(nChoice ==3)
//		cuboid.DrawWireframe();
//	else if(nChoice==4)
//		hinhtru.DrawWireframe();
//	else if(nChoice==5)
//		bienthehinhtru.DrawWireframe();
//	else if (nChoice==6)
//		hinhovan.DrawWireframe();
//	else if (nChoice==7)
//		hinhbannguyet.DrawWireframe();
//	else if (nChoice==8)
//		hinhcau.DrawWireframe();
//
//
//	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);
//
//	drawAxis();
//	if(nChoice == 1)
//		tetrahedron.DrawColor();
//	else if(nChoice == 2)
//		cube.DrawColor();
//	else if(nChoice ==3)
//		cuboid.DrawColor();
//	else if(nChoice==4)
//		hinhtru.DrawColor();
//	else if(nChoice==5)
//		bienthehinhtru.DrawColor();
//	else if (nChoice==6)
//		hinhovan.DrawColor();
//	else if (nChoice==7)
//		hinhbannguyet.DrawColor();
//	else if (nChoice==8)
//		hinhcau.DrawColor();
//
//	glFlush();
//    glutSwapBuffers();
//}
//
//void myInit()
//{
//	float	fHalfSize = 4;
//
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	glFrontFace(GL_CCW);
//	glEnable(GL_DEPTH_TEST);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	cout << "1. Tetrahedron" << endl;
//	cout << "2. Cube" << endl;
//	cout << "3. Cuboid" << endl;
//	cout <<	"4. HinhTru" <<endl;
//	cout <<	"5. BienTheHinhTru" <<endl;
//	cout<<	"6. HinhOvan" <<endl;
//	cout <<	"7. HinhBanNguyet"<<endl;
//	cout <<	"8. HinhCau"<<endl;
//	cout << "Input the choice: " << endl;
//	
//	cin  >> nChoice;
//
//	glutInit(&argc, (char**)argv); //initialize the tool kit
//	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
//	glutInitWindowSize(screenWidth, screenHeight); //set window size
//	glutInitWindowPosition(100, 100); // set window position on screen
//	glutCreateWindow("Lab 2"); // open the screen window
//
//	tetrahedron.CreateTetrahedron();
//	cube.CreateCube(1);
//	cuboid.CreateCuboid(1,2,1);  
//	hinhtru.CreateHinhTru(2,4);	
//	hinhcau.CreateHinhCau(3,9,18);
//	hinhovan.CreateHinhOvan(3,1,1,3,10);
//	bienthehinhtru.CreateBienTheHinhTru(2,1,1,0.2,0.5,20);
//	//hinhbannguyet.CreateHinhBanNguyet(2,1,1,2,6);
//
//	myInit();
//    glutDisplayFunc(myDisplay);
//	  
//	glutMainLoop();
//	return 0;
//}
//
