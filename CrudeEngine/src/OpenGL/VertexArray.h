/* Start Header -------------------------------------------------------

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute
of Technology is prohibited.
File Name:		VertexArray.h
Purpose:		OpenGL VertexArray Class
Platform:		Visual Studio 2017 | Visual C++ 14.1 | Windows 10 Home
Project:		CS529_sidhantt_FinalProject
Author:			Sidhant Tumma | sidhant.t | 60002218
Creation date:	12/04/2018

- End Header --------------------------------------------------------*/

#pragma once
#include <list>

class VertexBuffer;

class VertexElements
{
public:
	unsigned int m_Count;
	unsigned int m_Type;
	unsigned int m_Size;

public:
	VertexElements(unsigned int count, unsigned int type, unsigned int size);

};

class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int m_Stride;
	unsigned int m_Offset;
	unsigned int m_Index;
	std::list<VertexElements> m_Elements;

public:
	VertexArray();
	~VertexArray();

	void AddLayout();
	void AddBuffer(const VertexBuffer& vb) const;
	void Push(unsigned int count, unsigned int type, unsigned int size);
	void Bind() const;
	void Unbind() const;
};