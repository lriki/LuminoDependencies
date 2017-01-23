
#ifndef	__EFFEKSEER_INSTANCEGLOBAL_H__
#define	__EFFEKSEER_INSTANCEGLOBAL_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "Effekseer.Base.h"
#include "Effekseer.Vector3D.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
	@brief	�C���X�^���X���ʕ���
	@note
	�������ꂽ�C���X�^���X�̑S�Ă���Q�Ƃł��镔��
*/
class InstanceGlobal
{
	friend class ManagerImplemented;

private:
	/* ���̃G�t�F�N�g�Ŏg�p���Ă���C���X�^���X�� */
	int			m_instanceCount;
	
	/* �X�V���ꂽ�t���[���� */
	float		m_updatedFrame;

	InstanceContainer*	m_rootContainer;
	Vector3D			m_targetLocation;

	InstanceGlobal();

	virtual ~InstanceGlobal();

public:
	void IncInstanceCount();

	void DecInstanceCount();

	void AddUpdatedFrame( float frame );

	/**
		@brief	�S�ẴC���X�^���X�����擾
	*/
	int GetInstanceCount();

	/**
		@brief	�X�V���ꂽ�t���[�������擾����B
	*/
	float GetUpdatedFrame();

	InstanceContainer* GetRootContainer() const;
	void SetRootContainer( InstanceContainer* container );

	const Vector3D& GetTargetLocation() const;
	void SetTargetLocation( const Vector3D& location );
};
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEER_INSTANCEGLOBAL_H__
