#ifndef RGSPB_MAP_CODE
#define RGSPB_MAP_CODE

#include "Game.h"

/*
	Place to store specific level triggers,
	like changing tiles / starting convs
*/

namespace Map_0_Stuff
{
	struct Map_0_Data:public RGSPB_Game::Game_Map_Local_Data
	{			
		void Initialize();
		void Cleanup();

		void Add_To_Game();
											
		RGSPB_Conv::Conv_Full Oldman_Conv;
		RGSPB_Conv::Conv_Full Self_Conv;
	};

	struct Event_Flip_Sword_Barrier:public RGSPB_Events::Event_Base
	{	
		void Do_Event();
	};

	struct Event_Get_Sword:public RGSPB_Events::Event_Base
	{
		void Do_Event();
	};
}


namespace Map_1_Stuff
{
	struct Map_1_Data:public RGSPB_Game::Game_Map_Local_Data
	{			
		void Initialize();
		void Cleanup();

		void Add_To_Game();

						
		RGSPB_Conv::Conv_Full Oldman_Conv;
	};

							
	struct Event_Vert_Bridge:public RGSPB_Events::Event_Base
	{
		void Do_Event();
	};
	
	struct Event_Hors_Bridge:public RGSPB_Events::Event_Base
	{
		void Do_Event();
	};
	
	struct Event_Got_Hors_Conv:public RGSPB_Events::Event_Base
	{
		void Do_Event();
	};
}



namespace Map_2_Stuff
{
	struct Map_2_Data:public RGSPB_Game::Game_Map_Local_Data
	{			
		void Initialize();
		void Cleanup();

		void Add_To_Game();

						
		RGSPB_Conv::Conv_Full Final_Conv;
	};
}


#endif