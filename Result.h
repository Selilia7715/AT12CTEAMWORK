#pragma once
#include"Main.h"
#include "Input.h"

// Result
class Result
{
public:
	VERTEX_2D result_vertex[VERTEX_MAX];     // tileの赤

	LPDIRECT3DTEXTURE9  m_result_pD3DTexture = NULL;    // テクスチャを格納する変数(リザルト)

	Result();
	~Result();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex, POINT *pcl);     // 初期化
	void Draw(LPDIRECT3DDEVICE9 *device);                           // 描画
	void Update(int *scene);                                        // 更新
	void Uninit(void);                                              // 解放

};

