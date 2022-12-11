#ifndef ALIMENTO
#define ALIMENTO

#include <iostream>

class Item {
	private:
		int TipoItem;
		int QualItem;
		
		int AlturaItem;
		int LarguraItem;
		
		int xItem;
		int yItem;
		
		std::string nome;
		void setNome();
		
		bool atualizarImg;
	protected:
		void setNome(std::string nome);
		
		virtual void AtualizarNome();
	public:
		static bool AtualizarImg;
		
		int getTipoItem();
		int getQualItem();
		
		int getAlturaItem();
		int getLarguraItem();
		
		void set_xItem(int xItem);
		int get_xItem();
		void set_yItem(int yItem);
		int get_yItem();
		
		std::string getNome();
		
		void CriarObjeto(int TipoItem, int QualItem, int xItem, int yItem, int AlturaItem, int LarguraItem);
};

#endif


