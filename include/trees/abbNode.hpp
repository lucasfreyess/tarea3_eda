/*
 * abbNode.h
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 * 
 * modificado para que data sea un string (en orden de poder albergar los operadores, operandos y el string "ans")
 */

#ifndef ABBNODE_HPP_
#define ABBNODE_HPP_

#include <string>

namespace trees 
{
	class ABBNode 
	{
		private:
			ABBNode* ptrLeft;
			std::string data;
			ABBNode* ptrRight;
			int size;
			
		public:
			void setLeft(ABBNode* node);
			void setRight(ABBNode* node);

			void setData(std::string val);
			void setSize(int s);

			ABBNode* getLeft();
			ABBNode* getRight();

			std::string getData();
			int getSize();

			ABBNode();
			ABBNode(std::string val);
			virtual ~ABBNode();
	};
} /* namespace trees */ 

#endif /* ABBNODE_H_ */
