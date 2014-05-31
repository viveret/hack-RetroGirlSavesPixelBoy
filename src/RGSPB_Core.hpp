#ifndef RGSBP_CORE
#define RGSPB_CORE


#include <SE/debug/Logger.hpp>
#include <SE/utility/Lua.hpp>
#include <SE/Window.hpp>
#include <SE/filesys/Filesystem.hpp>
#include <SE/gl/segl.hpp>


namespace RGSPB_Core
{
	extern SE_Scheduler_Interface* SE_Scheduler;
	extern SE_Log_Interface* seLog;
	extern SE_Lua_Interface* SE_Lua;
	extern SE_Window_Interface* SE_Window;
	extern SE_Filesys_Interface* SE_Filesys;
	extern segl_Interface* segl;
}
using namespace RGSPB_Core;


#endif
