#pragma once

#include <list>
#include <map>

class AnimationModel;
class Model;

class ResourceManager
{
private:
	static ResourceManager* m_pInstance;

	static std::list<Model*> m_Models;
	//static std::map<char*, AnimationModel*> m_Models;
	static std::map<char*, ID3D11ShaderResourceView*> m_Textures;

private:
	ResourceManager(){}
	~ResourceManager(){}

public:
	static ResourceManager* GetInstance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new ResourceManager;
		}
		return m_pInstance;
	}

	static void DeleteInstance(void);

	Model* GetResouseModel(char* FileName);
	//AnimationModel* GetResouseModel(char* FileName);
	ID3D11ShaderResourceView* GetResouseTexture(char* FileName);
};