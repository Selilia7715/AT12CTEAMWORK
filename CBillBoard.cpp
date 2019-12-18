#include	"CBillBoard.h"

	// ビルボードの頂点座標を計算
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

// サイズをセット
void CBillBoard::SetSize(float x, float y){
	m_XSize = x;
	m_YSize = y;
	CalcVertex();
}

// カラー値をセット
void CBillBoard::SetColor(D3DCOLOR col){
	m_Color = col;
	CalcVertex();
}

// 位置をセット
void CBillBoard::SetPosition(float x,float y,float z){
		m_x=x;
		m_y=y;
		m_z=z;
}

// ビルボード用の行列を生成
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

// 描画
void CBillBoard::Draw(LPDIRECT3DDEVICE9 lpDXDevice){
	//ライティング計算はしない。　深度バッファには書き込まない
	lpDXDevice->SetRenderState(D3DRS_LIGHTING, FALSE);							//   光源計算オフ（頂点の色が有効になる）
	lpDXDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//   Ｚバッファを無効化（アルファブレンドを有効にするため）

	// テクスチャステージステート
	lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	lpDXDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//テクスチャをセット
	lpDXDevice->SetTexture(0, m_Tex1);
	//頂点の型をセット
	lpDXDevice->SetFVF(D3DFVFCUSTOM_VERTEX);

	// ワールド変換行列をセット
	lpDXDevice->SetTransform(D3DTS_WORLD, &m_mat);

	//レンダリング
	lpDXDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_Vertex, sizeof(MyVertex));

	lpDXDevice->SetRenderState(D3DRS_LIGHTING, true);							//   光源計算オフ（頂点の色が有効になる）
	lpDXDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);						//   Ｚバッファを無効化（アルファブレンドを有効にするため）
}

// ビルボードを描画
void CBillBoard::DrawNoBillBoard(LPDIRECT3DDEVICE9 lpDXDevice){

	// カメラ行列から　ビルボード用のマトリックスを作成

	D3DXMatrixIdentity(&m_mat);
	m_mat._41 = m_x;
	m_mat._42 = m_y;
	m_mat._43 = m_z;

	//アルファブレンディングで半透明合成をセットする
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 描画
	Draw(lpDXDevice);

	//アルファブレンディングで半透明合成をセットする
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


// ビルボードを描画
void CBillBoard::DrawBillBoard(LPDIRECT3DDEVICE9 lpDXDevice,const D3DXMATRIX& cameramat){

		// カメラ行列から　ビルボード用のマトリックスを作成
		CalcBillBoardMatrix(cameramat);

		//アルファブレンディングで半透明合成をセットする
		lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
		lpDXDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		lpDXDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

		// 描画
		Draw(lpDXDevice);

		//アルファブレンディングで半透明合成をセットする
		lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// ビルボードを描画(Ｚ軸で回転)
void CBillBoard::DrawRotateBillBoard(LPDIRECT3DDEVICE9 lpDXDevice, const D3DXMATRIX &cameramat, float radian){

	// カメラ行列から　ビルボード用のマトリックスを作成
	CalcBillBoardMatrix(cameramat);

	// Ｚ軸回転行列を作成
	D3DXMATRIX matRotZ;
	D3DXVECTOR3 axisZ(cameramat._13, cameramat._23, cameramat._33);
	D3DXMatrixRotationAxis(&matRotZ, &axisZ, radian);

	// 行列を合成し、位置をセット
	m_mat = m_mat*matRotZ;
	m_mat._41 = m_x;
	m_mat._42 = m_y;
	m_mat._43 = m_z;
	
	//アルファブレンディングをセットする
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	Draw(lpDXDevice);

	//アルファブレンディングをセットする
	lpDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpDXDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpDXDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//	テクスチャ読み込み
bool CBillBoard::LoadTexTure(LPDIRECT3DDEVICE9 lpDXDevice,const char* filename){

		// すでに読み込まれているテクスチャがあれば解放する
		if(m_Tex1!=NULL){
			m_Tex1->Release();
			m_Tex1=NULL;
		}

		// テクスチャオブジェクト生成
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
