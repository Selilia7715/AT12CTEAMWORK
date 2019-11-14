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
#define WINDOW_NAME		"DirectX���^����"	// �E�B���h�E�̖��O
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

VERTEX_2D vertex[VERTEX_MAX];     // ���L����
VERTEX_2D vertex2[VERTEX_MAX];     // �w�i
VERTEX_2D vertex3[VERTEX_MAX];     // �^�C�g��
VERTEX_2D vertex4[VERTEX_MAX];     // ���U���g

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void Uninit(void);
void GameInit(void);      // �Q�[�����	
void GameUpdate(void);   
void GameDraw(void);
void TitleInit(void);     // �^�C�g�����
void TitleDraw(void);
void TitleUpdate(void);
void ResultInit(void);   // ���U���g���
void ResultDraw(void);
void ResultUpdate(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
LPDIRECT3DTEXTURE9  g_pD3DTexture = NULL;    // �e�N�X�`�����i�[����ϐ�(�L����1)
LPDIRECT3DTEXTURE9  g_pD3DTexture2 = NULL;    // �e�N�X�`�����i�[����ϐ�(�w�i)
LPDIRECT3DTEXTURE9  g_pD3DTexture3 = NULL;    // �e�N�X�`�����i�[����ϐ�(�^�C�g��)
LPDIRECT3DTEXTURE9  g_pD3DTexture4 = NULL;    // �e�N�X�`�����i�[����ϐ�(���U���g)


LPD3DXFONT g_pD3DXFont = NULL;

D3DVECTOR g_playerPosition;  // ��l�����W

POINT cl; // �J�[�\��


// FPS�Ǘ��p
int g_nCountFPS = 0;
float g_dispFPS = 0;


// �V�[���t���O
int SceneFlag = 0;

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

				switch (scene)
				{
				case TITLE:     // �^�C�g�����

					TitleInit();
					TitleDraw();
					TitleUpdate();
					break;

				case GAME:     // �Q�[�����
					GameInit();
					GameDraw();
					GameUpdate();
					break;

				case RESULT:   // ���U���g���
					ResultInit();
					ResultDraw();
					ResultUpdate();
					break;

				}

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

	//SetCursorPos(900,300);
	// cursolposition
	// �J�[�\���̍��W���擾
	GetCursorPos(&cl);
	// ���J�[�\���������āA�e�N�X�`�����`�悳���
	ScreenToClient(hWnd, &cl);  
	// �J�[�\���\���������@
	ShowCursor(false);

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

			ShowCursor(true);
			SetCursorPos(900, 300);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

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
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/OP.tga", &g_pD3DTexture3)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(���U���g)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/92.jpg", &g_pD3DTexture4)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}


	// �e�N�X�`���`��(���L����)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/5.png", &g_pD3DTexture)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
	}

	// �e�N�X�`���`��(�w�i)
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rom/haikei.jpg", &g_pD3DTexture2)) == 1) {
		// ���b�Z�[�WBOX�Łu�e�N�X�`�����[�h���s�v�ƕ\��
		aID = MessageBox(hWnd, "�e�N�X�`�����[�h���s", "���s", MB_YESNO);
		if (aID == IDYES)
		{
			DestroyWindow(hWnd);
		}
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
	if (g_pD3DTexture != NULL)
	{
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
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

}

//=============================================================================
// �Q�[������
//=============================================================================
void GameInit()
{
	// �����l
	g_playerPosition.x = 10.0f;
	g_playerPosition.y = 400.0f;

	// �L����1
	//vertex[0].x = g_playerPosition.x;
	//vertex[0].y = g_playerPosition.y;
	//vertex[0].z = g_playerPosition.z;

	//vertex[1].x = g_playerPosition.x + 50.0f;
	//vertex[1].y = g_playerPosition.y;
	//vertex[1].z = g_playerPosition.z;

	//vertex[2].x = g_playerPosition.x;
	//vertex[2].y = g_playerPosition.y + 50.0f;
	//vertex[2].z = g_playerPosition.z;

	//vertex[3].x = g_playerPosition.x + 50.0f;
	//vertex[3].y = g_playerPosition.y + 50.0f;
	//vertex[3].z = g_playerPosition.z;


	// �L����(�J�[�\��ver)
	vertex[0].x = cl.x - 50.0f;  // cl.x�̓J�[�\����X���W��\���Ă��܂��B
	vertex[0].y = cl.y - 50.0f;  // cl.y�̓J�[�\����Y���W��\���Ă��܂��B
	vertex[0].z = 0.0f;

	vertex[1].x = cl.x + 50.0f;
	vertex[1].y = cl.y - 50.0f;
	vertex[1].z = 0.0f;

	vertex[2].x = cl.x - 50.0f;
	vertex[2].y = cl.y + 50.0f;
	vertex[2].z = 0.0f;

	vertex[3].x = cl.x + 50.0f;
	vertex[3].y = cl.y + 50.0f;
	vertex[3].z = 0.0f;

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

void GameUpdate()
{
	// �J�[�\���Ŏ��L�����̍��W�𓮂����Ă���̂ŃL�[���͂̓R�����g�ɂ��Ă��܂��B

	//�ړ�����
	// �����L�[(�L����1)
	// ��
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	g_playerPosition.x -= KYARA_SPEED_MAX;

	//}

	//// �E
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	g_playerPosition.x += KYARA_SPEED_MAX;

	//}

	//// ��
	//if (GetKeyboardPress(DIK_UP))
	//{
	//	g_playerPosition.y -= KYARA_SPEED_MAX;

	//}

	//// ��
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	g_playerPosition.y += KYARA_SPEED_MAX;
	//}

	// �J��
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		scene = RESULT;
	}

}

