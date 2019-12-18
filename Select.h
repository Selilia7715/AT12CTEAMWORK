#pragma once
#include"Main.h"
#include "Input.h"


// SelectStage
class SelectStage 
{
public:
	VERTEX_2D select_vertex[VERTEX_MAX];     // tile�̐�

	LPDIRECT3DTEXTURE9  m_select_pD3DTexture = NULL;    // �e�N�X�`�����i�[����ϐ�(���U���g)

	SelectStage();
	~SelectStage();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
	void Draw(LPDIRECT3DDEVICE9 *device);                           // �`��
	void Update(int *scene);                                        // �X�V
	void Uninit(void);                                              // ���


};

