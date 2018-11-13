#include "Controller.h"
#include "../InputManager.h"
#include "../GameObject.h"
#include "Body.h"
#include "Transform.h"
#include "SDL_keyboard.h"
#include "Animator.h"
#include "../ObjectFactory.h"
#include "../EventManager.h"

#include "../../Defines.h"

extern Input_Manager *gpInputManager;
extern ObjectFactory *gpObjectFactory;

Controller::Controller() : Component (CONTROLLER) , moving(false)
{
}

Controller::~Controller()
{
}

void Controller::Update()
{
	Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
	
	if(mpOwner != nullptr && gpInputManager != nullptr && pAnimator->mCurrState != "throw")
	{
		Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		
		if(pBody != nullptr)
		{
			if (gpInputManager->IsPressed(SDL_SCANCODE_UP))
			{
				pBody->mAngV = 90.0f;
				if(pAnimator->mCurrState!="move_shoot")
					pAnimator->SetState("move");
				moving = true;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_LEFT))
			{
				pBody->mAngV = 180.0f;
				if (pAnimator->mCurrState != "move_shoot")
					pAnimator->SetState("move");
				moving = true;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_DOWN))
			{
				pBody->mAngV = 270.0f;
				if (pAnimator->mCurrState != "move_shoot")
					pAnimator->SetState("move");
				moving = true;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_RIGHT))
			{
				pBody->mAngV = 0.0f;
				if (pAnimator->mCurrState != "move_shoot")
					pAnimator->SetState("move");
				moving = true;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_RIGHT) && gpInputManager->IsPressed(SDL_SCANCODE_DOWN)) {
				pBody->mAngV = 315.0f;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_RIGHT) && gpInputManager->IsPressed(SDL_SCANCODE_UP)) {
				pBody->mAngV = 45.0f;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_LEFT) && gpInputManager->IsPressed(SDL_SCANCODE_UP)) {
				pBody->mAngV = 135.0f;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_LEFT) && gpInputManager->IsPressed(SDL_SCANCODE_DOWN)) {
				pBody->mAngV = 225.0f;
			}
			if (gpInputManager->IsPressed(SDL_SCANCODE_G))
			{
				pAnimator->PlayAnimation("throw");
				moving = false;
			}
			else if (gpInputManager->IsTriggered(SDL_SCANCODE_SPACE))
			{
				if (pAnimator->mCurrState != "move")
					pAnimator->PlayAnimation("shoot");
				else if (pAnimator->mCurrState != "move_shoot")
					pAnimator->PlayAnimation("move_shoot");
				GameObject *pBullet = gpObjectFactory->LoadObject("bullet.json", BULLET);
				Body *pBbulletBody = static_cast<Body*>(pBullet->GetComponent(BODY));

				//---- Offset -----------
				Vector2D OffsetY,OffsetX,Offset;
				Vector2DSet(&OffsetX, 40.0f * cosf(pBody->mAngV * PI / 180), 40.0f * sinf(pBody->mAngV * PI / 180));
				Vector2DSet(&OffsetY, 18.0f * sinf(pBody->mAngV * PI / 180), 18.0f * -cosf(pBody->mAngV * PI / 180));
				Vector2DAdd(&Offset, &OffsetX, &OffsetY);
				Vector2DAdd(&pBbulletBody->mPosition, &pBody->mPosition, &Offset );
				//-------------------------

				pBbulletBody->mAngV = pBody->mAngV;
				pBbulletBody->AddVelocity(BULLET_SPEED);
			}

			if (moving == false)
			{
				if (!pAnimator->PlayingAnimation)
					pAnimator->ResetState();
				pBody->mVelocity.x = pBody->mVelocity.y = 0.0f;
			}
			else
			{
				pBody->AddVelocity(VELOCITY);
			}
			moving = false;
		}
	}
}

Component * Controller::Create()
{
	return new Controller();
}

void Controller::HandleEvent(Event * pEvent)
{
}
