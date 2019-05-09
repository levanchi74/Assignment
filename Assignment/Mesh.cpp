#include "stdafx.h"
#include "Mesh.h"
#include <math.h>

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

void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++){
		for (int v = 0; v < face[f].nVerts; v++){
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}




