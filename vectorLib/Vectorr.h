#pragma once
#include<iostream>
#include<fstream>

template<class Type>
class TVector
{
protected:
	Type* data;
	int length;

public:
	
	TVector(int _length = 0);
	TVector(const TVector<Type>& _vector);
	~TVector();
	Type GetLength();
	Type PopBack();
	void PushBack(Type variable);
	Type& operator[](int number);
	TVector<Type> operator + (const TVector<Type>& _vector);
	TVector<Type> operator - (const TVector<Type>& _vector);
	TVector<Type> operator / (const TVector<Type>& _vector);
	TVector<Type>& operator = (const TVector<Type>& _vector);
	TVector<Type> operator *(const TVector<Type>& _vector);
	Type ScalarMult(const TVector<Type>& FirstVector, const TVector<Type>& SecondVector);
	void ReSize(int NewLength = 1);
	bool operator == (const TVector<Type>& _vector);
	//допы задания
	int ReturnCountSimilarValues(Type variable);
	int* ReturnIJ(Type variable);
	
}; 



template<class Type>
std::istream& operator>>(std::istream& stream, TVector<Type>& _vector)
{

	int count = 0;
	stream >> count;
	Type variable = 0;
	int length = _vector.GetLength();
	_vector.ReSize(0);
	
	variable = 0;
	for (int q = 0; q < count; q++)
	{
		stream >> variable;
		_vector.PushBack(variable);
	}
	return stream;
}

template<class Type>
std::ostream& operator<<(std::ostream& stream, TVector<Type>& _vector)
{
	for (int q = 0; q < _vector.GetLength(); q++)
	{
		stream << _vector[q] << ' ';
	}
	return stream;
}

template<class Type>
inline TVector<Type>::TVector(int _length)
{
	data = 0;
	data = new Type[_length];
	length = _length;
}
template <class Type>
inline TVector<Type>::TVector(const TVector<Type>& _vector)
{
	if (_vector.data == 0) throw "varriable of vector is empty!";
	else
	{		
		if (data != 0)
		{
			data = 0;
			delete[] data;
			data = 0;
			data = new Type[_vector.length];
		}
		else		
			data = new Type[_vector.length];
		length = _vector.length;
		for (int q = 0; q < length; q++)
		{
			data[q] = _vector.data[q];
		}
	}
}

template<class Type>
inline TVector<Type>::~TVector()
{
	if (data != 0) delete[] data;
	data = 0;
}

template<class Type>
inline Type TVector<Type>::GetLength()
{
	return length;
}

template<class Type>
inline Type TVector<Type>::PopBack()
{
	if (length <= 0) { throw"vector is empty"; }
	else
	{
		Type* temporary = new Type[length];
		for (int i = 0; i < length; i++)
		{
			temporary[i] = data[i];
		}
		Type variable = data[length - 1];

	
		delete[] data;
		data = 0;
		data = new Type[length - 1];
		length--;
		for (int q = 0; q < length ; q++)
		{
			data[q] = temporary[q];
		}
		temporary = 0;
		delete[] temporary;
		temporary = 0;

		return variable;
	}
}

template<class Type>
inline void TVector<Type>::PushBack(Type variable)
{

		Type* temporary = new Type[length];
		for (int i = 0; i < length; i++)
		{
			temporary[i] = data[i];
		}
	
		delete[] data;
		data = 0;
		data = new Type[length + 1];
		for (int i = 0; i < length; i++)
		{
			data[i] = temporary[i];
		}
		data[length] = variable;
		length++;
	
}

template<class Type>
inline Type& TVector<Type>::operator[](int number)
{
	return data[number];
}

template<class Type> 
TVector<Type> TVector<Type>::operator+ (const TVector<Type>& _vector)
{
	if (_vector.data == 0 && _vector.length < 0) throw "empty variable";
	if (_vector.length != this->length) throw "length of 1-st vector isn't equals to the 2-d vector";
	else
	{
		TVector<Type> result(*this);
		for (int q = 0; q < length; q++)
		{
			result.data[q] = (this->data[q]) + _vector.data[q];
		}

		return result;
	}
}

