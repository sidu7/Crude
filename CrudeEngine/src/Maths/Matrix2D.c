/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute 
of Technology is prohibited.
File Name:		Matrix2D.c 
Purpose:		Functions to perform matrix operations
Language:		C
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home                         
Project:		CS529_sidhantt_1
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	09/18/2018

- End Header --------------------------------------------------------*/

#include "Matrix2D.h"
#include<stdio.h>
#include<string.h>

#define PI      3.1415926535897932384626433832795

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	memset(pResult, 0, 9 * sizeof(float));
	pResult->m[0][0] = 1;
	pResult->m[1][1] = 1;
	pResult->m[2][2] = 1;
}



void Matrix3DIdentity(Matrix3D *pResult)
{
	memset(pResult, 0, 16 * sizeof(float));
	pResult->m[0][0] = 1;
	pResult->m[1][1] = 1;
	pResult->m[2][2] = 1;
	pResult->m[3][3] = 1;
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	int i, j;
	float temp;
	
	*pResult = *pMtx;

	for (i = 0, j = 1; i < 3; ++i) {
		temp = pResult->m[i][j];
		pResult->m[i][j] = pResult->m[j][i];
		pResult->m[j][i] = temp;
		j = (j + 1) % 3;
	}
 
}

void Matrix3DTranspose(Matrix3D * pResult, Matrix3D * pMtx)
{
	int i, j;
	float temp;

	*pResult = *pMtx;

	for (i = 0; i < 4; ++i) {
		for (j = i + 1; j < 4; ++j) {
			temp = pResult->m[i][j];
			pResult->m[i][j] = pResult->m[j][i];
			pResult->m[j][i] = temp;
		}
	}
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	int i, j, k;
	Matrix2D temp = { 0 };

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			for (k = 0; k < 3; ++k) {
				temp.m[i][j] += pMtx0->m[i][k] * pMtx1->m[k][j];
			}
		}
	}

	*pResult = temp;
}

void Matrix3DConcat(Matrix3D * pResult, Matrix3D * pMtx0, Matrix3D * pMtx1)
{
	int i, j, k;
	Matrix3D temp = { 0 };

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			for (k = 0; k < 4; ++k) {
				temp.m[i][j] += pMtx0->m[i][k] * pMtx1->m[k][j];
			}
		}
	}

	*pResult = temp;
}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;

}

void Matrix3DTranslate(Matrix3D * pResult, float x, float y, float z)
{
	Matrix3DIdentity(pResult);
	pResult->m[0][3] = x;
	pResult->m[1][3] = y;
	pResult->m[2][3] = z;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

void Matrix3DScale(Matrix3D * pResult, float x, float y, float z)
{
	Matrix3DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
	pResult->m[2][2] = z;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	Matrix2DRotRad(pResult, Angle*((float)PI / 180));
}

void Matrix3DRotDeg(Matrix3D * pResult, float Angle)
{
	Matrix3DRotRad(pResult, Angle*((float)PI / 180));
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = pResult->m[1][1] = (float)cos(Angle);
	pResult->m[1][0] = (float)sin(Angle);
	pResult->m[0][1] = (float)-sin(Angle);
}

void Matrix3DRotRad(Matrix3D * pResult, float Angle)
{
	Matrix3DIdentity(pResult);
	pResult->m[0][0] = pResult->m[1][1] = (float)cos(Angle);
	pResult->m[1][0] = (float)sin(Angle);
	pResult->m[0][1] = (float)-sin(Angle);
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	Vector2D temp;

	temp.x = pMtx->m[0][0] * pVec->x + pMtx->m[0][1] * pVec->y + pMtx->m[0][2];
	temp.y = pMtx->m[1][0] * pVec->x + pMtx->m[1][1] * pVec->y + pMtx->m[1][2];
	
	*pResult = temp;
}

/*
This function creates Orthogonal Projection matrix and saves the result in Result
function takes parameters in the following order left, right, bottom, top, zNear, zFar
*/
void Matrix3DOrtho(Matrix3D *pResult, float left, float right, float bottom, float top, float zNear, float zFar)
{

	Matrix3DIdentity(pResult);
	pResult->m[0][0] = 2.0f / (right - left);
	pResult->m[1][1] = 2.0f / (top - bottom);
	pResult->m[2][2] = -1.0f;
	pResult->m[0][3] = -(right + left) / (right - left);
	pResult->m[1][3] = -(top + bottom) / (top - bottom);
	
}

// ---------------------------------------------------------------------------