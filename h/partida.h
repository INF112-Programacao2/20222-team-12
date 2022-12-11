#ifndef PARTIDA
#define PARTIDA

#include "cliente.h"
#include "item.h"
#include "alimento.h"

class Partida {
	private:
		int TempoDaPartida;
	
		int PratosServidos;
		double NotasRecebidas;
		
		static int xObjeto;
		static int yObjeto;
		
		static bool SegurandoObjeto;
		
		void ServirPrato(int PratosServidos, double NotasRecebidas);
		void setPratosServidos();
		void setNotasRecebidas();
	public:
		Cliente *Clientes;
		
		static bool AcabarPartida;
		
		static Item *ItemSeparado;
		static Item *ItemAuxSeparado;
		static Alimento *PedidoSeparado;
		
		Partida();
		~Partida();
		
		bool setTempoDaPartida();
		int getTempoDaPartida();
		
		int getPratosServidos();
		double getNotasRecebidas();
		
		bool SegurarObjeto(int mouseX, int mouseY);
		void setSegurandoObjeto(bool SegurandoObjeto);
		bool getSegurandoObjeto();
		
		void set_xObjeto(int xObjeto);
		int get_xObjeto();
		void set_yObjeto(int yObjeto);
		int get_yObjeto();
		
		void GerarPedido();
		
		void ContabilizarPedido(Alimento &servido, int i);
};

#endif
