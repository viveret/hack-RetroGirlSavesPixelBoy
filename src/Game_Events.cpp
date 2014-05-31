#include "Game_Events.h"
using namespace RGSPB_Events;

#include "Game.h"

#ifdef _DEPRECATED
Event_Base::Event_Base()
{
	this->Arg = 0.f;
}

void Event_Base::Do_Event()
{
	//
}


			   
Event_Timer::Event_Timer()
{
	this->Time_Left = -1.f;
}

void Event_Timer::Do_Event()
{
}

void Event_Conv::Do_Event()
{			  
	mGame->Conversation.Cur_Conv = this->Convs;
	mGame->In_Conv = true;
}

void Event_Load_Map::Do_Event()
{
	mGame->Get_Map( this->Arg );
}


Event_Handler::Event_Handler()
{
	//
}

void Event_Handler::Update()
{
	while( this->Event_Queue.size() > 0 )
	{
		this->Event_Queue[0]->Do_Event();
		this->Event_Queue.erase( this->Event_Queue.begin() );
	}
}


/*



		switch( this->Event_Queue[0]->Type )
		{
		case EVENT_CONV_START:
			{
				/*RGSPB_Conv::Conv_Single nConv;
				nConv.Text = "Lolwhat\nshiggy diggy doo\nIts dangerous to go alone;\ntake this:";
				nConv.Who = 0;// me

				mGame->Conversation.Cur_Conv.push_back( nConv );*/
			  /*
			}break;

			*/

#endif
