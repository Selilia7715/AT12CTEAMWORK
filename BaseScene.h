#pragma once
#include "Main.h"

class BaseScene
{
public:
	BaseScene();
	~BaseScene();

	virtual void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl) = 0;     // ‰Šú‰»

	virtual	void Draw(LPDIRECT3DDEVICE9 *device) = 0;                           // •`‰æ

	virtual	void Update(int *scene) = 0;                                        // XV

	virtual	void Uninit(void) = 0;                                              // ‰ğ•ú


};

