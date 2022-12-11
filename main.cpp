#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "./h/jogador.h"
#include "./h/partida.h"
#include "./h/item.h"

//g++ main.cpp ./cpp/*.cpp -lallegro -lallegro_image  -lallegro_font

const float FPS = 1;
const int SCREEN_W = 1200;
const int SCREEN_H = 800;
const int SQUARE = 50;

//-----------------------

char MAPA[24][16];

//-----------------------

bool close_ = false;
bool redraw = true;
bool mudar_scene = true;
int scene=0;

//-----------------------

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *map = NULL;
ALLEGRO_MOUSE_STATE mouse;
ALLEGRO_FONT *font = NULL;

//-----------------------

ALLEGRO_BITMAP *frigideira0 = NULL;
ALLEGRO_BITMAP *frigideira1 = NULL;
ALLEGRO_BITMAP *frigideira2 = NULL;
ALLEGRO_BITMAP *frigideira3 = NULL;
ALLEGRO_BITMAP *ovo0 = NULL;
ALLEGRO_BITMAP *ovo1 = NULL;
ALLEGRO_BITMAP *ovo2 = NULL;
ALLEGRO_BITMAP *ovo3 = NULL;
ALLEGRO_BITMAP *pedido0 = NULL;
ALLEGRO_BITMAP *pedido1 = NULL;
ALLEGRO_BITMAP *pedido2 = NULL;
ALLEGRO_BITMAP *pedido3 = NULL;
ALLEGRO_BITMAP *segurando = NULL;

//-----------------------

int inicializa();
void desenhar(Jogador &, Partida &);
void segurarObjeto(Partida &, int mouseX, int mouseY);
void atualizarIMG(Jogador &, Partida &);

//-----------------------

