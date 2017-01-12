#include "PlayerCharacter.h"
#include "../Backbone/Input.h"
#include "../Controller/MovementKeyboard.h"
#include "../Controller/MovementDebug.h"

PlayerCharacter* Player = NULL;

//Arbirtrarily Spawns the player character in the upper left corner
PlayerCharacter::PlayerCharacter (void)
{
	//Set extern pointer instance to point to this
	if (Player == NULL)
		Player = this;
	else
		std::cout << "Error: Instance of PlayerCharacter has already been created" << std::endl;
	
	//Texture info for the player sprite
	tObjTex = LoadTexture ("./res/testy.png");
	rPosition.h = 128;
	rPosition.w = 64;
	rPosition.x = 32;
	rPosition.y = 32;

	//Body definition to create a physics body
	sBodyDef.type = b2_dynamicBody;
	sBodyDef.position.Set( (float) rPosition.x / pEngine->ptom, (float) rPosition.y / pEngine->ptom);
	sBodyDef.angle = 0;
	//sBodyDef.gravityScale = 0.0f;

	//Create the body and get a pointer to it
	pBody = pEngine->gWorld->CreateBody(&sBodyDef);

	//Define the shape of the body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((float)(rPosition.w / 2) / pEngine->ptom, (float)(rPosition.h / 2) / pEngine->ptom);

	//Define the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	//Create the fixture for the body
	pBody->CreateFixture (&fixtureDef);
	pBody->SetFixedRotation(true); //Don't want this shit to rotate

	//Set the rendering position of the player based on its location in the physics world
	rPosition.x = (int)(sBodyDef.position.x * pEngine->ptom - rPosition.w / 2);
	rPosition.y = (int)(sBodyDef.position.y * pEngine->ptom - rPosition.h / 2);
	
	//Move the player based on keyboard input
	pController = new MovementDebug();

	//Arbitrary value for render depth.
	m_render_depth = 2;
}

//Nothing to do here since the player does not add any new member variables
PlayerCharacter::~PlayerCharacter (void) {}

//Not sure if this is needed anymore
//Stuff the code from the constructor in here if it is
void PlayerCharacter::OnCreate (void) {}

//Also may be unnecessary because of destructors
//Add stuff as necessary
void PlayerCharacter::OnDestroy (void) {}

void PlayerCharacter::Update (void)
{
	//SDL_Rect teleport;
	sBodyDef.position = pBody->GetPosition();
	//Move the sprite to the correct location based on the Box2D results
	rPosition.x = (int)(sBodyDef.position.x * pEngine->ptom - rPosition.w / 2);
	rPosition.y = (int)(sBodyDef.position.y * pEngine->ptom - rPosition.h / 2);
	
	//Get a struct to store the velocity
	b2Vec2 currentVelocity(0.0f, 0.0f);
	//Get the velocity and SpriteIndex
	mSpriteIndex = pController->GetMove (&currentVelocity);
	//Move
	pBody->SetLinearVelocity(currentVelocity);

	//Special inputs: None yet
}

void PlayerCharacter::LateUpdate (void) {}

//Probably needed later on, when I actually get sprites and want to test them
/*void PlayerCharacter::Draw (void) {}*/

//The coordinates of the position should be in pixels
void PlayerCharacter::SetPosition (SDL_Rect pos)
{
	b2Vec2 n_pos;

	//Convert the pixel coordinates back to meters
	n_pos.x = (float)(pos.x / pEngine->ptom);
	n_pos.y = (float)(pos.y / pEngine->ptom);
	
	std::cout << "Set position to: " << n_pos.x << ", " << n_pos.y << std::endl;
	
	//Pass it back to Box2D
	pBody->SetTransform(n_pos, 0.0f);

	//Reset the pixel position based on the physics position, for consistency
	sBodyDef.position = pBody->GetPosition();
	
	rPosition.x = (int)(sBodyDef.position.x * pEngine->ptom - rPosition.w / 2);
	rPosition.y = (int)(sBodyDef.position.y * pEngine->ptom - rPosition.h / 2);
}