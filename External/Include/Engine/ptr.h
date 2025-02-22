#pragma once


template<typename T>
class Ptr
{
private:
	T* Asset;


public:
	T* Get() { return Asset; }
	T** GetAdressOf() { return &Asset; }


	void operator = (T* asset)
	{
		if (nullptr != Asset)
			Asset->Release();

		Asset = asset;

		if (nullptr != Asset)
			Asset->AddRef();
	}

	void operator = (const Ptr<T>& ptr)
	{
		if (nullptr != Asset)
			Asset->Release();

		Asset = ptr.asset;

		if (nullptr != Asset)
			Asset->AddRef();
	}


	T* operator->()
	{
		return Asset;
	}

public:
	Ptr()
		:Asset(nullptr)
	{

	}
	Ptr(T* asset)
		: Asset(asset)
	{
		if (nullptr != Asset)
			Asset->AddRef();
	}

	Ptr(const Ptr<T>& ptr)
		: Asset(ptr.Asset)
	{
		if (nullptr != Asset)
			Asset->AddRef();
	}


	~Ptr()
	{
		if (nullptr != Asset)
			Asset->Release();
	}
};