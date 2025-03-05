#pragma once

template<typename T>
class CSingleton
{
private:
	typedef void(*DESTROY)(void);

private:
	static T* _this;

public:
	static T* GetInst()
	{
		if (nullptr == _this)
		{
			_this = new T;
		}

		return _this;
	}

	static void Destroy()
	{
		if (nullptr != _this)
		{
			delete _this;
			_this = nullptr;
		}
	}

protected:
	CSingleton()
	{
		atexit((DESTROY)&CSingleton<T>::Destroy);
	};
	CSingleton(const CSingleton& _other) = delete;
	~CSingleton()
	{
	};
};

template<typename T>
T* CSingleton<T>::_this = nullptr;
