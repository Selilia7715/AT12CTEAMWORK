#include	<d3dx9.h>
#include	"main.h"
#include	"game.h"
#include	"input.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = nullptr;			// Direct3D �I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = nullptr;		// Device�I�u�W�F�N�g(�`��ɕK�v)
LPD3DXFONT			g_pD3DXFont = nullptr;		// �t�H���g�ւ̃|�C���^

D3DXMATRIX			g_view;						// �r���[�ϊ��s��
D3DXMATRIX			g_world;					// ���[���h�ϊ��s��
D3DXMATRIX			g_projection;				// �v���W�F�N�V�����ϊ��s��				
//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
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
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.BackBufferCount = 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed = bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (bWindow)
	{// �E�B���h�E���[�h
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O����
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���t�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���u�l�̌J��Ԃ��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g�厞�̕�Ԑݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k�����̕�Ԑݒ�

																			// �e�N�X�`���X�e�[�W�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);					//   �����v�Z�I�t�i�����v�Z��؂��DIFFUSE�F�����̂܂܂ł�j

	// ���\���p�t�H���g��ݒ�
	// pDevice         : �f�o�C�X�ւ̃|�C���^
	// Height          : �����̍���
	// Width           : �����̕�
	// Weight          : �t�H���g�̑���
	// MipLevels       : �~�b�v�}�b�v���x����
	// Italic          : �C�^���b�N�t�H���g
	// CharSet         : �t�H���g�̕����Z�b�g
	// OutputPrecision : ���ۂ̃t�H���g�ƖړI�̃t�H���g�̃T�C�Y����ѓ����̈�v���@���w��
	// Quality         : ���ۂ̃t�H���g�ƖړI�̃t�H���g�Ƃ̈�v���@���w��
	// PitchAndFamily  : �s�b�`�ƃt�@�~���C���f�b�N�X
	// pFacename       : �t�H���g�̖��O��ێ����镶����
	// ppFont          : �t�H���g�ւ̃|�C���^
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

	// �c�h�q�d�b�s�@�h�m�o�t�s������
	InitInput(hInstance, hWnd);

	D3DXMatrixPerspectiveFovLH(&g_projection, D3DX_PI / 4, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &g_projection);

	D3DXVECTOR3 eye = { 0,0,-100 };
	D3DXVECTOR3 lookat = { 0,0,0 };
	D3DXVECTOR3 up = { 0,1,0 };
	D3DXMatrixLookAtLH(&g_view, &eye, &lookat, &up);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_view);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �c�h�q�d�b�s�@�h�m�o�t�s�I������
	UninitInput();

	if (g_pD3DXFont != NULL)
	{// ���\���p�t�H���g�̉��
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}

	if (g_pD3DDevice != NULL)
	{// �f�o�C�X�̉��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̉��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// ���͏���
//=============================================================================
void Input(void) {
	UpdateInput();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{

	Vertex_3D v[3] = {-25,0,0,D3DCOLOR_ARGB(255,255,0,0),
					0,25,0,D3DCOLOR_ARGB(255,255,0,0),
					25,0,0,D3DCOLOR_ARGB(255,255,0,0) };

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 255, 255), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// FPS�`��
		DrawFPS();

		// �P�ʍs��
		D3DXMatrixIdentity(&g_world);
	
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_world);

		g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, v, sizeof(Vertex_3D));

		// Direct3D�ɂ��`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// FPS�\������
//=============================================================================
void DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", GetFpsCounter());

	// �e�L�X�g�`��
	// hDC      : �f�o�C�X�R���e�L�X�g�̃n���h��
	// lpString : �`�悷�镶����ւ̃|�C���^
	// nCount   : ������̕�����
	// lpRect   : �����`�̈�
	// uFormat  : �e�L�X�g�̐��`���@���w��
	g_pD3DXFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff));
}
