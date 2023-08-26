#include "MemoryManagement.h"
#include "gui.h"
#include "Random.h"
#include "MathLib.h"
#include "BackupEngine.h"
#include "Application.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 

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

	sf::ContextSettings setting;
	setting.majorVersion = 3;
	setting.minorVersion = 3;
	setting.antialiasingLevel = 1;

	sf::RenderWindow window(sf::VideoMode(800, 600), "BackupEngine", sf::Style::Resize, setting);
	window.setFramerateLimit(60);
	sf::Event sfEvent{};
	sf::Texture CloseTexture, ReSizeTexture;
	sf::Clock clock;
	ButtonColor btnColor;

	TextBox textBox1(50, sf::Color::Blue, true);
	sf::Font comic;
	comic.loadFromFile("Font.TTF");
	textBox1.SetFont(comic);
	textBox1.SetPosition(sf::Vector2f(5, 100));
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
		}
		window.clear();
		sf::Vector2i mouseposwindow = sf::Mouse::getPosition(window);
		button.Update(mouseposwindow);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
			textBox1.SetSelected(true);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			textBox1.SetSelected(false);

		if (textBox1.getText() == "/exit" && !textBox1.IsSelected())
			window.close();

		window.draw(sp);
		for (auto item : button.getDrawables())
		{
			window.draw(*item);
		}
		
		if (button.isPressed())
			window.close();

		textBox1.drawText(window);
		sf::ContextSettings set;
		//button.Render(window);
		window.display();
	}
	return 0;
}