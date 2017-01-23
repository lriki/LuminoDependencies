
#ifndef	__EFFEKSEER_INSTANCE_H__
#define	__EFFEKSEER_INSTANCE_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "Effekseer.Base.h"

#include "Effekseer.Vector3D.h"
#include "Effekseer.Matrix43.h"
#include "Effekseer.RectF.h"
#include "Effekseer.Color.h"

#include "Effekseer.EffectNodeSprite.h"
#include "Effekseer.EffectNodeRibbon.h"
#include "Effekseer.EffectNodeRing.h"
#include "Effekseer.EffectNodeModel.h"
#include "Effekseer.EffectNodeTrack.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Effekseer
{
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------

/**
	@brief	�G�t�F�N�g�̎���
*/
class Instance
{
	friend class Manager;
	friend class InstanceContainer;


public:
	static const int32_t ChildrenMax = 16;

	// �}�l�[�W��
	Manager*	m_pManager;

	// �p�����[�^�[
	EffectNode* m_pEffectNode;

	// �R���e�i
	InstanceContainer*	m_pContainer;

	// �O���[�v�̘A�����X�g�̐擪
	InstanceGroup*	m_headGroups;

	// �e
	Instance*	m_pParent;
	
	// �O���[�o���ʒu
	Vector3D	m_GlobalPosition;
	Vector3D	m_GlobalVelocity;
	
	// �O���[�o���ʒu�␳
	Vector3D	m_GlobalRevisionLocation;
	Vector3D	m_GlobalRevisionVelocity;
	
	union 
	{
		struct
		{
		
		} fixed;

		struct
		{
			vector3d location;
			vector3d velocity;
			vector3d acceleration;
		} random;

		struct
		{
			vector3d	start;
			vector3d	end;
		} easing;

		struct
		{
			vector3d	offset;
		} fcruve;

	} translation_values;

	union 
	{
		struct
		{
		
		} fixed;

		struct
		{
			vector3d rotation;
			vector3d velocity;
			vector3d acceleration;
		} random;

		struct
		{
			vector3d start;
			vector3d end;
		} easing;
		
		struct
		{
			float rotation;
			vector3d axis;

			union
			{
				struct
				{
					float rotation;
					float velocity;
					float acceleration;
				} random;

				struct
				{
					float start;
					float end;
				} easing;
			};
		} axis;

		struct
		{
			vector3d offset;
		} fcruve;

	} rotation_values;

	union 
	{
		struct
		{
		
		} fixed;

		struct
		{
			vector3d  scale;
			vector3d  velocity;
			vector3d  acceleration;
		} random;

		struct
		{
			vector3d  start;
			vector3d  end;
		} easing;
		
		struct
		{
			float  scale;
			float  velocity;
			float  acceleration;
		} single_random;

		struct
		{
			float  start;
			float  end;
		} single_easing;

		struct
		{
			vector3d offset;
		} fcruve;

	} scaling_values;

	// �`��
	union
	{
		EffectNodeSprite::InstanceValues	sprite;
		EffectNodeRibbon::InstanceValues	ribbon;
		EffectNodeRing::InstanceValues		ring;
		EffectNodeModel::InstanceValues		model;
		EffectNodeTrack::InstanceValues		track;
	} rendererValues;
	
	// ��
	union
	{
		int		delay;
	} soundValues;

	// ���
	eInstanceState	m_State;

	// ��������
	float		m_LivedTime;

	// ��������Ă���̎���
	float		m_LivingTime;

	/* �������ꂽ�q�̌� */
	int32_t		m_generatedChildrenCount[ChildrenMax];

	/* ���Ɏq�𐶐����鎞�� */
	float		m_nextGenerationTime[ChildrenMax];

	// �����ʒu
	Matrix43		m_GenerationLocation;

	// �ϊ��p�s��
	Matrix43		m_GlobalMatrix43;

	// �e�̕ϊ��p�s��
	Matrix43		m_ParentMatrix43;

	/* ���Ԃ�i�߂邩�ǂ���? */
	bool			m_stepTime;

	/* �X�V�ԍ� */
	uint32_t		m_sequenceNumber;

	// �R���X�g���N�^
	Instance( Manager* pManager, EffectNode* pEffectNode, InstanceContainer* pContainer );

	// �f�X�g���N�^
	virtual ~Instance();

public:
	/**
		@brief	��Ԃ̎擾
	*/
	eInstanceState GetState() const;

	/**
		@brief	�s��̎擾
	*/
	const Matrix43& GetGlobalMatrix43() const;

	/**
		@brief	������
	*/
	void Initialize( Instance* parent, int32_t instanceNumber );

	/**
		@brief	�X�V
	*/
	void Update( float deltaFrame, bool shown );

	/**
		@brief	�`��
	*/
	void Draw();

	/**
		@brief	�j��
	*/
	void Kill();

	/**
		@brief	UV�̈ʒu�擾
	*/
	RectF GetUV() const;

private:
	/**
		@brief	�s��̍X�V
	*/
	void CalculateMatrix( float deltaFrame );
	
	/**
		@brief	�s��̍X�V
	*/
	void CalculateParentMatrix();
	
	/**
		@brief	��΃p�����[�^�̔��f
	*/
	void ModifyMatrixFromLocationAbs( float deltaFrame );
	
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEER_INSTANCE_H__
