#pragma once
#include "TDebug.h"

TOSHI_NAMESPACE_BEGIN

template<class T>
class TOSHI_EXPORT TManagedPointer
{
public:
    TManagedPointer() : m_pObject(new T())
    {

    }

    TManagedPointer(T* a_pObject) : m_pObject(a_pObject)
    {

    }

    ~TManagedPointer() 
    { 
        delete m_pObject; 
    }

    T& operator*() { TASSERT(m_pObject != TNULL); return *m_pObject; }

    operator T* () { TASSERT(m_pObject!=TNULL); return m_pObject; }

    T* operator->() { TASSERT(m_pObject != TNULL); return m_pObject; }

private:
	T* m_pObject;
};

TOSHI_NAMESPACE_END