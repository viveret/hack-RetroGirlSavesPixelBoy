#ifndef RGSPB_Map
#define RGSPB_Map

#include <SE/Types.hpp>


namespace RGSPB_Map_Lib
{
	void Register_Module();

	void Load_Whole( std::string Name );

	uchar Get( uint x, uint y, uchar Level );
	void Set( uint x, uint y, uchar Level, uchar ID );
	void Set_Box( uint x, uint y, uint w, uint h, uchar Level, uchar ID );

	uint Get_W();
	uint Get_H();
}


#endif
