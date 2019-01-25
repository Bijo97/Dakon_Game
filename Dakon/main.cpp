#include <SFML/Graphics.hpp>
#include "Dakon.h"
#include "Player.h"
#include "PowerUp.h"
#include "Button.h"
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string.h>
#include <math.h>

int windowWidth = 1366, windowHeight = 768, indexlubang = 15, indexlubang2 = 7, counterpu1 = 0, counterpu2 = 0;
bool turn = true, cekmikul = false, ambil = false, player1kosong = false, player2kosong = false, player1win = false, player2win = false, powerup1 = false, powerup2 = false, cekrestart = false, audiowin = false, audiotembak = false, audiomikul = false, audiopowerup = false;
double batas = 0.75;
node<Lubang> *mikulll;
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Dakon", sf::Style::Fullscreen);
sf::Sprite splayer1, splayer2;
sf::Texture tplayer1, tplayer2;
sf::Font font;
sf::Text turnplayer;
sf::SoundBuffer bufferwin, buffermikul, buffertembak, bufferpowerup;
sf::Sound suarawin, soundmikul, soundtembak, soundpowerup;
bool status[17];

void menu();
void how();
void next();
void next1();
void next2();
void next3();
void next4();
void next5();
void next6();
void next7();
void next8();
void next9();

void playAudioWin(){
	audiowin = true;
	bufferwin.loadFromFile("fx/win.ogg");
	suarawin.setBuffer(bufferwin);
	suarawin.setVolume(80);
	suarawin.play();
}

void playAudioTembak(){
	audiotembak = true;
	buffertembak.loadFromFile("fx/tembak.ogg");
	soundtembak.setBuffer(buffertembak);
	soundtembak.setVolume(30);
	soundtembak.play();
} 

void playAudioMikul(){
	buffermikul.loadFromFile("fx/mikul.ogg");
	soundmikul.setVolume(200);
	soundmikul.setBuffer(buffermikul);
	soundmikul.play();
	audiomikul = true;
}

void playAudioPowerup(){
	bufferpowerup.loadFromFile("fx/powerup.wav");
	soundpowerup.setVolume(200);
	soundpowerup.setBuffer(bufferpowerup);
	soundpowerup.play();
	audiopowerup = true;
}

void restart() {
	indexlubang = 15;
	indexlubang2 = 7;
	counterpu1 = 0;
	counterpu2 = 0;
	batas = 0.75;
	turn = true;
	cekmikul = false;
	ambil = false;
	player1kosong = false;
	player2kosong = false;
	player1win = false;
	player2win = false;
	powerup1 = false;
	powerup2 = false;
	audiowin = false;
}

void changeTurn(){
	if (turn == true && player1kosong){
		turn = false;
	} else if (turn == false && player2kosong){
		turn = true;
	}
}

void drawPowerup(cdll<Lubang> lubang) {
	node<Lubang> *i = lubang.getHead();
	if (i->getD()->cekBiji() % 20 == 0 && i->getD()->cekBiji() > 0 && !cekmikul) powerup2 = true;
	else powerup2 = false;
	while (i->getD()->getNomor() != 9) {
		i = i->getNext();
	}
	if (i->getD()->cekBiji() % 20 == 0 && i->getD()->cekBiji() > 0 && !cekmikul) powerup1 = true;
	else powerup1 = false;
}

//fungsi untuk return nomer depan
int getFront(int angka) {
	if (angka == 2) return 16;
	else if (angka == 3) return 15;
	else if (angka == 4) return 14;
	else if (angka == 5) return 13;
	else if (angka == 6) return 12;
	else if (angka == 7) return 11;
	else if (angka == 8) return 10;
	else if (angka == 10) return 8;
	else if (angka == 11) return 7;
	else if (angka == 12) return 6;
	else if (angka == 13) return 5;
	else if (angka == 14) return 4;
	else if (angka == 15) return 3;
	else if (angka == 16) return 2;
}

double getBatas() {
	return batas;
}

