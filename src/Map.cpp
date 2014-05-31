#include "Map_Code.h"
#include "Map.hpp"

#include "Game.h"
#include "Resources.h"

#include "RGSPB_Core.hpp"

#include <sstream>
#include <fstream>
#include <stdlib.h>


namespace RGSPB_Map_Lib
{
	uchar* Map_Array = NULL;
	uint w = 0, h = 0;

	uint Tile_Tex = 0;


	// Lua module
	int Wrap_Get_Plr_Obj( lua_State* L )
	{
		return 0;
	}
	int Wrap_Save_Map( lua_State* L );
	int Wrap_Load_Map( lua_State* L );
	int Wrap_Load_Map_Lua( lua_State* L );
	int Wrap_Init_Map( lua_State* L );
	int Wrap_Tile( lua_State* L );
	int Wrap_Tile_Box( lua_State* L );
//	int Wrap_( lua_State* L );

	luaL_Reg Lualib[] = {
		{ "Get_Plr_Obj", Wrap_Get_Plr_Obj },
		{ "Load_Map", Wrap_Load_Map },
		{ "Load_Map_Lua", Wrap_Load_Map_Lua },
		{ "Save_Map", Wrap_Save_Map },
		{ "Init_Map", Wrap_Init_Map },
		{ "Tile", Wrap_Tile },
		{ "Tile_Box", Wrap_Tile_Box },
		{ NULL, NULL }
	};


	// Functions	
	void Initialize();
	void Cleanup();
	void Get_Resources();

	void Initialize_Map( uint n_w, uint n_h );
	void Cleanup_Map();

	void Render();

	void Load_Map( std::string Where );
	void Load_Lua( std::string Where );
	void Save( std::string Where );

	void Load_Map_Deprecated( std::string Where );
}
using namespace RGSPB_Map_Lib;



void RGSPB_Map_Lib::Load_Whole( std::string Name )
{
	Load_Lua( Name );
//	Load_Map( Where );
}

void RGSPB_Map_Lib::Load_Map( std::string Where )
{
	seLog->Printf( "RGSPB-Map", "Loading map %s ... ", Where.c_str() );

	const std::string& Bin_Map_Name = Where;

	if( Bin_Map_Name.length() == 0 )
	{
		seLog->Printf( "RGSPB-Map", "$(e)RGSPB_Map must be a defined string\n" );
		lua_pop( SE_Lua->gLua_State(), 1 );
		return;
	}

	SE_Raw_Buffer Data = SE_Filesys->File_Load_Instant( "levels/" + Bin_Map_Name );
	if( Data.Size() == 0 )
	{
		seLog->Printf( "RGSPB-Map", "$(e)Cannot Load Map Without Data\n" );
		return;
	}

	// get sizes
	uint n_w = 0, n_h = 0;
	memcpy( (void*)&n_w, Data.Data(), sizeof(uint) );
	memcpy( (void*)&n_h, Data.Data() + sizeof(uint), sizeof(uint) );

	Initialize_Map( n_w, n_h );

	memcpy( Map_Array, Data.Data() + 2 * sizeof(uint), w * h * 3 );

	Data.Delete();
}

void RGSPB_Map_Lib::Load_Lua( std::string Where )
{
	SE_Lua->Do_File( "./assets/levels/" + Where + ".lua" );
}


void RGSPB_Map_Lib::Save( std::string Where )
{
	Where = "./assets/levels/" + Where + ".bin";
	std::ofstream Writer( Where, std::ios::out | std::ios::binary );
	if( !Writer.is_open() )
	{
		seLog->Printf( "RGSPB-Map", "$(e)Failed to open bin %s\n", Where.c_str() );
		return;
	}


	Writer.write( (const char*)&w, sizeof(uint) );
	Writer.write( (const char*)&h, sizeof(uint) );
	Writer.write( (const char*)Map_Array, w * h * 3 );

	Writer.close();

	seLog->Printf( "RGSPB-Map", "$(d) Saved %s (%d, %d)\n", Where.c_str(), w, h );
}

uchar RGSPB_Map_Lib::Get( uint x, uint y, uchar Level )
{
	if( x < w && y < h && Level < 3 )
		return Map_Array[ x + y * h + (w * h * Level) ];

	else
		return 0;
}

void RGSPB_Map_Lib::Set( uint x, uint y, uchar Level, uchar ID )
{
	if( x < w && y < h && Level < 3 )
		Map_Array[ x + y * h + (w * h * Level) ] = ID;
}

void RGSPB_Map_Lib::Set_Box( uint x, uint y, uint w, uint h, uchar Level, uchar ID )
{
	if( x + w <= w && y + h <= h && Level < 3 )
	{							
		for( uint i_y = 0;i_y < h; i_y++ ){
		for( uint i_x = 0;i_x < w; i_x++ )
		{
			Set( i_x + x, i_y + y, Level, ID );
		}}
	}
}

