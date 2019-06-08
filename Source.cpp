#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include<stdio.h> 
#include<stdlib.h> 
#include "BST.h"
#include "BST.cpp"
#include <queue>
#include <fcntl.h>
#include <sstream>
#include <cassert>
#include <cstring>
#include <stdlib.h> 



using namespace std;


std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}



struct MinHeapNode {

	char data;

	unsigned freq;

	MinHeapNode *left, *right;

	MinHeapNode(char data, unsigned freq)

	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

 
struct compare {

	bool operator()(MinHeapNode* l, MinHeapNode* r)

	{
		return (l->freq > r->freq);
	}
};



void printCodes(struct MinHeapNode* root, string str)
{

	if (!root)
		return;

	if (root->data != '$')
		cout << root->data << ": " << str << "\n";

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

void fastAccess(struct MinHeapNode* root, string str, vector<string>& x)
{

	if (!root)
		return;

	if (root->data != '$')
		if (root->data  > 0 )
			x[root->data] = str;

	fastAccess(root->left, str + "0", x);
	fastAccess(root->right, str + "1", x);
}



void HuffmanCodes(vector <dataFreq> da, int size, vector<string> &access, priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> & minHeap, int& totFrq)
{
	struct MinHeapNode *left, *right, *top;

	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(da[i].data, da[i].freq));

	// Iterate while size of heap doesn't become 1 
	while (minHeap.size() != 1) {

		// Extract the two minimum 
		// freq items from min heap 
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		// Create a new internal node with 
		// frequency equal to the sum of the 
		// two nodes frequencies. Make the 
		// two extracted node as left and right children 
		// of this new node. Add this node 
		// to the min heap '$' is a special value 
		// for internal nodes, not used 
		top = new MinHeapNode('$', left->freq + right->freq);

		totFrq = left->freq + right->freq;

		top->left = left;
		top->right = right;

		minHeap.push(top);
	}

	// Print Huffman codes using  
	// the Huffman tree built above 
	//printCodes(minHeap.top(), "");
	fastAccess(minHeap.top(), "", access);
}


int toBin(string io, unsigned char* & output) {

	int size = ceil(io.length() / 8.0);
	output = new unsigned char[size];

	int eights = io.length() / 8;
	int rest = io.length() % 8;

	int sum;

	for (int i = 0; i < eights; i++) {
		sum = 0;
		for (int j = 0; j < 8; j++) {
			if (io[(i * 8) + j] == '1') sum += pow(2, 7 - j);
			else sum += 0;
		}
		output[i] = char(sum);
	}

	sum = 0;

	for (int i = 0; i < rest; i++) {

		if (io[io.length() - rest + i] == '1') sum += pow(2, rest - i - 1);
		else sum += 0;
	}
	output[size] = char(sum);


	return size;
}


char toBinChar(string io) {

	char output;

	int sum = 0;

	for (int i = 0; i < 8; i++) {

		if (io[i] == '1') sum += pow(2, 7 - i);
		else sum += 0;
	}
	output = char(sum);

	return output;
}

string decode_file(struct MinHeapNode* root, string s, ofstream & output)
{
	string ans = "";
	int end = 0;
	struct MinHeapNode* curr = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '0')
			curr = curr->left;
		else
			curr = curr->right;

		// reached leaf node 
		if (curr->left == NULL and curr->right == NULL)
		{
			ans += curr->data;
			curr = root;
			end = i;
		}
	}

	output << ans;


	return s.substr(end +1, s.length()-end);
}

string tobinString(string s) {

	string out = "";

	for (int i = 0; i < s.length(); i++) {

		unsigned int c = int(s[i]);

		for (int j = 0; j < 8; j++) {

			int div = pow(2, 7 - j);

			if (c / div == 0)
				out += '0';
			else
				out += '1';

			c %= div;

		}

	}
	return out;
}


