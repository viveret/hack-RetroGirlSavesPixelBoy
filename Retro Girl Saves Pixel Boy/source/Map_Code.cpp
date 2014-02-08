#include "Map_Code.h"

#include <S_Engine\S_Engine.h>
extern S_Engine Engine;

#include "Game.h"
#include "Resources.h"


/*    MAP 0   */			  
#define M_0_LOC ((Map_0_Stuff::Map_0_Data*)mGame->M_Local)

void Map_0_Stuff::Event_Flip_Sword_Barrier::Do_Event()
{
	if( this->Arg )// true
		mGame->m_Map.Set_Box(13, 8, 1, 2, 1, 0);
	else//false									
		mGame->m_Map.Set_Box(13, 8, 1, 2, 1, 44);
}

void Map_0_Stuff::Event_Get_Sword::Do_Event()
{
	M_0_LOC->Oldman_Conv = mGame->Conversation.Load_Conv( "stuff/conv/welcome_pt2.txt" );
	
																		
	RGSPB_Phys::Obj_Trigger* nTrig = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig );

	nTrig->Pos.Set( 15,5 );
	nTrig->Radius = 1.f;
	nTrig->Plr_Only = true;

	nTrig->Event = new RGSPB_Events::Event_Conv;
	((RGSPB_Events::Event_Conv*)nTrig->Event)->Convs = M_0_LOC->Oldman_Conv;
}

void Map_0_Stuff::Map_0_Data::Initialize()
{				 																   
	this->Oldman_Conv = mGame->Conversation.Load_Conv( "stuff/conv/welcome.txt" );
	this->Self_Conv = mGame->Conversation.Load_Conv( "stuff/conv/self_thought.txt" );
}

void Map_0_Stuff::Map_0_Data::Cleanup()
{

}

void Map_0_Stuff::Map_0_Data::Add_To_Game()
{									
	RGSPB_Phys::Obj_Trigger* nTrig_Self = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig_Self );

	nTrig_Self->Pos.Set( 21,10 );
	nTrig_Self->Radius = 1.f;
	nTrig_Self->Plr_Only = true;

	nTrig_Self->Event = new RGSPB_Events::Event_Conv;
	((RGSPB_Events::Event_Conv*)nTrig_Self->Event)->Convs = M_0_LOC->Self_Conv;






	RGSPB_Items::Obj_Item* Test_Item = new RGSPB_Items::Obj_Item;
	mGame->Physics.Add( Test_Item );
	Test_Item->Pos.Set( 4, 3 );
	Test_Item->Tex = mRes->Sword;
	Test_Item->m_Item.Tex = mRes->Sword;
	Test_Item->m_Item.Type = RGSPB_Items::Item_Base::TYPE_MELLE;
	Test_Item->m_Item.Name = "Sharp Sword";


	RGSPB_Game::AI_Base* Old_Man = new RGSPB_Game::AI_Base;
	mGame->Physics.Add( Old_Man );

	Old_Man->Pos.Set( 15, 5 );
	Old_Man->Tex = mRes->Old_Man;
	Old_Man->Draw_Size.y = 1.f;
	Old_Man->Draw_Pos.y = -0.5f;



	
																		
	RGSPB_Phys::Obj_Trigger* nTrig = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig );

	nTrig->Pos.Set( 15,5 );
	nTrig->Radius = 1.f;
	nTrig->Plr_Only = true;

	nTrig->Event = new RGSPB_Events::Event_Conv;
	((RGSPB_Events::Event_Conv*)nTrig->Event)->Convs = M_0_LOC->Oldman_Conv;



	
	RGSPB_Phys::Obj_Trigger* nSwitch = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nSwitch );

	nSwitch->Pos.Set( 23,4 );
	nSwitch->Radius = 0.6f;
	nSwitch->Plr_Only = true;
	nSwitch->Tex = mRes->Switch[0];
	nSwitch->Trigger_Type = nSwitch->TYPE_SWITCH;
	nSwitch->Draw_Size.Set( 0.5f, 0.5f );

	nSwitch->Event = new Map_0_Stuff::Event_Flip_Sword_Barrier;


	
	RGSPB_Phys::Obj_Trigger* nTrig_Sword = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig_Sword );

	nTrig_Sword->Pos.Set( 4,3 );
	nTrig_Sword->Radius = 1.f;
	nTrig_Sword->Plr_Only = true;

	nTrig_Sword->Event = new Map_0_Stuff::Event_Get_Sword;


	
	RGSPB_Phys::Obj_Trigger* nDoor = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nDoor );

	nDoor->Pos.Set( 23,17 );
	nDoor->Radius = 1.f;
	nDoor->Plr_Only = true;

	nDoor->Event = new RGSPB_Events::Event_Load_Map;
	nDoor->Trig_Type_Arg = 1;
	nDoor->Trigger_Type = RGSPB_Phys::Obj_Trigger::TYPE_CONTINUOUS;
}





