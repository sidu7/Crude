#include "Controller.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameObject.h"
#include "Body.h"
#include "Transform.h"
#include "SDL_keyboard.h"
#include "Animator.h"
#include "../Managers/ObjectFactory.h"
#include "../Managers/Events.h"
#include "Buff.h"
#include "Attributes.h"
#include "Sprite.h"
#include "../Managers/ResourceManager.h"
#include "SDL.h"

#include "../../Defines.h"

extern Input_Manager *gpInputManager;
extern ObjectFactory *gpObjectFactory;
extern EventManager *gpEventManager;
extern ResourceManager *gpResourceManager;
extern int GrenadeCount;


Controller::Controller() : Component (CONTROLLER) , moving(false)
{
	wallcollision = { 0 };
}

Controller::~Controller()
{
}

void Controller::Update()
{
	Animator *pAnimator = static_cast<Animator*>(mpOwner->GetComponent(ANIMATOR));
	Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	
	if(pAnimator->mCurrState != "throw")
	{
		
		pBody->mAngV = getAngleFromMouse(pBody->mPosition);
			
		if (gpInputManager->IsPressed(SDL_SCANCODE_W))
		{
			pBody->mAngV = 90.0f;
			if(pAnimator->mCurrState!="move_shoot")
				pAnimator->SetState("move");
			moving = true;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_A))
		{
			pBody->mAngV = 180.0f;
			if (pAnimator->mCurrState != "move_shoot")
				pAnimator->SetState("move");
			moving = true;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_S))
		{
			pBody->mAngV = 270.0f;
			if (pAnimator->mCurrState != "move_shoot")
				pAnimator->SetState("move");
			moving = true;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_D))
		{
			pBody->mAngV = 0.0f;
			if (pAnimator->mCurrState != "move_shoot")
				pAnimator->SetState("move");
			moving = true;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_D) && gpInputManager->IsPressed(SDL_SCANCODE_S)) {
			pBody->mAngV = 315.0f;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_D) && gpInputManager->IsPressed(SDL_SCANCODE_W)) {
			pBody->mAngV = 45.0f;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_A) && gpInputManager->IsPressed(SDL_SCANCODE_W)) {
			pBody->mAngV = 135.0f;
		}
		if (gpInputManager->IsPressed(SDL_SCANCODE_A) && gpInputManager->IsPressed(SDL_SCANCODE_S)) {
			pBody->mAngV = 225.0f;
		}
		if (gpInputManager->IsTriggered(SDL_SCANCODE_G))
		{
			if (GrenadeCount > 0)
			{
				pAnimator->PlayAnimation("throw", false);

				ThrowGrenadeEvent *tge = new ThrowGrenadeEvent();
				tge->pBody = pBody;
				tge->mTimer = 0.7f;

				gpEventManager->AddTimedEvent(tge);

				moving = false;

				GrenadeCount--;
			}
		}
		if (gpInputManager->IsTriggered(SDL_SCANCODE_SPACE))
		//if(gpInputManager->IsMouseClicked(SDL_BUTTON_LEFT))
		{
				
			if (pAnimator->mCurrState != "move")
				pAnimator->PlayAnimation("shoot", false);
			else if (pAnimator->mCurrState != "move_shoot")
			pAnimator->PlayAnimation("move_shoot", false);
			GameObject *pBullet = gpObjectFactory->GetArcheType(BULLET);
			Body *pBbulletBody = static_cast<Body*>(pBullet->GetComponent(BODY));
			//pBbulletBody->Initialize();
			Attributes *pAttr = static_cast<Attributes*>(pBullet->AddComponent(ATTRIBUTES));
			Attributes *pPlayerAttr = static_cast<Attributes*>(mpOwner->GetComponent(ATTRIBUTES));

			Buff *pBuff = static_cast<Buff*>(mpOwner->GetComponent(BUFF));
			if (pBuff != nullptr)
			{
				pAttr->mDamage = pPlayerAttr->mDamage * 2;
				Sprite *pSp = static_cast<Sprite*>(pBullet->GetComponent(SPRITE));
				pSp->mpTexture = gpResourceManager->LoadSurface("res/textures/doublebullet.png");
				Transform *pTr = static_cast<Transform*>(pBullet->GetComponent(TRANSFORM));
				pTr->mScale.y = 20.0f;
			}
			else
			{
				pAttr->mDamage = pPlayerAttr->mDamage;
			}

			//---- Offset -----------
			Vector2D OffsetY, OffsetX, Offset;
			Vector2DSet(&OffsetX, 40.0f * (float)cosf(pBody->mAngV * PI / 180), 40.0f * (float)sinf(pBody->mAngV * PI / 180));
			Vector2DSet(&OffsetY, 18.0f * (float)sinf(pBody->mAngV * PI / 180), 18.0f * (float)-cosf(pBody->mAngV * PI / 180));
			Vector2DAdd(&Offset, &OffsetX, &OffsetY);
			Vector2DAdd(&pBbulletBody->mPosition, &pBody->mPosition, &Offset);
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
			if ((wallcollision[1] && pBody->mVelocity.y > 0.0f) || (wallcollision[3] && pBody->mVelocity.y < 0.0f))
				Vector2DSet(&pBody->mVelocity, pBody->mVelocity.x, 0.0f);
			if ((wallcollision[0] && pBody->mVelocity.x < 0.0f) || (wallcollision[2] && pBody->mVelocity.x > 0.0f))
				Vector2DSet(&pBody->mVelocity, 0.0f, pBody->mVelocity.y);

		}
		moving = false;
		wallcollision = { 0 };
		
	}
}