uint RGSPB_Map_Lib::Get_W()
{
	return w;
}

uint RGSPB_Map_Lib::Get_H()
{
	return h;
}

#define TILE_TEX_SIZE 1.f/8.f
void RGSPB_Map_Lib::Render()
{
	segl->Clear_Screen();
	segl->Use_Texture( Tile_Tex );

	glPushMatrix();

	glTranslatef( 100, 100, 0 );
	glScalef( 32, 32, 1 );

	glBegin( GL_QUADS );

	for( uchar Level = 0; Level < 3; Level++ )
	{
		for( uint y = 0;y < h; y++ )
		{
			for( uint x = 0;x < w; x++ )
			{
				float Tex_X = Get(x, y, Level) % 8,
					  Tex_Y = Get(x, y, Level) / 8,
									Tex_W = 1.f, Tex_H = 1.f;
									   
				Tex_X *= TILE_TEX_SIZE;
				Tex_Y *= TILE_TEX_SIZE;
				Tex_W *= TILE_TEX_SIZE;
				Tex_H *= TILE_TEX_SIZE;

				if( Get( x, y, Level ) != 0 )
				{
					glTexCoord2f(Tex_X,			Tex_Y		 );	glVertex2f(-0.5f + x,-0.5f + y);
					glTexCoord2f(Tex_X + Tex_W,	Tex_Y		 );	glVertex2f(+0.5f + x,-0.5f + y);
					glTexCoord2f(Tex_X + Tex_W,	Tex_Y + Tex_H);	glVertex2f(+0.5f + x,+0.5f + y);
					glTexCoord2f(Tex_X,			Tex_Y + Tex_H);	glVertex2f(-0.5f + x,+0.5f + y);
				}
			}			
		}
	}

	glEnd();
	glPopMatrix();
}

void RGSPB_Map_Lib::Initialize_Map( uint n_w, uint n_h )
{
	assert( n_w != 0 );
	assert( n_h != 0 );

	assert( n_w < 200 );
	assert( n_h < 200 );

	if( Map_Array != NULL )
		Cleanup_Map();

	w = n_w;
	h = n_h;

	Map_Array = (uchar*)malloc( w * h * 3 );
	memset( Map_Array, 0, w * h * 3 );

	seLog->Printf( "RGSPB-Map", "$(d)Initialized %d, %d\n", w, h );
}

void RGSPB_Map_Lib::Cleanup_Map()
{
	if( Map_Array == NULL )
	{
		free( Map_Array );
		w = h = 0;
		Map_Array = NULL;

		seLog->Printf( "RGSPB-Map", "$(d)Cleaned" );
	}
}

void RGSPB_Map_Lib::Initialize()
{
/*	Load_Map_Deprecated( "map_0.txt" );
	Save( "map_0.bin" );
	Load_Map_Deprecated( "map_1.txt" );
	Save( "map_1.bin" );
	Load_Map_Deprecated( "map_2.txt" );
	Save( "map_2.bin" );

	assert( false );
*/
	SE_Lua->Register_Module( Lualib, "rgspb" );
	Load_Lua( "home" );
}

void RGSPB_Map_Lib::Cleanup()
{
	Cleanup_Map();
}

void RGSPB_Map_Lib::Get_Resources()
{
	segl->Get_Clear_Screen_Col()->Set( 0, 0, 0 );
	Tile_Tex = segl->Texture_Load( "levels/tileset.bmp" );
}

void RGSPB_Map_Lib::Register_Module()
{
	SE_Scheduler->Insert_Pos( seSchedule_Render(), Render, S_Engine::Module_Positions::POS_MED, 50 );

	SE_Scheduler->Insert_Pos( seSchedule_Engine_Init(), Initialize, S_Engine::Module_Positions::POS_MED + 32, 50 );
	SE_Scheduler->Insert_Pos( seSchedule_Engine_Clean(), Cleanup, S_Engine::Module_Positions::POS_MED + 32, 50 );
	SE_Scheduler->Insert_Pos( seSchedule_Render_Init(), Get_Resources, S_Engine::Module_Positions::POS_MED + 32, 50 );
}


// Lua wrap

int RGSPB_Map_Lib::Wrap_Load_Map( lua_State* L )
{
	if( lua_isstring(L, -1) )
	{
		Load_Map( lua_tostring(L, -1) );
	}
	else
		seLog->Printf( "RGSPB-Map-Lua", "$(e) Load_Map( string )\n" );

	return 0;
}

