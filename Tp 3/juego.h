#pragma once
#include "locomotora.h"
#include "Vagon.h"
#include "nodo.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>


using namespace sf;
using namespace std;

class juego {

private:

////////////////////VARIABLES

	RenderWindow * app;
	Event evt;
	nodo *lista = NULL;

	int numeros[3];//numeros random a sumar
	int input_resultado;//resultado que pone el usuario 
	int result;//resultado de los tres numeros sumados
	int posvagon;//al llegar a cero vagones se pierde
	int estado;//determina que muestra al terminar la partida
	float instalarVagon;
	bool escribir;//se muestra el textbox y permite al usuario el input del teclado
	bool mostrar_cuentaregresiva;//mostrar cuenta regresiva 
	bool terminojuego;

	Clock tiempo;
//////////////OBJETOS

	locomotora *loco;

	Vagon *vagon[6];


///////////////////GRAFICOS

	Texture *fondotex;
	Sprite *fondo;

	Texture *gameovertex;
	Sprite *gameoverspr;
	Texture *ganastetex;
	Sprite *ganastespr;
/////////////////TEXTOS
	Texture *txtbox;//textbox de la suma de los numeros
	Sprite *spr_txtbox;//textbox de la suma de los numeros



	Font fuente;
	String string_inputtexto;
	Text txt_inputtexto;
	Text txt_numeros;
	String string_numeros;
	Text mostrar_tiempo;
public:
	juego();
	void dibujar();
	void loop();
	void eventos();
	void insertarvagon(nodo *&list,Vagon *vag,int nume);
	void eliminarvagon(nodo *&list, Vagon *vag);
	void cargar_textbox();
	void gameover();
	void calculo(Vagon *vag);//muestra el textbox  y si la operación se hizo bien o no
};
