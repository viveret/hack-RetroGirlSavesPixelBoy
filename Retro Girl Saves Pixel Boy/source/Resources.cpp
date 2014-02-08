#include "Resources.h"	  

#include <S_Engine\S_Engine.h>
extern S_Engine Engine;


#include <S_Engine\utility\Functions.h>

nnRes::nnRes()
{
	this->Tiles = 0; // floor, collide, top

	this->Player = 0;
	this->Old_Man = 0;
	this->Pixel_Boy = 0;

	this->Sword = 0;

	this->Shadow = 0;

	this->Trigger = 0;


	for( uint i = 0;i < AVATAR_NUM; i++ )
		this->Avatars[i] = 0;

	this->Conv_Arrow = 0;
	this->Conv_Tick = 0;

	
	this->Switch[0] = 0;
	this->Switch[1] = 0;

	this->Switch_Noise = 0;

	this->Get_Item = 0;

	this->Swoosh_IMG = 0;
	this->Swoosh_Sound = 0;

	this->Hit_Damage = 0;
}

void nnRes::Get_Resources()
{														  
	this->Tiles = Engine.Resources.Load_Texture( "stuff/world/tileset.bmp" );

	this->Player = Engine.Resources.Load_Texture( "stuff/env/player.png" );
	this->Old_Man = Engine.Resources.Load_Texture( "stuff/env/old_man.png" );
	this->Pixel_Boy = Engine.Resources.Load_Texture( "stuff/env/pixel_boy.png" );


	this->Sword = Engine.Resources.Load_Texture( "stuff/env/sword.png" );

	this->Shadow = Engine.Resources.Load_Texture( "stuff/env/shadow.png" );

	this->Trigger = Engine.Resources.Load_Texture( "stuff/env/trigger.png" );

	for( uint i = 0;i < AVATAR_NUM; i++ )
		this->Avatars[i] = Engine.Resources.Load_Texture( "stuff/hud/avatar_" + To_Str(i) + ".png" );

	this->Conv_Arrow = Engine.Resources.Load_Texture( "stuff/hud/arrow.png" );
	this->Conv_Tick = Engine.Bass_Manager.Load_Sample( "stuff/hud/letter_tick.wav" );

																				
	this->Switch[0] = Engine.Resources.Load_Texture( "stuff/env/switch_0.png" );
	this->Switch[1] = Engine.Resources.Load_Texture( "stuff/env/switch_1.png" );

	this->Switch_Noise = Engine.Bass_Manager.Load_Sample( "stuff/env/switch.wav" );

	this->Get_Item = Engine.Bass_Manager.Load_Sample( "stuff/hud/get_item.wav" );

	this->Swoosh_IMG = Engine.Resources.Load_Texture( "stuff/env/swoosh.png" );
	this->Swoosh_Sound = Engine.Bass_Manager.Load_Sample( "stuff/env/swing.wav" );

	this->Hit_Damage = Engine.Bass_Manager.Load_Sample( "stuff/env/hit.wav" );


	
	SE_File_Stream::Def_Files::File_TXT* nStrema = new SE_File_Stream::Def_Files::File_TXT;
	nStrema->Bytes_Per_Load = 1;// able to see process
	nStrema->Load( "stuff/test_stream.txt", &this->Test_Stream );
}