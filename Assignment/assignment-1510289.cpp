
#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <windows.h>
#include <gl.h>
#include <glut.h>

class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Point3& p)
						{ x = p.x; y = p.y; z = p.z;}
	Point3() { x = y = z = 0;}
	Point3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
						{ r = red; g = green; b = blue;}
	void set(Color3& c)
						{ r = c.r; g = c.g; b = c.b;}
	Color3() { r = g = b = 0;}
	Color3(float red, float green, float blue)
						{ r = red; g = green; b = blue;}

};
class Point2
{
	public:
		Point2() { x = y = 0.0f; } // constructor 1
		Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
		void set(float xx, float yy) { x = xx; y = yy; }
		float getX() { return x;}
		float getY() { return y;}
		void draw()		{	glBegin(GL_POINTS);
								glVertex2f((GLfloat)x, (GLfloat)y);
							glEnd();
						}
	private:
		float 	x, y;
};
class IntRect
{
	 public:
		IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
		IntRect( int left, int right, int bottom, int top)
			{ l = left; r = right; b = bottom; t = top; }
		void set( int left, int right, int bottom, int top)
			{ l = left; r = right; b = bottom; t = top; }
		void draw(){
						glRecti(l, b, r, t);
						glFlush();
					} // draw this rectangle using OpenGL
		int  getWidth(){return (r-l);}
		int  getHeight() { return (t-b);}
	 private:
		int	l, r, b, t;
};


class RealRect
{
	 public:
		RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
		RealRect( float left, float right, float bottom, float top)
			{ l = left; r = right; b = bottom; t = top; }
		void set( float left, float right, float bottom, float top)
			{ l = left; r = right; b = bottom; t = top; }
		float  getWidth(){return (r-l);}
		float  getHeight() { return (t-b);}
		void RealRect::draw(){
							glRectf(l, b, r, t);
							glFlush();
						};// draw this rectangle using OpenGL
	 private:
		float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	void flip()
						{ x = -x; y = -y; z = -z;}
	void normalize();
	Vector3() { x = y = z = 0;}
	Vector3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	Vector3(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};


class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	
	Face()
	{
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;
	
	int		numFaces;
	Face*		face;


	float		slideX, slideY, slideZ;		// added
	float		rotateX, rotateY, rotateZ;	// added
	float		scaleX, scaleY, scaleZ;		// added

public:
	Mesh()
	{
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;

		slideX = 0; slideY= 0; slideZ= 0;
		rotateX = 0, rotateY= 0, rotateZ= 0;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void SetColor(int colorIdx) ;
	void DrawWireframe();
	void DrawColor();
	void DrawColorSanNha();

	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);

	void CreateHinhTru(float H,float R,int nSlices);

	void CreateBienTheHinhTru(float D1,float D2,float L1,float L2,float L3,int n);

	void CreateHinhOvan(float d,float h,float r1,float r2,int n);

	void CreateHinhBanNguyet(float h,float w,float r1,float r2,float n);

	void CreateHinhBanNguyet(float l,float height,float r1,float r2,int nSlice);

	void CreateSanNha(float size,float posX,float Z);
};

////////////////////////////////////////////////////////////////////


#define PI			3.1415926
#define	COLORNUM		14
#define DEG2RAD (3.14159f/180.0f)


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};

////////////////////////////////////////////////////////////////////////

void Mesh::CreateCuboid(float fSizeX,float fSizeY, float fSizeZ){
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX/2, fSizeY, fSizeZ/2);
	pt[1].set( fSizeX/2, fSizeY, fSizeZ/2);
	pt[2].set( fSizeX/2, fSizeY, -fSizeZ/2);
	pt[3].set(-fSizeX/2, fSizeY, -fSizeZ/2);
	pt[4].set(-fSizeX/2, 0, fSizeZ/2);
	pt[5].set( fSizeX/2, 0, fSizeZ/2);
	pt[6].set( fSizeX/2, 0, -fSizeZ/2);
	pt[7].set(-fSizeX/2, 0, -fSizeZ/2);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	
	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	
	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	
	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
}

