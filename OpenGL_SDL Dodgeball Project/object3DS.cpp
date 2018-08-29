#include "object3DS.h" 
#include "../gl/glut.h" 
#include "3dsLoader.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "Constants.h"
#include <math.h>
#include "Texture.h"
#include <string>

//--------------------------------------------------------------------------------------------------
static float moveSpeed = 5.0f;

Object3DS::Object3DS(Vector3D startPosition, string modelFileName, string texturePath)
{
	//start position. 
	mPosition = startPosition;

	LoadTexture(texturePath);

	//3ds file to load. 
	std::strcpy(fileName, modelFileName.c_str());
	LoadModel();
}
//--------------------------------------------------------------------------------------------------

void Object3DS::LoadModel()
{
	if (fileName[0] != '-')
		Load3DS(&object, fileName);
}
//--------------------------------------------------------------------------------------------------

void Object3DS::LoadTexture(string texturePath)
{
	Texture2D* texture = new Texture2D();
	texture->Load(texturePath.c_str(), 512, 512);
	object.id_texture = texture->GetID();

	glBindTexture(GL_TEXTURE_2D, texture->GetID());

	glEnable(GL_TEXTURE_2D);

	//set some paramaters so it renders correctly
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
//--------------------------------------------------------------------------------------------------

void Object3DS::Update(float deltaTime, SDL_Event e)
{

}
//-------------------------------------------------------------------------------------------------- 

void Object3DS::Render()
{
	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);

	glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles) 

	for (int l_index = 0; l_index < object.triangles_qty; l_index++)
	{
		//-----------------FIRST VERTEX ----------------// 
		// Texture coordinates of the first vertex 
		glTexCoord2f( object.texcoord[ object.triangle[l_index].a ].u, 
			object.texcoord[ object.triangle[l_index].a ].v);
		// Coordinates of the first vertex 
		glVertex3f(object.vertex[object.triangle[l_index].a].x,
			object.vertex[object.triangle[l_index].a].y,
			object.vertex[object.triangle[l_index].a].z);
		//Vertex definition

		//-----------------SECOND VERTEX ---------------//
		// Texture coordinates of the second vertex 
		glTexCoord2f( object.texcoord[ object.triangle[l_index].b ].u,
			object.texcoord[ object.triangle[l_index].b ].v);
		// Coordinates of the second vertex 
		glVertex3f(object.vertex[object.triangle[l_index].b].x,
			object.vertex[object.triangle[l_index].b].y,
			object.vertex[object.triangle[l_index].b].z);

		//-----------------THIRD VERTEX -----------------
		// Texture coordinates of the third vertex 
		glTexCoord2f( object.texcoord[ object.triangle[l_index].c ].u,
			 object.texcoord[ object.triangle[l_index].c ].v);
		// Coordinates of the Third vertex 
		glVertex3f(object.vertex[object.triangle[l_index].c].x,
			object.vertex[object.triangle[l_index].c].y,
			object.vertex[object.triangle[l_index].c].z);
	}
	glEnd();
	glPopMatrix();
}
//--------------------------------------------------------------------------------------------------
