#pragma once
#include "Main.h"
#include "BaseScene.h"
#include "Input.h"

// �Q�[���V�[��
class GameScene :public BaseScene
{
public:// �l�X�g�N���X(����q)
	// Player
	class Player  
	{
	public:		

		D3DVECTOR m_playerPosition;                          // player���W
		LPDIRECT3DTEXTURE9  m_player_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�

		Player();
		~Player();

		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
		void Draw(LPDIRECT3DDEVICE9 *device);                                        // �`��
		void Update(int *scene);                                                     // �X�V
		void Uninit(void);															// ���

		float angle = 0.0f;
		float roll_x[4], roll_y[4];
		float center_x;
		float center_y;
	};

	// �w�i
	class Game
	{
	public:
		LPDIRECT3DTEXTURE9  m_game_pD3DTexture = NULL;    // �e�N�X�`�����i�[����ϐ�(�w�i)

		Game();
		~Game();
		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
		void Draw(LPDIRECT3DDEVICE9 *device);                            // �`��
		void Update(void);                                               // �X�V
		void Uninit(void);                                               // ���
	};

	Player player;  // Player�̃I�u�W�F�N�g
	Game game;      // �w�i�̃I�u�W�F�N�g

public:
	GameScene();
	~GameScene();


	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
	void Draw(LPDIRECT3DDEVICE9 *device);                                        // �`��
	void Update(int *scene);                                                     // �X�V
	void Uninit(void);                                                           // ���
};



