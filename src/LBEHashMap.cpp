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
		DEBUG("Getting pos");
		int pos = (int) hash[R];
		DEBUG("Got pos");
		int failCount = 0;
		while (true) {
			if (failCount > MAX_FAIL_COUNT) {
				markDataNode(local, pos);
			}
			Node* node = getNode(local, pos);
			DEBUG("Got node");

			if (isArrayNode(node)) {
				DEBUG("is array node");
				local = node;
				break;
			} else if (isMarked(node)) {
				DEBUG("is marked node");
				local = expandTable(local, pos, node, R);
				break;
			} else if (node == nullptr) {
				DEBUG("is null");
				if (atomic_compare_exchange_weak(dynamic_cast<ArrayNode*>(local)->array + pos, &NULL_NODE, insertThis)) {
					DEBUG("Successful CAS");
					lock.unlock();
					return true;
				} else {
					DEBUG("Failed CAS");
					node = getNode(local, pos);
					if (isArrayNode(node)) {
						DEBUG("is array node: 2");
						local = node;
						break;
					} else if (isMarked(node)) {
						DEBUG("is marked node: 2");
						local = expandTable(local, pos, node, R);
						break;
					} else if (node != nullptr && hashEqual(dynamic_cast<DataNode*>(node)->getHash(), dynamic_cast<DataNode*>(insertThis)->getHash(), keySize)) {
						DEBUG("Hashes are equal. Deleting insertThis");
						delete insertThis;
						lock.unlock();
						return true;
					} else {
						DEBUG("fail");
						failCount++;
					}
				}
			} else {
				DEBUG("first else");
				if(hashEqual(dynamic_cast<DataNode*>(node)->getHash(), dynamic_cast<DataNode*>(insertThis)->getHash(), keySize)) {
					DEBUG("Hash equal");
					if (atomic_compare_exchange_weak(dynamic_cast<ArrayNode*>(local)->array + pos, &node, insertThis)) {
						DEBUG("CAS Successful. Deleting old node");
						delete node;
						lock.unlock();
						return true;
					} else {
						DEBUG("CAS failed.");
						Node* node2 = getNode(local, pos);
						if (isArrayNode(node2)) {
							local = node2;
							break;
						} else if (isMarked(node2) ^ unmarkedEqual(node2, node, keySize)) {
							local = expandTable(local, pos, node, R);
							break;
						} else {
							delete insertThis;
							lock.unlock();
							return true;
						}
					}
				} else {
					local = expandTable(local, pos, node, R);
					if (!isArrayNode(local)) {
						failCount++;
					} else {
						break;
					}
				}
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
		DEBUG("Getting pos");
		int pos = (int) hash[R];
		DEBUG("Got pos");

		Node* node = getNode(local, pos);
		DEBUG("Got node");

		if (node == nullptr) {
			DEBUG("is null");
			lock.unlock();
			return false;
		} else if (isMarked(node)) {
			DEBUG("is marked node");
			local = expandTable(local, pos, node, R);
		} else if (!isArrayNode(node)) {
				DEBUG("is NOT array node");
				if (hashEqual(dynamic_cast<DataNode*>(node)->getHash(), hash, keySize)) {
					DEBUG("Hash equal");
					if (atomic_compare_exchange_weak(dynamic_cast<ArrayNode*>(local)->array + pos, &node, NULL_NODE)) {
						DEBUG("CAS Successful. Deleting node");
						delete node;
						lock.unlock();
						return true;
					} else {
						DEBUG("CAS failed.");
						Node* node2 = getNode(local, pos);
						DEBUG("Got node 2");
						if (isMarked(node2) ^ unmarkedEqual(node2, node, keySize)) {
							local = expandTable(local, pos, node, R);
						} else if (isArrayNode(node2)) {
							continue;
						} else {
							lock.unlock();
							return true;
						}
					}
				} else {
					lock.unlock();
					return false;
				}
		} else {
			local = node;
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