/*    MAP 1   */			  
#define M_1_LOC ((Map_1_Stuff::Map_1_Data*)mGame->M_Local)

void Map_1_Stuff::Map_1_Data::Initialize()
{
	this->Oldman_Conv = mGame->Conversation.Load_Conv( "stuff/conv/not_the_same.txt" );

	mGame->Plr_Obj->Pos.Set( 18.5f, 1 );
}

void Map_1_Stuff::Map_1_Data::Add_To_Game()
{			  
	RGSPB_Game::AI_Base* Old_Man = new RGSPB_Game::AI_Base;
	mGame->Physics.Add( Old_Man );

	Old_Man->Pos.Set( 18, 5 );
	Old_Man->Tex = mRes->Old_Man;
	Old_Man->Draw_Size.y = 1.f;
	Old_Man->Draw_Pos.y = -0.5f;



	
																		
	RGSPB_Phys::Obj_Trigger* nTrig = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig );

	nTrig->Pos.Set( 18,5 );
	nTrig->Radius = 1.f;
	nTrig->Plr_Only = true;

	nTrig->Event = new RGSPB_Events::Event_Conv;
	((RGSPB_Events::Event_Conv*)nTrig->Event)->Convs = M_0_LOC->Oldman_Conv;




	RGSPB_Phys::Obj_Trigger* nSwitch_Hors = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nSwitch_Hors );

	nSwitch_Hors->Pos.Set( 25,4.5f );
	nSwitch_Hors->Radius = 0.6f;
	nSwitch_Hors->Plr_Only = true;
	nSwitch_Hors->Tex = mRes->Switch[0];
	nSwitch_Hors->Trigger_Type = nSwitch_Hors->TYPE_SWITCH;
	nSwitch_Hors->Draw_Size.Set( 0.5f, 0.5f );

	nSwitch_Hors->Event = new Map_1_Stuff::Event_Hors_Bridge;



	RGSPB_Phys::Obj_Trigger* nSwitch_Vert = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nSwitch_Vert );

	nSwitch_Vert->Pos.Set( 14,15 );
	nSwitch_Vert->Radius = 0.6f;
	nSwitch_Vert->Plr_Only = true;
	nSwitch_Vert->Tex = mRes->Switch[0];
	nSwitch_Vert->Trigger_Type = nSwitch_Vert->TYPE_SWITCH;
	nSwitch_Vert->Draw_Size.Set( 0.5f, 0.5f );

	nSwitch_Vert->Event = new Map_1_Stuff::Event_Vert_Bridge;


	
	
	RGSPB_Phys::Obj_Trigger* nDoor = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nDoor );

	nDoor->Pos.Set( 31,4.5f );
	nDoor->Radius = 1.f;
	nDoor->Plr_Only = true;

	nDoor->Event = new RGSPB_Events::Event_Load_Map;
	nDoor->Trigger_Type = RGSPB_Phys::Obj_Trigger::TYPE_CONTINUOUS;
	nDoor->Trig_Type_Arg = 2;




	
	RGSPB_Phys::Obj_Trigger* nHors_Conv = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nHors_Conv );

	nHors_Conv->Pos.Set( 14,15 );
	nHors_Conv->Radius = 0.6f;
	nHors_Conv->Plr_Only = true;
	nHors_Conv->Trigger_Type = nSwitch_Hors->TYPE_SINGLE;
	nHors_Conv->Draw_Size.Set( 0.5f, 0.5f );

	nHors_Conv->Event = new Map_1_Stuff::Event_Got_Hors_Conv;
}

