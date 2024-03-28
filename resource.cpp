#include "main.h"
#include "renderer.h"
#include "resource.h"
#include "model.h"
#include "animationModel.h"

ResourceManager* ResourceManager::m_pInstance = nullptr;
std::list<Model*> ResourceManager::m_Models = {};
std::map<char*, ID3D11ShaderResourceView*> ResourceManager::m_Textures = {};

void ResourceManager::DeleteInstance(void)
{
	for (Model* it : m_Models)
	{
		it->Unload();
		delete (it);
	}
	m_Models.clear();

	for (auto& pair : m_Textures) 
	{
		pair.second->Release(); // ���\�[�X�����
	}
	m_Textures.clear(); // �}�b�v�̗v�f���N���A

	delete m_pInstance;
}

Model * ResourceManager::GetResouseModel(char* FileName)
{
	for (Model* it : m_Models)
	{
		if (it->GetFileName() == FileName)
			return (it);
	}
	
	Model* model = new Model;
	model->Load(FileName);

	m_Models.push_back(model);

	return model;
}

ID3D11ShaderResourceView * ResourceManager::GetResouseTexture(char* FileName)
{
	if (m_Textures.find(FileName) != m_Textures.end())
	{
		return m_Textures[FileName];
	}
	else
	{
		ID3D11ShaderResourceView* texture;

		//�e�N�X�`���ǂݍ���
		D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
			FileName,
			NULL,
			NULL,
			&texture,
			NULL);
		assert(texture);

		m_Textures[FileName] = texture;

		return m_Textures[FileName];
	}

	return nullptr;
}
