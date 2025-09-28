#pragma once
#include "Defines.h"
#include "TRender/TRenderContext.h"
#include "TRenderD3D/TRenderD3DInterface.h"

TOSHI_NAMESPACE_BEGIN

class TRENDERINTERFACED3D_EXPORTS TRenderContextD3D : public TRenderContext
{
public:

	TRenderContextD3D(TRenderD3DInterface &a_rRenderer)
		: TRenderContext(a_rRenderer)
	{
	}

	virtual void Update() override;

	void ComputeOrthographicProjection();
	void ComputeOrthographicFrustum();

	void ComputePerspectiveProjection();
	void ComputePerspectiveFrustum();

	TRenderD3DInterface &GetRenderer()
	{
		return *static_cast<TRenderD3DInterface *>(m_pRenderInterface);
	}

	const TMatrix44 &GetViewProjectionMatrix()
	{
		return m_oViewProjection;
	}

private:
	void SetRenderMatrices()
	{
		GetRenderer().GetD3DDevice()->SetTransform(D3DTS_VIEW, TREINTERPRETCAST(const D3DMATRIX *, &TMatrix44::IDENTITY));
		GetRenderer().GetD3DDevice()->SetTransform(D3DTS_PROJECTION, TREINTERPRETCAST(D3DMATRIX *, &m_oViewProjection));
	}

	TMatrix44 m_oViewProjection; // 0x484
};

TOSHI_NAMESPACE_END
