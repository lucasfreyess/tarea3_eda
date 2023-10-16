/*
 * node.hpp
 *
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>

namespace lLists 
{
	class Node 
	{
		private:
			std::string data;
			Node* ptrNext;

		public:
			void setData(std::string _data);
			void setNext(Node* _next);
			std::string getData();
			Node* getNext();
			void print();

			Node();
			Node(std::string _data, Node* next = nullptr);
			virtual ~Node();
	};

} /* namespace eda */

#endif /* NODE_HPP_ */
