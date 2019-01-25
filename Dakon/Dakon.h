#include "LinkedList.h"
#include <time.h>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Biji {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	bool status;
public:
	Biji() {
		texture.loadFromFile("images/biji1.png");
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
		status = false;
	}
	sf::Sprite getSprite() {
		return sprite;
	}
	bool getStatus() {
		return status;
	}
	void setPosition(double x, double y) {
		sprite.setPosition(x, y);
		status = true;
	}
	void Rotate(double degree) {
		sprite.rotate(degree);
	}
	void setOrigin(double x, double y) {
		sprite.setOrigin(x, y);
	}
	void setScale(double x, double y) {
		sprite.setScale(x, y);
	}
	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
	}
};

class Lubang {
private:
	Biji biji[100];
	bool besar, status, pos;
	int jumlah, nomor;
	char temp[100];
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Font font;
	sf::Text jmlbiji;
public:
	Lubang(){
		srand(time(NULL));
		status = true;
		besar = false;
		jumlah = 7;
		texture.loadFromFile("images/lubang.png");
		sprite.setTexture(texture);
		font.loadFromFile("fonts/ARLRDBD.ttf");
		jmlbiji.setCharacterSize(25);
		jmlbiji.setFont(font);
	}
	void setNomor(int x) {
		nomor = x;
	}
	int getNomor() {
		return nomor;
	}
	sf::Sprite getSprite() {
		return sprite;
	}
	void setTexture(char *path) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}
	void setPos(bool a){
		pos = a;
	}
	void setScale(double x, double y) {
		sprite.setScale(x, y);
	}
	void setPosition(double posx, double posy) {
		position.x = posx;
		position.y = posy;
		sprite.setPosition(position);
	}
	void setLubangBesar(){
		jumlah = 0;
		besar = true;
	}
	void addBiji(){
		jumlah++;
	}
	void addBiji(int x) {
		jumlah += x;
	}
	bool getPos(){
		return pos;
	}
	int getBiji(){
		int temp = jumlah;
		jumlah = 0;
		return temp;
	}
	int cekBiji(){
		return jumlah;
	}
	void disable() {
		status = false;
	}
	void setJumlah(int x) {
		jumlah = x;
	}
	sf::Vector2f getPosition() {
		sf::Vector2f pos;
		pos.x = position.x;
		pos.y = position.y;
		return pos;
	}
	void setOrigin(double x, double y) {
		sprite.setOrigin(x, y);
	}
	void draw(sf::RenderWindow &window) {
		if (!pos) jmlbiji.setPosition(position.x - sprite.getGlobalBounds().width/2, position.y - sprite.getGlobalBounds().height/2);
		else jmlbiji.setPosition(position.x + sprite.getGlobalBounds().width/2 - 20, position.y + sprite.getGlobalBounds().height/2 - 20);
		sprintf(temp, "%d", jumlah);
		jmlbiji.setString(temp);
		window.draw(sprite);
		for (int i=0; i<jumlah; i++) {
			if (!biji[i].getStatus()) {
				int degree = rand () % 361;
				int xbiji = rand () % 30 + (position.x - 10);
				int ybiji = rand () % 30 + (position.y - 10);
				biji[i].Rotate((double)degree);
				biji[i].setPosition((double)xbiji, (double)ybiji);
			}
			biji[i].draw(window);
		}
		window.draw(jmlbiji);
	}
	bool getStat() {
		return status;
	}
	bool Besar() {
		return besar; 
	}
	bool isClicked(float x, float y){
		if(sprite.getGlobalBounds().contains(x, y)){
			return true;
		}
		return false;
	}
};

class Papan {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
public:
	Papan() {
		texture.loadFromFile("images/papan.jpg");
		sprite.setTexture(texture);
	}
	void setPosition(double posx, double posy) {
		position.x = posx;
		position.y = posy;
		sprite.setPosition(position);
	}
	sf::Sprite getSprite() {
		return sprite;
	}
	void setOrigin(double x, double y) {
		sprite.setOrigin(x, y);
	}
	void setScale(double x, double y) {
		sprite.setScale(x, y);
	}
	void draw(sf::RenderWindow &window) {
		window.draw(sprite);
	}
};

