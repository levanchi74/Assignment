
#include "stdafx.h"

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

#define PI			3.1415926

// Camera
float camera_angle ;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
//float gocxoayY;

bool	b4View = false;

int		screenWidth = 600;
int		screenHeight= 600;

bool	bWireFrame = false;

float	deduoiRadius = 0.8;
float	deduoiHeight = 0.3;
float	deduoiRotateStep = 5;
int		deSlices =20;

float	detrenRadius = 0.7*deduoiRadius;
float	detrenHeight = 1.0;

float	xylanhRadius = 0.3;
float	xylanhHeight = 1.6;

float bandoLength = 8;
float bandoHeight = 0.2;
float bandoWidth = 3.5; 

float giadoLength = 0.35;
float giadoHeight =0.2;  // 
float giadoWidth =1;

float giadobnHeight = giadoLength;
float giadobnRadius1 =0.08;
float giadobnRadius2 = 0.15;
float giadobnWidth = 0.23;

float cclkHeight = 0.2;
float cclkRadius1 =0.12;
float cclkRadius2 =0.3;
float cclkLength = 1;

float rotorRadius = cclkLength + 0.3;
float rotorHeight = 0.4;

float ttRadius1 = giadobnRadius1;
float ttRadius2 =0.1 ;
float ttLength1 =  1.4;
float ttLength2 = 0.1;
float ttLength3 = 0.6;

float chotRadius1 = cclkRadius1-0.02;
//float chotRadius1 = 0.2;
float chotRadius2 =0.08 ;
float chotLength1 =  0.3;
float chotLength2 = 0.05;
float chotLength3 = 0;


float	cylinderRadius = 0.4;
float	cylinderHeight = 1.6;
float	cylinderRotateStep = 5;
float	cylinderTranslationStep = 0.05;
//float	cylinderOffset = detrenHeight-cylinderHeight/2;
float	cylinderOffset = 0;

Mesh	deduoi;
Mesh	detren;
Mesh	xylanh;
Mesh	bando;
Mesh	rotor;
Mesh	giado1;
Mesh	giado1bn;
Mesh	giado2;
Mesh	giado2bn;
Mesh	cclk;
Mesh	thanhtruot1;
Mesh	thanhtruot2;
Mesh	chot;


float Rnho =0.3;
float chieuX= -Rnho,chieuZ = 0; // khoi tao vi tri ban dau 
bool ct = false; 


void mySpecialKey(int theKey, int x, int y) {
	if (theKey == GLUT_KEY_RIGHT) {
		camera_angle -= 1;
		if (camera_angle < 0)
			camera_angle += 360;
	}
	else if (theKey == GLUT_KEY_LEFT) {
		camera_angle += 1;
		if (camera_angle > 360)
			camera_angle -= 360;
	}
	else if (theKey == GLUT_KEY_UP) {
		camera_height += 0.2;
	}
	else if (theKey == GLUT_KEY_DOWN) {
		camera_height -= 0.2;
	}
	glutPostRedisplay();
}
void FlagCartoon(int t){
		rotor.rotateY += 5;
		chieuX = -Rnho*  cos( rotor.rotateY*PI/180 );
		chieuZ = Rnho* sin(rotor.rotateY*PI/180);
			
		if(rotor.rotateY > 360)
			rotor.rotateY -=360;
	glutPostRedisplay();
	if (ct)
		glutTimerFunc(55, FlagCartoon, 0);
	
}
void myKeyboard(unsigned char key, int x, int y)
{

	float	fRInc;
	float	fAngle;
    switch(key)
    {
	case '1':
		deduoi.rotateY += deduoiRotateStep;
		if(deduoi.rotateY > 360)
			deduoi.rotateY -=360;
		break;
	case '2':	
		deduoi.rotateY -= deduoiRotateStep;
		if(deduoi.rotateY < 0)
			deduoi.rotateY +=360;
		break;
	case '3':
		xylanh.rotateY += cylinderRotateStep;
		if(xylanh.rotateY > 360)
			xylanh.rotateY -=360;
		break;
	case '4':	
		xylanh.rotateY -= cylinderRotateStep;
		if(xylanh.rotateY < 0)
			xylanh.rotateY +=360;
		break;
	case '5':
		cylinderOffset += cylinderTranslationStep;
		if(cylinderOffset > detrenHeight/2)
			cylinderOffset = detrenHeight/2;
		break;
	case '6':	
		cylinderOffset -= cylinderTranslationStep;
		if(cylinderOffset<0)
			cylinderOffset=0;
		break;
	case '7':
			
			rotor.rotateY += 5;
			chieuX = -Rnho*  cos( rotor.rotateY*PI/180 );
			chieuZ = Rnho* sin(rotor.rotateY*PI/180);
			
			if(rotor.rotateY > 360)
				rotor.rotateY -=360;


			break;
	case '8':
			rotor.rotateY -= 5;
			chieuX = -Rnho*  cos( rotor.rotateY*PI/180 );
			chieuZ = Rnho* sin(rotor.rotateY*PI/180);
			
			if(rotor.rotateY <0 )
				rotor.rotateY =360;
			
		break;
	case 'A':
	case 'a':
		ct = !ct;
		if (ct)
			glutTimerFunc(10, FlagCartoon, 0);
		
		

		break;
	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case '+':
		camera_dis +=0.5;
		break;
	case '-':
		camera_dis -= 0.5;		
		break;
	}

    glutPostRedisplay();
}

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);//x -> red
		glVertex3f(4, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);//y
		glVertex3f(0, 4, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);//z
		glVertex3f(0, 0, 4);
	glEnd();
}

