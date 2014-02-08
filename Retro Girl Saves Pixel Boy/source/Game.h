#ifndef RGSPB_GAME
#define RGSPB_GAME

#include <S_Engine\game\Game.h>
#include <S_Engine\win32\Threader.h>

#include "Physics.h"
#include "Game_Conv.h"
#include "Items.h"



#define MAP_START 0 // room + kitchen




namespace RGSPB_Game
{
	struct Map
	{
		Map();
		~Map();

		void Initialize( uint x, uint y );
		void Cleanup();		

		void Draw( uchar Level );

		uchar Get( uint x, uint y, uchar Level );

		// mutator operations
		void Set( uint x, uint y, uchar Level, uchar ID );
		void Set_Box( uint x, uint y, uint w, uint h, uchar Level, uchar ID );

		uint Get_W();
		uint Get_H();

	private:
		uchar* Map_Array;

		uint w,h;
	};

	struct Game_Map_Local_Data
	{
		virtual void Initialize();
		virtual void Cleanup();
		virtual void Add_To_Game();
	};

	struct AI_Base:public RGSPB_Phys::Obj_Base
	{
		AI_Base();
		uchar Get_Type();

		void Update( double dt );
		void Draw();

		float Health;
		float AI_Kill_Anim;
	};

	struct nnGame:public E_Game::G_Game
	{
		nnGame();

		bool Initialize();
		void Destroy();

		void Draw();
		void Draw_HUD();

		void Update( double dt );
		void Update_Input( double dt );

		void Clean();

		void Add_Body_Props( btRigidBody* Body );


		void Get_Map( uint ID );
		void Load_Map( std::string File );
		void Write_Map( std::string File );

		Map m_Map;
		RGSPB_Phys::Phys_Manager Physics;

		RGSPB_Events::Event_Handler Eventer;
		RGSPB_Conv::Conv_Manager Conversation;
		bool In_Conv;

		E_Threads::Mutex Plr_Mutex;
		AI_Base* Plr_Obj;


		Game_Map_Local_Data* M_Local;

		// for editing 
		uchar Edit_Tile_ID, Edit_Level;
		bool is_Editing;

		RGSPB_Items::Item_Base Plr_Item;
		float Item_Use_Delay;
		Vector2D Item_Use_Dir;
	};
}


#define mGame ((RGSPB_Game::nnGame*)Engine.Game)


#endif