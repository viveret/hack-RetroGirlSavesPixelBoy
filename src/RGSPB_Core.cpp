#include "RGSPB_Core.hpp"

#include <SE/Core.hpp>
#include <SE/module/Plugin.hpp>


namespace RGSPB_Core
{
	void* Module_Interface( const char* );
	uint Register_Module( const char* );
	void Create_Interface();

	SE_Scheduler_Interface* SE_Scheduler = NULL;
	SE_Log_Interface* seLog = NULL;
	SE_Lua_Interface* SE_Lua = NULL;
	SE_Window_Interface* SE_Window = NULL;
	SE_Filesys_Interface* SE_Filesys = NULL;
	segl_Interface* segl = NULL;
}
using namespace RGSPB_Core;

// Modules
#include "Map.hpp"


/*******************   MODULE OPERATIONS   ********************/
uint RGSPB_Core::Register_Module( const char* )
{
	SE_Scheduler = (SE_Scheduler_Interface*) SE_Mod_Plugin::Get_Plugin( "scheduler", SE_SCHEDULER_HEADER_VER );

/*	Mod_GUI = S_Engine::Generate_Module( "gui", "gui" );
	S_Engine::Register_Module_Engine( Mod_GUI, S_Engine::Reg_Mod_Time::MED_LEVEL, Initialize, Cleanup );
	S_Engine::Register_Module_Render( Mod_GUI, S_Engine::Reg_Mod_Time::MED_LEVEL, Get_Resources, NULL );
	SE_Scheduler->Insert_Pos( seSchedule_Render(), RGSPB_Core::Thread_Render, S_Engine::Module_Positions::POS_MED + 32, 100 );
	SE_Scheduler->Insert_Pos( seSchedule_Update(), RGSPB_Core::Thread_Update, S_Engine::Module_Positions::POS_END, 32 );
	S_Engine::Register_Module_Event_Engine( Mod_GUI, Event_Menu );
*/
	seLog = (SE_Log_Interface*) SE_Mod_Plugin::Get_Plugin( "log", SE_LOG_HEADER_VER );
	SE_Window = (SE_Window_Interface*) SE_Mod_Plugin::Get_Plugin( "window", SE_WINDOW_HEADER_VER );
	segl = (segl_Interface*) SE_Mod_Plugin::Get_Plugin( "segl", SEGL_HEADER_VER );
	SE_Filesys = (SE_Filesys_Interface*) SE_Mod_Plugin::Get_Plugin( "filesys", SE_FILESYS_HEADER_VER );
	SE_Lua = (SE_Lua_Interface*) SE_Mod_Plugin::Get_Plugin( "lua", SE_LUA_HEADER_VER );


	RGSPB_Map_Lib::Register_Module();


	return SE_SUCCESS;
}


void RGSPB_Core::Create_Interface()
{
/*	SE_GUI = new SE_GUI_Interface;

	memset( SE_GUI, 0, sizeof(SE_GUI_Interface) );*/
}

void* RGSPB_Core::Module_Interface( const char* )
{
	return NULL;
}


extern "C" {

DLL_EXPORT SE_Mod_Plugin_Interface SE_Plugin_Data = {
		__DATE__ ", " __TIME__,
		"rgspb",
		"Retro Girl Saves Pixel Boy",
		RGSPB_Core::Create_Interface,
		RGSPB_Core::Register_Module,
		RGSPB_Core::Module_Interface
};

DLL_EXPORT void* SE_Plugin()
{
	return &SE_Plugin_Data;
}

} // extern "C"
