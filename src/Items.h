#ifndef RGSPB_ITEMS
#define RGSPB_ITEMS

#include <SE/Core.hpp>
#include "Physics.h"

#include <string>

namespace RGSPB_Items
{
	struct Item_Base
	{
		Item_Base();

		void Use( RGSPB_Phys::Obj_Base* Self );

		uchar Type;

		uint Tex, Use_Sound;

		float Damage;

		std::string Name;

		enum {
			TYPE_NONE = 0,
			TYPE_MELLE,
			TYPE_RANGED,
			TYPE_STATIC
		};
	};


	struct Obj_Item:public RGSPB_Phys::Obj_Base
	{
		Obj_Item();

		uchar Get_Type();

		void Update( double dt );

		float Cooldown;

		Item_Base m_Item;
	};
}



#endif
