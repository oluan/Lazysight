#pragma once

#include <Windows.h>
#include <vector>

namespace helpers
{
	bool      is_address_readable     ( const uintptr_t address );
	bool      is_address_writable     ( const uintptr_t address );
	uintptr_t read_multilevel_pointer ( const uintptr_t base, const std::vector< uintptr_t >& offsets );
	uintptr_t find_pattern            ( const uintptr_t base, const size_t size, const char* pattern, const char* mask );
	uintptr_t find_pattern_module     ( const char* module_name, const char* pattern, const char* mask );
	uintptr_t get_module_export       ( const char* module_name, const char* export_name );
	void      patch                   ( void* dest, const void* src, size_t size );
};