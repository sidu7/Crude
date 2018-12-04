#include "Transform.h"
#include "../Events.h"
#include "../GameObject.h"
#include "../GameObjectManager.h"

extern Shader* gpShader;
extern Matrix3D* gpProj;
extern GameObjectManager* gpGameObjectManager;

Transform::Transform() : Component (TRANSFORM)
{
}

Transform::~Transform()
{
}

void Transform::Update()
{
	Matrix3D scale, trans, rot, transform;
	Matrix3D model;
	Matrix3D mvp;

	Matrix3DScale(&scale,mScale.x, mScale.y, 1.0f);

	Matrix3DTranslate(&trans, mPosition.x, mPosition.y, 0.0f);
	
	if (!Debug)
	{
		Matrix3DRotDeg(&rot, mAngle);
		Matrix3DConcat(&transform, &trans, &rot);
		Matrix3DConcat(&model, &transform, &scale);
	}
	else
	{
		Matrix3DConcat(&model, &trans, &scale);
	}

	Matrix3DConcat(&mvp, gpProj, &model);
	gpShader->SetUniformMat4f("u_MVP", &mvp);
}

void Transform::Serialize(JSONObject obj)
{
	if (obj.find(L"Pos") != obj.end()) {
		JSONArray Pos = obj[L"Pos"]->AsArray();
		mPosition.x = (float)Pos[0]->AsNumber();
		mPosition.y = (float)Pos[1]->AsNumber();
	}
	if (obj.find(L"Scale") != obj.end()) {
		JSONArray Scale = obj[L"Scale"]->AsArray();
		mScale.x = (float)Scale[0]->AsNumber();
		mScale.y = (float)Scale[1]->AsNumber();
	}
	if(obj.find(L"Angle") != obj.end())
		mAngle = (float)obj[L"Angle"]->AsNumber();
}

void Transform::HandleEvent(Event * pEvent)
{
	if (mpOwner->mType == HPBAR && pEvent->mType == PLAYERHP)
	{
		PlayerHPEvent *phe = static_cast<PlayerHPEvent*>(pEvent);
		mScale.x += 155.0f * phe->HPChange;
		mPosition.x += 77.0f * phe->HPChange;
	}
	if (pEvent->mType == TOMBHIT)
	{
		TombHitEvent *the = static_cast<TombHitEvent*>(pEvent);
		if (mpOwner->mType == TOMB1HP && the->tomb == 1)
		{
			mScale.x -= 90.0f * the->HPLost;
			mPosition.x -= 45.0f * the->HPLost;
			if (mScale.x == 0.0f)
			{
				for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i)
				{
  					Transform *pTr = static_cast<Transform*>(gpGameObjectManager->mGameObjects[i]->GetComponent(TRANSFORM));
					if (gpGameObjectManager->mGameObjects[i]->mType == NO_OBJECT && pTr->mPosition.x == 200.0f)
					{
						gpGameObjectManager->mGameObjects.erase(gpGameObjectManager->mGameObjects.begin() + i);
					}
				}
			}
		}
		else if(mpOwner->mType == TOMB2HP && the->tomb == 2)
		{
			mScale.x -= 90.0f * the->HPLost;
			mPosition.x -= 45.0f * the->HPLost;
			if (mScale.x == 0.0f)
			{
				for (unsigned int i = 0; i < gpGameObjectManager->mGameObjects.size(); ++i)
				{
					Transform *pTr = static_cast<Transform*>(gpGameObjectManager->mGameObjects[i]->GetComponent(TRANSFORM));
					if (gpGameObjectManager->mGameObjects[i]->mType == NO_OBJECT && pTr->mPosition.x == 760.0f)
					{
						gpGameObjectManager->mGameObjects.erase(gpGameObjectManager->mGameObjects.begin() + i);
					}
				}
			}
		}
	}
}

Component * Transform::Create()
{
	return new Transform();
}

