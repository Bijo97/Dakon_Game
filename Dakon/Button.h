#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class CButton{
private:
	sf::Texture textureButton;
	sf::Sprite spriteButton;
	sf::Font fontButton;
	sf::Text textButton;
public:
	CButton(){
		textureButton.loadFromFile("images/next3.png");
		spriteButton.setTexture(textureButton);
		spriteButton.setScale(1.0, 1.0);
		/*fontButton.loadFromFile("fonts/Tribalcase.otf");
		textButton.setFont(fontButton);
		textButton.setColor(sf::Color::Color(212,175,55));
		textButton.setCharacterSize(50);
		textButton.setString("Click here");
		textButton.setOrigin(textButton.getGlobalBounds().width / 2, textButton.getGlobalBounds().height / 2);
		textButton.setPosition(spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().height / 2);*/
	}
	CButton(char *nama){
		textureButton.loadFromFile("images/blood9.png");
		spriteButton.setTexture(textureButton);
		spriteButton.setScale(1.0, 1.0);
		fontButton.loadFromFile("fonts/Hanged Letters.ttf");
		textButton.setString(nama);
		textButton.setFont(fontButton);
		textButton.setColor(sf::Color::Color(240,230,140));
		textButton.setCharacterSize(60);
		textButton.setOrigin(textButton.getGlobalBounds().width / 2, (textButton.getGlobalBounds().height / 2)+15);
		textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}
	void setDir(char *dir){
		textureButton.loadFromFile(dir);
		spriteButton.setTexture(textureButton);
	}
	void draw(sf::RenderWindow &window){
		window.draw(spriteButton);
		window.draw(textButton);
	}
	void settext(char *nama){
		textButton.setString(nama);
	}
	void setPosition(float x, float y){
		spriteButton.setPosition(x, y);
		textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}
	bool isClicked(float x, float y){
		if(spriteButton.getGlobalBounds().contains(x, y)){
			return true;
		}
		return false;
	}
	float getX(){
		return spriteButton.getPosition().x;
	}
	float getY(){
		return spriteButton.getPosition().y;
	}
};