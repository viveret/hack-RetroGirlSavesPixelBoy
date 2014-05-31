#ifdef _DEPRECATED
void E_Application::Set_OpenGL_Settings()
{
	//sglEnable(GL_DEPTH_TEST);
	sglEnable(GL_COLOR_MATERIAL);   
	sglEnable(GL_BLEND);					 
	sglEnable(GL_ALPHA_TEST);	   


	glShadeModel(GL_SMOOTH);
	glClearDepth(1.f);	 
	glClearColor(0.f,0.f,0.f,0.f); 
	//glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);		
	glAlphaFunc(GL_GREATER, 0.1f); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	 
	glClear(GL_DEPTH_BUFFER_BIT);  

	sglEnable(GL_TEXTURE_2D);   
	sglDisable(GL_LIGHTING);
	sglDisable(GL_FOG);	 
	sglChange(SGL_GREYSCALE, 100.f);


	E_Application::Switch_To_2D();
}		  

void E_Application::Switch_To_3D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f + Engine.Application.Utility.Zoom,(float)Engine.Application.Window.Wind_w/(float)Engine.Application.Window.Wind_h, Engine.Application.OpenGL_Settings.Z_Near, Engine.Application.OpenGL_Settings.Z_Far );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	sglEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);  
	//sglEnable(GL_POLYGON_SMOOTH);	
    //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	//APP.UseLighting(true);	

	sglEnable(GL_LIGHTING);
	sglEnable(GL_FOG);
}

void E_Application::Switch_To_2D()
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho( 0.f ,Engine.Application.Window.Wind_w, Engine.Application.Window.Wind_h, 0, 0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT);
	sglDisable(GL_DEPTH_TEST);
    //glDepthMask(GL_FALSE); 
	//Engine.Application.OpenGL.GL_Shader->Cull(false);
					
	sglDisable(GL_LIGHTING);
	sglDisable(GL_FOG);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}	

void nnKeys::Defaults()
{
	this->Quit.Key_Code = VK_ESCAPE;
	this->Pause.Key_Code = VK_TAB;
	this->Debug.Key_Code = VK_OEM_3;// ~
							  
	this->Left.Key_Code = 'A';
	this->Right.Key_Code = 'D';
	this->Up.Key_Code = 'W';
	this->Down.Key_Code = 'S';

	this->Action.Key_Code = VK_SPACE;

	this->Toggle_Edit.Key_Code = 'Q';
}

E_Application::Key* nnKeys::String_TO_Key( std::string Name )
{
	return NULL;
}

#include "Game.h"
void nnKeys::Update( u_int Key_Code,bool Set )
{							   
	if( Key_Code == this->Left.Key_Code )
		this->Left.Down = Set;
	
	else if( Key_Code == this->Right.Key_Code )
		this->Right.Down = Set;
	
	else if( Key_Code == this->Up.Key_Code )
		this->Up.Down = Set;
	
	else if( Key_Code == this->Down.Key_Code )
		this->Down.Down = Set;

	else if( Key_Code == this->Action.Key_Code )
		this->Action.Down = Set;

	else if( Key_Code == this->Toggle_Edit.Key_Code )
		this->Toggle_Edit.Down = Set;






	else if( this->Pause.Key_Code == Key_Code )
		this->Pause.Down = Set;

	else if( this->Debug.Key_Code == Key_Code )
		this->Debug.Down = Set;
	
	else if( this->Quit.Key_Code == Key_Code )
		this->Quit.Down = Set;	 



	else if( mGame )
	{
		if( Key_Code == '1' )
			mGame->Edit_Level = 0;
		
		else if( Key_Code == '2' )
			mGame->Edit_Level = 1;

		else if( Key_Code == '3' )
			mGame->Edit_Level = 2;

		else if( Key_Code == VK_RETURN )
			mGame->Write_Map( "stuff/world/maps/temp.txt" );
	}
}



void E_Application::A_Application::Update( double dt )
{
	this->Update_Base( dt );
}

#endif
