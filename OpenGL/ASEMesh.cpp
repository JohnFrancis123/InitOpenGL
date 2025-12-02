#include "ASEMesh.h"

using namespace ASEMeshes;

ASEMesh::ASEMesh(const char* _fileName)
{
	FileName = gcnew String(_fileName);
	Materials = gcnew List<Material^>();
	GeoObjects = gcnew List<GeoObject^>();
}

void ASEMesh::ParseASEFile()
{
	String^ ASEFile = File::ReadAllText(FileName);
	ASEFile = ASEFile->Replace("\r\n", String::Empty);
	ASEFile = ASEFile->Replace('\t', ' ');

	cli::array<String^>^ splitTerm = gcnew cli::array<String^>(1);
	splitTerm[0] = "*MATERIAL ";
	cli::array<String^>^ MaterialSections = ASEFile->Split(splitTerm, StringSplitOptions::RemoveEmptyEntries);
	ParseMaterials(MaterialSections);

	splitTerm[0] = "*GEOOBJECT {";
	cli::array<String^>^ GeoObjectsSection = ASEFile->Split(splitTerm, StringSplitOptions::RemoveEmptyEntries);
	ParseGeoObjects(GeoObjectsSection);
}

void ASEMesh::ExtractVectorList(List<Vec3^>^ _list, String^ _tag, cli::array<String^>^ _lines, int& _lineFound)
{
	String^ info;
	while ((info = ExtractValue(_lines, _tag, _lineFound)) != String::Empty)
	{
		info = info->Remove(0, info->IndexOf('(') + 1);
		_list->Add(ParseStringToVec3(info));
	}
}

Vec3^ ASEMesh::ParseStringToVec3(String^ _vectorS)
{
	cli::array<String^>^ vecS = _vectorS->Split(' ');
	return gcnew Vec3(float::Parse(vecS[0]), float::Parse(vecS[1]), float::Parse(vecS[2]));
}

String^ ASEMesh::ExtractValue(cli::array<String^>^ _lines, String^ _tag, int& _lineFound)
{
	while (_lineFound < _lines->Length - 1)
	{
		_lineFound++;
		if (_lines[_lineFound]->Contains(_tag))
		{
			String^ s = _lines[_lineFound];
			s = s->Replace(_tag, String::Empty);
			s = s->Replace("\"", String::Empty);
			s = s->Trim();
			return s;
		}
	}

	_lineFound = -1;
	return String::Empty;
}

void ASEMesh::ParseMaterials(cli::array<String^>^ _materials)
{
	for (int count = 1; count < _materials->Length; count++)
	{
		int lineFound = -1;
		cli::array<String^>^ lines = _materials[count]->Split('\n');
		Material^ m = gcnew Material();

		m->Index = int::Parse(ExtractValue(lines, "*", lineFound));
		m->Name = ExtractValue(lines, "*MATERIAL_NAME", lineFound);
		m->Class = ExtractValue(lines, "*MATERIAL_CLASS", lineFound);
		m->AmbientColor = ParseStringToVec3(ExtractValue(lines, "*MATERIAL_AMBIENT ", lineFound));
		m->DiffuseColor = ParseStringToVec3(ExtractValue(lines, "*MATERIAL_DIFFUSE ", lineFound));
		m->SpecularColor = ParseStringToVec3(ExtractValue(lines, "*MATERIAL_SPECULAR ", lineFound));
		m->Shine = float::Parse(ExtractValue(lines, "*MATERIAL_SHINE", lineFound));
		m->ShineStrength = float::Parse(ExtractValue(lines, "*MATERIAL_SHINESTRENGTH", lineFound));
		m->Transparency = float::Parse(ExtractValue(lines, "*MATERIAL_TRANSPARENCY", lineFound));
		m->WireSize = float::Parse(ExtractValue(lines, "*MATERIAL_WIRESIZE", lineFound));
		m->Shading = ExtractValue(lines, "*MATERIAL_SHADING", lineFound);

		cli::array<String^>^ qx = gcnew cli::array<String^>(1);
		qx[0] = "\n *MAP_";
		cli::array<String^>^ maps = _materials[count]->Split(qx, StringSplitOptions::RemoveEmptyEntries);
		ParseMaps(maps, m);

		Materials->Add(m);
	}
}

void ASEMesh::ParseMaps(cli::array<String^>^ _maps, Material^ _material)
{
	for (int count = 1; count < _maps->Length; count++)
	{
		int lineFound = -1;
		cli::array<String^>^ lines = _maps[count]->Split('\n');
		Map^ m = gcnew Map();

		m->Name = ExtractValue(lines, "{", lineFound);
		m->TextureFileName = ExtractValue(lines, "*BITMAP", lineFound);
		m->UVW_U_Offset = float::Parse(ExtractValue(lines, "*UVW_U_OFFSET", lineFound));
		m->UVW_V_Offset = float::Parse(ExtractValue(lines, "*UVW_V_OFFSET", lineFound));
		m->UVW_U_Tiling = float::Parse(ExtractValue(lines, "*UVW_U_TILING", lineFound));
		m->UVW_V_Tiling = float::Parse(ExtractValue(lines, "*UVW_V_TILING", lineFound));

		_material->Maps->Add(m);
	}
}