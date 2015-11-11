#include "DataNode.hpp"

DataNode::DataNode(char* _key, int _value) {
	key = _key;
	hash = hashKey(key);
	value = _value;
}

char* DataNode::getKey() {
	return key;
}

char* DataNode::getHash() {
	return hash;
}
