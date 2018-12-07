#pragma once

template <class T>
class singleton
{
private:
	static T * instance;

public:
	static T * GetInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	}

	static void ReleaseInstance()
	{
		if (instance)
			delete instance;

		instance = nullptr;
	}
};

template <class T>
T * singleton<T>::instance = nullptr;