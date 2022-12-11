#include "../h/cliente.h"

int Cliente::ClientesAtuais = 0;
int Cliente::MaximoClientes = 4;

Cliente::Cliente(){
	PedidoFeito = false;
}

int Cliente::getMaximoClientes(){
	return MaximoClientes;
}
int Cliente::getClientesAtuais(){
	return ClientesAtuais;
}

bool Cliente::getPedidoFeito(){
	return PedidoFeito;
}
void Cliente::setPedidoFeito(bool PedidoFeito){
	this->PedidoFeito = PedidoFeito;
	if(PedidoFeito)	ClientesAtuais++;
	else ClientesAtuais--; 
}
double Cliente::VerificarPedido(Alimento &servido){
	if(servido.getEstadoAlimento()==7)	return 0;
	double nota = 100.0;
	int se=servido.getEstadoAlimento(), st=servido.getTempoEstado(), pe=Pedido.getEstadoAlimento(), pt=Pedido.getTempoEstado(), s=st-pt-(pe*10), p=pe-se;
	if(s>0)	nota -= s*2.0;
	if(p<0)	return nota+(p*4.0);
	return nota-(p*3.0);
}
