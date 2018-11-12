#pragma once
#include<list>

class Body;

class Shape
{
public:
	enum ShapeType
	{
		CIRCLE,
		RECTANGLE,
		NUM
	};

	Shape(ShapeType Type);
	virtual ~Shape() {}

	virtual bool TestPoint(float PointX, float PointY) = 0;

public:
	Body *mpOwnerBody;
	ShapeType mType;
};

//-----------------------------------------------------------------------------

class ShapeCircle : public Shape
{
public:
	ShapeCircle(float radius);
	~ShapeCircle();

	bool TestPoint(float PointX, float PointY);

public:
	float mRadius;
};


class ShapeAABB : public Shape
{
public:
	ShapeAABB(float left, float top, float right, float bottom);
	~ShapeAABB();

	bool TestPoint(float PointX, float PointY);

public:
	float mTop, mBottom, mRight, mLeft;
};


class Contact
{
public:
	Contact();
	~Contact() {}
public:
	Body *mBodies[2];

};


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Reset();
	bool checkCollisionAndGenerateContact(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts);

public:
	std::list<Contact *> mContacts;

private:
	//2D array of function pointers, used to store the collision function pointers
	bool (*CollisionFunctions[Shape::NUM][Shape::NUM])(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts);
	
};