void Mesh::CreateHinhTru(float H,float R,int n){

	int i;
	float D2R = 3.14159f / 180;
	float range = 360/n;

	numVerts = n * 2 +2 ; 
	pt = new Point3[numVerts];
	
	for(i =0;i<n;i++){
		
		pt[i].set( R * cos(i*range*D2R) ,0, R *sin(i*range*D2R));
		pt[i+n].set( R * cos(i*range*D2R) ,H, R *sin(i*range*D2R));

	}
	
	pt[numVerts-1].set(0,0,0);
	pt[numVerts-2].set(0, H ,0);
	

	numFaces = n*3 ;  
	face = new Face[numFaces];
	// mat duoi cung
	for(i=0;i<n-1;i++){
		face[i].nVerts=3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex= numVerts-1;
		face[i].vert[1].vertIndex= i;
		face[i].vert[2].vertIndex= i+1;
	}
	// i=n-1, mat cuoi 
	face[i].nVerts=3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex= numVerts-1;
	face[i].vert[1].vertIndex= 0;
	face[i].vert[2].vertIndex= i;

	// Mat ben hinh tru duoi 
	for(i=0;i<n-1;i++){
		face[i+n].nVerts=4;
		face[i+n].vert = new VertexID[face[i+n].nVerts];
		face[i+n].vert[0].vertIndex= i;
		face[i+n].vert[1].vertIndex= i+1;
		face[i+n].vert[2].vertIndex= i+n+1;
		face[i+n].vert[3].vertIndex= i+n;
	}
	face[i+n].nVerts=4;
	face[i+n].vert = new VertexID[face[i+n].nVerts];
	face[i+n].vert[0].vertIndex= 0;
	face[i+n].vert[1].vertIndex= n-1;
	face[i+n].vert[2].vertIndex= i+n;
	face[i+n].vert[3].vertIndex= n;
	// Mat tren 

	for(i=0;i<n-1;i++){
		face[i+2*n].nVerts=3;
		face[i+2*n].vert = new VertexID[face[i+2*n].nVerts];
		face[i+2*n].vert[0].vertIndex= numVerts-2;
		face[i+2*n].vert[1].vertIndex= i+n;
		face[i+2*n].vert[2].vertIndex= i+n+1;
	}
	 //i=n-1, mat cuoi 
	face[i+2*n].nVerts=3;
	face[i+2*n].vert = new VertexID[face[i+2*n].nVerts];
	face[i+2*n].vert[0].vertIndex= numVerts-2;
	face[i+2*n].vert[1].vertIndex= n;
	face[i+2*n].vert[2].vertIndex= 2*n-1;
}

