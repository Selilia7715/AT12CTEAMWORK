#include "Result.h"

// Result�̃R���X�g���N�^
Result::Result()
{
}

// Result�̃f�X�g���N�^
Result::~Result()
{
}

// Result�̏�����
void Result::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex, POINT *pcl)
{
	// �e�N�X�`���`��(���U���g)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/92.jpg", &m_result_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "���U���g�̃e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	result_vertex[0].x = 0.0f;
	result_vertex[0].y = 640.0f;
	result_vertex[0].z = 0.0f;

	result_vertex[1].x = SCREEN_WIDTH;
	result_vertex[1].y = 640.0f;
	result_vertex[1].z = 0.0f;

	result_vertex[2].x = 0.0f;
	result_vertex[2].y = 720.0f;
	result_vertex[2].z = 0.0f;

	result_vertex[3].x = SCREEN_WIDTH;
	result_vertex[3].y = 720.0f;
	result_vertex[3].z = 0.0f;

	// RHW�̒l
	result_vertex[0].rhw = 1.0f;
	result_vertex[1].rhw = 1.0f;
	result_vertex[2].rhw = 1.0f;
	result_vertex[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	result_vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	result_vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	result_vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	result_vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	result_vertex[0].u = 0.0f;
	result_vertex[0].v = 0.0f;
	result_vertex[1].u = 1.0f;
	result_vertex[1].v = 0.0f;
	result_vertex[2].u = 0.0f;
	result_vertex[2].v = 1.0f;
	result_vertex[3].u = 1.0f;
	result_vertex[3].v = 1.0f;

}

// Result�̕`��
void Result::Draw(LPDIRECT3DDEVICE9 *device)
{
	// ���U���g�`��
	(*device)->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	(*device)->SetTexture(0, m_result_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&result_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

// Result�̉��
void Result::Uninit()
{
	// �e�N�X�`���̉��
	if (m_result_pD3DTexture != NULL)
	{
		m_result_pD3DTexture->Release();
		m_result_pD3DTexture = NULL;
	}
}

// Result�̍X�V
void Result::Update(int *scene)
{
	UpdateInput();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 1;
	}
}
