#include "CollisionManager.h"
#include "../Maths/Math2D.h"

Shape::Shape(ShapeType Type)
{
	mType = Type;
	mpOwnerBody = nullptr;
}

ShapeCircle::ShapeCircle(float radius) :Shape(CIRCLE)
{
	mRadius = radius;
}

ShapeCircle::~ShapeCircle()
{

}

bool ShapeCircle::TestPoint(float PointX, float PointY)
{
	return false;
}

//TODO: Change it to width and height
ShapeAABB::ShapeAABB(float left, float top, float right, float bottom) :Shape(RECTANGLE)
{
	mTop = top;
	mBottom = bottom;
	mLeft = left;
	mRight = right;
}

ShapeAABB::~ShapeAABB()
{

}

bool ShapeAABB::TestPoint(float PointX, float PointY)
{
	return false;
}

Contact::Contact()
{
	mBodies[0] = mBodies[1] = nullptr;
}


bool checkCollisionCircleCircle(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{

	//Intersection!!!
	ShapeCircle *p1 = static_cast<ShapeCircle*>(pShape1);
	Vector2D Pos1;
	Vector2DSet(&Pos1, Pos1X, Pos1Y);
	ShapeCircle *p2 = static_cast<ShapeCircle*>(pShape2);
	Vector2D Pos2;
	Vector2DSet(&Pos2, Pos2X, Pos2Y);
	
	if (StaticCircleToStaticCircle(&Pos1, p1->mRadius, &Pos2, p2->mRadius))
	{
		//Create a new contact and add to the contacts list
		Contact *pNewContact = new Contact();
		pNewContact->mBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mBodies[1] = pShape2->mpOwnerBody;
		Contacts.push_back(pNewContact);

		return true;
	}

	return false;
}

bool checkCollisionCircleAABB(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	//Intersection!!!
	ShapeCircle *p1 = static_cast<ShapeCircle*>(pShape1);
	Vector2D Pos1;
	Vector2DSet(&Pos1, Pos1X, Pos1Y);
	ShapeAABB *p2 = static_cast<ShapeAABB*>(pShape2);
	Vector2D Pos2;
	Vector2DSet(&Pos2, Pos2X, Pos2Y);

	if (staticCircleToStaticRect(&Pos1, p1->mRadius, &Pos2, p2->mTop, p2->mLeft))
	{
		//Create a new contact and add to the contacts list
		Contact *pNewContact = new Contact();
		pNewContact->mBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mBodies[1] = pShape2->mpOwnerBody;
		Contacts.push_back(pNewContact);

		return true;
	}

	return false;
}
bool checkCollisionAABBAABB(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{

	//Intersection!!!
	ShapeAABB *p1 = static_cast<ShapeAABB*>(pShape1);
	Vector2D Pos1;
	Vector2DSet(&Pos1, Pos1X, Pos1Y);
	ShapeAABB *p2 = static_cast<ShapeAABB*>(pShape2);
	Vector2D Pos2;
	Vector2DSet(&Pos2, Pos2X, Pos2Y);

	if (StaticRectToStaticRect(&Pos1, p1->mTop, p1->mLeft, &Pos2, p2->mTop, p2->mLeft))
	{
		//Create a new contact and add to the contacts list
		Contact *pNewContact = new Contact();
		pNewContact->mBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mBodies[1] = pShape2->mpOwnerBody;
		Contacts.push_back(pNewContact);

		return true;
	}

	return false;
}
bool checkCollisionAABBCircle(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	return checkCollisionCircleAABB(pShape2, Pos2X, Pos2Y, pShape1, Pos1X, Pos1Y, Contacts);
}

CollisionManager::CollisionManager()
{
	CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = checkCollisionCircleCircle;
	CollisionFunctions[Shape::CIRCLE][Shape::RECTANGLE] = checkCollisionCircleAABB;
	CollisionFunctions[Shape::RECTANGLE][Shape::RECTANGLE] = checkCollisionAABBAABB;
	CollisionFunctions[Shape::RECTANGLE][Shape::CIRCLE] = checkCollisionAABBCircle;
}

CollisionManager::~CollisionManager()
{
	Reset();
}

void CollisionManager::Reset()
{
	for (auto c : mContacts)
		delete c;
	mContacts.clear();
}

bool CollisionManager::checkCollisionAndGenerateContact(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, Pos1X, Pos1Y, pShape2, Pos2X, Pos2Y, Contacts);
}