void drawDeDuoi()
{
	glPushMatrix();

		glTranslated(0,0, 0);
		glRotatef(deduoi.rotateY, 0, 1, 0);

		if(bWireFrame)
			deduoi.DrawWireframe();
		else
			deduoi.DrawColor();

	glPopMatrix();
}

void drawDeTren()
{
	glPushMatrix();

		glTranslated(0,deduoiHeight, 0);
		glRotatef(deduoi.rotateY, 0, 1, 0);

		if(bWireFrame)
			detren.DrawWireframe();
		else
			detren.DrawColor();

	glPopMatrix();
}

void drawXylanh()
{
	glPushMatrix();

		glTranslated(0, deduoiHeight+cylinderOffset, 0);
		glRotatef(xylanh.rotateY+deduoi.rotateY , 0, 1, 0);

		if(bWireFrame)
			xylanh.DrawWireframe();
		else
			xylanh.DrawColor();

	glPopMatrix();
}

void drawBanDo()
{
	glPushMatrix();
		glTranslated(0, deduoiHeight + xylanhHeight+cylinderOffset, 0);
		glRotatef(deduoi.rotateY + xylanh.rotateY, 0, 1, 0);

		if(bWireFrame)
			bando.DrawWireframe();
		else
			bando.DrawColor();

	glPopMatrix();
}

void drawGiaDo1()
{
	glPushMatrix();
	glRotatef(deduoi.rotateY + xylanh.rotateY  , 0, 1, 0);
	glTranslated(rotorRadius+0.5,bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);
	

	if(bWireFrame)
		giado1.DrawWireframe();
	else
		giado1.DrawColor();

	glPopMatrix();
}

void drawGiaDo1BN(){
	glPushMatrix();
	glRotatef(deduoi.rotateY + xylanh.rotateY  , 0, 1, 0);
	glTranslated(rotorRadius+0.5, giadoHeight +bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);
	glRotatef(90  , 0, 1, 0);
	

	if(bWireFrame)
		giado1bn.DrawWireframe();
	else
		giado1bn.DrawColor();

	glPopMatrix();
}

void drawGiaDo2()
{
	glPushMatrix();
	glRotatef(deduoi.rotateY + xylanh.rotateY  , 0, 1, 0);
	glTranslated(-rotorRadius-0.5,bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);
	

	if(bWireFrame)
		giado2.DrawWireframe();
	else
		giado2.DrawColor();

	glPopMatrix();
}

void drawGiaDo2BN(){
	glPushMatrix();
	glRotatef(deduoi.rotateY + xylanh.rotateY  , 0, 1, 0);
	
	glTranslated(-rotorRadius-0.5, giadoHeight +bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);
	glRotatef(90  , 0, 1, 0);

	if(bWireFrame)
		giado2bn.DrawWireframe();
	else
		giado2bn.DrawColor();

	glPopMatrix();
}

void drawRotor()
{
	glPushMatrix();

		glTranslated(0,bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);
		glRotatef(deduoi.rotateY + xylanh.rotateY+rotor.rotateY , 0, 1, 0);
	

		if(bWireFrame)
			rotor.DrawWireframe();
		else
			rotor.DrawColor();

	glPopMatrix();
}

void drawCoCauLienKet()
{
	glPushMatrix();
	//	glTranslated(Rnho,0, 0);
		glRotatef(deduoi.rotateY + xylanh.rotateY , 0, 1, 0);
		glTranslated(chieuX,rotorHeight + bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);
		
		glRotatef(90  , 0, 1, 0);

		if(bWireFrame)
			cclk.DrawWireframe();
		else
			cclk.DrawColor();

	glPopMatrix();
}

void drawThanhTruot1(){
	glPushMatrix();
	
	glRotatef(deduoi.rotateY + xylanh.rotateY , 0, 1, 0);
	glTranslated(2.4+chieuX ,giadoHeight + giadobnWidth+ (giadobnRadius2 - giadobnRadius1) + bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);

	glRotatef(90 , 0, 0, 1);

	if(bWireFrame)
		thanhtruot1.DrawWireframe();
	else
		thanhtruot1.DrawColor();

	glPopMatrix();
}

void drawThanhTruot2(){
	glPushMatrix();

	glRotatef(deduoi.rotateY + xylanh.rotateY , 0, 1, 0);
	glTranslated(-2.4+chieuX,giadoHeight + giadobnWidth+ (giadobnRadius2 - giadobnRadius1) + bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, 0);

	glRotatef(-90, 0, 0, 1);

	if(bWireFrame)
		thanhtruot2.DrawWireframe();
	else
		thanhtruot2.DrawColor();

	glPopMatrix();
}

