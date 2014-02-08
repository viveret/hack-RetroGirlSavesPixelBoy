#ifndef RGSPB_APP
#define RGSPB_APP

#include <S_Engine\app\App.h>


namespace RGSPB_App
{
	struct nnKeys:public E_Application::A_Input_Keys
	{
		void Defaults();

		E_Application::Key* String_TO_Key( std::string Name );

		void Update( u_int Key_Code,bool Set );

		E_Application::Key Left, Right, Up, Down;

		E_Application::Key Action, Toggle_Edit;
	};
}

#define Input_Keys ((RGSPB_App::nnKeys*)Engine.Application.Input.Keys)



#endif