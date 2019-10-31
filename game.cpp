#include	<d3dx9.h>
#include	"main.h"
#include	"game.h"
#include	"input.h"

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = nullptr;			// Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = nullptr;		// Deviceオブジェクト(描画に必要)
LPD3DXFONT			g_pD3DXFont = nullptr;		// フォントへのポインタ

D3DXMATRIX			g_view;						// ビュー変換行列
D3DXMATRIX			g_world;					// ワールド変換行列
D3DXMATRIX			g_projection;				// プロジェクション変換行列				
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.BackBufferCount = 1;						// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う

	if (bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリングする
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャＵ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャＶ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大時の補間設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小時の補間設定

																			// テクスチャステージの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);					//   光源計算オフ（光源計算を切るとDIFFUSE色がそのままでる）

	// 情報表示用フォントを設定
	// pDevice         : デバイスへのポインタ
	// Height          : 文字の高さ
	// Width           : 文字の幅
	// Weight          : フォントの太さ
	// MipLevels       : ミップマップレベル数
	// Italic          : イタリックフォント
	// CharSet         : フォントの文字セット
	// OutputPrecision : 実際のフォントと目的のフォントのサイズおよび特性の一致方法を指定
	// Quality         : 実際のフォントと目的のフォントとの一致方法を指定
	// PitchAndFamily  : ピッチとファミリインデックス
	// pFacename       : フォントの名前を保持する文字列
	// ppFont          : フォントへのポインタ
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

	// ＤＩＲＥＣＴ　ＩＮＰＵＴ初期化
	InitInput(hInstance, hWnd);

	D3DXMatrixPerspectiveFovLH(&g_projection, D3DX_PI / 4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &g_projection);

	D3DXVECTOR3 eye = { 0,0,-100 };
	D3DXVECTOR3 lookat = { 0,0,0 };
	D3DXVECTOR3 up = { 0,1,0 };
	D3DXMatrixLookAtLH(&g_view, &eye, &lookat, &up);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_view);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// ＤＩＲＥＣＴ　ＩＮＰＵＴ終了処理
	UninitInput();

	if (g_pD3DXFont != NULL)
	{// 情報表示用フォントの解放
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}

	if (g_pD3DDevice != NULL)
	{// デバイスの解放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの解放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 入力処理
//=============================================================================
void Input(void) {
	UpdateInput();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{

	Vertex_3D v[3] = {-25,0,0,D3DCOLOR_ARGB(255,255,0,0),
					0,25,0,D3DCOLOR_ARGB(255,255,0,0),
					25,0,0,D3DCOLOR_ARGB(255,255,0,0) };

	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 255, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// FPS描画
		DrawFPS();

		// 単位行列化
		D3DXMatrixIdentity(&g_world);
	
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_world);

		g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, v, sizeof(Vertex_3D));

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// FPS表示処理
//=============================================================================
void DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", GetFpsCounter());

	// テキスト描画
	// hDC      : デバイスコンテキストのハンドル
	// lpString : 描画する文字列へのポインタ
	// nCount   : 文字列の文字数
	// lpRect   : 長方形領域
	// uFormat  : テキストの整形方法を指定
	g_pD3DXFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}
