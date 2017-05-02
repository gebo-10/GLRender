#include <Mesh.h>
Mesh::Mesh()
{

}

Mesh::Mesh(aiMesh* paiMesh)
{
	Init(paiMesh);
}

Mesh::~Mesh()
{

}

void Mesh::Init(aiMesh* paiMesh)
{
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		vertex.push_back(paiMesh->mVertices[i].x);
		vertex.push_back(paiMesh->mVertices[i].y);
		vertex.push_back(paiMesh->mVertices[i].z);
	}
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pTexCoord = &(paiMesh->mTextureCoords[0][i]);
		if (pTexCoord ==NULL)
		{
			break;
		}
		uv.push_back(pTexCoord->x);
		uv.push_back(pTexCoord->y);
	}
	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
		const aiFace& Face = paiMesh->mFaces[i];
		index.push_back(Face.mIndices[0]);
		index.push_back(Face.mIndices[1]);
		index.push_back(Face.mIndices[2]);
	}
	for (unsigned int i=0;i<paiMesh->mNumVertices;i++)
	{
		const aiVector3D* norm = &(paiMesh->mNormals[i]);
		normal.push_back(norm->x);
		normal.push_back(norm->y);
		normal.push_back(norm->z);
	}
}
