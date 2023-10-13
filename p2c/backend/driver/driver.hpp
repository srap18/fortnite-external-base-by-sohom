#pragma once
#ifndef DRIVERH
#define DRIVERH

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdio.h>
#include <string_view>
#include <iostream>
#include <chrono>

namespace driver
{
	class comms
	{
	public:

		[[nodiscard]] bool read_virtual(const uintptr_t address, void* buffer, const size_t size);

		template <typename t>
		[[nodiscard]] auto read(const uintptr_t address) -> t
		{
			t response{};
			this->read_virtual(address, &response, sizeof(t));
			return response;
		}
		template <typename t>
		[[nodiscard]] auto read_array(const uintptr_t address, t buffer, size_t size) -> bool
		{
			return this->read_virtual(address, buffer, size);
		}
	};
}

static driver::comms* ioctl = new driver::comms();


#endif 
