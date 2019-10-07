//=============================================================================
//
// DX21
// DirectX���^���� [main.cpp]
//
//=============================================================================
#include "Main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	CLASS_NAME		"�T���v��"				// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"Run Gun"	// �E�B���h�E�̖��O
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// FPS�ݒ�
#define FPS (60)

// �A�j���[�V�����̌���
#define ANM_DOWN (0)
#define ANM_LEFT (1)
#define ANM_RIGHT (2)
#define ANM_UP (3)

// �A�j���[�V�����p�^�[����
#define ANM_MAX (4)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct VERTEX_2D {
	float x, y, z;
	float rhw;
	D3DCOLOR col;
	float u, v;  // �e�N�X�`�����W
}VERTEX_2D;

VERTEX_2D vertex[VERTEX_MAX];     // ���L����(�L����1)
VERTEX_2D vertex2[VERTEX_MAX];     // �w�i
VERTEX_2D vertex3[VERTEX_MAX];     // �L����2
VERTEX_2D vertex4[VERTEX_MAX];     // �^�C�g��
VERTEX_2D vertex5[VERTEX_MAX];     // �O���t�H��
VERTEX_2D vertex6[VERTEX_MAX];     // �h���S��
VERTEX_2D vertex7[VERTEX_MAX];     // �L����3
VERTEX_2D vertex8[VERTEX_MAX];     // �J�[�\��
VERTEX_2D vertex9[VERTEX_MAX];     // ���U���g
VERTEX_2D vertex10[VERTEX_MAX];     // score1
VERTEX_2D vertex11[VERTEX_MAX];     // score2
VERTEX_2D vertex12[VERTEX_MAX];     // score3
VERTEX_2D vertex13[VERTEX_MAX];     // �N���A
VERTEX_2D vertex14[VERTEX_MAX];     // hit
VERTEX_2D vertex15[VERTEX_MAX];     // ����	
VERTEX_2D vertex16[VERTEX_MAX];     // �����{�^��
VERTEX_2D vertex17[VERTEX_MAX];     // �߂�{�^��
VERTEX_2D vertex18[VERTEX_MAX];     // ���փ{�^��
VERTEX_2D vertex19[VERTEX_MAX];     // �Q�[���{�^��
VERTEX_2D vertex20[VERTEX_MAX];     // �^�C�g���ɖ߂�{�^��
VERTEX_2D vertex21[VERTEX_MAX];     // ���g���C�{�^��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void Hit(void);      // �����蔻��
void Main(void);     // �^�C�g�����
void MainDraw(void);
void MainUpdate(void);
void Result(void);   // ���U���g���
void ResultDraw(void);
void ResultUpdate(void);
void Clear(void);    // �N���A���
void ClearDraw(void);
void ClearUpdate(void);
void SetumeiDraw(void);   // ����
void SetumeiUpdate(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
LPDIRECT3DTEXTURE9  g_pD3DTexture1 = NULL;    // �e�N�X�`�����i�[����ϐ�(�L����1)
LPDIRECT3DTEXTURE9  g_pD3DTexture2 = NULL;    // �e�N�X�`�����i�[����ϐ�(�w�i)
LPDIRECT3DTEXTURE9  g_pD3DTexture3 = NULL;    // �e�N�X�`�����i�[����ϐ�(�L����2)
LPDIRECT3DTEXTURE9  g_pD3DTexture4 = NULL;    // �e�N�X�`�����i�[����ϐ�(�^�C�g��)
LPDIRECT3DTEXTURE9  g_pD3DTexture5 = NULL;    // �e�N�X�`�����i�[����ϐ�(�O���t�H��)
LPDIRECT3DTEXTURE9  g_pD3DTexture6 = NULL;    // �e�N�X�`�����i�[����ϐ�(�h���S��)
LPDIRECT3DTEXTURE9  g_pD3DTexture7 = NULL;    // �e�N�X�`�����i�[����ϐ�(�L����3)
LPDIRECT3DTEXTURE9  g_pD3DTexture8 = NULL;    // �e�N�X�`�����i�[����ϐ�(�J�[�\��)
LPDIRECT3DTEXTURE9  g_pD3DTexture9 = NULL;    // �e�N�X�`�����i�[����ϐ�(���U���g)
LPDIRECT3DTEXTURE9  g_pD3DTexture10 = NULL;    // �e�N�X�`�����i�[����ϐ�(score1)
LPDIRECT3DTEXTURE9  g_pD3DTexture11 = NULL;    // �e�N�X�`�����i�[����ϐ�(score2)
LPDIRECT3DTEXTURE9  g_pD3DTexture12 = NULL;    // �e�N�X�`�����i�[����ϐ�(score3)
LPDIRECT3DTEXTURE9  g_pD3DTexture13 = NULL;    // �e�N�X�`�����i�[����ϐ�(�N���A)
LPDIRECT3DTEXTURE9  g_pD3DTexture14 = NULL;    // �e�N�X�`�����i�[����ϐ�(hit)
LPDIRECT3DTEXTURE9  g_pD3DTexture15 = NULL;    // �e�N�X�`�����i�[����ϐ�(����)
LPDIRECT3DTEXTURE9  g_pD3DTexture21 = NULL;    // �e�N�X�`�����i�[����ϐ�(����2)
LPDIRECT3DTEXTURE9  g_pD3DTexture16 = NULL;    // �e�N�X�`�����i�[����ϐ�(�����{�^��)
LPDIRECT3DTEXTURE9  g_pD3DTexture17 = NULL;    // �e�N�X�`�����i�[����ϐ�(�J�[�\��2)
LPDIRECT3DTEXTURE9  g_pD3DTexture18 = NULL;    // �e�N�X�`�����i�[����ϐ�(�߂�{�^��)
LPDIRECT3DTEXTURE9  g_pD3DTexture19 = NULL;    // �e�N�X�`�����i�[����ϐ�(���փ{�^��)
LPDIRECT3DTEXTURE9  g_pD3DTexture20 = NULL;    // �e�N�X�`�����i�[����ϐ�(�Q�[���{�^��)
LPDIRECT3DTEXTURE9  g_pD3DTexture22 = NULL;    // �e�N�X�`�����i�[����ϐ�(�^�C�g���ɖ߂�{�^��)
LPDIRECT3DTEXTURE9  g_pD3DTexture23 = NULL;    // �e�N�X�`�����i�[����ϐ�(���g���C�{�^��)


LPD3DXFONT g_pD3DXFont = NULL;

D3DVECTOR g_playerPosition;  // ��l�����W
D3DVECTOR g_enemyPosition;   // �G���W
D3DVECTOR g_griPosition;     // �O���t�H�����W
D3DVECTOR g_draPosition;     // �h���S�����W
D3DVECTOR g_enemy2Position;   // �G2���W
D3DVECTOR g_effectPosition;   // �G�t�F�N�g���W
D3DVECTOR g_setumeiPosition;   // �����{�^�����W
D3DVECTOR g_returnPosition;   // �߂�{�^�����W
D3DVECTOR g_nextPosition;   // ���փ{�^�����W
D3DVECTOR g_gamePosition;   // �Q�[���{�^�����W
D3DVECTOR g_endPosition;   // �^�C�g���ɖ߂�{�^�����W
D3DVECTOR g_retryPosition;   // ���g���C�{�^�����W

POINT cl;  // �J�[�\���̍��W�̕ϐ�

// �A�j���[�V��������p�ϐ�
int g_anmCnt = 0; 
int g_anmNum = 0;
int g_anmSpeed = 15;

// �L����1
int g_anmDir = ANM_DOWN;
float g_anmTbl[ANM_MAX] = { 0.0f / 96.0f, 32.0f / 96.0f, 64.0f / 96.0f, 32.0f / 96.0f };

// �L����2
int g_anmDir2 = ANM_DOWN;
float g_anmTbl2[ANM_MAX] = { 0.0f / 96.0f, 32.0f / 96.0f, 64.0f / 96.0f, 32.0f / 96.0f };

// �O���t�H��
int g_anmDir3 = ANM_DOWN;
float g_anmTbl3[ANM_MAX] = { 0.0f / 135.0f, 45.0f / 135.0f, 90.0f / 135.0f, 45.0f / 135.0f };

// �h���S��
int g_anmDir4 = ANM_DOWN;
float g_anmTbl4[ANM_MAX] = { 0.0f / 240.0f, 80.0f / 240.0f, 160.0f / 240.0f, 80.0f / 240.0f };

// �L����3
int g_anmDir5 = ANM_DOWN;
float g_anmTbl5[ANM_MAX] = { 0.0f / 146.0f, 48.6f / 146.0f, 97.2f / 146.0f, 48.6f / 146.0f };

// FPS�Ǘ��p
int g_nCountFPS = 0;
float g_dispFPS = 0;

// �����_���p�ϐ�
int randam;  // �G�l�~�[�̈ړ��p

// �V�[���t���O
int SceneFlag = 0;

// �J�[�\���Əd�Ȃ�Ə����鏈��
bool Kyara2 = false;
bool Dora = false;
bool Gri = false;
bool Kyara3 = false;

// �����t���O
bool setumei = false;

// hit�t���O
bool hitFlag = false;

// HP�J�E���g
int enemylife;  // �G��̎��ʁ�1�J�E���g�Ƃ��� �ő�3�J�E���g
int life;       // ���L�����̗̑�
int grilife;    // �O���t�H���̗̑�
int kyara2life; // �L����2�̗̑�
int doralife;   // �h���S���̗̑�

int kyara2cnt = 0; // �L����2�\���̃J�E���g
int gricnt = 0;	   // �O���t�H���\���̃J�E���g
int doracnt = 0;   // �h���S���\���̃J�E���g

int hitcnt = 0;  // �q�b�g�\��
//=============================================================================
// ���C���֐�
//  (WINAPI : Win32API�֐����Ăяo�����̋K��)
//  hInstance     : ���̃A�v���P�[�V�����̃C���X�^���X�n���h��(���ʎq)
//  hPrevInstance : ���NULL(16bit����̖��c��)
//  lpCmdLine     : �R�}���h���C������󂯎���������ւ̃|�C���^
//  nCmdShow      : �A�v���P�[�V�����̏����E�C���h�E�\�����@�̎w��
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,						// �\������E�C���h�E�̃X�^�C����ݒ�
		WndProc,						// �E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,								// �ʏ�͎g�p���Ȃ��̂�"0"���w��
		0,								// �ʏ�͎g�p���Ȃ��̂�"0"���w��
		hInstance,						// WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
		NULL,							// �g�p����A�C�R�����w��(Windows�������Ă���A�C�R�����g���Ȃ�NULL)
		LoadCursor(NULL, IDC_ARROW),	// �}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),		// �E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�
		NULL,							// Window�ɂ��郁�j���[��ݒ�
		CLASS_NAME,						// �E�C���h�E�N���X�̖��O
		NULL							// �������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q
	};
	HWND hWnd;
	MSG msg;

	// FPS�Ǘ��p�ϐ�
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,						// �g���E�B���h�E�X�^�C��
		CLASS_NAME,				// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,			// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���x���W 
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2), // �E�B���h�E�̕�
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 +
			GetSystemMetrics(SM_CYCAPTION)), // �E�B���h�E�̍���
		NULL,					// �e�E�B���h�E�̃n���h��
		NULL,					// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,				// �C���X�^���X�n���h��
		NULL);					// �E�B���h�E�쐬�f�[�^

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// FPS�t���[���J�E���g������
	timeBeginPeriod(1); // ����\��ݒ�
	dwExecLastTime = timeGetTime(); // �V�X�e���������擾
	dwCurrentTime = dwFrameCount = 0;

	
	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂�āAWM_QUIT���b�Z�[�W�������烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / FPS))
			{
				g_dispFPS = (1000.0f / (dwCurrentTime - dwExecLastTime));
				dwExecLastTime = dwCurrentTime;
				
				UpdateInput();

				// Update&Init
				switch (SceneFlag)
				{
				case 0:
				// �^�C�g������
					Main();
					MainUpdate();
					break;

				case 1:
					// �X�V����
					Update();
					break;

				case 2:
					// �G���h����
					Result();
					ResultUpdate();
					break;

				case 3:
					// �N���A����
					Clear();
					ClearUpdate();
					break;

				case 4:
					// ��������
					SetumeiUpdate();
					break;
				}

				// �`�揈��(��񂵂��Ăяo���Ȃ�)
				g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
					D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

				if (SUCCEEDED(g_pD3DDevice->BeginScene()))
				{
					switch (SceneFlag)
					{
					case 0:
						MainDraw();
						break;

					case 1:
						Draw();
						break;

					case 2:
						ResultDraw();
						break;

					case 3:
						ClearDraw();
						break;

					case 4:
						SetumeiDraw();
						break;
					}
					// Direct3D�ɂ��`��̏I��
					g_pD3DDevice->EndScene();
				}
				g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
			}
		}
	}
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	//  ��P�����F���N���X��
	//  ��Q�����F�A�v���P�[�V�����C���X�^���X�̃n���h��
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	////////////////////////////////////////////////////////////////////////////////////////////
	// �J�[�\��
	GetCursorPos(&cl);  // ���W�擾
	ScreenToClient(hWnd, &cl); // �J�[�\���̉摜�ƂȂ���̂�\��(�����g_pD3DTexture8��\��)
	// �J�[�\���̕\��������(�}�E�X�J�[�\���̂��)
	ShowCursor(false); // �����Ƃ��̂܂�(true�ɂȂ�ƃ}�E�X�J�[�\�����o�Ă���)
	////////////////////////////////////////////////////////////////////////////////////////////

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I��", MB_YESNO);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

	/*	case VK_RIGHT:
			g_playerPosition.x += 5.0f;
			g_anmDir = ANM_RIGHT;
			break;

		case VK_LEFT:
			g_playerPosition.x -= 5.0f;
			g_anmDir = ANM_LEFT;
			break;


		case VK_DOWN:
			g_playerPosition.y += 5.0f;
			g_anmDir = ANM_DOWN;
			break;

		case VK_UP:
			g_playerPosition.y -= 5.0f;
			g_anmDir = ANM_UP;
			break;*/
		}
		break;

	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I��", MB_YESNO);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
