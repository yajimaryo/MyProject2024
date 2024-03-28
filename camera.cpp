
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include "input.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (player)
	{
		D3DXVECTOR3 pos = player->GetPosition();


		// �O��̃}�E�X���W
		static POINT prevMousePos;

		// ���݂̃}�E�X���W���擾
		POINT currentMousePos;
		GetCursorPos(&currentMousePos);

		// �}�E�X�̈ړ��ʂ��v�Z
		int deltaX = 300 - prevMousePos.x;
		int deltaY = 300 - prevMousePos.y;

		// �}�E�X���W��ۑ�
		prevMousePos = currentMousePos;

		// �}�E�X�ړ��ɉ����ăJ�����̉�]�ʂ��X�V
		float rotationSpeed = -0.002f; // ��]���x����
		m_Rotation.y += deltaX * rotationSpeed; // �������̉�]
		m_Rotation.x += deltaY * rotationSpeed; // �c�����̉�]
		m_Up += deltaY * rotationSpeed;

		if (m_Up >= 10.0f)
			m_Up = 10.0f;

		if (m_Up <= -3.0f)
			m_Up = -3.0f;

		if (m_Peek)
		{
			// FPS
			m_Position = pos + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
			D3DXVECTOR3 forward = D3DXVECTOR3(sinf(m_Rotation.y + D3DX_PI), m_Up - 1.5f, cosf(m_Rotation.y + D3DX_PI));
			m_Target = m_Position - forward; // �J�����̒����_���X�V
		}
		else
		{
			//TPS
			m_Target = pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
			m_Position = pos + D3DXVECTOR3(0.0f, m_Up, 0.0f);
			m_Position += D3DXVECTOR3(sinf(m_Rotation.y + D3DX_PI), 0.0f, cosf(m_Rotation.y + D3DX_PI)) * 4.0f;
		}

		SetCursorPos(300, 300);
	}

	


	//�J�����V�F�C�N
	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.8f;
}


void Camera::Draw()
{

	//�r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 position = m_Position + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);

	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

	Renderer::SetCameraPosition(m_Position);
}


bool Camera::CheckView(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	//���ʔ���
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;

		D3DXVec3Normalize(&v1,&v1);
		D3DXVec3Normalize(&v2, &v2);


		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < -Size.x)
		{
			return false;
		}
	}

	//�E�ʔ���
	{
		v1 = wpos[3] - m_Position;
		v2 = wpos[1] - m_Position;

		D3DXVec3Normalize(&v1, &v1);
		D3DXVec3Normalize(&v2, &v2);

		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < -Size.x)
		{
			return false;
		}
	}

	return true;
}
