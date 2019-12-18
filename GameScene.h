#pragma once
#include "Main.h"
#include "Input.h"
#include "xinpututil.h"
#include <math.h>

#define BLOCK_WIDTH		40				// ブロックの幅
#define BLOCK_HEIGHT	40				// ブロックの高さ

#define SEPARATEWIDTH   32				//画面分割数（横）
#define SEPARATEHEIGHT  18				//画面分割数（縦）
#define STAGEMAX		1 		        //ステージ数
#define MAX_TRIANGLE    20				//最大三角形設置可能数（ステージ毎）

#define Gravity		      0.1			// 重力
#define JumpASpeed		 -15			// ジャンプ力


enum MAPCHIP {
	NONE = -1,
	BLOCK,
};

// ゲームシーン
class GameScene
{
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


	//実装したいステージ数を設定して描画と更新
	class SetMapChip
	{
	public:

		LPDIRECT3DTEXTURE9  Blocktex[1] = { NULL };    // テクスチャを格納する変数(地面)
		static int stage;								//ステージ数ー１

		//[ステージ数][y][x](テクスチャ番号)
		static int Blocktexinfo[STAGEMAX][SEPARATEHEIGHT][SEPARATEWIDTH]; 

		//void LoadMapchip(int stage);
		void InitMapchip(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);
		void UpdateMapchip();
		void DrawMapchip(LPDIRECT3DDEVICE9 *device);
		void Uninit();
	private:
		void DrawBlock(LPDIRECT3DDEVICE9 device);
		void DrawDiagonalMapchip(LPDIRECT3DDEVICE9 device);

		//→ｘ		↓ｙ
		//第一段階（ブロック）
		VERTEX_2D StageBlock[VERTEX_MAX];					

		void SetTriangleTex(float x1, float y1, float x2, float y2, float x3, float y3, int texnum, LPDIRECT3DDEVICE9 device);

		//第二段階（斜め方向(三角形）などのマップチップ）
		VERTEX_2D DiagonalMapchip[STAGEMAX][20][3];//[ステージ数][三角形の数(テクスチャ番号）][頂点数]
	};

	class Player
	{
	private:
		D3DXVECTOR2 PlayerSpeed;							//速度
		D3DXVECTOR2 PlayerAddSpeed;							//加速度

		bool JumpFg;										//地面についてる時のみ可能
		bool LandFg;										//地面についているときtrue

	public:
		void FreeFall();									 //重力処理
		void PlayerOperation();								 //プレイヤー操作
		VERTEX_2D player_vertex[VERTEX_MAX];                 // player
		D3DVECTOR now_playerPosition;                        // player座標(現在座標)
		D3DVECTOR next_playerPosition;                       // player座標(次の座標)
		D3DXVECTOR2 m_shieldPosistion;						 // shield座標（描画用の変数は別に作る）
		bool SHIELD_Fg;										 //シールド出してるかフラグ
		bool isflg = false;                                  // 

		// XBOX(斜め移動)
		double moveHorizontal = 0;
		double moveVertical = 0;

		LPDIRECT3DTEXTURE9  m_player_pD3DTexture = NULL;     // テクスチャを格納する変数
		LPDIRECT3DTEXTURE9  m_shield_pD3DTexture = NULL;     // テクスチャを格納する変数

		Player();
		~Player();

		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // 初期化
		void Draw(LPDIRECT3DDEVICE9 *device);                                        // 描画
		void Update(int *scene);                                                     // 更新
		void Uninit(void);															 // 解放

		VERTEX_2D shield_vertex[VERTEX_MAX];
		void DesideShieldPlace();							//シールド位置決定
		VERTEX_2D sub_vector(const VERTEX_2D& a, const VERTEX_2D& b);
		int	BetweenPointsCollision(VERTEX_2D A, VERTEX_2D B, VERTEX_2D C, VERTEX_2D P);

	};


	
	Game game;      // 背景のオブジェクト
public:
	GameScene();
	~GameScene();

	Player player;
	SetMapChip mapchip;
	bool hitFlag = false;

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // 初期化
	void Draw(LPDIRECT3DDEVICE9 *device);                                        // 描画
	void Update(int *scene);                                                     // 更新
	void Uninit(void);                                                           // 解放

};
