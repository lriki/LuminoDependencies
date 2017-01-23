
#ifndef	__CULLING3D_CULLING3D_H__
#define	__CULLING3D_CULLING3D_H__

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <stdint.h>


namespace Culling3D
{
	/**
	@brief	�ő�l�擾
	*/
	template <typename T, typename U>
	T Max(T t, U u)
	{
		if (t > (T) u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	�ŏ��l�擾
	*/
	template <typename T, typename U>
	T Min(T t, U u)
	{
		if (t < (T) u)
		{
			return t;
		}
		return u;
	}

	/**
	@brief	�͈͓��l�擾
	*/
	template <typename T, typename U, typename V>
	T Clamp(T t, U max_, V min_)
	{
		if (t > (T) max_)
		{
			t = (T) max_;
		}

		if (t < (T) min_)
		{
			t = (T) min_;
		}

		return t;
	}

	template <class T>
	void SafeAddRef(T& t)
	{
		if (t != NULL)
		{
			t->AddRef();
		}
	}

	template <class T>
	void SafeRelease(T& t)
	{
		if (t != NULL)
		{
			t->Release();
			t = NULL;
		}
	}

	template <class T>
	void SafeSubstitute(T& target, T& value)
	{
		SafeAddRef(value);
		SafeRelease(target);
		target = value;
	}

	template <typename T>
	inline void SafeDelete(T*& p)
	{
		if (p != NULL)
		{
			delete (p);
			(p) = NULL;
		}
	}

	template <typename T>
	inline void SafeDeleteArray(T*& p)
	{
		if (p != NULL)
		{
			delete [](p);
			(p) = NULL;
		}
	}

	class World;
	class Object;

	struct Vector3DF
	{
		float	X;
		float	Y;
		float	Z;

		Vector3DF();
		Vector3DF(float x, float y, float z);

		bool operator == (const Vector3DF& o);
		bool operator != (const Vector3DF& o);

		Vector3DF operator-();

		Vector3DF operator + (const Vector3DF& o) const;

		Vector3DF operator - (const Vector3DF& o) const;

		Vector3DF operator * (const Vector3DF& o) const;

		Vector3DF operator / (const Vector3DF& o) const;

		Vector3DF operator * (const float& o) const;

		Vector3DF operator / (const float& o) const;

		Vector3DF& operator += (const Vector3DF& o);

		Vector3DF& operator -= (const Vector3DF& o);

		Vector3DF& operator *= (const Vector3DF& o);

		Vector3DF& operator /= (const Vector3DF& o);

		Vector3DF& operator *= (const float& o);

		Vector3DF& operator /= (const float& o);

		/**
		@brief	���̃x�N�g���̒������擾����B
		*/
		float GetLength() const
		{
			return sqrt(GetSquaredLength());
		}

		/**
		@brief	���̃x�N�g���̒����̓����擾����B
		*/
		float GetSquaredLength() const
		{
			return X * X + Y * Y + Z * Z;
		}

		/**
		@brief	���̃x�N�g���̒�����ݒ肷��B
		*/
		void SetLength(float value)
		{
			float length = GetLength();
			(*this) *= (value / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g�����擾����B
		*/
		Vector3DF GetNormal()
		{
			float length = GetLength();
			return Vector3DF(X / length, Y / length, Z / length);
		}

		/**
		@brief	���̃x�N�g���̒P�ʃx�N�g��������B
		*/
		void Normalize()
		{
			float length = GetLength();
			(*this) /= length;
		}

		/**
		@brief	���ς��擾����B
		*/
		static float Dot(const Vector3DF& v1, const Vector3DF& v2);

		/**
		@brief	�O�ς��擾����B
		@note
		�E��n�̏ꍇ�A�E��̐e�w��v1�A�l�����w��v2�Ƃ����Ƃ��A���w�̕�����Ԃ��B<BR>
		����n�̏ꍇ�A����̐e�w��v1�A�l�����w��v2�Ƃ����Ƃ��A���w�̕�����Ԃ��B<BR>
		*/
		static Vector3DF Cross(const Vector3DF& v1, const Vector3DF& v2);

		/**
		@brief	2�_�Ԃ̋������擾����B
		*/
		static float Distance(const Vector3DF& v1, const Vector3DF& v2);
	};
	
	struct Matrix44
	{
		float	Values[4][4];

		Matrix44();
		Matrix44& SetInverted();
		Vector3DF Transform3D(const Vector3DF& in) const;

		/**
		@brief	�J�����s��(�E��n)��ݒ肷��B
		@param	eye	�J�����̈ʒu
		@param	at	�J�����̒����_
		@param	up	�J�����̏����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetLookAtRH(const Vector3DF& eye, const Vector3DF& at, const Vector3DF& up);

		/**
		@brief	�J�����s��(����n)��ݒ肷��B
		@param	eye	�J�����̈ʒu
		@param	at	�J�����̒����_
		@param	up	�J�����̏����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetLookAtLH(const Vector3DF& eye, const Vector3DF& at, const Vector3DF& up);

		/**
		@brief	�ˉe�s��(�E��n)��ݒ肷��B
		@param	ovY	Y�����ւ̎���p(���W�A��)
		@param	aspect	��ʂ̃A�X�y�N�g��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetPerspectiveFovRH(float ovY, float aspect, float zn, float zf);

		/**
		@brief	OpenGL�p�ˉe�s��(�E��n)��ݒ肷��B
		@param	ovY	Y�����ւ̎���p(���W�A��)
		@param	aspect	��ʂ̃A�X�y�N�g��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetPerspectiveFovRH_OpenGL(float ovY, float aspect, float zn, float zf);

		/**
		@brief	�ˉe�s��(����n)��ݒ肷��B
		@param	ovY	Y�����ւ̎���p(���W�A��)
		@param	aspect	��ʂ̃A�X�y�N�g��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetPerspectiveFovLH(float ovY, float aspect, float zn, float zf);

		/**
		@brief	���ˉe�s��(�E��n)��ݒ肷��B
		@param	width	����
		@param	height	�c��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetOrthographicRH(float width, float height, float zn, float zf);

		/**
		@brief	���ˉe�s��(����n)��ݒ肷��B
		@param	width	����
		@param	height	�c��
		@param	zn	�ŋߋ���
		@param	zf	�ŉ�����
		@return	���̃C���X�^���X�ւ̎Q��
		*/
		Matrix44& SetOrthographicLH(float width, float height, float zn, float zf);

		Matrix44 operator * (const Matrix44& right) const;

		Vector3DF operator*(const Vector3DF& right) const;

		/**
		@brief	��Z���s���B
		@param	o	�o�͐�
		@param	in1	�s��1
		@param	in2	�s��2
		@return	�o�͐�̎Q��
		*/
		static Matrix44& Mul(Matrix44& o, const Matrix44& in1, const Matrix44& in2);
	};

	enum eObjectShapeType
	{
		OBJECT_SHAPE_TYPE_NONE,
		OBJECT_SHAPE_TYPE_SPHERE,
		OBJECT_SHAPE_TYPE_CUBOID,
		OBJECT_SHAPE_TYPE_ALL,
	};


	class IReference
	{
	public:
		/**
		@brief	�Q�ƃJ�E���^�����Z����B
		@return	���Z��̎Q�ƃJ�E���^
		*/
		virtual int AddRef() = 0;

		/**
		@brief	�Q�ƃJ�E���^���擾����B
		@return	�Q�ƃJ�E���^
		*/
		virtual int GetRef() = 0;

		/**
		@brief	�Q�ƃJ�E���^�����Z����B0�ɂȂ������A�C���X�^���X���폜����B
		@return	���Z��̎Q�ƃJ�E���^
		*/
		virtual int Release() = 0;
	};

	class World
		: public IReference
	{
	public:
		virtual void AddObject(Object* o) = 0;
		virtual void RemoveObject(Object* o) = 0;

		virtual void Culling(const Matrix44& cameraProjMat, bool isOpenGL) = 0;
		virtual int32_t GetObjectCount() = 0;
		virtual Object* GetObject(int32_t index) = 0;

		virtual bool Reassign() = 0;

		virtual void Dump(const char* path, const Matrix44& cameraProjMat, bool isOpenGL) = 0;

		static World* Create(float xSize, float ySize, float zSize, int32_t layerCount);
	};

	class Object
		: public IReference
	{
	public:
		virtual void SetShapeType(eObjectShapeType type) = 0;

		virtual Vector3DF GetPosition() = 0;
		virtual void SetPosition(Vector3DF pos) = 0;
		virtual void SetRadius(float radius) = 0;
		virtual void SetCuboidSize(Vector3DF size) = 0;

		virtual void* GetUserData() = 0;
		virtual void SetUserData(void* data) = 0;

		static Object* Create();
	};
}

#endif