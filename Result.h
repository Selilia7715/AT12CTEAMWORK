#pragma once
#include"Main.h"
#include "BaseScene.h"
#include "Input.h"

// Result
class Result :public BaseScene
{
public:

	LPDIRECT3DTEXTURE9  m_result_pD3DTexture = NULL;    // �e�N�X�`�����i�[����ϐ�(���U���g)

	Result();
	~Result();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex, POINT *pcl);     // ������
	void Draw(LPDIRECT3DDEVICE9 *device);                           // �`��
	void Update(int *scene);                                        // �X�V
	void Uninit(void);                                              // ���

};

