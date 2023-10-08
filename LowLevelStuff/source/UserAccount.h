#pragma once
#include <string>
#include <SFML/Network.hpp>
#include <map>
#include <iostream>

class Server;
template<class KEY, class DTYPE>
class DataBase
{
private:
	std::map<KEY, DTYPE> m_data;
	std::string m_password = "1234567890!@#$%^&*()";

	friend Server;
public:
	DataBase()
	{

	}

	void AddData(KEY key, DTYPE data)
	{
		if (this->m_data.contains(key))
			throw("Alredy has the key, try to updating the data");
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

enum user_type
{
	UT_DEFAULT, UT_ADMIN, UT_PREMIUM
};

using USER = user_type;

class Server
{
private:
	DataBase<std::string, USER> userData;
	std::string name = "Server";
	sf::Clock serverClock;

public:
	Server(std::string servername, std::string databasePassword)
	{
		this->serverClock.restart();
		this->userData.m_password = databasePassword;
	}

	void AddUser(std::string name, USER user)
	{
		this->userData.AddData(name, user);
	}

	USER GetUserLevel(std::string name) { return this->userData.GetData(name); }

	void OnUpdate()
	{
		
	}
};

std::string SendMessageB()
{
	DataBase<std::string, std::string> mobileNumber;
	mobileNumber.AddData("Adham", "9597998429");
	mobileNumber.UpdateData("Adham", "9286542910");
	return mobileNumber.GetData("Adham");
}