void deleteLubang(cdll<Lubang> lubang) {
	if ((turn && counterpu1 >= 6) || (!turn && counterpu2 >= 6)){
		return;
	}
	node<Lubang> *i = lubang.getHead();
	node<Lubang> *p1 = lubang.getHead();
	node<Lubang> *p2 = lubang.getHead();
	while (p1->getD()->getNomor() != 9) {
		p1 = p1->getNext();
	}
	int j = 0;
	playAudioPowerup();
	if (turn) {
		while (j != indexlubang2) {
			i = i->getNext();
			j++;
		}
		if (i->getD()->cekBiji() > 0) {
			double tempp = i->getD()->getBiji();
			p1->getD()->addBiji(ceil(tempp / 2));
			p2->getD()->addBiji(tempp - (ceil(tempp / 2)));
		}
		lubang.delIndex(indexlubang2);
		status[indexlubang2] = false;
		indexlubang2--;
		counterpu1++;
	}
	else {
		while (j != indexlubang) {
			i = i->getNext();
			j++;
		}
		if (i->getD()->cekBiji() > 0) {
			double tempp = i->getD()->getBiji();
			p2->getD()->addBiji(ceil(tempp / 2));
			p1->getD()->addBiji(tempp - (ceil(tempp / 2)));
		}
		lubang.delIndex(indexlubang);
		status[indexlubang] = false;
		counterpu2++;
	}
	indexlubang--;
}

void drawWinner(cdll<Lubang> lubang){
	node<Lubang> *temp1 = lubang.getHead();
	node<Lubang> *temp2 = lubang.getHead();

	/*if (player1kosong == true && turn == true){
	while (temp2->getD()->getNomor() != 9){
	temp2 = temp2->getNext();
	}
	do {
	if (temp1->getD()->getNomor() > 9){
	temp2->getD()->addBiji(temp1->getD()->getBiji());
	cout<<"Sabar ya mas 1..."<<endl;
	}
	temp1 = temp1->getNext();
	} while (temp1->getD()->getNomor() < 16);
	} else if (player2kosong == true && turn == false){
	do {
	if (temp1->getD()->getNomor() > 1 && temp1->getD()->getNomor() < 9){
	cout<<"Sabar ya mas 2..."<<endl;
	temp2->getD()->addBiji(temp1->getD()->getBiji());
	}
	temp1 = temp1->getNext();
	} while (temp1->getD()->getNomor() < 16);
	}*/

	if (player1kosong == true && player2kosong == true){
		temp1 = lubang.getHead();
		temp2 = lubang.getHead();

		while (temp1->getD()->getNomor() != 9){
			temp1 = temp1->getNext();
		}

		if (temp1->getD()->cekBiji() > temp2->getD()->cekBiji()){
			player1win = true;
			player2win = false;
		} else if (temp1->getD()->cekBiji() < temp2->getD()->cekBiji()){
			player2win = true;
			player1win = false;
		} else {
			player1win = true;
			player2win = true;
		}
	}
}

void cekLubang(cdll<Lubang> lubang) {
	node<Lubang> *i = lubang.getHead();
	do {
		if (i->getD()->getNomor() > 1 && i->getD()->getNomor() <= indexlubang2 + 1){
			if (i->getD()->cekBiji() == 0 && !i->getD()->Besar()) {
				player2kosong = true;
			}
			else {
				player2kosong = false;
				while (i->getD()->getNomor() != 9){
					i = i->getNext();
				}
			}
		} else if (i->getD()->getNomor() > 9 && i->getD()->getNomor() <= 16){
			if (i->getD()->cekBiji() == 0 && !i->getD()->Besar()) {
				player1kosong = true;
			}
			else {
				player1kosong = false;
				break;
			}
		}
		i = i->getNext();
	} while (i != lubang.getHead());
}

void nembak (int nomor, node<Lubang> *temp, node<Lubang> *counter) {
	node<Lubang> *temps = temp;
	int dummy = getFront(nomor);
	while (temp->getD()->getNomor() != dummy) {
		temp = temp->getNext();
	}
	if (turn) {
		while (temps->getD()->getNomor() != 9) {
			temps = temps->getNext();
		}
	}
	if (temp->getD()->cekBiji() > 0) {
		playAudioTembak();
		temps->getD()->addBiji(temp->getD()->getBiji());
		temps->getD()->addBiji(counter->getD()->getBiji());
	}
}