int main(int argc, char **argv){
	if(!inicializa()) return -1;
	
	Jogador *jogador = new Jogador;
	Partida *partida;
	
	char objSeparado;
	
	do{	
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
	
		if(ev.type == ALLEGRO_EVENT_TIMER && scene==1){
			if(!partida->setTempoDaPartida()){
				jogador->TerminarPartida(*partida);
				delete partida;
				scene=0;
				mudar_scene = true;
			}
			redraw = true;
		} else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			al_wait_for_event(event_queue, &event);	//atualiza o x e o y do mouse
			int mouseX = event.mouse.x/SQUARE, mouseY = event.mouse.y/SQUARE;	//std::cout << mouseX << " " << event.mouse.x << " | " << mouseY << " " << event.mouse.y << std::endl;
			if(mouseX>=0 && mouseX<=SCREEN_H && mouseY>=0 && mouseY<=SCREEN_W){
				if(scene==1 && partida->getSegurandoObjeto()){
					char mapa=MAPA[mouseX][mouseY];
					if(mapa=='f')	partida->AcabarPartida = true;
					else if(objSeparado=='5' || (objSeparado=='6'&&mapa=='1')){
						segurarObjeto(*partida,mouseX,mouseY);
					} else if(objSeparado=='8'){
						if(MAPA[mouseX][mouseY]=='p'){
							Alimento &a = dynamic_cast<Alimento&>(*(partida->ItemSeparado));
							int l;
							switch(mouseX){
								case 2:
									l=0;
									break;
								case 7:
									l=1;
									break;
								case 12:
									l=2;
									break;
								case 17:
									l=3;
									break;
							}
							if((partida->Clientes+l)->getPedidoFeito()){
								partida->ContabilizarPedido(a,l);
							}
						} else if(MAPA[mouseX][mouseY]!='8'){
							jogador->SepararItem(*partida,MAPA[mouseX][mouseY],mouseX,mouseY);
							segurarObjeto(*partida,mouseX,mouseY);
							jogador->Interacao(*partida);
						}
					} else if(MAPA[mouseX][mouseY]=='5'){
						objSeparado = '8';
						if(jogador->SepararItem(*partida,objSeparado,mouseX,mouseY))	jogador->Interacao(*partida);
					}
				} else if (mouseX>=0 && mouseX<=23 && mouseY>=0 && mouseY<=15){	//algumas vezes da bug no x e y do mouse, por isso o "filtro"
					switch(MAPA[mouseX][mouseY]){
						case 'h':	//casa
							scene=0;
							mudar_scene = true;
							redraw = true;
							break;
						case 'k':	//cozinha
							partida = new Partida;
							scene=1;
							mudar_scene = true;
							redraw = true;
							break;
						case 'f':
							partida->AcabarPartida = true;
							break;
						case '5':
						case '6':
						case '8':
							objSeparado = MAPA[mouseX][mouseY];
							jogador->SepararItem(*partida,MAPA[mouseX][mouseY],mouseX,mouseY);
							segurarObjeto(*partida,mouseX,mouseY);
							break;
					}
				}
			}
		} else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			close_ = true;	//x de fechar o jogo
			break;
		} else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:	//esc
				close_ = true;
				break;
			}
		}
	
		if(redraw){
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			if(mudar_scene){
				for(int i=0; i<24; i++)
					for(int j=0; j<16; j++)
						MAPA[i][j] = '0';
				switch(scene){
					case 0:
						map = al_load_bitmap("./img/home.png");
						al_draw_textf(font, al_map_rgb(0, 86.3, 100), (SCREEN_H/2), 10, ALLEGRO_ALIGN_CENTRE, "Pontuacao: %d", jogador->Qualidade());
						for(int i=7; i<17; i++)
							for(int j=4; j<9; j++)
									MAPA[i][j] = 'k';
						break;
						
					case 1:
						map = al_load_bitmap("./img/kitchen.png");
						break;
				}
				mudar_scene = false;
			}
			al_draw_bitmap(map,0,0,0);
			if(scene==1){
				/*
				for(int i=10; i<16; i++)
					for(int j=0; j<24; j++)
						if(j<23)	std::cout << MAPA[j][i] << " ";
						else 	std::cout << MAPA[j][i] << std::endl;
				std::cout << "---------------------" << std::endl;
				/**/
				if(jogador->Itens->AtualizarImg)	atualizarIMG(*jogador,*partida);
				for(int i=0; i<24; i++)
					for(int j=0; j<16; j++)
						if(i==23 && j==0){
							MAPA[i][j] = 'f';
						} else if((i==0 || i==3) && (j==11 || j==13)){
							MAPA[i][j] = '2';
						} else if((i>=5 && i<21) && (j>=11 && j<14)){
							MAPA[i][j] = '1';
						} else if(j==5 && (i==2 || i==7 || i==12 || i==17)){
							MAPA[i][j] = 'p';
						} else {
							MAPA[i][j] = '0';
						}
				al_draw_textf(font, al_map_rgb(0, 86.3, 100), (SCREEN_H/2), 10, ALLEGRO_ALIGN_CENTRE, "Tempo da Partida: %d <-> Pratos servidos: %d <-> Notas recebidas: %d", partida->getTempoDaPartida(), partida->getPratosServidos(), (int)(partida->getNotasRecebidas()));
				desenhar(*jogador, *partida);
			}
			al_flip_display();
		}
	}while(!close_);

    al_destroy_font(font);
    al_destroy_bitmap(map);
    al_destroy_bitmap(frigideira0);
    al_destroy_bitmap(frigideira1);
    al_destroy_bitmap(frigideira2);
    al_destroy_bitmap(frigideira3);
    al_destroy_bitmap(ovo0);
    al_destroy_bitmap(ovo1);
    al_destroy_bitmap(ovo2);
    al_destroy_bitmap(ovo3);
    al_destroy_bitmap(pedido0);
    al_destroy_bitmap(pedido1);
    al_destroy_bitmap(pedido2);
    al_destroy_bitmap(pedido3);
    al_destroy_bitmap(segurando);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

//-----------------------