Component * Controller::Create()
{
	return new Controller();
}

void Controller::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == WALLCOLLIDE)
	{
		Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		WallCollideEvent *wc = static_cast<WallCollideEvent*>(pEvent);
		wallcollision[wc->side] = true;
	}
	else if (pEvent->mType == GRENADETHROW)
	{
		ThrowGrenadeEvent *tge = static_cast<ThrowGrenadeEvent*>(pEvent);
		GameObject *pGrenade = gpObjectFactory->GetArcheType(GRENADE);
		Body *pGrenadeBody = static_cast<Body*>(pGrenade->GetComponent(BODY));
		
		//---- Offset -----------
		Vector2D Offset;
		Vector2DSet(&Offset, 40.0f * (float)cosf(tge->pBody->mAngV * PI / 180.0f), 40.0f * (float)sinf(tge->pBody->mAngV * PI / 180.0f));
		
		Vector2DAdd(&pGrenadeBody->mPosition, &tge->pBody->mPosition, &Offset);
		//-------------------------

		pGrenadeBody->mAngV = tge->pBody->mAngV;
		pGrenadeBody->AddVelocity(GRENADE_SPEED);

	}
}


float Controller::getAngleVector(Vector2D mVec1, Vector2D aVec2)
{

	float dotProduct, angle;
	Vector2D UpVec;

	dotProduct = Vector2DDotProduct(&mVec1, &aVec2);
	Vector2DSet(&UpVec, -mVec1.y, mVec1.x);


	angle = acosf(dotProduct / (Vector2DLength(&mVec1)*Vector2DLength(&aVec2)));

	if (Vector2DDotProduct(&UpVec, &aVec2) < 0)
	{
		angle = -angle;
	}
	return angle;
}

float Controller::getAngleFromMouse(Vector2D PlayerPos)
{
	Vector2D Dir, eDir;
	Vector2D MouseVec;
	int x, y;
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	Vector2DSet(&MouseVec, (float)x, (float)720 - y);
	Vector2DSub(&Dir, &MouseVec, &PlayerPos);
	Vector2DSet(&eDir, (float)cosf(PI), (float)sinf(PI));
	Vector2DNormalize(&Dir, &Dir);
	float ang = getAngleVector(Dir, eDir);
	if (ang > 0)
		return (float)acosf(Dir.x) * 180.0f / PI;
	else
		return (float)-(acosf(Dir.x) * 180.0f / PI);
}

