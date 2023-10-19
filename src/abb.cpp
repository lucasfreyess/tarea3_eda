/*
 * abb.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 */

#include "trees/abb.hpp"
#include <iostream>

namespace trees 
{
	int pemdas(std::string c) 
    {
        if (c == "^")
            return 3;

        else if (c == "/" || c == "*")
            return 2;

        else if (c == "+" || c == "-")
            return 1;

        else   
            return -1;
    }

	ABB::ABB():root(nullptr) 
	{
		// TODO Auto-generated constructor stub
	}

	void ABB::insert_postfix(std::vector <std::string> &vector_postfix)
	{
		/*
		for (int i = 0; i < vector_postfix.size(); i++)
		{
			lLists::Stack stack;

			if (vector_postfix[i] != "+" || vector_postfix[i] != "-" || vector_postfix[i] != "*" || vector_postfix[i] != "/" || vector_postfix[i] != "^" )
			{
				stack.push(vector_postfix[i]);  // se guarda variable en stack
			}
			else {
				root->setRight(stack.top()->getData());
				
			}
		}
		*/

		// empieza desde el caracter de mas a la derecha de la expresion postfija
		//for (int i = vector_postfix.size(); i >= 0; i--)
		//{
		//	
		//}

		ABBNode* node = root;
		node->setData(vector_postfix[vector_postfix.size() - 1]);    // caso edge !!!
		vector_postfix.pop_back();

		while (vector_postfix.empty() == false)
		{
			node->setRight(new ABBNode(vector_postfix[vector_postfix.size() - 1]));
			vector_postfix.pop_back();

			if (vector_postfix[vector_postfix.size() - 1] == "+")   // poner demas operadores
			{
				node->setLeft(new ABBNode(vector_postfix[vector_postfix.size() - 1]));
				vector_postfix.pop_back();
				node = node->getLeft();
			}
			else {  // si es que no es un operador, entonces va a la derecha de la derecha del root (pos right-right)

			}
		}
	}

	void ABB::insert_rec(std::string val, ABBNode* node)
	{
		// lo siguiente esta mal btw!! 
		if ( pemdas(val) < pemdas(node->getData()) ) // LEFT
		{
			if (node->getLeft() == nullptr)
			{
				node->setLeft(new ABBNode(val));
				//std::cout<<val << " inserted on left" << std::endl;
			}
			else {
				insert_rec(val, node->getLeft());
			}
		}
		else { // RIGHT
			
			if (node->getRight() == nullptr)
			{
				node->setRight(new ABBNode(val));
				//std::cout<<val << " inserted on right" << std::endl;
			}
			else {
				insert_rec(val, node->getRight());
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

	ABB::~ABB() 
	{
		delete root;
	}

} /* namespace trees */
