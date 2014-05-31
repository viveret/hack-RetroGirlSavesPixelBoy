#ifndef RGSPB_GAME
#define RGSPB_GAME

#include "Physics.h"
#include "Items.h"
#include <SE/gui/GUI.hpp>


//= (SE_GUI_Lib::Widget_Container*) SE_GUI->Generate_Widget( "menu", NULL );
 


namespace RGSPB_Game_Lib
{
	void Start_Game();
//	void Add_Body_Props( btRigidBody* Body );

	void Get_Map( uint ID );
	void Load_Map( std::string File );
	void Write_Map( std::string File );

	void Register_Module();
}


#endif
