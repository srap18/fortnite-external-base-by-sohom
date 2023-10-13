#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../../../includes.hpp"
#include "overlay/render.hpp"
#include "../aimbot/movement/controller.hpp"
#include "../aimbot/function.hpp"
#include "sdk/decrypt.hpp"
#include <string>

namespace cach
{
	class c
	{
	public:
		uintptr_t
			gworld,
			gameinstance,
			localplayers,
			playercontroller,
			acknowledgedpawn,
			entityarray,
			persistentlevel,
			playerstate,
			currentweapon,
			mesh,
			rootcomp;
		int
			entitycount;

		Vector3
			relativelocation;

		char
			teamid;
	};
}

static cach::c* cached = new cach::c();

namespace loop
{
	class entity
	{
	public:

		__forceinline auto cache() -> void
		{
		
		}

		__forceinline auto loop() -> void
		{
				
		}
	};
}

static loop::entity* entity = new loop::entity();

#endif