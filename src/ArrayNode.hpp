#ifndef _ARRAY_NODE_H_
#define _ARRAY_NODE_H_

#include <atomic>
#include "Node.hpp"

class ArrayNode: public Node {
public:
	std::atomic<Node*>* array;

	ArrayNode(int size);
};

#endif
