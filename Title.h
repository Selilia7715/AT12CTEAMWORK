#pragma once
#include"Main.h"
#include "Input.h"
#include"XAudio2.h"

// �^�C�g��
class Title 
{
private: // �t���O�p
	bool StartFlag;         // Start�{�^���\���؂�ւ�
	bool OptionFlag;        // Option�{�^���\���؂�ւ�

	bool S_Push_Button;     // Start�����ꂽ���ǂ���
	bool OP_Push_Button;    // Option�����ꂽ���ǂ���

	bool Button_Change;     // �{�^���؂�ւ�

	bool OP_Change;         // �I�v�V������ʂɐ؂�ւ��邩�ǂ���
	bool OP_Button_Change;  // �I�v�V������ʂł̃{�^���؂�ւ�

private: // �ϐ��p
	int cnt = 0;   // �J�E���g

private: // �^�C�g����ʂ̃X�^�[�g�{�^��(UI)

	VERTEX_2D title_StartButton[VERTEX_MAX];                // �X�^�[�g�{�^��
	D3DVECTOR StartButtonPosition;                          // �X�^�[�g�{�^�����W
	LPDIRECT3DTEXTURE9  StartButton_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�(�X�^�[�g�{�^��)
	LPDIRECT3DTEXTURE9  StartButton_pD3DTexture2 = NULL;    // �e�N�X�`�����i�[����ϐ�(�X�^�[�g�{�^��)


private: // �^�C�g����ʂ̃I�v�V�����{�^��(UI)

	VERTEX_2D title_OptionButton[VERTEX_MAX];                // �I�v�V�����{�^��
	D3DVECTOR OptionButtonPosition;                          // �I�v�V�����{�^�����W
	LPDIRECT3DTEXTURE9  OptionButton_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�(�I�v�V�����{�^��)
	LPDIRECT3DTEXTURE9  OptionButton_pD3DTexture2 = NULL;    // �e�N�X�`�����i�[����ϐ�(�I�v�V�����{�^��)

private: // �I�v�V�������
	// Option
	VERTEX_2D Option[VERTEX_MAX];                      // �I�v�V����
	D3DVECTOR OptionPosition;                          // �I�v�V�����{�^�����W

	// BGM
	VERTEX_2D BGM[VERTEX_MAX];                         // BGM
	D3DVECTOR BGMPosition;                             // BGM���W
	LPDIRECT3DTEXTURE9  BGM_pD3DTexture = NULL;        // �e�N�X�`�����i�[����ϐ�(BGM)
	LPDIRECT3DTEXTURE9  BGM__Bar_pD3DTexture = NULL;   // �e�N�X�`�����i�[����ϐ�(BGM�̃o�[)

	// SE
	VERTEX_2D SE[VERTEX_MAX];                          // SE
	D3DVECTOR SEPosition;                              // SE���W
	LPDIRECT3DTEXTURE9  SE_pD3DTexture = NULL;         // �e�N�X�`�����i�[����ϐ�(SE)
	LPDIRECT3DTEXTURE9  SE_Bar_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�(SE�̃o�[)

public: // �^�C�g����ʂ̔w�i

	VERTEX_2D title_vertex[VERTEX_MAX];                // �^�C�g��
	LPDIRECT3DTEXTURE9  title_pD3DTexture = NULL;    // �e�N�X�`�����i�[����ϐ�(�^�C�g��)

	Title();
	~Title();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex,POINT *pcl);     // ������
	void Draw(LPDIRECT3DDEVICE9 *device);                                      // �`��
	void Update(int *scene);                                                   // �X�V
	void Uninit(void);                                                         // ���


};

