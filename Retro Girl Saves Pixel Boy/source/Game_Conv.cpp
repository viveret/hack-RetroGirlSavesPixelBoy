#include "Game_Conv.h"
using namespace RGSPB_Conv;

Conv_Single::Conv_Single()
{
	this->Who = 0; 
}


Conv_Manager::Conv_Manager()
{
	this->Letter_At = 0;	
	this->Letter_At_F = 0.f;
	this->Done_Scrolling = false;
}

#include <S_Engine\S_Engine.h>
extern S_Engine Engine;
#include "Resources.h"


#define SCROLL_SPEED 0.01f
void Conv_Manager::Update( double dt )
{				
	this->Conv_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Conv_Mutex.Lock();

	if( this->Cur_Conv.size() > 0 )
	{
		if( this->Done_Scrolling == false )
		{
			this->Letter_At_F += SCROLL_SPEED * dt;
			if( this->Letter_At_F > SCROLL_SPEED )
			{
				this->Letter_At_F = 0.f;
				this->Letter_At++;

				//Engine.Bass_Manager.Play_Sample( mRes->Conv_Tick );

				if( this->Letter_At > this->Cur_Conv[0].Text.length() )
					this->Done_Scrolling = true;
			}
		}
	}

	this->Conv_Mutex.Unlock();
}

#include "Resources.h"
#include <S_Engine\utility\draw\Draw_Utility.h>
void Conv_Manager::Draw()
{
	glPushMatrix();
	sglDisable( GL_TEXTURE_2D );

	glColor4f( 0.4f, 0.4f, 0.4f, 0.7f );
					  
	glBegin( GL_QUADS );							   
		glVertex2f(0, Engine.Application.Window.Wind_h - 200);// CHAT BOX
		glVertex2f(500, Engine.Application.Window.Wind_h - 200);
		glVertex2f(500,Engine.Application.Window.Wind_h);
		glVertex2f(0,Engine.Application.Window.Wind_h);
					  // 6 padding
		glVertex2f(0, Engine.Application.Window.Wind_h - 140 - 200);// CHAT AVATAR
		glVertex2f(140, Engine.Application.Window.Wind_h -140 - 200);
		glVertex2f(140, Engine.Application.Window.Wind_h - 200);
		glVertex2f(0,Engine.Application.Window.Wind_h - 200);
	glEnd();
							   
	glColor4f( 1, 1, 1, 1 );
						
	this->Conv_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Conv_Mutex.Lock();

	if( this->Cur_Conv.size() > 0 )
	{
		if( this->Cur_Conv[0].Who < AVATAR_NUM )
		{
			Engine.Resources.Use_Texture( mRes->Avatars[ this->Cur_Conv[0].Who ] );
			glBegin( GL_QUADS );			// 6 padding
				glTexCoord2f(0, 0);glVertex2f(6, Engine.Application.Window.Wind_h - 134 - 200);// CHAT AVATAR
				glTexCoord2f(1, 0);glVertex2f(134, Engine.Application.Window.Wind_h -134 - 200);
				glTexCoord2f(1, 1);glVertex2f(134, Engine.Application.Window.Wind_h - 6 - 200);
				glTexCoord2f(0, 1);glVertex2f(6,Engine.Application.Window.Wind_h - 6 - 200);
			glEnd();
		}

		std::string Text_Amount_Draw;
		uint Text_Amount = this->Letter_At;

		Text_Amount_Draw = this->Cur_Conv[0].Text.substr( 0, Text_Amount );

		Draw_Utility::String_Draw( Text_Amount_Draw, 4, ScreenH - 140, 1, 1, 1, 1, STR_POS_L, 2.f );

		if( this->Done_Scrolling )
		{
			Engine.Resources.Use_Texture( mRes->Conv_Arrow );
			glBegin( GL_QUADS );			// 6 padding
				glTexCoord2f(0, 0);glVertex2f(500 - 64, Engine.Application.Window.Wind_h - 200);// CHAT AVATAR
				glTexCoord2f(1, 0);glVertex2f(500, Engine.Application.Window.Wind_h - 200);
				glTexCoord2f(1, 1);glVertex2f(500, Engine.Application.Window.Wind_h - 200 + 32);
				glTexCoord2f(0, 1);glVertex2f(500 - 64,Engine.Application.Window.Wind_h - 200 + 32);
			glEnd();
		}
	}

	this->Conv_Mutex.Unlock();


	glPopMatrix();
}

#include "Game.h"
void Conv_Manager::Next_Conv()
{			  
	this->Conv_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Conv_Mutex.Lock();

	this->Cur_Conv.erase( this->Cur_Conv.begin() );

	if( this->Cur_Conv.size() == 0 )// done with conv
		mGame->In_Conv = false;

	this->Conv_Mutex.Lock();
								 
	this->Letter_At = 0.f;
	this->Done_Scrolling = false;
}

Conv_Full Conv_Manager::Load_Conv( std::string File )
{
	Conv_Full Ret;

	std::string Data = Engine.Application.Input.Load_File_Str( File );

	if( Data.length() == 0 )
	{
		Engine.Log( "Cannot Make Conv W/ Data\n", Log_Type::TYPE_EROR );
		return Ret;
	}

	bool In_Text = false;

	Conv_Single nConv;
	std::string Temp_Str;

	for( uint l = 0;l < Data.length(); l++ )
	{
		if( In_Text == false )
		{
			if( Data[l] == '\"' )
				In_Text = true;
			else if( Data[l] == ':' )
			{
				nConv.Who = atoi( Temp_Str.c_str() );
				Temp_Str.clear();
			}
			else
				Temp_Str += Data[l];
		}
		else
		{
			if( Data[l] == '\"' )
			{
				nConv.Text = Temp_Str;
				In_Text = false;
				Ret.push_back( nConv );

				Temp_Str.clear();
			}
			else
				Temp_Str += Data[l];
		}
	}

	return Ret;
}