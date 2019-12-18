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
#include "xinpututil.h"
#include <math.h>
#include <dshow.h>
#include <atlbase.h>

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

#define SCREEN_WIDTH	(1280)			// ウインドウの幅
#define SCREEN_HEIGHT	(720)			// ウインドウの高さ
#define VERTEX_MAX  (4)                 // 頂点の数
#define COLOR_MAX  (255)                // ディフューズ色の最大
#define KYARA_SPEED_MAX (5.0f*2)          // キャラのスピード
#define KYARA_FPS (15)                  // キャラのFPS
#define CURSOR_X  (80)                  // カーソルのX座標
#define CURSOR_Y  (80)					// カーソルのY座標
#define PLAYER_XSIZE  40.0f             // プレイヤーの大きさ
#define PLAYER_YSIZE  80.0f

#define SHIELD_THICKNESS	5				//シールドの厚さ
#define SHIELD_WIDTH		30				//シールドの幅
#define PBETWEENS			50				//キャラとシールドの間の距離
#define SEPARATEANGLE		16				//シールドの角度の分割数

#define BUTTON_SIZE_X (220)					// ボタンの大きさX
#define BUTTON_SIZE_Y (100)					// ボタンの大きさY
#define BUTTON_SIZEUP_X (15)				// ボタンのサイズアップX
#define BUTTON_SIZEUP_Y (15)				// ボタンのサイズアップY

#define XBOX_A (4096)                       // XBOXのAボタン
#define XBOX_B (8192)                       // XBOXのBボタン
#define XBOX_X (16384)                      // XBOXのXボタン
#define XBOX_Y (32768)                      // XBOXのYボタン
#define XBOX_START (16)                     // XBOXのSTARTボタン
#define XBOX_BACK (32)                      // XBOXのBACKボタン
#define XBOX_UP (1)                         // XBOXのUPボタン
#define XBOX_DOWN (2)                       // XBOXのDOWNボタン
#define XBOX_LEFT (4)                       // XBOXのLEFTボタン
#define XBOX_RIGHT (8)                      // XBOXのRIGHTボタン
#define XBOX_LB (256)                       // XBOXのLBボタン
#define XBOX_RB (512)                       // XBOXのRBボタン
#define XBOX_RSTICK_PUSH (128)              // XBOXの右スティック押し込み
#define XBOX_LSTICK_PUSH (64)               // XBOXの左スティック押し込み
#define XBOX_LSTICK_X (32768)			    // XBOXの左スティックの値
#define XBOX_LSTICK_Y (32768)			    // XBOXの左スティックの値

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

enum SCENE {
	TITLE,
	GAME,
	RESULT
};

#endif