void atualizarIMG(Jogador &jogador, Partida &partida){
	try{
		segurando = al_load_bitmap("./img/0.png");
		frigideira0 = al_load_bitmap((((jogador.Itens)+0)->getNome()).c_str());
		frigideira1 = al_load_bitmap((((jogador.Itens)+1)->getNome()).c_str());
		frigideira2 = al_load_bitmap((((jogador.Itens)+2)->getNome()).c_str());
		frigideira3 = al_load_bitmap((((jogador.Itens)+3)->getNome()).c_str());
		ovo0 = al_load_bitmap((((jogador.Alimentos)+0)->getNome()).c_str());
		ovo1 = al_load_bitmap((((jogador.Alimentos)+1)->getNome()).c_str());
		ovo2 = al_load_bitmap((((jogador.Alimentos)+2)->getNome()).c_str());
		ovo3 = al_load_bitmap((((jogador.Alimentos)+3)->getNome()).c_str());
		if(((partida.Clientes)+0)->getPedidoFeito())	pedido0 = al_load_bitmap(((((partida.Clientes)+0)->Pedido).getNome()).c_str());
		if(((partida.Clientes)+1)->getPedidoFeito())	pedido1 = al_load_bitmap(((((partida.Clientes)+1)->Pedido).getNome()).c_str());
		if(((partida.Clientes)+2)->getPedidoFeito())	pedido2 = al_load_bitmap(((((partida.Clientes)+2)->Pedido).getNome()).c_str());
		if(((partida.Clientes)+3)->getPedidoFeito())	pedido3 = al_load_bitmap(((((partida.Clientes)+3)->Pedido).getNome()).c_str());
	} catch(...) {
		std::cerr << "Erro em abrir as imagens" << std::endl;
	}
	
	jogador.Itens->AtualizarImg = false;
}

//-----------------------

void desenhar(Jogador &jogador, Partida &partida){
	try{
		if(partida.getSegurandoObjeto())	al_draw_bitmap(segurando,18*SQUARE,0*SQUARE,100);
		al_draw_bitmap(frigideira0,(jogador.Itens+0)->get_xItem()*SQUARE,(jogador.Itens+0)->get_yItem()*SQUARE,100);
		al_draw_bitmap(frigideira1,(jogador.Itens+1)->get_xItem()*SQUARE,(jogador.Itens+1)->get_yItem()*SQUARE,100);
		al_draw_bitmap(frigideira2,(jogador.Itens+2)->get_xItem()*SQUARE,(jogador.Itens+2)->get_yItem()*SQUARE,100);
		al_draw_bitmap(frigideira3,(jogador.Itens+3)->get_xItem()*SQUARE,(jogador.Itens+3)->get_yItem()*SQUARE,100);
		al_draw_bitmap(ovo0,(jogador.Alimentos+0)->get_xItem()*SQUARE,(jogador.Alimentos+0)->get_yItem()*SQUARE,100);
		al_draw_bitmap(ovo1,(jogador.Alimentos+1)->get_xItem()*SQUARE,(jogador.Alimentos+1)->get_yItem()*SQUARE,100);
		al_draw_bitmap(ovo2,(jogador.Alimentos+2)->get_xItem()*SQUARE,(jogador.Alimentos+2)->get_yItem()*SQUARE,100);
		al_draw_bitmap(ovo3,(jogador.Alimentos+3)->get_xItem()*SQUARE,(jogador.Alimentos+3)->get_yItem()*SQUARE,100);
		if(((partida.Clientes)+0)->getPedidoFeito())	al_draw_bitmap(pedido0,((partida.Clientes+0)->Pedido).get_xItem()*SQUARE,((partida.Clientes+0)->Pedido).get_yItem()*SQUARE,100);
		if(((partida.Clientes)+1)->getPedidoFeito())	al_draw_bitmap(pedido1,((partida.Clientes+1)->Pedido).get_xItem()*SQUARE,((partida.Clientes+1)->Pedido).get_yItem()*SQUARE,100);
		if(((partida.Clientes)+2)->getPedidoFeito())	al_draw_bitmap(pedido2,((partida.Clientes+2)->Pedido).get_xItem()*SQUARE,((partida.Clientes+2)->Pedido).get_yItem()*SQUARE,100);
		if(((partida.Clientes)+3)->getPedidoFeito())	al_draw_bitmap(pedido3,((partida.Clientes+3)->Pedido).get_xItem()*SQUARE,((partida.Clientes+3)->Pedido).get_yItem()*SQUARE,100);
	} catch(...) {
		std::cerr << "Erro em atualizar as imagens" << std::endl;
	}

	for(int i=0; i<jogador.getQuantidadeItens(); i++)
		for(int k=(jogador.Itens+i)->get_xItem(); k<(jogador.Itens+i)->get_xItem()+(jogador.Itens+i)->getLarguraItem(); k++)
			for(int j=(jogador.Itens+i)->get_yItem(); j<(jogador.Itens+i)->get_yItem()+(jogador.Itens+i)->getAlturaItem(); j++)
						if(k==(jogador.Itens+i)->get_xItem() && j==(jogador.Itens+i)->get_yItem())	MAPA[k][j] = '5';
						else MAPA[k][j] = '1';
	for(int i=0; i<jogador.getQuantidadeAlimentos(); i++)
		for(int k=(jogador.Alimentos+i)->get_xItem(); k<(jogador.Alimentos+i)->get_xItem()+(jogador.Alimentos+i)->getLarguraItem(); k++)
			for(int j=(jogador.Alimentos+i)->get_yItem(); j<(jogador.Alimentos+i)->get_yItem()+(jogador.Alimentos+i)->getAlturaItem(); j++)
						if(MAPA[k][j]=='5'){
							MAPA[k][j]='8';
							if((j==11 || j==13) && (k==0 || k==3)){	jogador.AtualizarEstado(i,partida.getTempoDaPartida());}
						} else if(k==(jogador.Alimentos+i)->get_xItem() && j==(jogador.Alimentos+i)->get_yItem()){
							MAPA[k][j] = '6';
						} else 	MAPA[k][j] = '1';
}

