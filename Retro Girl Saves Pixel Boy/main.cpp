#include <process.h>

#define SE_INCLUDE_LIBS
#include <S_Engine\S_Engine.h>

#ifdef _DEBUG
#pragma comment (lib, "Survivor_Engine_Debug.lib")
#else			
#pragma comment (lib, "Survivor_Engine.lib")
#endif

S_Engine Engine;


#include "source\App.h"
#include "source\Resources.h"
#include "source\Menu.h"

void S_Engine::Handle_Logic_Event_Ex( E_Events::Event_Base* Event )
{
	//
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{			 
	Engine.Menu.Splash_R = MENU_COLOR;
	Engine.Menu.Splash_G = MENU_COLOR;
	Engine.Menu.Splash_B = MENU_COLOR;

	Engine_Descriptor E_Desc = { 
		"Retro Girl Saves Pixel Boy",
		hInstance,
		new RGSPB_App::nnKeys, new nnRes,
		"adventure.ttf", 32,
		"ingame_pause"
	};
																   
	Engine.Start( E_Desc );	  
	Engine.Menu.Load_Menu( "title" );// start there

    MSG msg;

	while(Engine.Is_Running)
    {
		while (PeekMessage(&msg,Engine.Application.Window.hWnd,0,0,PM_REMOVE)>0)
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
		Engine.Main_Loop();
    } 

	Engine.Exit();

    return 0;
}