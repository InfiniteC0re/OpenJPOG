#pragma once
#include "TKernel/TMatrix44.h"
#include "TKernel/TQuaternion.h"
#include "TKernel/TVector3.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACE_EXPORTS TTransformObject
{
public:
	class TTransformData
	{
	public:

		TTransformData()
			: m_Scale(1.0f, 1.0f, 1.0f)
		{

		}

		enum MODE
		{
			QUAT  = 0,
			EULER = 1,
			MATRIX = 2
		};

		enum EROT : unsigned char
		{
			EROT_X,
			EROT_Y,
			EROT_Z
		};

		MODE     m_eMode;
		TVector3 m_Translation;
		TVector3 m_Scale;
		EROT   m_EulerOrder[3];
	};

	#define MODE_QUAT   TTransformData::QUAT
	#define MODE_EULER  TTransformData::EULER
	#define MODE_MATRIX     TTransformData::MATRIX

public:
	TTransformObject();
	~TTransformObject();

	void Push();
	void Pop();

	TVector3 &GetTranslation();
	void      GetLocalMatrixImp(TMatrix44 &a_rOutMatrix);

	void SetEuler(const TVector3 &a_rEuler);
	void SetEulerOrder(TUINT8 a_uiX, TUINT8 a_uiy, TUINT8 a_uiz);
	void SetTranslate(const TVector3 &a_rTranslation);
	void SetQuat(const TQuaternion &a_rQuaternion);
	void SetMatrix(const TMatrix44 &a_rMatrix);

	void ResetChangedState()
	{
		m_bChanged = TFALSE;
	}

	TBOOL HasChanged() const
	{
		return m_bChanged;
	}

	TTransformData::MODE SetMode(TTransformData::MODE a_eMode)
	{
		TTransformData::MODE old = a_eMode;
		m_oData.m_eMode    = a_eMode;
		return old;
	}

	TTransformData::MODE GetMode() const
	{
		return m_oData.m_eMode;
	}

	const TQuaternion &GetQuat()
	{
		TASSERT(MODE_QUAT==GetMode());
		return m_Quat;
	}

	const TMatrix44 &GetMatrix()
	{
		TASSERT(MODE_MATRIX==GetMode());
		return m_Matrix;
	}

	const TVector3 &GetEuler()
	{
		TASSERT(MODE_EULER==GetMode());
		return m_Euler;
	}

	const TVector3 &GetScale() const
	{
		return m_oData.m_Scale;
	}

private:
	union
	{
		TMatrix44   m_Matrix;
		TQuaternion m_Quat;
		TVector3    m_Euler;
	};

	TTransformData m_oData; // 0x64
	TBOOL    m_bChanged;
};

TOSHI_NAMESPACE_END
