#include "Transform.h"
#include "../Events.h"
#include "../GameObject.h"

extern Shader* gpShader;
extern Matrix3D* gpProj;

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
		mPosition.x = Pos[0]->AsNumber();
		mPosition.y = Pos[1]->AsNumber();
	}
	if (obj.find(L"Scale") != obj.end()) {
		JSONArray Scale = obj[L"Scale"]->AsArray();
		mScale.x = Scale[0]->AsNumber();
		mScale.y = Scale[1]->AsNumber();
	}
	if(obj.find(L"Angle") != obj.end())
		mAngle = obj[L"Angle"]->AsNumber();
}

void Transform::HandleEvent(Event * pEvent)
{
	if (mpOwner->mType == HPBAR && pEvent->mType == PLAYERHP)
	{
		PlayerHPEvent *phe = static_cast<PlayerHPEvent*>(pEvent);
		mScale.x += 15.0f * phe->HPChange;
		mPosition.x += 7.5f * phe->HPChange;
	}
}

Component * Transform::Create()
{
	return new Transform();
}

