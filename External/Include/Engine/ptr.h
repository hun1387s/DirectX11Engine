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
			this->Asset->Release();

		this->Asset = asset;

		if (nullptr != Asset)
			this->Asset->AddRef();
	}

	void operator = (const Ptr<T>& ptr)
	{
		if (nullptr != Asset)
			this->Asset->Release();

		this->Asset = ptr.Asset;

		if (nullptr != Asset)
			this->Asset->AddRef();
	}


	T* operator->()
	{
		return this->Asset;
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
