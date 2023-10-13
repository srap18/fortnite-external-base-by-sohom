#pragma once
#ifndef DRIVER
#define DRIVER

#include "driver.hpp"

auto driver::comms::read_virtual(const std::uintptr_t address, void* buffer, const std::size_t size) -> bool
{
	return 0;
}

#endif