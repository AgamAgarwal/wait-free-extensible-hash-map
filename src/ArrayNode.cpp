#ifndef _ARRAY_NODE_H_
#define _ARRAY_NODE_H_

#include <atomic>
#include "Node.cpp"

using namespace std;

class ArrayNode: public Node {
public:
	atomic<Node*>* array;

	ArrayNode(int size) {
		array = new atomic<Node*>[size];
	}
};

#endif
