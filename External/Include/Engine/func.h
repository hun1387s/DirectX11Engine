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