// hInstance : �C���X�^���X�̃n���h��
// hWnd      : �E�C���h�E�̃n���h��
// bWindow   : �E�C���h�E���[�h�ɂ��邩�ǂ���
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	int aID;

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));						  	// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			  	// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.BackBufferCount = 1;						 // �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;     // �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;	// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;				 	// ���t���b�V�����[�g(�w��ł��Ȃ��̂�0�Œ�)
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		// �C���^�[�o��(VSync��҂����ɕ`��)
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		// �C���^�[�o��(VSync��҂��ĕ`��)
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,							// �f�o�C�X�^�C�v
		hWnd,								      	// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,   	// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,									    // �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// DirectInput
	InitInput(hInstance, hWnd);

	// XAudio2
	InitSound();

	// �����l(���W�ARHW�A�f�B�t���[�Y�F�̐ݒ�)

	// �e�N�X�`���`��(�^�C�g��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/title2.png", &g_pD3DTexture4)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(���U���g)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/gameover.png", &g_pD3DTexture9)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�N���A)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/clear.png", &g_pD3DTexture13)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(score1)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sysfont.png", &g_pD3DTexture10)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// �e�N�X�`���`��(score2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sysfont.png", &g_pD3DTexture11)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// �e�N�X�`���`��(score3)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sysfont.png", &g_pD3DTexture12)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// �e�N�X�`���`��(�L����1)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/5.png", &g_pD3DTexture1)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	// �e�N�X�`���`��(�J�[�\��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/scp1.png", &g_pD3DTexture8)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// �e�N�X�`���`��(hit)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/hit3.png", &g_pD3DTexture14)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�L����2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/6.png", &g_pD3DTexture3)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�O���t�H��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/gri.png", &g_pD3DTexture5)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�h���S��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/7.png", &g_pD3DTexture6)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�L����3)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/82.png", &g_pD3DTexture7)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�w�i)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/haikei3.jpg", &g_pD3DTexture2)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(����)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sousa1.png", &g_pD3DTexture15)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}	

	// �e�N�X�`���`��(����2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/sousa2.png", &g_pD3DTexture21)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}	
	
	// �e�N�X�`���`��(�����{�^��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/setumei.png", &g_pD3DTexture16)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// �e�N�X�`���`��(�J�[�\��2)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/cursor.png", &g_pD3DTexture17)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�߂�{�^��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/return.png", &g_pD3DTexture18)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(���փ{�^��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/return2.png", &g_pD3DTexture19)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// �e�N�X�`���`��(�Q�[���{�^��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/gamestart.png", &g_pD3DTexture20)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�^�C�g���ɖ߂�{�^��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/end.png", &g_pD3DTexture22)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(���g���C�{�^��)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/retry.png", &g_pD3DTexture23)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}
	
	// �����l(�|�W�V����)
	g_playerPosition.x = 600.0f;
	g_playerPosition.y = 400.0f;
	g_enemyPosition.x = 750.0f;
	g_enemyPosition.y = 250.0f;
	g_enemy2Position.x = 200.0f;
	g_enemy2Position.y = 300.0f;
	g_draPosition.x = 600.0f;
	g_draPosition.y = 140.0f;
	g_griPosition.x = 1000.0f;
	g_griPosition.y = 450.0f;

	// �L�����P
	// ���W�̒l
	vertex[0].x = g_playerPosition.x;
	vertex[0].y = g_playerPosition.y;
	vertex[0].z = g_playerPosition.z;

	vertex[1].x = g_playerPosition.x + 70.0f;
	vertex[1].y = g_playerPosition.y;
	vertex[1].z = g_playerPosition.z;

	vertex[2].x = g_playerPosition.x;
	vertex[2].y = g_playerPosition.y + 70.0f;
	vertex[2].z = g_playerPosition.z;

	vertex[3].x = g_playerPosition.x + 70.0f;
	vertex[3].y = g_playerPosition.y + 70.0f;
	vertex[3].z = g_playerPosition.z;

	// RHW�̒l
	vertex[0].rhw = 1.0f;
	vertex[1].rhw = 1.0f;
	vertex[2].rhw = 1.0f;
	vertex[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(3���ɐ؂邽��)
	vertex[0].u = 0.0f;
	vertex[0].v = 0.0f;
	vertex[1].u = 0.33f;
	vertex[1].v = 0.0f;
	vertex[2].u = 0.0f;
	vertex[2].v = 0.25f;
	vertex[3].u = 0.33f;
	vertex[3].v = 0.25f;

	////////////////////////////////////////////////
	// �J�[�\��
	////////////////////////////////////////////////
	// RHW�̒l
	vertex8[0].rhw = 1.0f;
	vertex8[1].rhw = 1.0f;
	vertex8[2].rhw = 1.0f;
	vertex8[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex8[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex8[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex8[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex8[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W
	vertex8[0].u = 0.0f;
	vertex8[0].v = 0.0f;
	vertex8[1].u = 1.0f;
	vertex8[1].v = 0.0f;
	vertex8[2].u = 0.0f;
	vertex8[2].v = 1.0f;
	vertex8[3].u = 1.0f;
	vertex8[3].v = 1.0f;
	////////////////////////////////////////////////


	if (Kyara2 == false)
	{
		// �L����2
	// ���W�̒l
		vertex3[0].x = g_enemyPosition.x + 400.0f;
		vertex3[0].y = g_enemyPosition.y + 140.0f;
		vertex3[0].z = g_enemyPosition.z;

		vertex3[1].x = g_enemyPosition.x + 464.0f;
		vertex3[1].y = g_enemyPosition.y + 140.0f;
		vertex3[1].z = g_enemyPosition.z;

		vertex3[2].x = g_enemyPosition.x + 400.0f;
		vertex3[2].y = g_enemyPosition.y + 204.0f;
		vertex3[2].z = g_enemyPosition.z;

		vertex3[3].x = g_enemyPosition.x + 464.0f;
		vertex3[3].y = g_enemyPosition.y + 204.0f;
		vertex3[3].z = g_enemyPosition.z;

		// RHW�̒l
		vertex3[0].rhw = 1.0f;
		vertex3[1].rhw = 1.0f;
		vertex3[2].rhw = 1.0f;
		vertex3[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex3[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex3[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex3[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex3[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// �e�N�X�`�����W(3���ɐ؂邽��)
		vertex3[0].u = 0.0f;
		vertex3[0].v = 0.0f;
		vertex3[1].u = 0.33f;
		vertex3[1].v = 0.0f;
		vertex3[2].u = 0.0f;
		vertex3[2].v = 0.25f;
		vertex3[3].u = 0.33f;
		vertex3[3].v = 0.25f;
	}
	
	if (Gri == false)
	{
		// �O���t�H���@
		vertex5[0].x = g_griPosition.x;
		vertex5[0].y = g_griPosition.y;
		vertex5[0].z = g_griPosition.z;

		vertex5[1].x = g_griPosition.x + 200.0f;
		vertex5[1].y = g_griPosition.y;
		vertex5[1].z = g_griPosition.z;

		vertex5[2].x = g_griPosition.x;
		vertex5[2].y = g_griPosition.y + 200.0f;
		vertex5[2].z = g_griPosition.z;

		vertex5[3].x = g_griPosition.x + 200.0f;
		vertex5[3].y = g_griPosition.y + 200.0f;
		vertex5[3].z = g_griPosition.z;

		vertex5[0].rhw = 1.0f;
		vertex5[1].rhw = 1.0f;
		vertex5[2].rhw = 1.0f;
		vertex5[3].rhw = 1.0f;

		vertex5[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertex5[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertex5[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertex5[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		vertex5[0].u = 0.0f;
		vertex5[0].v = 0.0f;
		vertex5[1].u = 0.33f;
		vertex5[1].v = 0.0f;
		vertex5[2].u = 0.0f;
		vertex5[2].v = 0.25f;
		vertex5[3].u = 0.33f;
		vertex5[3].v = 0.25f;

		// �w�i
		vertex2[0].x = 0.0f;
		vertex2[0].y = 0.0f;
		vertex2[0].z = 0.0f;

		vertex2[1].x = SCREEN_WIDTH;
		vertex2[1].y = 0.0f;
		vertex2[1].z = 0.0f;

		vertex2[2].x = 0.0f;
		vertex2[2].y = SCREEN_HEIGHT;
		vertex2[2].z = 0.0f;

		vertex2[3].x = SCREEN_WIDTH;
		vertex2[3].y = SCREEN_HEIGHT;
		vertex2[3].z = 0.0f;

		// RHW�̒l
		vertex2[0].rhw = 1.0f;
		vertex2[1].rhw = 1.0f;
		vertex2[2].rhw = 1.0f;
		vertex2[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex2[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex2[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex2[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex2[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
		vertex2[0].u = 0.0f;
		vertex2[0].v = 0.0f;
		vertex2[1].u = 1.0f;
		vertex2[1].v = 0.0f;
		vertex2[2].u = 0.0f;
		vertex2[2].v = 1.0f;
		vertex2[3].u = 1.0f;
		vertex2[3].v = 1.0f;
	}
	
	if (Dora == false)
	{
		// �h���S��
	// ���W�̒l
		vertex6[0].x = g_draPosition.x + 600.0f;
		vertex6[0].y = g_draPosition.y + 140.0f;
		vertex6[0].z = g_draPosition.z;

		vertex6[1].x = g_draPosition.x + 695.0f;
		vertex6[1].y = g_draPosition.y + 140.0f;
		vertex6[1].z = g_draPosition.z;

		vertex6[2].x = g_draPosition.x + 600.0f;
		vertex6[2].y = g_draPosition.y + 195.0f;
		vertex6[2].z = g_draPosition.z;

		vertex6[3].x = g_draPosition.x + 695.0f;
		vertex6[3].y = g_draPosition.y + 195.0f;
		vertex6[3].z = g_draPosition.z;

		// RHW�̒l
		vertex6[0].rhw = 1.0f;
		vertex6[1].rhw = 1.0f;
		vertex6[2].rhw = 1.0f;
		vertex6[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex6[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex6[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex6[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex6[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// �e�N�X�`�����W(3���ɐ؂邽��)
		vertex6[0].u = 0.0f;
		vertex6[0].v = 0.0f;
		vertex6[1].u = 0.33f;
		vertex6[1].v = 0.0f;
		vertex6[2].u = 0.0f;
		vertex6[2].v = 0.33f;
		vertex6[3].u = 0.33f;
		vertex6[3].v = 0.33f;

	}
	
	if (Kyara3 = false)
	{
		// �L����3
	// ���W�̒l
		vertex7[0].x = g_enemy2Position.x;
		vertex7[0].y = g_enemy2Position.y;
		vertex7[0].z = g_enemy2Position.z;

		vertex7[1].x = g_enemy2Position.x + 95.0f;
		vertex7[1].y = g_enemy2Position.y;
		vertex7[1].z = g_enemy2Position.z;

		vertex7[2].x = g_enemy2Position.x;
		vertex7[2].y = g_enemy2Position.y + 65.0f;
		vertex7[2].z = g_enemy2Position.z;

		vertex7[3].x = g_enemy2Position.x + 95.0f;
		vertex7[3].y = g_enemy2Position.y + 65.0f;
		vertex7[3].z = g_enemy2Position.z;

		// RHW�̒l
		vertex7[0].rhw = 1.0f;
		vertex7[1].rhw = 1.0f;
		vertex7[2].rhw = 1.0f;
		vertex7[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex7[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex7[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex7[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex7[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// �e�N�X�`�����W(3���ɐ؂邽��)
		vertex7[0].u = 0.0f;
		vertex7[0].v = 0.0f;
		vertex7[1].u = 0.25f;
		vertex7[1].v = 0.0f;
		vertex7[2].u = 0.0f;
		vertex7[2].v = 0.25f;
		vertex7[3].u = 0.25f;
		vertex7[3].v = 0.25f;
	}
	
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// �����F
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	UninitInput();

	UninitSound();

	// �e�N�X�`��1
	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// �e�N�X�`���̉��
	if (g_pD3DTexture1 != NULL) 
	{
		g_pD3DTexture1->Release();
		g_pD3DTexture1 = NULL;
	}

	// �e�N�X�`��2�̉��
	if (g_pD3DTexture2 != NULL)
	{
		g_pD3DTexture2->Release();
		g_pD3DTexture2 = NULL;
	}

	// �e�N�X�`��3�̉��
	if (g_pD3DTexture3 != NULL)
	{
		g_pD3DTexture3->Release();
		g_pD3DTexture3 = NULL;
	}

	// �e�N�X�`��4�̉��
	if (g_pD3DTexture4 != NULL)
	{
		g_pD3DTexture4->Release();
		g_pD3DTexture4 = NULL;
	}

	// �e�N�X�`��5�̉��
	if (g_pD3DTexture5 != NULL)
	{
		g_pD3DTexture5->Release();
		g_pD3DTexture5 = NULL;
	}

	// �e�N�X�`��6�̉��
	if (g_pD3DTexture6 != NULL)
	{
		g_pD3DTexture6->Release();
		g_pD3DTexture6 = NULL;
	}

	// �e�N�X�`��7�̉��
	if (g_pD3DTexture7 != NULL)
	{
		g_pD3DTexture7->Release();
		g_pD3DTexture7 = NULL;
	}

	// �e�N�X�`��8�̉�� �J�[�\��
	if (g_pD3DTexture8 != NULL)
	{
		g_pD3DTexture8->Release();
		g_pD3DTexture8 = NULL;
	}

	// �e�N�X�`��9�̉��
	if (g_pD3DTexture9 != NULL)
	{				 
		g_pD3DTexture9->Release();
		g_pD3DTexture9 = NULL;
	}

	// �e�N�X�`��10�̉��
	if (g_pD3DTexture10 != NULL)
	{				 
		g_pD3DTexture10->Release();
		g_pD3DTexture10 = NULL;
	}

	// �e�N�X�`��11�̉��
	if (g_pD3DTexture11 != NULL)
	{				 
		g_pD3DTexture11->Release();
		g_pD3DTexture11 = NULL;
	}

	// �e�N�X�`��12�̉��
	if (g_pD3DTexture12 != NULL)
	{				 
		g_pD3DTexture12->Release();
		g_pD3DTexture12 = NULL;
	}
	
	// �e�N�X�`��13�̉��
	if (g_pD3DTexture13 != NULL)
	{				 
		g_pD3DTexture13->Release();
		g_pD3DTexture13 = NULL;
	}
	
	// �e�N�X�`��14�̉��
	if (g_pD3DTexture14 != NULL)
	{				 
		g_pD3DTexture14->Release();
		g_pD3DTexture14 = NULL;
	}
	
	// �e�N�X�`��15�̉��
	if (g_pD3DTexture15 != NULL)
	{				 
		g_pD3DTexture15->Release();
		g_pD3DTexture15 = NULL;
	}
	
	// �e�N�X�`��16�̉��
	if (g_pD3DTexture16 != NULL)
	{				 
		g_pD3DTexture16->Release();
		g_pD3DTexture16 = NULL;
	}
	
	// �e�N�X�`��17�̉��
	if (g_pD3DTexture17 != NULL)
	{				 
		g_pD3DTexture17->Release();
		g_pD3DTexture17 = NULL;
	}

	// �e�N�X�`��18�̉��
	if (g_pD3DTexture18 != NULL)
	{				 
		g_pD3DTexture18->Release();
		g_pD3DTexture18 = NULL;
	}
	
	// �e�N�X�`��19�̉��
	if (g_pD3DTexture19 != NULL)
	{				 
		g_pD3DTexture19->Release();
		g_pD3DTexture19 = NULL;
	}	
	
	// �e�N�X�`��20�̉��
	if (g_pD3DTexture20 != NULL)
	{				 
		g_pD3DTexture20->Release();
		g_pD3DTexture20 = NULL;
	}

		// �e�N�X�`��21�̉��
	if (g_pD3DTexture21 != NULL)
	{				 
		g_pD3DTexture21->Release();
		g_pD3DTexture21 = NULL;
	}
}

//=============================================================================
// �Q�[����ʏ���
//=============================================================================
void Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	// Count   : pRects�z��ɂ����`�̐�
	// pRects  : �N���A�����`�̔z��(NULL�w��Ńr���[�|�[�g��`�S�̂��N���A)
	// Flags   : �N���A����T�[�t�F�X�������t���O(���Ȃ��Ƃ��P���g�p���Ȃ���΂Ȃ�Ȃ�)
	//         : [D3DCLEAR_TARGET - �����_�����O�^�[�Q�b�g���N���A����Color�p�����[�^�̒l�ɂ���]
	//         : [D3DCLEAR_ZBUFFER - �[�x(�y)�o�b�t�@���N���A����Z�p�����[�^�̒l�ɂ���]
	//         : [D3DCLEAR_STENCIL - �X�e���V���o�b�t�@���N���A����Stencil�p�����[�^�̒l�ɂ���]
	// Color   : �T�[�t�F�X���N���A����F
	// Z       : �f�v�X�o�b�t�@�ɕۑ�����l
	// Stencil : �X�e���V���o�b�t�@�ɕۑ�����l(����)

	// �w�i
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture2);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex2[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);


	if (Gri == false)
	{
		// �O���t�H���`��

		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture5);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex5[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

	}


	if (Kyara2 == false)
	{
		// �L�����`��2
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture3);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex3[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

	}

	if (Dora == false)
	{
		// �h���S���`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture6);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex6[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

	}


	//if (Kyara3 == false)
	//{
	//	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	//	// �e�N�X�`�����|���S���ɃZ�b�g
	//	g_pD3DDevice->SetTexture(0, g_pD3DTexture7);

	//	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	//	g_pD3DDevice->DrawPrimitiveUP(
	//		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
	//		2,                   // �|���S���̐�
	//		&vertex7[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
	//		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	//	);

	//}

	// ���L�����`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture1);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// hit�`��
	if (hitFlag == true)
	{

		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture14);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex14[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

	}

	// �J�[�\���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture8);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex8[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	// pSourceRect         : �]������`
	// pDestRect           : �]�����`
	// hDestWindowOverride : �]����E�C���h�E�ւ̃|�C���^
	// pDirtyRegion        : �ʏ��NULL��
}

void Update()
{
	// �����_���ŃL����2����������
	srand((unsigned)time(NULL));
	randam = rand() % 12 + 1;

	//�\�����W�̍X�V
	// �J�[�\��
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f; 

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;

	// hit
	if (hitFlag == true)
	{
		// hit
		vertex14[0].x = cl.x - CURSOR_X;
		vertex14[0].y = cl.y - CURSOR_Y - HIT_X;
		vertex14[0].z = 0.0f;

		vertex14[1].x = cl.x + CURSOR_X;
		vertex14[1].y = cl.y - CURSOR_Y - HIT_Y;
		vertex14[1].z = 0.0f;

		vertex14[2].x = cl.x - CURSOR_X;
		vertex14[2].y = cl.y + CURSOR_Y - HIT_X;
		vertex14[2].z = 0.0f;

		vertex14[3].x = cl.x + CURSOR_X;
		vertex14[3].y = cl.y + CURSOR_Y - HIT_Y;
		vertex14[3].z = 0.0f;
		
		//// hit
		//vertex14[0].x = cl.x - CURSOR_X;
		//vertex14[0].y = cl.y - CURSOR_Y;
		//vertex14[0].z = 0.0f;

		//vertex14[1].x = cl.x + CURSOR_X;
		//vertex14[1].y = cl.y - CURSOR_Y;
		//vertex14[1].z = 0.0f;

		//vertex14[2].x = cl.x - CURSOR_X;
		//vertex14[2].y = cl.y + CURSOR_Y;
		//vertex14[2].z = 0.0f;

		//vertex14[3].x = cl.x + CURSOR_X;
		//vertex14[3].y = cl.y + CURSOR_Y;
		//vertex14[3].z = 0.0f;
		
		if (hitcnt <= HITTIME_MAX)
		{
			hitcnt++;
		}

		if (hitcnt > HITTIME_MIN)
		{
			hitcnt = 0;
			hitFlag = false;
		}
		else
		{
			// RHW�̒l
			vertex14[0].rhw = 1.0f;
			vertex14[1].rhw = 1.0f;
			vertex14[2].rhw = 1.0f;
			vertex14[3].rhw = 1.0f;

			// �f�B�t���[�Y�F�̐ݒ�
			vertex14[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
			vertex14[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
			vertex14[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
			vertex14[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

			// �e�N�X�`�����W
			vertex14[0].u = 0.0f;
			vertex14[0].v = 0.0f;
			vertex14[1].u = 1.0f;
			vertex14[1].v = 0.0f;
			vertex14[2].u = 0.0f;
			vertex14[2].v = 1.0f;
			vertex14[3].u = 1.0f;
			vertex14[3].v = 1.0f;
		}
	}
	else
	{
		// hit(�����l�͉�ʊO�ɂ���)
		vertex14[0].x = 1500.0f;
		vertex14[0].y = 1500.0f;
		vertex14[0].z = 0.0f;

		vertex14[1].x = 1500.0f;
		vertex14[1].y = 1500.0f;
		vertex14[1].z = 0.0f;

		vertex14[2].x = 1500.0f;
		vertex14[2].y = 1500.0f;
		vertex14[2].z = 0.0f;

		vertex14[3].x = 1500.0f;
		vertex14[3].y = 1500.0f;
		vertex14[3].z = 0.0f;

		// RHW�̒l
		vertex14[0].rhw = 1.0f;
		vertex14[1].rhw = 1.0f;
		vertex14[2].rhw = 1.0f;
		vertex14[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex14[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex14[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex14[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex14[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// �e�N�X�`�����W
		vertex14[0].u = 0.0f;
		vertex14[0].v = 0.0f;
		vertex14[1].u = 1.0f;
		vertex14[1].v = 0.0f;
		vertex14[2].u = 0.0f;
		vertex14[2].v = 1.0f;
		vertex14[3].u = 1.0f;
		vertex14[3].v = 1.0f;
	}

	// �L����1
	vertex[0].x = g_playerPosition.x;
	vertex[0].y = g_playerPosition.y;
	vertex[0].z = g_playerPosition.z;

	vertex[1].x = g_playerPosition.x + 70.0f;
	vertex[1].y = g_playerPosition.y;  
	vertex[1].z = g_playerPosition.z;  
									   
	vertex[2].x = g_playerPosition.x;  
	vertex[2].y = g_playerPosition.y + 70.0f;
	vertex[2].z = g_playerPosition.z; 
									  
	vertex[3].x = g_playerPosition.x + 70.0f;
	vertex[3].y = g_playerPosition.y + 70.0f;
	vertex[3].z = g_playerPosition.z;
	

	//�ړ�����
	// �����L�[(�L����1)
	// ��
	if (GetKeyboardPress(DIK_LEFT))
	{
		g_playerPosition.x -= KYARA_SPEED_MAX;
		g_anmDir = ANM_LEFT;
	}

	// �E
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_playerPosition.x += KYARA_SPEED_MAX;
		g_anmDir = ANM_RIGHT;
	}
	
	// ��
	if (GetKeyboardPress(DIK_UP))
	{
		g_playerPosition.y -= KYARA_SPEED_MAX;
		g_anmDir = ANM_UP;
	}

	// ��
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_playerPosition.y += KYARA_SPEED_MAX;
		g_anmDir = ANM_DOWN;
	}

	// A
	if (GetAsyncKeyState('A'))
	{
		g_playerPosition.x -= KYARA_SPEED_MAX;
		g_anmDir = ANM_LEFT;
	}

	// D
	if (GetAsyncKeyState('D'))
	{
		g_playerPosition.x += KYARA_SPEED_MAX;
		g_anmDir = ANM_RIGHT;
	}

	// W
	if (GetAsyncKeyState('W'))
	{
		g_playerPosition.y -= KYARA_SPEED_MAX;
		g_anmDir = ANM_UP;
	}

	// S
	if (GetAsyncKeyState('S'))
	{
		g_playerPosition.y += KYARA_SPEED_MAX;
		g_anmDir = ANM_DOWN;
	}


	// �L����2
	if (Kyara2 == false)
	{
		// �L����2
		vertex3[0].x = g_enemyPosition.x;
		vertex3[0].y = g_enemyPosition.y;
		vertex3[0].z = g_enemyPosition.z;

		vertex3[1].x = g_enemyPosition.x + 64.0f;
		vertex3[1].y = g_enemyPosition.y;
		vertex3[1].z = g_enemyPosition.z;

		vertex3[2].x = g_enemyPosition.x;
		vertex3[2].y = g_enemyPosition.y + 64.0f;
		vertex3[2].z = g_enemyPosition.z;

		vertex3[3].x = g_enemyPosition.x + 64.0f;
		vertex3[3].y = g_enemyPosition.y + 64.0f;
		vertex3[3].z = g_enemyPosition.z;

		if (enemylife == 1)
		{
			// �����_���ړ�
			if (randam == 7)             // ��
			{
				g_enemyPosition.x -= KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_LEFT;
			}
			else if (randam == 5 || randam == 11)        // �E
			{
				g_enemyPosition.x += KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_RIGHT;
			}
			else if (randam == 3)        // ��
			{
				g_enemyPosition.y -= KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_UP;
			}
			else if (randam == 1 || randam == 9)         // ��
			{
				g_enemyPosition.y += KYARA3_SPEED_MAX * 1.2f;
				g_anmDir2 = ANM_DOWN;
			}
			else
			{
				g_enemyPosition.x = g_enemyPosition.x;
				g_enemyPosition.y = g_enemyPosition.y;
			}
		}
		else if (enemylife == 2)
		{
			// �����_���ړ�
			if (randam == 7)             // ��
			{
				g_enemyPosition.x -= KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_LEFT;
			}
			else if (randam == 5 || randam == 11)        // �E
			{
				g_enemyPosition.x += KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_RIGHT;
			}
			else if (randam == 3)        // ��
			{
				g_enemyPosition.y -= KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_UP;
			}
			else if (randam == 1 || randam == 9)         // ��
			{
				g_enemyPosition.y += KYARA4_SPEED_MAX * 1.5f;
				g_anmDir2 = ANM_DOWN;
			}
			else
			{
				g_enemyPosition.x = g_enemyPosition.x;
				g_enemyPosition.y = g_enemyPosition.y;
			}
		}
		else
		{
			// �����_���ړ�
			if (randam == 7)             // ��
			{
				g_enemyPosition.x -= KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_LEFT;
			}
			else if (randam == 5 || randam == 11)        // �E
			{
				g_enemyPosition.x += KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_RIGHT;
			}
			else if (randam == 3)        // ��
			{
				g_enemyPosition.y -= KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_UP;
			}
			else if (randam == 1 || randam == 9)         // ��
			{
				g_enemyPosition.y += KYARA2_SPEED_MAX;
				g_anmDir2 = ANM_DOWN;
			}
			else
			{
				g_enemyPosition.x = g_enemyPosition.x;
				g_enemyPosition.y = g_enemyPosition.y;
			}
		}
	
	}
	
	// �O���t�H��
	if (Gri == false)
	{
		// �O���t�H���@
		vertex5[0].x = g_griPosition.x;
		vertex5[0].y = g_griPosition.y;
		vertex5[0].z = g_griPosition.z;

		vertex5[1].x = g_griPosition.x + 90.0f;
		vertex5[1].y = g_griPosition.y;
		vertex5[1].z = g_griPosition.z;

		vertex5[2].x = g_griPosition.x;
		vertex5[2].y = g_griPosition.y + 90.0f;
		vertex5[2].z = g_griPosition.z;

		vertex5[3].x = g_griPosition.x + 90.0f;
		vertex5[3].y = g_griPosition.y + 90.0f;
		vertex5[3].z = g_griPosition.z;

		if (enemylife == 1)
		{
			// �����_���ŃO���t�H������������
			if (randam == 3 || randam == 7 || randam == 12)             // ��
			{
				g_griPosition.x -= GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_LEFT;
			}
			else if (randam == 1 || randam == 8)        // �E
			{
				g_griPosition.x += GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_RIGHT;
			}
			else if (randam == 4 || randam == 6)        // ��
			{
				g_griPosition.y -= GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_UP;
			}
			else if (randam == 2 || randam == 10)           // ��
			{
				g_griPosition.y += GRI_SPEED_MAX + 2.0f;
				g_anmDir3 = ANM_DOWN;
			}
			else                          // ��~
			{
				g_griPosition.x = g_griPosition.x;
				g_griPosition.y = g_griPosition.y;
			}
		}
		else if (enemylife == 2)
		{
			// �����_���ŃO���t�H������������
			if (randam == 3 || randam == 7 || randam == 12)             // ��
			{
				g_griPosition.x -= GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_LEFT;
			}
			else if (randam == 1 || randam == 8)        // �E
			{
				g_griPosition.x += GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_RIGHT;
			}
			else if (randam == 4 || randam == 6)        // ��
			{
				g_griPosition.y -= GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_UP;
			}
			else if (randam == 2 || randam == 10)           // ��
			{
				g_griPosition.y += GRI_SPEED_MAX * 3.0f;
				g_anmDir3 = ANM_DOWN;
			}
			else                          // ��~
			{
				g_griPosition.x = g_griPosition.x;
				g_griPosition.y = g_griPosition.y;
			}	
		}
		else
		{
			// �����_���ŃO���t�H������������
			if (randam == 3 || randam == 7 || randam == 12)             // ��
			{
				g_griPosition.x -= GRI_SPEED_MAX;
				g_anmDir3 = ANM_LEFT;
			}
			else if (randam == 1 || randam == 8)        // �E
			{
				g_griPosition.x += GRI_SPEED_MAX;
				g_anmDir3 = ANM_RIGHT;
			}
			else if (randam == 4 || randam == 6)        // ��
			{
				g_griPosition.y -= GRI_SPEED_MAX;
				g_anmDir3 = ANM_UP;
			}
			else if (randam == 2 || randam == 10)           // ��
			{
				g_griPosition.y += GRI_SPEED_MAX;
				g_anmDir3 = ANM_DOWN;
			}
			else                          // ��~
			{
				g_griPosition.x = g_griPosition.x;
				g_griPosition.y = g_griPosition.y;
			}
		}
	}
	
	// �h���S��
	if (Dora == false)
	{
		// �h���S��
		vertex6[0].x = g_draPosition.x;
		vertex6[0].y = g_draPosition.y;
		vertex6[0].z = g_draPosition.z;

		vertex6[1].x = g_draPosition.x + 95.0f;
		vertex6[1].y = g_draPosition.y;
		vertex6[1].z = g_draPosition.z;

		vertex6[2].x = g_draPosition.x;
		vertex6[2].y = g_draPosition.y + 95.0f;
		vertex6[2].z = g_draPosition.z;

		vertex6[3].x = g_draPosition.x + 95.0f;
		vertex6[3].y = g_draPosition.y + 95.0f;
		vertex6[3].z = g_draPosition.z;

		if (enemylife == 1)
		{
			// �����_���Ńh���S������������
			if (randam == 1 || randam == 6)              // ��
			{
				g_draPosition.x -= DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_LEFT;
			}
			else if (randam == 8 || randam == 7)         // �E
			{
				g_draPosition.x += DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_RIGHT;
			}
			else if (randam == 5 || randam == 4)         // ��
			{
				g_draPosition.y -= DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 3 || randam == 2)         // ��
			{
				g_draPosition.y += DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_DOWN;
			}
			else if (randam == 10)                       // �΂ߏ�
			{
				g_draPosition.x += DORA_SPEED_MAX + 1.5f;
				g_draPosition.y += DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 11)                       // �΂߉�
			{
				g_draPosition.x -= DORA_SPEED_MAX + 1.5f;
				g_draPosition.y -= DORA_SPEED_MAX + 1.5f;
				g_anmDir4 = ANM_DOWN;
			}
			else
			{
				g_draPosition.x = g_draPosition.x;
				g_draPosition.y = g_draPosition.y;
			}
		}
		else if (enemylife == 2)
		{
			// �����_���Ńh���S������������
			if (randam == 1 || randam == 6)              // ��
			{
				g_draPosition.x -= DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_LEFT;
			}
			else if (randam == 8 || randam == 7)         // �Ef
			{
				g_draPosition.x += DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_RIGHT;
			}
			else if (randam == 5 || randam == 4)         // ��
			{
				g_draPosition.y -= DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 3 || randam == 2)         // ��
			{
				g_draPosition.y += DORA_SPEED_MAX * 3.0f;
				g_anmDir4 = ANM_DOWN;
			}
			else if (randam == 10)                       // �΂ߏ�
			{
				g_draPosition.x += DORA_SPEED_MAX * 2.0f;
				g_draPosition.y += DORA_SPEED_MAX * 2.0f;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 11)                       // �΂߉�
			{
				g_draPosition.x -= DORA_SPEED_MAX * 2.0f;
				g_draPosition.y -= DORA_SPEED_MAX * 2.0f;
				g_anmDir4 = ANM_DOWN;
			}
			else
			{
				g_draPosition.x = g_draPosition.x;
				g_draPosition.y = g_draPosition.y;
			}
		}
		else
		{
			// �����_���Ńh���S������������
			if (randam == 1 || randam == 6)              // ��
			{
				g_draPosition.x -= DORA_SPEED_MAX;
				g_anmDir4 = ANM_LEFT;
			}
			else if (randam == 8 || randam == 7)         // �E
			{
				g_draPosition.x += DORA_SPEED_MAX;
				g_anmDir4 = ANM_RIGHT;
			}
			else if (randam == 5 || randam == 4)         // ��
			{
				g_draPosition.y -= DORA_SPEED_MAX;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 3 || randam == 2)         // ��
			{
				g_draPosition.y += DORA_SPEED_MAX;
				g_anmDir4 = ANM_DOWN;
			}
			else if (randam == 10)                       // �΂ߏ�
			{
				g_draPosition.x += DORA_SPEED_MAX;
				g_draPosition.y += DORA_SPEED_MAX;
				g_anmDir4 = ANM_UP;
			}
			else if (randam == 11)                       // �΂߉�
			{
				g_draPosition.x -= DORA_SPEED_MAX;
				g_draPosition.y -= DORA_SPEED_MAX;
				g_anmDir4 = ANM_DOWN;
			}
			else
			{
				g_draPosition.x = g_draPosition.x;
				g_draPosition.y = g_draPosition.y;
			}
		}
	}
	
	// �A�j���[�V�����J�E���g�̍X�V
	++g_anmCnt;
	if (g_anmCnt % g_anmSpeed == 0)
	{
		++g_anmNum;
		if (g_anmNum >= ANM_MAX)
		{
			g_anmNum = 0;
		}

		// �L����1
		vertex[0].u = g_anmTbl[g_anmNum]; // ����X�s�N�Z��[0]
		vertex[1].u = g_anmTbl[g_anmNum] + 32.0f / 96.0f; // [1]
		vertex[2].u = g_anmTbl[g_anmNum]; // [2]
		vertex[3].u = g_anmTbl[g_anmNum] + 32.0f / 96.0f; // [3]

		// �L����2
		vertex3[0].u = g_anmTbl2[g_anmNum]; // ����X�s�N�Z��[0]
		vertex3[1].u = g_anmTbl2[g_anmNum] + 32.0f / 96.0f; // [1]
		vertex3[2].u = g_anmTbl2[g_anmNum]; // [2]
		vertex3[3].u = g_anmTbl2[g_anmNum] + 32.0f / 96.0f; // [3]

		// �O���t�H��
		vertex5[0].u = g_anmTbl3[g_anmNum];//����135�s�N�Z��
		vertex5[1].u = g_anmTbl3[g_anmNum] + 45.0f / 135.0f;
		vertex5[2].u = g_anmTbl3[g_anmNum];
		vertex5[3].u = g_anmTbl3[g_anmNum] + 45.0f / 135.0f;

		// �h���S��
		vertex6[0].u = g_anmTbl4[g_anmNum]; // ����X�s�N�Z��[0]
		vertex6[1].u = g_anmTbl4[g_anmNum] + 32.0f / 96.0f; // [1]
		vertex6[2].u = g_anmTbl4[g_anmNum]; // [2]
		vertex6[3].u = g_anmTbl4[g_anmNum] + 32.0f / 96.0f; // [3]

		//// �L����3
		//vertex7[0].u = g_anmTbl5[g_anmNum]; // ����X�s�N�Z��[0]
		//vertex7[1].u = g_anmTbl5[g_anmNum] + 48.6f / 146.0f; // [1]
		//vertex7[2].u = g_anmTbl5[g_anmNum]; // [2]
		//vertex7[3].u = g_anmTbl5[g_anmNum] + 48.6f / 146.0f; // [3]

	}

	// �L����1
	vertex[0].v = g_anmDir * 32.0f / 128.0f;
	vertex[1].v = vertex[0].v;
	vertex[2].v = ((g_anmDir + 1) * 32.0f) / 128.0f;
	vertex[3].v = vertex[2].v;

	// �L����2
	vertex3[0].v = g_anmDir2 * 32.0f / 128.0f;
	vertex3[1].v = vertex3[0].v;
	vertex3[2].v = ((g_anmDir2 + 1) * 32.0f) / 128.0f;
	vertex3[3].v = vertex3[2].v;
	
	// �O���t�H��
	vertex5[0].v = g_anmDir3 * 50.0f / 200.0f;
	vertex5[1].v = vertex5[0].v;
	vertex5[2].v = ((g_anmDir3 + 1) * 50.0f) / 200.0f;
	vertex5[3].v = vertex5[2].v;

	// �h���S��
	vertex6[0].v = g_anmDir4 * 32.0f / 128.0f;
	vertex6[1].v = vertex6[0].v;
	vertex6[2].v = ((g_anmDir4 + 1) * 32.0f) / 128.0f;
	vertex6[3].v = vertex6[2].v;

	// �����蔻�菈��
	Hit();
}

//=============================================================================
// �Q�[����ʏ����̓����蔻�菈��
//=============================================================================
void Hit()
{
	// �ǂƃL����1�Ƃ̓����蔻��
	if (g_playerPosition.x < 0)
	{
		g_playerPosition.x = 0;
	}
	if (g_playerPosition.x >= 1135)
	{
		g_playerPosition.x = 1135;
	}
	if (g_playerPosition.y < 0)
	{
		g_playerPosition.y = 0;
	}
	if (g_playerPosition.y >= 535)
	{
		g_playerPosition.y = 535;
	}

	// �ǂƃL����2�Ƃ̓����蔻��
	if (g_enemyPosition.x < 0)
	{
		g_enemyPosition.x = 0;
	}
	if (g_enemyPosition.x >= 1136)
	{
		g_enemyPosition.x = 1136;
	}
	if (g_enemyPosition.y < 0)
	{
		g_enemyPosition.y = 0;
	}
	if (g_enemyPosition.y >= 536)
	{
		g_enemyPosition.y = 536;
	}

	// �ǂƃO���t�H���Ƃ̓����蔻��
	if (g_griPosition.x <0)
	{	  
		g_griPosition.x = 0;
	}	  
	if (g_griPosition.x >= 1110)
	{	  
		g_griPosition.x = 1110;
	}	  
	if (g_griPosition.y < 0)
	{	  
		g_griPosition.y = 0;
	}	  
	if (g_griPosition.y >= 510)
	{	  
		g_griPosition.y = 510;
	}

	// �ǂƃh���S���Ƃ̓����蔻��
	if (g_draPosition.x < 0)
	{
		g_draPosition.x = 0;
	}
	if (g_draPosition.x >= 1105)
	{
		g_draPosition.x = 1105;
	}
	if (g_draPosition.y < 0)
	{
		g_draPosition.y = 0;
	}
	if (g_draPosition.y >= 505)
	{
		g_draPosition.y = 505;
	}

	// ���C�t
	if (life > 0)
	{
		if (!Kyara2)
		{
			// �L����1�ƃL����2�̓����蔻��
			if (g_playerPosition.x + 70.0f >= g_enemyPosition.x && g_playerPosition.x <= g_enemyPosition.x + 64.0f)
			{
				if (g_playerPosition.y + 70.0f >= g_enemyPosition.y && g_playerPosition.y <= g_enemyPosition.y + 64.0f)
				{
					PlaySound(SOUND_LABEL_SE002);// player��ememy�̓����艹SE
					Kyara2 = true;
					life -= 1;
				}
			}
		}

		// �L����1�ƃh���S���̓����蔻��
		if (!Dora) {
			if (g_playerPosition.x + 70.0f >= g_draPosition.x && g_playerPosition.x <= g_draPosition.x + 80.0f)
			{
				if (g_playerPosition.y + 70.0f >= g_draPosition.y && g_playerPosition.y <= g_draPosition.y + 80.0f)
				{
					PlaySound(SOUND_LABEL_SE002);// player��ememy�̓����艹SE
					Dora = true;
					life -= 1;
				}
			}
		}

		if (!Gri)
		{
			// �L����1�ƃO���t�H���`��̓����蔻��
			if (g_playerPosition.x + 70.0f >= g_griPosition.x && g_playerPosition.x <= g_griPosition.x + 90.0f)
			{
				if (g_playerPosition.y + 70.0f >= g_griPosition.y && g_playerPosition.y <= g_griPosition.y + 90.0f)
				{
					PlaySound(SOUND_LABEL_SE002);// player��ememy�̓����艹SE
					Gri = true;
					life -= 1;
				}
			}
		}
	}
	else if(life <= 0)
	{
		SceneFlag = 2;
	}

	// �J�[�\���ƓG�Ƃ̓����蔻��
	if (enemylife < 3)
	{
		if (GetMouseLeftTrigger())
		{
			PlaySound(SOUND_LABEL_SE000); // �V���b�g��

			if (!Kyara2)
			{
				// �J�[�\���ƃL����2�̓����蔻��
				if (cl.x >= g_enemyPosition.x && cl.x <= g_enemyPosition.x + 64.0f)
				{
					if (cl.y + 15.0f >= g_enemyPosition.y && cl.y <= g_enemyPosition.y + 64.0f)
					{
						
						// kyara2�̗̑� 
						if (kyara2life < KYARA2_LIFE)
						{
							hitFlag = true;
							kyara2life += 1;
						}
						else if(kyara2life >= KYARA2_LIFE)
						{
							PlaySound(SOUND_LABEL_SE001); // �j��
							Kyara2 = true;
							enemylife += 1;
						}
					}
				}
			}

			if (!Dora) {
				// �J�[�\���ƃh���S���̓����蔻��
				if (cl.x + 15.0f >= g_draPosition.x && cl.x <= g_draPosition.x + 80.0f)
				{
					if (cl.y + 15.0f >= g_draPosition.y && cl.y <= g_draPosition.y + 80.0f)
					{
						// �h���S���̗̑� 
						if (doralife < DORA_LIFE)
						{
							hitFlag = true;
							doralife += 1;
						}
						else if (doralife >= DORA_LIFE)
						{
							PlaySound(SOUND_LABEL_SE001); // �j��
							Dora = true;
							enemylife += 1;
						}
					}
				}
			}

			if (!Gri) {
				// �J�[�\���ƃO���t�H���`��̓����蔻��
				if (cl.x + 15.0f >= g_griPosition.x && cl.x <= g_griPosition.x + 90.0f)
				{
					if (cl.y + 15.0f >= g_griPosition.y && cl.y <= g_griPosition.y + 90.0f)
					{
						// �O���t�H���̗̑� 
						if (grilife < GRI_LIFE)
						{
							hitFlag = true;
							grilife += 1;
						}
						else if (grilife >= GRI_LIFE)
						{
							PlaySound(SOUND_LABEL_SE001); // �j��
							Gri = true;
							enemylife += 1;
						}
						
					}
				}
			}
		}
		
	}
	else if(enemylife >= 3)
	{
		SceneFlag = 3;
	}
}

//=============================================================================
// �^�C�g������
//=============================================================================
void Main()
{
	// �����t���O
    setumei = false;

	// �����l(�|�W�V����)
	g_playerPosition.x = 550.0f;
	g_playerPosition.y = 300.0f;
	g_enemyPosition.x = 250.0f;
	g_enemyPosition.y = 250.0f;
	g_enemy2Position.x = 200.0f;
	g_enemy2Position.y = 300.0f;
	g_draPosition.x = 100.0f;
	g_draPosition.y = 240.0f;
	g_griPosition.x = 1000.0f;
	g_griPosition.y = 450.0f;

	// �Q�[���{�^��
	g_gamePosition.x = 800.0f;
	g_gamePosition.y = 400.0f;

	// �t���O���Z�b�g
	Kyara2 = false;
	Dora = false;
	Gri = false;
	//Kyara3 = false;

	enemylife = 0;
	life = 1;
	kyara2life = 0;
	grilife = 0;
	doralife = 0;

	g_setumeiPosition.x = 150.0f;
	g_setumeiPosition.y = 440.0f;

	// �^�C�g��
	vertex4[0].x = 0.0f;
	vertex4[0].y = 0.0f;
	vertex4[0].z = 0.0f;

	vertex4[1].x = SCREEN_WIDTH;
	vertex4[1].y = 0.0f;
	vertex4[1].z = 0.0f;

	vertex4[2].x = 0.0f;
	vertex4[2].y = SCREEN_HEIGHT;
	vertex4[2].z = 0.0f;

	vertex4[3].x = SCREEN_WIDTH;
	vertex4[3].y = SCREEN_HEIGHT;
	vertex4[3].z = 0.0f;

	// RHW�̒l
	vertex4[0].rhw = 1.0f;
	vertex4[1].rhw = 1.0f;
	vertex4[2].rhw = 1.0f;
	vertex4[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex4[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex4[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex4[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex4[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex4[0].u = 0.0f;
	vertex4[0].v = 0.0f;
	vertex4[1].u = 1.0f;
	vertex4[1].v = 0.0f;
	vertex4[2].u = 0.0f;
	vertex4[2].v = 1.0f;
	vertex4[3].u = 1.0f;
	vertex4[3].v = 1.0f; 

	// �����{�^��
	vertex16[0].x = g_setumeiPosition.x;
	vertex16[0].y = g_setumeiPosition.y;
	vertex16[0].z = 0.0f;
		  
	vertex16[1].x = g_setumeiPosition.x + 150.0f;
	vertex16[1].y = g_setumeiPosition.y;
	vertex16[1].z = 0.0f;
		  
	vertex16[2].x = g_setumeiPosition.x;
	vertex16[2].y = g_setumeiPosition.y + 100.0f;
	vertex16[2].z = 0.0f;
		  
	vertex16[3].x = g_setumeiPosition.x + 150.0f;
	vertex16[3].y = g_setumeiPosition.y + 100.0f; 
	vertex16[3].z = 0.0f;

	// RHW�̒l
	vertex16[0].rhw = 1.0f;
	vertex16[1].rhw = 1.0f;
	vertex16[2].rhw = 1.0f;
	vertex16[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex16[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex16[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex16[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex16[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �����{�^���̐F�Ɗg��
	if (cl.x >= g_setumeiPosition.x && cl.x <= g_setumeiPosition.x + 150.0f)
	{
		if (cl.y >= g_setumeiPosition.y && cl.y <= g_setumeiPosition.y + 100.0f)
		{
			vertex16[0].x = g_setumeiPosition.x - BIGSIZE_X;
			vertex16[0].y = g_setumeiPosition.y - BIGSIZE_Y;
			vertex16[0].z = 0.0f;

			vertex16[1].x = g_setumeiPosition.x + 150.0f + BIGSIZE_X;
			vertex16[1].y = g_setumeiPosition.y - BIGSIZE_Y;
			vertex16[1].z = 0.0f;

			vertex16[2].x = g_setumeiPosition.x - BIGSIZE_X;
			vertex16[2].y = g_setumeiPosition.y + 100.0f + BIGSIZE_Y;
			vertex16[2].z = 0.0f;

			vertex16[3].x = g_setumeiPosition.x + 150.0f + BIGSIZE_X;
			vertex16[3].y = g_setumeiPosition.y + 100.0f + BIGSIZE_Y;
			vertex16[3].z = 0.0f;

			vertex16[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex16[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex16[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex16[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex16[0].u = 0.0f;
	vertex16[0].v = 0.0f;
	vertex16[1].u = 1.0f;
	vertex16[1].v = 0.0f;
	vertex16[2].u = 0.0f;
	vertex16[2].v = 1.0f;
	vertex16[3].u = 1.0f;
	vertex16[3].v = 1.0f;
	
	// �Q�[���{�^��
	vertex19[0].x = g_gamePosition.x;
	vertex19[0].y = g_gamePosition.y;
	vertex19[0].z = 0.0f;
		   
	vertex19[1].x = g_gamePosition.x + 300.0f;
	vertex19[1].y = g_gamePosition.y;
	vertex19[1].z = 0.0f;
		   
	vertex19[2].x = g_gamePosition.x;
	vertex19[2].y = g_gamePosition.y + 130.0f;
	vertex19[2].z = 0.0f;
		   
	vertex19[3].x = g_gamePosition.x + 300.0f;
	vertex19[3].y = g_gamePosition.y + 130.0f; 
	vertex19[3].z = 0.0f;

	// RHW�̒l
	vertex19[0].rhw = 1.0f;
	vertex19[1].rhw = 1.0f;
	vertex19[2].rhw = 1.0f;
	vertex19[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex19[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex19[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex19[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex19[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �Q�[���{�^���̐F�Ɗg��
	if (cl.x >= g_gamePosition.x && cl.x <= g_gamePosition.x + 300.0f)
	{
		if (cl.y >= g_gamePosition.y && cl.y <= g_gamePosition.y + 130.0f)
		{
			vertex19[0].x = g_gamePosition.x - BIGSIZE_X;
			vertex19[0].y = g_gamePosition.y - BIGSIZE_Y;
			vertex19[0].z = 0.0f;

			vertex19[1].x = g_gamePosition.x + 300.0f + BIGSIZE_X;
			vertex19[1].y = g_gamePosition.y - BIGSIZE_Y;
			vertex19[1].z = 0.0f;

			vertex19[2].x = g_gamePosition.x - BIGSIZE_X;
			vertex19[2].y = g_gamePosition.y + 130.0f + BIGSIZE_Y;
			vertex19[2].z = 0.0f;

			vertex19[3].x = g_gamePosition.x + 300.0f + BIGSIZE_X;
			vertex19[3].y = g_gamePosition.y + 130.0f + BIGSIZE_Y;
			vertex19[3].z = 0.0f;

			vertex19[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex19[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex19[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex19[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex19[0].u = 0.0f;
	vertex19[0].v = 0.0f;
	vertex19[1].u = 1.0f;
	vertex19[1].v = 0.0f;
	vertex19[2].u = 0.0f;
	vertex19[2].v = 1.0f;
	vertex19[3].u = 1.0f;
	vertex19[3].v = 1.0f;


	// �J�[�\��
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;
}

void MainDraw()
{
	// �^�C�g�����
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture4);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex4[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// �����{�^���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture16);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex16[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
	
	// �Q�[���{�^���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture20);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex19[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
	
	// �J�[�\���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex8[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

void MainUpdate()
{
	
	if (GetMouseLeftTrigger())
	{
		// �����{�^��
		if (cl.x >= g_setumeiPosition.x && cl.x <= g_setumeiPosition.x + 150.0f)
		{
			if (cl.y >= g_setumeiPosition.y && cl.y <= g_setumeiPosition.y + 100.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // �N���b�N

				SceneFlag = 4;
			}
		}
		
		// �Q�[���{�^��
		if (cl.x >= g_gamePosition.x && cl.x <= g_gamePosition.x + 300.0f)
		{
			if (cl.y >= g_gamePosition.y && cl.y <= g_gamePosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // �N���b�N

				SceneFlag = 1;
			}
		}
	}


}

//=============================================================================
// �Q�[���I�[�o�[����
//==================================================================\==========
void Result()
{
	// �����l(�|�W�V����)
	g_playerPosition.x = 550.0f;
	g_playerPosition.y = 300.0f;
	g_enemyPosition.x = 250.0f;
	g_enemyPosition.y = 250.0f;
	g_enemy2Position.x = 200.0f;
	g_enemy2Position.y = 300.0f;
	g_draPosition.x = 100.0f;
	g_draPosition.y = 240.0f;
	g_griPosition.x = 1000.0f;
	g_griPosition.y = 450.0f;

	// �^�C�g���ɖ߂�{�^��
	g_endPosition.x = 250.0f;
	g_endPosition.y = 420.0f;

	// ���g���C�{�^��
	g_retryPosition.x = 650.0f;
	g_retryPosition.y = 420.0f;


	// �t���O���Z�b�g
	Kyara2 = false;
	Dora = false;
	Gri = false;
	//Kyara3 = false;

	enemylife = 0;
	life = 1;
	kyara2life = 0;
	grilife = 0;
	doralife = 0;

	// ���g���C
	vertex9[0].x = 0.0f;
	vertex9[0].y = 0.0f;
	vertex9[0].z = 0.0f;
		  
	vertex9[1].x = SCREEN_WIDTH;
	vertex9[1].y = 0.0f;
	vertex9[1].z = 0.0f;
		  
	vertex9[2].x = 0.0f;
	vertex9[2].y = SCREEN_HEIGHT;
	vertex9[2].z = 0.0f;
		  
	vertex9[3].x = SCREEN_WIDTH;
	vertex9[3].y = SCREEN_HEIGHT;
	vertex9[3].z = 0.0f;

	// RHW�̒l
	vertex9[0].rhw = 1.0f;
	vertex9[1].rhw = 1.0f;
	vertex9[2].rhw = 1.0f;
	vertex9[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex9[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex9[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex9[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex9[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex9[0].u = 0.0f;
	vertex9[0].v = 0.0f;
	vertex9[1].u = 1.0f;
	vertex9[1].v = 0.0f;
	vertex9[2].u = 0.0f;
	vertex9[2].v = 1.0f;
	vertex9[3].u = 1.0f;
	vertex9[3].v = 1.0f;

	// �^�C�g���ɖ߂�{�^��
	vertex20[0].x = g_endPosition.x;
	vertex20[0].y = g_endPosition.y;
	vertex20[0].z = 0.0f;
		  
	vertex20[1].x = g_endPosition.x + 300.0f;
	vertex20[1].y = g_endPosition.y;
	vertex20[1].z = 0.0f;
		  
	vertex20[2].x = g_endPosition.x;
	vertex20[2].y = g_endPosition.y + 130.0f;
	vertex20[2].z = 0.0f;
		  
	vertex20[3].x = g_endPosition.x + 300.0f;
	vertex20[3].y = g_endPosition.y + 130.0f;
	vertex20[3].z = 0.0f;

	// RHW�̒l
	vertex20[0].rhw = 1.0f;
	vertex20[1].rhw = 1.0f;
	vertex20[2].rhw = 1.0f;
	vertex20[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex20[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �^�C�g���ɖ߂�{�^���̐F�ς��Ɗg��
	if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
	{
		if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
		{
			// �^�C�g���ɖ߂�{�^��
			vertex20[0].x = g_endPosition.x - BIGSIZE_X;
			vertex20[0].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[0].z = 0.0f;

			vertex20[1].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[1].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[1].z = 0.0f;

			vertex20[2].x = g_endPosition.x - BIGSIZE_X;
			vertex20[2].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[2].z = 0.0f;

			vertex20[3].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[3].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[3].z = 0.0f;

			vertex20[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex20[0].u = 0.0f;
	vertex20[0].v = 0.0f;
	vertex20[1].u = 1.0f;
	vertex20[1].v = 0.0f;
	vertex20[2].u = 0.0f;
	vertex20[2].v = 1.0f;
	vertex20[3].u = 1.0f;
	vertex20[3].v = 1.0f;

	// ���g���C�{�^��
	vertex21[0].x = g_retryPosition.x;
	vertex21[0].y = g_retryPosition.y;
	vertex21[0].z = 0.0f;
		   
	vertex21[1].x = g_retryPosition.x + 300.0f;
	vertex21[1].y = g_retryPosition.y;
	vertex21[1].z = 0.0f;
		   
	vertex21[2].x = g_retryPosition.x;
	vertex21[2].y = g_retryPosition.y + 130.0f;
	vertex21[2].z = 0.0f;
		   
	vertex21[3].x = g_retryPosition.x + 300.0f;
	vertex21[3].y = g_retryPosition.y + 130.0f;
	vertex21[3].z = 0.0f;

	// RHW�̒l
	vertex21[0].rhw = 1.0f;
	vertex21[1].rhw = 1.0f;
	vertex21[2].rhw = 1.0f;
	vertex21[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex21[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex21[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex21[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex21[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// ���g���C�{�^���̐F�ς��Ɗg��
	if (cl.x >= g_retryPosition.x && cl.x <= g_retryPosition.x + 300.0f)
	{
		if (cl.y >= g_retryPosition.y && cl.y <= g_retryPosition.y + 130.0f)
		{
			// ���g���C�{�^��
			vertex21[0].x = g_retryPosition.x - BIGSIZE_X;
			vertex21[0].y = g_retryPosition.y - BIGSIZE_Y;
			vertex21[0].z = 0.0f;

			vertex21[1].x = g_retryPosition.x + 300.0f + BIGSIZE_X;
			vertex21[1].y = g_retryPosition.y - BIGSIZE_Y;
			vertex21[1].z = 0.0f;

			vertex21[2].x = g_retryPosition.x - BIGSIZE_X;
			vertex21[2].y = g_retryPosition.y + 130.0f + BIGSIZE_Y;
			vertex21[2].z = 0.0f;

			vertex21[3].x = g_retryPosition.x + 300.0f + BIGSIZE_X;
			vertex21[3].y = g_retryPosition.y + 130.0f + BIGSIZE_Y;
			vertex21[3].z = 0.0f;

			vertex21[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex21[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex21[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex21[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex21[0].u = 0.0f;
	vertex21[0].v = 0.0f;
	vertex21[1].u = 1.0f;
	vertex21[1].v = 0.0f;
	vertex21[2].u = 0.0f;
	vertex21[2].v = 1.0f;
	vertex21[3].u = 1.0f;
	vertex21[3].v = 1.0f;

	// �J�[�\��
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;

}

void ResultDraw()
{
	// �Q�[���I�[�o�[
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture9);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex9[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// �^�C�g���ɖ߂�`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture22);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex20[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// ���g���C�`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture23);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex21[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);


	// �J�[�\���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex8[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

}

void ResultUpdate()
{
	if (GetMouseLeftTrigger())
	{
		// �^�C�g���ɖ߂�{�^��
		if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
		{
			if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // �N���b�N

				SceneFlag = 0;
			}
		}

		// ���g���C�{�^��
		if (cl.x >= g_retryPosition.x && cl.x <= g_retryPosition.x + 300.0f)
		{
			if (cl.y >= g_retryPosition.y && cl.y <= g_retryPosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // �N���b�N

				SceneFlag = 1;
			}
		}
	}
}

//=============================================================================
// �Q�[���N���A����
//=============================================================================
void Clear()
{

	// �^�C�g���ɖ߂�{�^��
	g_endPosition.x = 450.0f;
	g_endPosition.y = 390.0f;

	// �N���A
	vertex13[0].x = 0.0f;
	vertex13[0].y = 0.0f;
	vertex13[0].z = 0.0f;
		  
	vertex13[1].x = SCREEN_WIDTH;
	vertex13[1].y = 0.0f;
	vertex13[1].z = 0.0f;
		  
	vertex13[2].x = 0.0f;
	vertex13[2].y = SCREEN_HEIGHT;
	vertex13[2].z = 0.0f;
		  
	vertex13[3].x = SCREEN_WIDTH;
	vertex13[3].y = SCREEN_HEIGHT;
	vertex13[3].z = 0.0f;

	// RHW�̒l
	vertex13[0].rhw = 1.0f;
	vertex13[1].rhw = 1.0f;
	vertex13[2].rhw = 1.0f;
	vertex13[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex13[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex13[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex13[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex13[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex13[0].u = 0.0f;
	vertex13[0].v = 0.0f;
	vertex13[1].u = 1.0f;
	vertex13[1].v = 0.0f;
	vertex13[2].u = 0.0f;
	vertex13[2].v = 1.0f;
	vertex13[3].u = 1.0f;
	vertex13[3].v = 1.0f;

	// �^�C�g���ɖ߂�{�^��
	vertex20[0].x = g_endPosition.x;
	vertex20[0].y = g_endPosition.y;
	vertex20[0].z = 0.0f;

	vertex20[1].x = g_endPosition.x + 300.0f;
	vertex20[1].y = g_endPosition.y;
	vertex20[1].z = 0.0f;

	vertex20[2].x = g_endPosition.x;
	vertex20[2].y = g_endPosition.y + 130.0f;
	vertex20[2].z = 0.0f;

	vertex20[3].x = g_endPosition.x + 300.0f;
	vertex20[3].y = g_endPosition.y + 130.0f;
	vertex20[3].z = 0.0f;

	// RHW�̒l
	vertex20[0].rhw = 1.0f;
	vertex20[1].rhw = 1.0f;
	vertex20[2].rhw = 1.0f;
	vertex20[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex20[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex20[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �^�C�g���ɖ߂�{�^���̐F�ς��Ɗg��
	if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
	{
		if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
		{
			vertex20[0].x = g_endPosition.x - BIGSIZE_X;
			vertex20[0].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[0].z = 0.0f;

			vertex20[1].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[1].y = g_endPosition.y - BIGSIZE_Y;
			vertex20[1].z = 0.0f;

			vertex20[2].x = g_endPosition.x - BIGSIZE_X;
			vertex20[2].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[2].z = 0.0f;

			vertex20[3].x = g_endPosition.x + 300.0f + BIGSIZE_X;
			vertex20[3].y = g_endPosition.y + 130.0f + BIGSIZE_Y;
			vertex20[3].z = 0.0f;

			vertex20[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			vertex20[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
		}
	}

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex20[0].u = 0.0f;
	vertex20[0].v = 0.0f;
	vertex20[1].u = 1.0f;
	vertex20[1].v = 0.0f;
	vertex20[2].u = 0.0f;
	vertex20[2].v = 1.0f;
	vertex20[3].u = 1.0f;
	vertex20[3].v = 1.0f;

	// �J�[�\��
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;
}

void ClearDraw()
{
	// �^�C�g���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture13);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex13[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// �^�C�g���ɖ߂�`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture22);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex20[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);

	// �J�[�\���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex8[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

void ClearUpdate()
{
	if (GetMouseLeftTrigger())
	{
		// �^�C�g���ɖ߂�{�^��
		if (cl.x >= g_endPosition.x && cl.x <= g_endPosition.x + 300.0f)
		{
			if (cl.y >= g_endPosition.y && cl.y <= g_endPosition.y + 130.0f)
			{
				PlaySound(SOUND_LABEL_SE003);  // �N���b�N

				SceneFlag = 0;
			}
		}
	}
}

//=============================================================================
// �Q�[����������
//=============================================================================
void SetumeiDraw()
{
	// �����{�^��
	if (setumei == false)
	{
		// �����`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture15);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex15[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

		// ���փ{�^���`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture19);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex18[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);
	}
	else
	{
		// ����2�`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture21);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex15[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

		// �߂�{�^���`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture18);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex17[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);
	}

	// �J�[�\���`��
	g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`�����|���S���ɃZ�b�g
	g_pD3DDevice->SetTexture(0, g_pD3DTexture17);

	// g_pD3DDevice->DrawPrimitiveUP���Ă�
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
		2,                   // �|���S���̐�
		&vertex8[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
		sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
	);
}

void SetumeiUpdate()
{
	// �����l(�߂�{�^��)
	g_returnPosition.x = 1100.0f;
	g_returnPosition.y = 515.0f;

	// �����l(���փ{�^��)
	g_nextPosition.x = 1100.0f;
	g_nextPosition.y = 515.0f;

	// ����
	vertex15[0].x = 0.0f;
	vertex15[0].y = 0.0f;
	vertex15[0].z = 0.0f;
		   
	vertex15[1].x = SCREEN_WIDTH;
	vertex15[1].y = 0.0f;
	vertex15[1].z = 0.0f;
		   
	vertex15[2].x = 0.0f;
	vertex15[2].y = SCREEN_HEIGHT;
	vertex15[2].z = 0.0f;
		   
	vertex15[3].x = SCREEN_WIDTH;
	vertex15[3].y = SCREEN_HEIGHT;
	vertex15[3].z = 0.0f;

	// RHW�̒l
	vertex15[0].rhw = 1.0f;
	vertex15[1].rhw = 1.0f;
	vertex15[2].rhw = 1.0f;
	vertex15[3].rhw = 1.0f;

	// �f�B�t���[�Y�F�̐ݒ�
	vertex15[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex15[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex15[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
	vertex15[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex15[0].u = 0.0f;
	vertex15[0].v = 0.0f;
	vertex15[1].u = 1.0f;
	vertex15[1].v = 0.0f;
	vertex15[2].u = 0.0f;
	vertex15[2].v = 1.0f;
	vertex15[3].u = 1.0f;
	vertex15[3].v = 1.0f;


	if (setumei == false)
	{
		// ���փ{�^��
		vertex18[0].x = g_nextPosition.x;
		vertex18[0].y = g_nextPosition.y;
		vertex18[0].z = 0.0f;

		vertex18[1].x = g_nextPosition.x + 90.0f;
		vertex18[1].y = g_nextPosition.y;
		vertex18[1].z = 0.0f;

		vertex18[2].x = g_nextPosition.x;
		vertex18[2].y = g_nextPosition.y + 70.0f;
		vertex18[2].z = 0.0f;

		vertex18[3].x = g_nextPosition.x + 90.0f;
		vertex18[3].y = g_nextPosition.y + 70.0f;
		vertex18[3].z = 0.0f;

		// RHW�̒l
		vertex18[0].rhw = 1.0f;
		vertex18[1].rhw = 1.0f;
		vertex18[2].rhw = 1.0f;
		vertex18[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex18[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex18[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex18[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex18[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// ���փ{�^���̐F�Ɗg��
		if (cl.x >= g_nextPosition.x && cl.x <= g_nextPosition.x + 90.0f)
		{
			if (cl.y >= g_nextPosition.y && cl.y <= g_nextPosition.y + 70.0f)
			{
				vertex18[0].x = g_nextPosition.x - BIGSIZE2_X;
				vertex18[0].y = g_nextPosition.y - BIGSIZE2_Y;
				vertex18[0].z = 0.0f;

				vertex18[1].x = g_nextPosition.x + 90.0f + BIGSIZE2_X;
				vertex18[1].y = g_nextPosition.y - BIGSIZE2_Y;
				vertex18[1].z = 0.0f;

				vertex18[2].x = g_nextPosition.x - BIGSIZE2_X;
				vertex18[2].y = g_nextPosition.y + 70.0f + BIGSIZE2_Y;
				vertex18[2].z = 0.0f;

				vertex18[3].x = g_nextPosition.x + 90.0f + BIGSIZE2_X;
				vertex18[3].y = g_nextPosition.y + 70.0f + BIGSIZE2_Y;
				vertex18[3].z = 0.0f;

				vertex18[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex18[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex18[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex18[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			}
		}

		// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
		vertex18[0].u = 0.0f;
		vertex18[0].v = 0.0f;
		vertex18[1].u = 1.0f;
		vertex18[1].v = 0.0f;
		vertex18[2].u = 0.0f;
		vertex18[2].v = 1.0f;
		vertex18[3].u = 1.0f;
		vertex18[3].v = 1.0f;
	}
	else
	{
		// �߂�{�^��
		vertex17[0].x = g_returnPosition.x;
		vertex17[0].y = g_returnPosition.y;
		vertex17[0].z = 0.0f;

		vertex17[1].x = g_returnPosition.x + 90.0f;
		vertex17[1].y = g_returnPosition.y;
		vertex17[1].z = 0.0f;

		vertex17[2].x = g_returnPosition.x;
		vertex17[2].y = g_returnPosition.y + 70.0f;
		vertex17[2].z = 0.0f;

		vertex17[3].x = g_returnPosition.x + 90.0f;
		vertex17[3].y = g_returnPosition.y + 70.0f;
		vertex17[3].z = 0.0f;

		// RHW�̒l
		vertex17[0].rhw = 1.0f;
		vertex17[1].rhw = 1.0f;
		vertex17[2].rhw = 1.0f;
		vertex17[3].rhw = 1.0f;

		// �f�B�t���[�Y�F�̐ݒ�
		vertex17[0].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex17[1].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex17[2].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);
		vertex17[3].col = D3DCOLOR_RGBA(COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX);

		// �߂�{�^���̐F�ς��Ɗg��
		if (cl.x >= g_returnPosition.x && cl.x <= g_returnPosition.x + 90.0f)
		{
			if (cl.y >= g_returnPosition.y && cl.y <= g_returnPosition.y + 70.0f)
			{
				vertex17[0].x = g_returnPosition.x - BIGSIZE2_X;
				vertex17[0].y = g_returnPosition.y - BIGSIZE2_Y;
				vertex17[0].z = 0.0f;

				vertex17[1].x = g_returnPosition.x + 90.0f + BIGSIZE2_X;
				vertex17[1].y = g_returnPosition.y - BIGSIZE2_Y;
				vertex17[1].z = 0.0f;

				vertex17[2].x = g_returnPosition.x - BIGSIZE2_X;
				vertex17[2].y = g_returnPosition.y + 70.0f + BIGSIZE2_Y;
				vertex17[2].z = 0.0f;

				vertex17[3].x = g_returnPosition.x + 90.0f + BIGSIZE2_X;
				vertex17[3].y = g_returnPosition.y + 70.0f + BIGSIZE2_Y;
				vertex17[3].z = 0.0f;

				vertex17[0].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex17[1].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex17[2].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
				vertex17[3].col = D3DCOLOR_RGBA(0, 0, COLOR_MAX, 0);
			}
		}

		// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
		vertex17[0].u = 0.0f;
		vertex17[0].v = 0.0f;
		vertex17[1].u = 1.0f;
		vertex17[1].v = 0.0f;
		vertex17[2].u = 0.0f;
		vertex17[2].v = 1.0f;
		vertex17[3].u = 1.0f;
		vertex17[3].v = 1.0f;
	}
	
	// �J�[�\��
	vertex8[0].x = cl.x - CURSOR_X;
	vertex8[0].y = cl.y - CURSOR_Y;
	vertex8[0].z = 0.0f;

	vertex8[1].x = cl.x + CURSOR_X;
	vertex8[1].y = cl.y - CURSOR_Y;
	vertex8[1].z = 0.0f;

	vertex8[2].x = cl.x - CURSOR_X;
	vertex8[2].y = cl.y + CURSOR_Y;
	vertex8[2].z = 0.0f;

	vertex8[3].x = cl.x + CURSOR_X;
	vertex8[3].y = cl.y + CURSOR_Y;
	vertex8[3].z = 0.0f;

	// �^�C�g���ɖ߂�
	if (GetMouseLeftTrigger())
	{
		if (setumei == true)
		{
			if (cl.x >= g_returnPosition.x && cl.x <= g_returnPosition.x + 90.0f)
			{
				if (cl.y >= g_returnPosition.y && cl.y <= g_returnPosition.y + 70.0f)
				{
					PlaySound(SOUND_LABEL_SE003);  // �N���b�N

					SceneFlag = 0;
					setumei = false;
				}
			}
		}
		else
		{
			if (cl.x >= g_nextPosition.x && cl.x <= g_nextPosition.x + 90.0f)
			{
				if (cl.y >= g_nextPosition.y && cl.y <= g_nextPosition.y + 70.0f)
				{
					PlaySound(SOUND_LABEL_SE003);  // �N���b�N
					setumei = true;
				}
			}
		}
	}
}
