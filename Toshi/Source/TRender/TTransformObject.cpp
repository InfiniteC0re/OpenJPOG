#include "TTransformObject.h"
#include "TRenderInterface.h"

//-----------------------------------------------------------------------------
// Enables memory debugging.
// Note: Should be the last include!
//-----------------------------------------------------------------------------
#include "TKernel/TMemoryDebugOn.h"

TOSHI_NAMESPACE_BEGIN

TTransformObject::TTransformObject()
{
	SetEulerOrder(2, 1, 0);
	SetMode(MODE_QUAT);
	SetQuat(TQuaternion());
	SetTranslate(TVector3::VEC_ZERO);
}

TTransformObject::~TTransformObject()
{
}

void TTransformObject::Push()
{
	TIMPLEMENT();
}

void TTransformObject::Pop()
{
	TIMPLEMENT();
}

Toshi::TVector3 &TTransformObject::GetTranslation()
{
	TIMPLEMENT();
	return (TVector3 &)TVector3::VEC_ZERO;
}

void TTransformObject::GetLocalMatrixImp(TMatrix44 &outMatrix)
{
	TIMPLEMENT();
}

void TTransformObject::SetEuler(const TVector3 &a_rEuler)
{
	TIMPLEMENT();
}

void TTransformObject::SetEulerOrder(TUINT8 x, TUINT8 y, TUINT8 z)
{
	TIMPLEMENT();
}

void TTransformObject::SetTranslate(const TVector3 &a_rTranslation)
{
	TIMPLEMENT();
}

void TTransformObject::SetQuat(const TQuaternion &quaternion)
{
	TIMPLEMENT();
}

void TTransformObject::SetMatrix(const TMatrix44 &matrix)
{
	TIMPLEMENT();
}

TOSHI_NAMESPACE_END