void Mesh::CreateBienTheHinhTru(float R1,float R2,float L1,float L2,float L3,int n){
	int i;

	float D2R = 3.14159f / 180;
	float range = 360/n;

	numVerts = n * 4 +3 ; 
	pt = new Point3[numVerts];
	
	for(i =0;i<n;i++){
		pt[i].set( R1 * cos(i*range*D2R) ,0, R1 *sin(i*range*D2R));
		pt[i+n].set( R1 * cos(i*range*D2R) ,L1, R1 *sin(i*range*D2R));

		pt[i+2*n].set( R2 * cos(i*range*D2R) ,L1+L2, R2 *sin(i*range*D2R));
		pt[i+3*n].set( R2 * cos(i*range*D2R) ,L1+L2+L3, R2 *sin(i*range*D2R));
	}
	
	pt[numVerts-1].set(0, 0 ,0);
	pt[numVerts-2].set(0, L1 ,0);
	pt[numVerts-3].set(0, L1+L2+L3,0);

	numFaces = n*5 ;  
	face = new Face[numFaces];
	// mat duoi cung
	for(i=0;i<n-1;i++){
		face[i].nVerts=3;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex= numVerts-1;
		face[i].vert[1].vertIndex= i;
		face[i].vert[2].vertIndex= i+1;
	}
	// i=n-1, mat cuoi 
	face[i].nVerts=3;
	face[i].vert = new VertexID[face[i].nVerts];
	face[i].vert[0].vertIndex= numVerts-1;
	face[i].vert[1].vertIndex= 0;
	face[i].vert[2].vertIndex= i;

	// Mat ben hinh tru duoi 
	for(i=0;i<n-1;i++){
		face[i+n].nVerts=4;
		face[i+n].vert = new VertexID[face[i+n].nVerts];
		face[i+n].vert[0].vertIndex= i;
		face[i+n].vert[1].vertIndex= i+1;
		face[i+n].vert[2].vertIndex= i+n+1;
		face[i+n].vert[3].vertIndex= i+n;
	}
	face[i+n].nVerts=4;
	face[i+n].vert = new VertexID[face[i+n].nVerts];
	face[i+n].vert[0].vertIndex= 0;
	face[i+n].vert[1].vertIndex= n-1;
	face[i+n].vert[2].vertIndex= i+n;
	face[i+n].vert[3].vertIndex= n;

	// mat noi 2 hinh tru
	for(i=0;i<n-1;i++){
		face[i+2*n].nVerts=4;
		face[i+2*n].vert = new VertexID[face[i+2*n].nVerts];
		face[i+2*n].vert[0].vertIndex= i+n;
		face[i+2*n].vert[1].vertIndex= i+n+1;
		face[i+2*n].vert[2].vertIndex= i+2*n+1;
		face[i+2*n].vert[3].vertIndex= i+2*n;
	}
	face[i+2*n].nVerts=4;
	face[i+2*n].vert = new VertexID[face[i+2*n].nVerts];
	face[i+2*n].vert[0].vertIndex= 2*n-1;
	face[i+2*n].vert[1].vertIndex= n;
	face[i+2*n].vert[2].vertIndex= 2*n;
	face[i+2*n].vert[3].vertIndex= 3*n-1;

	// mat xung quanh tru nho
	for(i=0;i<n-1;i++){
		face[i+3*n].nVerts=4;
		face[i+3*n].vert = new VertexID[face[i+3*n].nVerts];
		face[i+3*n].vert[0].vertIndex= i+2*n;
		face[i+3*n].vert[1].vertIndex= i+2*n+1;
		face[i+3*n].vert[2].vertIndex= i+3*n+1;
		face[i+3*n].vert[3].vertIndex= i+3*n;
	}
	face[i+3*n].nVerts=4;
	face[i+3*n].vert = new VertexID[face[i+3*n].nVerts];
	face[i+3*n].vert[0].vertIndex= 2*n;
	face[i+3*n].vert[1].vertIndex= 3*n-1;
	face[i+3*n].vert[2].vertIndex= 4*n-1;
	face[i+3*n].vert[3].vertIndex= 3*n;
	
	// Mat tren cung
	for(i=0;i<n-1;i++){
		face[i+4*n].nVerts=3;
		face[i+4*n].vert = new VertexID[face[i+4*n].nVerts];
		face[i+4*n].vert[0].vertIndex= numVerts-3;
		face[i+4*n].vert[1].vertIndex= i+3*n;
		face[i+4*n].vert[2].vertIndex= i+3*n+1;
	}
	face[i+4*n].nVerts=3;
	face[i+4*n].vert = new VertexID[face[i+4*n].nVerts];
	face[i+4*n].vert[0].vertIndex= numVerts-3;
	face[i+4*n].vert[1].vertIndex= 3*n;
	face[i+4*n].vert[2].vertIndex= 4*n-1;
}

