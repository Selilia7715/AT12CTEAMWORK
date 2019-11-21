#pragma once
#include"Main.h"
#include "Input.h"
#include "BaseScene.h"
#include"XAudio2.h"

// タイトル
class Title :public BaseScene
{
public:

	LPDIRECT3DTEXTURE9  m_title_pD3DTexture = NULL;    // テクスチャを格納する変数(タイトル)

	Title();
	~Title();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex,POINT *pcl);     // 初期化
	void Draw(LPDIRECT3DDEVICE9 *device);                           // 描画
	void Update(int *scene);                                        // 更新
	void Uninit(void);                                              // 解放

};

