#pragma once
#include "Main.h"

class BaseScene
{
public:
	BaseScene();
	~BaseScene();

	virtual void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl) = 0;     // 初期化

	virtual	void Draw(LPDIRECT3DDEVICE9 *device) = 0;                           // 描画

	virtual	void Update(int *scene) = 0;                                        // 更新

	virtual	void Uninit(void) = 0;                                              // 解放


};

