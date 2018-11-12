/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		LineSegment2D.c
Purpose:		Math Functions to check for collision between point, Circle and Rectangle
Language:		C
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_2
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	10/02/2018
- End Header --------------------------------------------------------*/

#include "LineSegment2D.h"


int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
{
	Vector2D DirectionVec, temp;

	if (Point0->x == Point1->x && Point0->y == Point1->y) {
		return 0;
	}
	//Setting Line segment Point 0 vector
	Vector2DSet(&LS->mP0, Point0->x, Point0->y);
	//Setting Line segment Point 1 vector
	Vector2DSet(&LS->mP1, Point1->x, Point1->y);
	//Creating Direction Vector of Line segment
	Vector2DSub(&DirectionVec, Point1, Point0);
	//Normal unit vector of the Line segment
	Vector2DSet(&temp, DirectionVec.y, -DirectionVec.x);
	Vector2DNormalize(&LS->mN, &temp);
	//Dot Product of Normal and Point 0
	LS->mNdotP0 = Vector2DDotProduct(&LS->mN, Point0);
	return 1;
}