void Mesh::CreateHinhOvan(float d,float h,float r1,float r2,int n){


	numVerts = (n+1)*4*2;
	float angle=PI/n;
	pt = new Point3[numVerts];

	int i;

	for(i =0 ; i <n+1;i++){
		pt[i].set(d/2 +  r1*sin( i*angle), 0, r1*cos(i*angle) );		
		pt[i+n+1].set(d/2+ r2*sin(i*angle),0,r2*cos(i*angle)    );

		pt[i+2*n+2].set(d/2+ r1*sin( i*angle) ,h, r1*cos(i*angle) );		
		pt[i+3*n+3].set(d/2+ r2*sin(i*angle),h,r2*cos(i*angle));

		pt[i+4*n+4].set(-d/2-r1 *sin(i*angle), 0  ,-r1*cos(i*angle));
		pt[i+5*n+5].set(-d/2-r2*sin(i*angle),0,  - r2*cos(i*angle)    );

		pt[i+6*n+6].set(-d/2-r1 *sin(i*angle), h  ,-r1*cos(i*angle));
		pt[i+7*n+7].set(-d/2-r2*sin(i*angle),  h,  - r2*cos(i*angle)    );

	}

	numFaces = 8*n+ 4*2;
	face = new Face[numFaces];

	//mat duoi thu 1
	for(i =0 ;i<n;i++){
		face[i].nVerts=4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex= i ;
		face[i].vert[1].vertIndex= i+1;
		face[i].vert[2].vertIndex= i+2+n;
		face[i].vert[3].vertIndex= i+1+n;
	}
	// Mat tren thu 1
	for(i =0 ;i<n;i++){
		face[i+n].nVerts=4;
		face[i+n].vert = new VertexID[face[i].nVerts];
		face[i+n].vert[0].vertIndex= i +2*n+2;
		face[i+n].vert[1].vertIndex= i+2*n+3;
		face[i+n].vert[2].vertIndex= i+3*n+4;
		face[i+n].vert[3].vertIndex= i+3*n+3;
	}
	// mat trong thu 1
	for(i =0 ;i<n;i++){
		face[i+2*n].nVerts=4;
		face[i+2*n].vert = new VertexID[face[i].nVerts];
		face[i+2*n].vert[0].vertIndex= i;
		face[i+2*n].vert[1].vertIndex= i+1;
		face[i+2*n].vert[2].vertIndex= i+2*n+3;
		face[i+2*n].vert[3].vertIndex= i+2*n+2;
	}
	// mat ngoai thu 1 
	for(i =0 ;i<n;i++){
		face[i+3*n].nVerts=4;
		face[i+3*n].vert = new VertexID[face[i].nVerts];
		face[i+3*n].vert[0].vertIndex= i+n+1;
		face[i+3*n].vert[1].vertIndex= i+n+2;
		face[i+3*n].vert[2].vertIndex= i+3*n+4;
		face[i+3*n].vert[3].vertIndex= i+3*n+3;
	}
		// mat duoi thu 2
	for(i =0 ;i<n;i++){
	
		face[i+4*n].nVerts=4;
		face[i+4*n].vert = new VertexID[face[i].nVerts];
		face[i+4*n].vert[0].vertIndex= i+4*n+4;
		face[i+4*n].vert[1].vertIndex= i+4*n+4+1;
		face[i+4*n].vert[2].vertIndex= i+5*n+5+1;
		face[i+4*n].vert[3].vertIndex= i+5*n+5;
	}

	// Mat tren thu 2
	for(i =0 ;i<n;i++){
	
		face[i+5*n].nVerts=4;
		face[i+5*n].vert = new VertexID[face[i].nVerts];
		face[i+5*n].vert[0].vertIndex= i+6*n+6;
		face[i+5*n].vert[1].vertIndex= i+6*n+6+1;
		face[i+5*n].vert[2].vertIndex= i+7*n+7+1;
		face[i+5*n].vert[3].vertIndex= i+7*n+7;
	}

	// mat trong thu 2
	for(i =0 ;i<n;i++){
		face[i+6*n].nVerts=4;
		face[i+6*n].vert = new VertexID[face[i].nVerts];
		face[i+6*n].vert[0].vertIndex= i+4*n+4;
		face[i+6*n].vert[1].vertIndex= i+4*n+4+1;
		face[i+6*n].vert[2].vertIndex= i+6*n+6+1;
		face[i+6*n].vert[3].vertIndex= i+6*n+6;
	}
	// mat ngoai thu 2
	for(i =0 ;i<n;i++){
		face[i+7*n].nVerts=4;
		face[i+7*n].vert = new VertexID[face[i].nVerts];
		face[i+7*n].vert[0].vertIndex= i+5*n+5;
		face[i+7*n].vert[1].vertIndex= i+5*n+5+1;
		face[i+7*n].vert[2].vertIndex= i+7*n+7+1;
		face[i+7*n].vert[3].vertIndex= i+7*n+7;
	}
	// mat duoi HCN1 - phia sau
	face[8*n].nVerts = 4;
	face[8*n].vert = new VertexID[face[0].nVerts];
	face[8*n].vert[0].vertIndex = n;
	face[8*n].vert[1].vertIndex = n+1+n;
	face[8*n].vert[2].vertIndex = 5*n+5;
	face[8*n].vert[3].vertIndex = 4*n+4;

	// mat sau HCN1
	face[8*n+1].nVerts = 4;
	face[8*n+1].vert = new VertexID[face[0].nVerts];
	face[8*n+1].vert[0].vertIndex = n+1+n;
	face[8*n+1].vert[1].vertIndex = 3*n+3+n;
	face[8*n+1].vert[2].vertIndex = 7*n+7;
	face[8*n+1].vert[3].vertIndex = 5*n+5;

	// mat tren HCN1
	face[8*n+2].nVerts = 4;
	face[8*n+2].vert = new VertexID[face[0].nVerts];
	face[8*n+2].vert[0].vertIndex = 3*n+3+n;
	face[8*n+2].vert[1].vertIndex = 7*n+7;
	face[8*n+2].vert[2].vertIndex = 6*n+6;
	face[8*n+2].vert[3].vertIndex = 2*n+2+n;

	// mat truoc HCN1
	face[8*n+3].nVerts = 4;
	face[8*n+3].vert = new VertexID[face[0].nVerts];
	face[8*n+3].vert[0].vertIndex = n;
	face[8*n+3].vert[1].vertIndex = 2*n+2+n;
	face[8*n+3].vert[2].vertIndex = 6*n+6;
	face[8*n+3].vert[3].vertIndex = 4*n+4;

	// mat duoi HCN2
	face[8*n+4].nVerts = 4;
	face[8*n+4].vert = new VertexID[face[0].nVerts];
	face[8*n+4].vert[0].vertIndex = n+1;
	face[8*n+4].vert[1].vertIndex = 0;
	face[8*n+4].vert[2].vertIndex = 4*n+4+n;
	face[8*n+4].vert[3].vertIndex = 5*n+5+n;

	// mat sau HCN2
	face[8*n+5].nVerts = 4;
	face[8*n+5].vert = new VertexID[face[0].nVerts];
	face[8*n+5].vert[0].vertIndex = 0;
	face[8*n+5].vert[1].vertIndex = 2*n+2;
	face[8*n+5].vert[2].vertIndex = 6*n+6+n;
	face[8*n+5].vert[3].vertIndex = 4*n+4+n;

	// mat tren HCN2
	face[8*n+6].nVerts = 4;
	face[8*n+6].vert = new VertexID[face[0].nVerts];
	face[8*n+6].vert[0].vertIndex = 3*n+3;
	face[8*n+6].vert[1].vertIndex = 2*n+2;
	face[8*n+6].vert[2].vertIndex = 6*n+6+n;
	face[8*n+6].vert[3].vertIndex = 7*n+7+n;

	//  mat to ngoai 
	face[8*n+7].nVerts = 4;
	face[8*n+7].vert = new VertexID[face[0].nVerts];
	face[8*n+7].vert[0].vertIndex = n+1;
	face[8*n+7].vert[1].vertIndex = 3*n+3;
	face[8*n+7].vert[2].vertIndex = 7*n + 7+n;
	face[8*n+7].vert[3].vertIndex = 5*n+5+n;
}

