#pragma once
#include "TTransformObject.h"
#include "TRenderInterface.h"
#include "TMath.h"
#include "Defines.h"

TOSHI_NAMESPACE_BEGIN

#define MINFOV (1.0f / 180.0f) * TMath::PI
#define MAXFOV TMath::PI

class TRENDERINTERFACE_EXPORTS TCameraObject
{
public:
	TCameraObject();
	~TCameraObject();

	void Render();

	// $TRenderInterface: FUNCTION 100134d0
	TFLOAT SetNear(TFLOAT fNear)
	{
		TFLOAT old = m_fNear;
		m_fNear    = fNear;
		return old;
	}

	// $TRenderInterface: FUNCTION 100134b0
	TFLOAT SetFar(TFLOAT fFar)
	{
		TFLOAT old = m_fFar;
		m_fFar     = fFar;
		return old;
	}

	// $TRenderInterface: FUNCTION 10013210
	TFLOAT SetFOV(TFLOAT fFOV)
	{
		TMath::Clip(fFOV, MINFOV, MAXFOV);
		TFLOAT old = m_fFOV;
		m_fFOV     = fFOV;
		return old;
	}

	// $TRenderInterface: FUNCTION 10013280
	TFLOAT SetProjectionCentreX(TFLOAT fCentreX)
	{
		TMath::Clip(fCentreX, 0.0f, 1.0f);
		TFLOAT old = m_fCentreX;
		m_fCentreX = fCentreX;
		return old;
	}

	// $TRenderInterface: FUNCTION 100132d0
	TFLOAT SetProjectionCentreY(TFLOAT fCentreY)
	{
		TMath::Clip(fCentreY, 0.0f, 1.0f);
		TFLOAT old = m_fCentreY;
		m_fCentreY = fCentreY;
		return old;
	}

	TFLOAT GetNear() const
	{
		return m_fNear;
	}

	TFLOAT GetFar() const
	{
		return m_fFar;
	}

	TFLOAT GetFOV() const
	{
		return m_fFOV;
	}

	TRenderContext::CameraMode GetMode() const
	{
		return m_eMode;
	}

	void SetMode(TRenderContext::CameraMode a_eMode)
	{
		m_eMode = a_eMode;
	}

	TBOOL IsEnabled() const
	{
		return m_bEnabled;
	}

	TTransformObject &GetTransformObject()
	{
		return m_TransformObject;
	}

private:
	TFLOAT                     m_fNear;
	TFLOAT                     m_fFar;
	TFLOAT                     m_fFOV;
	TINT                       m_Unk1;
	TRenderContext::CameraMode m_eMode;
	TFLOAT                     m_fCentreX;
	TFLOAT                     m_fCentreY;
	TTransformObject           m_TransformObject;
	TBOOL                      m_bEnabled;
};

TOSHI_NAMESPACE_END