void drawLubang(sf::RenderWindow &window, Papan &papan, cdll<Lubang> lubang, int ambilbiji=0) {
	papan.draw(window);
	node<Lubang> *temp;
	temp = lubang.getHead();
	do {
		temp->getD()->draw(window);
		temp = temp->getNext();
	} while (temp != lubang.getHead());
	if (player1win || player2win) {
		tplayer1.loadFromFile("images/p1.png");
		tplayer2.loadFromFile("images/p2.png");
	}
	else {
		if (turn) {
			tplayer1.loadFromFile("images/p1s.png");
			tplayer2.loadFromFile("images/p2.png");
		}
		else {
			tplayer1.loadFromFile("images/p1.png");
			tplayer2.loadFromFile("images/p2s.png");
		}
	}
	splayer1.setTexture(tplayer1);
	splayer2.setTexture(tplayer2);
	splayer1.setOrigin(splayer1.getGlobalBounds().width / 2, splayer1.getGlobalBounds().height / 2);
	splayer2.setOrigin(splayer2.getGlobalBounds().width / 2, splayer2.getGlobalBounds().height / 2);
	splayer1.setPosition(windowWidth / 2, 675);
	splayer2.setPosition(windowWidth / 2, 120);
	window.draw(splayer1);
	window.draw(splayer2);

	if (player1win || player2win){
		if (player1win == true && player2win == false){
			ambil = false;
			turnplayer.setString("PLAYER 1 MENANG!!!");
		} else if (player2win == true && player1win == false){
			ambil = false;
			turnplayer.setString("PLAYER 2 MENANG!!!");
		} else if (player1win == true && player2win == true){
			ambil = false;
			turnplayer.setString("PLAYER 1 DAN PLAYER 2 SERI!!!");
		}
	} 
	else if (cekmikul) {
		if (!mikulll->getPrev()->getD()->Besar() && mikulll->getPrev()->getD()->cekBiji() != 0 && mikulll->getPrev()->getD()->getNomor() == mikulll->getD()->getNomor() - 1) {
			mikulll->getPrev()->getD()->setTexture("images/lubang1.png");
		}
		if (!mikulll->getNext()->getD()->Besar() && mikulll->getNext()->getD()->cekBiji() != 0 && mikulll->getNext()->getD()->getNomor() == mikulll->getD()->getNomor() + 1) {
			mikulll->getNext()->getD()->setTexture("images/lubang1.png");
		}
		if (turn) turnplayer.setString("Pemain 1 Mikul");
		else turnplayer.setString("Pemain 2 Mikul");
	}
	else if (ambil) {
		if (turn) { 
			char bijitemp[100], temp[100] = "Biji Pemain 1: ";
			sprintf(bijitemp, "%d", ambilbiji + 1);
			strcat(temp, bijitemp);
			turnplayer.setString(temp);
		}
		else {
			char bijitemp[100], temp[100] = "Biji Pemain 2: ";
			sprintf(bijitemp, "%d", ambilbiji + 1);
			strcat(temp, bijitemp);
			turnplayer.setString(temp);
		}
	}
	else {
		turnplayer.setString("");
	}
	turnplayer.setOrigin(turnplayer.getGlobalBounds().width / 2, turnplayer.getGlobalBounds().height / 2); 
	window.draw(turnplayer);
}

