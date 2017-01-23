
#ifndef	__EFFEKSEERRENDERER_DX9_RENDERER_H__
#define	__EFFEKSEERRENDERER_DX9_RENDERER_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerRendererDX9.Base.h"
#include "../../EffekseerRendererCommon/EffekseerRenderer.Renderer.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerRendererDX9
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	�`��N���X
*/
class Renderer
	: public ::EffekseerRenderer::Renderer
{
protected:
	Renderer() {}
	virtual ~Renderer() {}

public:
	/**
		@brief	�C���X�^���X�𐶐�����B
		@param	device	[in]	DirectX�̃f�o�C�X
		@param	squareMaxCount	[in]	�ő�`��X�v���C�g��
		@return	�C���X�^���X
	*/
	static Renderer* Create( LPDIRECT3DDEVICE9 device, int32_t squareMaxCount );

	/**
		@brief	�f�o�C�X���擾����B
	*/
	virtual LPDIRECT3DDEVICE9 GetDevice() = 0;

	/**
		@brief	�f�o�C�X���X�g���Z�b�g�ԂŃf�o�C�X���̂��č\�z����ۂɊO������f�o�C�X��ݒ肷��B
	*/
	virtual void ChangeDevice( LPDIRECT3DDEVICE9 device ) = 0;

	/**
	@brief	�w�i���擾����B
	*/
	virtual IDirect3DTexture9* GetBackground() = 0;

	/**
	@brief	�w�i��ݒ肷��B
	*/
	virtual void SetBackground(IDirect3DTexture9* background) = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	���f��
*/
class Model : public Effekseer::Model
{
private:

public:
	IDirect3DVertexBuffer9*		VertexBuffer;
	IDirect3DIndexBuffer9*		IndexBuffer;
	int32_t						VertexCount;
	int32_t						IndexCount;
	int32_t						FaceCount;
	int32_t						ModelCount;

	Model( uint8_t* data, int32_t size )
		: Effekseer::Model	( data, size )
		, VertexBuffer	( NULL )
		, IndexBuffer	( NULL )
		, VertexCount		( 0 )
		, IndexCount		( 0 )
		, FaceCount			( 0 )
		, ModelCount		( 0 )
	{
	}

	virtual ~Model()
	{
		ES_SAFE_RELEASE( VertexBuffer );
		ES_SAFE_RELEASE( IndexBuffer );
	}
};


//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_DX9_RENDERER_H__