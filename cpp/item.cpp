#include "../h/item.h"
#include <iostream>
#include <stdio.h>

bool Item::AtualizarImg = false;

int Item::getTipoItem(){
	return TipoItem;
}
int Item::getQualItem(){
	return QualItem;
}

void Item::set_xItem(int xItem){
	this->xItem = xItem;
}
int Item::get_xItem(){
	return xItem;
}
void Item::set_yItem(int yItem){
	this->yItem = yItem;
}
int Item::get_yItem(){
	return yItem;
}	

int Item::getAlturaItem(){
	return AlturaItem;
}
int Item::getLarguraItem(){
	return LarguraItem;
}

std::string Item::getNome(){
	return nome;
}
void Item::setNome(){
	nome = "./img/0-0-0.png";
	AtualizarNome();
}
void Item::setNome(std::string nome){
	this->nome = nome;
	atualizarImg = true;
	AtualizarImg = true;
}
void Item::AtualizarNome(){
	for(int i=6; i<9; i+=2)
		(i==6 && nome[i]!=getTipoItem()) ? (nome[i]=(std::to_string(getTipoItem()))[0]):((i==8 && nome[i]!=getQualItem()) ? (nome[i]=(std::to_string(getQualItem()))[0]):(i=i));
}

void Item::CriarObjeto(int TipoItem, int QualItem, int xItem, int yItem, int AlturaItem, int LarguraItem){
	this->TipoItem = TipoItem;
	this->QualItem = QualItem;
	this->xItem = xItem;
	this->yItem = yItem;
	this->AlturaItem = AlturaItem;
	this->LarguraItem = LarguraItem;
	setNome();
}