void move(node<Lubang> *counter, cdll<Lubang> lubang, sf::RenderWindow &window, int &ambilbiji, bool &ambil, float &waktu, sf::Clock &clock, Papan &papan, sf::Sprite &smouse) {
	//Suara Step
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(200);

	//base condition
	if (ambilbiji == 0) {
		ambil = false;
		return;
	}
	int tempprev;
	//loop untuk add biji tiap lubang
	while (ambilbiji > 0) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Right) {
					if (batas > 0 && batas <= 2.5) {
						batas-=0.25;
					}
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Left) {
					if (batas < 2.5 && batas >= 0) {
						batas+=0.25;
					}
				}
			}
		}
		bool drawmousee = false;
		waktu = clock.getElapsedTime().asSeconds();
		double dummy = getBatas();
		if (waktu >= dummy) {
			//harus getPrev karena kita add nya searah jarum jam tapi jalan nya dakon berlawanan arah jarum jam
			counter = counter->getPrev();
			tempprev = counter->getD()->cekBiji();
			//jika lubang besar
			if (counter->getD()->Besar()){
				//jika lubang besarnya milik kita
				if (counter->getD()->getPos() == true){
					if (turn == true){
						counter->getD()->addBiji();
						drawmousee = true;
						soundstep.play();
					}
					else continue; //kalo bukan, continue
				//jika lubang besarnya milik kita
				} else if (counter->getD()->getPos() == false){
					if (turn == false){
						counter->getD()->addBiji();
						drawmousee = true;
						soundstep.play();
					}
					else continue; //kalo bukan, continue
				}	
			//jika bukan lubang besar add aja
			} else {
				counter->getD()->addBiji();
				drawmousee = true;
				soundstep.play();
			}
			smouse.setOrigin(smouse.getGlobalBounds().width / 2, smouse.getGlobalBounds().height / 2);
			smouse.setPosition(counter->getD()->getSprite().getPosition().x, counter->getD()->getSprite().getPosition().y);
			//biji berkurang
			ambilbiji--;
			window.clear();
			drawLubang(window, papan, lubang, ambilbiji);
			if (drawmousee) window.draw(smouse);
			window.display();
			clock.restart();
		}
	} 
	//jika lubang terakhir jumlah bijinya 1 dan sebelum diisi lubang tersebut 0 atau lubang terakhir adalah lubang bsar
	if ((counter->getD()->cekBiji() == 1 && tempprev == 0) || counter->getD()->Besar()) {
		//jika lubang bukan lubang besar
		if (!counter->getD()->Besar()) {
			//jika lubang terakhir di wilayah kita, nembak
			if ((turn && counter->getD()->getNomor() > 9) || (!turn && counter->getD()->getNomor() < 9)) {
				node<Lubang> *tempss = lubang.getHead(); 
				ambil = false;
				if (status[getFront(counter->getD()->getNomor()) - 1]) {
					nembak(counter->getD()->getNomor(), tempss, counter); 
				}
			}
			//jika lubang terakhir di wilayah musuh, mikul
			else if ((!turn && counter->getD()->getNomor() > 9) || (turn && counter->getD()->getNomor() < 9)) {
				node<Lubang> *tempss = lubang.getHead(); 
				mikulll = counter;
				ambil = true;
				cekmikul = true;
				return;
			}
			//ganti turn
			if (turn == true){
				turn = false;
			} else if (turn == false){
				turn = true;
			}
		}
		//kalau lubang terakhir lubang besar e kita, turn tetep gk diubah
		else {
			ambil = false;
			return;
		}
	}
	//kalau lubang terakhir bijinya > 1, rekursi move
	else {
		ambilbiji = counter->getD()->getBiji();
		move(counter, lubang, window, ambilbiji, ambil, waktu, clock, papan, smouse);
	}
}