void Map_1_Stuff::Map_1_Data::Cleanup()
{	  
}
											 

void Map_1_Stuff::Event_Hors_Bridge::Do_Event()
{
	if( this->Arg )// true
		mGame->m_Map.Set_Box(18, 7, 2, 2, 1, 0);
	else//false									
		mGame->m_Map.Set_Box(18, 7, 2, 2, 1, 5);
}

void Map_1_Stuff::Event_Vert_Bridge::Do_Event()
{
	if( this->Arg )// true
		mGame->m_Map.Set_Box(28, 4, 2, 2, 1, 0);
	else//false									
		mGame->m_Map.Set_Box(28, 4, 2, 2, 1, 5);
}

void Map_1_Stuff::Event_Got_Hors_Conv::Do_Event()
{	  
	M_1_LOC->Oldman_Conv = mGame->Conversation.Load_Conv( "stuff/conv/where_could_he.txt" );
	
																		
	RGSPB_Phys::Obj_Trigger* nTrig = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig );

	nTrig->Pos.Set( 18,5 );
	nTrig->Radius = 1.f;
	nTrig->Plr_Only = true;

	nTrig->Event = new RGSPB_Events::Event_Conv;
	((RGSPB_Events::Event_Conv*)nTrig->Event)->Convs = M_1_LOC->Oldman_Conv;
}







/*    MAP 2   */			  
#define M_2_LOC ((Map_2_Stuff::Map_2_Data*)mGame->M_Local)

void Map_2_Stuff::Map_2_Data::Initialize()
{
	this->Final_Conv = mGame->Conversation.Load_Conv( "stuff/conv/found_you.txt" );

	mGame->Plr_Obj->Pos.Set( 21, 10 );
}

void Map_2_Stuff::Map_2_Data::Add_To_Game()
{			  														
	RGSPB_Phys::Obj_Trigger* nTrig = new RGSPB_Phys::Obj_Trigger;
	mGame->Physics.Add( nTrig );

	nTrig->Pos.Set( 21,10 );
	nTrig->Radius = 1.f;
	nTrig->Plr_Only = true;

	nTrig->Event = new RGSPB_Events::Event_Conv;
	((RGSPB_Events::Event_Conv*)nTrig->Event)->Convs = M_2_LOC->Final_Conv;



		  
	RGSPB_Game::AI_Base* Old_Man = new RGSPB_Game::AI_Base;
	mGame->Physics.Add( Old_Man );

	Old_Man->Pos.Set( 18, 5 );
	Old_Man->Tex = mRes->Old_Man;
	Old_Man->Draw_Size.y = 1.f;
	Old_Man->Draw_Pos.y = -0.5f;



		  
	RGSPB_Game::AI_Base* Pixel_Boy = new RGSPB_Game::AI_Base;
	mGame->Physics.Add( Pixel_Boy );

	Pixel_Boy->Pos.Set( 18, 10 );
	Pixel_Boy->Tex = mRes->Pixel_Boy;
	Pixel_Boy->Draw_Size.y = 1.f;
	Pixel_Boy->Draw_Pos.y = -0.5f;
}

void Map_2_Stuff::Map_2_Data::Cleanup()
{			  
	//
}