void drawChot(){
	
	glPushMatrix();
	

	glRotatef(deduoi.rotateY + xylanh.rotateY  , 0, 1, 0);
	glTranslated( chieuX,rotorHeight + bandoHeight+ deduoiHeight + xylanhHeight+cylinderOffset, chieuZ);


	if(bWireFrame)
		
		chot.DrawWireframe();
	else
		chot.DrawColor();

	glPopMatrix();
}

void drawSanNha(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex3f(-2, 0,-2);
		glVertex3f(-2, 0,2);
		glVertex3f(2, 0,2);
		glVertex3f(2, 0,-2);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(0, 0,-2);
		glVertex3f(0, 0,2);
		glVertex3f(2, 0,2);
		glVertex3f(2, 0,-2);
	glEnd();
	glFlush();


}

void mySetupCameraVolume(int nType)
{
	if (nType == 4)
	{
		glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
		glLoadIdentity();						// reset projection matrix

												// calculate aspect ratio of window
		gluPerspective(60.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1.0f, 1000.0f);
	}
	else
	{
		glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
		glLoadIdentity();						// reset projection matrix
		glOrtho(-5, 5, -5, 5, -1000, 1000);
	}

}
void changeCameraPos()
{
	camera_Y = camera_height;
	camera_X = camera_dis * cos(camera_angle);
	camera_Z = camera_dis * sin(camera_angle);
}
void DisplayOneView(int nType, int left, int right, int top, int bottom)
{
	mySetupCameraVolume(nType);
	glViewport(left, top, right - left, bottom - top);

	changeCameraPos();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (nType == 1)
		gluLookAt(0, camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	else if (nType == 2)
		gluLookAt(0, 0.0, camera_dis, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (nType == 3)
		gluLookAt(camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else
		gluLookAt(camera_X, camera_Y, camera_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	if (!b4View)
		DisplayOneView(4, 0, screenWidth, 0, screenHeight);
	else {
		DisplayOneView(1, 0, screenWidth / 2, 0, screenHeight / 2);
		DisplayOneView(2, 0, screenWidth / 2, screenHeight / 2, screenHeight);
		DisplayOneView(3, screenWidth / 2, screenWidth, screenHeight / 2, screenHeight);
		DisplayOneView(4, screenWidth / 2, screenWidth, 0, screenHeight / 2);
	}
	

	
	
	
	drawAxis();
	drawSanNha();
	drawDeDuoi();
	drawDeTren();
	drawXylanh();
	drawBanDo();
	drawRotor();
	drawGiaDo1();
	drawGiaDo1BN();
	drawGiaDo2();
	drawGiaDo2BN();
	drawCoCauLienKet();
	drawThanhTruot1();
	drawThanhTruot2();
	drawChot();
	
	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	camera_angle = 45;
	camera_dis = 10;
	camera_height = 6;

	lookAt_X = 0;
	lookAt_Y = 2;
	lookAt_Z = 0;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Le Van Chi - 1510289"); // open the screen window

	deduoi.CreateHinhTru(deduoiHeight, deduoiRadius,deSlices);
	deduoi.SetColor(2);

	detren.CreateHinhTru(detrenHeight, detrenRadius,deSlices);
	detren.SetColor(1);

	xylanh.CreateHinhTru(xylanhHeight, xylanhRadius,deSlices);
	xylanh.SetColor(3);

	bando.CreateCuboid(bandoLength, bandoHeight,bandoWidth);
	bando.SetColor(4);

	giado1.CreateCuboid(giadoLength, giadoHeight,giadoWidth);
	giado1.SetColor(5);
	giado1bn.CreateHinhBanNguyet(giadobnWidth,giadobnHeight,giadobnRadius1,giadobnRadius2,deSlices);
	giado1bn.SetColor(6);

	giado2.CreateCuboid(giadoLength, giadoHeight,giadoWidth);
	giado2.SetColor(5);
	giado2bn.CreateHinhBanNguyet(giadobnWidth,giadobnHeight,giadobnRadius1,giadobnRadius2,deSlices);
	giado2bn.SetColor(6);

	rotor.CreateHinhTru(rotorHeight, rotorRadius,deSlices);
	rotor.SetColor(9);

	cclk.CreateHinhOvan(cclkLength,cclkHeight,cclkRadius1,cclkRadius2,deSlices);
	cclk.SetColor(10);
	
	thanhtruot1.CreateBienTheHinhTru(ttRadius1,ttRadius2,ttLength1,ttLength2,ttLength3,deSlices);
	thanhtruot1.SetColor(7);

	thanhtruot2.CreateBienTheHinhTru(ttRadius1,ttRadius2,ttLength1,ttLength2,ttLength3,deSlices);
	thanhtruot2.SetColor(7);

	chot.CreateBienTheHinhTru(chotRadius1,chotRadius2,chotLength1,chotLength2,chotLength3,deSlices);
	chot.SetColor(2);



	myInit();

	glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKey);
	  
	glutMainLoop();
	return 0;
}

