#ifndef RGSPB_CONV
#define RGSPB_CONV

#include <S_Engine\Core.h>
#include <string>
#include <vector>
#include <S_Engine\win32\Threader.h>

namespace RGSPB_Conv
{
	struct Conv_Single
	{
		Conv_Single();

		std::string Text;
		uint Who;			   // 0 == player
	};

	typedef std::vector< Conv_Single > Conv_Full;

	struct Conv_Manager
	{
		Conv_Manager();

		void Update( double dt );
		void Draw();

		void Next_Conv();

		E_Threads::Mutex Conv_Mutex;
		Conv_Full Cur_Conv;

		float Letter_At_F;// for scrolling, can also be sped up
		uint Letter_At;
		bool Done_Scrolling;


		Conv_Full Load_Conv( std::string File );
	};
}



#endif