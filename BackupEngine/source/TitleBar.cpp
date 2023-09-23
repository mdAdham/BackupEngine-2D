#include "pch.h"
//#include "TitleBar.h"
//#include <iostream>
//
//void TitleBar::UpdatePosition()
//{
//	this->TopMoveSpace.setPosition(0, 0);
//	this->TopMoveSpace.setSize(
//		sf::Vector2f(
//			Window->getSize().x,
//			CloseButtonSprite.getGlobalBounds().height + 5
//		)
//	);
//	this->TopMoveSpace.setFillColor(sf::Color(50, 50, 50, 255));
//
//	if (Position == TitleBarPosition::Right)
//	{
//		CloseButtonTexture.setSmooth(true);
//		ResizeButtonTexture.setSmooth(true);
//
//		CloseButtonSprite.setPosition(
//			Window->getSize().x - (CloseButtonSprite.getGlobalBounds().width + TITLEBARICONSOFFSET),
//			2
//		);
//		ResizeButtonSprite.setPosition(
//			Window->getSize().x - (ResizeButtonSprite.getGlobalBounds().width + CloseButtonSprite.getGlobalBounds().width + TITLEBARICONSOFFSET + 5.f),
//			2
//		);
//
//		system("cls");
//		std::cout << Window->getSize().x << " " << Window->getSize().y << std::endl;
//		std::cout << TopMoveSpace.getSize().x << " " << TopMoveSpace.getSize().y << std::endl;
//	}
//}
//
//void TitleBar::DrawMenus(sf::RenderWindow* window)
//{
//	if (!this->TitleMenu.empty())
//	{
//		for (auto& [index, menuItem] : this->TitleMenu)
//		{
//			window->draw(second);
//		}
//	}
//}
//
//void TitleBar::UpdateInput(sf::Event* event)
//{
//	//Close
//	if (this->CloseButtonSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*Window)))
//	{
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		{
//			closeFunc(this->Window);
//		}
//	}
//
//	//Resize
//	if (this->ResizeButtonSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*Window)))
//	{
//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		{
//			resizeFunc(this->Window, event);
//		}
//	}
//}
//
//void TitleBar::AddMenu(MenuItem item, uint32_t index, std::function<void()> menu_action)
//{
//	this->TitleMenu[index] = item;
//}
//
//void TitleBar::AddSubMenu(MenuItem item, uint32_t parent_index, uint32_t index, std::function<void()> menu_action)
//{
//
//}
//
//TitleBar::TitleBar(std::string closebuttontexpath, std::string resizebuttontexpath, TitleBarPosition position, sf::RenderWindow* window)
//{
//	Window = window;
//
//	CloseButtonTexture.loadFromFile(closebuttontexpath);
//	ResizeButtonTexture.loadFromFile(resizebuttontexpath);
//
//	CloseButtonSprite.setTexture(CloseButtonTexture);
//	ResizeButtonSprite.setTexture(ResizeButtonTexture);
//
//	CloseButtonSprite.setScale(.5f, .5f);
//	ResizeButtonSprite.setScale(.5f, .5f);
//
//	Position = position;
//
//	UpdatePosition();
//}
//
//void TitleBar::SetCallBack(std::function<void(sf::RenderWindow*)> close, std::function<void(sf::RenderWindow*, sf::Event*)> resize)
//{
//	this->closeFunc = close;
//	this->resizeFunc = resize;
//}
//
//void TitleBar::Draw(sf::RenderWindow& window)
//{
//	UpdatePosition();
//
//	window.draw(this->TopMoveSpace);
//	window.draw(this->CloseButtonSprite);
//	window.draw(this->ResizeButtonSprite);
//	DrawMenus(&window);
//}
