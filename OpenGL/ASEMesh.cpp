#include "ASEMesh.h"

using namespace ASEMeshes;

ASEMesh::ASEMesh(const char* _fileName) {
	FileName = gcnew String(_fileName);
	Materials = gcnew List<Material^>();
	GeoObjects = gcnew List<GeoObject^>();
}