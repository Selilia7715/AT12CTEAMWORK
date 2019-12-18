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
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/Pic/92.jpg", &m_result_pD3DTexture)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		*tex = MessageBox(*pHWND, "リザルトのテクスチャロード失敗", "失敗", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}

	result_vertex[0].x = 0.0f;
	result_vertex[0].y = 640.0f;
	result_vertex[0].z = 0.0f;

	result_vertex[1].x = SCREEN_WIDTH;
	result_vertex[1].y = 640.0f;
	result_vertex[1].z = 0.0f;

	result_vertex[2].x = 0.0f;
	result_vertex[2].y = 720.0f;
	result_vertex[2].z = 0.0f;

	result_vertex[3].x = SCREEN_WIDTH;
	result_vertex[3].y = 720.0f;
	result_vertex[3].z = 0.0f;

	// RHWの値
	result_vertex[0].rhw = 1.0f;
	result_vertex[1].rhw = 1.0f;
	result_vertex[2].rhw = 1.0f;
	result_vertex[3].rhw = 1.0f;

	// ディフューズ色の設定
	result_vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	result_vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	result_vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	result_vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	result_vertex[0].u = 0.0f;
	result_vertex[0].v = 0.0f;
	result_vertex[1].u = 1.0f;
	result_vertex[1].v = 0.0f;
	result_vertex[2].u = 0.0f;
	result_vertex[2].v = 1.0f;
	result_vertex[3].u = 1.0f;
	result_vertex[3].v = 1.0f;

}

// Resultの描画
void Result::Draw(LPDIRECT3DDEVICE9 *device)
{
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
