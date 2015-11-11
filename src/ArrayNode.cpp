#include "ArrayNode.hpp"

ArrayNode::ArrayNode(int size) {
	array = new std::atomic<Node*>[size];
}
