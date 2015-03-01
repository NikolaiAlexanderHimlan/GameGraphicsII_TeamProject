//=============================================================================
//              Adopted from Franc Luna's CubeDemo sample project.
//
// Please use this file to add classes / inherit and create various vertex classes
//=============================================================================
#ifndef VERTEX_H
#define VERTEX_H
//=============================================================================
#include <d3dx9.h>
#include "../d3dUtil.h"
//=============================================================================
// Call in constructor and destructor, respectively, of derived application class.
void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();
//=============================================================================
struct VertexPos
{
	VertexPos()
		: pos(0.0f, 0.0f, 0.0f)
		, norm(0.0f, 0.0f, 0.0f)
		, tex(0.0f, 0.0f)
		{}
	VertexPos(float x, float y, float z
		, float nx, float ny, float nz
		, float u, float v
		) : pos(x,y,z)
		, norm(nx,ny,nz)
		, tex(u,v)
		{}
	VertexPos(const D3DXVECTOR3& v
		, const D3DXVECTOR3& n
		, const D3DXVECTOR2& uv
		) : pos(v)
		, norm(n)
		, tex(uv)
		{}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	D3DXVECTOR2 tex;
	static IDirect3DVertexDeclaration9* Decl;
};
//=============================================================================
#endif // VERTEX_H