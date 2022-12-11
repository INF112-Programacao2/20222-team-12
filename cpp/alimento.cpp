#include <iostream>
#include <stdexcept>

#include "../h/item.h"
#include "../h/alimento.h"

Alimento::Alimento(){
	EstadoAlimento = 0;
	setTempoEstado(0);
}

void Alimento::setEstadoAlimento(){
	if(EstadoAlimento%10<7){
		this->EstadoAlimento = EstadoAlimento+1;
		AtualizarNome();
	}
}
void Alimento::setEstadoAlimento(int EstadoAlimento){
	this->EstadoAlimento = EstadoAlimento;
	AtualizarNome();
}
int Alimento::getEstadoAlimento(){
	return EstadoAlimento;
}
void Alimento::setTempoEstado(int TempoEstado){
	this->TempoEstado = TempoEstado;
}
int Alimento::getTempoEstado(){
	return TempoEstado;
}

void Alimento::AtualizarNome(){
	try{
		std::string nome = getNome();
		for(int i=6; i<11; i+=2)
			(i==6 && nome[i]!=getTipoItem()) ? (nome[i]=(std::to_string(getTipoItem()))[0]):(i==8 && nome[i]!=getQualItem()) ? (nome[i]=(std::to_string(getQualItem()))[0]):(i==10 && nome[i]!=getEstadoAlimento()) ? (nome[i]=(std::to_string(getEstadoAlimento()))[0]):(i=i);
		if(getEstadoAlimento()>10) throw std::out_of_range("Estado do Alimento Invalido! O estado do alimento deve ser menor que 10");
		setNome(nome);
	} catch(...) {
		std::cerr << "Erro em atualizar o nome da imagem" << std::endl;
	}
}
