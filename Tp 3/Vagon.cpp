#include"Vagon.h"


Vagon::Vagon(Vector2i pos) {

	numero_vagon = 0;
	
	enganchado = false;
	mostrar_numero = false;
	borrado = false;
	////////////GRAFICOS//////////
	
	vagontex = new Texture;
	vag = new Sprite;

	vagontex->loadFromFile("imagenes/vagon.png");
	vag->setTexture(*vagontex);
	vag->setScale(0.7f, 0.5f);
	//vag->setOrigin(vagontex->getSize().x/2, vagontex->getSize().y / 2);
	vag->setPosition(pos.x,pos.y);

	/////////////TEXTOS CARTEL////

	fuente.loadFromFile("fuente.ttf");
	cartel.setFont(fuente);
	cartel.setCharacterSize(35);
	cartel.setFillColor(Color::Yellow);
	
}
void Vagon::dibujar(RenderWindow *app) {
	if (!borrado) {
		app->draw(*vag);
		if (mostrar_numero) {
			cartel.setPosition(vag->getPosition().x + 40, vag->getPosition().y - 5);
			app->draw(cartel);
		}
	}
}

void Vagon::mover(Vector2f pos) {
	
	if (enganchado) {
		vag->setPosition(pos.x - (90*posvagon), pos.y);
	}
}
bool Vagon::colision_locomotora(FloatRect loco) {

	if (vag->getGlobalBounds().intersects(loco)) {
		
		return true;
	}
	else {
		return false;
	}

}


void Vagon::asignarcartel() {
	numero_vagon;
	char numtext[5];
	_itoa_s(numero_vagon, numtext, 10);
	cartel.setString(numtext);
	mostrar_numero = true;
}