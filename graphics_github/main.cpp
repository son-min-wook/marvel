#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "imageloader.h"
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <GL/GL.h>
#define TRUE 1
#define GL_PI 3.1415f
#define FALSE 0
#define PI 3.141592
#define HORIZONTAL  0
#define VERTICAL 1
#define TOP 5
#define BTM -1.5
#define roomDMusic "C:\\Users\\oneca\\marvel\\graphics_github\\marvel.wav"
#define roomEMusic "C:\\Users\\oneca\\marvel\\graphics_github\\IronmanOST.wav"
#define roomAMusic "C:\\Users\\oneca\\marvel\\graphics_github\\EnterMusic.wav"
#define roomCMusic "C:\\Users\\oneca\\marvel\\graphics_github\\CaptainOST.wav"
GLuint helmet;
GLuint man;
GLuint hammer;
GLuint shield;
GLuint iron;
int musicCode = 0;
float carrot;
GLfloat eye1 = 0, eye2 = -0.7, eye3 = 13, at1 = 0, at2 = 0, at3 = 20;   //gluLookAt elements
																		// eye1 = 0, eye2 = -0.7, eye3 = 12
GLfloat beye1 = 0, beye2 = 0, beye3 = 0;         //previous gluLookAt's eye location. before of b
int delay = 20;
int ViewX = 0, ViewY = 0;          // location of mouse  (window Coordinate system)
int bViewX = 0, bViewY = 0;             //previous location of mouse (window Coordinate system)
GLfloat theta1 = 0, theta2 = 0;                //theta1: angle of x axis, theta2: angle of Y axis
GLfloat doora[3] = { -0.5, 0.1,-0.01 };
GLfloat doorb[3] = { 0.5, 0.1, -0.01 };
GLfloat doorc[3] = { 0.5, -1.5, -0.01 };
GLfloat doord[3] = { -0.5, -1.5,-0.01 };
float _angle = 0.0;
GLuint  _texturePebbles, _textureMark1, _textureMark2, _textureMark3, _textureMark4, _textureMark5, _textureMark6, _textureMark7, _textureBacklegr, _textureBackfootl, _textureBackfootr, _textureBackshoulderr, _textureBackhandr, _textureBacklegl, _textureBackhandl, _textureBackbody, _textureBackhead, _textureBackshoulderl, _Frontbody, _Frontshoulderr, _Frontshoulderl, _Frontlegr, _Frontlegl, _Fronthandr, _Fronthandl, _Frontfootr, _Frontfootl, _Fronthead, _textureAwake, _textureSpark, _textureThorgod, _textureMjolnir, _textureThunder, _textureWakanda, _textureDoc, _textureAgamoto, _textureDoctorstrange, _textureMask, _textureShieldicon, _textureWinterarm, _textureAnt, _textureCaptain2, _textureCaptain3, _textureCaptainshield, _texturePanthersuit, _textureSpidersuit, _textureIronman3, _textureIron2, _textureHulkbuster, _textureMark, _textureCaptainpost, _textureFalconpost, _textureWhitchpost, _textureWinterpost, _textureAntmanpost, _textureHawkeyepost, _textureSpiderpost, _textureIronpost, _textureWidowpost, _textureWarpost, _textureVisionpost, _texturePantherpost, _textureHulk, _textureLoki, _textureDoctor, _textureRun, _textureYellow, _textureGauntlet, _textureStone, _textureLaser, _textureUltron, _textureAvengers2, _textureAvengers3, _textureAntman, _textureHawkeye, _textureWhitch, _textureVision, _textureWidow, _textureSpiderman, _textureCivil3, _textureFalcon, _textureWinter, _textureWarmachine, _textureBlack, _textureCivil2, _textureCivil1, _textureThor, _textureRed, _textureBlue, _textureCaptain, _textureAvengers, _textureIron1, _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky, _texturelogo, _textureGrayBrick, _textureBlueBottom;
GLUquadricObj *pObj, *sky;
typedef struct RoomCoordinate {
	double x1;
	double z1;
	double x2;
	double z2;
}roomCoord;
roomCoord roomA = { -12.5,-15,12.5,-5 };
roomCoord roomB = { -12.5,-35,12.5,-15 };
roomCoord roomC = { -27.5,-35,-12.5,-15 };
roomCoord roomD = { -12.5,-50,12.5,-35 };
roomCoord roomE = { 12.5,-35,27.5,-15 };


static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 1, 200.0);
	gluPerspective(45.0f, 1.8, 0.1, 200);
	glMatrixMode(GL_MODELVIEW);

}
void MyMouseMove(GLint X, GLint Y) {          //Only move the gaze at the current position
	if (bViewX == 0 && bViewY == 0) {    //for the first mouse click, there is no previous mouse location data
		ViewX = X;
		bViewX = X;
		ViewY = Y;
		bViewY = Y;
	}
	else {                             //not a first mouse click
		ViewX = X;
		ViewY = Y;
		theta1 = theta1 - ((ViewX - bViewX)*0.4);          //x axis angle
		theta2 = theta2 - ((ViewY - bViewY)*0.4);
		printf("theta1 :%f  theta2:%f\n", theta1, theta2);  //y axis angle       Match movement of mouse with movement of eyes
		if (theta1>360)
			theta1 -= 360;
		if (theta2>90)
			theta2 = 90;
		if (theta1<-360)
			theta1 += 360;
		if (theta2<-90)
			theta2 = -90;
		bViewX = ViewX;
		bViewY = ViewY;
		at1 = eye1 + sin((theta1 * PI) / 180);              //change  x location
		at2 = eye2 + sin((theta2 * PI) / 180);           //change y location
		at3 = eye3 + cos(((360 - theta1) * PI) / 180);       //cahnge z location
		beye1 = eye1;
		beye2 = eye2;
		beye3 = eye3;
	}
}

void forward() {
	printf("cos((theta1*PI): %f\n", cos((theta1*PI)));
	printf("sin((theta1*PI): %f\n", sin((theta1*PI)));
	printf("theta1: %f\n", theta1);
	eye3 = eye3 + 3 * 0.05*cos((theta1*PI) / 180);
	eye1 = eye1 + 3 * 0.05*sin((theta1*PI) / 180);
	at3 = at3 + 3 * 0.05*cos((theta1*PI) / 180);
	at1 = at1 + 3 * 0.05*sin((theta1*PI) / 180);

}
void backward() {
	eye1 -= 3 * 0.05*sin((theta1 * PI) / 180);
	eye3 -= 3 * 0.05*cos((theta1 * PI) / 180);
	at1 -= 3 * 0.05*sin((theta1 * PI) / 180);
	at3 -= 3 * 0.05*cos((theta1 * PI) / 180);
}
void leftward() {
	eye1 += 3 * 0.05*sin(((theta1 + 90) * PI) / 180);
	eye3 += 3 * 0.05*cos(((theta1 + 90)  * PI) / 180);
	at1 += 3 * 0.05*sin(((theta1 + 90)  * PI) / 180);
	at3 += 3 * 0.05*cos(((theta1 + 90)  * PI) / 180);
}
void rightward() {
	eye1 -= 3 * 0.05*sin(((theta1 + 90)  * PI) / 180);
	eye3 -= 3 * 0.05*cos(((theta1 + 90)  * PI) / 180);
	at1 -= 3 * 0.05*sin(((theta1 + 90)  * PI) / 180);
	at3 -= 3 * 0.05*cos(((theta1 + 90)  * PI) / 180);
}
void moveBack(unsigned char key, int x, int y) {
	if (key == 'w')
		backward();
	else if (key == 's')
		forward();
	else if (key == 'a')
		rightward();
	else if (key == 'd')
		leftward();
}

