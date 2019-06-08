#pragma once

#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

struct dataFreq {
	char data;
	int freq;
};

template<class keyType, class dataType>

class BST
{
private:


	class treeNode {
		public:
			keyType key;
			dataType data;
			treeNode* left;
			treeNode* right;
	};
	typedef treeNode* nodeptr;

	nodeptr Root;
	int numofElements;

	bool search2(nodeptr,const keyType) const;
	bool insert2(nodeptr&,const keyType&, const dataType&);
	void retrieve2(nodeptr,keyType, dataType&);
	void inorder2(nodeptr);
	void postorder2(nodeptr);
	void preorder2(nodeptr);
	void levelorder2(nodeptr);
	void fillArray2(nodeptr, std::vector<dataFreq>& x );
	void updateDictionary2(nodeptr, std::ofstream&);
	void update2(nodeptr& aRoot, keyType k);
	void remove2(nodeptr &, keyType);
	keyType findMin(nodeptr aRoot);




public:
	BST();
	bool insert(keyType, dataType);
	bool empty();
	bool search(keyType);
	void retrieve(keyType, dataType&);
	void inorder();
	void fillArray(std::vector<dataFreq> &x);
	void postorder();
	void preorder();
	void update(keyType);
	void levelorder();
	void remove(keyType);
	void updateDictionary(std::ofstream&);
	~BST();
};

#endif // !BST_H

