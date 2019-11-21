#pragma once
#include "Main.h"
#include "BaseScene.h"
#include "Input.h"

// ゲームシーン
class GameScene :public BaseScene
{
public:// ネストクラス(入れ子)
	// Player
	class Player  
	{
	public:		

		D3DVECTOR m_playerPosition;                          // player座標
		LPDIRECT3DTEXTURE9  m_player_pD3DTexture = NULL;     // テクスチャを格納する変数

		Player();
		~Player();

		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // 初期化
		void Draw(LPDIRECT3DDEVICE9 *device);                                        // 描画
		void Update(int *scene);                                                     // 更新
		void Uninit(void);															// 解放

		float angle = 0.0f;
		float roll_x[4], roll_y[4];
		float center_x;
		float center_y;
	};

	// 背景
	class Game
	{
	public:
		LPDIRECT3DTEXTURE9  m_game_pD3DTexture = NULL;    // テクスチャを格納する変数(背景)

		Game();
		~Game();
		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // 初期化
		void Draw(LPDIRECT3DDEVICE9 *device);                            // 描画
		void Update(void);                                               // 更新
		void Uninit(void);                                               // 解放
	};

	Player player;  // Playerのオブジェクト
	Game game;      // 背景のオブジェクト

public:
	GameScene();
	~GameScene();


	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // 初期化
	void Draw(LPDIRECT3DDEVICE9 *device);                                        // 描画
	void Update(int *scene);                                                     // 更新
	void Uninit(void);                                                           // 解放
};