void Mesh::CreateHinhBanNguyet(float l,float height,float r1,float r2,int nSlice){
	int i;

	numVerts = (nSlice * 6+6) +2*(nSlice+1)+4;
	pt = new Point3[numVerts];
	float alpha = PI / nSlice ;

	for (i = 0; i < nSlice+1; i++) {
		float angle = alpha * i ;
		pt[i].set(r1 * cos(angle),l+r1 * sin(angle),-height/2);
		pt[i + nSlice+1].set(r2* cos(angle),l+r2 * sin(angle),-height/2);
		pt[i+nSlice*2+2].set(r1 * cos(angle),l+r1 * sin(angle),height/2);
		pt[i+nSlice*3+3].set(r2* cos(angle),l+r2 * sin(angle),height/2);
		pt[i+nSlice*4+4].set(r1* cos(angle),l+r1*-sin(angle),-height/2);
		pt[i+nSlice*5+5].set(r1* cos(angle),l+r1*-sin(angle),height/2);
		pt[i+nSlice*6+6].set(r1* cos(angle),0,-height/2);
		pt[i+nSlice*7+7].set(r1* cos(angle),0,height/2);

	}
	pt[nSlice*8+8].set(r2,0,-height/2);
	pt[nSlice*8+9].set(-r2,0,-height/2);
	pt[nSlice*8+10].set(r2,0,height/2);
	pt[nSlice*8+11].set(-r2,0,height/2);
	numFaces =nSlice*7+8;
	face=new Face[numFaces];
	for (i=0;i<nSlice;i++){
		face[i].nVerts = 4;
		face[i].vert = new VertexID[4];
		face[i].vert[0].vertIndex = i;
		face[i].vert[1].vertIndex = i+1;
		face[i].vert[2].vertIndex = i+nSlice+2;
		face[i].vert[3].vertIndex = i+nSlice+1;
	}
	for (i=0;i<nSlice;i++){
		face[i+nSlice].nVerts = 4;
		face[i+nSlice].vert = new VertexID[4];
		face[i+nSlice].vert[0].vertIndex = i+2*nSlice+2;
		face[i+nSlice].vert[1].vertIndex = i+2*nSlice+3;
		face[i+nSlice].vert[2].vertIndex = i+3*nSlice+4;
		face[i+nSlice].vert[3].vertIndex = i+3*nSlice+3;
	}
	for (i = 0; i < nSlice; i++) {
		face[i+nSlice*2].nVerts = 4;
		face[i+nSlice*2].vert = new VertexID[4];
		face[i+nSlice*2].vert[0].vertIndex = i;
		face[i+nSlice*2].vert[1].vertIndex = i+1;
		face[i+nSlice*2].vert[2].vertIndex= i+nSlice*2+3;
		face[i+nSlice*2].vert[3].vertIndex = i+nSlice*2+2;
		
	}
	for (i = 0; i < nSlice; i++) {
		face[i+nSlice*3].nVerts = 4;
		face[i+nSlice*3].vert = new VertexID[4];
		face[i+nSlice*3].vert[0].vertIndex = i+nSlice+1;
		face[i+nSlice*3].vert[1].vertIndex = i+nSlice*3+3;
		face[i+nSlice*3].vert[2].vertIndex= i+nSlice*3+4;
		face[i+nSlice*3].vert[3].vertIndex = i+nSlice+2;
		
	}
	for (i = 0; i < nSlice; i++) {
		face[i+nSlice*4].nVerts = 4;
		face[i+nSlice*4].vert = new VertexID[4];
		face[i+nSlice*4].vert[0].vertIndex = i+4*nSlice+4;
		face[i+nSlice*4].vert[1].vertIndex = i+4*nSlice+5;
		face[i+nSlice*4].vert[2].vertIndex= i+6*nSlice+7;
		face[i+nSlice*4].vert[3].vertIndex = i+6*nSlice+6;
		
	}
	for (i = 0; i < nSlice; i++) {
		face[i+nSlice*5].nVerts = 4;
		face[i+nSlice*5].vert = new VertexID[4];
		face[i+nSlice*5].vert[0].vertIndex = i+4*nSlice+4;
		face[i+nSlice*5].vert[1].vertIndex = i+4*nSlice+5;
		face[i+nSlice*5].vert[2].vertIndex= i+5*nSlice+6;
		face[i+nSlice*5].vert[3].vertIndex = i+5*nSlice+5;
	}

	for (i = 0; i < nSlice; i++) {
		face[i+nSlice*6].nVerts = 4;
		face[i+nSlice*6].vert = new VertexID[4];
		face[i+nSlice*6].vert[0].vertIndex = i+5*nSlice+5;
		face[i+nSlice*6].vert[1].vertIndex = i+5*nSlice+6;
		face[i+nSlice*6].vert[2].vertIndex= i+7*nSlice+8;
		face[i+nSlice*6].vert[3].vertIndex = i+7*nSlice+7;
		
	}
	face[nSlice*7].nVerts=4;
	face[nSlice*7].vert = new VertexID[4];
	face[nSlice*7].vert[0].vertIndex = 0;
	face[nSlice*7].vert[1].vertIndex = nSlice+1;
	face[nSlice*7].vert[2].vertIndex= nSlice*8+8;
	face[nSlice*7].vert[3].vertIndex = 6*nSlice+6;

	face[nSlice*7+1].nVerts=4;
	face[nSlice*7+1].vert = new VertexID[4];
	face[nSlice*7+1].vert[0].vertIndex =nSlice;
	face[nSlice*7+1].vert[1].vertIndex = 2*nSlice+1;
	face[nSlice*7+1].vert[2].vertIndex= nSlice*8+9;
	face[nSlice*7+1].vert[3].vertIndex = 7*nSlice+6;
	
	face[nSlice*7+2].nVerts=4;
	face[nSlice*7+2].vert = new VertexID[4];
	face[nSlice*7+2].vert[0].vertIndex =2*nSlice+2;
	face[nSlice*7+2].vert[1].vertIndex = 3*nSlice+3;
	face[nSlice*7+2].vert[2].vertIndex= nSlice*8+10;
	face[nSlice*7+2].vert[3].vertIndex = 7*nSlice+7;

	face[nSlice*7+3].nVerts=4;
	face[nSlice*7+3].vert = new VertexID[4];
	face[nSlice*7+3].vert[0].vertIndex =3*nSlice+2;
	face[nSlice*7+3].vert[1].vertIndex = 4*nSlice+3;
	face[nSlice*7+3].vert[2].vertIndex= nSlice*8+11;
	face[nSlice*7+3].vert[3].vertIndex = 8*nSlice+7;

	face[nSlice*7+4].nVerts=4;
	face[nSlice*7+4].vert = new VertexID[4];
	face[nSlice*7+4].vert[0].vertIndex =2*nSlice+1;
	face[nSlice*7+4].vert[1].vertIndex = 4*nSlice+3;
	face[nSlice*7+4].vert[2].vertIndex= 8*nSlice+11;
	face[nSlice*7+4].vert[3].vertIndex = 8*nSlice+9;

	face[nSlice*7+5].nVerts=4;
	face[nSlice*7+5].vert = new VertexID[4];
	face[nSlice*7+5].vert[0].vertIndex =nSlice+1;
	face[nSlice*7+5].vert[1].vertIndex = 3*nSlice+3;
	face[nSlice*7+5].vert[2].vertIndex= 8*nSlice+10;
	face[nSlice*7+5].vert[3].vertIndex = 8*nSlice+8;

	face[nSlice*7+6].nVerts=4;
	face[nSlice*7+6].vert = new VertexID[4];
	face[nSlice*7+6].vert[0].vertIndex =8*nSlice+8;
	face[nSlice*7+6].vert[1].vertIndex = 8*nSlice+9;
	face[nSlice*7+6].vert[2].vertIndex= 8*nSlice+11;
	face[nSlice*7+6].vert[3].vertIndex = 8*nSlice+10;

}

