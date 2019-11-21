#include "GameScene.h"

// GameScene�̃R���X�g���N�^
GameScene::GameScene()
{
}

// GameScene�̃f�X�g���N�^
GameScene::~GameScene()
{
}

// GameScene�̏�����
void GameScene::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl) {
	player.Init(pHWND, device, tex, pcl);  // Player
	game.Init(pHWND, device, tex, pcl);	   // �w�i
}

// GameScene�̕`��
void GameScene::Draw(LPDIRECT3DDEVICE9 *device)
{
	player.Draw(device);  // Player
	game.Draw(device);	  // �w�i
}

// GameScene�̍X�V
void GameScene::Update(int *scene)
{
	player.Update(scene);  // Player
	game.Update();		   // �w�i
}

// GameScene�̉��
void GameScene::Uninit(void)
{
	player.Uninit();  // Player
	game.Uninit(); 	  // �w�i
}

// Player�̃R���X�g���N�^
GameScene::Player::Player()
{
	// �����l
	m_playerPosition.x = 500.0f;
	m_playerPosition.y = 300.0f;
}

// Player�̃f�X�g���N�^
GameScene::Player::~Player()
{

}

// Player�̏�����
void GameScene::Player::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// Player�`��(player)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/5.png", &m_player_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// Player�̍X�V
void GameScene::Player::Update(int *scene)
{
	// �}�E�X�g���Ƃ��̓R�����g�ɂ��遫
	// Player(�ʏ펞)
	VERTEX_2D player_vertex[4] = {
	   {m_playerPosition.x,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.0f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.0f},
	   {m_playerPosition.x,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.25f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.25f},
	};

	//�ړ�����
	// �����L�[
	// ��
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	m_playerPosition.x -= KYARA_SPEED_MAX;
	//}

	//// �E
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	m_playerPosition.x += KYARA_SPEED_MAX;
	//}

	//// ��
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	m_playerPosition.y -= KYARA_SPEED_MAX;
	//}

	//// ��
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

		center_x = player_vertex[0].x + PLAYER_SIZE / 2;  // �|���S���̔���
		center_y = player_vertex[0].y + PLAYER_SIZE / 2;

		for (int i = 0; i < 4; i++)
		{
			player_vertex[i].x = ((roll_x[i] - center_x) * cos(angle)) + ((roll_x[i] - center_y) * sin(angle)) + center_x;
			player_vertex[i].y = ((roll_y[i] - center_y) * cos(angle)) - ((roll_y[i] - center_x) * sin(angle)) + center_y;
		}

	}

	// �V�[���J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		*scene = 3;
	}
}

// Player�̕`��
void GameScene::Player::Draw(LPDIRECT3DDEVICE9 *device)
{
	// Player(�ʏ펞)
	VERTEX_2D player_vertex[4] = {
	   {m_playerPosition.x,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.0f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.0f},
	   {m_playerPosition.x,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.25f},
	   {m_playerPosition.x + PLAYER_SIZE,m_playerPosition.y + PLAYER_SIZE,m_playerPosition.z,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.25f},
	};

	//// Player(�}�E�X�g�p��)
	//VERTEX_2D player_vertex[4] = {
	//   {(*pcl).x,(*pcl).y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.0f},
	//   {(*pcl).x + CURSOR_X,(*pcl).y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.0f},
	//   {(*pcl).x,(*pcl).y + CURSOR_Y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.0f,0.25f},
	//   {(*pcl).x + CURSOR_X,(*pcl).y + CURSOR_Y,0.0f,1,D3DCOLOR_ARGB(255,255,255,255),0.33f,0.25f},
	//};

	// player�̕`��
	(*device)->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	(*device)->SetTexture(0, m_player_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&player_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

// Player�̏I������
void GameScene::Player::Uninit()
{
	// �e�N�X�`���̉��
	if (m_player_pD3DTexture != NULL)
	{
		m_player_pD3DTexture->Release();
		m_player_pD3DTexture = NULL;
	}
}

// �w�i�̃R���X�g���N�^
GameScene::Game::Game()
{
}

// �w�i�̃f�X�g���N�^
GameScene::Game::~Game()
{
}

// �w�i�̏�����
void GameScene::Game::Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl)
{
	// �e�N�X�`���`��(�w�i)
	if (FAILED(D3DXCreateTextureFromFile(*device, "rom/46.jpg", &m_game_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		*tex = MessageBox(*pHWND, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (*tex == IDYES)
		{
			DestroyWindow(*pHWND);
		}
	}
}

// �w�i�̕`��	
void GameScene::Game::Draw(LPDIRECT3DDEVICE9 *device)
{
	// �w�i
	VERTEX_2D game_vertex[4] = {
	{0,0,1,1,D3DCOLOR_ARGB(255,255,255,255),0,0},
	{SCREEN_WIDTH,0,1,1,D3DCOLOR_ARGB(255,255,255,255),1,0},
	{0,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),0,1},
	{SCREEN_WIDTH,SCREEN_HEIGHT,1,1,D3DCOLOR_ARGB(255,255,255,255),1,1},
	};

	// �w�i�`��
	(*device)->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	(*device)->SetTexture(0, m_game_pD3DTexture);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	(*device)->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&game_vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

// �w�i�̍X�V
void GameScene::Game::Update()
{
	// ��
}

// �w�i�̏I������
void GameScene::Game::Uninit()
{
	// �e�N�X�`���̉��
	if (m_game_pD3DTexture != NULL)
	{
		m_game_pD3DTexture->Release();
		m_game_pD3DTexture = NULL;
	}
}


