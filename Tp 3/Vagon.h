#pragma once

#include <SFML\Graphics.hpp>


using namespace sf;

class Vagon {

private:

	Texture * vagontex;
	Sprite *vag;

	int ordenvagon;
	
	Font fuente;
	Text cartel;
	bool enganchado;
	bool mostrar_numero;
	bool borrado;
public:
	Vagon(Vector2i pos);
	void dibujar(RenderWindow *app);
	void mover(Vector2f pos);
	void asignarcartel();

	void set_borrado(bool bor) { borrado = bor; };
	bool colision_locomotora(FloatRect loco);
	void set_enganchado(bool eng) { enganchado = eng; };
	FloatRect dev_bound() { return vag->getGlobalBounds(); };
	void set_numerovagon(int num) { numero_vagon = num; };
	int get_numerovagon() { return numero_vagon; };
	void setpos_vagon(int pos) { posvagon = pos; };
	int numero_vagon;
	int posvagon;
};