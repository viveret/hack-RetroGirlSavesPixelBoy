#include "RGSPB_Core.hpp"

#include "Resources.h"
#include "Game.h"

#define MENU_COLOR 64/255.f

#ifdef _DEPRECATED

void E_Menu::Menu_Manager::Draw()
{
	glClearColor( MENU_COLOR, MENU_COLOR, MENU_COLOR, 1 );
	this->Draw_Base();
																											 
	Draw_Utility::String_Draw( "RETRO GIRL SAVES PIXEL BOY", ScreenW/2.f, 100, 1,1,1,1,STR_POS_MID, 4.f );
	Draw_Utility::String_Draw( "Or so she thought...", ScreenW/2.f, 150, 1,1,1,1,STR_POS_MID, 2.f );

	
	Draw_Utility::String_Draw( ((nnRes*)Engine.Resources.Stuff)->Test_Stream, 0, 0, 1,1,1,1 );
}
	
E_Menu::Menu_Base* E_Menu::Menu_Manager::Load_Menu_Internal( std::string Which )
{						 
	if( Which == "title" )
	{
		E_Menu::Menu_Base* nMenu = new E_Menu::Menu_Base;

		nMenu->Title = "RETRO GIRL SAVES PIXEL BOY";

		nMenu->Make_Buttons(2);
																							  
		nMenu->Buttons[0] = new Menu_Buttons::Button_Menu("Singleplayer","single-play",-200,-100);
		nMenu->Buttons[1] = new Menu_Buttons::Button_Menu("Quit","quit",-200,92);
			
		Engine.Mem_Add( nMenu->Buttons[0], "button" );
		Engine.Mem_Add( nMenu->Buttons[1], "button" );
			
		return nMenu;
	}
	else if( Which == "single-play" )
	{
		RGSPB_Game_Lib::Start_Game();
		return NULL;
	}
	else
		return (E_Menu::Menu_Base*)(-1);

	return (E_Menu::Menu_Base*)(-1);
}	
	
std::string E_Menu::Menu_Manager::Menu_Int_TO_String( u_int Which )
{
	return "lol";
}
	
u_int E_Menu::Menu_Manager::Menu_String_TO_Int( std::string Which )
{
	return 0;
}

#endif
