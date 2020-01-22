#include <MinHook.h>
#include "hooks/hooks.h"

DWORD __stdcall thread( LPVOID )
{
	AllocConsole();
	FILE* f_ptr = nullptr;
	freopen_s( &f_ptr, "CONOUT$", "w", stdout );
	SetConsoleTitle( TEXT( "Lazysight" ) );

	const auto base = reinterpret_cast< uintptr_t >( GetModuleHandleA( nullptr ) );

	// g_render A1 ? ? ? ? 8B 88 ? ? ? ? 8B 46 1C 8B 56 0C 8B 78 54 
	auto g_render = 0;

	while ( !( g_render = *reinterpret_cast< uintptr_t* >( base + 0xA89198 ) ) )
		Sleep( 200 );

	const auto p_device = **reinterpret_cast< uintptr_t*** >( g_render + 0x20 );

	const auto present = p_device[17];

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

bool __stdcall DllMain( HINSTANCE, DWORD reason, LPVOID )
{
	if ( reason == DLL_PROCESS_ATTACH )
		CreateThread( nullptr, 0, thread, nullptr, 0, nullptr );

	return true;
}