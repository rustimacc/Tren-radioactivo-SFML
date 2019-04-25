#include "juego.h"





juego::juego() {

	app = new RenderWindow(VideoMode(800, 600), "Tp 3");
	app->setFramerateLimit(30);

///////////////VARIABLES

	escribir = false;
	mostrar_cuentaregresiva = false;
	input_resultado = 0;
	posvagon = 0;
	terminojuego = false;
////////////////GRAFICOS 

	fondotex = new Texture;
	fondo = new Sprite;

	fondotex->loadFromFile("imagenes/fondo.jpg");
	fondo->setTexture(*fondotex);
	fondo->setScale((float)app->getSize().x / fondotex->getSize().x,(float)app->getSize().y / fondotex->getSize().y);

	gameovertex = new Texture;
	gameoverspr = new Sprite;

	gameovertex->loadFromFile("imagenes/gameover.png");
	gameoverspr->setTexture(*gameovertex);
	gameoverspr->setOrigin(gameovertex->getSize().x / 2, gameovertex->getSize().y / 2);
	gameoverspr->setPosition((float)app->getSize().x / 2,(float) app->getSize().y / 2);

	ganastetex = new Texture;
	ganastespr = new Sprite;

	ganastetex->loadFromFile("imagenes/ganaste.png");
	ganastespr->setTexture(*ganastetex);
	ganastespr->setOrigin(ganastetex->getSize().x / 2, ganastetex->getSize().y / 2);
	ganastespr->setPosition((float)app->getSize().x / 2, (float)app->getSize().y / 2);

////////////////OBJETOS

	vagon[0] = new Vagon({ 10, 70 });//70
	vagon[1] = new Vagon({10, 185 });
	vagon[2] = new Vagon({  650, 70 });//298
	vagon[3] = new Vagon({ rand() % 550 + 300, 185 });
	vagon[4] = new Vagon({ rand() % 550 + 300, 298 });
	vagon[5] = new Vagon({ rand() % 550 + 300, 417 });
	loco = new locomotora;

///////////insertar en lista

	insertarvagon(lista, vagon[0],15);
	insertarvagon(lista, vagon[1],7);

//////////TEXTOS

	txtbox = new Texture;
	spr_txtbox = new Sprite;

	txtbox->loadFromFile("imagenes/textbox.png");
	spr_txtbox->setTexture(*txtbox);
	spr_txtbox->setOrigin(txtbox->getSize().x / 2, txtbox->getSize().y / 2);
	spr_txtbox->setPosition(app->getSize().x / 2, app->getSize().y / 2);
	spr_txtbox->setScale(0.5f, 0.5f);

	fuente.loadFromFile("fuente.ttf");
	//texto input
	txt_inputtexto.setFont(fuente);
	txt_inputtexto.setPosition(spr_txtbox->getPosition().x+40,spr_txtbox->getPosition().y);
	txt_inputtexto.setCharacterSize(25);
	txt_inputtexto.setFillColor(Color::Black);
	//texto numeros
	txt_numeros.setFont(fuente);
	txt_numeros.setPosition(spr_txtbox->getPosition().x - 60, spr_txtbox->getPosition().y);
	txt_numeros.setCharacterSize(25);
	txt_numeros.setFillColor(Color::Green);
	//texto cuenta regresiva
	mostrar_tiempo.setFont(fuente);
	mostrar_tiempo.setPosition(750, 20);
	mostrar_tiempo.setCharacterSize(50);
	


///////
	loop();
}

void juego::dibujar() {

	app->clear();

	app->draw(*fondo);

	loco->dibujar(app);
	

	for (int i = 0; i < 6; i++) {
		vagon[i]->dibujar(app);
	}
	if (escribir) {
		app->draw(*spr_txtbox);
		app->draw(txt_numeros);
		app->draw(txt_inputtexto);
		app->draw(mostrar_tiempo);
	}
	
	
	gameover();
	
	app->display();
}

void juego::loop() {

	while (app->isOpen()){
		eventos();
		dibujar();
		if (!terminojuego) {
			
			/////////LOCOMOTORA
			if (loco->get_mover()) {
				loco->movimiento();
				instalarVagon = loco->get_pos().x;
			}
			if (loco->get_meta()) {
				estado = 1;
				terminojuego = true;
			}
			////////VAGONES
			for (int i = 2; i < 6; i++) {
				if (vagon[i]->colision_locomotora(loco->get_bound())) {
					loco->set_mover(false);
					calculo(vagon[i]);
				}
			}
			for (int i = 0; i < 6; i++) {
				vagon[i]->mover({ instalarVagon,loco->get_pos().y });
				vagon[i]->asignarcartel();
			}
		}

//////GAMEOVER
				
	}
}

void juego::eventos() {

	if (app->pollEvent(evt)) {
		switch (evt.type) {

		case Event::Closed:
			app->close();

		case Event::KeyPressed:
			if (evt.key.code == Keyboard::Escape) { app->close(); };
			if (evt.key.code == Keyboard::R) { app->close(); new juego(); };
			
		case Event::TextEntered://detectar e imprimir en pantalla el input del teclado
			if (escribir) {
					if (evt.text.unicode >= 48 && evt.text.unicode <= 57) {//sólo números
						if (string_inputtexto.getSize() < 2) {
							string_inputtexto += evt.text.unicode;
							txt_inputtexto.setString(string_inputtexto);
							string num = string_inputtexto;
							input_resultado = stoi(num);
						}
					}
			}
		}
	}
}

