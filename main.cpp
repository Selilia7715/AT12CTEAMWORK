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
#define WINDOW_NAME		"Run Gun"	// ウィンドウの名前
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

VERTEX_2D vertex[VERTEX_MAX];     // 自キャラ(キャラ1)
VERTEX_2D vertex2[VERTEX_MAX];     // 背景
VERTEX_2D vertex3[VERTEX_MAX];     // キャラ2
VERTEX_2D vertex4[VERTEX_MAX];     // タイトル
VERTEX_2D vertex5[VERTEX_MAX];     // グリフォン
VERTEX_2D vertex6[VERTEX_MAX];     // ドラゴン
VERTEX_2D vertex7[VERTEX_MAX];     // キャラ3
VERTEX_2D vertex8[VERTEX_MAX];     // カーソル
VERTEX_2D vertex9[VERTEX_MAX];     // リザルト
VERTEX_2D vertex10[VERTEX_MAX];     // score1
VERTEX_2D vertex11[VERTEX_MAX];     // score2
VERTEX_2D vertex12[VERTEX_MAX];     // score3
VERTEX_2D vertex13[VERTEX_MAX];     // クリア
VERTEX_2D vertex14[VERTEX_MAX];     // hit
VERTEX_2D vertex15[VERTEX_MAX];     // 説明	
VERTEX_2D vertex16[VERTEX_MAX];     // 説明ボタン
VERTEX_2D vertex17[VERTEX_MAX];     // 戻るボタン
VERTEX_2D vertex18[VERTEX_MAX];     // 次へボタン
VERTEX_2D vertex19[VERTEX_MAX];     // ゲームボタン
VERTEX_2D vertex20[VERTEX_MAX];     // タイトルに戻るボタン
VERTEX_2D vertex21[VERTEX_MAX];     // リトライボタン

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void Hit(void);      // 当たり判定
void Main(void);     // タイトル画面
void MainDraw(void);
void MainUpdate(void);
void Result(void);   // リザルト画面
void ResultDraw(void);
void ResultUpdate(void);
void Clear(void);    // クリア画面
void ClearDraw(void);
void ClearUpdate(void);
void SetumeiDraw(void);   // 説明
void SetumeiUpdate(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
LPDIRECT3DTEXTURE9  g_pD3DTexture1 = NULL;    // テクスチャを格納する変数(キャラ1)
LPDIRECT3DTEXTURE9  g_pD3DTexture2 = NULL;    // テクスチャを格納する変数(背景)
LPDIRECT3DTEXTURE9  g_pD3DTexture3 = NULL;    // テクスチャを格納する変数(キャラ2)
LPDIRECT3DTEXTURE9  g_pD3DTexture4 = NULL;    // テクスチャを格納する変数(タイトル)
LPDIRECT3DTEXTURE9  g_pD3DTexture5 = NULL;    // テクスチャを格納する変数(グリフォン)
LPDIRECT3DTEXTURE9  g_pD3DTexture6 = NULL;    // テクスチャを格納する変数(ドラゴン)
LPDIRECT3DTEXTURE9  g_pD3DTexture7 = NULL;    // テクスチャを格納する変数(キャラ3)
LPDIRECT3DTEXTURE9  g_pD3DTexture8 = NULL;    // テクスチャを格納する変数(カーソル)
LPDIRECT3DTEXTURE9  g_pD3DTexture9 = NULL;    // テクスチャを格納する変数(リザルト)
LPDIRECT3DTEXTURE9  g_pD3DTexture10 = NULL;    // テクスチャを格納する変数(score1)
LPDIRECT3DTEXTURE9  g_pD3DTexture11 = NULL;    // テクスチャを格納する変数(score2)
LPDIRECT3DTEXTURE9  g_pD3DTexture12 = NULL;    // テクスチャを格納する変数(score3)
LPDIRECT3DTEXTURE9  g_pD3DTexture13 = NULL;    // テクスチャを格納する変数(クリア)
LPDIRECT3DTEXTURE9  g_pD3DTexture14 = NULL;    // テクスチャを格納する変数(hit)
LPDIRECT3DTEXTURE9  g_pD3DTexture15 = NULL;    // テクスチャを格納する変数(説明)
LPDIRECT3DTEXTURE9  g_pD3DTexture21 = NULL;    // テクスチャを格納する変数(説明2)
LPDIRECT3DTEXTURE9  g_pD3DTexture16 = NULL;    // テクスチャを格納する変数(説明ボタン)
LPDIRECT3DTEXTURE9  g_pD3DTexture17 = NULL;    // テクスチャを格納する変数(カーソル2)
LPDIRECT3DTEXTURE9  g_pD3DTexture18 = NULL;    // テクスチャを格納する変数(戻るボタン)
LPDIRECT3DTEXTURE9  g_pD3DTexture19 = NULL;    // テクスチャを格納する変数(次へボタン)
LPDIRECT3DTEXTURE9  g_pD3DTexture20 = NULL;    // テクスチャを格納する変数(ゲームボタン)
LPDIRECT3DTEXTURE9  g_pD3DTexture22 = NULL;    // テクスチャを格納する変数(タイトルに戻るボタン)
LPDIRECT3DTEXTURE9  g_pD3DTexture23 = NULL;    // テクスチャを格納する変数(リトライボタン)


LPD3DXFONT g_pD3DXFont = NULL;

D3DVECTOR g_playerPosition;  // 主人公座標
D3DVECTOR g_enemyPosition;   // 敵座標
D3DVECTOR g_griPosition;     // グリフォン座標
D3DVECTOR g_draPosition;     // ドラゴン座標
D3DVECTOR g_enemy2Position;   // 敵2座標
D3DVECTOR g_effectPosition;   // エフェクト座標
D3DVECTOR g_setumeiPosition;   // 説明ボタン座標
D3DVECTOR g_returnPosition;   // 戻るボタン座標
D3DVECTOR g_nextPosition;   // 次へボタン座標
D3DVECTOR g_gamePosition;   // ゲームボタン座標
D3DVECTOR g_endPosition;   // タイトルに戻るボタン座標
D3DVECTOR g_retryPosition;   // リトライボタン座標

POINT cl;  // カーソルの座標の変数

// アニメーション制御用変数
int g_anmCnt = 0; 
int g_anmNum = 0;
int g_anmSpeed = 15;

// キャラ1
int g_anmDir = ANM_DOWN;
float g_anmTbl[ANM_MAX] = { 0.0f / 96.0f, 32.0f / 96.0f, 64.0f / 96.0f, 32.0f / 96.0f };

// キャラ2
int g_anmDir2 = ANM_DOWN;
float g_anmTbl2[ANM_MAX] = { 0.0f / 96.0f, 32.0f / 96.0f, 64.0f / 96.0f, 32.0f / 96.0f };

// グリフォン
int g_anmDir3 = ANM_DOWN;
float g_anmTbl3[ANM_MAX] = { 0.0f / 135.0f, 45.0f / 135.0f, 90.0f / 135.0f, 45.0f / 135.0f };

// ドラゴン
int g_anmDir4 = ANM_DOWN;
float g_anmTbl4[ANM_MAX] = { 0.0f / 240.0f, 80.0f / 240.0f, 160.0f / 240.0f, 80.0f / 240.0f };

// キャラ3
int g_anmDir5 = ANM_DOWN;
float g_anmTbl5[ANM_MAX] = { 0.0f / 146.0f, 48.6f / 146.0f, 97.2f / 146.0f, 48.6f / 146.0f };

// FPS管理用
int g_nCountFPS = 0;
float g_dispFPS = 0;

// ランダム用変数
int randam;  // エネミーの移動用

// シーンフラグ
int SceneFlag = 0;

// カーソルと重なると消える処理
bool Kyara2 = false;
bool Dora = false;
bool Gri = false;
bool Kyara3 = false;

// 説明フラグ
bool setumei = false;

// hitフラグ
bool hitFlag = false;

// HPカウント
int enemylife;  // 敵一体死ぬ＝1カウントとする 最大3カウント
int life;       // 自キャラの体力
int grilife;    // グリフォンの体力
int kyara2life; // キャラ2の体力
int doralife;   // ドラゴンの体力

int kyara2cnt = 0; // キャラ2表示のカウント
int gricnt = 0;	   // グリフォン表示のカウント
int doracnt = 0;   // ドラゴン表示のカウント

int hitcnt = 0;  // ヒット表示
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

				// Update&Init
				switch (SceneFlag)
				{
				case 0:
				// タイトル処理
					Main();
					MainUpdate();
					break;

				case 1:
					// 更新処理
					Update();
					break;

				case 2:
					// エンド処理
					Result();
					ResultUpdate();
					break;

				case 3:
					// クリア処理
					Clear();
					ClearUpdate();
					break;

				case 4:
					// 説明処理
					SetumeiUpdate();
					break;
				}

				// 描画処理(一回しか呼び出さない)
				g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
					D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

				if (SUCCEEDED(g_pD3DDevice->BeginScene()))
				{
					switch (SceneFlag)
					{
					case 0:
						MainDraw();
						break;

					case 1:
						Draw();
						break;

					case 2:
						ResultDraw();
						break;

					case 3:
						ClearDraw();
						break;

					case 4:
						SetumeiDraw();
						break;
					}
					// Direct3Dによる描画の終了
					g_pD3DDevice->EndScene();
				}
				g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
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

	////////////////////////////////////////////////////////////////////////////////////////////
	// カーソル
	GetCursorPos(&cl);  // 座標取得
	ScreenToClient(hWnd, &cl); // カーソルの画像となるものを表示(今回はg_pD3DTexture8を表示)
	// カーソルの表示を消す(マウスカーソルのやつ)
	ShowCursor(false); // ずっとこのまま(trueになるとマウスカーソルが出てくる)
	////////////////////////////////////////////////////////////////////////////////////////////

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
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

	/*	case VK_RIGHT:
			g_playerPosition.x += 5.0f;
			g_anmDir = ANM_RIGHT;
			break;

		case VK_LEFT:
			g_playerPosition.x -= 5.0f;
			g_anmDir = ANM_LEFT;
			break;


		case VK_DOWN:
			g_playerPosition.y += 5.0f;
			g_anmDir = ANM_DOWN;
			break;

		case VK_UP:
			g_playerPosition.y -= 5.0f;
			g_anmDir = ANM_UP;
			break;*/
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
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/title2.png", &g_pD3DTexture4)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(リザルト)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/gameover.png", &g_pD3DTexture9)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(クリア)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/clear.png", &g_pD3DTexture13)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(score1)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sysfont.png", &g_pD3DTexture10)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// テクスチャ描画(score2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sysfont.png", &g_pD3DTexture11)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// テクスチャ描画(score3)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sysfont.png", &g_pD3DTexture12)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// テクスチャ描画(キャラ1)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/5.png", &g_pD3DTexture1)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// テクスチャ描画(カーソル)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/scp1.png", &g_pD3DTexture8)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// テクスチャ描画(hit)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/hit3.png", &g_pD3DTexture14)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(キャラ2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/6.png", &g_pD3DTexture3)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(グリフォン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/gri.png", &g_pD3DTexture5)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(ドラゴン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/7.png", &g_pD3DTexture6)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(キャラ3)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/82.png", &g_pD3DTexture7)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(背景)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/haikei3.jpg", &g_pD3DTexture2)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(説明)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sousa1.png", &g_pD3DTexture15)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}	

	// テクスチャ描画(説明2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sousa2.png", &g_pD3DTexture21)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}	
	
	// テクスチャ描画(説明ボタン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/setumei.png", &g_pD3DTexture16)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// テクスチャ描画(カーソル2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/cursor.png", &g_pD3DTexture17)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(戻るボタン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/return.png", &g_pD3DTexture18)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(次へボタン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/return2.png", &g_pD3DTexture19)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// テクスチャ描画(ゲームボタン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/gamestart.png", &g_pD3DTexture20)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(タイトルに戻るボタン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/end.png", &g_pD3DTexture22)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// テクスチャ描画(リトライボタン)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/retry.png", &g_pD3DTexture23)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		aID = MessageBox(hWnd, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// 初期値(ポジション)
	g_playerPosition.x = 600.0f;
	g_playerPosition.y = 400.0f;
	g_enemyPosition.x = 750.0f;
	g_enemyPosition.y = 250.0f;
	g_enemy2Position.x = 200.0f;
	g_enemy2Position.y = 300.0f;
	g_draPosition.x = 600.0f;
	g_draPosition.y = 140.0f;
	g_griPosition.x = 1000.0f;
	g_griPosition.y = 450.0f;

	// キャラ１
	// 座標の値
	vertex[0].x = g_playerPosition.x;
	vertex[0].y = g_playerPosition.y;
	vertex[0].z = g_playerPosition.z;

	vertex[1].x = g_playerPosition.x + 70.0f;
	vertex[1].y = g_playerPosition.y;
	vertex[1].z = g_playerPosition.z;

	vertex[2].x = g_playerPosition.x;
	vertex[2].y = g_playerPosition.y + 70.0f;
	vertex[2].z = g_playerPosition.z;

	vertex[3].x = g_playerPosition.x + 70.0f;
	vertex[3].y = g_playerPosition.y + 70.0f;
	vertex[3].z = g_playerPosition.z;

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

	////////////////////////////////////////////////
	// カーソル
	////////////////////////////////////////////////
	// RHWの値
	vertex8[0].rhw = 1.0f;
	vertex8[1].rhw = 1.0f;
	vertex8[2].rhw = 1.0f;
	vertex8[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex8[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex8[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex8[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex8[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標
	vertex8[0].u = 0.0f;
	vertex8[0].v = 0.0f;
	vertex8[1].u = 1.0f;
	vertex8[1].v = 0.0f;
	vertex8[2].u = 0.0f;
	vertex8[2].v = 1.0f;
	vertex8[3].u = 1.0f;
	vertex8[3].v = 1.0f;
	////////////////////////////////////////////////


	if (Kyara2 == false)
	{
		// キャラ2
	// 座標の値
		vertex3[0].x = g_enemyPosition.x + 400.0f;
		vertex3[0].y = g_enemyPosition.y + 140.0f;
		vertex3[0].z = g_enemyPosition.z;

		vertex3[1].x = g_enemyPosition.x + 464.0f;
		vertex3[1].y = g_enemyPosition.y + 140.0f;
		vertex3[1].z = g_enemyPosition.z;

		vertex3[2].x = g_enemyPosition.x + 400.0f;
		vertex3[2].y = g_enemyPosition.y + 204.0f;
		vertex3[2].z = g_enemyPosition.z;

		vertex3[3].x = g_enemyPosition.x + 464.0f;
		vertex3[3].y = g_enemyPosition.y + 204.0f;
		vertex3[3].z = g_enemyPosition.z;

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

		// テクスチャ座標(3枚に切るため)
		vertex3[0].u = 0.0f;
		vertex3[0].v = 0.0f;
		vertex3[1].u = 0.33f;
		vertex3[1].v = 0.0f;
		vertex3[2].u = 0.0f;
		vertex3[2].v = 0.25f;
		vertex3[3].u = 0.33f;
		vertex3[3].v = 0.25f;
	}
	
	if (Gri == false)
	{
		// グリフォン　
		vertex5[0].x = g_griPosition.x;
		vertex5[0].y = g_griPosition.y;
		vertex5[0].z = g_griPosition.z;

		vertex5[1].x = g_griPosition.x + 200.0f;
		vertex5[1].y = g_griPosition.y;
		vertex5[1].z = g_griPosition.z;

		vertex5[2].x = g_griPosition.x;
		vertex5[2].y = g_griPosition.y + 200.0f;
		vertex5[2].z = g_griPosition.z;

		vertex5[3].x = g_griPosition.x + 200.0f;
		vertex5[3].y = g_griPosition.y + 200.0f;
		vertex5[3].z = g_griPosition.z;

		vertex5[0].rhw = 1.0f;
		vertex5[1].rhw = 1.0f;
		vertex5[2].rhw = 1.0f;
		vertex5[3].rhw = 1.0f;

		vertex5[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertex5[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertex5[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertex5[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		vertex5[0].u = 0.0f;
		vertex5[0].v = 0.0f;
		vertex5[1].u = 0.33f;
		vertex5[1].v = 0.0f;
		vertex5[2].u = 0.0f;
		vertex5[2].v = 0.25f;
		vertex5[3].u = 0.33f;
		vertex5[3].v = 0.25f;

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
	
	if (Dora == false)
	{
		// ドラゴン
	// 座標の値
		vertex6[0].x = g_draPosition.x + 600.0f;
		vertex6[0].y = g_draPosition.y + 140.0f;
		vertex6[0].z = g_draPosition.z;

		vertex6[1].x = g_draPosition.x + 695.0f;
		vertex6[1].y = g_draPosition.y + 140.0f;
		vertex6[1].z = g_draPosition.z;

		vertex6[2].x = g_draPosition.x + 600.0f;
		vertex6[2].y = g_draPosition.y + 195.0f;
		vertex6[2].z = g_draPosition.z;

		vertex6[3].x = g_draPosition.x + 695.0f;
		vertex6[3].y = g_draPosition.y + 195.0f;
		vertex6[3].z = g_draPosition.z;

		// RHWの値
		vertex6[0].rhw = 1.0f;
		vertex6[1].rhw = 1.0f;
		vertex6[2].rhw = 1.0f;
		vertex6[3].rhw = 1.0f;

		// ディフューズ色の設定
		vertex6[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex6[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex6[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex6[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// テクスチャ座標(3枚に切るため)
		vertex6[0].u = 0.0f;
		vertex6[0].v = 0.0f;
		vertex6[1].u = 0.33f;
		vertex6[1].v = 0.0f;
		vertex6[2].u = 0.0f;
		vertex6[2].v = 0.33f;
		vertex6[3].u = 0.33f;
		vertex6[3].v = 0.33f;

	}
	
	if (Kyara3 = false)
	{
		// キャラ3
	// 座標の値
		vertex7[0].x = g_enemy2Position.x;
		vertex7[0].y = g_enemy2Position.y;
		vertex7[0].z = g_enemy2Position.z;

		vertex7[1].x = g_enemy2Position.x + 95.0f;
		vertex7[1].y = g_enemy2Position.y;
		vertex7[1].z = g_enemy2Position.z;

		vertex7[2].x = g_enemy2Position.x;
		vertex7[2].y = g_enemy2Position.y + 65.0f;
		vertex7[2].z = g_enemy2Position.z;

		vertex7[3].x = g_enemy2Position.x + 95.0f;
		vertex7[3].y = g_enemy2Position.y + 65.0f;
		vertex7[3].z = g_enemy2Position.z;

		// RHWの値
		vertex7[0].rhw = 1.0f;
		vertex7[1].rhw = 1.0f;
		vertex7[2].rhw = 1.0f;
		vertex7[3].rhw = 1.0f;

		// ディフューズ色の設定
		vertex7[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex7[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex7[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex7[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// テクスチャ座標(3枚に切るため)
		vertex7[0].u = 0.0f;
		vertex7[0].v = 0.0f;
		vertex7[1].u = 0.25f;
		vertex7[1].v = 0.0f;
		vertex7[2].u = 0.0f;
		vertex7[2].v = 0.25f;
		vertex7[3].u = 0.25f;
		vertex7[3].v = 0.25f;
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

	// テクスチャ1
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
	if (g_pD3DTexture1 != NULL) 
	{
		g_pD3DTexture1->Release();
		g_pD3DTexture1 = NULL;
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

	// テクスチャ5の解放
	if (g_pD3DTexture5 != NULL)
	{
		g_pD3DTexture5->Release();
		g_pD3DTexture5 = NULL;
	}

	// テクスチャ6の解放
	if (g_pD3DTexture6 != NULL)
	{
		g_pD3DTexture6->Release();
		g_pD3DTexture6 = NULL;
	}

	// テクスチャ7の解放
	if (g_pD3DTexture7 != NULL)
	{
		g_pD3DTexture7->Release();
		g_pD3DTexture7 = NULL;
	}

	// テクスチャ8の解放 カーソル
	if (g_pD3DTexture8 != NULL)
	{
		g_pD3DTexture8->Release();
		g_pD3DTexture8 = NULL;
	}

	// テクスチャ9の解放
	if (g_pD3DTexture9 != NULL)
	{				 
		g_pD3DTexture9->Release();
		g_pD3DTexture9 = NULL;
	}

	// テクスチャ10の解放
	if (g_pD3DTexture10 != NULL)
	{				 
		g_pD3DTexture10->Release();
		g_pD3DTexture10 = NULL;
	}

	// テクスチャ11の解放
	if (g_pD3DTexture11 != NULL)
	{				 
		g_pD3DTexture11->Release();
		g_pD3DTexture11 = NULL;
	}

	// テクスチャ12の解放
	if (g_pD3DTexture12 != NULL)
	{				 
		g_pD3DTexture12->Release();
		g_pD3DTexture12 = NULL;
	}
	
	// テクスチャ13の解放
	if (g_pD3DTexture13 != NULL)
	{				 
		g_pD3DTexture13->Release();
		g_pD3DTexture13 = NULL;
	}
	
	// テクスチャ14の解放
	if (g_pD3DTexture14 != NULL)
	{				 
		g_pD3DTexture14->Release();
		g_pD3DTexture14 = NULL;
	}
	
	// テクスチャ15の解放
	if (g_pD3DTexture15 != NULL)
	{				 
		g_pD3DTexture15->Release();
		g_pD3DTexture15 = NULL;
	}
	
	// テクスチャ16の解放
	if (g_pD3DTexture16 != NULL)
	{				 
		g_pD3DTexture16->Release();
		g_pD3DTexture16 = NULL;
	}
	
	// テクスチャ17の解放
	if (g_pD3DTexture17 != NULL)
	{				 
		g_pD3DTexture17->Release();
		g_pD3DTexture17 = NULL;
	}

	// テクスチャ18の解放
	if (g_pD3DTexture18 != NULL)
	{				 
		g_pD3DTexture18->Release();
		g_pD3DTexture18 = NULL;
	}
	
	// テクスチャ19の解放
	if (g_pD3DTexture19 != NULL)
	{				 
		g_pD3DTexture19->Release();
		g_pD3DTexture19 = NULL;
	}	
	
	// テクスチャ20の解放
	if (g_pD3DTexture20 != NULL)
	{				 
		g_pD3DTexture20->Release();
		g_pD3DTexture20 = NULL;
	}

		// テクスチャ21の解放
	if (g_pD3DTexture21 != NULL)
	{				 
		g_pD3DTexture21->Release();
		g_pD3DTexture21 = NULL;
	}
}

//=============================================================================
// ゲーム画面処理
//=============================================================================
void Draw()
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


	if (Gri == false)
	{
		// グリフォン描画

		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture5);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex5[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

	}


	if (Kyara2 == false)
	{
		// キャラ描画2
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

	}

	if (Dora == false)
	{
		// ドラゴン描画
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture6);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex6[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

	}


	//if (Kyara3 == false)
	//{
	//	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	//	// テクスチャをポリゴンにセット
	//	g_pD3DDevice->SetTexture(0, g_pD3DTexture7);

	//	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	//	g_pD3DDevice->DrawPrimitiveUP(
	//		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
	//		2,                   // ポリゴンの数
	//		&vertex7[0],          // 頂点データ構造体の先頭アドレス
	//		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	//	);

	//}

	// 自キャラ描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture1);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

	// hit描画
	if (hitFlag == true)
	{

		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture14);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex14[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

	}

	// カーソル描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture8);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex8[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

	// バックバッファとフロントバッファの入れ替え
	// pSourceRect         : 転送元矩形
	// pDestRect           : 転送先矩形
	// hDestWindowOverride : 転送先ウインドウへのポインタ
	// pDirtyRegion        : 通常はNULLで
}

void Update()
{
	// ランダムでキャラ2が動く処理
	srand((unsigned)time(NULL));
	randam = rand() % 12 + 1;

	//表示座標の更新
	// カーソル
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f; 

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;

	// hit
	if (hitFlag == true)
	{
		// hit
		vertex14[0].x = cl.x - CURSOR_X;
		vertex14[0].y = cl.y - CURSOR_Y - HIT_X;
		vertex14[0].z = 0.0f;

		vertex14[1].x = cl.x + CURSOR_X;
		vertex14[1].y = cl.y - CURSOR_Y - HIT_Y;
		vertex14[1].z = 0.0f;

		vertex14[2].x = cl.x - CURSOR_X;
		vertex14[2].y = cl.y + CURSOR_Y - HIT_X;
		vertex14[2].z = 0.0f;

		vertex14[3].x = cl.x + CURSOR_X;
		vertex14[3].y = cl.y + CURSOR_Y - HIT_Y;
		vertex14[3].z = 0.0f;
		
		//// hit
		//vertex14[0].x = cl.x - CURSOR_X;
		//vertex14[0].y = cl.y - CURSOR_Y;
		//vertex14[0].z = 0.0f;

		//vertex14[1].x = cl.x + CURSOR_X;
		//vertex14[1].y = cl.y - CURSOR_Y;
		//vertex14[1].z = 0.0f;

		//vertex14[2].x = cl.x - CURSOR_X;
		//vertex14[2].y = cl.y + CURSOR_Y;
		//vertex14[2].z = 0.0f;

		//vertex14[3].x = cl.x + CURSOR_X;
		//vertex14[3].y = cl.y + CURSOR_Y;
		//vertex14[3].z = 0.0f;
		
		if (hitcnt <= HITTIME_MAX)
		{
			hitcnt++;
		}

		if (hitcnt > HITTIME_MIN)
		{
			hitcnt = 0;
			hitFlag = false;
		}
		else
		{
			// RHWの値
			vertex14[0].rhw = 1.0f;
			vertex14[1].rhw = 1.0f;
			vertex14[2].rhw = 1.0f;
			vertex14[3].rhw = 1.0f;

			// ディフューズ色の設定
			vertex14[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
			vertex14[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
			vertex14[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
			vertex14[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

			// テクスチャ座標
			vertex14[0].u = 0.0f;
			vertex14[0].v = 0.0f;
			vertex14[1].u = 1.0f;
			vertex14[1].v = 0.0f;
			vertex14[2].u = 0.0f;
			vertex14[2].v = 1.0f;
			vertex14[3].u = 1.0f;
			vertex14[3].v = 1.0f;
		}
	}
	else
	{
		// hit(初期値は画面外にある)
		vertex14[0].x = 1500.0f;
		vertex14[0].y = 1500.0f;
		vertex14[0].z = 0.0f;

		vertex14[1].x = 1500.0f;
		vertex14[1].y = 1500.0f;
		vertex14[1].z = 0.0f;

		vertex14[2].x = 1500.0f;
		vertex14[2].y = 1500.0f;
		vertex14[2].z = 0.0f;

		vertex14[3].x = 1500.0f;
		vertex14[3].y = 1500.0f;
		vertex14[3].z = 0.0f;

		// RHWの値
		vertex14[0].rhw = 1.0f;
		vertex14[1].rhw = 1.0f;
		vertex14[2].rhw = 1.0f;
		vertex14[3].rhw = 1.0f;

		// ディフューズ色の設定
		vertex14[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex14[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex14[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex14[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// テクスチャ座標
		vertex14[0].u = 0.0f;
		vertex14[0].v = 0.0f;
		vertex14[1].u = 1.0f;
		vertex14[1].v = 0.0f;
		vertex14[2].u = 0.0f;
		vertex14[2].v = 1.0f;
		vertex14[3].u = 1.0f;
		vertex14[3].v = 1.0f;
	}

	// キャラ1
	vertex[0].x = g_playerPosition.x;
	vertex[0].y = g_playerPosition.y;
	vertex[0].z = g_playerPosition.z;

	vertex[1].x = g_playerPosition.x + 70.0f;
	vertex[1].y = g_playerPosition.y;  
	vertex[1].z = g_playerPosition.z;  
									   
	vertex[2].x = g_playerPosition.x;  
	vertex[2].y = g_playerPosition.y + 70.0f;
	vertex[2].z = g_playerPosition.z; 
									  
	vertex[3].x = g_playerPosition.x + 70.0f;
	vertex[3].y = g_playerPosition.y + 70.0f;
	vertex[3].z = g_playerPosition.z;
	

	//移動処理
	// 方向キー(キャラ1)
	// 左
	if (GetKeyboardPress(DIK_LEFT))
	{
		g_playerPosition.x -= KYARA_SPEED_MAX;
		g_anmDir = ANM_LEFT;
	}

	// 右
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_playerPosition.x += KYARA_SPEED_MAX;
		g_anmDir = ANM_RIGHT;
	}
	
	// 上
	if (GetKeyboardPress(DIK_UP))
	{
		g_playerPosition.y -= KYARA_SPEED_MAX;
		g_anmDir = ANM_UP;
	}

	// 下
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_playerPosition.y += KYARA_SPEED_MAX;
		g_anmDir = ANM_DOWN;
	}

	// A
	if (GetAsyncKeyState('A'))
	{
		g_playerPosition.x -= KYARA_SPEED_MAX;
		g_anmDir = ANM_LEFT;
	}

	// D
	if (GetAsyncKeyState('D'))
	{
		g_playerPosition.x += KYARA_SPEED_MAX;
		g_anmDir = ANM_RIGHT;
	}

	// W
	if (GetAsyncKeyState('W'))
	{
		g_playerPosition.y -= KYARA_SPEED_MAX;
		g_anmDir = ANM_UP;
	}

	// S
	if (GetAsyncKeyState('S'))
	{
		g_playerPosition.y += KYARA_SPEED_MAX;
		g_anmDir = ANM_DOWN;
	}


	// キャラ2
	if (Kyara2 == false)
	{
		// キャラ2
		vertex3[0].x = g_enemyPosition.x;
		vertex3[0].y = g_enemyPosition.y;
		vertex3[0].z = g_enemyPosition.z;

		vertex3[1].x = g_enemyPosition.x + 64.0f;
		vertex3[1].y = g_enemyPosition.y;
		vertex3[1].z = g_enemyPosition.z;

		vertex3[2].x = g_enemyPosition.x;
		vertex3[2].y = g_enemyPosition.y + 64.0f;
		vertex3[2].z = g_enemyPosition.z;

		vertex3[3].x = g_enemyPosition.x + 64.0f;
		vertex3[3].y = g_enemyPosition.y + 64.0f;
		vertex3[3].z = g_enemyPosition.z;

		if (enemylife == 1)
		{
			// ランダム移動
			if (randam == 7)             // 左
			{
				g_enemyPosition.x -= KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_LEFT;
			}
			else if (randam == 5 || randam == 11)        // 右
			{
				g_enemyPosition.x += KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_RIGHT;
			}
			else if (randam == 3)        // 上
			{
				g_enemyPosition.y -= KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_UP;
			}
			else if (randam == 1 || randam == 9)         // 下
			{
				g_enemyPosition.y += KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_DOWN;
			}
			else
			{
				g_enemyPosition.x = g_enemyPosition.x;
				g_enemyPosition.y = g_enemyPosition.y;
			}
		}
		else if (enemylife == 2)
		{
			// ランダム移動
			if (randam == 7)             // 左
			{
				g_enemyPosition.x -= KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_LEFT;
			}
			else if (randam == 5 || randam == 11)        // 右
			{
				g_enemyPosition.x += KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_RIGHT;
			}
			else if (randam == 3)        // 上
			{
				g_enemyPosition.y -= KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_UP;
			}
			else if (randam == 1 || randam == 9)         // 下
			{
				g_enemyPosition.y += KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_DOWN;
			}
			else
			{
				g_enemyPosition.x = g_enemyPosition.x;
				g_enemyPosition.y = g_enemyPosition.y;
			}
		}
		else
		{
			// ランダム移動
			if (randam == 7)             // 左
			{
				g_enemyPosition.x -= KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_LEFT;
			}
			else if (randam == 5 || randam == 11)        // 右
			{
				g_enemyPosition.x += KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_RIGHT;
			}
			else if (randam == 3)        // 上
			{
				g_enemyPosition.y -= KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_UP;
			}
			else if (randam == 1 || randam == 9)         // 下
			{
				g_enemyPosition.y += KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_DOWN;
			}
			else
			{
				g_enemyPosition.x = g_enemyPosition.x;
				g_enemyPosition.y = g_enemyPosition.y;
			}
		}
	
	}
	
	// グリフォン
	if (Gri == false)
	{
		// グリフォン　
		vertex5[0].x = g_griPosition.x;
		vertex5[0].y = g_griPosition.y;
		vertex5[0].z = g_griPosition.z;

		vertex5[1].x = g_griPosition.x + 90.0f;
		vertex5[1].y = g_griPosition.y;
		vertex5[1].z = g_griPosition.z;

		vertex5[2].x = g_griPosition.x;
		vertex5[2].y = g_griPosition.y + 90.0f;
		vertex5[2].z = g_griPosition.z;

		vertex5[3].x = g_griPosition.x + 90.0f;
		vertex5[3].y = g_griPosition.y + 90.0f;
		vertex5[3].z = g_griPosition.z;

		if (enemylife == 1)
		{
			// ランダムでグリフォンが動く処理
			if (randam == 3 || randam == 7 || randam == 12)             // 左
			{
				g_griPosition.x -= GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_LEFT;
			}
			else if (randam == 1 || randam == 8)        // 右
			{
				g_griPosition.x += GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_RIGHT;
			}
			else if (randam == 4 || randam == 6)        // 上
			{
				g_griPosition.y -= GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_UP;
			}
			else if (randam == 2 || randam == 10)           // 下
			{
				g_griPosition.y += GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_DOWN;
			}
			else                          // 停止
			{
				g_griPosition.x = g_griPosition.x;
				g_griPosition.y = g_griPosition.y;
			}
		}
		else if (enemylife == 2)
		{
			// ランダムでグリフォンが動く処理
			if (randam == 3 || randam == 7 || randam == 12)             // 左
			{
				g_griPosition.x -= GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_LEFT;
			}
			else if (randam == 1 || randam == 8)        // 右
			{
				g_griPosition.x += GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_RIGHT;
			}
			else if (randam == 4 || randam == 6)        // 上
			{
				g_griPosition.y -= GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_UP;
			}
			else if (randam == 2 || randam == 10)           // 下
			{
				g_griPosition.y += GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_DOWN;
			}
			else                          // 停止
			{
				g_griPosition.x = g_griPosition.x;
				g_griPosition.y = g_griPosition.y;
			}	
		}
		else
		{
			// ランダムでグリフォンが動く処理
			if (randam == 3 || randam == 7 || randam == 12)             // 左
			{
				g_griPosition.x -= GRI_SPEED_MAX;
				g_anmDir3 = ANM_LEFT;
			}
			else if (randam == 1 || randam == 8)        // 右
			{
				g_griPosition.x += GRI_SPEED_MAX;
				g_anmDir3 = ANM_RIGHT;
			}
			else if (randam == 4 || randam == 6)        // 上
			{
				g_griPosition.y -= GRI_SPEED_MAX;
				g_anmDir3 = ANM_UP;
			}
			else if (randam == 2 || randam == 10)           // 下
			{
				g_griPosition.y += GRI_SPEED_MAX;
				g_anmDir3 = ANM_DOWN;
			}
			else                          // 停止
			{
				g_griPosition.x = g_griPosition.x;
				g_griPosition.y = g_griPosition.y;
			}
		}
	}
	
	// ドラゴン
	if (Dora == false)
	{
		// ドラゴン
		vertex6[0].x = g_draPosition.x;
		vertex6[0].y = g_draPosition.y;
		vertex6[0].z = g_draPosition.z;

		vertex6[1].x = g_draPosition.x + 95.0f;
		vertex6[1].y = g_draPosition.y;
		vertex6[1].z = g_draPosition.z;

		vertex6[2].x = g_draPosition.x;
		vertex6[2].y = g_draPosition.y + 95.0f;
		vertex6[2].z = g_draPosition.z;

		vertex6[3].x = g_draPosition.x + 95.0f;
		vertex6[3].y = g_draPosition.y + 95.0f;
		vertex6[3].z = g_draPosition.z;

		if (enemylife == 1)
		{
			// ランダムでドラゴンが動く処理
			if (randam == 1 || randam == 6)              // 左
			{
				g_draPosition.x -= DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_LEFT;
			}
			else if (randam == 8 || randam == 7)         // 右
			{
				g_draPosition.x += DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_RIGHT;
			}
			else if (randam == 5 || randam == 4)         // 上
			{
				g_draPosition.y -= DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 3 || randam == 2)         // 下
			{
				g_draPosition.y += DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_DOWN;
			}
			else if (randam == 10)                       // 斜め上
			{
				g_draPosition.x += DORA_SPEED_MAX + 1.5f;
				g_draPosition.y += DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 11)                       // 斜め下
			{
				g_draPosition.x -= DORA_SPEED_MAX + 1.5f;
				g_draPosition.y -= DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_DOWN;
			}
			else
			{
				g_draPosition.x = g_draPosition.x;
				g_draPosition.y = g_draPosition.y;
			}
		}
		else if (enemylife == 2)
		{
			// ランダムでドラゴンが動く処理
			if (randam == 1 || randam == 6)              // 左
			{
				g_draPosition.x -= DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_LEFT;
			}
			else if (randam == 8 || randam == 7)         // 右f
			{
				g_draPosition.x += DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_RIGHT;
			}
			else if (randam == 5 || randam == 4)         // 上
			{
				g_draPosition.y -= DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 3 || randam == 2)         // 下
			{
				g_draPosition.y += DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_DOWN;
			}
			else if (randam == 10)                       // 斜め上
			{
				g_draPosition.x += DORA_SPEED_MAX * 2.0f;
				g_draPosition.y += DORA_SPEED_MAX * 2.0f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 11)                       // 斜め下
			{
				g_draPosition.x -= DORA_SPEED_MAX * 2.0f;
				g_draPosition.y -= DORA_SPEED_MAX * 2.0f;
				g_anmDir4 = ANM_DOWN;
			}
			else
			{
				g_draPosition.x = g_draPosition.x;
				g_draPosition.y = g_draPosition.y;
			}
		}
		else
		{
			// ランダムでドラゴンが動く処理
			if (randam == 1 || randam == 6)              // 左
			{
				g_draPosition.x -= DORA_SPEED_MAX;
				g_anmDir4 = ANM_LEFT;
			}
			else if (randam == 8 || randam == 7)         // 右
			{
				g_draPosition.x += DORA_SPEED_MAX;
				g_anmDir4 = ANM_RIGHT;
			}
			else if (randam == 5 || randam == 4)         // 上
			{
				g_draPosition.y -= DORA_SPEED_MAX;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 3 || randam == 2)         // 下
			{
				g_draPosition.y += DORA_SPEED_MAX;
				g_anmDir4 = ANM_DOWN;
			}
			else if (randam == 10)                       // 斜め上
			{
				g_draPosition.x += DORA_SPEED_MAX;
				g_draPosition.y += DORA_SPEED_MAX;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 11)                       // 斜め下
			{
				g_draPosition.x -= DORA_SPEED_MAX;
				g_draPosition.y -= DORA_SPEED_MAX;
				g_anmDir4 = ANM_DOWN;
			}
			else
			{
				g_draPosition.x = g_draPosition.x;
				g_draPosition.y = g_draPosition.y;
			}
		}
	}
	
	// アニメーションカウントの更新
	++g_anmCnt;
	if (g_anmCnt % g_anmSpeed == 0)
	{
		++g_anmNum;
		if (g_anmNum >= ANM_MAX)
		{
			g_anmNum = 0;
		}

		// キャラ1
		vertex[0].u = g_anmTbl[g_anmNum]; // 横幅Xピクセル[0]
		vertex[1].u = g_anmTbl[g_anmNum] + 32.0f / 96.0f; // [1]
		vertex[2].u = g_anmTbl[g_anmNum]; // [2]
		vertex[3].u = g_anmTbl[g_anmNum] + 32.0f / 96.0f; // [3]

		// キャラ2
		vertex3[0].u = g_anmTbl2[g_anmNum]; // 横幅Xピクセル[0]
		vertex3[1].u = g_anmTbl2[g_anmNum] + 32.0f / 96.0f; // [1]
		vertex3[2].u = g_anmTbl2[g_anmNum]; // [2]
		vertex3[3].u = g_anmTbl2[g_anmNum] + 32.0f / 96.0f; // [3]

		// グリフォン
		vertex5[0].u = g_anmTbl3[g_anmNum];//横幅135ピクセル
		vertex5[1].u = g_anmTbl3[g_anmNum] + 45.0f / 135.0f;
		vertex5[2].u = g_anmTbl3[g_anmNum];
		vertex5[3].u = g_anmTbl3[g_anmNum] + 45.0f / 135.0f;

		// ドラゴン
		vertex6[0].u = g_anmTbl4[g_anmNum]; // 横幅Xピクセル[0]
		vertex6[1].u = g_anmTbl4[g_anmNum] + 32.0f / 96.0f; // [1]
		vertex6[2].u = g_anmTbl4[g_anmNum]; // [2]
		vertex6[3].u = g_anmTbl4[g_anmNum] + 32.0f / 96.0f; // [3]

		//// キャラ3
		//vertex7[0].u = g_anmTbl5[g_anmNum]; // 横幅Xピクセル[0]
		//vertex7[1].u = g_anmTbl5[g_anmNum] + 48.6f / 146.0f; // [1]
		//vertex7[2].u = g_anmTbl5[g_anmNum]; // [2]
		//vertex7[3].u = g_anmTbl5[g_anmNum] + 48.6f / 146.0f; // [3]

	}

	// キャラ1
	vertex[0].v = g_anmDir * 32.0f / 128.0f;
	vertex[1].v = vertex[0].v;
	vertex[2].v = ((g_anmDir + 1) * 32.0f) / 128.0f;
	vertex[3].v = vertex[2].v;

	// キャラ2
	vertex3[0].v = g_anmDir2 * 32.0f / 128.0f;
	vertex3[1].v = vertex3[0].v;
	vertex3[2].v = ((g_anmDir2 + 1) * 32.0f) / 128.0f;
	vertex3[3].v = vertex3[2].v;
	
	// グリフォン
	vertex5[0].v = g_anmDir3 * 50.0f / 200.0f;
	vertex5[1].v = vertex5[0].v;
	vertex5[2].v = ((g_anmDir3 + 1) * 50.0f) / 200.0f;
	vertex5[3].v = vertex5[2].v;

	// ドラゴン
	vertex6[0].v = g_anmDir4 * 32.0f / 128.0f;
	vertex6[1].v = vertex6[0].v;
	vertex6[2].v = ((g_anmDir4 + 1) * 32.0f) / 128.0f;
	vertex6[3].v = vertex6[2].v;

	// 当たり判定処理
	Hit();
}

//=============================================================================
// ゲーム画面処理の当たり判定処理
//=============================================================================
void Hit()
{
	// 壁とキャラ1との当たり判定
	if (g_playerPosition.x < 0)
	{
		g_playerPosition.x = 0;
	}
	if (g_playerPosition.x >= 1135)
	{
		g_playerPosition.x = 1135;
	}
	if (g_playerPosition.y < 0)
	{
		g_playerPosition.y = 0;
	}
	if (g_playerPosition.y >= 535)
	{
		g_playerPosition.y = 535;
	}

	// 壁とキャラ2との当たり判定
	if (g_enemyPosition.x < 0)
	{
		g_enemyPosition.x = 0;
	}
	if (g_enemyPosition.x >= 1136)
	{
		g_enemyPosition.x = 1136;
	}
	if (g_enemyPosition.y < 0)
	{
		g_enemyPosition.y = 0;
	}
	if (g_enemyPosition.y >= 536)
	{
		g_enemyPosition.y = 536;
	}

	// 壁とグリフォンとの当たり判定
	if (g_griPosition.x <0)
	{	  
		g_griPosition.x = 0;
	}	  
	if (g_griPosition.x >= 1110)
	{	  
		g_griPosition.x = 1110;
	}	  
	if (g_griPosition.y < 0)
	{	  
		g_griPosition.y = 0;
	}	  
	if (g_griPosition.y >= 510)
	{	  
		g_griPosition.y = 510;
	}

	// 壁とドラゴンとの当たり判定
	if (g_draPosition.x < 0)
	{
		g_draPosition.x = 0;
	}
	if (g_draPosition.x >= 1105)
	{
		g_draPosition.x = 1105;
	}
	if (g_draPosition.y < 0)
	{
		g_draPosition.y = 0;
	}
	if (g_draPosition.y >= 505)
	{
		g_draPosition.y = 505;
	}

	// ライフ
	if (life > 0)
	{
		if (!Kyara2)
		{
			// キャラ1とキャラ2の当たり判定
			if (g_playerPosition.x + 70.0f >= g_enemyPosition.x && g_playerPosition.x <= g_enemyPosition.x + 64.0f)
			{
				if (g_playerPosition.y + 70.0f >= g_enemyPosition.y && g_playerPosition.y <= g_enemyPosition.y + 64.0f)
				{
					PlaySound(SOUND_LABEL_SE002);// playerとememyの当たり音SE
					Kyara2 = true;
					life -= 1;
				}
			}
		}

		// キャラ1とドラゴンの当たり判定
		if (!Dora) {
			if (g_playerPosition.x + 70.0f >= g_draPosition.x && g_playerPosition.x <= g_draPosition.x + 80.0f)
			{
				if (g_playerPosition.y + 70.0f >= g_draPosition.y && g_playerPosition.y <= g_draPosition.y + 80.0f)
				{
					PlaySound(SOUND_LABEL_SE002);// playerとememyの当たり音SE
					Dora = true;
					life -= 1;
				}
			}
		}

		if (!Gri)
		{
			// キャラ1とグリフォン描画の当たり判定
			if (g_playerPosition.x + 70.0f >= g_griPosition.x && g_playerPosition.x <= g_griPosition.x + 90.0f)
			{
				if (g_playerPosition.y + 70.0f >= g_griPosition.y && g_playerPosition.y <= g_griPosition.y + 90.0f)
				{
					PlaySound(SOUND_LABEL_SE002);// playerとememyの当たり音SE
					Gri = true;
					life -= 1;
				}
			}
		}
	}
	else if(life <= 0)
	{
		SceneFlag = 2;
	}

	// カーソルと敵との当たり判定
	if (enemylife < 3)
	{
		if (GetMouseLeftTrigger())
		{
			PlaySound(SOUND_LABEL_SE000); // ショット音

			if (!Kyara2)
			{
				// カーソルとキャラ2の当たり判定
				if (cl.x >= g_enemyPosition.x && cl.x <= g_enemyPosition.x + 64.0f)
				{
					if (cl.y + 15.0f >= g_enemyPosition.y && cl.y <= g_enemyPosition.y + 64.0f)
					{
						
						// kyara2の体力 
						if (kyara2life < KYARA2_LIFE)
						{
							hitFlag = true;
							kyara2life += 1;
						}
						else if(kyara2life >= KYARA2_LIFE)
						{
							PlaySound(SOUND_LABEL_SE001); // 破壊音
							Kyara2 = true;
							enemylife += 1;
						}
					}
				}
			}

			if (!Dora) {
				// カーソルとドラゴンの当たり判定
				if (cl.x + 15.0f >= g_draPosition.x && cl.x <= g_draPosition.x + 80.0f)
				{
					if (cl.y + 15.0f >= g_draPosition.y && cl.y <= g_draPosition.y + 80.0f)
					{
						// ドラゴンの体力 
						if (doralife < DORA_LIFE)
						{
							hitFlag = true;
							doralife += 1;
						}
						else if (doralife >= DORA_LIFE)
						{
							PlaySound(SOUND_LABEL_SE001); // 破壊音
							Dora = true;
							enemylife += 1;
						}
					}
				}
			}

			if (!Gri) {
				// カーソルとグリフォン描画の当たり判定
				if (cl.x + 15.0f >= g_griPosition.x && cl.x <= g_griPosition.x + 90.0f)
				{
					if (cl.y + 15.0f >= g_griPosition.y && cl.y <= g_griPosition.y + 90.0f)
					{
						// グリフォンの体力 
						if (grilife < GRI_LIFE)
						{
							hitFlag = true;
							grilife += 1;
						}
						else if (grilife >= GRI_LIFE)
						{
							PlaySound(SOUND_LABEL_SE001); // 破壊音
							Gri = true;
							enemylife += 1;
						}
						
					}
				}
			}
		}
		
	}
	else if(enemylife >= 3)
	{
		SceneFlag = 3;
	}
}

//=============================================================================
// タイトル処理
//=============================================================================
void Main()
{
	// 説明フラグ
    setumei = false;

	// 初期値(ポジション)
	g_playerPosition.x = 550.0f;
	g_playerPosition.y = 300.0f;
	g_enemyPosition.x = 250.0f;
	g_enemyPosition.y = 250.0f;
	g_enemy2Position.x = 200.0f;
	g_enemy2Position.y = 300.0f;
	g_draPosition.x = 100.0f;
	g_draPosition.y = 240.0f;
	g_griPosition.x = 1000.0f;
	g_griPosition.y = 450.0f;

	// ゲームボタン
	g_gamePosition.x = 800.0f;
	g_gamePosition.y = 400.0f;

	// フラグリセット
	Kyara2 = false;
	Dora = false;
	Gri = false;
	//Kyara3 = false;

	enemylife = 0;
	life = 1;
	kyara2life = 0;
	grilife = 0;
	doralife = 0;

	g_setumeiPosition.x = 150.0f;
	g_setumeiPosition.y = 440.0f;

	// タイトル
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

	// 説明ボタン
	vertex16[0].x = g_setumeiPosition.x;
	vertex16[0].y = g_setumeiPosition.y;
	vertex16[0].z = 0.0f;
		  
	vertex16[1].x = g_setumeiPosition.x + 150.0f;
	vertex16[1].y = g_setumeiPosition.y;
	vertex16[1].z = 0.0f;
		  
	vertex16[2].x = g_setumeiPosition.x;
	vertex16[2].y = g_setumeiPosition.y + 100.0f;
	vertex16[2].z = 0.0f;
		  
	vertex16[3].x = g_setumeiPosition.x + 150.0f;
	vertex16[3].y = g_setumeiPosition.y + 100.0f; 
	vertex16[3].z = 0.0f;

	// RHWの値
	vertex16[0].rhw = 1.0f;
	vertex16[1].rhw = 1.0f;
	vertex16[2].rhw = 1.0f;
	vertex16[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex16[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex16[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex16[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex16[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// 説明ボタンの色と拡大
	if (cl.x >= g_setumeiPosition.x && cl.x <= g_setumeiPosition.x + 150.0f)
	{
		if (cl.y >= g_setumeiPosition.y && cl.y <= g_setumeiPosition.y + 100.0f)
		{
			vertex16[0].x = g_setumeiPosition.x - BIGSIZE_X;
			vertex16[0].y = g_setumeiPosition.y - BIGSIZE_Y;
			vertex16[0].z = 0.0f;

			vertex16[1].x = g_setumeiPosition.x + 150.0f + BIGSIZE_X;
			vertex16[1].y = g_setumeiPosition.y - BIGSIZE_Y;
			vertex16[1].z = 0.0f;

			vertex16[2].x = g_setumeiPosition.x - BIGSIZE_X;
			vertex16[2].y = g_setumeiPosition.y + 100.0f + BIGSIZE_Y;
			vertex16[2].z = 0.0f;

			vertex16[3].x = g_setumeiPosition.x + 150.0f + BIGSIZE_X;
			vertex16[3].y = g_setumeiPosition.y + 100.0f + BIGSIZE_Y;
			vertex16[3].z = 0.0f;

			vertex16[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex16[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex16[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex16[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// テクスチャ座標(背景なので一枚)
	vertex16[0].u = 0.0f;
	vertex16[0].v = 0.0f;
	vertex16[1].u = 1.0f;
	vertex16[1].v = 0.0f;
	vertex16[2].u = 0.0f;
	vertex16[2].v = 1.0f;
	vertex16[3].u = 1.0f;
	vertex16[3].v = 1.0f;
	
	// ゲームボタン
	vertex19[0].x = g_gamePosition.x;
	vertex19[0].y = g_gamePosition.y;
	vertex19[0].z = 0.0f;
		   
	vertex19[1].x = g_gamePosition.x + 300.0f;
	vertex19[1].y = g_gamePosition.y;
	vertex19[1].z = 0.0f;
		   
	vertex19[2].x = g_gamePosition.x;
	vertex19[2].y = g_gamePosition.y + 130.0f;
	vertex19[2].z = 0.0f;
		   
	vertex19[3].x = g_gamePosition.x + 300.0f;
	vertex19[3].y = g_gamePosition.y + 130.0f; 
	vertex19[3].z = 0.0f;

	// RHWの値
	vertex19[0].rhw = 1.0f;
	vertex19[1].rhw = 1.0f;
	vertex19[2].rhw = 1.0f;
	vertex19[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex19[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex19[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex19[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex19[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// ゲームボタンの色と拡大
	if (cl.x >= g_gamePosition.x && cl.x <= g_gamePosition.x + 300.0f)
	{
		if (cl.y >= g_gamePosition.y && cl.y <= g_gamePosition.y + 130.0f)
		{
			vertex19[0].x = g_gamePosition.x - BIGSIZE_X;
			vertex19[0].y = g_gamePosition.y - BIGSIZE_Y;
			vertex19[0].z = 0.0f;

			vertex19[1].x = g_gamePosition.x + 300.0f + BIGSIZE_X;
			vertex19[1].y = g_gamePosition.y - BIGSIZE_Y;
			vertex19[1].z = 0.0f;

			vertex19[2].x = g_gamePosition.x - BIGSIZE_X;
			vertex19[2].y = g_gamePosition.y + 130.0f + BIGSIZE_Y;
			vertex19[2].z = 0.0f;

			vertex19[3].x = g_gamePosition.x + 300.0f + BIGSIZE_X;
			vertex19[3].y = g_gamePosition.y + 130.0f + BIGSIZE_Y;
			vertex19[3].z = 0.0f;

			vertex19[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex19[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex19[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex19[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// テクスチャ座標(背景なので一枚)
	vertex19[0].u = 0.0f;
	vertex19[0].v = 0.0f;
	vertex19[1].u = 1.0f;
	vertex19[1].v = 0.0f;
	vertex19[2].u = 0.0f;
	vertex19[2].v = 1.0f;
	vertex19[3].u = 1.0f;
	vertex19[3].v = 1.0f;


	// カーソル
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;
}

void MainDraw()
{
	// タイトル画面
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

	// 説明ボタン描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture16);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex16[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
	
	// ゲームボタン描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture20);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex19[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
	
	// カーソル描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex8[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

void MainUpdate()
{
	
	if (GetMouseLeftTrigger())
	{
		// 説明ボタン
		if (cl.x >= g_setumeiPosition.x && cl.x <= g_setumeiPosition.x + 150.0f)
		{
			if (cl.y >= g_setumeiPosition.y && cl.y <= g_setumeiPosition.y + 100.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // クリック

				SceneFlag = 4;
			}
		}
		
		// ゲームボタン
		if (cl.x >= g_gamePosition.x && cl.x <= g_gamePosition.x + 300.0f)
		{
			if (cl.y >= g_gamePosition.y && cl.y <= g_gamePosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // クリック

				SceneFlag = 1;
			}
		}
	}


}

//=============================================================================
// ゲームオーバー処理
//==================================================================\==========
void Result()
{
	// 初期値(ポジション)
	g_playerPosition.x = 550.0f;
	g_playerPosition.y = 300.0f;
	g_enemyPosition.x = 250.0f;
	g_enemyPosition.y = 250.0f;
	g_enemy2Position.x = 200.0f;
	g_enemy2Position.y = 300.0f;
	g_draPosition.x = 100.0f;
	g_draPosition.y = 240.0f;
	g_griPosition.x = 1000.0f;
	g_griPosition.y = 450.0f;

	// タイトルに戻るボタン
	g_endPosition.x = 250.0f;
	g_endPosition.y = 420.0f;

	// リトライボタン
	g_retryPosition.x = 650.0f;
	g_retryPosition.y = 420.0f;


	// フラグリセット
	Kyara2 = false;
	Dora = false;
	Gri = false;
	//Kyara3 = false;

	enemylife = 0;
	life = 1;
	kyara2life = 0;
	grilife = 0;
	doralife = 0;

	// リトライ
	vertex9[0].x = 0.0f;
	vertex9[0].y = 0.0f;
	vertex9[0].z = 0.0f;
		  
	vertex9[1].x = SCREEN_WIDTH;
	vertex9[1].y = 0.0f;
	vertex9[1].z = 0.0f;
		  
	vertex9[2].x = 0.0f;
	vertex9[2].y = SCREEN_HEIGHT;
	vertex9[2].z = 0.0f;
		  
	vertex9[3].x = SCREEN_WIDTH;
	vertex9[3].y = SCREEN_HEIGHT;
	vertex9[3].z = 0.0f;

	// RHWの値
	vertex9[0].rhw = 1.0f;
	vertex9[1].rhw = 1.0f;
	vertex9[2].rhw = 1.0f;
	vertex9[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex9[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex9[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex9[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex9[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	vertex9[0].u = 0.0f;
	vertex9[0].v = 0.0f;
	vertex9[1].u = 1.0f;
	vertex9[1].v = 0.0f;
	vertex9[2].u = 0.0f;
	vertex9[2].v = 1.0f;
	vertex9[3].u = 1.0f;
	vertex9[3].v = 1.0f;

	// タイトルに戻るボタン
	vertex20[0].x = g_endPosition.x;
	vertex20[0].y = g_endPosition.y;
	vertex20[0].z = 0.0f;
		  
	vertex20[1].x = g_endPosition.x + 300.0f;
	vertex20[1].y = g_endPosition.y;
	vertex20[1].z = 0.0f;
		  
	vertex20[2].x = g_endPosition.x;
	vertex20[2].y = g_endPosition.y + 130.0f;
	vertex20[2].z = 0.0f;
		  
	vertex20[3].x = g_endPosition.x + 300.0f;
	vertex20[3].y = g_endPosition.y + 130.0f;
	vertex20[3].z = 0.0f;

	// RHWの値
	vertex20[0].rhw = 1.0f;
	vertex20[1].rhw = 1.0f;
	vertex20[2].rhw = 1.0f;
	vertex20[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex20[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// タイトルに戻るボタンの色変えと拡大
	if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
	{
		if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
		{
			// タイトルに戻るボタン
			vertex20[0].x = g_endPosition.x - BIGSIZE_X;
			vertex20[0].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[0].z = 0.0f;

			vertex20[1].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[1].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[1].z = 0.0f;

			vertex20[2].x = g_endPosition.x - BIGSIZE_X;
			vertex20[2].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[2].z = 0.0f;

			vertex20[3].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[3].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[3].z = 0.0f;

			vertex20[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// テクスチャ座標(背景なので一枚)
	vertex20[0].u = 0.0f;
	vertex20[0].v = 0.0f;
	vertex20[1].u = 1.0f;
	vertex20[1].v = 0.0f;
	vertex20[2].u = 0.0f;
	vertex20[2].v = 1.0f;
	vertex20[3].u = 1.0f;
	vertex20[3].v = 1.0f;

	// リトライボタン
	vertex21[0].x = g_retryPosition.x;
	vertex21[0].y = g_retryPosition.y;
	vertex21[0].z = 0.0f;
		   
	vertex21[1].x = g_retryPosition.x + 300.0f;
	vertex21[1].y = g_retryPosition.y;
	vertex21[1].z = 0.0f;
		   
	vertex21[2].x = g_retryPosition.x;
	vertex21[2].y = g_retryPosition.y + 130.0f;
	vertex21[2].z = 0.0f;
		   
	vertex21[3].x = g_retryPosition.x + 300.0f;
	vertex21[3].y = g_retryPosition.y + 130.0f;
	vertex21[3].z = 0.0f;

	// RHWの値
	vertex21[0].rhw = 1.0f;
	vertex21[1].rhw = 1.0f;
	vertex21[2].rhw = 1.0f;
	vertex21[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex21[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex21[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex21[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex21[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// リトライボタンの色変えと拡大
	if (cl.x >= g_retryPosition.x && cl.x <= g_retryPosition.x + 300.0f)
	{
		if (cl.y >= g_retryPosition.y && cl.y <= g_retryPosition.y + 130.0f)
		{
			// リトライボタン
			vertex21[0].x = g_retryPosition.x - BIGSIZE_X;
			vertex21[0].y = g_retryPosition.y - BIGSIZE_Y;
			vertex21[0].z = 0.0f;

			vertex21[1].x = g_retryPosition.x + 300.0f + BIGSIZE_X;
			vertex21[1].y = g_retryPosition.y - BIGSIZE_Y;
			vertex21[1].z = 0.0f;

			vertex21[2].x = g_retryPosition.x - BIGSIZE_X;
			vertex21[2].y = g_retryPosition.y + 130.0f + BIGSIZE_Y;
			vertex21[2].z = 0.0f;

			vertex21[3].x = g_retryPosition.x + 300.0f + BIGSIZE_X;
			vertex21[3].y = g_retryPosition.y + 130.0f + BIGSIZE_Y;
			vertex21[3].z = 0.0f;

			vertex21[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex21[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex21[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex21[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// テクスチャ座標(背景なので一枚)
	vertex21[0].u = 0.0f;
	vertex21[0].v = 0.0f;
	vertex21[1].u = 1.0f;
	vertex21[1].v = 0.0f;
	vertex21[2].u = 0.0f;
	vertex21[2].v = 1.0f;
	vertex21[3].u = 1.0f;
	vertex21[3].v = 1.0f;

	// カーソル
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;

}

void ResultDraw()
{
	// ゲームオーバー
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture9);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex9[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

	// タイトルに戻る描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture22);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex20[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

	// リトライ描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture23);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex21[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);


	// カーソル描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex8[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

}

void ResultUpdate()
{
	if (GetMouseLeftTrigger())
	{
		// タイトルに戻るボタン
		if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
		{
			if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // クリック

				SceneFlag = 0;
			}
		}

		// リトライボタン
		if (cl.x >= g_retryPosition.x && cl.x <= g_retryPosition.x + 300.0f)
		{
			if (cl.y >= g_retryPosition.y && cl.y <= g_retryPosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // クリック

				SceneFlag = 1;
			}
		}
	}
}

//=============================================================================
// ゲームクリア処理
//=============================================================================
void Clear()
{

	// タイトルに戻るボタン
	g_endPosition.x = 450.0f;
	g_endPosition.y = 390.0f;

	// クリア
	vertex13[0].x = 0.0f;
	vertex13[0].y = 0.0f;
	vertex13[0].z = 0.0f;
		  
	vertex13[1].x = SCREEN_WIDTH;
	vertex13[1].y = 0.0f;
	vertex13[1].z = 0.0f;
		  
	vertex13[2].x = 0.0f;
	vertex13[2].y = SCREEN_HEIGHT;
	vertex13[2].z = 0.0f;
		  
	vertex13[3].x = SCREEN_WIDTH;
	vertex13[3].y = SCREEN_HEIGHT;
	vertex13[3].z = 0.0f;

	// RHWの値
	vertex13[0].rhw = 1.0f;
	vertex13[1].rhw = 1.0f;
	vertex13[2].rhw = 1.0f;
	vertex13[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex13[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex13[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex13[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex13[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	vertex13[0].u = 0.0f;
	vertex13[0].v = 0.0f;
	vertex13[1].u = 1.0f;
	vertex13[1].v = 0.0f;
	vertex13[2].u = 0.0f;
	vertex13[2].v = 1.0f;
	vertex13[3].u = 1.0f;
	vertex13[3].v = 1.0f;

	// タイトルに戻るボタン
	vertex20[0].x = g_endPosition.x;
	vertex20[0].y = g_endPosition.y;
	vertex20[0].z = 0.0f;

	vertex20[1].x = g_endPosition.x + 300.0f;
	vertex20[1].y = g_endPosition.y;
	vertex20[1].z = 0.0f;

	vertex20[2].x = g_endPosition.x;
	vertex20[2].y = g_endPosition.y + 130.0f;
	vertex20[2].z = 0.0f;

	vertex20[3].x = g_endPosition.x + 300.0f;
	vertex20[3].y = g_endPosition.y + 130.0f;
	vertex20[3].z = 0.0f;

	// RHWの値
	vertex20[0].rhw = 1.0f;
	vertex20[1].rhw = 1.0f;
	vertex20[2].rhw = 1.0f;
	vertex20[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex20[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// タイトルに戻るボタンの色変えと拡大
	if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
	{
		if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
		{
			vertex20[0].x = g_endPosition.x - BIGSIZE_X;
			vertex20[0].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[0].z = 0.0f;

			vertex20[1].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[1].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[1].z = 0.0f;

			vertex20[2].x = g_endPosition.x - BIGSIZE_X;
			vertex20[2].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[2].z = 0.0f;

			vertex20[3].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[3].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[3].z = 0.0f;

			vertex20[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// テクスチャ座標(背景なので一枚)
	vertex20[0].u = 0.0f;
	vertex20[0].v = 0.0f;
	vertex20[1].u = 1.0f;
	vertex20[1].v = 0.0f;
	vertex20[2].u = 0.0f;
	vertex20[2].v = 1.0f;
	vertex20[3].u = 1.0f;
	vertex20[3].v = 1.0f;

	// カーソル
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;
}

void ClearDraw()
{
	// タイトル描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture13);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex13[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

	// タイトルに戻る描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture22);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex20[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);

	// カーソル描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex8[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

void ClearUpdate()
{
	if (GetMouseLeftTrigger())
	{
		// タイトルに戻るボタン
		if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
		{
			if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // クリック

				SceneFlag = 0;
			}
		}
	}
}

//=============================================================================
// ゲーム説明処理
//=============================================================================
void SetumeiDraw()
{
	// 説明ボタン
	if (setumei == false)
	{
		// 説明描画
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture15);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex15[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

		// 次へボタン描画
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture19);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex18[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);
	}
	else
	{
		// 説明2描画
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture21);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex15[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);

		// 戻るボタン描画
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャをポリゴンにセット
		g_pD3DDevice->SetTexture(0, g_pD3DTexture18);

		// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
			2,                   // ポリゴンの数
			&vertex17[0],          // 頂点データ構造体の先頭アドレス
			sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
		);
	}

	// カーソル描画
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&vertex8[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

void SetumeiUpdate()
{
	// 初期値(戻るボタン)
	g_returnPosition.x = 1100.0f;
	g_returnPosition.y = 515.0f;

	// 初期値(次へボタン)
	g_nextPosition.x = 1100.0f;
	g_nextPosition.y = 515.0f;

	// 説明
	vertex15[0].x = 0.0f;
	vertex15[0].y = 0.0f;
	vertex15[0].z = 0.0f;
		   
	vertex15[1].x = SCREEN_WIDTH;
	vertex15[1].y = 0.0f;
	vertex15[1].z = 0.0f;
		   
	vertex15[2].x = 0.0f;
	vertex15[2].y = SCREEN_HEIGHT;
	vertex15[2].z = 0.0f;
		   
	vertex15[3].x = SCREEN_WIDTH;
	vertex15[3].y = SCREEN_HEIGHT;
	vertex15[3].z = 0.0f;

	// RHWの値
	vertex15[0].rhw = 1.0f;
	vertex15[1].rhw = 1.0f;
	vertex15[2].rhw = 1.0f;
	vertex15[3].rhw = 1.0f;

	// ディフューズ色の設定
	vertex15[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex15[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex15[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex15[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// テクスチャ座標(背景なので一枚)
	vertex15[0].u = 0.0f;
	vertex15[0].v = 0.0f;
	vertex15[1].u = 1.0f;
	vertex15[1].v = 0.0f;
	vertex15[2].u = 0.0f;
	vertex15[2].v = 1.0f;
	vertex15[3].u = 1.0f;
	vertex15[3].v = 1.0f;


	if (setumei == false)
	{
		// 次へボタン
		vertex18[0].x = g_nextPosition.x;
		vertex18[0].y = g_nextPosition.y;
		vertex18[0].z = 0.0f;

		vertex18[1].x = g_nextPosition.x + 90.0f;
		vertex18[1].y = g_nextPosition.y;
		vertex18[1].z = 0.0f;

		vertex18[2].x = g_nextPosition.x;
		vertex18[2].y = g_nextPosition.y + 70.0f;
		vertex18[2].z = 0.0f;

		vertex18[3].x = g_nextPosition.x + 90.0f;
		vertex18[3].y = g_nextPosition.y + 70.0f;
		vertex18[3].z = 0.0f;

		// RHWの値
		vertex18[0].rhw = 1.0f;
		vertex18[1].rhw = 1.0f;
		vertex18[2].rhw = 1.0f;
		vertex18[3].rhw = 1.0f;

		// ディフューズ色の設定
		vertex18[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex18[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex18[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex18[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// 次へボタンの色と拡大
		if (cl.x >= g_nextPosition.x && cl.x <= g_nextPosition.x + 90.0f)
		{
			if (cl.y >= g_nextPosition.y && cl.y <= g_nextPosition.y + 70.0f)
			{
				vertex18[0].x = g_nextPosition.x - BIGSIZE2_X;
				vertex18[0].y = g_nextPosition.y - BIGSIZE2_Y;
				vertex18[0].z = 0.0f;

				vertex18[1].x = g_nextPosition.x + 90.0f + BIGSIZE2_X;
				vertex18[1].y = g_nextPosition.y - BIGSIZE2_Y;
				vertex18[1].z = 0.0f;

				vertex18[2].x = g_nextPosition.x - BIGSIZE2_X;
				vertex18[2].y = g_nextPosition.y + 70.0f + BIGSIZE2_Y;
				vertex18[2].z = 0.0f;

				vertex18[3].x = g_nextPosition.x + 90.0f + BIGSIZE2_X;
				vertex18[3].y = g_nextPosition.y + 70.0f + BIGSIZE2_Y;
				vertex18[3].z = 0.0f;

				vertex18[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex18[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex18[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex18[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			}
		}

		// テクスチャ座標(背景なので一枚)
		vertex18[0].u = 0.0f;
		vertex18[0].v = 0.0f;
		vertex18[1].u = 1.0f;
		vertex18[1].v = 0.0f;
		vertex18[2].u = 0.0f;
		vertex18[2].v = 1.0f;
		vertex18[3].u = 1.0f;
		vertex18[3].v = 1.0f;
	}
	else
	{
		// 戻るボタン
		vertex17[0].x = g_returnPosition.x;
		vertex17[0].y = g_returnPosition.y;
		vertex17[0].z = 0.0f;

		vertex17[1].x = g_returnPosition.x + 90.0f;
		vertex17[1].y = g_returnPosition.y;
		vertex17[1].z = 0.0f;

		vertex17[2].x = g_returnPosition.x;
		vertex17[2].y = g_returnPosition.y + 70.0f;
		vertex17[2].z = 0.0f;

		vertex17[3].x = g_returnPosition.x + 90.0f;
		vertex17[3].y = g_returnPosition.y + 70.0f;
		vertex17[3].z = 0.0f;

		// RHWの値
		vertex17[0].rhw = 1.0f;
		vertex17[1].rhw = 1.0f;
		vertex17[2].rhw = 1.0f;
		vertex17[3].rhw = 1.0f;

		// ディフューズ色の設定
		vertex17[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex17[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex17[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex17[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// 戻るボタンの色変えと拡大
		if (cl.x >= g_returnPosition.x && cl.x <= g_returnPosition.x + 90.0f)
		{
			if (cl.y >= g_returnPosition.y && cl.y <= g_returnPosition.y + 70.0f)
			{
				vertex17[0].x = g_returnPosition.x - BIGSIZE2_X;
				vertex17[0].y = g_returnPosition.y - BIGSIZE2_Y;
				vertex17[0].z = 0.0f;

				vertex17[1].x = g_returnPosition.x + 90.0f + BIGSIZE2_X;
				vertex17[1].y = g_returnPosition.y - BIGSIZE2_Y;
				vertex17[1].z = 0.0f;

				vertex17[2].x = g_returnPosition.x - BIGSIZE2_X;
				vertex17[2].y = g_returnPosition.y + 70.0f + BIGSIZE2_Y;
				vertex17[2].z = 0.0f;

				vertex17[3].x = g_returnPosition.x + 90.0f + BIGSIZE2_X;
				vertex17[3].y = g_returnPosition.y + 70.0f + BIGSIZE2_Y;
				vertex17[3].z = 0.0f;

				vertex17[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex17[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex17[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex17[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			}
		}

		// テクスチャ座標(背景なので一枚)
		vertex17[0].u = 0.0f;
		vertex17[0].v = 0.0f;
		vertex17[1].u = 1.0f;
		vertex17[1].v = 0.0f;
		vertex17[2].u = 0.0f;
		vertex17[2].v = 1.0f;
		vertex17[3].u = 1.0f;
		vertex17[3].v = 1.0f;
	}
	
	// カーソル
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;

	// タイトルに戻る
	if (GetMouseLeftTrigger())
	{
		if (setumei == true)
		{
			if (cl.x >= g_returnPosition.x && cl.x <= g_returnPosition.x + 90.0f)
			{
				if (cl.y >= g_returnPosition.y && cl.y <= g_returnPosition.y + 70.0f)
				{
					PlaySound(SOUND_LABEL_SE003);  // クリック

					SceneFlag = 0;
					setumei = false;
				}
			}
		}
		else
		{
			if (cl.x >= g_nextPosition.x && cl.x <= g_nextPosition.x + 90.0f)
			{
				if (cl.y >= g_nextPosition.y && cl.y <= g_nextPosition.y + 70.0f)
				{
					PlaySound(SOUND_LABEL_SE003);  // クリック
					setumei = true;
				}
			}
		}
	}
}