//-----------------------

void segurarObjeto(Partida &partida, int mouseX, int mouseY){
	if(partida.SegurarObjeto(mouseX,mouseY)){
		int cont=0;
		bool desenhar = true;
		for(int i=partida.ItemSeparado->get_xItem(); i<partida.ItemSeparado->get_xItem()+partida.ItemSeparado->getLarguraItem() && cont<1; i++)
			for(int j=partida.ItemSeparado->get_yItem(); j<partida.ItemSeparado->get_yItem()+partida.ItemSeparado->getAlturaItem(); j++)
				if(MAPA[i][j]=='2'){
					cont++;
					break;
				} else if(MAPA[i][j]!='1'){
					cont++;
					desenhar = false;
					break;
				}
		if(desenhar){
			redraw = true;
			partida.setSegurandoObjeto(false);
		} else {
			partida.ItemSeparado->set_yItem(partida.get_yObjeto());
			partida.ItemSeparado->set_xItem(partida.get_xObjeto());
		}
	} else {
		partida.setSegurandoObjeto(true);
	}
}

//-----------------------

int inicializa() {
	if(!al_init()){
		std::cout << "Error in init" << std::endl;
		return 0;
	}

	if(!al_install_keyboard()){
		std::cout << "Error in keyboard" << std::endl;
		return 0;
	}
	
	timer = al_create_timer(1.0 / FPS);
	if(!timer){
		std::cout << "Error in timer" << std::endl;
		return 0;
	}
	
	if(!al_install_mouse()){
		std::cout << "Error in mouse" << std::endl;
		return 0;
	}
	
	if(!al_init_image_addon()){
		std::cout <<"Error in image_addon!" << std::endl;
		return 0;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	map = al_load_bitmap("./img/home.png");
	al_draw_bitmap(map,0,0,0);
	
	font = al_create_builtin_font();
	al_set_target_bitmap(al_get_backbuffer(display)); //muda de volta o destino dos desenhos para o display
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);
	    
	for(int i=0; i<24; i++)
		for(int j=0; j<16; j++)
			MAPA[i][j] = '0';

	 return 1;
}

//-----------------------

