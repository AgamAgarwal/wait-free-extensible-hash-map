#include "LBEHashMap.hpp"

LBEHashMap::LBEHashMap(int _keySize): keySize(_keySize) {
	head = new ArrayNode(ARRAY_LENGTH);
}

bool LBEHashMap::put(std::string key, int value) {
	lock.lock();
	char* hash = hashKey(key, keySize);
	Node* insertThis = allocateNode(value, key, keySize);
	Node* local = head;

	for (int R = 0; R < keySize; R++) {
		int pos = (int) hash[R];
		Node* node = getNode(local, pos);
		if (isArrayNode(node)) {
			local = node;
		} else {
			DataNode* dataNode = dynamic_cast<DataNode*>(node);
			if (dataNode == nullptr) {
				//adding new node
				dynamic_cast<ArrayNode*>(local)->array[pos] = insertThis;
				lock.unlock();
				return true;
			} else if (hashEqual(dataNode->getHash(), hash, keySize)) {
				//replace old node
				dynamic_cast<ArrayNode*>(local)->array[pos] = insertThis;
				delete node;
				lock.unlock();
				return true;
			} else {
				//expand
				local = expandTable(local, pos, insertThis, R);
			}
		}
	}

	lock.unlock();
	return false;
}

bool LBEHashMap::remove(std::string key) {
	lock.lock();
	char* hash = hashKey(key, keySize);
	Node* local = head;

	for (int R = 0; R < keySize; R++) {
		int pos = (int) hash[R];
		Node* node = getNode(local, pos);

		if (node == nullptr) {
			lock.unlock();
			return false;
		} else if (isArrayNode(node)) {
			local = node;
		} else {
			if (hashEqual(dynamic_cast<DataNode*>(node)->getHash(), hash, keySize)) {
				dynamic_cast<ArrayNode*>(local)->array[pos] = nullptr;
				delete node;
				lock.unlock();
				return true;
			} else {
				lock.unlock();
				return false;
			}
		}
	}
	lock.unlock();
	return false;
}

int* LBEHashMap::get(std::string key) {
	lock.lock();
	char* hash = hashKey(key, keySize);
	Node* local = head;

	for (int R = 0; R < keySize; R += 1) {
		int pos = (int) hash[R];
		Node* node = getNode(local, pos);
		if (isArrayNode(node)) {
			local = node;
		} else {
			DataNode* dataNode = dynamic_cast<DataNode*>(node);
			if ((dataNode != nullptr) && hashEqual(dataNode->getHash(), hash, keySize)) {
				lock.unlock();
				return &(dataNode->value);
			} else {
				lock.unlock();
				return nullptr;
			}
		}
	}

	lock.unlock();
	return nullptr;
}
