/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Transform.cpp
Purpose:		Transformation Component of GameObject
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#include "Transform.h"
#include "../Managers/Events.h"
#include "../Managers/GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/EventManager.h"

extern Shader* gpShader;
extern Shader* gdShader;
extern Matrix3D* gpProj;
extern GameObjectManager* gpGameObjectManager;
extern EventManager *gpEventManager;

Transform::Transform() : Component (TRANSFORM)
{
}

Transform::~Transform()
{
}

void Transform::Update()
{
	Matrix3D rot, scale, transform;
	Matrix3D model;

	Matrix3DScale(&scale,mScale.x, mScale.y, 1.0f);

	Matrix3DTranslate(&trans, mPosition.x, mPosition.y, 0.0f);
	
	Matrix3DRotDeg(&rot, mAngle);
	Matrix3DConcat(&transform, &trans, &rot);
	Matrix3DConcat(&model, &transform, &scale);

	Matrix3DConcat(&mvp, gpProj, &model);
	gpShader->Bind();
	gpShader->SetUniformMat4fLoc(2, &mvp);
}

void Transform::UpdateLine()
{
	gdShader->Bind();
	gdShader->SetUniformMat4fLoc(1, &mvp);
}

void Transform::UpdateDebug()
{
	Matrix3D model, scale;
	Matrix3D d_mvp;
	Matrix3DScale(&scale, mScale.x, mScale.y, 1.0f);
	Matrix3DConcat(&model, &trans, &scale);
	Matrix3DConcat(&d_mvp, gpProj, &model);
	gdShader->Bind();
	gdShader->SetUniformMat4fLoc(1, &d_mvp);
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
			if (mScale.x <= 0.0f)
			{
				TombDestroyed *tbd = new TombDestroyed();
				tbd->tomb = the->tomb;
				gpEventManager->BroadcastEventToSubscribers(tbd);
			}
		}
		else if(mpOwner->mType == TOMB2HP && the->tomb == 2)
		{
			mScale.x -= 90.0f * the->HPLost;
			mPosition.x -= 45.0f * the->HPLost;
			if (mScale.x <= 0.0f)
			{
				TombDestroyed *tbd = new TombDestroyed();
				tbd->tomb = the->tomb;
				gpEventManager->BroadcastEventToSubscribers(tbd);
			}
		}
	}
	else if (pEvent->mType == TOMBDESTROY)
	{
		TombDestroyed *tbd = static_cast<TombDestroyed*>(pEvent);
		if (tbd->tomb == 1 && mPosition.x == 200.0f)
		{
			gpGameObjectManager->Destroy(mpOwner);
		}
		else if(tbd->tomb == 2 && mPosition.x == 760.0f)
		{
			gpGameObjectManager->Destroy(mpOwner);
		}
	}
}

Component * Transform::Create()
{
	return new Transform();
}

