#pragma once
#include"Main.h"
#include "Input.h"
#include "BaseScene.h"
#include"XAudio2.h"

// �^�C�g��
class Title :public BaseScene
{
public:

	LPDIRECT3DTEXTURE9  m_title_pD3DTexture = NULL;    // �e�N�X�`�����i�[����ϐ�(�^�C�g��)

	Title();
	~Title();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex,POINT *pcl);     // ������
	void Draw(LPDIRECT3DDEVICE9 *device);                           // �`��
	void Update(int *scene);                                        // �X�V
	void Uninit(void);                                              // ���

};

