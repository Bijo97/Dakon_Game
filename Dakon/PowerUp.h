#include <iostream>
using namespace std;

class Powerup {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
public:
	Powerup() {
		texture.loadFromFile("images/powerup.png");
		sprite.setTexture(texture);
		sprite.setScale(0.1, 0.1);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	}
	void setPosition(double x, double y) {
		sprite.setPosition(x, y);
	}
	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
	}
	bool isClicked(float x, float y){
		if(sprite.getGlobalBounds().contains(x, y)){
			return true;
		}
		return false;
	}
};