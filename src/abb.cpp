/*
 * abb.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 * 
 */

#include "trees/abb.hpp"
#include "calculator/utils.hpp"
#include <iostream>
#include <stack>

namespace trees 
{
	ABB::ABB():root(nullptr) 
	{
		// TODO Auto-generated constructor stub
	}

	void ABB::insertRoot(ABBNode* node)
	{
		root = node;
	}

	ABBNode* ABB::insertPostfix(std::vector <std::string> &vector_postfix)
	{
		// tratamos de implementar un stack.cpp con ABBNode*, pero no fue posible !
		// simplemente muy dificil, por lo que decidimos utilizar std::stack!!
		std::stack <ABBNode*> stack;
		
		for (int i = 0; i < vector_postfix.size(); i++)
		{
			if (calc::isOperator(vector_postfix[i]))
			{
				ABBNode* right_node = stack.top();
				stack.pop();

				ABBNode* left_node = stack.top();
				stack.pop();

				ABBNode* new_node = new ABBNode(vector_postfix[i]);
				new_node->setRight(right_node);
				new_node->setLeft(left_node);
				//std::cout << "new node " << new_node->getData() << " created.\n\tptrLeft: " << new_node->getLeft()->getData() << "\n\tptrRight: " << new_node->getRight()->getData() << "\n\n";

				stack.push(new_node);
			}
			else   // entonces vector_postfix[i] no es un operador
			{
				stack.push(new ABBNode(vector_postfix[i]));
			}
		}

		return stack.top();   // queda un puntero al root del nuevo arbol binario en el stack !
	}

	void ABB::traverse_rec(ABBNode* node, int level)
	{
		if (node != nullptr)
		{
			std::cout << std::string(level*3, '-');
			//std::cout << node->getData() << " | s = " << node->getSize() << std::endl;
			std::cout << node->getData() << std::endl;

			traverse_rec(node->getLeft(), level + 1);
			traverse_rec(node->getRight(), level + 1);
		}
	}

	void ABB::traverse()
	{
		traverse_rec(root, 1);
	}

	void ABB::updateSize_rec(ABBNode* node)
	{
		if (node != nullptr)
		{
			updateSize_rec(node->getLeft());
			updateSize_rec(node->getRight());

			int lSize = 0;
			int rSize = 0;

			if (node->getLeft() != nullptr)
			{
				lSize = node->getLeft()->getSize();
			}
			if (node->getRight() != nullptr)
			{
				rSize = node->getRight()->getSize();
			}

			node->setSize(lSize + rSize + 1);
		}
	}

	void ABB::updateSize()
	{
		updateSize_rec(root);
	}

	void ABB::clearAll()
	{
		delete root;
	}

	ABB::~ABB() 
	{
		clearAll();
	}

} /* namespace trees */
