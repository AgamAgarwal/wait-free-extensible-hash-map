#include "DataNode.hpp"
#include <string>

DataNode::DataNode(std::string _key, int _value, int _keySize) {
	key = _key;
	keySize = _keySize;
	hash = hashKey(key, keySize);
	value = _value;
	marked = false;
}

DataNode::DataNode(const DataNode& dataNode) {
	key = dataNode.key;
	keySize = dataNode.keySize;
	hash = hashKey(key, keySize);
	value = dataNode.value;
	marked = false;
}

DataNode::~DataNode() {
	delete hash;
}

std::string DataNode::getKey() {
	return key;
}

char* DataNode::getHash() {
	return hash;
}