void Mesh::CreateSanNha(float fSize,float posX,float posZ)
{
	//int i;
	//float range = 60;

	numVerts = 7;
	pt = new Point3[numVerts];

	//for( i=0;i<6;i++){
	//	pt[i].set(  posX+ fSize*cos( i*range*DEG2RAD)  ,0, posZ+  fSize*sin(i*range*DEG2RAD) );	
	//}
	pt[0].set(posX+ fSize* cos(30*PI/180) , 0, posZ+ fSize*sin(30*PI/180) );
	//pt[1].set(posX+ fSize* cos(30*PI/180) , 0, posZ+ fSize/2);
	pt[1].set(posX , 0, posZ+ fSize);
	pt[2].set(posX - fSize*cos(30*PI/180)  , 0, posZ+  fSize*sin(30*PI/180));
	pt[3].set(posX - fSize*cos(30*PI/180)  , 0, posZ-  fSize*sin(30*PI/180));
	pt[4].set(posX  , 0, posZ- fSize);
	pt[5].set(posX+ fSize* cos(30*PI/180) , 0, posZ-  fSize*sin(30*PI/180));
	pt[6].set(posX,0,posZ);

	
	numFaces=3;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[4];
	face[0].vert[0].vertIndex = 6;
	face[0].vert[1].vertIndex = 0;
	face[0].vert[2].vertIndex = 1;
	face[0].vert[3].vertIndex = 2;


	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[4];
	face[1].vert[0].vertIndex = 6;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 3;
	face[1].vert[3].vertIndex = 4;
	

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[4];
	face[2].vert[0].vertIndex = 6;
	face[2].vert[1].vertIndex = 4;
	face[2].vert[2].vertIndex = 5;
	face[2].vert[3].vertIndex = 0;
	
}

