#ifndef RGSPB_RESOURCES
#define RGSPB_RESOURCES

#include <SE/Types.hpp>


#define AVATAR_NUM 3

#ifdef _DEPRECATED
namespace RGSPB
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
#endif
			   

#endif