void outsideSky(unsigned char key, int x, int y) {
	//left side over
	if (eye1 <= -45)
		moveBack(key, x, y);

	// right side over
	else if (eye1 >= 45)
		moveBack(key, x, y);

	//frontside over
	else if (eye3 <= -55)
		moveBack(key, x, y);
	//backside over
	else if (eye3 >= 35)
		moveBack(key, x, y);
}
int checkInAnyRoom(double x1, double z1, double x2, double z2) {

	if (eye1 >= x1 - 0.2&&eye1 <= x2 + 0.2&&eye3 >= z1 - 0.2&&eye3 <= z2 + 0.2) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}
void drawhelmet()
{
	glPushMatrix();

	glTranslatef(-35, -75, 15);
	glScalef(0.8, 0.8, 0.8);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(helmet);
	glPopMatrix();
	//carrot = carrot + 0.6;
	//if (carrot>360)carrot = carrot - 360;
}


void drawshield()
{
	glPushMatrix();
	glTranslatef(-20, -0.5, -25);
	glScalef(0.03, 0.03, 0.03);
	glRotatef(carrot, 0, 1, 0);
	glCallList(shield);
	glPopMatrix();
	carrot = carrot + 0.6;
	if (carrot>360)carrot = carrot - 360;
}



void GLRenderObject(char *fname) {
	int read;
	GLfloat x, y, z;
	FILE *fp;
	static float angle = 0.0f;
	char ch;
	helmet = glGenLists(1);

	fp = fopen(fname, "r");
	if (!fp) {
		printf("can't open file %s\n", fname);
		exit(1);
	}
	else {

		glPointSize(0.05);
		glNewList(helmet, GL_COMPILE);
		{
			glPushMatrix();
			glBegin(GL_POINTS);
			while (!(feof(fp)))
			{
				read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
				if (read == 4 && ch == 'v')
				{
					glVertex3f(x, y, z);
				}
			}
			glEnd();
		}
		glPopMatrix();
		glEndList();
		fclose(fp);
	}
}

void GLRenderObject3(char *fname) {
	int read;
	GLfloat x, y, z;
	FILE *fp;
	static float angle = 0.0f;
	char ch;
	shield = glGenLists(1);

	fp = fopen(fname, "r");
	if (!fp) {
		printf("can't open file %s\n", fname);
		exit(1);
	}
	else {

		glPointSize(4.0);
		glNewList(shield, GL_COMPILE);
		{
			glPushMatrix();
			glBegin(GL_POINTS);
			while (!(feof(fp)))
			{
				read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
				if (read == 4 && ch == 'v')
				{
					glVertex3f(x, y, z);
				}
			}
			glEnd();
		}
		glPopMatrix();
		glEndList();
		fclose(fp);
	}
}

void openCloseDoor() {
	if ((eye1 >= -1.5 && eye1 <= 0.75) && (eye3 >= -9.0 && eye3 <= -1.0)) {
		printf("opening\n");

		doora[0] = doora[0] - 0.05;
		if (doora[0] <= -1.5)
			doora[0] = -1.5;
		doorb[0] = doorb[0] - 0.05;
		if (doorb[0] <= -0.5)
			doorb[0] = -0.5;
		doorc[0] = doorc[0] - 0.05;
		if (doorc[0] <= -0.5)
			doorc[0] = -0.5;
		doord[0] = doord[0] - 0.05;
		if (doord[0] <= -1.5)
			doord[0] = -1.5;
	}
	else {

		printf("closing\n");
		doora[0] = doora[0] + 0.05;
		if (doora[0] >= -0.5)
			doora[0] = -0.5;
		doorb[0] = doorb[0] + 0.05;
		if (doorb[0] >= 0.5)
			doorb[0] = 0.5;
		doorc[0] = doorc[0] + 0.05;
		if (doorc[0] >= 0.5)
			doorc[0] = 0.5;
		doord[0] = doord[0] + 0.05;
		if (doord[0] >= -0.5)
			doord[0] = -0.5;
	}

}
void inMuseum1(unsigned char key, int x, int y) {
	//enter Room A
	if (checkInAnyRoom(roomA.x1, roomA.z1, roomA.x2, roomA.z2) == TRUE) {
		if (musicCode != 1) {
			PlaySound(TEXT(roomAMusic), NULL, SND_FILENAME | SND_ASYNC);
			musicCode = 1;
		}
		if ((eye3 > roomA.z2 - 0.2&&eye1 >= roomA.x1&&eye1 < -0.5) || (eye3 >= roomA.z2 - 0.2&&eye1 > 0.5 && eye1 <= roomA.x2))// front
			moveBack(key, x, y);
		else if (eye1 <= roomA.x1 + 0.2)// left
			moveBack(key, x, y);
		else if (eye1 >= roomA.x2 - 0.2)// right
			moveBack(key, x, y);
		//open door
	}

	//enter Room B
	else if (checkInAnyRoom(roomB.x1, roomB.z1, roomB.x2, roomB.z2) == TRUE) {
		if (musicCode != 0) {

			PlaySound(NULL, NULL, NULL); // 정지
			musicCode = 0;
		}
	}
	else if (checkInAnyRoom(roomC.x1, roomC.z1, roomC.x2, roomC.z2) == TRUE) {
		if (musicCode != 2) {
			PlaySound(TEXT(roomCMusic), NULL, SND_FILENAME | SND_ASYNC);
			musicCode = 2;
		}
		if (eye3 >= roomC.z2 - 0.2)//front
			moveBack(key, x, y);
		else if (eye1 <= roomC.x1 + 0.2)//left
			moveBack(key, x, y);
		else if (eye3 <= roomC.z1 + 0.2)//back
			moveBack(key, x, y);
	}

	else if (checkInAnyRoom(roomD.x1, roomD.z1, roomD.x2, roomD.z2) == TRUE) {
		if (musicCode != 3) {
			PlaySound(TEXT(roomDMusic), NULL, SND_FILENAME | SND_ASYNC);
			musicCode = 3;
		}
		if (eye3 <= roomD.z1 + 0.2)//back
			moveBack(key, x, y);
		else if (eye1 <= roomD.x1 + 0.2)//left
			moveBack(key, x, y);
		else if (eye1 >= roomD.x2 - 0.2)//right
			moveBack(key, x, y);

	}
	else if (checkInAnyRoom(roomE.x1, roomE.z1, roomE.x2, roomE.z2) == TRUE) { //여기로
		if (musicCode != 4) {
			PlaySound(TEXT(roomEMusic), NULL, SND_FILENAME | SND_ASYNC);
			musicCode = 4;
		}
		if (eye3 >= roomE.z2 - 0.2)//front
			moveBack(key, x, y);
		else if (eye1 >= roomE.x2 - 0.2)//right
			moveBack(key, x, y);
		else if (eye3 <= roomE.z1 + 0.2)//back
			moveBack(key, x, y);
	}

	//노래 나가면 꺼짐
	else if (checkInAnyRoom(roomA.x1, roomA.z1, roomA.x2, roomA.z2) == FALSE) {
		if (musicCode != 0) {

			PlaySound(NULL, NULL, NULL); // 정지
			musicCode = 0;
		}
	}

	if (checkInAnyRoom(-12, -25, 12, -23) == TRUE) {

		if (eye3 >= -23 - 0.2)//front
			moveBack(key, x, y);
		else if (eye3 <= -25 + 0.2)//back
			moveBack(key, x, y);
		else if (eye1 <= -12 + 0.2)//left
			moveBack(key, x, y);
		else if (eye1 >= 12 - 0.2)//right
			moveBack(key, x, y);
	}

	//원기둥 벽 설치

	//left front
	if (checkInAnyRoom(-29.7, -4.2, -28.3, -3.8) == TRUE) {
		if (eye3 >= -3.8 - 0.3)//front
			moveBack(key, x, y);
		else if (eye3 <= -4.2 + 0.3)//back
			moveBack(key, x, y);
		else if (eye1 <= -29.7 + 0.3)//left
			moveBack(key, x, y);
		else if (eye1 >= -28.3 - 0.3)//right
			moveBack(key, x, y);
	}
	//right front
	if (checkInAnyRoom(28.3, -4.2, 29.7, -3.8) == TRUE) {
		if (eye3 >= -3.8 - 0.3)//front
			moveBack(key, x, y);
		else if (eye3 <= -4.2 + 0.3)//back
			moveBack(key, x, y);
		else if (eye1 <= 28.3 + 0.3)//left
			moveBack(key, x, y);
		else if (eye1 >= 29.7 - 0.3)//right
			moveBack(key, x, y);
	}
	//left back
	if (checkInAnyRoom(-29.7, -51.2, -28.3, -50.8) == TRUE) {
		if (eye3 >= -52.8 - 0.3)//front
			moveBack(key, x, y);
		else if (eye3 <= -53.2 + 0.3)//back
			moveBack(key, x, y);
		else if (eye1 <= -29.7 + 0.3)//left
			moveBack(key, x, y);
		else if (eye1 >= -28.3 - 0.3)//right
			moveBack(key, x, y);
	}
	//right back
	if (checkInAnyRoom(28.3, -51.2, 29.7, -50.8) == TRUE) {
		if (eye3 >= -52.8 - 0.3)//front
			moveBack(key, x, y);
		else if (eye3 <= -53.2 + 0.3)//back
			moveBack(key, x, y);
		else if (eye1 <= 28.3 + 0.3)//left
			moveBack(key, x, y);
		else if (eye1 >= 29.7 - 0.3)//right
			moveBack(key, x, y);
	}

	//   renderingSquare(4, 1, -0.98, 8, BTM + 1, -0.98, 1, 0);
	//표지판 벽 설치
	if (checkInAnyRoom(4, -0.98, 8, -0.98) == TRUE) {

		if (eye3 >= -0.98 - 0.2)//front
			moveBack(key, x, y);
		else if (eye3 <= -0.98 + 0.2)//back
			moveBack(key, x, y);
		else if (eye1 <= 4 + 0.2)//left
			moveBack(key, x, y);
		else if (eye1 >= 8 - 0.2)//right
			moveBack(key, x, y);
	}

}



