#pragma once

#include "scene.h"

class Manager
{
private:
	static Manager* m_pInstance;
	static Scene* m_Scene;
	static Scene* m_NextScene;
	static bool m_End;

private:
	Manager() {}
	~Manager() {}

public:
	static Manager* GetInstance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new Manager;
		}
		return m_pInstance;
	}

	static void DeleteInstance(void) {
		delete m_pInstance;
	}

	static void GameEnd() { m_End = true; }
	static bool IsGameEnd() { return m_End; }

	void Init();
	void Uninit();
	void Update();
	void Draw();

	Scene* GetScene() { return m_Scene; }


	template <typename T>
	void SetScene()
	{
		m_NextScene = new T();
	}
};