template<class Type>
TVector<Type> TVector<Type>::operator-(const TVector<Type>& _vector)
{
	if (_vector.data == 0 && _vector.length < 0) throw "empty variable";
	if (_vector.length != this->length) throw "length of 1-st vector isn't equals to the 2-d vector";
	else
	{
		TVector<Type> result(*this);
		for (int q = 0; q < length; q++)
		{
			result.data[q] = (this->data[q]) - _vector.data[q];
		}

		return result;
	}
}

template<class Type>
TVector<Type> TVector<Type>::operator/(const TVector<Type>& _vector)
{
	if (_vector.data == 0 && _vector.length < 0) throw "empty variable";
	if (_vector.length != this->length) throw "length of 1-st vector isn't equals to the 2-d vector";
	else
	{
		TVector<Type> result(*this);
		for (int q = 0; q < length; q++)
		{
			if (_vector.data[q] != 0)
				result.data[q] = (this->data[q]) / _vector.data[q];
			else throw "division by zero";
		}

		return result;
	}
}

template<class Type>
inline TVector<Type>& TVector<Type>::operator=(const TVector<Type>& _vector)
{
	if(data == 0 ) data  = new Type[_vector.length];
	else if (data != 0)
	{

		delete[] data;
		data = 0;
		data = new Type[_vector.length];
	}

	length = _vector.length;
	for (int q=0; q < length; q++)
	{
		data[q] = _vector.data[q];
	}
	return *this;
}

template<class Type>
inline TVector<Type> TVector<Type>::operator*(const TVector<Type>& _vector)
{
	if (_vector.length != length) throw "Error!";
	TVector<Type> result(*this);
	for (int q = 0; q < result.length; q++)
	{
		result.data[q] = result.data[q] * _vector.data[q];
	}
	return result;
}

template<class Type>
inline Type TVector<Type>::ScalarMult(const TVector<Type>& FirstVector, const TVector<Type>& SecondVector)
{
	Type result = 0;
	if (FirstVector.length != SecondVector.length) throw "Error";
	for (int q = 0; q < FirstVector.length; q++)
		result += FirstVector.data[q] * SecondVector.data[q];
	return result;
}

template<class Type>
inline void TVector<Type>::ReSize(int NewLength)
{
	if (NewLength < 0) throw "The new length (or equals) less than zero";
	if (NewLength >= 0)
	{
		Type* temporary = new Type[NewLength];
		for (int q = 0; q < NewLength; q++)
		{
			temporary[q] = data[q];
		}

	
		delete[] data;
		data = 0;

		data = new Type[NewLength];
		length = NewLength;

		for (int q = 0; q < length; q++)
			data[q] = temporary[q];
		temporary = 0;
		delete[] temporary;
		temporary = 0;
	}

}

template<class Type>
inline bool TVector<Type>::operator==(const TVector<Type>& _vector)
{
	if (length != _vector.length) return false;
	for (int q = 0; q < length; q++)
	{
		if (data[q] != _vector.data[q]) return false;
	}
	return true;
}

template<class Type>
inline int TVector<Type>::ReturnCountSimilarValues(Type variable)
{
	int count = 0;
	for (int i = 0; i < length; i++)
		if (data[i] == variable)
			count++;
	return count;
}

template<class Type>
inline int* TVector<Type>::ReturnIJ(Type variable)
{
	int qwerty = 0;
	int* array = 0;
	int count = 0;
	for (int i = 0; i < length; i++)
		if (data[i] == variable)
			count++;
	array = new int[count];
	for (int q = 0; q < length; q++)
	{
		if (data[q] == variable)
		{
			array[qwerty] = q;
			qwerty++;
		}
	}
	return array;
}
