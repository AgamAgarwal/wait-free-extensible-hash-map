#include <atomic>
#include "utils.hpp"

using namespace std;

Node* NULL_NODE = nullptr;

char* hashKey(char* key) {
	return key;
}

Node* allocateNode(int value, char* hash) {
	DEBUG("allocating node");
	return new DataNode(hash, value);
}

void markDataNode(Node* node, int pos) {
	DEBUG("marking node");
	dynamic_cast<DataNode*>(dynamic_cast<ArrayNode*>(node)->array[pos].load())->marked = true;
	DEBUG("node marked");
}

Node* getNode(Node* node, int pos) {
	return dynamic_cast<ArrayNode*>(node)->array[pos];
}

bool isArrayNode(Node* node) {
	DEBUG("Checking if array node");
	return dynamic_cast<ArrayNode*>(node) != nullptr;
}

bool isMarked(Node* node) {
	DEBUG("Checking if marked");
	DataNode* x = dynamic_cast<DataNode*>(node);
	return (x!=nullptr) && (x->marked);
}

ArrayNode* expandTable(Node* outerNode, int pos, Node* innerNode, int R) {
	ArrayNode* arrayNode = dynamic_cast<ArrayNode*>(outerNode);
	DataNode* dataNode = dynamic_cast<DataNode*>(innerNode);
	ArrayNode* table = new ArrayNode(ARRAY_LENGTH);
	table->array[(int)dataNode->getKey()[R+1]] = dataNode;
	bool res = atomic_compare_exchange_weak(arrayNode->array + pos, &innerNode, dynamic_cast<Node*>(table));
	DEBUG("CAS result "<<res);
}

bool hashEqual(char* a, char* b, int size) {
	for (int i = 0; i < size; i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

bool unmarkedEqual(Node* x, Node* y, int size) {
	DataNode* a = dynamic_cast<DataNode*>(x);
	DataNode* b = dynamic_cast<DataNode*>(y);
	return !b->marked && (a->value == b->value) && hashEqual(a->getKey(), b->getKey(), size);
}