void play(){
	//Init
	//Suara Step
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	cekrestart = false;
	sf::Time time;
	sf::Clock clock;
	sf::Sprite smouse;
	sf::Texture tmouse;
	Powerup powerupP1, powerupP2;
	powerupP1.setPosition(1090, 375);
	powerupP2.setPosition(220, 375);

	font.loadFromFile("fonts/ARLRDBD.ttf");
	turnplayer.setFont(font);
	turnplayer.setColor(sf::Color::Yellow);
	turnplayer.setCharacterSize(24);
	turnplayer.setPosition(windowWidth / 2, windowHeight / 2 - 3);

	tmouse.loadFromFile("images/empty.png");
	smouse.setTexture(tmouse);
	window.setFramerateLimit(30);

	//inisiasi circular double linked list
	cdll<Lubang> lubang;
	//inisiasi class Lubang untuk di add ke circular double linked list
	Lubang lubangs, lubangBesar1, lubangBesar2;
	Powerup powerup;
	Papan papan;
	float waktu;

	//inisisasi array of boolean untuk pengecekan linked list ada atau tidak
	for (int i=0; i<16; i++) {
		status[i] = true;
	}

	//Set Origin, Position, Scale papan, lubang besar
	papan.setOrigin(papan.getSprite().getGlobalBounds().width/2, papan.getSprite().getGlobalBounds().height/2);
	papan.setPosition(windowWidth/2, windowHeight/2);
	lubangBesar1.setLubangBesar();
	lubangBesar1.setOrigin(lubangBesar1.getSprite().getGlobalBounds().width/2, lubangBesar1.getSprite().getGlobalBounds().height/2);
	lubangBesar1.setPosition(windowWidth*0.08, 390);
	lubangBesar1.setScale(0.65, 0.65);
	lubangBesar1.setPos(false);
	lubangBesar2.setLubangBesar();
	lubangBesar2.setOrigin(lubangBesar2.getSprite().getGlobalBounds().width/2, lubangBesar2.getSprite().getGlobalBounds().height/2);
	lubangBesar2.setPosition(windowWidth*0.92, 398);
	lubangBesar2.setScale(0.65, 0.65);
	lubangBesar2.setPos(true);
	lubangs.setOrigin(lubangs.getSprite().getGlobalBounds().width/2, lubangs.getSprite().getGlobalBounds().height/2);
	window.setMouseCursorVisible(false);

	//Button back dan restart
	CButton Back;
	CButton Restart;
	Back.setDir("images/back.png");
	Restart.setDir("images/restart.png");
	Back.setPosition(1200, 125);
	Restart.setPosition(1270, 125);

	//Set linked list (proses add ke linked list)
	//nomer urut untuk penomeran lubang
	int nomorurut = 1;
	double inc = -((((windowWidth - 1000) * 1.4) / 7) - (lubangs.getSprite().getGlobalBounds().width * 0.7)), posx = 265;
	lubangs.setScale(0.4, 0.4);
	lubangBesar1.setNomor(nomorurut);
	nomorurut++;
	lubang.addBack(lubangBesar1);
	for (int i = 0; i < 7; i++){
		lubangs.setPosition(posx, 300);
		if (i==0)lubangs.setJumlah(7);
		else lubangs.setJumlah(0);
		lubangs.setPos(false);
		lubangs.setNomor(nomorurut);
		nomorurut++;
		lubang.addBack(lubangs);
		posx+=inc;
	}
	posx-=inc;
	lubangBesar2.setNomor(nomorurut);
	nomorurut++;
	lubang.addBack(lubangBesar2);
	for (int i = 0; i < 7; i++){
		lubangs.setPosition(posx, 500);
		if (i==0)lubangs.setJumlah(7);
		else lubangs.setJumlah(0);
		lubangs.setPos(true);
		lubangs.setNomor(nomorurut);
		nomorurut++;
		lubang.addBack(lubangs);
		posx-=inc;
	}
	node<Lubang> *counter;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//untuk restart dan back to menu
			if (event.type == sf::Event::MouseButtonReleased){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(Restart.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						restart();
						cekrestart = true;
						menu();
					}
					else if(Back.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						restart();
						menu();
					}
				}
			}
			//cek kalau game belum selesai
			if (!player1win && !player2win) {
				//cek jika belum ngambil biji
				if (ambil == false) {
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							counter = lubang.getHead();
							//cek satu" apakah ada yang di klik
							do {
								if (counter->getD()->isClicked(event.mouseButton.x, event.mouseButton.y) && !counter->getD()->Besar() && counter->getD()->getStat() && !ambil && turn == counter->getD()->getPos()) {
									ambil = true;
									clock.restart();
									break;
								}
								counter = counter->getNext();
							} while (counter != lubang.getHead());

						}
					}
				}
				//pengecekan bila mau menggunakan powerup
				if (!ambil && !cekmikul) {
					if (event.type == sf::Event::MouseButtonReleased) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							//kalau turn ku, cuma boleh klik powerup ku sendiri
							if (turn) {
								//cek kalau diklik dan lubang musuh > 3 dan powerup ada
								if (powerupP1.isClicked(event.mouseButton.x, event.mouseButton.y) && counterpu1 < 6 && powerup1) {
									deleteLubang(lubang);
								}
							}
							else {
								//cek kalau diklik dan lubang musuh > 3 dan powerup ada
								if (powerupP2.isClicked(event.mouseButton.x, event.mouseButton.y) && counterpu2 < 6 && powerup2) {
									deleteLubang(lubang);
								}
							}
						}
					}
				}
				if (event.type == sf::Event::KeyReleased) {
					if (event.key.code == sf::Keyboard::Right) {
						if (batas > 0 && batas <= 2.5) {
							batas-=0.25;
						}
					}
				}
				if (event.type == sf::Event::KeyReleased) {
					if (event.key.code == sf::Keyboard::Left) {
						if (batas < 2.5 && batas >= 0) {
							batas+=0.25;
						}
					}
				}
				//cek kalau mikul, tapi kiri kanan nya nggak ada biji atau kiri lubang besar kanan kosong atau kiri kosong kanan lubang besar, maka gk mikul dan ganti turn
				if (cekmikul){
					if ((mikulll->getPrev()->getD()->cekBiji() == 0 && mikulll->getNext()->getD()->cekBiji() == 0) || (mikulll->getPrev()->getD()->Besar() && mikulll->getNext()->getD()->cekBiji() == 0) || (mikulll->getNext()->getD()->Besar() && mikulll->getPrev()->getD()->cekBiji() == 0)){
						cekmikul = false;
						if (turn == true){
							turn = false;
						} else if (turn == false){
							turn = true;
						}
					}
				}
				//jika bisa mikul
				if (cekmikul) {
					//yang bisa diklik cuma sebelah kiri dan kanan e node yang mikul
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							//pengecekekan kalo yang kanan yang dipikul
							if (mikulll->getPrev()->getD()->isClicked(event.mouseButton.x, event.mouseButton.y) && !mikulll->getPrev()->getD()->Besar() && mikulll->getPrev()->getD()->cekBiji() != 0) {
								if (audiomikul == false){
									playAudioMikul();
								}
								node<Lubang> *tempp;
								tempp = lubang.getHead();
								if (turn) {
									while (tempp->getD()->getNomor() != 9) {
										tempp = tempp->getNext();
									}
									tempp->getD()->addBiji(mikulll->getPrev()->getD()->getBiji());
									if (!player2kosong){
										turn = false;
									}
								}
								else {
									tempp->getD()->addBiji(mikulll->getPrev()->getD()->getBiji());
									if (!player1kosong){
										turn = true;
									}
								}
								tempp->getD()->addBiji(mikulll->getD()->getBiji());
								cekmikul = false;
								ambil = false;
								mikulll->getPrev()->getD()->setTexture("images/lubang.png");
								mikulll->getNext()->getD()->setTexture("images/lubang.png");
							}
							//pengecekekan kalo yang kiri yang dipikul
							else if (mikulll->getNext()->getD()->isClicked(event.mouseButton.x, event.mouseButton.y) && !mikulll->getNext()->getD()->Besar() && mikulll->getNext()->getD()->cekBiji() != 0) {
								if (audiomikul == false){
									playAudioMikul();
								}
								node<Lubang> *tempp;
								tempp = lubang.getHead();
								if (turn) {
									while (tempp->getD()->getNomor() != 9) {
										tempp = tempp->getNext();
									}
									tempp->getD()->addBiji(mikulll->getNext()->getD()->getBiji());
									turn = false;
								}
								else {
									tempp->getD()->addBiji(mikulll->getNext()->getD()->getBiji());
									turn = true;
								}
								tempp->getD()->addBiji(mikulll->getD()->getBiji());
								cekmikul = false;
								ambil = false;
								mikulll->getPrev()->getD()->setTexture("images/lubang.png");
								mikulll->getNext()->getD()->setTexture("images/lubang.png");
							}
						}
					}
				}
			}
		}
		if (!cekmikul){
			audiomikul = false;
		}
		changeTurn();
		window.clear();
		//kalau ngambil biji dan gak mikul
		if (ambil && !cekmikul) {
			tmouse.loadFromFile("images/full.png");
			smouse.setTexture(tmouse);
			int ambilbiji = counter->getD()->getBiji();
			move(counter, lubang, window, ambilbiji, ambil, waktu, clock, papan, smouse);
		}
		else {
			tmouse.loadFromFile("images/empty.png");
			smouse.setTexture(tmouse);
		}
		smouse.setOrigin(smouse.getGlobalBounds().width / 2, smouse.getGlobalBounds().height / 2);
		smouse.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		drawLubang(window, papan, lubang);
		drawPowerup(lubang);
		//pengecekan kapan powerup didraw
		if (powerup1 && counterpu1 < 6) powerupP1.draw(window);
		if (powerup2 && counterpu2 < 6) powerupP2.draw(window);
		Back.draw(window);
		Restart.draw(window);
		window.draw(smouse);
		window.display();
		if (!cekmikul && !ambil){
			cekLubang(lubang);
		}
		if (player1kosong && player2kosong){
			drawWinner(lubang);
		}
		if (player1win || player2win){
			if (audiowin == false){
				playAudioWin();
			}
		}
	}
	drawLubang(window, papan, lubang);
}

