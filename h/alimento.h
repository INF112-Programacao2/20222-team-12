#ifndef ITEM
#define ITEM

class Alimento: public Item{
	private:
		int EstadoAlimento;
		int TempoEstado;
	protected:
		void AtualizarNome() override;
	public:
		Alimento();
		
		void setEstadoAlimento();
		void setEstadoAlimento(int EstadoAlimento);
		int getEstadoAlimento();
		void setTempoEstado(int TempoEstado);
		int getTempoEstado();
};

#endif
