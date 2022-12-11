#include "../h/partida.h"
#include "../h/jogador.h"

bool Partida::AcabarPartida = false;

int Partida::xObjeto = 0;
int Partida::yObjeto = 0;

bool Partida::SegurandoObjeto = false;
Item* Partida::ItemSeparado;
Item* Partida::ItemAuxSeparado;
Alimento* Partida::PedidoSeparado;

Partida::Partida(){
	AcabarPartida=SegurandoObjeto=false;
	xObjeto=yObjeto=TempoDaPartida=0;
	
	setPratosServidos();
	setNotasRecebidas();
	
	Clientes = new Cliente[Clientes->getMaximoClientes()];
}
Partida::~Partida(){
	delete PedidoSeparado;
	delete []Clientes;
	ItemSeparado=ItemAuxSeparado=NULL;	//nao pode dar delete, pq esta apontando pros itens do jogador	
}

bool Partida::setTempoDaPartida(){
	TempoDaPartida = TempoDaPartida+1;
	int max=Clientes->getMaximoClientes(), atual=Clientes->getClientesAtuais();
	if(AcabarPartida && atual==0)	return 0;
	else if(!AcabarPartida && atual<max)	GerarPedido();
	return 1;
}
int Partida::getTempoDaPartida(){
	return TempoDaPartida;
}

void Partida::ServirPrato(int PratosServidos, double NotasRecebidas){
	if(getPratosServidos()==PratosServidos){
		this->PratosServidos = PratosServidos+1;
	} else {
		throw std::out_of_range("A quantidade de pratos servidos recebido, nao e a mesma que a quantidade real. Portanto nao foi possivel aumentar o numero de pratos servidos");
	}
	if(NotasRecebidas>10)	NotasRecebidas=10;
	else if(NotasRecebidas<0)	NotasRecebidas=0;
	this->NotasRecebidas = getNotasRecebidas()+NotasRecebidas;
}
void Partida::setPratosServidos(){
	this->PratosServidos = 0;
}
int Partida::getPratosServidos(){
	return PratosServidos;
}
void Partida::setNotasRecebidas(){
	this->NotasRecebidas = 0;
}
double Partida::getNotasRecebidas(){
	return NotasRecebidas;
}

bool Partida::SegurarObjeto(int mouseX, int mouseY){
	if(SegurandoObjeto){
		ItemSeparado->set_yItem(mouseY);
		ItemSeparado->set_xItem(mouseX);
		return true;
	}
	xObjeto = ItemSeparado->get_xItem();
	yObjeto = ItemSeparado->get_yItem();
	return false;
}

void Partida::setSegurandoObjeto(bool SegurandoObjeto){
	this->SegurandoObjeto = SegurandoObjeto;
}
bool Partida::getSegurandoObjeto(){
	return SegurandoObjeto;
}

void Partida::set_xObjeto(int xObjeto){
	this->xObjeto = xObjeto;
}
int Partida::get_xObjeto(){
	return xObjeto;
}
void Partida::set_yObjeto(int yObjeto){
	this->yObjeto = yObjeto;
}
int Partida::get_yObjeto(){
	return yObjeto;
}

void Partida::GerarPedido(){
	int n = std::rand() % 20;	//std::cout << n << std::endl;
	if(n<2){
		for(int i=0; i<Clientes->getMaximoClientes(); i++)
			if(!((Clientes+i)->getPedidoFeito())){
				((Clientes+i)->Pedido).CriarObjeto(2,0,(i*5),5,2,2);
				(Clientes+i)->setPedidoFeito(true);
				switch(n){
					case 0:
						((Clientes+i)->Pedido).setEstadoAlimento(4);
						break;
					case 1:
						((Clientes+i)->Pedido).setEstadoAlimento(5);
						break;
				}
				((Clientes+i)->Pedido).setTempoEstado(getTempoDaPartida());
				break;
			}
	}
}

void Partida::ContabilizarPedido(Alimento &servido, int i){
	ServirPrato(getPratosServidos(),Clientes[i].VerificarPedido(servido));
	Clientes[i].setPedidoFeito(false);
	servido.CriarObjeto(2,0,9,11,1,1);
	servido.setEstadoAlimento(0);
	servido.setTempoEstado(0);
	setSegurandoObjeto(false);
}
