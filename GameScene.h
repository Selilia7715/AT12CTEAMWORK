#pragma once
#include "Main.h"
#include "Input.h"
#include "xinpututil.h"
#include <math.h>

#define BLOCK_WIDTH			40
#define BLOCK_HEIGHT		40

#define SEPARATEWIDTH		32			//��ʕ������i���j
#define SEPARATEHEIGHT		18			//��ʕ������i�c�j
#define STAGEMAX			1 		    //�X�e�[�W��
#define SEPARATESCROLLNUM	1.2//�傫������ƃX�N���[���܂ł������Ȃ�i�Q�Ő^�񒆁A�P�ň�Ԓ[�j

										//60fps
#define	ERASEBLOCKTIME	240				//�u���b�N�W�F�l���[�^���o�����u���b�N��������܂ł̎���
#define CREATEBLOCKRATE 240				//�u���b�N�W�F�l���[�^���u���b�N���o���Ԋu

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
		static int stage[STAGEMAX];									   //�X�e�[�W���[�P
		//int stagewidth[STAGEMAX] = { 320 };			   //�X�e�[�W���Ƃ̉���				

		//[�X�e�[�W��][y][x](�e�N�X�`���ԍ�)
		static int Stage1Blocktexinfo[SEPARATEHEIGHT][320]; 
		static float CameraCoord;					//�X�e�[�W�̂����W(Player�ŋN���AStage�֐��A��ʃX�N���[�����Ɏg�p)

		
		//void LoadMapchip(int stage);
		void InitMapchip(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);
		void UpdateMapchip(int num);													//�����F�ǂ̃X�e�[�W��`�悷�邩
		void DrawMapchip(LPDIRECT3DDEVICE9 *device);
		void Uninit();
		
		static void UpdateStageCoord();					//��ʃX�N���[��
	private:
		void DrawBlock(LPDIRECT3DDEVICE9 device);										//��{�I�ɓ����Ȃ��Ďl�p�̃u���b�N
		void DrawDiagonalMapchip(LPDIRECT3DDEVICE9 device);


														
		//����		����
		//���i�K�i�u���b�N�j
		VERTEX_2D StageBlock[VERTEX_MAX];					

		void SetTriangleTex(float x1, float y1, float x2, float y2, float x3, float y3, int texnum, LPDIRECT3DDEVICE9 device);

		//���i�K�i�΂ߕ���(�O�p�`�j�Ȃǂ̃}�b�v�`�b�v�j
		VERTEX_2D DiagonalMapchip[STAGEMAX][20][3];//[�X�e�[�W��][�O�p�`�̐�(�e�N�X�`���ԍ��j][���_��]

	protected:
		int currentstagenum = 1;											//���݂ǂ̃X�e�[�W���`�悳��Ă邩
	};

	class Player
	{
	private:
		D3DXVECTOR2 PlayerSpeed;							//���x
		D3DXVECTOR2 PlayerAddSpeed;							//�����x

		bool JumpFg;										//�n�ʂɂ��Ă鎞�̂݉\
		bool LandFg;										//�n�ʂɂ��Ă���Ƃ�true

		//��update�ɓ����
		//�d�͏���
		void FreeFall();
		//�v���C���[����
		void CheckLand();							//�n�ʂɂ��Ă邩�`�F�b�N


	public:

		VERTEX_2D player_vertex[VERTEX_MAX];				 // player
		static D3DVECTOR m_playerPosition;                   // player���W
		D3DXVECTOR2 m_shieldPosistion;						 // shield���W�i�`��p�̕ϐ��͕ʂɍ��j
		bool SHIELD_Fg;										 //�V�[���h�o���Ă邩�t���O
		bool isflg = false;                                  // 

		LPDIRECT3DTEXTURE9  m_player_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�
		LPDIRECT3DTEXTURE9  m_shield_pD3DTexture = NULL;     // �e�N�X�`�����i�[����ϐ�

		Player();
		~Player();

		void Init(HWND *pHWND, LPDIRECT3DDEVICE9 *device, int *tex, POINT *pcl);     // ������
		void Draw(LPDIRECT3DDEVICE9 *device);                                        // �`��
		void Update(int *scene);                                                     // �X�V
		void PlayerOperation();								//�v���C���[����
		void Uninit(void);															// ���

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
