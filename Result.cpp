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
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/92.jpg", &m_result_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// Result�̕`��
void Result::Draw(LPDIRECT3DDEVICE9 *device)
{
	// ���U���g
	VERTEX_2D result_vertex[4] = {
	{0,0,1,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,1,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

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
