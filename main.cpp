//=============================================================================
//
// DX21
// DirectX雛型処理 [main.cpp]
//
//=============================================================================
#include "Main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CLASS_NAME		"サンプル"				// ウインドウクラスの名前
#define WINDOW_NAME		"DirectX雛型処理"	// ウィンドウの名前
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// FPS設定
#define FPS (60)

// アニメーションの向き
#define ANM_DOWN (0)
#define ANM_LEFT (1)
#define ANM_RIGHT (2)
#define ANM_UP (3)

// アニメーションパターン数
#define ANM_MAX (4)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct VERTEX_2D {
	float x, y, z;
	float rhw;
	D3DCOLOR col;
	float u, v;  // テクスチャ座標
}VERTEX_2D;

VERTEX_2D vertex[VERTEX_MAX];     // 自キャラ
VERTEX_2D vertex2[VERTEX_MAX];     // 背景
VERTEX_2D vertex3[VERTEX_MAX];     // タイトル
VERTEX_2D vertex4[VERTEX_MAX];     // リザルト

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void Uninit(void);
void GameInit(void);      // ゲーム画面	
void GameUpdate(void);   
void GameDraw(void);
void TitleInit(void);     // タイトル画面
void TitleDraw(void);
void TitleUpdate(void);
void ResultInit(void);   // リザルト画面
void ResultDraw(void);
void ResultUpdate(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
LPDIRECT3DTEXTURE9  g_pD3DTexture = NULL;    // テクスチャを格納する変数(キャラ1)
LPDIRECT3DTEXTURE9  g_pD3DTexture2 = NULL;    // テクスチャを格納する変数(背景)
LPDIRECT3DTEXTURE9  g_pD3DTexture3 = NULL;    // テクスチャを格納する変数(タイトル)
LPDIRECT3DTEXTURE9  g_pD3DTexture4 = NULL;    // テクスチャを格納する変数(リザルト)


LPD3DXFONT g_pD3DXFont = NULL;

D3DVECTOR g_playerPosition;  // 主人公座標

POINT cl; // カーソル


// FPS管理用
int g_nCountFPS = 0;
float g_dispFPS = 0;


// シーンフラグ
int SceneFlag = 0;

//=============================================================================
// メイン関数
//  (WINAPI : Win32API関数を呼び出す時の規約)
//  hInstance     : このアプリケーションのインスタンスハンドル(識別子)
//  hPrevInstance : 常にNULL(16bit時代の名残り)
//  lpCmdLine     : コマンドラインから受け取った引数へのポインタ
//  nCmdShow      : アプリケーションの初期ウインドウ表示方法の指定
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEXのメモリサイズを指定
		CS_CLASSDC,						// 表示するウインドウのスタイルを設定
		WndProc,						// ウィンドウプロシージャのアドレス(関数名)を指定
		0,								// 通常は使用しないので"0"を指定
		0,								// 通常は使用しないので"0"を指定
		hInstance,						// WinMainのパラメータのインスタンスハンドルを設定
		NULL,							// 使用するアイコンを指定(Windowsがもっているアイコンを使うならNULL)
		LoadCursor(NULL, IDC_ARROW),	// マウスカーソルを指定
		(HBRUSH)(COLOR_WINDOW + 1),		// ウインドウのクライアント領域の背景色を設定
		NULL,							// Windowにつけるメニューを設定
		CLASS_NAME,						// ウインドウクラスの名前
		NULL							// 小さいアイコンが設定された場合の情報を記述
	};
	HWND hWnd;
	MSG msg;

	// FPS管理用変数
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,						// 拡張ウィンドウスタイル
		CLASS_NAME,				// ウィンドウクラスの名前
		WINDOW_NAME,			// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
		CW_USEDEFAULT,			// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,			// ウィンドウの左上Ｙ座標 
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2), // ウィンドウの幅
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 +
			GetSystemMetrics(SM_CYCAPTION)), // ウィンドウの高さ
		NULL,					// 親ウィンドウのハンドル
		NULL,					// メニューハンドルまたは子ウィンドウID
		hInstance,				// インスタンスハンドル
		NULL);					// ウィンドウ作成データ

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// FPSフレームカウント初期化
	timeBeginPeriod(1); // 分解能を設定
	dwExecLastTime = timeGetTime(); // システム時刻を取得
	dwCurrentTime = dwFrameCount = 0;


	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれて、WM_QUITメッセージが来たらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / FPS))
			{
				g_dispFPS = (1000.0f / (dwCurrentTime - dwExecLastTime));
				dwExecLastTime = dwCurrentTime;

				UpdateInput();

				switch (scene)
				{
				case TITLE:     // タイトル画面

					TitleInit();
					TitleDraw();
					TitleUpdate();
					break;

				case GAME:     // ゲーム画面
					GameInit();
					GameDraw();
					GameUpdate();
					break;

				case RESULT:   // リザルト画面
					ResultInit();
					ResultDraw();
					ResultUpdate();
					break;

				}

			}

		}
	}
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	//  第１引数：メクラス名
	//  第２引数：アプリケーションインスタンスのハンドル
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	//SetCursorPos(900,300);
	// cursolposition
	// カーソルの座標を取得
	GetCursorPos(&cl);
	// 矢印カーソルが消えて、テクスチャが描画される
	ScreenToClient(hWnd, &cl);  
	// カーソル表示を消す　
	ShowCursor(false);

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか？", "終了", MB_YESNO);

			ShowCursor(true);
			SetCursorPos(900, 300);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

		}
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか？", "終了", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	int aID;

	// Direct3Dオブジェクトの生成
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
	ZeroMemory(&d3dpp, sizeof(d3dpp));						  	// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			  	// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.BackBufferCount = 1;						 // バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;     // 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;	// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// デプスバッファとして16bitを使う

	if (bWindow)
	{// ウィンドウモード
		d3dpp.FullScreen_RefreshRateInHz = 0;				 	// リフレッシュレート(指定できないので0固定)
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		// インターバル(VSyncを待たずに描画)
	}
	else
	{// フルスクリーンモード
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		// リフレッシュレート(現在の速度に合わせる)
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		// インターバル(VSyncを待って描画)
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
		D3DDEVTYPE_HAL,							// デバイスタイプ
		hWnd,								      	// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,   	// デバイス作成制御の組み合わせ
		&d3dpp,									    // デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// DirectInput
	InitInput(hInstance, hWnd);

	// XAudio2
	InitSound();

	// 初期値(座標、RHW、ディフューズ色の設定)

	// テクスチャ描画(タイトル)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/OP.tga", &g_pD3DTexture3)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(リザルト)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/92.jpg", &g_pD3DTexture4)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}


	// テクスチャ描画(自キャラ)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/5.png", &g_pD3DTexture)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(背景)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/haikei.jpg", &g_pD3DTexture2)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// 透明色
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	UninitInput();

	UninitSound();

	
	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// テクスチャの解放
	if (g_pD3DTexture != NULL)
	{
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}

	// テクスチャ2の解放
	if (g_pD3DTexture2 != NULL)
	{
		g_pD3DTexture2->Release();
		g_pD3DTexture2 = NULL;
	}

	// テクスチャ3の解放
	if (g_pD3DTexture3 != NULL)
	{
		g_pD3DTexture3->Release();
		g_pD3DTexture3 = NULL;
	}

	// テクスチャ4の解放
	if (g_pD3DTexture4 != NULL)
	{
		g_pD3DTexture4->Release();
		g_pD3DTexture4 = NULL;
	}

}