void next9()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page10.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack/*,buttonNext*/;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next8();
					}
				}
			}
		}
		buttonBack.draw(window);
		//buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next8()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page9.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next7();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next9();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next7()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page8.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next6();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next8();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next6()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page7.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next5();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next7();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next5()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page6.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next4();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next6();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next4()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page5.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next3();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next5();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next3()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page4.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next2();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next4();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void next2()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page3.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next3();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}


void next()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page2.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonBack.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						how();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next2();
					}
				}
			}
		}
		buttonBack.draw(window);
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

void how()
{
	sf::SoundBuffer bufferstep;
	sf::Sound soundstep;
	bufferstep.loadFromFile("fx/steps.ogg");
	soundstep.setVolume(200);
	soundstep.setBuffer(bufferstep);
	soundstep.setVolume(100);

	sf::Texture textureHow;
	sf::Sprite spriteHow;
	textureHow.loadFromFile("images/page1.png");
	spriteHow.setTexture(textureHow);
	CButton buttonMenu,buttonBack,buttonNext;
	buttonMenu.setDir("images/back.png");
	buttonMenu.setPosition(114, 650);
	buttonBack.setDir("images/prev3.png");
	buttonBack.setPosition(553, 650);
	buttonNext.setDir("images/next3.png");
	buttonNext.setPosition(683, 650);
	while (window.isOpen()){
		window.clear();
		window.draw(spriteHow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			//Mengecek apakah mouse diklik
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(buttonMenu.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						menu();
					}
					if(buttonNext.isClicked(event.mouseButton.x, event.mouseButton.y)){
						soundstep.play();
						next();
					}
				}
			}
		}
		/*buttonBack.draw(window);*/
		buttonNext.draw(window);
		buttonMenu.draw(window);
		window.display();
	}
}