void keyboard_handler(unsigned char key, int x, int y)
{
	printf("%lf %lf %lf\n", eye1, eye2, eye3);
	if (key == 'w')
		forward();
	else if (key == 's')
		backward();
	else if (key == 'a')
		leftward();
	else if (key == 'd')
		rightward();

	outsideSky(key, x, y);
	openCloseDoor();
	inMuseum1(key, x, y);

}



void mouse_handler(int btn, int state, int x, int y) {                  //If you turn your eye with the mouse and click again or move 
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {               //the position and turn your eyes with the mouse, it will not
																	   //match the coordinates of the previous mouse and need to be reset.
		bViewX = 0;
		bViewY = 0;                       //move user's position

	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		bViewX = 0, bViewY = 0;                         //click other location
}


void renderingSquare(double x1, double y1, double z1, double x2, double y2, double z2, int d, int t) {
	glBegin(GL_QUADS);
	if (t == HORIZONTAL) {
		glTexCoord2f(0.0, d);  glVertex3f(x1, y1, z1);
		glTexCoord2f(d, d);  glVertex3f(x2, y1, z2);
		glTexCoord2f(d, 0.0);  glVertex3f(x2, y2, z2);
		glTexCoord2f(0.0, 0.0);  glVertex3f(x1, y2, z1);
	}
	else if (t == VERTICAL) {
		glTexCoord2f(0.0, d);  glVertex3f(x1, y1, z1);
		glTexCoord2f(0, 0);  glVertex3f(x1, y1, z2);
		glTexCoord2f(d, 0);  glVertex3f(x2, y2, z2);
		glTexCoord2f(d, d);  glVertex3f(x2, y2, z1);
	}
	glEnd();
}

void createSylinder(double x, double y, double z, double length, GLfloat size)
{
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(x, y, z);
	glRotatef(180.0f, 0, 1, 1);

	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	gluCylinder(pObj, size, size, length, 26, 13);

	glPopMatrix();
}

void renderingSquare1(double x1, double y1, double z1, double x2, double y2, double z2, int d, int t) {
	glBegin(GL_QUADS);
	if (t == HORIZONTAL) {
		glTexCoord2f(0.0, d);  glVertex3f(x1, y1, z1);
		glTexCoord2f(1, d);  glVertex3f(x2, y1, z2);
		glTexCoord2f(1, 0.0);  glVertex3f(x2, y2, z2);
		glTexCoord2f(0.0, 0.0);  glVertex3f(x1, y2, z1);
	}
	else if (t == VERTICAL) {
		glTexCoord2f(0.0, d);  glVertex3f(x1, y1, z1);
		glTexCoord2f(0, 0);  glVertex3f(x1, y1, z2);
		glTexCoord2f(1, 0);  glVertex3f(x2, y2, z2);
		glTexCoord2f(1, d);  glVertex3f(x2, y2, z1);
	}
	glEnd();
}
void renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	glLoadIdentity();
	gluLookAt(eye1, eye2, eye3, at1, at2, at3, 0, 1, 0);     //user's view point


	drawhelmet();
	drawshield();


	// Sky
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureSky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -10);
	sky = gluNewQuadric();
	glEnable(GL_LINE_SMOOTH);

	gluSphere(sky, 60.0f, 30, 30);


	glPopMatrix();

	// Grass
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureGrass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -6);
	glRotatef(_angle, 0.0, 1.0, 0.0);

	renderingSquare(-50, -1.5, 50, 50, -1.5, -50, 70, 1);

	glPopMatrix();

	//Museum

	//front


	//left side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -15);
	renderingSquare(-27.5, TOP, 0, -12.5, BTM, 0, 2, 0);
	renderingSquare(-27.5, TOP, -20, -27.5, BTM, 0, 2, 0);
	renderingSquare(-27.5, TOP, -20, -12.5, BTM, -20, 2, 0);
	renderingSquare(-12.5, TOP, 0, -27.5, TOP, -20, 2, 1);
	renderingSquare(-12.5, BTM + 0.01, 0, -27.5, BTM + 0.01, -20, 2, 1);
	glPopMatrix();


	//left 내곽
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBlue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -15);
	renderingSquare(-27.49, TOP - 0.01, -0.01, -12.51, BTM + 0.01, -0.01, 2, 0);
	renderingSquare(-27.49, TOP - 0.01, -19.99, -27.49, BTM + 0.01, -0.01, 2, 0);
	renderingSquare(-27.49, TOP - 0.01, -19.99, -12.51, BTM + 0.01, -19.99, 2, 0);
	renderingSquare(-12.51, TOP - 0.01, -0.01, -27.49, TOP - 0.01, -19.99, 2, 1);
	renderingSquare(-12.51, BTM + 0.01, -0.02, -27.49, BTM + 0.02, -19.99, 2, 1);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();



	//뒷방
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -35);
	renderingSquare(-12.5, TOP, -15, -12.5, BTM, 0, 2, 0);
	renderingSquare(-12.5, TOP, -15, 12.5, BTM, -15, 2, 0);
	renderingSquare(12.5, TOP, -15, 12.5, BTM, 0, 2, 0);
	renderingSquare(12.5, TOP, 0, -12.5, TOP, -15, 2, 1);
	renderingSquare(12.5, BTM + 0.01, 0, -12.5, BTM + 0.01, -15, 2, 1);
	glPopMatrix();

	//뒷방내곽
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureYellow);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -35);
	renderingSquare(-12.49, TOP - 0.01, -14.99, -12.49, BTM + 0.01, 0.01, 1, 0);
	renderingSquare(-12.49, TOP - 0.01, -14.99, 12.49, BTM + 0.01, -14.99, 1, 0);
	renderingSquare(12.49, TOP - 0.01, 0.01, 12.49, BTM + 0.01, -14.99, 1, 0);
	renderingSquare(12.49, TOP - 0.01, 0.01, -12.49, TOP - 0.01, -14.99, 1, 1);
	renderingSquare(12.49, BTM + 0.02, 0.01, -12.49, BTM + 0.02, -14.99, 1, 1);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();




	//right side
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -15);
	renderingSquare(12.5, TOP, -20, 27.5, BTM, -20, 2, 0);
	renderingSquare(27.5, TOP, -20, 27.5, BTM, 0, 2, 0);
	renderingSquare(12.5, TOP, 0, 27.5, BTM, 0, 2, 0);
	renderingSquare(27.5, TOP, 0, 12.5, TOP, -20, 2, 1);
	renderingSquare(27.5, BTM + 0.01, 0, 12.5, BTM + 0.01, -20, 2, 1);
	glPopMatrix();

	//오른쪽 내곽
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureRed);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -15);
	renderingSquare(12.51, TOP - 0.01, -19.99, 27.49, BTM + 0.01, -19.99, 2, 0);
	renderingSquare(27.49, TOP - 0.01, -19.99, 27.49, BTM + 0.01, -0.01, 2, 0);
	renderingSquare(12.51, TOP - 0.01, -0.01, 27.49, BTM + 0.01, -0.01, 2, 0);
	renderingSquare(27.49, TOP - 0.01, -0.01, 12.51, TOP - 0.01, -19.99, 2, 1);
	renderingSquare(27.49, BTM + 0.02, -0.01, 12.51, BTM + 0.02, -20, 2, 1);
	glBegin(GL_QUADS);
	glEnd();
	glPopMatrix();



	//가운데 위아래
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -15);
	renderingSquare(12.5, TOP, 0, -12.5, TOP, -20, 2, 1);
	renderingSquare(12.5, BTM + 0.01, 0, -12.5, BTM + 0.01, -20, 2, 1);
	glPopMatrix();

	//앞방
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -5);
	renderingSquare(-12.5, TOP, -10, -12.5, BTM, 0, 2, 0);
	renderingSquare(12.5, TOP, -10, 12.5, BTM, 0, 2, 0);
	renderingSquare(12.5, TOP, 0, -12.5, TOP, -10, 2, 1);
	renderingSquare(12.5, BTM + 0.01, 0, -12.5, BTM + 0.01, -10, 2, 1);
	renderingSquare(-12.5, TOP, 0, -0.5, BTM, 0, 2, 0);
	renderingSquare(-0.5, TOP, 0, 0.5, 0.1, 0, 1, 0);
	renderingSquare(0.5, TOP, 0, 12.5, BTM, 0, 2, 0);


	//입구 방 내곽

	glBindTexture(GL_TEXTURE_2D, _textureBlue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	renderingSquare(-12.49, TOP - 0.01, -10, -12.49, BTM + 0.01, -0.01, 1, 0);//left

	glBindTexture(GL_TEXTURE_2D, _textureRed);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	renderingSquare(12.49, TOP - 0.01, -10, 12.49, BTM + 0.01, -0.01, 1, 0);//right


	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	renderingSquare(-0.5, TOP, -0.01, 0.5, 0.1, -0.01, 1, 0);

	//문
	glBindTexture(GL_TEXTURE_2D, _textureDoor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	renderingSquare(doora[0], doora[1], doora[2], doorc[0], doorc[1], doorc[2], 1, 0);
	glPopMatrix();


	//건물 윗부분 장식
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	renderingSquare(30, TOP + 0.01, -3, -30, TOP + 0.01, -52, 4, 1);
	renderingSquare(32, TOP + 0.01 + 2, -1, -32, TOP + 0.01 + 2, -54, 2, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(-0.5, 0.7);  glVertex3f(-32, TOP + 2, -1);
	glTexCoord2f(5.5, 0.7);  glVertex3f(32, TOP + 2, -1);
	glTexCoord2f(5, 0.0);  glVertex3f(30, TOP + 0.01, -3);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-30, TOP + 0.01, -3);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2);  glVertex3f(32, TOP + 2, -1);
	glTexCoord2f(2, 2);  glVertex3f(32, TOP + 2, -54);
	glTexCoord2f(2, 0.0);  glVertex3f(30, TOP + 0.01, -52);
	glTexCoord2f(0.0, 0.0);  glVertex3f(30, TOP + 0.01, -3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2);  glVertex3f(32, TOP + 2, -1);
	glTexCoord2f(2, 2);  glVertex3f(32, TOP + 2, -54);
	glTexCoord2f(2, 0.0);  glVertex3f(30, TOP + 0.01, -52);
	glTexCoord2f(0.0, 0.0);  glVertex3f(30, TOP + 0.01, -3);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2);  glVertex3f(-32, TOP + 2, -52);
	glTexCoord2f(2, 2);  glVertex3f(32, TOP + 2, -52);
	glTexCoord2f(2, 0.0);  glVertex3f(30, TOP + 0.01, -50);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-30, TOP + 0.01, -50);
	glEnd();
	glPopMatrix();
	//건물 밖 기둥

	createSylinder(-29, BTM, -4, TOP - BTM + 0.5, 0.5f);
	createSylinder(29, BTM, -4, TOP - BTM + 0.5, 0.5f);
	createSylinder(29, BTM, -51, TOP - BTM + 0.5, 0.5f);
	createSylinder(-29, BTM, -51, TOP - BTM + 0.5, 0.5f);

	//가운데방 진열대

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureGrayBrick);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	renderingSquare(-12, 2, -25, 12, BTM + 0.01, -25, 2, 0);
	renderingSquare(-12, 2, -23, 12, BTM + 0.01, -23, 2, 0);
	renderingSquare(-12, 2, -25, -12, BTM + 0.01, -23, 2, 0);
	renderingSquare(12, 2, -25, 12, BTM + 0.01, -23, 2, 0);
	glPopMatrix();

	// 박물관 간판

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texturelogo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTranslatef(0, 0, -5);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-4.5, 4, 0.01);
	glTexCoord2f(1, 1);  glVertex3f(4.5, 4, 0.01);
	glTexCoord2f(1, 0.0);  glVertex3f(4.5, 0.5, 0.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-4.5, 0.5, 0.01);
	glEnd();
	glPopMatrix();

	// 표지판 기둥
	createSylinder(5, BTM, -1, 1, 0.05f);
	createSylinder(7, BTM, -1, 1, 0.05f);
	// 표지판 사진
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCivil2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	renderingSquare(4, 1, -0.98, 8, BTM + 1, -0.98, 1, 0);
	glPopMatrix();

	// ironmanpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureIronpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(27.48, 4, -27);
	glTexCoord2f(1, 1);  glVertex3f(27.48, 4, -23);
	glTexCoord2f(1, 0.0);  glVertex3f(27.48, -1, -23);
	glTexCoord2f(0.0, 0.0);  glVertex3f(27.48, -1, -27);
	glEnd();
	glPopMatrix();

	// ironman3
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureIronman3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(27.48, 3, -31);
	glTexCoord2f(1, 1);  glVertex3f(27.48, 3, -27.5);
	glTexCoord2f(1, 0.0);  glVertex3f(27.48, -0.5, -27.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(27.48, -0.5, -31);
	glEnd();
	glPopMatrix();

	// iron2
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureIron2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(27.48, 3, -22.5);
	glTexCoord2f(1, 1);  glVertex3f(27.48, 3, -19);
	glTexCoord2f(1, 0.0);  glVertex3f(27.48, -0.5, -19);
	glTexCoord2f(0.0, 0.0);  glVertex3f(27.48, -0.5, -22.5);
	glEnd();
	glPopMatrix();

	// hurkbuster
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureHulkbuster);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(27.48, 3, -34.5);
	glTexCoord2f(1, 1);  glVertex3f(27.48, 3, -31.5);
	glTexCoord2f(1, 0.0);  glVertex3f(27.48, -0.5, -31.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(27.48, -0.5, -34.5);
	glEnd();
	glPopMatrix();

	// mark
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(27.48, 4, -18);
	glTexCoord2f(1, 1);  glVertex3f(27.48, 4, -16);
	glTexCoord2f(1, 0.0);  glVertex3f(27.48, -1, -16);
	glTexCoord2f(0.0, 0.0);  glVertex3f(27.48, -1, -18);
	glEnd();
	glPopMatrix();


	// warpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWarpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(18.5, 4, -34.98);
	glTexCoord2f(1, 1);  glVertex3f(21.5, 4, -34.98);
	glTexCoord2f(1, 0.0);  glVertex3f(21.5, -1, -34.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(18.5, -1, -34.98);
	glEnd();
	glPopMatrix();

	// visionpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureVisionpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(23, 4, -34.98);
	glTexCoord2f(1, 1);  glVertex3f(26, 4, -34.98);
	glTexCoord2f(1, 0.0);  glVertex3f(26, -1, -34.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(23, -1, -34.98);
	glEnd();
	glPopMatrix();

	// spiderpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureSpiderpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(17.5, 4, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(14.5, 4, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(14.5, -1, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(17.5, -1, -15.02);
	glEnd();
	glPopMatrix();

	// pantherpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texturePantherpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(26, 4, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(23, 4, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(23, -1, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(26, -1, -15.02);
	glEnd();
	glPopMatrix();

	// panthersuit
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texturePanthersuit);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(21.5, 4.5, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(18.5, 4.5, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(18.5, 2, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(21.5, 2, -15.02);
	glEnd();
	glPopMatrix();

	// spidersuit
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureSpidersuit);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(21.5, 1.5, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(18.5, 1.5, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(18.5, -1.5, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(21.5, -1.5, -15.02);
	glEnd();
	glPopMatrix();



	// widowpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWidowpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(14, 4, -34.98);
	glTexCoord2f(1, 1);  glVertex3f(17, 4, -34.98);
	glTexCoord2f(1, 0.0);  glVertex3f(17, -1, -34.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(14, -1, -34.98);
	glEnd();
	glPopMatrix();

	// captainpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCaptainpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-27.48, 4, -23);
	glTexCoord2f(1, 1);  glVertex3f(-27.48, 4, -27);
	glTexCoord2f(1, 0.0);  glVertex3f(-27.48, -1, -27);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-27.48, -1, -23);
	glEnd();
	glPopMatrix();

	// captainshield
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCaptainshield);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-27.48, 4, -16);
	glTexCoord2f(1, 1);  glVertex3f(-27.48, 4, -21);
	glTexCoord2f(1, 0.0);  glVertex3f(-27.48, -1, -21);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-27.48, -1, -16);
	glEnd();
	glPopMatrix();

	// captain3
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCaptain3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-27.48, 3, -31.5);
	glTexCoord2f(1, 1);  glVertex3f(-27.48, 3, -34.5);
	glTexCoord2f(1, 0.0);  glVertex3f(-27.48, -0.5, -34.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-27.48, -0.5, -31.5);
	glEnd();
	glPopMatrix();

	// captain2
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCaptain2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-27.48, 3, -27.5);
	glTexCoord2f(1, 1);  glVertex3f(-27.48, 3, -31);
	glTexCoord2f(1, 0.0);  glVertex3f(-27.48, -0.5, -31);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-27.48, -0.5, -27.5);
	glEnd();
	glPopMatrix();


	// whitchpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWhitchpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-26, 4, -34.98);
	glTexCoord2f(1, 1);  glVertex3f(-23, 4, -34.98);
	glTexCoord2f(1, 0.0);  glVertex3f(-23, -1, -34.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-26, -1, -34.98);
	glEnd();
	glPopMatrix();

	// winterpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWinterpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-23, 4, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(-26, 4, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(-26, -1, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-23, -1, -15.02);
	glEnd();
	glPopMatrix();


	// falconpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureFalconpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-17, 4, -34.98);
	glTexCoord2f(1, 1);  glVertex3f(-14, 4, -34.98);
	glTexCoord2f(1, 0.0);  glVertex3f(-14, -1, -34.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-17, -1, -34.98);
	glEnd();
	glPopMatrix();

	// antmanpost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAntmanpost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-14.5, 4, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(-17.5, 4, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(-17.5, -1, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-14.5, -1, -15.02);
	glEnd();
	glPopMatrix();


	// ant
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAnt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-21.5, 4.5, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(-18.5, 4.5, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(-18.5, 2, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-21.5, 2, -15.02);
	glEnd();
	glPopMatrix();

	// winterarm
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWinterarm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-21.5, 1.5, -15.02);
	glTexCoord2f(1, 1);  glVertex3f(-18.5, 1.5, -15.02);
	glTexCoord2f(1, 0.0);  glVertex3f(-18.5, -1.5, -15.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-21.5, -1.5, -15.02);
	glEnd();
	glPopMatrix();

	// hawkeyepost
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureHawkeyepost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-21.5, 4, -34.98);
	glTexCoord2f(1, 1);  glVertex3f(-18.5, 4, -34.98);
	glTexCoord2f(1, 0.0);  glVertex3f(-18.5, -1, -34.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-21.5, -1, -34.98);
	glEnd();
	glPopMatrix();


	// ironman1
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureIron1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(5, 1.5, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(2.5, 1.5, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(2.5, -1, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(5, -1, -22.99);
	glEnd();
	glPopMatrix();

	// blackpanther
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureBlack);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(5.25, 1.5, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(7.75, 1.5, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(7.75, -1, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(5.25, -1, -22.99);
	glEnd();
	glPopMatrix();

	// war machine
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWarmachine);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(8, 1.5, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(10.5, 1.5, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(10.5, -1, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(8, -1, -22.99);
	glEnd();
	glPopMatrix();

	//avengers
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAvengers);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-12.48, 4, -38);
	glTexCoord2f(1, 1);  glVertex3f(-12.48, 4, -46);
	glTexCoord2f(1, 0.0);  glVertex3f(-12.48, 0, -46);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-12.48, 0, -38);
	glEnd();
	glPopMatrix();

	//loki
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureLoki);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-12.48, 3, -35.5);
	glTexCoord2f(1, 1);  glVertex3f(-12.48, 3, -37.5);
	glTexCoord2f(1, 0.0);  glVertex3f(-12.48, 1, -37.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-12.48, 1, -35.5);
	glEnd();
	glPopMatrix();

	//hulk
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureHulk);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-12.48, 3, -46.5);
	glTexCoord2f(1, 1);  glVertex3f(-12.48, 3, -49.5);
	glTexCoord2f(1, 0.0);  glVertex3f(-12.48, 1, -49.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-12.48, 1, -46.5);
	glEnd();
	glPopMatrix();

	//avengers2
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAvengers2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(12.48, 4, -46);
	glTexCoord2f(1, 1);  glVertex3f(12.48, 4, -38);
	glTexCoord2f(1, 0.0);  glVertex3f(12.48, 0, -38);
	glTexCoord2f(0.0, 0.0);  glVertex3f(12.48, 0, -46);
	glEnd();
	glPopMatrix();

	//avengers3
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAvengers3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-5, 4, -49.98);
	glTexCoord2f(1, 1);  glVertex3f(5, 4, -49.98);
	glTexCoord2f(1, 0.0);  glVertex3f(5, 0, -49.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-5, 0, -49.98);
	glEnd();
	glPopMatrix();

	//run
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureRun);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(8.5, 3, -49.98);
	glTexCoord2f(1, 1);  glVertex3f(6, 3, -49.98);
	glTexCoord2f(1, 0.0);  glVertex3f(6, 1, -49.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(8.5, 1, -49.98);
	glEnd();
	glPopMatrix();

	//stone
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureStone);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-9, 3, -49.98);
	glTexCoord2f(1, 1);  glVertex3f(-6, 3, -49.98);
	glTexCoord2f(1, 0.0);  glVertex3f(-6, 1, -49.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-9, 1, -49.98);
	glEnd();
	glPopMatrix();

	//gauntlet
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureGauntlet);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-11.5, 3, -49.98);
	glTexCoord2f(1, 1);  glVertex3f(-9.5, 3, -49.98);
	glTexCoord2f(1, 0.0);  glVertex3f(-9.5, 1, -49.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-11.5, 1, -49.98);
	glEnd();
	glPopMatrix();

	//ultron
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureUltron);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(12.48, 3.5, -37.5);
	glTexCoord2f(1, 1);  glVertex3f(12.48, 3.5, -35);
	glTexCoord2f(1, 0.0);  glVertex3f(12.48, 0.5, -35);
	glTexCoord2f(0.0, 0.0);  glVertex3f(12.48, 0.5, -37.5);
	glEnd();
	glPopMatrix();

	//laser
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureLaser);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(12.48, 3.5, -49);
	glTexCoord2f(1, 1);  glVertex3f(12.48, 3.5, -46.5);
	glTexCoord2f(1, 0.0);  glVertex3f(12.48, 0.5, -46.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(12.48, 0.5, -49);
	glEnd();
	glPopMatrix();

	//captain
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCaptain);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-5, 1.5, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(-2.5, 1.5, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(-2.5, -1, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-5, -1, -22.99);
	glEnd();
	glPopMatrix();

	//winter soilder
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWinter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-7.75, 1.5, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(-5.25, 1.5, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(-5.25, -1, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-7.75, -1, -22.99);
	glEnd();
	glPopMatrix();

	//falcon
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureFalcon);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-10.5, 1.5, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(-8, 1.5, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(-8, -1, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-10.5, -1, -22.99);
	glEnd();
	glPopMatrix();


	// civil1
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCivil1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-2.0, 1.7, -22.99);
	glTexCoord2f(1, 1);  glVertex3f(2, 1.7, -22.99);
	glTexCoord2f(1, 0.0);  glVertex3f(2, -1.2, -22.99);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-2, -1.2, -22.99);
	glEnd();
	glPopMatrix();

	// civil3
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureCivil3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-2.0, 1.7, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(2, 1.7, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(2, -1.2, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-2, -1.2, -25.01);
	glEnd();
	glPopMatrix();

	// spiderman
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureSpiderman);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(5, 1.5, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(2.5, 1.5, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(2.5, -1, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(5, -1, -25.01);
	glEnd();
	glPopMatrix();


	// blackwidow
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWidow);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(5.25, 1.5, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(7.75, 1.5, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(7.75, -1, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(5.25, -1, -25.01);
	glEnd();
	glPopMatrix();

	// vision
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureVision);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(8, 1.5, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(10.5, 1.5, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(10.5, -1, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(8, -1, -25.01);
	glEnd();
	glPopMatrix();

	//whitch
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWhitch);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-5, 1.5, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(-2.5, 1.5, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-2.5, -1, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-5, -1, -25.01);
	glEnd();
	glPopMatrix();

	//hawkeye
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureHawkeye);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-7.75, 1.5, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(-5.25, 1.5, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-5.25, -1, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-7.75, -1, -25.01);
	glEnd();
	glPopMatrix();

	//antman
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAntman);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-10.5, 1.5, -25.01);
	glTexCoord2f(1, 1);  glVertex3f(-8, 1.5, -25.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-8, -1, -25.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-10.5, -1, -25.01);
	glEnd();
	glPopMatrix();


	//mask
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMask);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(12.48, 4.5, -11.75);
	glTexCoord2f(1, 1);  glVertex3f(12.48, 4.5, -8.23);
	glTexCoord2f(1, 0.0);  glVertex3f(12.48, -1.0, -8.25);
	glTexCoord2f(0.0, 0.0);  glVertex3f(12.48, -1.0, -11.75);
	glEnd();
	glPopMatrix();


	//shieldicon
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureShieldicon);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-12.48, 4.5, -12.5);
	glTexCoord2f(1, 1);  glVertex3f(-12.48, 4.5, -7.5);
	glTexCoord2f(1, 0.0);  glVertex3f(-12.48, -1.0, -7.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-12.48, -1.0, -12.5);
	glEnd();
	glPopMatrix();


	//doctorstrange
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureDoctorstrange);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(4.5, 4.5, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(8.5, 4.5, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(8.5, -0.5, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(4.5, -0.5, -5.01);
	glEnd();
	glPopMatrix();


	//agamoto
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAgamoto);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(9.5, 4, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(11.5, 4, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(11.5, 2, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(9.5, 2, -5.01);
	glEnd();
	glPopMatrix();

	//doctor
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureDoctor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(12, 1, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(9, 1, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(9, -1, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(12, -1, -5.01);
	glEnd();
	glPopMatrix();

	//doc
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureDoc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(1, 3, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(4, 3, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(4, 1, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(1, 1, -5.01);
	glEnd();
	glPopMatrix();

	//wakanda
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureWakanda);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(12, 3, -49.98);
	glTexCoord2f(1, 1);  glVertex3f(9.5, 3, -49.98);
	glTexCoord2f(1, 0.0);  glVertex3f(9.5, 1, -49.98);
	glTexCoord2f(0.0, 0.0);  glVertex3f(12, 1, -49.98);
	glEnd();
	glPopMatrix();


	//thorgod
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureThorgod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-4.5, 4.5, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(-8.5, 4.5, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-8.5, -0.5, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-4.5, -0.5, -5.01);
	glEnd();
	glPopMatrix();


	//mjolnir
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMjolnir);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-9.5, 4, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(-11.5, 4, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-11.5, 2, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-9.5, 2, -5.01);
	glEnd();
	glPopMatrix();

	//thor
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureThor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-12, 1, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(-9, 1, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-9, -1, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-12, -1, -5.01);
	glEnd();
	glPopMatrix();

	//thunder
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureThunder);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-1, 4.25, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(-4, 4.25, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-4, 2.25, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-1, 2.25, -5.01);
	glEnd();
	glPopMatrix();

	//spark
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureSpark);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(0, 2.15, -5.02);
	glTexCoord2f(1, 1);  glVertex3f(-2, 2.15, -5.02);
	glTexCoord2f(1, 0.0);  glVertex3f(-2, 0.65, -5.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(0, 0.65, -5.02);
	glEnd();
	glPopMatrix();

	//awake
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureAwake);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(-2.1, 0.5, -5.01);
	glTexCoord2f(1, 1);  glVertex3f(-4.15, 0.5, -5.01);
	glTexCoord2f(1, 0.0);  glVertex3f(-4.15, -1.4, -5.01);
	glTexCoord2f(0.0, 0.0);  glVertex3f(-2.1, -1.4, -5.01);
	glEnd();
	glPopMatrix();


	//-----------------------------------------------------------------------------------------------------
	//front

	//head
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Fronthead);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, 0.9, -23.1);
	glTexCoord2f(1, 1);  glVertex3f(19.98, 0.9, -22.9);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, 0.6, -22.9);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, 0.6, -23.1);
	glEnd();
	glPopMatrix();

	//body
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontbody);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, 0.6, -23.3);
	glTexCoord2f(1, 1);  glVertex3f(19.98, 0.6, -22.7);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -0.25, -22.7);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -0.25, -23.3);
	glEnd();
	glPopMatrix();

	//SHOULDER L
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontshoulderl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, 0.5775, -23.45);
	glTexCoord2f(1, 1);  glVertex3f(19.98, 0.5775, -23.3);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, 0.18, -23.3);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, 0.18, -23.45);
	glEnd();
	glPopMatrix();

	//SHOULDER R
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontshoulderr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, 0.5775, -22.7);
	glTexCoord2f(1, 1);  glVertex3f(19.98, 0.5775, -22.55);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, 0.18, -22.55);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, 0.18, -22.7);
	glEnd();
	glPopMatrix();

	//hand l
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Fronthandl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, 0.18, -23.6);
	glTexCoord2f(1, 1);  glVertex3f(19.98, 0.18, -23.3);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -0.47, -23.3);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -0.47, -23.6);
	glEnd();
	glPopMatrix();

	//hand r
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Fronthandr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, 0.18, -22.7);
	glTexCoord2f(1, 1);  glVertex3f(19.98, 0.18, -22.4);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -0.47, -22.4);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -0.47, -22.7);
	glEnd();
	glPopMatrix();

	//leg l
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontlegl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, -0.25, -23.3);
	glTexCoord2f(1, 1);  glVertex3f(19.98, -0.25, -23.02);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -0.75, -23.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -0.75, -23.3);
	glEnd();
	glPopMatrix();

	//leg r
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontlegr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, -0.25, -22.98);
	glTexCoord2f(1, 1);  glVertex3f(19.98, -0.25, -22.7);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -0.75, -22.7);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -0.75, -22.98);
	glEnd();
	glPopMatrix();

	//foot l
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontfootl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, -0.75, -23.3405);
	glTexCoord2f(1, 1);  glVertex3f(19.98, -0.75, -23.0905);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -1.5, -23.0905);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -1.5, -23.3405);
	glEnd();
	glPopMatrix();


	//foot r
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _Frontfootr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.98, -0.75, -22.9095);
	glTexCoord2f(1, 1);  glVertex3f(19.98, -0.75, -22.6595);
	glTexCoord2f(1, 0.0);  glVertex3f(19.98, -1.5, -22.6595);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.98, -1.5, -22.9095);
	glEnd();
	glPopMatrix();



	//-------------------------------------------------------------------------------------------------------------------
	//front end



	//-----------------------------------------------------------------------------------------------------
	//back

	//head
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackhead);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, 0.9, -23.1);
	glTexCoord2f(1, 1);  glVertex3f(19.99, 0.9, -22.9);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, 0.6, -22.9);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, 0.6, -23.1);
	glEnd();
	glPopMatrix();

	//body
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackbody);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, 0.6, -23.3);
	glTexCoord2f(1, 1);  glVertex3f(19.99, 0.6, -22.7);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -0.25, -22.7);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -0.25, -23.3);
	glEnd();
	glPopMatrix();

	//SHOULDER L
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackshoulderl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, 0.5775, -23.45);
	glTexCoord2f(1, 1);  glVertex3f(19.99, 0.5775, -23.3);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, 0.18, -23.3);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, 0.18, -23.45);
	glEnd();
	glPopMatrix();

	//SHOULDER R
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackshoulderr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, 0.5775, -22.7);
	glTexCoord2f(1, 1);  glVertex3f(19.99, 0.5775, -22.55);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, 0.18, -22.55);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, 0.18, -22.7);
	glEnd();
	glPopMatrix();

	//hand r
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackhandr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, 0.18, -23.3);
	glTexCoord2f(1, 1);  glVertex3f(19.99, 0.18, -23.6);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -0.47, -23.6);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -0.47, -23.3);
	glEnd();
	glPopMatrix();

	//hand l
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackhandl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, 0.18, -22.4);
	glTexCoord2f(1, 1);  glVertex3f(19.99, 0.18, -22.7);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -0.47, -22.7);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -0.47, -22.4);
	glEnd();
	glPopMatrix();

	//leg l
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBacklegl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, -0.25, -23.3);
	glTexCoord2f(1, 1);  glVertex3f(19.99, -0.25, -23.02);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -0.75, -23.02);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -0.75, -23.3);
	glEnd();
	glPopMatrix();

	//leg r
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBacklegr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, -0.25, -22.98);
	glTexCoord2f(1, 1);  glVertex3f(19.99, -0.25, -22.7);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -0.75, -22.7);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -0.75, -22.98);
	glEnd();
	glPopMatrix();

	//foot l
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackfootl);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, -0.75, -23.3405);
	glTexCoord2f(1, 1);  glVertex3f(19.99, -0.75, -23.0905);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -1.5, -23.0905);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -1.5, -23.3405);
	glEnd();
	glPopMatrix();


	//foot r
	glPushMatrix();
	glTranslatef(-2.24, 0, -2);
	glBindTexture(GL_TEXTURE_2D, _textureBackfootr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(19.99, -0.75, -22.9095);
	glTexCoord2f(1, 1);  glVertex3f(19.99, -0.75, -22.6595);
	glTexCoord2f(1, 0.0);  glVertex3f(19.99, -1.5, -22.6595);
	glTexCoord2f(0.0, 0.0);  glVertex3f(19.99, -1.5, -22.9095);
	glEnd();
	glPopMatrix();

	//-------------------------------------------------------------------------------------------------------------------
	//back end
	//mark1
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(17, 1.5, -28.5);
	glTexCoord2f(1, 1);  glVertex3f(18.5, 1.5, -28.5);
	glTexCoord2f(1, 0.0);  glVertex3f(18.5, -1.5, -28.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(17, -1.5, -28.5);
	glEnd();
	glPopMatrix();

	//mark2
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  glVertex3f(18.7, 1.5, -28.25);
	glTexCoord2f(1, 1);  glVertex3f(19.7, 1.5, -27.25);
	glTexCoord2f(1, 0.0);  glVertex3f(19.7, -1.5, -27.25);
	glTexCoord2f(0, 0.0);  glVertex3f(18.7, -1.5, -28.25);
	glEnd();
	glPopMatrix();

	//mark3
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  glVertex3f(20.05, 1.5, -27);
	glTexCoord2f(1, 1);  glVertex3f(21.05, 1.5, -26);
	glTexCoord2f(1, 0);  glVertex3f(21.05, -1.5, -26);
	glTexCoord2f(0, 0);  glVertex3f(20.05, -1.5, -27);
	glEnd();
	glPopMatrix();

	//mark4
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(21.25, 1.5, -25.75);
	glTexCoord2f(1, 1);  glVertex3f(21.25, 1.5, -24.25);
	glTexCoord2f(1, 0.0);  glVertex3f(21.25, -1.5, -24.25);
	glTexCoord2f(0.0, 0.0);  glVertex3f(21.25, -1.5, -25.75);
	glEnd();
	glPopMatrix();

	//mark5
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  glVertex3f(20.05, 1.5, -23);
	glTexCoord2f(1, 1);  glVertex3f(21.05, 1.5, -24);
	glTexCoord2f(1, 0);  glVertex3f(21.05, -1.5, -24);
	glTexCoord2f(0, 0);  glVertex3f(20.05, -1.5, -23);
	glEnd();
	glPopMatrix();

	//mark6
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);  glVertex3f(18.7, 1.5, -21.75);
	glTexCoord2f(1, 1);  glVertex3f(19.7, 1.5, -22.75);
	glTexCoord2f(1, 0.0);  glVertex3f(19.7, -1.5, -22.75);
	glTexCoord2f(0, 0.0);  glVertex3f(18.7, -1.5, -21.75);
	glEnd();
	glPopMatrix();

	//mark7
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _textureMark7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1);  glVertex3f(17, 1.5, -21.5);
	glTexCoord2f(1, 1);  glVertex3f(18.5, 1.5, -21.5);
	glTexCoord2f(1, 0.0);  glVertex3f(18.5, -1.5, -21.5);
	glTexCoord2f(0.0, 0.0);  glVertex3f(17, -1.5, -21.5);
	glEnd();
	glPopMatrix();

	//road
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texturePebbles);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	renderingSquare1(0.7, BTM + 0.01, 5, -0.7, BTM + 0.01, -4, 5, 1);
	glPopMatrix();





	glutSwapBuffers();


}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Initialize() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 20);
	Image* image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\bricks.bmp");
	_textureBrick = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\door.bmp");
	_textureDoor = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\grass.bmp");
	_textureGrass = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\window.bmp");
	_textureWindow = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\sky.bmp");
	_textureSky = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\logo.bmp");
	_texturelogo = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\gray_brick.bmp");
	_textureGrayBrick = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\iron1.bmp");
	_textureIron1 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\avengers.bmp");
	_textureAvengers = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\captain.bmp");
	_textureCaptain = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\blue.bmp");
	_textureBlue = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\red.bmp");
	_textureRed = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\thor.bmp");
	_textureThor = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\civil1.bmp");
	_textureCivil1 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\civil2.bmp");
	_textureCivil2 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\blackpanther.bmp");
	_textureBlack = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\warmachine.bmp");
	_textureWarmachine = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\winter.bmp");
	_textureWinter = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\falcon.bmp");
	_textureFalcon = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\civil3.bmp");
	_textureCivil3 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\spiderman.bmp");
	_textureSpiderman = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\blackwidow.bmp");
	_textureWidow = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\vision.bmp");
	_textureVision = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\whitch.bmp");
	_textureWhitch = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\hawkeye.bmp");
	_textureHawkeye = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\antman.bmp");
	_textureAntman = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\avengers3.bmp");
	_textureAvengers3 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\avengers2.bmp");
	_textureAvengers2 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\ultron.bmp");
	_textureUltron = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\laser.bmp");
	_textureLaser = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\stone.bmp");
	_textureStone = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\gauntlet.bmp");
	_textureGauntlet = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\yellow.bmp");
	_textureYellow = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\run.bmp");
	_textureRun = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\doctor.bmp");
	_textureDoctor = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\loki.bmp");
	_textureLoki = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\hulk.bmp");
	_textureHulk = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\ironpost.bmp");
	_textureIronpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\spiderpost.bmp");
	_textureSpiderpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\widowpost.bmp");
	_textureWidowpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\warpost.bmp");
	_textureWarpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\visionpost.bmp");
	_textureVisionpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\pantherpost.bmp");
	_texturePantherpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\captainpost.bmp");
	_textureCaptainpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\falconpost.bmp");
	_textureFalconpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\whitchpost.bmp");
	_textureWhitchpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\winterpost.bmp");
	_textureWinterpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\antmanpost.bmp");
	_textureAntmanpost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\hawkeyepost.bmp");
	_textureHawkeyepost = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\ironman3.bmp");
	_textureIronman3 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\iron2.bmp");
	_textureIron2 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\hulkbuster.bmp");
	_textureHulkbuster = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark.bmp");
	_textureMark = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\spidersuit.bmp");
	_textureSpidersuit = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\panthersuit.bmp");
	_texturePanthersuit = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\captainshield.bmp");
	_textureCaptainshield = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\Captain2.bmp");
	_textureCaptain2 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\Captain3.bmp");
	_textureCaptain3 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\winterarm.bmp");
	_textureWinterarm = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\ant.bmp");
	_textureAnt = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mask.bmp");
	_textureMask = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\shieldicon.bmp");
	_textureShieldicon = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\doctorstrange.bmp");
	_textureDoctorstrange = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\agamoto.bmp");
	_textureAgamoto = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\doc.bmp");
	_textureDoc = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\wakanda.bmp");
	_textureWakanda = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\thunder.bmp");
	_textureThunder = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mjolnir.bmp");
	_textureMjolnir = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\thorgod.bmp");
	_textureThorgod = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\spark.bmp");
	_textureSpark = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\awake.bmp");
	_textureAwake = loadTexture(image);
	//--------------------------------------------------------------------------------------------------------------
	//front suit
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\fronthead.bmp");
	_Fronthead = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontfootl.bmp");
	_Frontfootl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontfootr.bmp");
	_Frontfootr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\fronthandl.bmp");
	_Fronthandl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\fronthandr.bmp");
	_Fronthandr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontlegl.bmp");
	_Frontlegl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontlegr.bmp");
	_Frontlegr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontshoulderl.bmp");
	_Frontshoulderl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontshoulderr.bmp");
	_Frontshoulderr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\frontbody.bmp");
	_Frontbody = loadTexture(image);
	//--------------------------------------------------------------------------------------------------------------
	//back suit
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backlegr.bmp");
	_textureBacklegr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backfootl.bmp");
	_textureBackfootl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backfootr.bmp");
	_textureBackfootr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backshoulderr.bmp");
	_textureBackshoulderr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backhandr.bmp");
	_textureBackhandr = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backlegl.bmp");
	_textureBacklegl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backhandl.bmp");
	_textureBackhandl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backbody.bmp");
	_textureBackbody = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backhead.bmp");
	_textureBackhead = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\backshoulderl.bmp");
	_textureBackshoulderl = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark1.bmp");
	_textureMark1 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark2.bmp");
	_textureMark2 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark3.bmp");
	_textureMark3 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark4.bmp");
	_textureMark4 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark5.bmp");
	_textureMark5 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark6.bmp");
	_textureMark6 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\mark7.bmp");
	_textureMark7 = loadTexture(image);
	image = loadBMP("C:\\Users\\oneca\\marvel\\graphics_github\\pebbles.bmp");
	_texturePebbles = loadTexture(image);

	delete image;
}

int main(int argc, char **argv) {
	void timer(int);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1800, 900);
	glutCreateWindow("openGL Museum by Son & Bae");
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(delay, timer, 0);
	glutMouseFunc(mouse_handler);             // add mouse handler
	glutKeyboardFunc(keyboard_handler);       // add keyboard handler

	glutMotionFunc(MyMouseMove);             // add mouse location funciton
	glutReshapeFunc(resize);
	glutDisplayFunc(renderScene);
	Initialize();

	GLRenderObject("helm.obj");
	GLRenderObject3("shield.obj");


	glutMainLoop();

	return 0;
}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}