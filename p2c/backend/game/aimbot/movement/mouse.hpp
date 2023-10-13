#pragma once
#include <wtypes.h>
#include "../../../../frontend/protection/encryption/string/xor.hpp"

namespace Mouse
{
	static BYTE NtUserInjectMouseInput_Bytes[30];

	static BOOLEAN WINAPI Init()
	{
;
	}

	static BOOLEAN WINAPI NtInjectMouse(int X, int Y)
	{

	}
}