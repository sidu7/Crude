#include "GameObject.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/Controller.h"
#include "../Components/Body.h"
#include "../Components/Animator.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "EventManager.h"

extern GameObjectManager *gpGameObjectManager;
extern ResourceManager *gpResourceManager;

GameObject::GameObject(GameObjectTypes type) : mType(type), mDeathDelay(0.0f), Destroyed(false)
{
	Vector2DZero(&mTempScale);
}


GameObject::~GameObject()
{
	for(auto c: mComponents)
		delete c;
	mComponents.clear();
}

bool GameObject::Update()
{	
	for(auto c: mComponents)
		c->Update();
	return Destroyed;
}

Component* GameObject::AddComponent(unsigned int Type)
{
	Component *pNewComponent = nullptr;
	pNewComponent = gpGameObjectManager->mComponentMap[Type]->Create();
	
	if(pNewComponent != nullptr)
	{
		mComponents.push_back(pNewComponent);
		pNewComponent->mpOwner = this;
	}
	return pNewComponent;
}

Component* GameObject::GetComponent(unsigned int Type)
{
	for(auto c : mComponents)
		if(c->GetType() == Type)
			return c;
		
	return nullptr;
}

void GameObject::RemoveComponent(unsigned int Type)
{
	for (unsigned int i = 0; i < mComponents.size(); ++i)
		if (mComponents[i]->GetType() == Type)
		{
			mComponents.erase(mComponents.begin() + i);
			break;
		}
}

void GameObject::SetTransform(float posX, float posY, float scaleX, float scaleY, float angle)
{
	Transform* pTr = static_cast<Transform*>(GetComponent(TRANSFORM));
	
	pTr->mPosition.x = posX;
	pTr->mPosition.y = posY;
	pTr->mScale.x = scaleX;
	pTr->mScale.y = scaleY;
	pTr->mAngle = angle;
}

void GameObject::SetSprite(const char* filePath)
{
	Sprite* pSp = static_cast<Sprite*>(GetComponent(SPRITE));

	pSp->mpTexture = gpResourceManager->LoadSurface(filePath);
}

void GameObject::HandleEvent(Event * pEvent)
{
	for (auto c : mComponents)
	{
		if (mComponents.size() == 0)
			break;
		c->HandleEvent(pEvent);
	}
}


//For Debug Drawing

void GameObject::ScaleToBody()
{
	Transform *pTr = static_cast<Transform*>(GetComponent(TRANSFORM));
	Body* pBody = static_cast<Body*>(GetComponent(BODY));
	if (pBody == nullptr)
		return;
	Vector2DSet(&mTempScale, pTr->mScale.x, pTr->mScale.y);
	if (pBody->mpShape->mType == Shape::CIRCLE)
	{
		ShapeCircle *pCircle = static_cast<ShapeCircle*>(pBody->mpShape);
		Vector2DSet(&pTr->mScale, pCircle->mRadius*2, pCircle->mRadius * 2);
	}
	else
	{
		ShapeAABB *pShape = static_cast<ShapeAABB*>(pBody->mpShape);
		Vector2DSet(&pTr->mScale, pShape->mTop, pShape->mLeft);	
	}
	pTr->Debug = true;
	pTr->Update();
}

void GameObject::ResetScale()
{
	Transform *pTr = static_cast<Transform*>(GetComponent(TRANSFORM));
	Vector2DSet(&pTr->mScale, mTempScale.x, mTempScale.y);
	pTr->Debug = false;
	pTr->Update();
}

