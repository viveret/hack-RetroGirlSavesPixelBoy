#ifndef RGSPB_RESOURCES
#define RGSPB_RESOURCES

#include <S_Engine\content\Resources.h>

#define AVATAR_NUM 3

struct nnRes:public E_Resources::R_Other_Resources
{
	nnRes();

	void Get_Resources();


	uint Tiles; // floor, collide, top

	uint Player, Old_Man, Pixel_Boy;

	uint Sword;

	uint Shadow;

	uint Trigger;


	uint Avatars[AVATAR_NUM];
	uint Conv_Arrow;
	uint Conv_Tick;

	// switches (uint[2]) are false/true
	uint Switch[2];
	uint Switch_Noise;

	uint Get_Item;

	uint Swoosh_IMG, Swoosh_Sound;

	uint Hit_Damage;

	std::string Test_Stream;
};
			   

#define mRes ((nnRes*)Engine.Resources.Stuff)

#endif