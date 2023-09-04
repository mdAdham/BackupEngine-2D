#pragma once
#include <string>
#include <SFML/Network.hpp>
#include <map>
#include <iostream>

template<class KEY, class DTYPE>
class DataBase
{
private:
	std::map<KEY, DTYPE> m_data;
	std::string m_password = "1234567890!@#$%^&*()";
public:
	DataBase()
	{

	}

	void AddData(KEY key, DTYPE data)
	{
		this->m_data[key] = data;
	}

	void UpdateData(KEY key, DTYPE type)
	{
		m_data[key] = type;
	}

	DTYPE GetData(KEY key)
	{
		return this->m_data[key];
	}

	//Correct Password to Clear the database
	void Clear(std::string password)
	{
		if (password == m_password)
		{
			m_data.clear();
		}
	}
};

class Server
{
	
};

std::string SendMessageB()
{
	DataBase<std::string, std::string> mobileNumber;
	mobileNumber.AddData("Adham", "9597998429");
	mobileNumber.UpdateData("Adham", "9286542910");
	return mobileNumber.GetData("Adham");
}