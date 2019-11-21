#include "GameScene.h"

// GameSceneのコンストラクタ
GameScene::GameScene()
{
}

// GameSceneのデストラクタ
GameScene::~GameScene()
{
}

// GameSceneの初期化
void GameScene::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl) {
	player.Init(pHWND, device, tex, pcl);  // Player
	game.Init(pHWND, device, tex, pcl);	   // 背景
}

// GameSceneの描画
void GameScene::Draw(LPDIRECT3DDEVICE9 *device)
{
	player.Draw(device);  // Player
	game.Draw(device);	  // 背景
}

// GameSceneの更新
void GameScene::Update(int *scene)
{
	player.Update(scene);  // Player
	game.Update();		   // 背景
}

// GameSceneの解放
void GameScene::Uninit(void)
{
	player.Uninit();  // Player
	game.Uninit(); 	  // 背景
}

// Playerのコンストラクタ
GameScene::Player::Player()
{
	// 初期値
	m_playerPosition.x = 500.0f;
	m_playerPosition.y = 300.0f;
}

// Playerのデストラクタ
GameScene::Player::~Player()
{

}

// Playerの初期化
void GameScene::Player::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// Player描画(player)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/5.png", &m_player_pD3DTexture)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		*tex = MessageBox(*pHWND, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// Playerの更新
void GameScene::Player::Update(int *scene)
{
	// マウス使うときはコメントにする↓
	// Player(通常時)
	VERTEX_2D player_vertex[4] = {
	   {m_playerPosition.x,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.0f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.0f},
	   {m_playerPosition.x,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.25f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.25f},
	};

	//移動処理
	// 方向キー
	// 左
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	m_playerPosition.x -= KYARA_SPEED_MAX;
	//}

	//// 右
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	m_playerPosition.x += KYARA_SPEED_MAX;
	//}

	//// 上
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	m_playerPosition.y -= KYARA_SPEED_MAX;
	//}

	//// 下
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	m_playerPosition.y += KYARA_SPEED_MAX;
	//}

	if (GetKeyboardPress(DIK_SPACE))
	{
		angle += 10.0f;

		for (int i = 0; i < 4; i++)
		{
			roll_x[i] = player_vertex[i].x;
			roll_y[i] = player_vertex[i].y;
		}

		center_x = player_vertex[0].x + PLAYER_SIZE / 2;  // ポリゴンの半分
		center_y = player_vertex[0].y + PLAYER_SIZE / 2;

		for (int i = 0; i < 4; i++)
		{
			player_vertex[i].x = ((roll_x[i] - center_x) * cos(angle)) + ((roll_x[i] - center_y) * sin(angle)) + center_x;
			player_vertex[i].y = ((roll_y[i] - center_y) * cos(angle)) - ((roll_y[i] - center_x) * sin(angle)) + center_y;
		}

	}

	// シーン遷移
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 3;
	}
}

// Playerの描画
void GameScene::Player::Draw(LPDIRECT3DDEVICE9 *device)
{
	// Player(通常時)
	VERTEX_2D player_vertex[4] = {
	   {m_playerPosition.x,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.0f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.0f},
	   {m_playerPosition.x,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.25f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.25f},
	};

	//// Player(マウス使用時)
	//VERTEX_2D player_vertex[4] = {
	//   {(*pcl).x,(*pcl).y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.0f},
	//   {(*pcl).x + CURSOR_X,(*pcl).y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.0f},
	//   {(*pcl).x,(*pcl).y + CURSOR_Y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.25f},
	//   {(*pcl).x + CURSOR_X,(*pcl).y + CURSOR_Y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.25f},
	//};

	// playerの描画
	(*device)->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	(*device)->SetTexture(0, m_player_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&player_vertex[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

// Playerの終了処理
void GameScene::Player::Uninit()
{
	// テクスチャの解放
	if (m_player_pD3DTexture != NULL)
	{
		m_player_pD3DTexture->Release();
		m_player_pD3DTexture = NULL;
	}
}

// 背景のコンストラクタ
GameScene::Game::Game()
{
}

// 背景のデストラクタ
GameScene::Game::~Game()
{
}

// 背景の初期化
void GameScene::Game::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// テクスチャ描画(背景)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/46.jpg", &m_game_pD3DTexture)) == 1) {
		// メッセージBOXで「テクスチャロード失敗」と表示
		*tex = MessageBox(*pHWND, "テクスチャロード失敗", "失敗", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// 背景の描画	
void GameScene::Game::Draw(LPDIRECT3DDEVICE9 *device)
{
	// 背景
	VERTEX_2D game_vertex[4] = {
	{0,0,1,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,1,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

	// 背景描画
	(*device)->SetFVF(FVF_VERTEX_2D);
	// テクスチャをポリゴンにセット
	(*device)->SetTexture(0, m_game_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUPを呼ぶ
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // ポリゴンの種類(三角、四角など)
		2,                   // ポリゴンの数
		&game_vertex[0],          // 頂点データ構造体の先頭アドレス
		sizeof(VERTEX_2D)    // 頂点データ構造体のサイズ
	);
}

// 背景の更新
void GameScene::Game::Update()
{
	// 空欄
}

// 背景の終了処理
void GameScene::Game::Uninit()
{
	// テクスチャの解放
	if (m_game_pD3DTexture != NULL)
	{
		m_game_pD3DTexture->Release();
		m_game_pD3DTexture = NULL;
	}
}