//=============================================================================
// ゲーム処理
//=============================================================================
void GameInit()
{
	// 初期値
	g_playerPosition.x = 10.0f;
	g_playerPosition.y = 400.0f;

	// キャラ1
	//vertex[0].x = g_playerPosition.x;
	//vertex[0].y = g_playerPosition.y;
	//vertex[0].z = g_playerPosition.z;

	//vertex[1].x = g_playerPosition.x + 50.0f;
	//vertex[1].y = g_playerPosition.y;
	//vertex[1].z = g_playerPosition.z;

	//vertex[2].x = g_playerPosition.x;
	//vertex[2].y = g_playerPosition.y + 50.0f;
	//vertex[2].z = g_playerPosition.z;

	//vertex[3].x = g_playerPosition.x + 50.0f;
	//vertex[3].y = g_playerPosition.y + 50.0f;
	//vertex[3].z = g_playerPosition.z;


	// キャラ(カーソルver)
	vertex[0].x = cl.x - 50.0f;  // cl.xはカーソルのX座標を表しています。
	vertex[0].y = cl.y - 50.0f;  // cl.yはカーソルのY座標を表しています。
	vertex[0].z = 0.0f;

	vertex[1].x = cl.x + 50.0f;
	vertex[1].y = cl.y - 50.0f;
	vertex[1].z = 0.0f;

	vertex[2].x = cl.x - 50.0f;
	vertex[2].y = cl.y + 50.0f;
	vertex[2].z = 0.0f;

	vertex[3].x = cl.x + 50.0f;
	vertex[3].y = cl.y + 50.0f;
	vertex[3].z = 0.0f;

	// RHWの値
	vertex[0].rhw = 1.0f;
	vertex[1].rhw = 1.0f;
	vertex[2].rhw = 1.0f;
	vertex[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(3枚に切るため)
	vertex[0].u = 0.0f;
	vertex[0].v = 0.0f;
	vertex[1].u = 0.33f;
	vertex[1].v = 0.0f;
	vertex[2].u = 0.0f;
	vertex[2].v = 0.25f;
	vertex[3].u = 0.33f;
	vertex[3].v = 0.25f;

	// 背景
	vertex2[0].x = 0.0f;
	vertex2[0].y = 0.0f;
	vertex2[0].z = 0.0f;

	vertex2[1].x = SCREEN_WIDTH;
	vertex2[1].y = 0.0f;
	vertex2[1].z = 0.0f;

	vertex2[2].x = 0.0f;
	vertex2[2].y = SCREEN_HEIGHT;
	vertex2[2].z = 0.0f;

	vertex2[3].x = SCREEN_WIDTH;
	vertex2[3].y = SCREEN_HEIGHT;
	vertex2[3].z = 0.0f;

	// RHWの値
	vertex2[0].rhw = 1.0f;
	vertex2[1].rhw = 1.0f;
	vertex2[2].rhw = 1.0f;
	vertex2[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex2[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex2[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex2[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex2[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	vertex2[0].u = 0.0f;
	vertex2[0].v = 0.0f;
	vertex2[1].u = 1.0f;
	vertex2[1].v = 0.0f;
	vertex2[2].u = 0.0f;
	vertex2[2].v = 1.0f;
	vertex2[3].u = 1.0f;
	vertex2[3].v = 1.0f;

}

void GameUpdate()
{
	// カーソルで自キャラの座標を動かしているのでキー入力はコメントにしています。

	//移動処理
	// 方向キー(キャラ1)
	// 左
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	g_playerPosition.x -= KYARA_SPEED_MAX;

	//}

	//// 右
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	g_playerPosition.x += KYARA_SPEED_MAX;

	//}

	//// 上
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	g_playerPosition.y -= KYARA_SPEED_MAX;

	//}

	//// 下
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	g_playerPosition.y += KYARA_SPEED_MAX;
	//}

	// 遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		scene = RESULT;
	}

}

void GameDraw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	// Count   : pRects配列にある矩形の数
	// pRects  : クリアする矩形の配列(NULL指定でビューポート矩形全体をクリア)
	// Flags   : クリアするサーフェスを示すフラグ(少なくとも１つを使用しなければならない)
	//         : [D3DCLEAR_TARGET - レンダリングターゲットをクリアしてColorパラメータの値にする]
	//         : [D3DCLEAR_ZBUFFER - 深度(Ｚ)バッファをクリアしてZパラメータの値にする]
	//         : [D3DCLEAR_STENCIL - ステンシルバッファをクリアしてStencilパラメータの値にする]
	// Color   : サーフェスをクリアする色
	// Z       : デプスバッファに保存する値
	// Stencil : ステンシルバッファに保存する値(整数)

	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//// カリングをオフにする
	/*g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DDCULL_NONE);*/

	// 描画
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//具体的な描画処理をココに記述していく

		// 背景
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture2);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex2[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);


		// 自キャラ描画
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}


	// バックバッファとフロントバッファの入れ替え
	// pSourceRect         : 転送元矩形
	// pDestRect           : 転送先矩形
	// hDestWindowOverride : 転送先ウインドウへのポインタ
	// pDirtyRegion        : 通常はNULLで
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//=============================================================================
// タイトル処理
//=============================================================================
void TitleInit()
{
	//// タイトル マウス
	//vertex3[0].x = cl.x - 300; // cl.xはカーソルのX座標を表しています。
	//vertex3[0].y = cl.y - 150; // cl.yはカーソルのY座標を表しています。
	//vertex3[0].z = 0; 

	//vertex3[1].x = cl.x + 300;
	//vertex3[1].y = cl.y - 150;
	//vertex3[1].z = 0.0f;

	//vertex3[2].x = cl.x - 300;
	//vertex3[2].y = cl.y + 150;
	//vertex3[2].z = 0.0f;

	//vertex3[3].x = cl.x  + 300;
	//vertex3[3].y = cl.y + 150;
	//vertex3[3].z = 0.0f;

	// タイトル
	vertex3[0].x = 0.0f;
	vertex3[0].y = 0.0f;
	vertex3[0].z = 0.0f;

	vertex3[1].x = SCREEN_WIDTH;
	vertex3[1].y = 0.0f;
	vertex3[1].z = 0.0f;

	vertex3[2].x = 0.0f;
	vertex3[2].y = SCREEN_HEIGHT;
	vertex3[2].z = 0.0f;

	vertex3[3].x = SCREEN_WIDTH;
	vertex3[3].y = SCREEN_HEIGHT;
	vertex3[3].z = 0.0f;

	// RHWの値
	vertex3[0].rhw = 1.0f;
	vertex3[1].rhw = 1.0f;
	vertex3[2].rhw = 1.0f;
	vertex3[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex3[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex3[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex3[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex3[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	vertex3[0].u = 0.0f;
	vertex3[0].v = 0.0f;
	vertex3[1].u = 1.0f;
	vertex3[1].v = 0.0f;
	vertex3[2].u = 0.0f;
	vertex3[2].v = 1.0f;
	vertex3[3].u = 1.0f;
	vertex3[3].v = 1.0f;
}

void TitleDraw()
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//// カリングをオフにする
	/*g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DDCULL_NONE);*/

	// タイトル描画
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//具体的な描画処理をココに記述していく

		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture3);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex3[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void TitleUpdate()
{

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		scene = GAME;
	}
}

//=============================================================================
// ゲームオーバー処理
//=============================================================================
void ResultInit()
{
	// リザルト
	vertex4[0].x = 0.0f;
	vertex4[0].y = 0.0f;
	vertex4[0].z = 0.0f;

	vertex4[1].x = SCREEN_WIDTH;
	vertex4[1].y = 0.0f;
	vertex4[1].z = 0.0f;

	vertex4[2].x = 0.0f;
	vertex4[2].y = SCREEN_HEIGHT;
	vertex4[2].z = 0.0f;

	vertex4[3].x = SCREEN_WIDTH;
	vertex4[3].y = SCREEN_HEIGHT;
	vertex4[3].z = 0.0f;

	// RHWの値
	vertex4[0].rhw = 1.0f;
	vertex4[1].rhw = 1.0f;
	vertex4[2].rhw = 1.0f;
	vertex4[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex4[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex4[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex4[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex4[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	vertex4[0].u = 0.0f;
	vertex4[0].v = 0.0f;
	vertex4[1].u = 1.0f;
	vertex4[1].v = 0.0f;
	vertex4[2].u = 0.0f;
	vertex4[2].v = 1.0f;
	vertex4[3].u = 1.0f;
	vertex4[3].v = 1.0f;
}

void ResultDraw()
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//// カリングをオフにする
	/*g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DDCULL_NONE);*/

	// タイトル描画
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//具体的な描画処理をココに記述していく

		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture4);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex4[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void ResultUpdate()
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		scene = TITLE;
	}
}

