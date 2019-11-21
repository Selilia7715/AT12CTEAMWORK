//=============================================================================
//
// DX21
// DirectX雛型処理 [main.h]
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "d3dx9.h"						// 描画処理に必要
#include "XAudio2.h"


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に
// 対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")		// 描画処理に必要
#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]の拡張ライブラリ
#pragma comment (lib, "dxguid.lib")		// DirectXコンポーネント使用に必要
#pragma comment(lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")      // 現在時刻取得等に必要

#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CLASS_NAME		"サンプル"				// ウインドウクラスの名前
#define WINDOW_NAME		"DirectX雛型処理"	// ウィンドウの名前
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// FPS設定
#define FPS (60)

#define SCREEN_WIDTH	(1200)			// ウインドウの幅
#define SCREEN_HEIGHT	(600)			// ウインドウの高さ
#define VERTEX_MAX  (4)                 // 頂点の数
#define COLOR_MAX  (255)                // ディフューズ色の最大
#define KYARA_SPEED_MAX (20.0f)          // キャラのスピード
#define KYARA_FPS (15)                  // キャラのFPS
#define CURSOR_X  (80)                  // カーソルのX座標
#define CURSOR_Y  (80)					// カーソルのY座標
#define PLAYER_SIZE (80.0f)             // プレイヤーの大きさ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct VERTEX_2D {
	float x, y, z;
	float rhw;
	DWORD col;
	float u, v;  // テクスチャ座標
}VERTEX_2D;

#endif