void GameDraw(void)
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

	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//// �J�����O���I�t�ɂ���
	/*g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DDCULL_NONE);*/

	// �`��
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//��̓I�ȕ`�揈�����R�R�ɋL�q���Ă���

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


		// ���L�����`��
		g_pD3DDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`�����|���S���ɃZ�b�g
		g_pD3DDevice->SetTexture(0, g_pD3DTexture);

		// g_pD3DDevice->DrawPrimitiveUP���Ă�
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP, // �|���S���̎��(�O�p�A�l�p�Ȃ�)
			2,                   // �|���S���̐�
			&vertex[0],          // ���_�f�[�^�\���̂̐擪�A�h���X
			sizeof(VERTEX_2D)    // ���_�f�[�^�\���̂̃T�C�Y
		);

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}


	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	// pSourceRect         : �]������`
	// pDestRect           : �]�����`
	// hDestWindowOverride : �]����E�C���h�E�ւ̃|�C���^
	// pDirtyRegion        : �ʏ��NULL��
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//=============================================================================
// �^�C�g������
//=============================================================================
void TitleInit()
{
	//// �^�C�g�� �}�E�X
	//vertex3[0].x = cl.x - 300; // cl.x�̓J�[�\����X���W��\���Ă��܂��B
	//vertex3[0].y = cl.y - 150; // cl.y�̓J�[�\����Y���W��\���Ă��܂��B
	//vertex3[0].z = 0; 

	//vertex3[1].x = cl.x + 300;
	//vertex3[1].y = cl.y - 150;
	//vertex3[1].z = 0.0f;

	//vertex3[2].x = cl.x - 300;
	//vertex3[2].y = cl.y + 150;
	//vertex3[2].z = 0.0f;

	//vertex3[3].x = cl.x  + 300;
	//vertex3[3].y = cl.y + 150;
	//vertex3[3].z = 0.0f;

	// �^�C�g��
	vertex3[0].x = 0.0f;
	vertex3[0].y = 0.0f;
	vertex3[0].z = 0.0f;

	vertex3[1].x = SCREEN_WIDTH;
	vertex3[1].y = 0.0f;
	vertex3[1].z = 0.0f;

	vertex3[2].x = 0.0f;
	vertex3[2].y = SCREEN_HEIGHT;
	vertex3[2].z = 0.0f;

	vertex3[3].x = SCREEN_WIDTH;
	vertex3[3].y = SCREEN_HEIGHT;
	vertex3[3].z = 0.0f;

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

	// �e�N�X�`�����W(�w�i�Ȃ̂ňꖇ)
	vertex3[0].u = 0.0f;
	vertex3[0].v = 0.0f;
	vertex3[1].u = 1.0f;
	vertex3[1].v = 0.0f;
	vertex3[2].u = 0.0f;
	vertex3[2].v = 1.0f;
	vertex3[3].u = 1.0f;
	vertex3[3].v = 1.0f;
}

void TitleDraw()
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//// �J�����O���I�t�ɂ���
	/*g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DDCULL_NONE);*/

	// �^�C�g���`��
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//��̓I�ȕ`�揈�����R�R�ɋL�q���Ă���

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

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void TitleUpdate()
{

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		scene = GAME;
	}
}

//=============================================================================
// �Q�[���I�[�o�[����
//=============================================================================
void ResultInit()
{
	// ���U���g
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
}

void ResultDraw()
{
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);


	//// �J�����O���I�t�ɂ���
	/*g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DDCULL_NONE);*/

	// �^�C�g���`��
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//��̓I�ȕ`�揈�����R�R�ɋL�q���Ă���

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

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void ResultUpdate()
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		scene = TITLE;
	}
}

