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
	delete this->state;
}

void Application::Run()
{
	StateData sd;
	sd.window = this->_data.Window;
	sd.states = this->states;
	state = new DefaultState(&sd, this->_data);
	this->states = CreateRef<StateStack>(StateID::DEFAULT_STATE, state);

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
	float time = this->_dtClock.getElapsedTime().asSeconds();
	this->ts = time - m_LastFrameTime;
	m_LastFrameTime = time;
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
#if 0
	this->states->Update(this->_dt)
#else
	this->states->Update(ts);
#endif // 0
}

void Application::Render()
{
	this->_data.Window->clear();

	this->states->Render();

	this->_data.Window->display();
}
