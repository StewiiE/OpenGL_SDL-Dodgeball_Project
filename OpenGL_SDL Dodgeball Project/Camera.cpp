#include "camera.h" 
#include "Constants.h" 
#include <math.h> 
#include "../gl/glut.h" 

static Camera* instance = 0;
static float moveSpeed = 50.0f;
static float lookSpeed = 2.0f;

Camera::Camera()
{
	position.x = 0;
	position.y = 6;
	position.z = 6;
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}

void Camera::Update(float deltaTime, SDL_Event e)
{

	// Forward Vector: Spherical coordinates to Cartesian coordinates conversion (also known as the ‘look’ direction) 
	forward = Vector3D(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw));

	// Right vector 
	right = Vector3D(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));

	// Up vector : perpendicular to both forward and right, calculate using the cross product 
	up = Vector3D((right.y*forward.z) - (right.z*forward.y),
		(right.z*forward.x) - (right.x*forward.z),
		(right.x*forward.y) - (right.y*forward.x));

}

//-----------------------------------------------------------------------Rendering----------------------------------------------//

void Camera::Render()
{
	Vector3D lookatPos = position + forward; // make sure we're always looking at a point infront of the camera 
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y -1, lookatPos.z, up.x, up.y, up.z);

}