#include "DataNode.hpp"
#include <string>

DataNode::DataNode(char* _key, int _value) {
	key = _key;
	hash = hashKey(key);
	value = _value;
	marked = false;
}

DataNode::DataNode(const DataNode& dataNode) {
	key = dataNode.key;
	hash = hashKey(key);
	value = dataNode.value;
	marked = false;
}

char* DataNode::getKey() {
	return key;
}

char* DataNode::getHash() {
	return hash;
}
