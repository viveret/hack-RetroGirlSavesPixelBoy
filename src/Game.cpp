#include "Game.h"
using namespace RGSPB_Game_Lib;

#ifdef _DEPRECATED
namespace RGSPB_Game_Lib
{
	SE_GUI_Lib::Widget_Dialogue* Conversation;

	AI_Base* Plr_Obj;

	// for editing 
	uchar Edit_Tile_ID, Edit_Level;
	bool is_Editing;

	RGSPB_Items::Item_Base Plr_Item;
	float Item_Use_Delay;
	Vector2f Item_Use_Dir;
}
// mutator operations
void Map::Set( uint x, uint y, uchar Level, uchar ID )
{				 

}

void Map::Set_Box( uint x, uint y, uint w, uint h, uchar Level, uchar ID )
{

}
		  
uint Map::Get_W()
{				   
	return this->w;
}

uint Map::Get_H()
{
	return this->h;
}


void Game_Map_Local_Data::Initialize()
{
	//
}

void Game_Map_Local_Data::Add_To_Game()
{
	//
}

void Game_Map_Local_Data::Cleanup()
{
	//
}



nnGame::nnGame()
{				
	this->In_Conv = false;
	this->M_Local = NULL;

	this->Plr_Obj = NULL;

	this->Edit_Tile_ID = 0;
	this->Edit_Level = 0;
	this->is_Editing = false;

	this->Item_Use_Delay = 0.f;
}

#include "Map_Code.h"
bool nnGame::Initialize()
{
	if( this->Initialize_Base() == false )
		return false;

	this->Get_Map( 0 );

	//this->Write_Map( "stuff/world/maps/map_0.txt" );  
							
	this->Plr_Obj = new AI_Base;
	this->Physics.Add( Plr_Obj );

	this->Plr_Obj->Pos.Set( 21, 10 );
	this->Plr_Obj->Radius = 0.5f;
	this->Plr_Obj->Tex = mRes->Player;
	this->Plr_Obj->do_Phys = false;
	this->Plr_Obj->do_Draw = false;

	this->Plr_Item.Tex = mRes->Sword;
}

void nnGame::Destroy()
{						  
	this->Physics.Cleanup();
	this->m_Map.Cleanup();

	this->Destroy_Base();
}

#include <SE/utility/Functions.hpp>
void nnGame::Draw()
{
	glPushMatrix();
	glTranslatef( Engine.Application.Window.Wind_w/2.f, Engine.Application.Window.Wind_h/ 2.f, 0 );
	glScalef( 32, 32, 1 );
								
	glTranslatef( -this->Plr_Obj->Pos.x, -this->Plr_Obj->Pos.y, 0 );

						   
	this->m_Map.Draw( 0 );
	this->m_Map.Draw( 1 );

	this->Physics.Draw();

	if( this->is_Editing )
	{
		sglDisable( GL_TEXTURE_2D );
		glColor4f( 1, 0, 0, 0.5f );
	
		int Plr_X = this->Plr_Obj->Pos.x, Plr_Y = this->Plr_Obj->Pos.y;

		glBegin( GL_QUADS );
			glVertex2f(-0.5f + Plr_X,-0.5f + Plr_Y);
			glVertex2f(+0.5f + Plr_X,-0.5f + Plr_Y);
			glVertex2f(+0.5f + Plr_X,+0.5f + Plr_Y);
			glVertex2f(-0.5f + Plr_X,+0.5f + Plr_Y);
		glEnd();
												
		glColor4f( 1, 1, 1, 1 );
	}
				  
	this->m_Map.Draw( 2 );

	glPopMatrix();

	if( this->is_Editing )
	{
		Draw_Utility::String_Draw( "Tile: "+To_Str(this->Edit_Tile_ID)+", Lvl: "+To_Str(this->Edit_Level), 200,200,1,0,0,1 );
					 
		float Tex_X = this->Edit_Tile_ID % 8,
				Tex_Y = this->Edit_Tile_ID / 8,
							Tex_W = 1.f, Tex_H = 1.f;
									   
		Tex_X *= TILE_TEX_SIZE;
		Tex_Y *= TILE_TEX_SIZE;
		Tex_W *= TILE_TEX_SIZE;
		Tex_H *= TILE_TEX_SIZE;				   

		Engine.Resources.Use_Texture( mRes->Tiles );
		glBegin( GL_QUADS );
			glTexCoord2f(Tex_X,			Tex_Y		 );	glVertex2f(200,220);
			glTexCoord2f(Tex_X + Tex_W,	Tex_Y		 );	glVertex2f(232,220);
			glTexCoord2f(Tex_X + Tex_W,	Tex_Y + Tex_H);	glVertex2f(232,252);
			glTexCoord2f(Tex_X,			Tex_Y + Tex_H);	glVertex2f(200,252);
		glEnd();

	}
}

