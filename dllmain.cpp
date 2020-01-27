#include <MinHook.h>
#include "thirdparty/helpers/helpers.hpp"
#include "hooks/hooks.h"

uintptr_t ironsight_base = 0;

using f_RtlInsertInvertedFunctionTable = VOID( __fastcall* )( PVOID ImageBase, ULONG SizeOfImage );

DWORD __stdcall thread( LPVOID lparam )
{
	AllocConsole();
	FILE* f_ptr = nullptr;
	freopen_s( &f_ptr, "CONOUT$", "w", stdout );
	SetConsoleTitle( TEXT( "Lazysight" ) );

	ironsight_base = reinterpret_cast< uintptr_t >( GetModuleHandle( nullptr ) );

	const auto RtlInsertInvertedFunctionTable = reinterpret_cast< f_RtlInsertInvertedFunctionTable >( helpers::find_pattern_module( "ntdll.dll",
		"\x8B\xFF\x55\x8B\xEC\x83\xEC\x0C\x53\x56\x57\x8D\x45\xF8\x8B\xFA", "xxxxxxxxxxxxxxxx" ) );

	if ( RtlInsertInvertedFunctionTable )
	{
		const auto image_base        = reinterpret_cast< uintptr_t >( lparam );
		const auto pimage_dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( image_base );
		const auto pimage_nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( image_base + pimage_dos_header->e_lfanew );

		RtlInsertInvertedFunctionTable( lparam, pimage_nt_headers->OptionalHeader.SizeOfImage );

		printf( "[+] Exception handlers - OK" );
	}

	// g_render A1 ? ? ? ? 8B 88 ? ? ? ? 8B 46 1C 8B 56 0C 8B 78 54 
	auto g_render = 0;

	while ( !( g_render = *reinterpret_cast< uintptr_t* >( ironsight_base + 0xA89198 ) ) )
		Sleep( 200 );

	const auto p_device = **reinterpret_cast< uintptr_t*** >( g_render + 0x20 );
	const auto present  = p_device[17];

	if ( MH_Initialize() != MH_OK )
	{
		printf( "[Lazysight] Failed to init MinHook\n" );
		return 0;
	}

	if ( MH_CreateHook( reinterpret_cast< LPVOID >( present ) , &hk_present , reinterpret_cast< LPVOID* >( &o_present ) ) != MH_OK )
	{
		printf( "[Lazysight] Failed to create hook at Present\n" );
		return 0;
	}

	if ( MH_EnableHook( MH_ALL_HOOKS ) )
	{
		printf( "[Lazysight] Failed to enable hook(s)\n" );
		return 0;
	}

	return 1;
}

bool __stdcall DllMain( HINSTANCE hinstance, DWORD reason, LPVOID )
{
	if ( reason == DLL_PROCESS_ATTACH )
	{
		auto hthread = CreateThread( nullptr, 0, thread, hinstance, 0, nullptr );

		if ( hthread )
			CloseHandle( hthread );
	}

	return true;
}