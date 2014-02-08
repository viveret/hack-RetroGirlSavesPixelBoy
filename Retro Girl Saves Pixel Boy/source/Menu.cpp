#include "Menu.h"	 

#include <S_Engine\S_Engine.h>
extern S_Engine Engine;

#include "Resources.h"
#include "Game.h"

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
		Engine.Make_Game( new RGSPB_Game::nnGame ); 

		E_Events::Event_Base* nEvent = new E_Events::Event_Base;
		nEvent->Type = E_Events::Event_Types::TYPE_MENU;
		nEvent->Code = E_Events::Events::EVENT_ENTER;	
		Engine.Event_Manager.Add_Event( nEvent, "Enter Game Event" );

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