int RGSPB_Map_Lib::Wrap_Load_Map_Lua( lua_State* L )
{
	if( lua_isstring(L, -1) )
	{
		Load_Lua( lua_tostring(L, -1) );
	}
	else
		seLog->Printf( "RGSPB-Map-Lua", "$(e) Load_Map( string )\n" );

	return 0;
}

int RGSPB_Map_Lib::Wrap_Save_Map( lua_State* L )
{
	if( lua_isstring(L, -1) )
	{
		Save( lua_tostring(L, -1) );
	}
	else
		seLog->Printf( "RGSPB-Map-Lua", "$(e) Save_Map( string )\n" );

	return 0;
}

int RGSPB_Map_Lib::Wrap_Init_Map( lua_State* L )
{
	if( lua_isnumber(L, -1) && lua_isnumber(L, -2) )
	{
		Initialize_Map( lua_tonumber(L, -2), lua_tonumber(L, -1) );
	}
	else
		seLog->Printf( "RGSPB-Map-Lua", "$(e)Init_Map( uint, uint )\n" );

	return 0;
}

int RGSPB_Map_Lib::Wrap_Tile( lua_State* L )
{
	if( lua_isnumber(L, -3) && lua_isnumber(L, -2) && lua_isnumber(L, -1) )
	{
		int l = 0;
		if( lua_tonumber(L, -4) )
		{
			Set( lua_tonumber(L, -4), lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1) );
			l = -1;
		}
		
		lua_pushnumber( L, Get( lua_tonumber(L, l-3), lua_tonumber(L, l-2), lua_tonumber(L, l-1) ) );
		return 1;
	}
	else if( lua_gettop( L ) != 0 )
		seLog->Printf( "RGSPB-Map-Lua", "$(e)Tile( x, y, level, id )\n" );

	return 0;
}

int RGSPB_Map_Lib::Wrap_Tile_Box( lua_State* L )
{
	if( lua_isnumber(L, -3) && lua_isnumber(L, -2) && lua_isnumber(L, -1) )
	{
		Set_Box( lua_tonumber(L, -6), lua_tonumber(L, -5), lua_tonumber(L, -4), lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1) );
	}
	else
		seLog->Printf( "RGSPB-Map-Lua", "$(e)Tile_Box( x, y, w, h, level, id )\n" );

	return 0;
}






void RGSPB_Map_Lib::Load_Map_Deprecated( std::string Where )
{
	SE_Raw_Buffer Data_Raw = SE_Filesys->File_Load_Instant( "levels/" + Where );
	std::string Data = Data_Raw.Data();
	Data_Raw.Delete();

	if( Data.length() == 0 )
	{
		seLog->Printf( "RGSPB-Map", "$(e)Cannot Load Map Without Data\n" );
		return;
	}	

	Cleanup_Map();


	std::string Cur_Str;

	std::istringstream Name_Stream( Data );

	std::getline( Name_Stream, Cur_Str, ',' );// get starting size w
	uint n_w = atoi( Cur_Str.c_str() );	

	std::getline( Name_Stream, Cur_Str, '\n' );// get starting size h
	uint n_h = atoi( Cur_Str.c_str() );	


	Initialize_Map( n_w, n_h );


	uint x = 0, y = 0, Level = 0;

	// first get through directories
	while( std::getline( Name_Stream, Cur_Str, ',' ) )// for each branch
	{
		if( Cur_Str.find( "\n" ) )
			;//continue;

		uint nID = atoi(Cur_Str.c_str());
		Set( x, y, Level, nID );
		x++;
		if( x >= n_w )
		{
			x = 0;
			y++;

			if( y >= n_h )
			{
				y = 0;

				Level++;
				if( Level == 3 )
					break;
			}
		}
	}
}




#ifdef _DEPRECATED
/*    MAP 0   */			  
#define M_0_LOC ((Map_0_Stuff::Map_0_Data*)mGame->M_Local)

void Map_0_Stuff::Event_Flip_Sword_Barrier::Do_Event()
{
	if( Arg )// true
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
	Oldman_Conv = mGame->Conversation.Load_Conv( "stuff/conv/welcome.txt" );
	Self_Conv = mGame->Conversation.Load_Conv( "stuff/conv/self_thought.txt" );
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
	Oldman_Conv = mGame->Conversation.Load_Conv( "stuff/conv/not_the_same.txt" );

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
	if( Arg )// true
		mGame->m_Map.Set_Box(18, 7, 2, 2, 1, 0);
	else//false									
		mGame->m_Map.Set_Box(18, 7, 2, 2, 1, 5);
}

void Map_1_Stuff::Event_Vert_Bridge::Do_Event()
{
	if( Arg )// true
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
	Final_Conv = mGame->Conversation.Load_Conv( "stuff/conv/found_you.txt" );

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

#endif