void nnGame::Draw_HUD()
{					 
	glPushMatrix();
						 
	glTranslatef( Engine.Application.Window.Wind_w/2.f, Engine.Application.Window.Wind_h/ 2.f, 0 );
	glScalef( 32, 32, 1 );

	if( this->Item_Use_Delay != 0.f )
	{
		glPushMatrix();

		float Angle_Dir = atan2( this->Item_Use_Dir.x, this->Item_Use_Dir.y ) * 180 / 3.14f;
		//glTranslatef( 0,  , 0 ); 
		glRotatef( -Angle_Dir, 0, 0, 1 );

		Engine.Resources.Use_Texture( this->Plr_Item.Tex );
		glScalef( 0.5f,0.5f,1 );
		glBegin( GL_QUADS );
			glTexCoord2f(0, 0);	glVertex2f(-1,-1);
			glTexCoord2f(1,	0);	glVertex2f(+1,-1);
			glTexCoord2f(1,	1);	glVertex2f(+1,+1);
			glTexCoord2f(0,	1);	glVertex2f(-1,+1);
		glEnd();

		glPopMatrix();
	}

	//glTranslatef( -this->Plr_Obj->Pos.x, -this->Plr_Obj->Pos.y, 0 );	 
	glScalef( this->Plr_Obj->Radius, this->Plr_Obj->Radius * 2, 1 );
	glTranslatef( 0, -0.5f, 0 );					   
	
	Engine.Resources.Use_Texture( mRes->Shadow );
	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1.2f,-0.6f);
		glTexCoord2f(1,	0);	glVertex2f(+1.2f,-0.6f);
		glTexCoord2f(1,	1);	glVertex2f(+1.2f,+1.4f);
		glTexCoord2f(0,	1);	glVertex2f(-1.2f,+1.4f);
	glEnd();
	
	Engine.Resources.Use_Texture( mRes->Player );
	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1,-1);
		glTexCoord2f(1,	0);	glVertex2f(+1,-1);
		glTexCoord2f(1,	1);	glVertex2f(+1,+1);
		glTexCoord2f(0,	1);	glVertex2f(-1,+1);
	glEnd();

	glPopMatrix();

	if( this->Plr_Item.Type != this->Plr_Item.TYPE_NONE )
	{
		Engine.Resources.Use_Texture( this->Plr_Item.Tex );
		glBegin( GL_QUADS );
			glTexCoord2f(0, 0);	glVertex2f(ScreenW - 128,0);
			glTexCoord2f(1,	0);	glVertex2f(ScreenW,0);
			glTexCoord2f(1,	1);	glVertex2f(ScreenW,128);
			glTexCoord2f(0,	1);	glVertex2f(ScreenW - 128,128);
		glEnd();

		Draw_Utility::String_Draw( this->Plr_Item.Name, ScreenW - 4, 132, 1, 1, 1, 1, STR_POS_R );
	}

	if( this->In_Conv )
		this->Conversation.Draw();
}

void nnGame::Update( double dt )
{		
	ShowCursor( TRUE );

	if( Engine.In_Game )
	{
		this->Update_Input( Engine.Thread_Logic.m_Timer.dt );// only get input when in game
		
		this->Physics.Update( dt * this->Phys_Speed_Mod );

		this->Eventer.Update();

		if( this->In_Conv )
			this->Conversation.Update( dt );

		if( this->Item_Use_Delay != 0.f )
		{
			this->Item_Use_Delay -= dt;
			if( this->Item_Use_Delay < 0.f )
				this->Item_Use_Delay = 0.f;
		}
	}


	if( Engine.Is_Paused == false )
		this->Update_Base( dt );
}

