/*
 * abb.hpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 * 
 * 	modificado para insertar data de abbNode.hpp como string.
 *  ademas, se eliminaron funciones que no se utilizaron (como show_asc(), k_element() e insert())
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
			void insertRoot(ABBNode* node);
			ABBNode* insertPostfix(std::vector <std::string> &vector_postfix);

			void traverse_rec(ABBNode* node, int level);
			void traverse();

			void updateSize_rec(ABBNode* node);
			void updateSize();

			void clearAll();

			ABB();
			virtual ~ABB();
	};
} /* namespace trees */ 

#endif /* ABB_HPP_ */