void juego::insertarvagon(nodo *&list, Vagon *vag,int nume) {
	
	nodo *nuevo_nodo = new nodo();
	vag->numero_vagon = nume;
	nuevo_nodo->vagon = vag;
	
	nodo *aux = list;
	nodo *aux2=NULL;
	
	int temp1;
	int temp2;
	while ((aux != NULL)/*&&(aux->vagon->numero_vagon > nuevo_nodo->vagon->numero_vagon)*/) {
		if (aux->vagon->numero_vagon > nuevo_nodo->vagon->numero_vagon) {
			int temp1 = aux->vagon->numero_vagon;
			int temp2 = nuevo_nodo->vagon->numero_vagon;
			aux->vagon->numero_vagon = temp2;
			nuevo_nodo->vagon->numero_vagon = temp1;
		}
		aux2 = aux;
		aux = aux->siguiente;
		
	}
	if (list == aux) {	
		list = nuevo_nodo;		
	}
	else {
		
		aux2->siguiente = nuevo_nodo;
	}
	posvagon++;
	nuevo_nodo->vagon->setpos_vagon(posvagon);
	nuevo_nodo->vagon->set_enganchado(true);
	nuevo_nodo->siguiente = aux;
	//cout << "se agregó un vagon " << posvagon << endl;
}

void juego::eliminarvagon(nodo *&list, Vagon *vag) {

	if (list != NULL) {
		nodo *aux_borrar;
		nodo *anterior=NULL;
		aux_borrar = list;

		while (aux_borrar->siguiente != NULL) {
			anterior = aux_borrar;
			aux_borrar = aux_borrar->siguiente;
		}
		if (aux_borrar == NULL) {
			cout << "no hay mas vagones";
			anterior->siguiente = aux_borrar->siguiente;
			delete aux_borrar;
			estado = 0;
			terminojuego = true;
		}
		if (aux_borrar->siguiente == NULL) {
			if (anterior != NULL) {
				posvagon--;
				anterior->vagon->setpos_vagon(posvagon);
				anterior->siguiente = aux_borrar->siguiente;
				aux_borrar->vagon->setpos_vagon(posvagon);
				aux_borrar->vagon->set_enganchado(false);
				aux_borrar->vagon->set_borrado(true);
				cout << "Se perdio un vagon  "<<posvagon << endl;
				delete aux_borrar;
			}
			else if (anterior == NULL) {
				aux_borrar->vagon->set_enganchado(false);
				aux_borrar->vagon->set_borrado(true);
				cout << "Se perdio un vagon  " << posvagon << endl;
				estado = 0;
				terminojuego = true;
				delete aux_borrar;
			}
			
				
		}

		
		
	}
}

void juego::calculo(Vagon *vag) {
	//loco->set_pos();

	//muestra en pantalla la cuenta regresiva y cambiar color de la cuenta
	int temp = 6 - tiempo.getElapsedTime().asSeconds();
	char convertirtemp[10];
	_itoa_s(temp, convertirtemp, 10);
	mostrar_tiempo.setString(convertirtemp);
	if (temp > 3) {
		mostrar_tiempo.setFillColor(Color::Green);
	}
	else if (temp == 3) {
		mostrar_tiempo.setFillColor(Color::Yellow);
	}
	else if (temp < 3) {
		mostrar_tiempo.setFillColor(Color::Red);
	}
	cargar_textbox();
	
	if (tiempo.getElapsedTime().asSeconds() < 5) {
		//cout << endl << tiempo.getElapsedTime().asSeconds();
		if (evt.key.code == Keyboard::Return) {//al apretar Enter el sistema se fija si el resultado puesto es correcto o no
			if (Keyboard::isKeyPressed(Keyboard::Return) == true) {
				if (escribir&&string_inputtexto != "") {//si el resultado está bien se agrega vagón
					if (result == input_resultado) {
						insertarvagon(lista, vag, result);
						string_inputtexto = "";
						escribir = false;
						loco->set_mover(true);
					}
					else {//si el resultado está mal se elimina vagón
						
						eliminarvagon(lista, vag);
						escribir = false;
						string_inputtexto = "";

					}
				}
			}
		}
	}
	else {
		eliminarvagon(lista, vag);
		tiempo.restart();
	}
	
}

void juego::cargar_textbox() {
	if (!escribir) {

		for (int i = 0; i < 3; i++) {
			numeros[i] = rand() % 10;
		}
		result = numeros[0] + numeros[1] + numeros[2];
		char num1[5];
		char num2[5];
		char num3[5];


		_itoa_s(numeros[0], num1, 10);
		_itoa_s(numeros[1], num2, 10);
		_itoa_s(numeros[2], num3, 10);

		string_numeros = num1; string_numeros += "+";
		string_numeros += num2; string_numeros += "+";
		string_numeros += num3; string_numeros += "= ";
		txt_inputtexto.setString("");//borrar input 
		txt_numeros.setString(string_numeros);//mostrar en pantalla los números a sumar
		escribir = true;
		tiempo.restart();
	}
}

void juego::gameover() {
	if (terminojuego) {
		switch (estado) {
		case 0:
			app->draw(*gameoverspr);
			break;
		case 1:
			app->draw(*ganastespr);
			break;
		}
	}
}