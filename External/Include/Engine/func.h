#pragma once

// 배열 지워주는 함수템플릿
template<typename T, int SIZE>
void Safe_Del_Array(T* (&Array)[SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		if (nullptr != Array[i])
		{
			delete Array[i];
			Array[i] = nullptr;
		}
	}
}

// Vector 지워주는 함수템플릿
template<typename T>
void Safe_Del_Vector(vector<T*>& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (nullptr != vec[i])
		{
			delete vec[i];
			vec[i] = nullptr;
		}
	}
	vec.clear();
}
