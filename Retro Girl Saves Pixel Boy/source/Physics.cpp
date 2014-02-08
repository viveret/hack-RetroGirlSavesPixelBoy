#include "Physics.h"
using namespace RGSPB_Phys;	

#include <S_Engine\S_Engine.h>
extern S_Engine Engine;

#include "Game.h"


Obj_Base::Obj_Base()
{
	this->Delete_Flag = false;
	this->Tex = 0; 
	this->Radius = 0.5f;
	this->Draw_Size.Set( 0.5f, 0.5f );

	this->do_Phys = true;
	this->do_Draw = true;
	this->Collides = true;
}

uchar Obj_Base::Get_Type()
{
	return Obj_Types::TYPE_BASE;
}


#define PHYS_VEL_SPEED 0.04f
#define PHYS_VEL_RESIST 0.004f

#include <S_Engine\utility\Functions.h>
void Obj_Base::Update_Pos( double dt )
{				
	this->Pos_Last = this->Pos;

	this->Pos.x += this->Velocity.x * dt * PHYS_VEL_SPEED;
	this->Pos.y += this->Velocity.y * dt * PHYS_VEL_SPEED;
					
	schar Sign_Check = Sign( this->Velocity.x );
	this->Velocity.x -= this->Velocity.x * dt * PHYS_VEL_RESIST;
	if( Sign(this->Velocity.x) != Sign_Check )
		this->Velocity.x = 0.f;
												
	Sign_Check = Sign( this->Velocity.y );
	this->Velocity.y -= this->Velocity.y * dt * PHYS_VEL_RESIST;
	if( Sign(this->Velocity.y) != Sign_Check )
		this->Velocity.y = 0.f;
		
	if( this->Collide_Map() && this->Collides )
	{
		this->Pos = this->Pos_Last;
		this->Velocity.Set( 0, 0 );
	}
	/*else if( this->Collide_Map( Sign(this->Velocity.x), Sign(this->Velocity.y) ) )
	{
		this->Pos = this->Pos_Last;
		this->Velocity.Set( 0, 0 );
	}
	else if( this->Collide_Map( Sign(this->Velocity.x), 0 ) )
	{
		this->Pos.x = this->Pos_Last.x;
		this->Velocity.x = 0.f;
	}
	else if( this->Collide_Map( 0, Sign(this->Velocity.y) ) )
	{
		this->Pos.y = this->Pos_Last.y;
		this->Velocity.y = 0.f;
	} 	  */
}

void Obj_Base::Update( double dt )
{
	this->Update_Pos( dt );
	this->Collide_Map( Sign(this->Velocity.x), Sign(this->Velocity.y) );
								   
	//this->Velocity.x -= 0.0005f * dt;
	//this->Velocity.y -= 0.0005f * dt;
}

#include "Resources.h"

void Obj_Base::Draw()
{
	glPushMatrix();

	glTranslatef( this->Pos.x, this->Pos.y, 0 );
	glScalef( this->Draw_Size.x, 1, 1 );		  
	
	Engine.Resources.Use_Texture( mRes->Shadow );
	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1,-1.2f);
		glTexCoord2f(1,	0);	glVertex2f(+1,-1.2f);
		glTexCoord2f(1,	1);	glVertex2f(+1,+0.8f);
		glTexCoord2f(0,	1);	glVertex2f(-1,+0.8f);
	glEnd();

	glPopMatrix();
	glPushMatrix();
						  
	glTranslatef( this->Pos.x + this->Draw_Pos.x, this->Pos.y + this->Draw_Pos.y, 0 );
	glScalef( this->Draw_Size.x, this->Draw_Size.y, 1 );		  

	Engine.Resources.Use_Texture( this->Tex );
	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1,-1);
		glTexCoord2f(1,	0);	glVertex2f(+1,-1);
		glTexCoord2f(1,	1);	glVertex2f(+1,+1);
		glTexCoord2f(0,	1);	glVertex2f(-1,+1);
	glEnd();


	glPopMatrix();
}

/*void Obj_Base::::Collides_With( Point2D* Points )
{
	//
} */
bool Obj_Base::Collide_Map( schar Dirx, schar Diry )// direction (optional) for only faces
{
	/*uint x_s = this->Pos.x + this->Radius * Dirx, x_m = this->Pos.x + this->Radius * Dirx + 1.5f * Dirx;
	uint y_s = this->Pos.y + this->Radius * Diry, y_m = this->Pos.y + this->Radius * Diry + 1.5f * Diry;

	bool Points[4] = {
		mGame->m_Map.Get( x_s, y_s, 1 ) != 0,
		mGame->m_Map.Get( x_s, y_m, 1 ) != 0,
		mGame->m_Map.Get( x_m, y_m, 1 ) != 0,
		mGame->m_Map.Get( x_m, y_m, 1 ) != 0
	};*/
	/*
			()a()e
				()b
			()c()d	  NEED TO DO CORNER OF EACH SIDE
	*/

	bool Checks[3];
	if( mGame->m_Map.Get( this->Pos.x + this->Radius, this->Pos.y + this->Radius * 2, 1 ) ||
		mGame->m_Map.Get( this->Pos.x + this->Radius, this->Pos.y, 1 )  )// c
		return true;

	if( mGame->m_Map.Get( this->Pos.x + this->Radius * 2, this->Pos.y + this->Radius, 1 ) ||
		mGame->m_Map.Get( this->Pos.x, this->Pos.y + this->Radius, 1 )  )// c
		return true;


	//if( Points[0] || Points[1] || Points[2] || Points[3] )//if( mGame->m_Map.Get( x_s, y_s, 1 ) != 0 || mGame->m_Map.Get( x_m, y_m, 1 ) != 0 )
/*	{
		return true;
	}	*/
	else
		return false;
}

