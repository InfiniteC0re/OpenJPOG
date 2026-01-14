#pragma once
#include <Toshi/Defines.h>

#include <Windows.h>

namespace Interface
{

inline static TUINT TApplication     = TREINTERPRETCAST(TUINT, GetModuleHandleA("TApplication.dll"));
inline static TUINT TRenderInterface = TREINTERPRETCAST(TUINT, GetModuleHandleA("TRenderInterface.dll"));

} // namespace Interface
