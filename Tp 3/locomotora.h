#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class locomotora {

private:

	int x, y;
	int borde;
	int velocidad = 0;
	bool mover;//habilita el movimiento del tren
	bool meta;//muestra si se llegó a la meta

	Clock *tiempo_mov;

/////////////GRAFICOS
	Texture *locotex;
	Sprite *loco;

public:
	locomotora();
	void dibujar(RenderWindow *app);
	void movimiento();
	bool colision_vagon(FloatRect vagon);
	void set_pos();
	
	bool get_mover() { return mover; };
	void set_mover(bool mov) { mover = mov; };
	bool get_meta() { return meta; };

	FloatRect get_bound() { return loco->getGlobalBounds(); };
	Vector2f get_pos() { return loco->getPosition(); };
	int set_borde(int bord) {return  borde = bord; };
};
