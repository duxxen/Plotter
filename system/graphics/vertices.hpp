#pragma once
#include "vertex.hpp"

namespace System
{
	enum class PrimitiveType
	{
		Points,
		Lines,
		LineStrip,
		TriangleStrip
	};

	class Vertices
	{
	public:

		Vertices();
		Vertices(size_t size);
		Vertices(PrimitiveType pt);
		Vertices(PrimitiveType pt, size_t size);
		~Vertices();

		void clear();
		void setType(PrimitiveType pt);
		void append(Vertex vertex);
		void resize(size_t size);

		PrimitiveType getType() const;
		size_t getSize() const;

		Vertex& operator[] (int i);
		const Vertex& operator[] (int i) const;

	private:

		PrimitiveType	primitiveType;
		Vertex*			vertexArray;
		size_t			size;
	};

	inline Vertices::Vertices() :
		primitiveType	{ PrimitiveType::Points },
		size			{ 0 },
		vertexArray		{ nullptr }
	{
	}

	inline Vertices::Vertices(size_t size) :
		primitiveType	{ PrimitiveType::Points },
		size			{ size },
		vertexArray		{ new Vertex[size] }
	{
	}

	inline Vertices::Vertices(PrimitiveType pt) :
		primitiveType	{ pt },
		size			{ 0 },
		vertexArray		{ nullptr }
	{
	}

	inline Vertices::Vertices(PrimitiveType pt, size_t size) :
		primitiveType	{ pt },
		size			{ size },
		vertexArray		{ new Vertex[size] }
	{
	}

	inline Vertices::~Vertices()
	{
		clear();
	}

	inline void Vertices::clear()
	{
		delete[] vertexArray;
		vertexArray = nullptr;
		size = 0;
	}

	inline void Vertices::setType(PrimitiveType pt)
	{
		primitiveType = pt;
	}

	inline void Vertices::append(Vertex vertex)
	{
		auto copy = new Vertex[size + 1];
		for (auto i = 0; i < size; i++)
			copy[i] = vertexArray[i];

		copy[size] = vertex;
		delete[] vertexArray;
		vertexArray = copy;
		size++;
	}

	inline void Vertices::resize(size_t size)
	{
		delete[] vertexArray;
		vertexArray = new Vertex[size];
		this->size = size;
	}

	inline PrimitiveType Vertices::getType() const
	{
		return primitiveType;
	}

	inline size_t Vertices::getSize() const
	{
		return size;
	}

	inline Vertex& Vertices::operator[](int i)
	{
		return vertexArray[i];
	}

	inline const Vertex& Vertices::operator[](int i) const
	{
		return vertexArray[i];
	}
}