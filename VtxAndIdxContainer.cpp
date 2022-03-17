#include "VtxAndIdxContainer.h"

VtxAndIdxContainer::VtxAndIdxContainer(ID3D10Device* pDevice)
{
}

VtxAndIdxContainer::~VtxAndIdxContainer()
{
	for (auto info : m_VtxAndIdxArray) {
		SAFE_DELETE(info.second);
	}
}

VtxAndIdxInfo* VtxAndIdxContainer::CreateFromBlueprint(ID3D10Device *pDevice, VtxAndIdxBlueprint* blueprint)
{
	VtxAndIdxInfo* ret = new VtxAndIdxInfo;
	//既に読み込み済みの場合それを返す
	if (m_VtxAndIdxArray.count(blueprint->m_ObjName) != 0) {
		ret = m_VtxAndIdxArray[blueprint->m_ObjName];
		return ret;
	}
	if (blueprint->m_ObjFileName != "") {
		int vertexNum = 0;
		int faceNum = 0;;
		int normNum = 0;
		float x, y, z;
		int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
		int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
		int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
		int vn1 = 0, vn2 = 0, vn3 = 0, vn4 = 0;
		char key[200] = { 0 };
		FILE* fp = NULL;
		errno_t error;
		const char* fileName = blueprint->m_ObjFileName.c_str();
		const char* startKeyword = blueprint->m_StartKeyword.c_str();
		const char* endKeyword = blueprint->m_EndKeyword.c_str();
		error = fopen_s(&fp, fileName, "rt");

		if (error != 0)
		{
			MessageBox(0, L"ファイル読み込み失敗", NULL, MB_OK);
			exit(0);
		}
		bool flg = false;
		while (!feof(fp)){
			fscanf_s(fp, "%s ", key, sizeof(key));

			if (strcmp(key, "o") == 0){
				fscanf_s(fp, "%s", key, sizeof(key));

				if (strcmp(key, startKeyword) == 0)
				{
					flg = true;
				}
				if (strcmp(key, endKeyword) == 0)
				{
					break;
				}
			}
			if (!flg)continue;

			if (strcmp(key, "v") == 0){
				vertexNum++;
			}
			if (strcmp(key, "vn") == 0){
				normNum++;
			}
			if (strcmp(key, "f") == 0){
				faceNum++;
			}
		}
		flg = false;

		Vertex* vertices = new Vertex[vertexNum];
		int* indices = new int[faceNum * 6];

		fseek(fp, SEEK_SET, 0);
		int vertexCnt = 0;
		int indexCnt = 0;
		int normCnt = 0;

		flg = startKeyword == "" ? true : false;
		float min_X = 100.0f, min_Y = 100.0f, min_Z = 100.0f, max_X = -100.0f, max_Y = -100.0f, max_Z = -100.0f;
		int off = 247;
		if (blueprint->m_ObjName == "Pin")off = 5457;
		while (!feof(fp)){
			//キーワード読み込み
			ZeroMemory(key, sizeof(key));
			fscanf_s(fp, "%s ", key, sizeof(key));
			if (strcmp(key, "o") == 0){
				fscanf_s(fp, "%s", key, sizeof(key));
				if (strcmp(key, startKeyword) == 0){
					flg = true;
				}
				if (strcmp(key, endKeyword) == 0){
					break;
				}
			}
			if (!flg)continue;
			if (strcmp(key, "vn") == 0){
				fscanf_s(fp, "%f %f %f", &x, &y, &z);
				vertices[normCnt].Normal.x = -x;
				vertices[normCnt].Normal.y = y;
				vertices[normCnt].Normal.z = z;
				normCnt++;
			}

			if (strcmp(key, "v") == 0)
			{
				fscanf_s(fp, "%f %f %f", &x, &y, &z);
				vertices[vertexCnt].Pos.x = -x;
				vertices[vertexCnt].Pos.y = y;
				vertices[vertexCnt].Pos.z = z;
				min_X = fmin(min_X, -x);
				min_Y = fmin(min_Y, y);
				min_Z = fmin(min_Z, z);
				max_X = fmax(max_X, -x);
				max_Y = fmax(max_Y, y);
				max_Z = fmax(max_Z, z);

				vertexCnt++;
			}

			if (strcmp(key, "f") == 0)
			{
				fscanf_s(fp, "%d//%d %d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3, &v4, &vn4);
				indices[indexCnt] = v1 - off;
				indexCnt++;
				indices[indexCnt] = v2 - off;
				indexCnt++;
				indices[indexCnt] = v3 - off;
				indexCnt++;
				if (v4)
				{
					indices[indexCnt] = v4 - off;
					indexCnt++;
					indices[indexCnt] = v3 - off;
					indexCnt++;
					indices[indexCnt] = v1 - off;
					indexCnt++;
				}
			}

		}
		fclose(fp);
		int idxNum = indexCnt;
		D3DXVECTOR3 offset = {(max_X+min_X)/2, (max_Y+min_Y)/2, (max_Z+min_Z)/2};

		ret->m_Offset = offset;
		ret->m_IndexNum = idxNum;
		CreateVertexBuffer(pDevice, vertices, vertexCnt, ret);
		CreateIndexBuffer(pDevice, indices, indexCnt, ret);
		if (blueprint->m_ObjName == "Pin")
		{

			int i = 0;
		}
		SAFE_DELETE_ARRAY(indices);
		SAFE_DELETE_ARRAY(vertices);
	}
	else {
		int idxNum = blueprint->m_IdxNum;
		D3DXVECTOR3 offset = { 0,0,0 };
		Vertex* vertices = new Vertex[blueprint->m_VtxNum];
		for (int i = 0; i < blueprint->m_VtxNum; i++) {
			vertices[i] = blueprint->m_Vertices[i];
		}
		int* indices = new int[blueprint->m_IdxNum];
		for (int i = 0; i < blueprint->m_IdxNum; i++) {
			indices[i] = blueprint->m_Indices[i];
		}
		CreateVertexBuffer(pDevice, vertices, blueprint->m_VtxNum, ret);
		CreateIndexBuffer(pDevice, indices, blueprint->m_IdxNum, ret);
		ret->m_IndexNum = blueprint->m_IdxNum;
		ret->m_Offset = offset;
		SAFE_DELETE_ARRAY(indices);
		SAFE_DELETE_ARRAY(vertices);
	}
	m_VtxAndIdxArray.insert({ blueprint->m_ObjName, ret });
	return ret;

}

void VtxAndIdxContainer::CreateVertexBuffer(ID3D10Device* pDevice, Vertex* vertices, int vCount, VtxAndIdxInfo *info)
{
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vCount;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;

	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, &info->m_pVertexBuffer)))
	{
		exit(0);
	}
	return;
}

void VtxAndIdxContainer::CreateIndexBuffer(ID3D10Device* pDevice, int* indices, int iCount, VtxAndIdxInfo *info)
{
	D3D10_BUFFER_DESC bd;

	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * iCount;
	bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D10_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = indices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	if (FAILED(pDevice->CreateBuffer(&bd, &InitData, &info->m_pIndexBuffer)))
	{
		exit(0);
	}
	return;
}