#pragma once
#include"Main.h"
#include "Input.h"
#include"XAudio2.h"

// タイトル
class Title 
{
private: // フラグ用
	bool StartFlag;         // Startボタン表示切り替え
	bool OptionFlag;        // Optionボタン表示切り替え

	bool S_Push_Button;     // Start押されたかどうか
	bool OP_Push_Button;    // Option押されたかどうか

	bool Button_Change;     // ボタン切り替え

	bool OP_Change;         // オプション画面に切り替えるかどうか
	bool OP_Button_Change;  // オプション画面でのボタン切り替え

private: // 変数用
	int cnt = 0;   // カウント

private: // タイトル画面のスタートボタン(UI)

	VERTEX_2D title_StartButton[VERTEX_MAX];                // スタートボタン
	D3DVECTOR StartButtonPosition;                          // スタートボタン座標
	LPDIRECT3DTEXTURE9  StartButton_pD3DTexture = NULL;     // テクスチャを格納する変数(スタートボタン)
	LPDIRECT3DTEXTURE9  StartButton_pD3DTexture2 = NULL;    // テクスチャを格納する変数(スタートボタン)


private: // タイトル画面のオプションボタン(UI)

	VERTEX_2D title_OptionButton[VERTEX_MAX];                // オプションボタン
	D3DVECTOR OptionButtonPosition;                          // オプションボタン座標
	LPDIRECT3DTEXTURE9  OptionButton_pD3DTexture = NULL;     // テクスチャを格納する変数(オプションボタン)
	LPDIRECT3DTEXTURE9  OptionButton_pD3DTexture2 = NULL;    // テクスチャを格納する変数(オプションボタン)

private: // オプション画面
	// Option
	VERTEX_2D Option[VERTEX_MAX];                      // オプション
	D3DVECTOR OptionPosition;                          // オプションボタン座標

	// BGM
	VERTEX_2D BGM[VERTEX_MAX];                         // BGM
	D3DVECTOR BGMPosition;                             // BGM座標
	LPDIRECT3DTEXTURE9  BGM_pD3DTexture = NULL;        // テクスチャを格納する変数(BGM)
	LPDIRECT3DTEXTURE9  BGM__Bar_pD3DTexture = NULL;   // テクスチャを格納する変数(BGMのバー)

	// SE
	VERTEX_2D SE[VERTEX_MAX];                          // SE
	D3DVECTOR SEPosition;                              // SE座標
	LPDIRECT3DTEXTURE9  SE_pD3DTexture = NULL;         // テクスチャを格納する変数(SE)
	LPDIRECT3DTEXTURE9  SE_Bar_pD3DTexture = NULL;     // テクスチャを格納する変数(SEのバー)

public: // タイトル画面の背景

	VERTEX_2D title_vertex[VERTEX_MAX];                // タイトル
	LPDIRECT3DTEXTURE9  title_pD3DTexture = NULL;    // テクスチャを格納する変数(タイトル)

	Title();
	~Title();

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device,int *tex,POINT *pcl);     // 初期化
	void Draw(LPDIRECT3DDEVICE9 *device);                                      // 描画
	void Update(int *scene);                                                   // 更新
	void Uninit(void);                                                         // 解放


};

