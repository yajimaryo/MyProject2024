#pragma once

#include "scene.h"

class Loading : public Scene
{
private:
	static int m_StageNum;
public:
	static void SetLoadStage(int StageNum) { m_StageNum = StageNum; }

	void Init() override;
	void Update() override;
};