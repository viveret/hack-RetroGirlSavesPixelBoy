#ifdef _DEPRECATED

AI_Base::AI_Base()
{
	this->Health = 84.f;
	this->AI_Kill_Anim = 450.f;
}

uchar AI_Base::Get_Type()
{
	return RGSPB_Phys::Obj_Types::TYPE_AI;
}

void AI_Base::Update( double dt )
{		 
	this->Update_Pos( dt );
	this->Collide_Map( Sign(this->Velocity.x), Sign(this->Velocity.y) );

	if( this->Health < 0.f )
	{
		if( this->AI_Kill_Anim > 0.f )
		{
			this->AI_Kill_Anim -= dt;
		}
		else
			this->Delete_Flag = true;
	}
}

void AI_Base::Draw()
{		   
	glPushMatrix();

	glTranslatef( this->Pos.x, this->Pos.y, 0 );

	sglDisable( GL_TEXTURE_2D );// draw health bar	
	glBegin( GL_QUADS );							
		glColor3ub( 255, 216, 0 );
		glTexCoord2f(0, 0);	glVertex2f(-0.8f,-1.8f);// background
		glTexCoord2f(1,	0);	glVertex2f(+0.8f,-1.8f);
		glTexCoord2f(1,	1);	glVertex2f(+0.8f,-1.65f);
		glTexCoord2f(0,	1);	glVertex2f(-0.8f,-1.65f);
		
		glColor3f( 1, 0, 0 );					 
		glTexCoord2f(0, 0);	glVertex2f(-0.8f,-1.8f);
		glTexCoord2f(1,	0);	glVertex2f(-0.8f + 1.6f * this->Health / 100.f,-1.8f);
		glTexCoord2f(1,	1);	glVertex2f(-0.8f + 1.6f * this->Health / 100.f,-1.65f);
		glTexCoord2f(0,	1);	glVertex2f(-0.8f,-1.65f);
	glEnd();

	glColor3f( 1, 1, 1 );


	glScalef( this->Draw_Size.x, 1, 1 );		  
	
	Engine.Resources.Use_Texture( mRes->Shadow );
	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1,-1.2f);
		glTexCoord2f(1,	0);	glVertex2f(+1,-1.2f);
		glTexCoord2f(1,	1);	glVertex2f(+1,+0.8f);
		glTexCoord2f(0,	1);	glVertex2f(-1,+0.8f);
	glEnd();

	glPopMatrix();
	glPushMatrix();
						  
	glTranslatef( this->Pos.x + this->Draw_Pos.x, this->Pos.y + this->Draw_Pos.y, 0 );
	glScalef( this->Draw_Size.x * this->AI_Kill_Anim / 450.f, this->Draw_Size.y, 1 );		  

	Engine.Resources.Use_Texture( this->Tex );
	glBegin( GL_QUADS );
		glTexCoord2f(0, 0);	glVertex2f(-1,-1);
		glTexCoord2f(1,	0);	glVertex2f(+1,-1);
		glTexCoord2f(1,	1);	glVertex2f(+1,+1);
		glTexCoord2f(0,	1);	glVertex2f(-1,+1);
	glEnd();


	glPopMatrix();
}


#endif
