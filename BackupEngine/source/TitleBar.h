//#pragma once
//#include <SFML/Graphics.hpp>
//#include <functional>
//#include <map>
//
//static const float TITLEBARICONSOFFSET = 5.f;
//
//enum class TitleBarPosition
//{
//	Right = 0,
//	Left
//};
//
//struct MenuItem
//{
//	sf::Text name;
//	uint32_t index = 0;
//};
//
//struct MenuButton
//{
//	sf::Vector2f position = { };
//	sf::Vector2f size = { };
//	MenuButtonColor color = { };
//
//	struct MenuButtonColor
//	{
//		sf::Color idleColor;
//		sf::Color hoverColor;
//		sf::Color clickedColor;
//	};
//
//	MenuButton();
//};
//
//class TitleBar
//{
//private:
//	sf::RenderWindow* Window = NULL;
//	sf::Texture CloseButtonTexture, ResizeButtonTexture;
//	sf::Sprite CloseButtonSprite, ResizeButtonSprite;
//	sf::RectangleShape TopMoveSpace;
//	sf::Font titleBar_font = { };
//	std::map<uint32_t, MenuItem> TitleMenu = { };
//	std::map<uint32_t, MenuButton> MenuButton = { };
//
//	std::function<void(sf::RenderWindow*)> closeFunc;
//	std::function<void(sf::RenderWindow*, sf::Event*)> resizeFunc;
//
//	TitleBarPosition Position;
//
//	void UpdatePosition();
//	void DrawMenus(sf::RenderWindow* window);
//
//public:
//	//TitleBarPosition: Right Only
//	TitleBar(std::string closebuttontexpath, std::string resizebuttontexpath, TitleBarPosition position, sf::RenderWindow* window);
//
//	void SetCallBack(std::function<void(sf::RenderWindow*)> close, std::function<void(sf::RenderWindow*, sf::Event*)> resize);
//	void UpdateInput(sf::Event* event);
//	void AddMenu(MenuItem item, uint32_t index, std::function<void()> menu_action);
//	void AddSubMenu(MenuItem item, uint32_t parent_index, uint32_t index, std::function<void()> menu_action);
//
//	void Draw(sf::RenderWindow& window);
//};
//
