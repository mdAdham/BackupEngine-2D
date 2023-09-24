#include "pch.h"
#include "MemoryManagement.h"
#include "gui.h"
#include "Random.h"
#include "MathLib.h"
#include "BackupEngine.h"
#include "Application.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "UserAccount.h"
#include <SFML/OpenGL.hpp>
#include "glad/glad.h"

MemoryManagement memory;

void* operator new(size_t size)
{
	memory.totalalocations += size;
	return malloc(size);
}

void operator delete(void* data, size_t size)
{
	memory.removedalocations += size;
	free(data);
}

void OnClose(sf::RenderWindow* window)
{
	window->close();
}

void OnResize(sf::RenderWindow* window, sf::Event* p_event)
{
	window->setVisible(false);
	window->create(sf::VideoMode(800, 600), "......................RenderWindow", sf::Style::Titlebar);
	window->setFramerateLimit(60);
	window->setVisible(true);
}
#include <iostream>
int main()
{
	Application app("BackupEngine", "BackupEngine_Data", sf::Vector2u(800, 600));
	app.Run();
	
	std::cout << SendMessageB() << std::endl;

	sf::ContextSettings setting;
	setting.majorVersion = 3;
	setting.minorVersion = 3;
	setting.antialiasingLevel = 1;

	Server server("UserAccount Server", "1234567890!@#$%^&*()");
	server.AddUser("BackupCookie686", USER::UT_ADMIN);
	server.AddUser("J4CN", USER::UT_ADMIN);

	sf::RenderWindow window(sf::VideoMode(850, 650, 32u), "BackupEngine", sf::Style::Resize, setting);
	window.setFramerateLimit(120);
	sf::View view;
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	bool fullscreen = false;
	sf::Event sfEvent{};
	sf::Texture CloseTexture, ReSizeTexture;
	sf::Clock clock;
	ButtonColor btnColor, sndButtonColor;

	sndButtonColor.idle = sf::Color(0, 0, 0, 50);
	sndButtonColor.hover = sf::Color(20, 20, 20, 100);
	sndButtonColor.active = sf::Color(50, 50, 50, 150);
	sndButtonColor.outlineColor = sf::Color(0, 0, 0, 20);

	TextBox textBox1(0.f, window.getSize().y - 32, window.getSize().x, 30 , 25, sf::Color(255, 255, 255, 255), sf::Color(50, 50, 50, 200), 3.f, sf::Color(150, 150, 150, 50), true);
	Button sendButton(70, 30, 0, 0, sndButtonColor, "SEND ", "Font.ttf", 18);
	SetTextBox_ButtonPos(textBox1, sendButton, TBButtonPosion::TB_RIGHT);
	sf::Font comic;
	comic.loadFromFile("Font.TTF");
	textBox1.SetFont(comic);
	textBox1.SetLimit(true, 120);

	///////////////////////////////////////////////////////
	Utility::Core::FileSystem::DataFolder gamedata("BackupEngine_Data");

	gamedata.createSubFolder("playerdata");
	gamedata.createSubFolder("leveldata");
	gamedata.SaveToFile("playerdata", "highscore.data", "1000");
	gamedata.SaveToFile("leveldata", "current_level.data", "3");

	gamedata.SaveToFile("settings.data", "sound=true");
	std::string settings = gamedata.LoadFormFile("settings.data");
	std::cout << "Settings: " << settings << std::endl;

	std::string highscore = gamedata.LoadFromFile("playerdata", "highscore.data");
	std::string currentLevel = gamedata.LoadFromFile("leveldata", "current_level.data");

	std::cout << "HighScore: " << highscore << std::endl;
	std::cout << "Current Level: " << currentLevel << std::endl;

	sf::Image testing = gamedata.LoadImageFromFile("texture", "BCS1.data");
	sf::Texture tex;
	tex.loadFromImage(testing);
	sf::Sprite sp;
	sp.setTexture(tex);

	///////////////////////////////////////////////////////
	btnColor.idle = sf::Color(0, 0, 0, 10);
	btnColor.hover = sf::Color(100, 100, 100, 50);
	btnColor.active = sf::Color(255, 255, 255, 100);

	Button button(100.f, 50.f, 50.f, 50.f,
								btnColor, "Exit", "Font.TTF", Utility::Core::Random::Int(10, 30));
	std::cout << pythagorasTheoremFindValueOfHypo(2, 4) << std::endl;

	while (window.isOpen())
	{
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed || sfEvent.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (sfEvent.type == sf::Event::TextEntered)
			{
				textBox1.TypedOn(sfEvent);
			}
			if (sfEvent.type == sf::Event::MouseButtonPressed)
			{
				textBox1.BoxClicked(sfEvent, window);
			}
			if (sfEvent.type == sf::Event::Resized)
			{
				view.setSize(sf::Vector2f(sfEvent.size.width, sfEvent.size.height));
				view.setCenter(sf::Vector2f(sfEvent.size.width, sfEvent.size.height) / 2.f);
				window.setView(view);
			}
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//window.clear();
		sf::Vector2i mouseposwindow = sf::Mouse::getPosition(window);
		button.Update(mouseposwindow);
		sendButton.Update(mouseposwindow);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
			textBox1.SetSelected(true);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sendButton.isPressed())
			textBox1.SetSelected(false);

		
		if (textBox1.getText() == "/exit" && !textBox1.IsSelected())
			window.close();
		
		window.draw(sp);
		for (auto item : button.getDrawables())
		{
			window.draw(*item);
		}
		sendButton.Render(window);
		
		if (button.isPressed())
			window.close();

		textBox1.drawText(window);

		window.display();
	}
	return 0;
}