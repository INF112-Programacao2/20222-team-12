#ifndef JOGADOR
#define JOGADOR

#include "item.h"
#include "alimento.h"
#include "partida.h"

class Jogador {
	private:
		int QuantidadeItens;
		int QuantidadeAlimentos;
		
		int PratosServidos;
		double NotasRecebidas;
		
		void setPratosServidos();
		void setNotasRecebidas();
		
		void setQuantidadeItens(int QuantidadeItens);
		void setQuantidadeAlimentos(int QuantidadeAlimentos);
	public:
		Item *Itens;
		Alimento *Alimentos;
		
		Jogador();
		~Jogador();
		
		int getPratosServidos();
		double getNotasRecebidas();
		int Qualidade();
		
		int getQuantidadeItens();
		int getQuantidadeAlimentos();
		
		bool SepararItem(Partida &partida,char TipoItem,int x, int y);
		void Interacao(Partida &partida);
		void AtualizarEstado(int qualAlimento,int tempoPartida);
		
		void TerminarPartida(Partida &partida);
};

#endif
