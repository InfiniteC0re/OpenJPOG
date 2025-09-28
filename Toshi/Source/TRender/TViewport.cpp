#include "TViewport.h"
#include "TRender/TRenderInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include <TKernel/TMemoryDebugOn.h>

TOSHI_NAMESPACE_USING

IMPLEMENT_DYNCREATE(TViewport, TSceneObject)

TBOOL TViewport::Create(TBOOL a_bConnectToRenderer)
{
	m_pRenderContext = GetRenderer()->CreateRenderContext();
	SetWidth(-1.0f);
	SetHeight(-1.0f);
	if (a_bConnectToRenderer) {
		GetRenderer()->ConnectDefaultViewportHandlers(*this);
	}
	return TResource::Create();
}

TBOOL TViewport::Update(TScene &a_rScene)
{
	if (m_bIsEnabled) {
		if (GetRenderer()) {
			if (GetWidth() < 0.0f) {
				TFLOAT width = static_cast<TFLOAT>(GetRenderer()->GetCurrentDevice()->GetMode()->GetWidth());
				if (width < 0.0f) {
					width += 0.0f; // Why??
				}
				SetWidth(width);
			}
			if (GetHeight() < 0.0f) {
				TFLOAT height = static_cast<TFLOAT>(GetRenderer()->GetCurrentDevice()->GetMode()->GetHeight());
				if (height < 0.0f) {
					height += 0.0f; // Why??
				}
				SetHeight(height);
			}
		}
		m_oBeginUpdateEmitter.Throw(TNULL);
		m_oUpdateEmitter.Throw(TNULL);
		m_oEndUpdateEmitter.Throw(TNULL);
	}
	return TSceneObject::Update(a_rScene);
}

TBOOL TViewport::Render(TScene &a_rScene)
{
	if (m_bIsEnabled) {
		if (GetRenderer()) {
			if (GetWidth() < 0.0f) {
				TFLOAT width = static_cast<TFLOAT>(GetRenderer()->GetCurrentDevice()->GetMode()->GetWidth());
				if (width < 0.0f) {
					width += 0.0f; // Why??
				}
				SetWidth(width);
			}
			if (GetHeight() < 0.0f) {
				TFLOAT height = static_cast<TFLOAT>(GetRenderer()->GetCurrentDevice()->GetMode()->GetHeight());
				if (height < 0.0f) {
					height += 0.0f; // Why??
				}
				SetHeight(height);
			}
		}
		TRenderContext *pPrevRenderContext = GetRenderer()->GetCurrentRenderContext();
		GetRenderer()->SetCurrentRenderContext(m_pRenderContext);
		TIMPLEMENT("m_pRenderContext->m_vAmbientColour = m_vAmbientColour");
		m_oBeginRenderEmitter.Throw(TNULL);
		//TASSERT(GetRenderContext()->Get)
		TIMPLEMENT("ClipFlags validation");
		m_oRenderEmitter.Throw(TNULL);
		TIMPLEMENT("ClipFlags validation");
		m_oEndRenderEmitter.Throw(TNULL);
		GetRenderer()->SetCurrentRenderContext(pPrevRenderContext);
	}
	return TSceneObject::Render(a_rScene);
}
