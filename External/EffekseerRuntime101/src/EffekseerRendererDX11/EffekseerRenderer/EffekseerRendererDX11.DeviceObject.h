
#ifndef	__EFFEKSEERRENDERER_DX11_DEVICEOBJECT_H__
#define	__EFFEKSEERRENDERER_DX11_DEVICEOBJECT_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerRendererDX11.RendererImplemented.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerRendererDX11
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	�f�o�C�X�ɂ���Đ��������I�u�W�F�N�g
*/
class DeviceObject
{
private:
	RendererImplemented*	m_renderer;

public:
		DeviceObject( RendererImplemented* renderer );
		virtual ~DeviceObject();

	public:
		virtual void OnLostDevice() = 0;
		virtual void OnResetDevice() = 0;
		RendererImplemented* GetRenderer() const;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_DX11_DEVICEOBJECT_H__