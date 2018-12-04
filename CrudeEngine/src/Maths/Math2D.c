/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		Math2D.c
Purpose:		Math Functions to check for collision between point, Circle and Rectangle
Language:		C
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_2
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	10/02/2018
- End Header --------------------------------------------------------*/

#include "Math2D.h"
#include "stdio.h"

////////////////////
// From Project 1 //
////////////////////


/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{

	if (Vector2DSquareDistance(pP, pCenter) > Radius*Radius) {
		return 0;
	}
	return 1;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	float hw = Width / 2;
	float hh = Height / 2;

	float left = pRect->x - hw;
	float right = pRect->x + hw;
	float top = pRect->y + hh;
	float bottom = pRect->y - hh;

	if (pPos->x < left || pPos->x > right || pPos->y > top || pPos->y < bottom) 
	{
		return 0;
	}

	return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	float TotalRadius = Radius0 + Radius1;
	if (Vector2DSquareDistance(pCenter0, pCenter1) > TotalRadius*TotalRadius) {
		return 0;
	}
	return 1;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	float hw0, hh0, hw1, hh1;
	float left0, right0, top0, bottom0;
	float left1, right1, top1, bottom1;

	hw0 = Width0 / 2;
	hh0 = Height0 / 2;

	left0 = pRect0->x - hw0;
	right0 = pRect0->x + hw0;
	top0 = pRect0->y + hh0;
	bottom0 = pRect0->y - hh0;

	hw1 = Width1 / 2;
	hh1 = Height1 / 2;

	left1 = pRect1->x - hw1;
	right1 = pRect1->x + hw1;
	top1 = pRect1->y + hh1;
	bottom1 = pRect1->y - hh1;


	if (right0 < left1 || left0 > right1 || top0 < bottom1 || bottom0 >top1) {
		return 0;
	}
	return 1;
}

//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	return Vector2DDotProduct(&LS->mN, P) - (LS->mNdotP0);
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{
	return AnimatedCircleToStaticLineSegment(Ps, Pe, 0.0f, LS, Pi);
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	float Ti;
	Vector2D v, Tempi, P0Pi, P1Pi;
	float distS, distE, dotPro;

	distS = StaticPointToStaticLineSegment(Ps, LS);
	distE = StaticPointToStaticLineSegment(Pe, LS);

	if ( (distS > Radius && distE > Radius) || (distS < -Radius && distE < -Radius))
	{
		return -1.0;
	}

	//Vector v=Pe-Ps
	Vector2DSub(&v, Pe, Ps);

	//Intersection time Ti
	if (StaticPointToStaticLineSegment(Ps, LS) < 0) {
		Radius = -Radius;
	}
	dotPro = Vector2DDotProduct(&LS->mN, &v);
	Ti = (LS->mNdotP0 - Vector2DDotProduct(&LS->mN, Ps) + Radius) / dotPro;

	if ( dotPro == 0.0f || Ti < 0.0f || Ti > 1.0f) {
		return -1.0f;
	}

	//Temporary Intersection Point
	Vector2DScaleAdd(&Tempi, &v, Ps, Ti);

	//Check if the Path of Animated point is outside Line segment
	Vector2DSub(&P0Pi, &Tempi, &LS->mP0);
	Vector2DSub(&P1Pi, &Tempi, &LS->mP1);
	if (Vector2DDotProduct(&P0Pi, &P1Pi) > 0) {
		return -1.0;
	}

	//Set Intersection Point and return Intersection Time
	Vector2DSet(Pi, Tempi.x, Tempi.y);
	return Ti;
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	return ReflectAnimatedCircleOnStaticLineSegment(Ps, Pe, 0.0f, LS, Pi, R);
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	float Ti;
	Vector2D Vi, Temp;
	Ti = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);
	if (Ti == -1.0f) {
		return -1.0f;
	}
	Vector2DSub(&Vi, Pe, Pi);
	Vector2DScale(&Temp, &LS->mN, 2 * Vector2DDotProduct(&Vi, &LS->mN));
	Vector2DSub(R, &Vi, &Temp);
	return Ti;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{
	float Ti;
	Vector2D PsC, v, vn, P0Pi,P1Pi;
	float m, n, s;

	Vector2DSub(&PsC, Center, Ps);
	Vector2DSub(&v, Pe, Ps);
	Vector2DNormalize(&vn, &v);
	m = Vector2DDotProduct(&PsC, &vn);
	n = Vector2DSquareLength(&PsC) - (m * m);
	if (m < 0.0f || n > (Radius * Radius))
	{
		return -1.0f;
	}
	s = (float)sqrt((Radius * Radius) - n);
	Ti = (m - s) / Vector2DLength(&v);
	if (Ti < 0 || Ti > 1)
	{
		return -1.0f;
	}
	Vector2DScaleAdd(Pi, &v, Ps, Ti);
	Vector2DSub(&P0Pi, Pi, Ps);
	Vector2DSub(&P1Pi, Pi, Pe);
	if (Vector2DDotProduct(&P0Pi, &P1Pi) > 0)
	{
		Ti = (m + s) / Vector2DLength(&v);
		Vector2DScaleAdd(Pi, &v, Ps, Ti);
	}
	return Ti;
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	float Ti;
	Vector2D nC, m, tempR, v;

	Ti = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);
	if (Ti == -1.0f)
	{
		return -1.0f;
	}
	Vector2DSub(&v, Pe, Ps);
	Vector2DSub(&nC, Pi, Center );
	Vector2DNormalize(&nC, &nC);
	Vector2DSub(&m, Ps, Pi);
	Vector2DScaleSub(&tempR, &nC, &m, 2 * Vector2DDotProduct(&m, &nC));
	Vector2DNormalize(&tempR, &tempR);
	Vector2DScale(R, &tempR, Vector2DLength(&v)*(1 - Ti));
	return Ti;
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{
	return AnimatedPointToStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi);
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{
	return ReflectAnimatedPointOnStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi, R);
}

/*
 Detect collision between Circle and Rectangle
*/
int staticCircleToStaticRect(Vector2D *pCircle, float Radius, Vector2D *pRect, float Width, float Height)
{
	return StaticPointToStaticRect(pCircle, pRect, Width + 2 * Radius, Height + 2 * Radius);
}