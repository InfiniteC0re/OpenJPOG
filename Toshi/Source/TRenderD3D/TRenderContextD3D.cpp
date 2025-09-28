#include "TRenderD3D/TRenderContextD3D.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_BEGIN

void TRenderContextD3D::Update()
{
	if (IsDirty()) {
		if (m_eProjType == PROJTYPE_PERSPECTIVE) {
			ComputePerspectiveProjection();
			ComputePerspectiveFrustum();
		}
		else {
			ComputeOrthographicProjection();
			ComputeOrthographicFrustum();
		}
	}
	SetRenderMatrices();
}

void TRenderContextD3D::ComputeOrthographicProjection()
{
	PROJECTIONPARAMS oProjectionParams = GetProjectionParameters();
	VIEWPORTPARAMS   oViewportParams   = GetViewportParameters();
	m_oViewProjection.m_f11           = (oProjectionParams.m_oProj(0) * 2.0f) / oViewportParams.fWidth;
	m_oViewProjection.m_f12           = 0.0f;
	m_oViewProjection.m_f13           = 0.0f;
	m_oViewProjection.m_f14           = 0.0f;
	m_oViewProjection.m_f21           = 0.0f;
	m_oViewProjection.m_f22           = -((oProjectionParams.m_oProj(1) * 2.0f) / oViewportParams.fHeight);
	m_oViewProjection.m_f23           = 0.0f;
	m_oViewProjection.m_f24           = 0.0f;
	m_oViewProjection.m_f31           = 0.0f;
	m_oViewProjection.m_f32           = 0.0f;
	m_oViewProjection.m_f33           = 1.0f / (oProjectionParams.m_fFarClip - oProjectionParams.m_fNearClip);
	m_oViewProjection.m_f34           = 0.0f;
	m_oViewProjection.m_f41           = (oProjectionParams.m_oCentre(0) * 2.0f) / oViewportParams.fWidth - 1.0f;
	m_oViewProjection.m_f42           = -((oProjectionParams.m_oCentre(1) * 2.0f) / oViewportParams.fHeight - 1.0f);
	m_oViewProjection.m_f43           = -(oProjectionParams.m_fNearClip / (oProjectionParams.m_fFarClip - oProjectionParams.m_fNearClip));
	m_oViewProjection.m_f44           = 1.0f;
}

void TRenderContextD3D::ComputeOrthographicFrustum()
{
	TIMPLEMENT();
}

void TRenderContextD3D::ComputePerspectiveProjection()
{
	PROJECTIONPARAMS oProjectionParams = GetProjectionParameters();
	VIEWPORTPARAMS   oViewportParams   = GetViewportParameters();
	m_oViewProjection.m_f11           = (oProjectionParams.m_oProj(0) * 2.0f) / oViewportParams.fWidth;
	m_oViewProjection.m_f12           = 0.0f;
	m_oViewProjection.m_f13           = 0.0f;
	m_oViewProjection.m_f14           = 0.0f;
	m_oViewProjection.m_f21           = 0.0f;
	m_oViewProjection.m_f22           = -((oProjectionParams.m_oProj(1) * 2.0f) / oViewportParams.fHeight);
	m_oViewProjection.m_f23           = 0.0f;
	m_oViewProjection.m_f24           = 0.0f;
	m_oViewProjection.m_f31           = (oProjectionParams.m_oCentre(0) * 2.0f) / oViewportParams.fWidth - 1.0f;
	m_oViewProjection.m_f32           = -((oProjectionParams.m_oCentre(1) * 2.0f) / oViewportParams.fHeight - 1.0f);
	m_oViewProjection.m_f33           = oProjectionParams.m_fFarClip / (oProjectionParams.m_fFarClip - oProjectionParams.m_fNearClip);
	m_oViewProjection.m_f34           = 1.0f;
	m_oViewProjection.m_f41           = 0.0f;
	m_oViewProjection.m_f42           = 0.0f;
	m_oViewProjection.m_f43           = -((oProjectionParams.m_fNearClip * oProjectionParams.m_fFarClip) / (oProjectionParams.m_fFarClip - oProjectionParams.m_fNearClip));
	m_oViewProjection.m_f44           = 0.0f;
}

void TRenderContextD3D::ComputePerspectiveFrustum()
{
	PROJECTIONPARAMS oProjectionParams = GetProjectionParameters();
	TFLOAT           fVal1             = 1.0f / oProjectionParams.m_oProj(0);
	TIMPLEMENT();
}

TOSHI_NAMESPACE_END