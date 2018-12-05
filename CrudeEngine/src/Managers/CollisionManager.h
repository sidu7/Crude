/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		CollisionManager.h
Purpose:		Header file for Collision Manager
Language:		C++
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

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