#include "locomotora.h"




locomotora::locomotora() {

////////////VARIABLES

	x = 280;
	y = 70;

	tiempo_mov = new Clock;

	mover = true;
	meta = false;
///////////GRAFICOS
	locotex = new Texture;
	loco = new Sprite;

	locotex->loadFromFile("imagenes/locomotora.png");
	loco->setTexture(*locotex);
	loco->setScale(0.5f, 0.5f);
	loco->setPosition(x,y);


	set_borde(x);


}

void locomotora::dibujar(RenderWindow *app) {
	app->draw(*loco);
}

void locomotora::movimiento() {

	if (mover) {
		loco->setPosition(loco->getPosition().x + 11, loco->getPosition().y);
	}

	if (loco->getPosition().x > 1480) {
		loco->setPosition(-100, loco->getPosition().y + 115);
	}
		
	if (loco->getPosition().x > 550 && loco->getPosition().y >= 530) {
		mover = false;
		meta = true;
	}

	
}

bool locomotora::colision_vagon(FloatRect vagon) {

	if (loco->getGlobalBounds().intersects(vagon)) {
		return true;
	}

}

void locomotora::set_pos() {

	loco->setPosition(loco->getPosition().x - 5, loco->getPosition().y);

}