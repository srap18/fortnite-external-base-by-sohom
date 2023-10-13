#pragma once
#ifndef DECRYPT
#define DECRYPT

#include "../../../../includes.hpp"
#include "hexray.hpp"

namespace cach
{
	class decrypt
	{
	public:

		uintptr_t
			pname,
			weapondata,
			displayname,
			weaponlength;

		wchar_t*
			weaponname;
	};
}

static cach::decrypt* decryptcached = new cach::decrypt();

namespace unrealenginedecryption
{
	class decrypt
	{
	public:

		__forceinline std::string platform()
		{
		
		}

		__forceinline std::string username() 
		{
			
		}

		__forceinline std::string weapon() 
		{
			
		}

		__forceinline auto reloading() -> bool
		{
			
		}

		__forceinline auto ammocount() -> int
		{
	
		}
	};
}
static unrealenginedecryption::decrypt* decrypt = new unrealenginedecryption::decrypt();
#endif 