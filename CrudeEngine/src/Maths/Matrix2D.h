/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute 
of Technology is prohibited.
File Name:		Matrix2D.h 
Purpose:		Header file for Matrix2D.c
Language:		C
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home                         
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#ifndef MATRIX2D_H
#define MATRIX2D_H

#ifdef __cplusplus
extern "C" {  //only visible by C++ compiler
#endif

#include "Vector2D.h"

typedef struct Matrix2D
{
	float m[3][3];
}Matrix2D;

typedef struct Matrix3D
{
	float m[4][4];
}Matrix3D;
/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult);

void Matrix3DIdentity(Matrix3D *pResult);
/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx);

void Matrix3DTranspose(Matrix3D *pResult, Matrix3D *pMtx);

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1);

void Matrix3DConcat(Matrix3D *pResult, Matrix3D *pMtx0, Matrix3D *pMtx1);
/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y);

void Matrix3DTranslate(Matrix3D *pResult, float x, float y, float z);

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y);

void Matrix3DScale(Matrix3D *pResult, float x, float y, float z);

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle);

void Matrix3DRotDeg(Matrix3D *pResult, float Angle);

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle);

void Matrix3DRotRad(Matrix3D *pResult, float Angle);

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec);

/*
This function creates Orthogonal Projection matrix and saves the result in Result
function takes parameters in the following order left, right, bottom, top, zNear, zFar
*/
void Matrix3DOrtho(Matrix3D *pResult, float left, float right, float bottom, float top, float zNear, float zFar);

#ifdef __cplusplus
} //only visible by C++ compiler
#endif

#endif