#ifndef RGSPB_PHYS
#define RGSPB_PHYS

#include <vector>
#include <S_Engine\utility\Math.h>
#include <S_Engine\win32\Threader.h>

#include "Game_Events.h"

namespace RGSPB_Phys
{				  
	namespace Obj_Types
	{enum {

		TYPE_BASE = 0,
		TYPE_TRIGGER,
		TYPE_AI,
		TYPE_ITEM
	};}

	struct Obj_Base
	{
		Obj_Base();		
		bool Delete_Flag;

		virtual uchar Get_Type();

		Point2D Pos;
		Point2D Pos_Last;
		Vector2D Velocity;	 
		float Radius;

		uint Tex;		
		Point2D Draw_Size;
		Point2D Draw_Pos;

		bool do_Phys, do_Draw, Collides;

		void Update_Pos( double dt );

		virtual void Update( double dt );
		virtual void Draw();

		//virtual void Collides_With( Point2D* Points ) = 0;// check all points within
		virtual bool Collide_Map( schar Dirx = 0, schar Diry = 0 );// collides with map object layer
															// direction (optional) for only faces);

		virtual bool Collide_Obj( Obj_Base* Other );
	};

	struct Obj_Trigger:public Obj_Base
	{
		Obj_Trigger();
		void Draw();
		void Update( double dt );

		uchar Get_Type();

		virtual void Trigger();
		bool Plr_Only;

		RGSPB_Events::Event_Base* Event;

		uint Trigger_Type;

		enum {
			TYPE_CONTINUOUS = 0,
			TYPE_SINGLE,
			TYPE_TIMER,
			TYPE_SWITCH
		};

		float Trig_Type_Arg, Cooldown;
	};


	struct Phys_Manager
	{
		Phys_Manager();

		void Cleanup();

		void Update( double dt );
		void Draw();
		bool Draw_Triggers;

									  
		Obj_Base* New_Obj();

		void Add( Obj_Base* Obj );

		E_Threads::Mutex Obj_Mutex;
		std::vector< Obj_Base* > Objects;
	};
}





#endif