#define PLR_SPEED 0.0005f
void nnGame::Update_Input( double dt )
{				
	if( this->In_Conv == false )
	{
		this->Plr_Mutex.Wait_For_Lock( __FUNCTION__ );
		this->Plr_Mutex.Lock();
			  
		if( Input_Keys->Left.Down )
			this->Plr_Obj->Velocity.x -= PLR_SPEED * dt;
	
		if( Input_Keys->Right.Down )
			this->Plr_Obj->Velocity.x += PLR_SPEED * dt;
	
		if( Input_Keys->Up.Down )
			this->Plr_Obj->Velocity.y -= PLR_SPEED * dt;
	
		if( Input_Keys->Down.Down )
			this->Plr_Obj->Velocity.y += PLR_SPEED * dt;

		if( Engine.Application.Input.Mouse_L_Down )	// use item
		{
			if( this->Plr_Item.Type != RGSPB_Items::Item_Base::TYPE_NONE )
			{
				this->Plr_Item.Use( this->Plr_Obj );
				Engine.Application.Input.Mouse_L_Down = false;

				this->Item_Use_Delay = 100.f;

				this->Item_Use_Dir.x = Engine.Application.Input.Mouse_X - ScreenW/2.f;
				this->Item_Use_Dir.y = Engine.Application.Input.Mouse_Y - ScreenH/2.f;

				this->Item_Use_Dir.Normalize();

				//Engine.Bass_Manager.Play_Sample( mRes->Swoosh_Sound );
			}
		}

		this->Plr_Obj->Update_Pos( dt );	  

		this->Plr_Mutex.Unlock();

		if( this->is_Editing )
		{
			this->Edit_Tile_ID += Engine.Application.Input.Mouse_Scroll;
			Engine.Application.Input.Mouse_Scroll = 0;

			if( Input_Keys->Action.Down )
			{
				uint Plr_X = this->Plr_Obj->Pos.x, Plr_Y = this->Plr_Obj->Pos.y;

				this->m_Map.Set( Plr_X, Plr_Y, this->Edit_Level, this->Edit_Tile_ID );
			}
		}
		
		if( Input_Keys->Toggle_Edit.Down )
		{
			this->is_Editing = !this->is_Editing;
			Input_Keys->Toggle_Edit.Down = false;
			this->Plr_Obj->Collides = !this->is_Editing;
		}
	}
	else
	{
		if( Input_Keys->Action.Down )
		{
			this->Conversation.Next_Conv();
			Input_Keys->Action.Down = false;
		}
	}
}

void nnGame::Clean()
{
}

void nnGame::Add_Body_Props( btRigidBody* Body )
{
	//
}

void nnGame::Get_Map( uint ID )
{
	if( this->M_Local )
	{
		this->M_Local->Cleanup();

		delete this->M_Local;
		this->M_Local = NULL;
	}

	this->Physics.Cleanup();


	switch( ID )
	{
	case 0:
		{				
			this->Load_Map( "stuff/world/maps/map_0.txt" );
			this->M_Local = new Map_0_Stuff::Map_0_Data;

			this->M_Local->Initialize();
			this->M_Local->Add_To_Game();
		}break;
	case 1:
		{								 
			this->Load_Map( "stuff/world/maps/map_1.txt" );
			this->M_Local = new Map_1_Stuff::Map_1_Data;

			this->M_Local->Initialize();
			this->M_Local->Add_To_Game();
		}break;
	case 2:
		{								 
			this->Load_Map( "stuff/world/maps/map_2.txt" );
			this->M_Local = new Map_2_Stuff::Map_2_Data;

			this->M_Local->Initialize();
			this->M_Local->Add_To_Game();
		}break;

	default:
		{
			Engine.Log( "Unknown Map: " + To_Str( ID ) + "\n", Log_Type::TYPE_EROR );
			return; // do not continue with level
		}break;
	}
}


void nnGame::Write_Map( std::string File )
{
	
}



bool E_Game::Obj_Callback( btManifoldPoint& cp, const btCollisionObject* Obj1, int id1, int index1, const btCollisionObject* Obj2, int id2, int index2 )
{
	return true;
}

#endif
