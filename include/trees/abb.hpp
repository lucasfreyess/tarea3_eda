/*
 * abb.hpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 * 
 * 	modificado para insertar data de abbNode.hpp como string
 */

#ifndef ABB_HPP_
#define ABB_HPP_

#include "trees/abbNode.hpp"
#include "lLists/stack.hpp"
#include <vector>

namespace trees 
{
	class ABB 
	{
		private:
			ABBNode* root;

		public:
			void insertNode(ABBNode* node);
			ABBNode* insertPostfix(std::vector <std::string> &vector_postfix);
			void insert_rec(std::string val, ABBNode* node);
			void insert(std::string val);

			/* creo que no va a ser necesario buscar un valor dentro del arbol asi q 
			comentare las siguientes dos funciones nomas

			ABBNode* find_rec(int val, ABBNode* node);
			ABBNode* find(int val);

			*/

			void traverse_rec(ABBNode* node, int level);
			void traverse();

			void showASC_rec(ABBNode* node);
			void showASC();

			void updateSize_rec(ABBNode* node);
			void updateSize();

			ABBNode* k_element_rec(int k, ABBNode* node);
			ABBNode* k_element(int k);

			void clearAll();

			ABB();
			virtual ~ABB();
	};
} /* namespace trees */ 

#endif /* ABB_HPP_ */