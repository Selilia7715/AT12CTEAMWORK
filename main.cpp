//=============================================================================
//
// DX21
// DirectX雛型処理 [main.cpp]
//
//=============================================================================
#include "Main.h"
#include "Title.h"
#include "GameScene.h"
#include "Result.h"
#include "Select.h"

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)

// FPS管理用
int g_nCountFPS = 0;
float g_dispFPS = 0;

IGraphBuilder *pGraphBuilder;
IMediaControl *pMediaControl;
IVideoWindow *pVideoWindow;

// 純粋仮想関数
int SceneFlag = 1; // シーンフラグ

// カーソルの座標の変数
POINT cl; 

// テクスチャ
int g_texture;  

GameScene gamescene;
Title title;
Result result;
SelectStage selectstage;

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

				UpdateXinputControllerState();  // XBOX 

				// Upadate・Draw
				// 描画(一回だけ呼ぶ)
				g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
					D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

				if (SUCCEEDED(g_pD3DDevice->BeginScene()))
				{
					switch (SceneFlag)
					{
					case 1:// Title



						// 再生開始
						pMediaControl->Run();

						title.Update(&SceneFlag);							   // 更新
						title.Draw(&g_pD3DDevice);						   // 描画

						break;

					case 2:// Select
						// セレクト	
						selectstage.Update(&SceneFlag);
						selectstage.Draw(&g_pD3DDevice);

					case 3:// GameScene

						// 背景とステージ
						gamescene.Update(&SceneFlag);
						gamescene.Draw(&g_pD3DDevice);
						break;

					case 4:// Result
						result.Update(&SceneFlag);
						result.Draw(&g_pD3DDevice);
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
	// COM終了
	CoUninitialize();

	return (int)msg.wParam, 0;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	////////////////////////////////////////////////////////////////////////////////////////////
    // カーソル
	GetCursorPos(&cl);  // 座標取得
	//ScreenToClient(hWnd, &cl); // カーソルの画像となるものを表示(今回はm_player_pD3DTextureを表示) playerクラスを参照
	// カーソルの表示を消す(マウスカーソルのやつ)
	//ShowCursor(false); // ずっとこのまま(trueになるとマウスカーソルが出てくる)
	ShowCursor(true); // ずっとこのまま(trueになるとマウスカーソルが出てくる)
	////////////////////////////////////////////////////////////////////////////////////////////

	int nID;

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

	// COMを初期化
	CoInitialize(NULL);

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// FilterGraphを生成
	CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC,
		IID_IGraphBuilder,
		(LPVOID *)&pGraphBuilder);

	// MediaControlインターフェース取得
	pGraphBuilder->QueryInterface(IID_IMediaControl,
		(LPVOID *)&pMediaControl);

	//// フルスクリーンにできる
	//pGraphBuilder->QueryInterface(IID_IVideoWindow,
	//	(LPVOID *)&pVideoWindow);

	BSTR bstr1 = CComBSTR(FILENAME);
	// Graphを生成
	pMediaControl->RenderFile(bstr1);
	//// Full Screen 開始
	//pVideoWindow->put_FullScreenMode(OATRUE);

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

	// Xinput初期化
	InitXinputState();

	// XAudio2
	InitSound();

	title.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // Titleの初期化
	selectstage.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // Selectの初期化
	gamescene.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // GameSceneの初期化
	result.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // Resultの初期化

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// 透明色
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
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

	// 資源を解放
	pMediaControl->Release();
	pGraphBuilder->Release();
	pVideoWindow->Release();

	// 解放処理
	title.Uninit();
	selectstage.Uninit();
	gamescene.Uninit();
	result.Uninit();
}
