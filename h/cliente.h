#ifndef CLIENTE
#define CLIENTE

#include "item.h"
#include "alimento.h"

class Cliente {
	private:
		bool PedidoFeito;
		
		static int MaximoClientes;
		static int ClientesAtuais;
	public:
		Alimento Pedido;
		
		Cliente();
		
		int getMaximoClientes();
		int getClientesAtuais();
		
		bool getPedidoFeito();
		void setPedidoFeito(bool PedidoFeito);
		
		double VerificarPedido(Alimento &servido);
};

#endif
