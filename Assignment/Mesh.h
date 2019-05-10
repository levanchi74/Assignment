#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


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

#endif