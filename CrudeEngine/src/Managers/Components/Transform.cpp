#include "Transform.h"
#include "../Events.h"
#include "../GameObject.h"

extern Shader* gpShader;
extern Matrix3D* gpProj;
extern bool PlayerIsDead;

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

	Matrix3DRotDeg(&rot, mAngle);

	Matrix3DConcat(&transform, &trans, &rot);
	Matrix3DConcat(&model, &transform, &scale);

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
	if (mpOwner->mType == HPBAR && pEvent->mType == PLAYERHIT)
	{
		PlayerHitEvent *phe = static_cast<PlayerHitEvent*>(pEvent);
		mScale.x -= 17.5f * phe->HPLost;
		mPosition.x -= 8.75f * phe->HPLost;
		if (mScale.x == 0.0f)
			PlayerIsDead = true;
	}
}

Component * Transform::Create()
{
	return new Transform();
}

