#include "Application.h"

Application::Application(std::string appName, std::string appDataFolder, sf::Vector2u windowSize)
{
	this->_data.datafolder = new Utility::Core::FileSystem::DataFolder(appDataFolder);
	this->_data.Window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), appName);
	this->_data.Window->setVerticalSyncEnabled(true);
	this->appIcon = this->_data.datafolder->LoadImageFromFile("texture", "icon1.data");
	this->_data.Window->setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());
	this->running = true;
}

Application::~Application()
{
	delete this->_data.datafolder;
	delete this->_data.Window;
}

void Application::Run()
{
	StateData sd;
	sd.window = this->_data.Window;
	sd.states = this->states;
	state = new DefaultState(&sd, this->_data);

	this->states.push(state);
	while (running)
	{
		while (this->_data.Window->isOpen())
		{
			UpdateDt();
			UpdateSFMLEvents();
			Update();
			Render();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			running = false;
	}
}

void Application::UpdateDt()
{
	this->_dt = this->_dtClock.restart().asSeconds();
}

void Application::UpdateSFMLEvents()
{
	while (this->_data.Window->pollEvent(this->_data.sfEvent))
	{
		if (this->_data.sfEvent.type == sf::Event::Closed)
			this->_data.Window->close();
	}
}

void Application::Update()
{
	this->states.top()->Update(_dt);
}

void Application::Render()
{
	this->_data.Window->clear();

	this->states.top()->Render();

	this->_data.Window->display();
}
