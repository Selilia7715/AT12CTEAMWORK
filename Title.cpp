#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// テクスチャ描画(タイトル)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/4.png", &m_title_pD3DTexture)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		*tex = MessageBox(*pHWND, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

void Title::Draw(LPDIRECT3DDEVICE9 *device)
{
	// タイトル
	VERTEX_2D title_vertex[4] = {
	{0,0,1,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,1,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

	// タイトル描画
	(*device)->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	(*device)->SetTexture(0, m_title_pD3DTexture);

	// (*device)->DrawPrimitiveUPを呼ぶ
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&title_vertex[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

void Title::Update(int *scene)
{
	UpdateInput();

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 2;
		PlaySound(SOUND_LABEL_BGM000);
	}
}

void Title::Uninit()
{
	// テクスチャの解放
	if (m_title_pD3DTexture != NULL)
	{
		m_title_pD3DTexture->Release();
		m_title_pD3DTexture = NULL;
	}
}
