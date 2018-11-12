#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include <list>

VertexArray::VertexArray()
{
	m_Stride = 0;
	m_Offset = 0;
	m_Index  = 0;
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{

}

void VertexArray::AddLayout()
{
	for (auto c : m_Elements)
	{
		GLCall(glEnableVertexAttribArray(m_Index));
		GLCall(glVertexAttribPointer(m_Index, c.m_Count, c.m_Type, GL_FALSE, m_Stride, (const void*)m_Offset));
		m_Offset += c.m_Size * c.m_Count;
		m_Index++;
	}
}

void VertexArray::Push(unsigned int count, unsigned int type, unsigned int size)
{
	VertexElements element(count, type, size);
	m_Elements.push_back(element);
	m_Stride += count * size;

}

void VertexArray::AddBuffer(const VertexBuffer& vb) const
{
	Bind();
	vb.Bind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

VertexElements::VertexElements(unsigned int count, unsigned int type, unsigned int size) :m_Count(count), m_Type(type), m_Size(size)
{
}