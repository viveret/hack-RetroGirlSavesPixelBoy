#include "Items.h"
using namespace RGSPB_Items;

#include <SE/module/Module.hpp>

#include "Game.h"


Item_Base::Item_Base()
{
	this->Type = this->TYPE_NONE;
	this->Damage = 0.f;

	this->Tex = 0;
	this->Use_Sound = 0;
}

#include "Resources.h"
#ifdef _DEPRECATED
void Item_Base::Use( RGSPB_Phys::Obj_Base* Self )
{
	switch( this->Type )
	{
	case Item_Base::TYPE_MELLE:
		{
			for( uint i = 0;i < mGame->Physics.Objects.size(); i++ )
			{
				if( mGame->Physics.Objects[i]->Get_Type() == RGSPB_Phys::Obj_Types::TYPE_AI && Self != mGame->Physics.Objects[i] )
				{
					if( Dist_2D( Self->Pos, mGame->Physics.Objects[i]->Pos ) < Self->Radius + mGame->Physics.Objects[i]->Radius + 1.f )
					{
						((RGSPB_Game::AI_Base*)mGame->Physics.Objects[i])->Health -= 11.f;
						//Engine.Bass_Manager.Play_Sample( mRes->Hit_Damage );
					}
				}
			}

			mGame->Physics.Obj_Mutex.Unlock();
		}break;
	case Item_Base::TYPE_RANGED:
		break;
	case Item_Base::TYPE_STATIC:
		break;

	default:
		return;
		break;
	}

	if( this->Use_Sound )
		;//Engine.Bass_Manager.Play_Sample( this->Use_Sound );
}


Obj_Item::Obj_Item()
{
	this->Cooldown = 0.f;
}

uchar Obj_Item::Get_Type()
{
	return RGSPB_Phys::Obj_Types::TYPE_ITEM;
}

#include "Resources.h"
void Obj_Item::Update( double dt )
{
	this->Cooldown -= dt;
	if( this->Cooldown < 0.f )
		this->Cooldown = 0.f;

	if( this->Collide_Obj( mGame->Plr_Obj ) )// player has grabbed
	{
		if( this->Cooldown <= 0.f )
		{
			if( mGame->Plr_Item.Type == Item_Base::TYPE_NONE )// just replace
			{
				mGame->Plr_Item = this->m_Item;
				this->Delete_Flag = true;
			}
			else
			{
				Item_Base Temp_Item = mGame->Plr_Item;
				mGame->Plr_Item = this->m_Item;

				this->m_Item = Temp_Item;
			}

			//Engine.Bass_Manager.Play_Sample( mRes->Get_Item );
		}

		this->Cooldown = 600.f;
	}
}

#endif