void encode(string filename) {

	BST<char, int> tree;

	ifstream input;
	ofstream output;

	string inputFileName = filename + ".txt";
	string outputFileName = filename + ".binary";


	input.open(inputFileName);
	output.open(outputFileName, ios::binary);

	if (!input.is_open())
	{
		cout << "error while opening the file, plz check the spelling or that the file exist" << endl;
		return;
	}

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
	vector<dataFreq> dafeq;

	int totalfrq;

	vector <string> access;

	string bufferstr = "";
	unsigned char* arr;
	char c;

	// counting the frequences
	while (input.get(c)) {

		if (tree.search(c)) {

			tree.update(c);
		}
		else {
			tree.insert(c, 1);
		}
	}
	input.close();

	tree.fillArray(dafeq);

	/*for (int i = 0; i < dafeq.size(); i++) {
		cout << dafeq[i].data << ' ' << dafeq[i].freq << ' ';
	}*/

	access.resize(255);

	HuffmanCodes(dafeq, dafeq.size(), access, minHeap, totalfrq);

	output << dafeq.size() << ' ';

	for (int i = 0; i < dafeq.size(); i++) {
		output << dafeq[i].data << ' ' << dafeq[i].freq << ' ';
	}

	float resultLength = 0;
	float entropy = 0;


	for (int i = 0; i < dafeq.size(); i++) {
		if (dafeq[i].data > 0)
			resultLength += (dafeq[i].freq / float(totalfrq)) * access[dafeq[i].data].length();
	}

	for (int i = 0; i < dafeq.size(); i++) {
		float p = (dafeq[i].freq / float(totalfrq));
		if (dafeq[i].data > 0)
			entropy += p * log2f(p);
	}

	entropy = entropy * -1;



	input.open(inputFileName);


	while (!input.eof()) {

		do {

			input.get(c);

			if (c > 0)

			{
				bufferstr += access[c];
			}


		} while (bufferstr.length() % 8 != 0 && !input.eof());

		//	cout << bufferstr.length() << endl;

		int size = toBin(bufferstr, arr);

		for (int i = 0; i < ceil(bufferstr.length() / 8.0); i++)
			output << arr[i];

		bufferstr = "";

	}

	cout << "*  encoding efficiency  = " << entropy / float(resultLength) << endl;
	cout << "** compression ratio = " << filesize(outputFileName.c_str()) << " / " << filesize(inputFileName.c_str()) <<
		" = " << filesize(outputFileName.c_str()) / float(filesize(inputFileName.c_str())) << endl;;


	cout << "DONE!!" << endl;

}

void decode(string filename) {
	ofstream decode;
	ifstream input;

	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap2;

	vector<dataFreq> dafeq2;
	vector <string> access2;


	string inputFileName = filename + ".binary";
	string outputFileName = filename + "- decoded.txt";

	input.open(inputFileName, ios::binary);
	decode.open(outputFileName);

	if (!input.is_open())
	{
		cout << "error while opening the file, plz check the spelling or that the file exist" << endl;
		return;
	}

	string bufferstr = "";
	unsigned char* arr;
	char c;

	int totalfrq;

	bufferstr = "";
	string s = "";


	int size;

	input >> size;
	dafeq2.resize(size);


	for (int i = 0; i < size; i++) {
		
		input.get(c);
		input.get(c);
		dafeq2[i].data = c;
		input >> dafeq2[i].freq;

	}

	access2.resize(255);

	HuffmanCodes(dafeq2, dafeq2.size(), access2, minHeap2, totalfrq);

	input.get(c);

	while (!input.eof()) {
		s = "";

		for (int i = 0; i < 1000 && !input.eof(); i++) {
			input.get(c);
			s += c;
		}

		bufferstr += tobinString(s);

		bufferstr = decode_file(minHeap2.top(), bufferstr, decode);

	}

	cout << "DONE!" << endl;
}


int main()
{
	

	string filename;
	char op;

	
	do {
		
		cout << "enter the desired operation:\n(e -> encoding (compressing) &  d -> decoding (decompressing))! && q ->  quit " << endl;

		cin >> op;
		cin.ignore();

		cout << "enter the file's name: " << endl;
		
		if (op != 'q')
		getline(cin, filename, '\n');
		else return 0;

				
		//encoding 

		switch (op) {
		case 'e':
			encode(filename);
			break;
		case 'd':
			decode(filename);
			break;
		default:
			cout << "enter the operation again, plz!" << endl;
		}
		
	
	} while (op != 'q');

	
	

	system("pause");

	return 0;
}
