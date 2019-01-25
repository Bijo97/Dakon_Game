#include "Dakon.h"
#include "Player.h"
#include "PowerUp.h"
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game {
private:
	cdll<Lubang> lubang;
	Lubang lubangs, lubangBesar1, lubangBesar2;
	Player player1, player2;
	PowerUp powerup;
	Papan papan;
public:
	Game(){
		lubangBesar1.setLubangBesar(0);
		lubangBesar2.setLubangBesar(0);
		lubang.addBack(lubangBesar1);
		for (int i = 0; i < 7; i++){
			lubang.addBack(lubangs);
		}
		lubang.addBack(lubangBesar2);
		for (int i = 0; i < 7; i++){
			lubang.addBack(lubangs);
		}
		/*texture.loadFromFile("images/papan.jpg");
		sprite.setTexture(texture);
		sprite.setPosition(10, 10);*/
	}

	void setNamaPlayer1(string _nama){
		player1.setNama(_nama);
	}

	void setNamaPlayer2(string _nama){
		player2.setNama(_nama);
	}

	void play(){
		
	}
};