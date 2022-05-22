#pragma once
#include "Vectorr.h"
#include <iostream>

template <class Type>
class TMatrix : public TVector<TVector<Type>>
{
protected:
	
	int width;
public:
	TMatrix();
	~TMatrix();
	TMatrix(int _length);
	TMatrix(int _length, int width, Type variable);
	TMatrix(const TMatrix<Type>& _matrix);
	int GetWidth();
	int GetLength();
	TMatrix<Type> operator + (const TMatrix<Type>& _matrix);
	TMatrix<Type> operator - (const TMatrix<Type>& _matrix);
	TMatrix<Type>& operator = (const TMatrix<Type>& _matrix);
	TMatrix<Type> operator * (const TMatrix<Type>& _matrix);
	TMatrix<Type> operator * (const TVector<Type>& _vector);
	bool operator == (const TMatrix<Type>& _matrix);
	void Show();
	int  ReturnCountSimilarValues(Type variable);
	int** ReturnIJ(Type variable);
};

template<class Type>
std::ostream& operator<<(std::ostream& stream, TMatrix<Type>& _matrix)
{
	for (int q = 0; q < _matrix.GetWidth(); q++)
	{
		for (int i = 0; i < _matrix.GetLength(); i++)
			stream << _matrix[q][i] << ' ';
		stream << std::endl;
	}
	return stream;
}

template<class Type>
std::istream& operator>>(std::istream& stream, TMatrix<Type>& _matrix)
{
	Type var = 0;
	for (int q = 0; q < _matrix.GetWidth(); q++)
	{
		for (int i = 0; i < _matrix.GetLength(); i++)
		{
			stream >> var;
			_matrix[q][i] = var;
		}
	
	}
	return stream;
}

template<class Type>
inline TMatrix<Type>::TMatrix()
{
	this->length = 0;
	this->width = 0;
	this->data = 0;
}

template<class Type>
inline TMatrix<Type>::~TMatrix()
{
	if (data != 0)
	{

		/*for (int q = 0; q < width; q++)
		{
			this->data[q].~TVector();
			this->data[q] = 0;
		}*/
		
		delete[] this->data;
		this->data = 0;
	}

}

template<class Type>
inline TMatrix<Type>::TMatrix(int _length) : TVector(_length)
{
	width = _length;
	this->data = new TVector<Type>[width];
	for (int q = 0; q < width; q++)
		this->data[q] = TVector<Type>(this->length);
	this->length = _length;
}

template<class Type>
inline TMatrix<Type>::TMatrix(int _length, int _width, Type variable) : TVector( _length )
{
	width = _width;
	this->data = new TVector<Type>[width];
	for (int q = 0; q < width; q++)
		this->data[q] =  TVector<Type>(_length);
	this->length = _length;
	
	for (int q = 0; q < width; q++)
		for (int i = 0; i < this->length; i++)
			this->data[q][i] = variable;
}

template<class Type>
inline TMatrix<Type>::TMatrix(const TMatrix<Type>& _matrix)
{

	width = _matrix.width;
	this->length = _matrix.length;
	this->data = new TVector<Type>[width];
	for (int q = 0; q < width; q++)
		this->data[q] = TVector<Type>(this->length);
	this->length = _matrix.length;

	for (int q = 0; q < _matrix.width; q++)
		for (int w = 0; w < _matrix.length; w++)
			this->data[q][w] = _matrix.data[q][w];

}

template<class Type>
inline int TMatrix<Type>::GetWidth()
{
	return width;
}

template<class Type>
inline int TMatrix<Type>::GetLength()
{
	return this->length;
}

template<class Type>
inline TMatrix<Type> TMatrix<Type>::operator+(const TMatrix& _matrix)
{
	if (this->length != _matrix.length || width != _matrix.width) throw "the length or width of first matrix isn't equals to length of width of second matrix";
	TMatrix result(*this);
	for (int q = 0; q < width; q++)
		for (int w = 0; w < this->length; w++)
			result.data[q][w] = this->data[q][w] + _matrix.data[q][w];
	return result;
}

template<class Type>
inline TMatrix<Type> TMatrix<Type>::operator-(const TMatrix<Type>& _matrix)
{
	if (this->length != _matrix.length || width != _matrix.width) throw "the length or width of first matrix isn't equals to length of width of second matrix";
	TMatrix result(*this);
	for (int q = 0; q < width; q++)
		for (int w = 0; w < this->length; w++)
			result.data[q][w] = this->data[q][w] - _matrix.data[q][w];
	return result;
}

template<class Type>
inline TMatrix<Type>& TMatrix<Type>::operator=(const TMatrix<Type>& _matrix)
{
	if (this == &_matrix) return *this;
	if (this->length != _matrix.length || width != _matrix.width) throw "the length or width of first matrix isn't equals to length of width of second matrix";
	for (int q = 0; q < width; q++)
		for (int w = 0; w < this->length; w++)
			data[q][w] = _matrix.data[q][w];
	return *this;
}

template<class Type>
inline TMatrix<Type> TMatrix<Type>::operator*(const TMatrix<Type>& _matrix)
{
	if (this -> length != _matrix.width) throw "size of matriñes aren't correct";
	TMatrix<Type> result(_matrix.length, width, 0);
	
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < _matrix.length; j++)
		{
			result[i][j] = 0;
			for (int x = 0; x < this->length; x++)
				result[i][j] += this->data[i][x] * _matrix.data[x][j];
		}
	}
	return result;
}

template<class Type>
 TMatrix<Type> TMatrix<Type>::operator*(const TVector<Type>& _vector)
{
	TVector<Type> temp(_vector);
	if ((this->length) != temp.GetLength()) throw "size of matriñes aren't correct";

	TMatrix<Type> result(1, width, 0);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			result[i][j] = 0;
			for(int x = 0 ; x< this->length; x++)
				result[i][j] += this->data[i][x] * temp[x];
		}
	}
	result.Show();
	return result;
}

template<class Type>
inline bool TMatrix<Type>::operator==(const TMatrix<Type>& _matrix)
{
	if (this == &_matrix) return true;
	if (this->length != _matrix.length || width != _matrix.width) return false;
	for (int q = 0; q < width; q++)
	{
		for (int w = 0; w < this->length; w++)
			if (data[q][w] != _matrix.data[q][w]) return false;
	}
	return true;
}

template<class Type>
inline void TMatrix<Type>::Show()
{
	for (int q = 0; q < width; q++)
	{
		for (int i = 0; i < this->length; i++)
			std::cout << this->data[q][i] << ' ';
		std::cout << std::endl;
	}
}

template<class Type>
inline int TMatrix<Type>::ReturnCountSimilarValues(Type variable)
{
	int count = 0;
	for (int q = 0; q < width; q++)
		for (int w = 0; w < this->length; w++)
			if (data[q][w] == variable) count++;
	return count;
}

template<class Type>
inline int** TMatrix<Type>::ReturnIJ(Type variable)
{
	int qwerty = 0;
	int** arr = 0;
	int count = 0;
	for (int q = 0; q < width; q++)
		for (int w = 0; w < this->length; w++)
			if (data[q][w] == variable) count++;

	arr = new int*[count];
	for (int q = 0; q < count; q++)
		arr[q] = new int[2];
	
	for (int q = 0; q < width; q++)
		for (int w = 0; w < this->length; w++)
		{
			if (data[q][w] == variable)
			{
				arr[qwerty][0] = q;
				arr[qwerty][1] = w;
				std::cout << "q = " << q << ' ' << "w = " << w << std::endl;
				qwerty++;
			}
		}
	return arr;
}