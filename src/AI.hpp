#ifndef RGSPB_AI
#define RGSPB_AI


namespace RGSPB_AI_Lib
{
	struct AI_Base:public RGSPB_Phys::Obj_Base
	{
		AI_Base();
		uchar Get_Type();

		void Update( double dt );
		void Draw();

		float Health;
		float AI_Kill_Anim;
	};
}


#endif
