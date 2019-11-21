#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// �e�N�X�`���`��(�^�C�g��)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/4.png", &m_title_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

void Title::Draw(LPDIRECT3DDEVICE9 *device)
{
	// �^�C�g��
	VERTEX_2D title_vertex[4] = {
	{0,0,1,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,1,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

	// �^�C�g���`��
	(*device)->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	(*device)->SetTexture(0, m_title_pD3DTexture);

	// (*device)->DrawPrimitiveUP���Ă�
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&title_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

void Title::Update(int *scene)
{
	UpdateInput();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 2;
		PlaySound(SOUND_LABEL_BGM000);
	}
}

void Title::Uninit()
{
	// �e�N�X�`���̉��
	if (m_title_pD3DTexture != NULL)
	{
		m_title_pD3DTexture->Release();
		m_title_pD3DTexture = NULL;
	}
}
