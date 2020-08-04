#pragma once
class ResourceManager
{
protected:
	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager &){}
	ResourceManager& operator =(const ResourceManager &){}
public:
	static void CreatInstance()
	{
		if (ms_pInstance == NULL)
			ms_pInstance = new ResourceManager;
	}
	static ResourceManager * GetInstance()
	{
		return ms_pInstance;
	}
	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
	void LoadResources(char *path);
protected:
	static ResourceManager * ms_pInstance;
private:
	char m_type;
	int m_ID;
	int m_numberObject;
	char m_FILE;
	char m_TILINGMODE;
	char m_STATES;
};

