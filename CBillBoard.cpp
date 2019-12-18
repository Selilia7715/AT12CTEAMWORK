#include	"CBillBoard.h"

	// �r���{�[�h�̒��_���W���v�Z
void CBillBoard::CalcVertex(){
		m_Vertex[0].x = -m_XSize/2;
		m_Vertex[0].y = -m_YSize/2;
		m_Vertex[0].z =0.0f;
		m_Vertex[0].color = m_Color;
		m_Vertex[0].tu =0.0f;
		m_Vertex[0].tv =1.0f;

		m_Vertex[1].x = -m_XSize/2;
		m_Vertex[1].y =  m_YSize/2;
		m_Vertex[1].z =0.0f;
		m_Vertex[1].color = m_Color;
		m_Vertex[1].tu =0.0f;
		m_Vertex[1].tv =0.0f;

		m_Vertex[2].x = m_XSize/2;
		m_Vertex[2].y = m_YSize/2;
		m_Vertex[2].z =0.0f;
		m_Vertex[2].color = m_Color;
		m_Vertex[2].tu =1.0f;
		m_Vertex[2].tv =0.0f;

		m_Vertex[3].x = m_XSize/2;
		m_Vertex[3].y = -m_YSize/2;
		m_Vertex[3].z =0;
		m_Vertex[3].color = m_Color;
		m_Vertex[3].tu =1.0f;
		m_Vertex[3].tv =1.0f;
}

// �T�C�Y���Z�b�g
void CBillBoard::SetSize(float x, float y){
	m_XSize = x;
	m_YSize = y;
	CalcVertex();
}

// �J���[�l���Z�b�g
void CBillBoard::SetColor(D3DCOLOR col){
	m_Color = col;
	CalcVertex();
}

// �ʒu���Z�b�g
void CBillBoard::SetPosition(float x,float y,float z){
		m_x=x;
		m_y=y;
		m_z=z;
}

// �r���{�[�h�p�̍s��𐶐�
void CBillBoard::CalcBillBoardMatrix(const D3DXMATRIX&	cameramat){

		m_mat._11 =cameramat._11;
		m_mat._12 =cameramat._21;
		m_mat._13 =cameramat._31;

		m_mat._21 =cameramat._12;
		m_mat._22 =cameramat._22; 
		m_mat._23 =cameramat._32;

		m_mat._31 =cameramat._13;
		m_mat._32 =cameramat._23; 
		m_mat._33 =cameramat._33;

		m_mat._41 = m_x;
		m_mat._42 = m_y;
		m_mat._43 = m_z;

		m_mat._14=0;
		m_mat._24=0;
		m_mat._34=0;
		m_mat._44=1;
}

// �`��
void CBillBoard::Draw(LPDIRECT3DDEVICE9 lpDXDevice){
	//���C�e�B���O�v�Z�͂��Ȃ��B�@�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	lpDXDevice->SetRenderState(D3DRS_LIGHTING, FALSE);							//   �����v�Z�I�t�i���_�̐F���L���ɂȂ�j
	lpDXDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//   �y�o�b�t�@�𖳌����i�A���t�@�u�����h��L���ɂ��邽�߁j

	// �e�N�X�`���X�e�[�W�X�e�[�g
	lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	lpDXDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//�e�N�X�`�����Z�b�g
	lpDXDevice->SetTexture(0, m_Tex1);
	//���_�̌^���Z�b�g
	lpDXDevice->SetFVF(D3DFVFCUSTOM_VERTEX);

	// ���[���h�ϊ��s����Z�b�g
	lpDXDevice->SetTransform(D3DTS_WORLD, &m_mat);

	//�����_�����O
	lpDXDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Vertex, sizeof(MyVertex));

	lpDXDevice->SetRenderState(D3DRS_LIGHTING, true);							//   �����v�Z�I�t�i���_�̐F���L���ɂȂ�j
	lpDXDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);						//   �y�o�b�t�@�𖳌����i�A���t�@�u�����h��L���ɂ��邽�߁j
}

// �r���{�[�h��`��
void CBillBoard::DrawNoBillBoard(LPDIRECT3DDEVICE9 lpDXDevice){

	// �J�����s�񂩂�@�r���{�[�h�p�̃}�g���b�N�X���쐬

	D3DXMatrixIdentity(&m_mat);
	m_mat._41 = m_x;
	m_mat._42 = m_y;
	m_mat._43 = m_z;

	//�A���t�@�u�����f�B���O�Ŕ������������Z�b�g����
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �`��
	Draw(lpDXDevice);

	//�A���t�@�u�����f�B���O�Ŕ������������Z�b�g����
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


// �r���{�[�h��`��
void CBillBoard::DrawBillBoard(LPDIRECT3DDEVICE9 lpDXDevice,const D3DXMATRIX& cameramat){

		// �J�����s�񂩂�@�r���{�[�h�p�̃}�g���b�N�X���쐬
		CalcBillBoardMatrix(cameramat);

		//�A���t�@�u�����f�B���O�Ŕ������������Z�b�g����
		lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		lpDXDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		lpDXDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

		// �`��
		Draw(lpDXDevice);

		//�A���t�@�u�����f�B���O�Ŕ������������Z�b�g����
		lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// �r���{�[�h��`��(�y���ŉ�])
void CBillBoard::DrawRotateBillBoard(LPDIRECT3DDEVICE9 lpDXDevice, const D3DXMATRIX &cameramat, float radian){

	// �J�����s�񂩂�@�r���{�[�h�p�̃}�g���b�N�X���쐬
	CalcBillBoardMatrix(cameramat);

	// �y����]�s����쐬
	D3DXMATRIX matRotZ;
	D3DXVECTOR3 axisZ(cameramat._13, cameramat._23, cameramat._33);
	D3DXMatrixRotationAxis(&matRotZ, &axisZ, radian);

	// �s����������A�ʒu���Z�b�g
	m_mat = m_mat*matRotZ;
	m_mat._41 = m_x;
	m_mat._42 = m_y;
	m_mat._43 = m_z;
	
	//�A���t�@�u�����f�B���O���Z�b�g����
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	Draw(lpDXDevice);

	//�A���t�@�u�����f�B���O���Z�b�g����
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//	�e�N�X�`���ǂݍ���
bool CBillBoard::LoadTexTure(LPDIRECT3DDEVICE9 lpDXDevice,const char* filename){

		// ���łɓǂݍ��܂�Ă���e�N�X�`��������Ή������
		if(m_Tex1!=NULL){
			m_Tex1->Release();
			m_Tex1=NULL;
		}

		// �e�N�X�`���I�u�W�F�N�g����
		HRESULT hr = D3DXCreateTextureFromFileEx(lpDXDevice,
											filename,
											0,0,
											0,0,
											D3DFMT_UNKNOWN,
											D3DPOOL_DEFAULT,
											D3DX_FILTER_NONE,
											D3DX_DEFAULT,
								            0xff000000,
											NULL,
											NULL,
											&m_Tex1);
		if(FAILED(hr)){
			return false;
		}
		return true;
}
