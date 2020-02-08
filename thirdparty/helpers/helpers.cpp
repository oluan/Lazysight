#include "helpers.hpp"
#include <Psapi.h>

#define MEMORY_READABLE	  ( PAGE_READONLY  | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE )
#define MEMORY_WRITABLE	  ( PAGE_READWRITE | PAGE_EXECUTE_READWRITE )
#define MEMORY_EXECUTABLE ( PAGE_EXECUTE   | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE )

bool bdata_compare( const char* pData, const char* pattern, const char* mask )
{
	for ( ; *mask; ++mask, ++pData, ++pattern )
	{
		if ( *mask == 'x' && *pData != *pattern )
			return false;
	}

	return !*mask;
}

uintptr_t find_pattern_buffer( const uintptr_t base, const size_t size, const char* pattern, const char* mask )
{
	for ( size_t i = 0; i < size; ++i )
		if ( bdata_compare( reinterpret_cast< const char* >( base + i ), pattern, mask ) )
			return base + i;

	return 0;
}

bool helpers::is_address_readable( const uintptr_t address )
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };

	if ( !VirtualQuery( reinterpret_cast< const void* >( address ), &mbi, sizeof( mbi ) ) )
		return false;

	return ( mbi.State == MEM_COMMIT ) && ( mbi.Protect & MEMORY_READABLE ) && !( mbi.Protect & ( PAGE_NOACCESS | PAGE_GUARD ) );
}

bool helpers::is_address_writable( const uintptr_t address )
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };

	if ( !VirtualQuery( reinterpret_cast< const void* >( address ), &mbi, sizeof( mbi ) ) )
		return false;

	return ( mbi.State == MEM_COMMIT ) && ( mbi.Protect & MEMORY_WRITABLE ) && !( mbi.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) );
}

uintptr_t helpers::read_multilevel_pointer( const uintptr_t base, const std::vector< uintptr_t >& offsets )
{
	if ( !is_address_readable( base ) || !offsets.size() )
		return 0;

	auto address      = *reinterpret_cast< uintptr_t* >( base );
	auto offset_count = offsets.size();

	for ( size_t i = 0; i < offset_count - 1; ++i )
	{
		if ( !is_address_readable( address ) )
			return 0;

		address = *reinterpret_cast< uintptr_t* >( address + offsets.at( i ) );
	}

	return address ? address + offsets.at( offset_count - 1 ) : 0;
}

uintptr_t helpers::find_pattern( const uintptr_t base, const size_t size, const char* pattern, const char* mask )
{
	if ( !size || !pattern || !mask )
		return 0;

	auto address = base;

	MEMORY_BASIC_INFORMATION mbi = { 0 };

	while ( address < base + size )
	{
		if ( !VirtualQuery( reinterpret_cast< const void* >( address ), &mbi, sizeof( mbi ) ) )
			return 0;

		if ( ( mbi.State == MEM_COMMIT ) && !( mbi.Protect & ( PAGE_NOACCESS | PAGE_GUARD ) ) )
		{
			auto result = find_pattern_buffer( reinterpret_cast< const uintptr_t >( mbi.BaseAddress ), mbi.RegionSize, pattern, mask );

			if ( result )
				return result;
		}

		address += mbi.RegionSize;
	}

	return 0;
}

uintptr_t helpers::find_pattern_module( const char* module_name, const char* pattern, const char* mask )
{
	auto hmodule = GetModuleHandleA( module_name );

	if ( !hmodule )
		return 0;

	MODULEINFO module_info = { 0 };

	auto success = GetModuleInformation( GetCurrentProcess(), hmodule, &module_info, sizeof( module_info ) );

	return success ? find_pattern( reinterpret_cast< uintptr_t >( module_info.lpBaseOfDll ), module_info.SizeOfImage, pattern, mask ) : 0;
}

uintptr_t helpers::get_module_export( const char* module_name, const char* export_name )
{
	if ( !module_name || !export_name )
		return 0;

	auto module_base = reinterpret_cast< uintptr_t >( GetModuleHandleA( module_name ) );

	if ( !module_base )
		return 0;

	auto pimage_dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module_base );

	if ( pimage_dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return 0;

	auto pimage_nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( module_base + pimage_dos_header->e_lfanew );

	if ( pimage_nt_headers->Signature != IMAGE_NT_SIGNATURE )
		return 0;

	auto export_directory_rva = pimage_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if ( !export_directory_rva )
		return 0;

	auto pimage_export_directory = reinterpret_cast< PIMAGE_EXPORT_DIRECTORY >( module_base + export_directory_rva );

	auto peat = reinterpret_cast< PDWORD >( module_base + pimage_export_directory->AddressOfFunctions );
	auto pent = reinterpret_cast< PDWORD >( module_base + pimage_export_directory->AddressOfNames );
	auto peot = reinterpret_cast< PWORD >( module_base + pimage_export_directory->AddressOfNameOrdinals );

	unsigned short ordinal = 0;

	for ( DWORD i = 0; i < pimage_export_directory->NumberOfNames; ++i )
	{
		if ( !lstrcmpiA( export_name, reinterpret_cast< const char* >( module_base + pent[i] ) ) )
		{
			ordinal = peot[i];
			break;
		}
	}

	return ordinal ? module_base + peat[ordinal] : 0;
}

void helpers::patch( void* dest, const void* src, size_t size )
{
	DWORD old_protection = 0;

	if ( !VirtualProtect( dest, size, PAGE_EXECUTE_READWRITE, &old_protection ) )
		return;

	memcpy( dest, src, size );

	VirtualProtect( dest, size, old_protection, &old_protection );
}