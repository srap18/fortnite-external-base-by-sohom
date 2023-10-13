#pragma once
#ifndef DRAW
#define DRAW

#include "../../../../includes.hpp"

namespace v
{
	class draw
	{
	public:

		__forceinline auto skeleton(uintptr_t Mesh) -> bool
		{
			
		}

		__forceinline auto twodbox(uintptr_t Mesh) -> void
		{
	
		}

		__forceinline auto text(ImFont* Font, ImVec2 pos, ImU32 color, const char* text) -> void
		{
		
		}
	};
}
static v::draw* draw = new v::draw();

#endif