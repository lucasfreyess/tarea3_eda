/*
 * stack.hpp
 *
 *  Created on: Aug 18, 2022
 *      Author: jsaavedr
 * 
 *  modificado para push-ear val como string.
 *  ademas, el namespace no es "eda", es "lLists".
 * 
 */

#ifndef STACK_HPP_
#define STACK_HPP_

#include "lLists/node.hpp"

namespace lLists
{
	class Stack 
	{
		private:
			Node* head;

		public:
			void push(std::string val);
			void push(Node* node);
			
			void pop();
			Node* top();
			bool isEmpty();
			void clear();

			Stack();
			virtual ~Stack();
	};
} /* namespace lLists */

#endif /* STACK_HPP_ */