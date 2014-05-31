#ifndef RGSPB_EVENTS
#define RGSPB_EVENTS

#include <SE/Core.hpp>
#include <vector>

namespace RGSPB_Events
{
	struct Event_Base
	{
		Event_Base();
		virtual void Do_Event();

		uint Arg;
	};

/*	struct Event_Conv:public Event_Base
	{
		void Do_Event();
		std::vector< RGSPB_Conv::Conv_Single > Convs;
	};
*/
	struct Event_Load_Map:public Event_Base
	{
		void Do_Event();
	};

	struct Event_Timer:public Event_Base
	{
		Event_Timer();
		void Do_Event();

		float Time_Left;
		Event_Base Event;
	};

	struct Event_Handler
	{
		Event_Handler();
		void Update();

		std::vector< Event_Base* > Event_Queue;
	};
}



#endif