int main() {
	sf::SoundBuffer bufferawal;
	sf::Sound suarawal;	
	bufferawal.loadFromFile("fx/bg2.wav");
	suarawal.setLoop(true);
	suarawal.setBuffer(bufferawal);
	suarawal.setVolume(25);
	suarawal.play();
	menu();

	return 0;
}

void menu()
{
	/*sf::RenderWindow window(sf::VideoMode(1366,768), "Main Menu", sf::Style::Fullscreen);*/
	if (cekrestart){
		//cout << "LALA" << endl;
		cekrestart = false;
		play();
	} else {
		sf::SoundBuffer bufferstep;
		sf::Sound soundstep;
		bufferstep.loadFromFile("fx/steps.ogg");
		soundstep.setVolume(200);
		soundstep.setBuffer(bufferstep);
		soundstep.setVolume(100);

		sf::Texture textureMenu;
		sf::Sprite spriteMenu;
		sf::Text titleText;
		sf::String titleString;
		sf::Font titleFont;
		window.setMouseCursorVisible(true);

		textureMenu.loadFromFile("images/menu.jpg");
		spriteMenu.setTexture(textureMenu);
		CButton buttonStart("START");
		CButton buttonHow("HOW TO PLAY");
		CButton buttonExit("EXIT");
		buttonStart.setPosition(458, 190);
		buttonHow.setPosition(458, 360);
		buttonExit.setPosition(458, 530);

		titleFont.loadFromFile("fonts/Sketch_Block.ttf");
		titleString="Dakon";
		titleText.setString(titleString);
		titleText.setFont(titleFont);
		titleText.setColor(sf::Color::Color(240,230,140));
		titleText.setCharacterSize(100);
		titleText.setPosition(510,32);
		while (window.isOpen()){
			window.clear();
			window.draw(spriteMenu);
			sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed)
					window.close();
				//Mengecek apakah mouse diklik
				if (event.type == sf::Event::MouseButtonPressed){
					if (event.mouseButton.button == sf::Mouse::Left){
						if(buttonStart.isClicked(event.mouseButton.x, event.mouseButton.y)){
							soundstep.play();
							play();
						}
						if(buttonHow.isClicked(event.mouseButton.x, event.mouseButton.y)){
							soundstep.play();
							how();
						}
						if(buttonExit.isClicked(event.mouseButton.x, event.mouseButton.y)){
							soundstep.play();
							window.close();
						}
					}
				}
			}

			spriteMenu.setPosition(0, 0);	
			window.draw(titleText);
			buttonStart.draw(window);
			buttonHow.draw(window);
			buttonExit.draw(window);
			window.display();
		}
	}
}