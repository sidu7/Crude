#include "GameObject.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/Controller.h"
#include "Components/Body.h"
#include "Components/Animator.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "EventManager.h"

extern GameObjectManager *gpGameObjectManager;
extern ResourceManager *gpResourceManager;

GameObject::GameObject(int type) : mType(type)
{
}


GameObject::~GameObject()
{
	for(auto c: mComponents)
		delete c;
	mComponents.clear();
}

void GameObject::Update()
{	
	for(auto c: mComponents)
		c->Update();
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
		
	return NULL;
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

