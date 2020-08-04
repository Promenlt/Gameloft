//
//#include "stdafx.h"
//#include "ResourceManager.h"
//
//ResourceManager * ResourceManager::ms_pInstance = NULL;
//ResourceManager::ResourceManager()
//{
//}
//ResourceManager::~ResourceManager()
//{
//}
//void ResourceManager::LoadResources(char *path) {
//	FILE *f;
//	f = fopen(path, "r");
//	fscanf("#%c: %d\n", &m_type, &m_numberObject);
//	if (m_type == 'Models')
//	{
//		for (int i = 0; i < m_numberObject; i++) {
//			fscanf("ID %d\n", &m_ID);
//			fscanf("FILE %c\n", &m_FILE);
//		}
//	}
//	else if (m_type == '2D Textures') {
//		for (int i = 0; i < m_numberObject; i++) {
//			fscanf("ID %d\n", &m_ID);
//			fscanf("FILE %c\n", &m_FILE);
//			fscanf("%c\n",&m_TILINGMODE);
//		}
//	}
//	else if (m_type == 'Cube Textures')
//	{
//		for (int i = 0; i < m_numberObject; i++) {
//			fscanf("ID %d\n", &m_ID);
//			fscanf("FILE %c\n", &m_FILE);
//			fscanf("%c\n", &m_TILINGMODE);
//		}
//	}
//	else if (m_type == 'Shaders') {
//		for (int i = 0; i < m_numberObject; i++) {
//			fscanf("ID %d\n", &m_ID);
//			fscanf("FILE %c\n", &m_FILE);
//			fscanf("%c\n", &m_TILINGMODE);
//		}
//	}
//}
