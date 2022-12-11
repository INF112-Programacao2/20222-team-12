#include "../h/jogador.h"
#include <iostream>

Jogador::Jogador(){
	setPratosServidos();
	setNotasRecebidas();
	
	setQuantidadeItens(4);
	Itens = new Item[getQuantidadeItens()];
	(Itens+0)->CriarObjeto(0,1,5,11,2,2);
	(Itens+1)->CriarObjeto(0,1,5,11,2,2);
	(Itens+2)->CriarObjeto(0,1,5,11,2,2);
	(Itens+3)->CriarObjeto(0,1,5,11,2,2);
	
	setQuantidadeAlimentos(4);
	Alimentos = new Alimento[getQuantidadeAlimentos()];
	(Alimentos+0)->CriarObjeto(2,0,9,11,1,1);
	(Alimentos+1)->CriarObjeto(2,0,9,11,1,1);
	(Alimentos+2)->CriarObjeto(2,0,9,11,1,1);
	(Alimentos+3)->CriarObjeto(2,0,9,11,1,1);
}
Jogador::~Jogador(){
	delete []Itens;
	delete []Alimentos;
}

void Jogador::setPratosServidos(){
	this->PratosServidos = 0;
}
int Jogador::getPratosServidos(){
	return PratosServidos;
}
void Jogador::setNotasRecebidas(){
	this->NotasRecebidas = 0;
}
double Jogador::getNotasRecebidas(){
	return NotasRecebidas;
}
int Jogador::Qualidade(){
	if(getPratosServidos()==0)	return 0;
	return getNotasRecebidas()/getPratosServidos();
}

void Jogador::setQuantidadeItens(int QuantidadeItens){
	this->QuantidadeItens = QuantidadeItens;
}
int Jogador::getQuantidadeItens(){
	return QuantidadeItens;
}
void Jogador::setQuantidadeAlimentos(int QuantidadeAlimentos){
	this->QuantidadeAlimentos = QuantidadeAlimentos;
}
int Jogador::getQuantidadeAlimentos(){
	return QuantidadeAlimentos;
}

bool Jogador::SepararItem(Partida &partida,char TipoItem,int x, int y){
	if(TipoItem=='5'){
		for(int i=0; i<getQuantidadeItens(); i++)
			if((Itens+i)->get_xItem()==x && (Itens+i)->get_yItem()==y){
				partida.ItemSeparado = (Itens+i);
				break;
			}
	} else {
		for(int i=0; i<getQuantidadeAlimentos(); i++)
			if((Alimentos+i)->get_xItem()==x && (Alimentos+i)->get_yItem()==y){
				partida.ItemSeparado = (Alimentos+i);
				break;
			}
				
		if(TipoItem=='8'){
			for(int i=0; i<getQuantidadeItens(); i++)
				if((Itens+i)->get_xItem()==x && (Itens+i)->get_yItem()==y && (Itens+i)->getQualItem()==1){
					partida.ItemAuxSeparado = (Itens+i);
					partida.ItemSeparado->set_xItem(x);
					partida.ItemSeparado->set_yItem(y);
					return true;
				}
		}
	}
	return false;
}

void Jogador::Interacao(Partida &partida){
	partida.ItemAuxSeparado->set_xItem(partida.ItemSeparado->get_xItem());
	partida.ItemAuxSeparado->set_yItem(partida.ItemSeparado->get_yItem());
	
	Alimento &alimento = dynamic_cast<Alimento&>(*(partida.ItemSeparado));
	if(alimento.getEstadoAlimento()<1)	alimento.setEstadoAlimento();
	
	partida.setSegurandoObjeto(false);
}

void Jogador::AtualizarEstado(int qualAlimento, int tempoPartida){
	int tempo_estado = (Alimentos+qualAlimento)->getTempoEstado();
	int cont = 0;
	if(tempo_estado!=0){
		if(tempoPartida-tempo_estado==13){
			(Alimentos+qualAlimento)->setEstadoAlimento();
			(Alimentos+qualAlimento)->setTempoEstado(tempoPartida);
		}
	} else {
		(Alimentos+qualAlimento)->setTempoEstado(tempoPartida);
	}
}


void Jogador::TerminarPartida(Partida &partida){
	this->PratosServidos = getPratosServidos()+partida.getPratosServidos();
	this->NotasRecebidas = getNotasRecebidas()+partida.getNotasRecebidas();
}