bool Obj_Base::Collide_Obj( Obj_Base* Other )
{
	if( Dist_2D( Other->Pos, this->Pos ) < Other->Radius + this->Radius )// there was a collision
	{
		return true;
	}

	return false;
}





Obj_Trigger::Obj_Trigger()
{
	this->Radius = 0.f;
	this->Trigger_Type = this->TYPE_SINGLE;
	this->Trig_Type_Arg = 0.f;
	this->Cooldown = 0.f;

	this->Event = NULL;

	this->Plr_Only = false;

	this->Tex = NULL;

	this->Draw_Size.Set( 0.5f, 0.5f );
}

uchar Obj_Trigger::Get_Type()
{
	return Obj_Types::TYPE_TRIGGER;
}

void Obj_Trigger::Update( double dt )
{
	this->Cooldown -= dt;
	if( this->Cooldown < 0.f )
		this->Cooldown = 0.f;


	for( uint i = 0;i < mGame->Physics.Objects.size(); i++ )
	{
		if( this->Plr_Only )
		{
			if( mGame->Physics.Objects[i] == mGame->Plr_Obj )
			/*
		if( mGame->Physics.Objects[i]->Get_Type() != Obj_Types::TYPE_TRIGGER && mGame->Physics.Objects[i] != this &&
			mGame->Physics.Objects[i]->Get_Type() != Obj_Types::TYPE_ITEM )//&&
			//mGame->Physics.Objects[i]->Get_Type() != Obj_Types::TYPE_BASE )
		{
			if( this->Plr_Only )*/

			if( this->Collide_Obj( mGame->Physics.Objects[i] ) )
			{
				this->Trigger();
			}
		}
	}
}

void Obj_Trigger::Draw()
{				
	if( this->Tex == NULL )
		return;

	glPushMatrix();
	glTranslatef( this->Pos.x + this->Draw_Pos.x, this->Pos.y + this->Draw_Pos.y, 0 );
	glScalef( this->Draw_Size.x, this->Draw_Size.y, 1 );

	switch( this->Trigger_Type )
	{
	case Obj_Trigger::TYPE_SWITCH:
		Engine.Resources.Use_Texture( this->Tex + this->Trig_Type_Arg );
		break;
	default:
		Engine.Resources.Use_Texture( mRes->Trigger );
		break;
	}

	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1,-1);
		glTexCoord2f(1,	0);	glVertex2f(+1,-1);
		glTexCoord2f(1,	1);	glVertex2f(+1,+1);
		glTexCoord2f(0,	1);	glVertex2f(-1,+1);
	glEnd();


	glPopMatrix();
}	


#define COOLDOWN_TIME 600.f
void Obj_Trigger::Trigger()
{
	if( this->Cooldown > 0.f )
	{
		this->Cooldown = COOLDOWN_TIME;
		return;
	}

	switch( this->Trigger_Type )
	{
	case Obj_Trigger::TYPE_SINGLE:
		if( this->Trig_Type_Arg == 1.f )
			return;
		else
			this->Trig_Type_Arg = 1.f;
		break;
	case Obj_Trigger::TYPE_SWITCH:
		this->Trig_Type_Arg = !this->Trig_Type_Arg;
		//Engine.Bass_Manager.Play_Sample( mRes->Switch_Noise );
		break;
	}

	this->Cooldown = COOLDOWN_TIME;
	this->Event->Arg = this->Trig_Type_Arg;

	mGame->Eventer.Event_Queue.push_back( this->Event );
}


	 
Phys_Manager::Phys_Manager()
{
	this->Draw_Triggers = true;
}

void Phys_Manager::Cleanup()
{				
	for( uint i = 0;i < this->Objects.size(); i++ )
	{
		if( this->Objects[i] != mGame->Plr_Obj || Engine.Is_Running == false ) // dont delete player plz
		{
			Engine.Mem_Remove( this->Objects[i] );
			delete this->Objects[i];

			this->Objects.erase( this->Objects.begin() + i );
			i--;
		}
	}
}

void Phys_Manager::Update( double dt )
{
	this->Obj_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Obj_Mutex.Lock();

	for( uint i = 0;i < this->Objects.size(); i++ )
	{
		if( this->Objects[i]->Delete_Flag )
		{
			this->Objects.erase( this->Objects.begin() + i );
			i--;
		}
		else
			this->Objects[i]->Update( dt );
	}

	this->Obj_Mutex.Unlock();
}

/*
			  
		

		*/

void Phys_Manager::Draw()
{		   
	this->Obj_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Obj_Mutex.Lock();

	for( uint i = 0;i < this->Objects.size(); i++ )
	{
		if( this->Objects[i]->do_Draw )
			this->Objects[i]->Draw();
	}

	this->Obj_Mutex.Unlock();
}

Obj_Base* Phys_Manager::New_Obj()
{
	this->Obj_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Obj_Mutex.Lock();


	Obj_Base* nObj = new Obj_Base;
	this->Objects.push_back( nObj );
							
	this->Obj_Mutex.Unlock();

	Engine.Mem_Add( nObj, "Obj Base" );
	return nObj;
}

void Phys_Manager::Add( Obj_Base* Obj )
{		   
	this->Obj_Mutex.Wait_For_Lock( __FUNCTION__ );
	this->Obj_Mutex.Lock();
				
	this->Objects.push_back( Obj );
	Engine.Mem_Add( Obj, "Added Obj" );
			  
	this->Obj_Mutex.Unlock();
}
