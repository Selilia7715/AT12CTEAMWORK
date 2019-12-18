//=============================================================================
//
// DX21
// DirectX���^���� [main.cpp]
//
//=============================================================================
#include "Main.h"
#include "Title.h"
#include "GameScene.h"
#include "Result.h"
#include "Select.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)

// FPS�Ǘ��p
int g_nCountFPS = 0;
float g_dispFPS = 0;

IGraphBuilder *pGraphBuilder;
IMediaControl *pMediaControl;
IVideoWindow *pVideoWindow;

// �������z�֐�
int SceneFlag = 1; // �V�[���t���O

// �J�[�\���̍��W�̕ϐ�
POINT cl; 

// �e�N�X�`��
int g_texture;  

GameScene gamescene;
Title title;
Result result;
SelectStage selectstage;

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

				UpdateXinputControllerState();  // XBOX 

				// Upadate�EDraw
				// �`��(��񂾂��Ă�)
				g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
					D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

				if (SUCCEEDED(g_pD3DDevice->BeginScene()))
				{
					switch (SceneFlag)
					{
					case 1:// Title



						// �Đ��J�n
						pMediaControl->Run();

						title.Update(&SceneFlag);							   // �X�V
						title.Draw(&g_pD3DDevice);						   // �`��

						break;

					case 2:// Select
						// �Z���N�g	
						selectstage.Update(&SceneFlag);
						selectstage.Draw(&g_pD3DDevice);

					case 3:// GameScene

						// �w�i�ƃX�e�[�W
						gamescene.Update(&SceneFlag);
						gamescene.Draw(&g_pD3DDevice);
						break;

					case 4:// Result
						result.Update(&SceneFlag);
						result.Draw(&g_pD3DDevice);
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
	// COM�I��
	CoUninitialize();

	return (int)msg.wParam, 0;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	////////////////////////////////////////////////////////////////////////////////////////////
    // �J�[�\��
	GetCursorPos(&cl);  // ���W�擾
	//ScreenToClient(hWnd, &cl); // �J�[�\���̉摜�ƂȂ���̂�\��(�����m_player_pD3DTexture��\��) player�N���X���Q��
	// �J�[�\���̕\��������(�}�E�X�J�[�\���̂��)
	//ShowCursor(false); // �����Ƃ��̂܂�(true�ɂȂ�ƃ}�E�X�J�[�\�����o�Ă���)
	ShowCursor(true); // �����Ƃ��̂܂�(true�ɂȂ�ƃ}�E�X�J�[�\�����o�Ă���)
	////////////////////////////////////////////////////////////////////////////////////////////

	int nID;

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

	// COM��������
	CoInitialize(NULL);

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// FilterGraph�𐶐�
	CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC,
		IID_IGraphBuilder,
		(LPVOID *)&pGraphBuilder);

	// MediaControl�C���^�[�t�F�[�X�擾
	pGraphBuilder->QueryInterface(IID_IMediaControl,
		(LPVOID *)&pMediaControl);

	//// �t���X�N���[���ɂł���
	//pGraphBuilder->QueryInterface(IID_IVideoWindow,
	//	(LPVOID *)&pVideoWindow);

	BSTR bstr1 = CComBSTR(FILENAME);
	// Graph�𐶐�
	pMediaControl->RenderFile(bstr1);
	//// Full Screen �J�n
	//pVideoWindow->put_FullScreenMode(OATRUE);

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

	// Xinput������
	InitXinputState();

	// XAudio2
	InitSound();

	title.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // Title�̏�����
	selectstage.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // Select�̏�����
	gamescene.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // GameScene�̏�����
	result.Init(&hWnd, &g_pD3DDevice, &g_texture, &cl); // Result�̏�����

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	// �����F
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
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

	// ���������
	pMediaControl->Release();
	pGraphBuilder->Release();
	pVideoWindow->Release();

	// �������
	title.Uninit();
	selectstage.Uninit();
	gamescene.Uninit();
	result.Uninit();
}
