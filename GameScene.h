#pragma once
#include "Main.h"
#include "Input.h"
#include "xinpututil.h"
#include <math.h>

#define BLOCK_WIDTH		40				// �u���b�N�̕�
#define BLOCK_HEIGHT	40				// �u���b�N�̍���

#define SEPARATEWIDTH   32				//��ʕ������i���j
#define SEPARATEHEIGHT  18				//��ʕ������i�c�j
#define STAGEMAX		1 		        //�X�e�[�W��
#define MAX_TRIANGLE    20				//�ő�O�p�`�ݒu�\���i�X�e�[�W���j

#define Gravity		      0.1			// �d��
#define JumpASpeed		 -15			// �W�����v��


enum MAPCHIP {
	NONE = -1,
	BLOCK,
};

// �Q�[���V�[��
class GameScene
{
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


	//�����������X�e�[�W����ݒ肵�ĕ`��ƍX�V
	class SetMapChip
	{
	public:

		LPDIRECT3DTEXTURE9  Blocktex[1] = { NULL };    // �e�N�X�`�����i�[����ϐ�(�n��)
		static int stage;								//�X�e�[�W���[�P

		//[�X�e�[�W��][y][x](�e�N�X�`���ԍ�)
		static int Blocktexinfo[STAGEMAX][SEPARATEHEIGHT][SEPARATEWIDTH]; 

		//void LoadMapchip(int stage);
		void InitMapchip(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);
		void UpdateMapchip();
		void DrawMapchip(LPDIRECT3DDEVICE9 *device);
		void Uninit();
	private:
		void DrawBlock(LPDIRECT3DDEVICE9 device);
		void DrawDiagonalMapchip(LPDIRECT3DDEVICE9 device);

		//����		����
		//���i�K�i�u���b�N�j
		VERTEX_2D StageBlock[VERTEX_MAX];					

		void SetTriangleTex(float x1, float y1, float x2, float y2, float x3, float y3, int texnum, LPDIRECT3DDEVICE9 device);

		//���i�K�i�΂ߕ���(�O�p�`�j�Ȃǂ̃}�b�v�`�b�v�j
		VERTEX_2D DiagonalMapchip[STAGEMAX][20][3];//[�X�e�[�W��][�O�p�`�̐�(�e�N�X�`���ԍ��j][���_��]
	};

	class Player
	{
	private:
		D3DXVECTOR2 PlayerSpeed;							//���x
		D3DXVECTOR2 PlayerAddSpeed;							//�����x

		bool JumpFg;										//�n�ʂɂ��Ă鎞�̂݉\
		bool LandFg;										//�n�ʂɂ��Ă���Ƃ�true

	public:
		void FreeFall();									 //�d�͏���
		void PlayerOperation();								 //�v���C���[����
		VERTEX_2D player_vertex[VERTEX_MAX];                 // player
		D3DVECTOR now_playerPosition;                        // player���W(���ݍ��W)
		D3DVECTOR next_playerPosition;                       // player���W(���̍��W)
		D3DXVECTOR2 m_shieldPosistion;						 // shield���W�i�`��p�̕ϐ��͕ʂɍ��j
		bool SHIELD_Fg;										 //�V�[���h�o���Ă邩�t���O
		bool isflg = false;                                  // 

		// XBOX(�΂߈ړ�)
		double moveHorizontal = 0;
		double moveVertical = 0;

		LPDIRECT3DTEXTURE9  m_player_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�
		LPDIRECT3DTEXTURE9  m_shield_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�

		Player();
		~Player();

		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
		void Draw(LPDIRECT3DDEVICE9 *device);                                        // �`��
		void Update(int *scene);                                                     // �X�V
		void Uninit(void);															 // ���

		VERTEX_2D shield_vertex[VERTEX_MAX];
		void DesideShieldPlace();							//�V�[���h�ʒu����
		VERTEX_2D sub_vector(const VERTEX_2D& a, const VERTEX_2D& b);
		int	BetweenPointsCollision(VERTEX_2D A, VERTEX_2D B, VERTEX_2D C, VERTEX_2D P);

	};


	
	Game game;      // �w�i�̃I�u�W�F�N�g
public:
	GameScene();
	~GameScene();

	Player player;
	SetMapChip mapchip;
	bool hitFlag = false;

	void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
	void Draw(LPDIRECT3DDEVICE9 *device);                                        // �`��
	void Update(int *scene);                                                     // �X�V
	void Uninit(void);                                                           // ���

};
