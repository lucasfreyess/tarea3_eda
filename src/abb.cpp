/*
 * abb.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 */

#include "trees/abb.hpp"
#include <iostream>
#include <stack>

namespace trees 
{
	ABB::ABB():root(nullptr) 
	{
		// TODO Auto-generated constructor stub
	}

	void ABB::insertNode(ABBNode* node)
	{
		root = node;
	}

	ABBNode* ABB::insert_postfix(std::vector <std::string> &vector_postfix)
	{
		std::stack <ABBNode*> stack;    // hubiera hecho otra clase de stack pero con data ABBNode* pero me dio demasiada lata !

		for (int i = 0; i < vector_postfix.size(); i++)
		{
			if (vector_postfix[i] == "+" || vector_postfix[i] == "-" || vector_postfix[i] == "*" || vector_postfix[i] == "/" || vector_postfix[i] == "^" )
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
			else   // entonces [i] no es un operador
			{
				stack.push(new ABBNode(vector_postfix[i]));
				//std::cout << vector_postfix[i] << " pushed to stack\n\n";
			}
		}

		//std::cout << "top de stack: " << stack.top()->getData() << std::endl;

		return stack.top();   // queda un puntero al root del nuevo arbol de expresion
	}

	void ABB::insert_rec(std::string val, ABBNode* node)
	{
		if (val > node->getData()) // RIGHT
		{
			if (node->getRight() == nullptr)
			{
				node->setRight(new ABBNode(val));
				std::cout << val << " inserted on left of " << node->getData() << std::endl;
			}
			else {
				insert_rec(val, node->getLeft());
			}
		}
		else { // LEFT
			
			if (node->getLeft() == nullptr)
			{
				node->setLeft(new ABBNode(val));
				std::cout << val << " inserted on right of " << node->getData() << std::endl;
			}
			else {
				insert_rec(val, node->getLeft());
			}
		}
	}

	void ABB::insert(std::string val)
	{
	
		if (root == nullptr)
		{
			root = new ABBNode(val);
		}
		else {
			insert_rec(val, root);
		}
	}

	/*
	ABBNode* ABB::find_rec(int val, ABBNode* node)
	{
		ABBNode* ans = nullptr;

		if (node->getData() == val)
		{
			ans = node;
		}
		else {
			if (val < node->getData())
			{
				ans = find_rec(val, node->getLeft());
			}
			else {
				ans = find_rec(val, node->getRight());
			}
		}

		return ans;
	}

	ABBNode* ABB::find(int val) 
	{
		ABBNode* ans = nullptr;
		ans = find_rec(val, root);

		return ans;
	}
	*/

	void ABB::traverse_rec(ABBNode* node, int level)
	{
		if (node != nullptr)
		{
			std::cout << std::string(level*2, '-');
			std::cout << node->getData() << " | s = " << node->getSize() << std::endl;

			traverse_rec(node->getLeft(), level + 1);
			traverse_rec(node->getRight(), level + 1);
		}
	}

	void ABB::traverse()
	{
		traverse_rec(root, 1);
	}

	/*extras*/
	void ABB::showASC_rec(ABBNode* node)
	{
		if (node != nullptr)
		{
			showASC_rec(node->getLeft());
			std::cout << node->getData() << " " << std::flush;
			showASC_rec(node->getRight());
		}
	}

	void ABB::showASC()
	{
		showASC_rec(root);
		std::cout << std::endl;
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

	ABBNode* ABB::k_element_rec(int k, ABBNode* node)
	{
		ABBNode* ans = nullptr;

		if (node != nullptr)
		{
			int lSize = 0;
			int posNode = 0;

			if (node->getLeft() != nullptr)
			{
				lSize = node->getLeft()->getSize();
			}
			posNode = lSize + 1;

			if (k == posNode)
			{
				ans = node;
			}
			else if (k > posNode )
			{
				ans = k_element_rec( k - posNode, node->getRight());
			}
			else {
				ans = k_element_rec( k, node->getLeft());
			}
		}
		return ans;

	}

	ABBNode* ABB::k_element(int k)
	{
		return k_element_rec(k, root);
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
