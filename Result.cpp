#include "Result.h"

// Resultのコンストラクタ
Result::Result()
{
}

// Resultのデストラクタ
Result::~Result()
{
}

// Resultの初期化
void Result::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex, POINT *pcl)
{
	// テクスチャ描画(リザルト)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/92.jpg", &m_result_pD3DTexture)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		*tex = MessageBox(*pHWND, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// Resultの描画
void Result::Draw(LPDIRECT3DDEVICE9 *device)
{
	// リザルト
	VERTEX_2D result_vertex[4] = {
	{0,0,1,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,1,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

	// リザルト描画
	(*device)->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	(*device)->SetTexture(0, m_result_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&result_vertex[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

// Resultの解放
void Result::Uninit()
{
	// テクスチャの解放
	if (m_result_pD3DTexture != NULL)
	{
		m_result_pD3DTexture->Release();
		m_result_pD3DTexture = NULL;
	}
}

// Resultの更新
void Result::Update(int *scene)
{
	UpdateInput();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 1;
	}


}