///////////////////////////////////////////////////////////////////////

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
		
		//////////////////For test
		glPointSize(20);
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
void Mesh::DrawColorSanNha()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			if(f==0)
				ic =9;
			else if(f==1)
				ic=10;
			else
				ic=11;

			//ic = f % COLORNUM;


			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++){
		for (int v = 0; v < face[f].nVerts; v++){
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

////////////////////////////////
using namespace std;

#define PI			3.1415926

// Camera
float camera_angle ;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool	viewB4 = false;

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
float chotRadius2 =0.08 ;
float chotLength1 =  0.3;
float chotLength2 = 0.05;
float chotLength3 = 0;


float	cylinderRadius = 0.4;
float	cylinderHeight = 1.6;
float	cylinderRotateStep = 5;
float	cylinderTranslationStep = 0.05;
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
Mesh	sannha;
Mesh *p_sannha = new Mesh[600];
int dv =0;
float R_floor = 1;


float Rnho =0.3;
float chieuX= -Rnho,chieuZ = 0; 
bool ct = false; 


void mySpecialKey(int theKey, int x, int y) {
	if (theKey == GLUT_KEY_RIGHT) {
		camera_angle -= 0.1;
		if (camera_angle < 0)
			camera_angle += 360;
	}
	else if (theKey == GLUT_KEY_LEFT) {
		camera_angle += 0.1;
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

	glPushMatrix();

	if(bWireFrame)
		
		for(int i =0 ;i<dv;i++){
			p_sannha[i].DrawWireframe();
		}
	
	else

		for(int i =0 ;i<dv;i++){
			p_sannha[i].DrawColorSanNha();
		}


	glPopMatrix();
	
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


void shadowMatrix(float plane[], float light_pos[]) {
	float shadow_mat[16];
	float dot;

	//Finds dot, which is the product of the light vetcor and the plane's normal
	dot = plane[0] * light_pos[0] +
		plane[1] * light_pos[1] +
		plane[2] * light_pos[2] +
		plane[3] * light_pos[3];

	shadow_mat[0] = dot - light_pos[0] * plane[0];
	shadow_mat[4] = -light_pos[0] * plane[1];
	shadow_mat[8] = -light_pos[0] * plane[2];
	shadow_mat[12] = -light_pos[0] * plane[3];

	shadow_mat[1] = -light_pos[1] * plane[0];
	shadow_mat[5] = dot - light_pos[1] * plane[1];
	shadow_mat[9] = -light_pos[1] * plane[2];
	shadow_mat[13] = -light_pos[1] * plane[3];

	shadow_mat[2] = -light_pos[2] * plane[0];
	shadow_mat[6] = -light_pos[2] * plane[1];
	shadow_mat[10] = dot - light_pos[2] * plane[2];
	shadow_mat[14] = -light_pos[2] * plane[3];

	shadow_mat[3] = -light_pos[3] * plane[0];
	shadow_mat[7] = -light_pos[3] * plane[1];
	shadow_mat[11] = -light_pos[3] * plane[2];
	shadow_mat[15] = dot - light_pos[3] * plane[3];

	glMultMatrixf(shadow_mat);
}


void DisplayView(int nType, int left, int right, int top, int bottom)
{
	mySetupCameraVolume(nType);
	glViewport(left, top, right - left, bottom - top);

	camera_Y = camera_height;
	camera_X = camera_dis * cos(camera_angle);
	camera_Z = camera_dis * sin(camera_angle);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camera_X, camera_Y, camera_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	if (!viewB4)
		DisplayView(4, 0, screenWidth, 0, screenHeight);
	
	drawAxis();
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

	drawSanNha();
	
	
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
	glutCreateWindow("Le Van Chi ( 1510289 )"); // open the screen window

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


	
	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,i*2*cos(30*PI/180),-6*R_floor);
		dv++;
	}
	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,i*2*cos(30*PI/180),-3*R_floor);
		dv++;
	}
	for(int i =-10 ;i< 10;i++){
		//p_sannha[0].CreateSanNha(1,0,0);
		p_sannha[dv].CreateSanNha(R_floor,i*2*cos(30*PI/180),0);
		dv++;
		
	}
	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,i*2*cos(30*PI/180),3*R_floor);
		dv++;
	}
	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,i*2*cos(30*PI/180),6*R_floor);
		dv++;
	}

	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,cos(30*PI/180) * i*2 - cos(30*PI/180),  3*R_floor/2);
		dv++;
	}

	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,cos(30*PI/180) * i*2 - cos(30*PI/180),  3*R_floor/2 + 3*R_floor);
		dv++;

	}
	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,cos(30*PI/180) * i*2 - cos(30*PI/180),  3*R_floor/2 + 6*R_floor);
		dv++;

	}

	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,cos(30*PI/180) * i*2 - cos(30*PI/180),  3*R_floor/2 - 3*R_floor);
		dv++;

	}
	for(int i =-10 ;i< 10;i++){
		p_sannha[dv].CreateSanNha(R_floor,cos(30*PI/180) * i*2 - cos(30*PI/180),  3*R_floor/2 - 6*R_floor);
		dv++;

	}
	

	myInit();

	glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialKey);
	  
	glutMainLoop();
	return 0;
}

