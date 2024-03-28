#include "main.h"
#include "scene.h"
#include "camera.h"
#include <algorithm>

void Scene::Draw(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (GameObject* object : m_GameObject[i])
		{
			(object)->Draw();
		}
	}
}
