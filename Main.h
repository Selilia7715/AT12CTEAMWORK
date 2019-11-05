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
#include "Input.h"


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
#define SCREEN_WIDTH	(1200)			// ウインドウの幅
#define SCREEN_HEIGHT	(600)			// ウインドウの高さ
#define VERTEX_MAX  (4)                 // 頂点の数
#define COLOR_MAX  (255)                // ディフューズ色の最大
#define KYARA_SPEED_MAX (6.0f)          // キャラのスピード
#define KYARA_FPS (15)                  // キャラのFPS
#define PLAYERBULLET_SPEED (20)         // playerの弾の速度
#define PLAYERROLL_SPEED (20)           // 自キャラの回転速度
#define ANGLE (90.0f)                      // 弾の角度
#define ROLL_MAX  (100)


enum SCENE
{
	TITLE = 1,
	GAME,
	RESULT
};

SCENE scene = TITLE;
#endif