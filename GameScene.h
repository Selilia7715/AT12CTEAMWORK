#pragma once
#include "Main.h"
#include "Input.h"
#include "xinpututil.h"
#include <math.h>

#define BLOCK_WIDTH			40
#define BLOCK_HEIGHT		40

#define SEPARATEWIDTH		32			//画面分割数（横）
#define SEPARATEHEIGHT		18			//画面分割数（縦）
#define STAGEMAX			1 		    //ステージ数
#define SEPARATESCROLLNUM	1.2//大きくするとスクロールまでが早くなる（２で真ん中、１で一番端）

										//60fps
#define	ERASEBLOCKTIME	240				//ブロックジェネレータが出したブロックが消えるまでの時間
#define CREATEBLOCKRATE 240				//ブロックジェネレータがブロックを出す間隔

#define Gravity		      0.1
#define JumpASpeed		  -30

enum MAPCHIP {
	NONE = -1,
	BLOCK,
	
	GOAL,
	
};

enum DIRECTION {
	NORMAL,
	UP,
	DAWN,
	RIGHT,
	LEFT
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
		static int stage[STAGEMAX];									   //ステージ数ー１
		//int stagewidth[STAGEMAX] = { 320 };			   //ステージごとの横幅				

		//[ステージ数][y][x](テクスチャ番号)
		static int Stage1Blocktexinfo[SEPARATEHEIGHT][320]; 
		static float CameraCoord;					//ステージのｘ座標(Playerで起動、Stage関数、画面スクロール時に使用)

		
		//void LoadMapchip(int stage);
		void InitMapchip(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);
		void UpdateMapchip(int num);													//引数：どのステージを描画するか
		void DrawMapchip(LPDIRECT3DDEVICE9 *device);
		void Uninit();
		
		static void UpdateStageCoord();					//画面スクロール
	private:
		void DrawBlock(LPDIRECT3DDEVICE9 device);										//基本的に動かなくて四角のブロック
		void DrawDiagonalMapchip(LPDIRECT3DDEVICE9 device);


														
		//→ｘ		↓ｙ
		//第一段階（ブロック）
		VERTEX_2D StageBlock[VERTEX_MAX];					

		void SetTriangleTex(float x1, float y1, float x2, float y2, float x3, float y3, int texnum, LPDIRECT3DDEVICE9 device);

		//第二段階（斜め方向(三角形）などのマップチップ）
		VERTEX_2D DiagonalMapchip[STAGEMAX][20][3];//[ステージ数][三角形の数(テクスチャ番号）][頂点数]

	protected:
		int currentstagenum = 1;											//現在どのステージが描画されてるか
	};

	class Player
	{
	private:
		D3DXVECTOR2 PlayerSpeed;							//速度
		D3DXVECTOR2 PlayerAddSpeed;							//加速度

		bool JumpFg;										//地面についてる時のみ可能
		bool LandFg;										//地面についているときtrue

		//↓updateに入れる
		//重力処理
		void FreeFall();
		//プレイヤー操作
		void CheckLand();							//地面についてるかチェック


	public:

		VERTEX_2D player_vertex[VERTEX_MAX];				 // player
		static D3DVECTOR m_playerPosition;                   // player座標
		D3DXVECTOR2 m_shieldPosistion;						 // shield座標（描画用の変数は別に作る）
		bool SHIELD_Fg;										 //シールド出してるかフラグ
		bool isflg = false;                                  // 

		LPDIRECT3DTEXTURE9  m_player_pD3DTexture = NULL;     // テクスチャを格納する変数
		LPDIRECT3DTEXTURE9  m_shield_pD3DTexture = NULL;     // テクスチャを格納する変数

		Player();
		~Player();

		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // 初期化
		void Draw(LPDIRECT3DDEVICE9 *device);                                        // 描画
		void Update(int *scene);                                                     // 更新
		void PlayerOperation();								//プレイヤー操作
		void Uninit(void);															// 解放

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
