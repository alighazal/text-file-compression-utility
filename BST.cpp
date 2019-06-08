#include "BST.h"


template<class keyType, class dataType>
BST<keyType, dataType> :: BST() {

	Root = nullptr;
	numofElements = 0;
}

template<class keyType, class dataType>
bool BST<keyType, dataType> ::insert(keyType k , dataType d) {

	numofElements++;

	return insert2(Root, k, d);

}

template<class keyType, class dataType>
bool BST<keyType, dataType> ::insert2(nodeptr &aRoot,const keyType &k,const dataType& d) {

	if (aRoot == nullptr) {
		aRoot = new treeNode;
		aRoot->key = k;
		aRoot->data = d;
		aRoot->left = nullptr;
		aRoot->right = nullptr;
		}
	else if (k < aRoot->key) {
		insert2(aRoot->left, k, d);
			}
	else {
		insert2(aRoot->right, k, d);
	}
	return true;
}

template<class keyType, class dataType>
bool BST<keyType, dataType> ::search(keyType k) {

	return search2(Root, k);

}

template<class keyType, class dataType>
bool BST<keyType, dataType> ::search2(nodeptr aRoot,const keyType k) const {

	if (aRoot == nullptr) {
		return false;
	}
	else if (aRoot->key == k) {
		return true;
	}
	else if (k < aRoot->key) {

		return search2(aRoot->left, k);
	}
	else {
		return search2(aRoot->right, k);
	}
	

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::update(keyType k) {

	update2(Root, k);

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::update2(nodeptr& aRoot , keyType k) {

	if (aRoot == nullptr) {
		return;
	}
	else if (aRoot->key == k) {
		aRoot->data++;
	}
	else {

		if (k < aRoot->key) {

			update2(aRoot->left, k);
		}
		else {
			update2(aRoot->right, k);
		}
	}

}

template<class keyType, class dataType>
bool BST<keyType, dataType> ::empty() {
	if (Root == nullptr) return true;
	else return false;
}

template<class keyType, class dataType>
void BST<keyType, dataType> ::retrieve(keyType k , dataType& receiver) {
	
	 retrieve2(Root, k, receiver);
	 
}

template<class keyType, class dataType>
void BST<keyType, dataType> ::retrieve2(nodeptr aRoot, keyType k, dataType &receiver) {

	if (aRoot != nullptr) {

		if (search2(aRoot, k)) {

			if (aRoot->key == k) {
				receiver = aRoot->data;
			}
			else if (k < aRoot->key) {
				retrieve2(aRoot->left, k, receiver);
			}
			else {
				retrieve2(aRoot->right, k, receiver);
			}


		}
		else { std::cout << "error: 404" << std::endl;
		receiver = -1;
		}
	}

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::inorder() {
	inorder2(Root);
}

template<class keyType, class dataType>
void BST<keyType, dataType> ::inorder2(nodeptr aRoot) {


	if (aRoot == nullptr) return;
	inorder2(aRoot->left);
	std::cout << aRoot->key << "  "<< aRoot->data << std::endl;
	inorder2(aRoot->right);	

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::fillArray(std::vector<dataFreq> &x) {

	fillArray2(Root, x);
}

template<class keyType, class dataType>
void BST<keyType, dataType> ::fillArray2(nodeptr aRoot, std::vector<dataFreq> &x) {
	dataFreq y;

	if (aRoot == nullptr) return;
	fillArray2(aRoot->left, x);
	
	y.data = aRoot->key;
	y.freq = aRoot->data;
	x.push_back(y);

	fillArray2(aRoot->right, x);

}



template<class keyType, class dataType>
void BST<keyType, dataType> ::preorder() {
	
	preorder2(Root);

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::preorder2(nodeptr aRoot) {
	
	if (aRoot == nullptr) return;

	std::cout << aRoot->key << "  " << aRoot->data << std::endl;
	preorder2(aRoot->left);
	preorder2(aRoot->right);

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::postorder() {

	postorder2(Root);

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::postorder2(nodeptr aRoot) {


	if (aRoot == nullptr) return;

	preorder2(aRoot->left);
	preorder2(aRoot->right);
	std::cout << aRoot->key << "  " << aRoot->data << std::endl;

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::levelorder() {

	levelorder2(Root);

}

template<class keyType, class dataType>
void BST<keyType, dataType> ::levelorder2(nodeptr aRoot) {

	std::deque<nodeptr> q;
	nodeptr temp;
	if (aRoot != nullptr) {
		q.push_back(aRoot);

		while (!q.empty()) {
			temp = q.front();
			std::cout << temp->key << "  " << temp->data << std::endl;
			q.pop_front();
			if (temp->left != nullptr) q.push_back(temp->left);
			if (temp->right != nullptr) q.push_back(temp->right);
		}
	}
}

template<class keyType, class dataType>
void BST<keyType, dataType> ::updateDictionary(std::ofstream& output) {
	updateDictionary2(Root, output);

}


template<class keyType, class dataType>
void BST<keyType, dataType> ::updateDictionary2(nodeptr aRoot, std::ofstream &output) {

	std::deque<nodeptr> q;
	nodeptr temp;
	if (aRoot != nullptr) {
		q.push_back(aRoot);

		while (!q.empty()) {
			temp = q.front();
			output << temp->key << "  " << temp->data << std::endl;
			q.pop_front();
			if (temp->left != nullptr) q.push_back(temp->left);
			if (temp->right != nullptr) q.push_back(temp->right);
		}
	}

}



template<class keyType, class dataType>
void BST<keyType, dataType> ::remove(keyType k ) {
	
	remove2(Root, k);


}

template<class keyType, class dataType>
keyType BST<keyType, dataType> ::findMin(nodeptr aRoot) {

	while (aRoot->left != nullptr) aRoot = aRoot->left;
	return aRoot->key;
}


template<class keyType, class dataType>
void BST<keyType, dataType> ::remove2(nodeptr & aRoot, keyType k ) {

	if (aRoot == nullptr) return;
	else if (k < aRoot->key) remove2(aRoot->left, k);
	else if (k > aRoot->key) remove2(aRoot->right, k);
	else {

		//case one
		if (aRoot->left == nullptr && aRoot->right == nullptr) {
			delete aRoot;
			aRoot = nullptr;
			
		}
		//case two
		else if (aRoot->left == nullptr) {
			nodeptr temp = aRoot;
			aRoot = aRoot->right;
			delete temp;
		
		}
		else if (aRoot->right == nullptr) {
			nodeptr temp = aRoot;
			aRoot = aRoot->left;
			delete temp;
			
		}
		else {
			dataType temp;
			//finding the minimum 
			
			retrieve2(aRoot, findMin(aRoot->right), temp);
			aRoot->key = findMin(aRoot->right);
			aRoot->data = temp;
			remove2(aRoot->right, aRoot->key);

		}
	}



}


template<class keyType, class dataType>
BST<keyType, dataType> :: ~BST() {
	

	
}