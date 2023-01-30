// Computing Structures Fall 2022
// Project 5
// Vasu Deva Sai Nadha Reddy Janapala

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBTNode
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBTNode
{
protected:
	// Instance Variables
	DT* _info;
	int _left;
	int _right;

public:
	// Constructors and Destructor
	ArrayBTNode();
	ArrayBTNode(DT& info);
	~ArrayBTNode();

	// getter Methods
	DT* getInfo();
	int getLeft();
	int getRight();

	// setter Methods
	void setInfo(DT& info);
	void setInfoNull(); // Sets _info to Null
	void setLeft(int left);
	void setRight(int right);

	// Display Method
	// Outputs data in _info, _left, _right
	void display();

	// Overloaded Comparison Operators
	// Used for comparing _info field with other ArrayBTNodes
	bool operator<(const ArrayBTNode<DT>& x);
	bool operator>(const ArrayBTNode<DT>& x);
	bool operator==(const ArrayBTNode<DT>& x);
	bool operator>=(const ArrayBTNode<DT>& x);
	bool operator<=(const ArrayBTNode<DT>& x);
	bool operator!=(const ArrayBTNode<DT>& x);

	// friend method
	friend ostream& operator<<(ostream& os, ArrayBTNode<DT> var)
	{
		var.display(os);
		return os;
	}
};

// default constructor
template <class DT>
ArrayBTNode<DT>::ArrayBTNode() {
	_info = NULL;
	_left = -1;
	_right = -1;
}

// non-default constructor
template <class DT>
ArrayBTNode<DT>::ArrayBTNode(DT& info) {
	_info = new DT(info);
	_left = -1;
	_right = -1;
}

// setters
template <class DT>
void ArrayBTNode<DT>::setInfo(DT& info) {
	delete _info;
	_info = new DT(info);
}

template <class DT>
void ArrayBTNode<DT>::setInfoNull() {
	_info = NULL;
}

template <class DT>
void ArrayBTNode<DT>::setLeft(int left) {
	_left = left;
}

template <class DT>
void ArrayBTNode<DT>::setRight(int right) {
	_right = right;
}

// getters
template <class DT>
DT* ArrayBTNode<DT>::getInfo() {
	return _info;
}

template <class DT>
int ArrayBTNode<DT>::getLeft() {
	return _left;
}

template <class DT>
int ArrayBTNode<DT>::getRight() {
	return _right;
}

// Overloaded '<' Operator
template <class DT>
bool ArrayBTNode<DT>::operator<(const ArrayBTNode<DT>& x) {
	return((*_info) < *(x._info));
}

// Overloaded '>' Operator
template <class DT>
bool ArrayBTNode<DT>::operator>(const ArrayBTNode<DT>& x) {
	return((*_info) > *(x._info));
}

// Overloaded '==' Operator
template <class DT>
bool ArrayBTNode<DT>::operator==(const ArrayBTNode<DT>& x) {
	return((*_info) == *(x._info));
}

// Overloaded '>=' Operator
template <class DT>
bool ArrayBTNode<DT>::operator>=(const ArrayBTNode<DT>& x) {
	return((*_info) >= *(x._info));
}

// Overloaded '<=' Operator
template <class DT>
bool ArrayBTNode<DT>::operator<=(const ArrayBTNode<DT>& x) {
	return((*_info) <= *(x._info));
}

// Overloaded '!=' Operator
template <class DT>
bool ArrayBTNode<DT>::operator!=(const ArrayBTNode<DT>& x) {
	return((*_info) != *(x._info));
}

// display
template <class DT>
void ArrayBTNode<DT>::display() {
	cout << "Info: " << *(getInfo()) << ", "
		<< "Left: " << getLeft() << ", "
		<< "Right: " << getRight() << endl;
}

// destructor
template <class DT>
ArrayBTNode<DT>::~ArrayBTNode() {
	//delete _info; // throwing garbage values
	_left = -1;
	_right = -1;
}




////////////////////////////////////////////////////////////////////////////////////////
// Class ArrayBST
////////////////////////////////////////////////////////////////////////////////////////

template <class DT>
class ArrayBST
{
protected:
	// Instance Variables
	vector<ArrayBTNode<DT> > _tree;    // Vector of ArrayBTNodes used to create a tree
	int _rootIndex;            // Index of the root node in _tree
	int _numNodes;             // Number of nodes in the tree
	int _size;                 // Maximum size of the _tree array
	stack<int> _freeLocations; // Stack containing indexes of freeLocations in the _tree array
	
public:
	// Constructors and Destructor
	ArrayBST();
	ArrayBST(int k); // initialize the vector with NULL nodes and fill the stack
	~ArrayBST();

	// Accessor Methods
	bool isEmpty();
	int Height();
	int Size();
	int rootIndex();
	int maxSize();

	// Mutator Methods
	void setData(int index, DT& value);
	void setLeft(int index, int value);
	void setRight(int index, int value);

	// Display methods and traversals
	void display(ostream& os);
	void displayPreOrder(ostream& os);
	void displayInOrder(ostream& os);
	void printRaw(); // Display the array and all of its contents

	

	// BST Specific Methods
	void insert(DT& object);
	bool find(DT& object);
	int findIndex(DT& object);
	bool _find(DT& object, int pos); // helper method
	int _findIndex(DT& object, int pos); // helper method

	// Methods used for pre-order and post-order travesal
	int _functionPreOrder(int value); // helper method for preOrder
	int _functionInOrder(int value);  // helper method for inOrder
	int _functionHeight(int value); // helper method for Height

	// friend method
	friend ostream& operator<<(ostream& os, ArrayBST<DT> var)
	{
		var.display(os);
		return os;
	}
};

// default constructor
template <class DT>
ArrayBST<DT>::ArrayBST() {
	_size = -1;
	_rootIndex = -1;
	_numNodes = -1;
	_freeLocations = -1;
}

// non-default constructor
template <class DT>
ArrayBST<DT>::ArrayBST(int k) {

	_tree.reserve(k); // reserving the size of the vector tree
	_size = k;		  // assigning the maximum number od nodes

	/*	
	*	setting the stack and the vector positions to default values,
	*						which are unique to individual position
	*/
	int count = 0;
	while (count < k) {
		_freeLocations.push(count);			// inserting values to _freeLocations stack
		_tree.push_back(ArrayBTNode<DT>()); // default value allocation to _tree vector
		count++;
	}

	_numNodes = 0;
	_rootIndex = k - 1;
}

// accessor methods
template <class DT>
bool ArrayBST<DT>::isEmpty() { // checking whether the stack is empty
	if (_freeLocations.size() == 0)
		return true;
	else
		return false;
}

// helper method for -- Height -- method
// here the recursion takes place multiple times
template <class DT>
int ArrayBST<DT>::_functionHeight(int value) {
	int inc = 1;
	if (_tree[value].getLeft() == -1 && _tree[value].getRight() == -1) {
		return inc;
	}

	// 1. Below if statement helps to call the recursion method - _functionHeight
	// 2. If the condition statisfies, first the left value, later the right value - 
	//				- will be kept on recursion in "_functionHeight" helper function
	// 3. The return values will be compared
	// 4. The highest value will be returned, which is the 'height of the tree'
	else if (_tree[value].getLeft() != -1 && _tree[value].getRight() != -1) {
		int x = inc + _functionHeight(_tree[value].getLeft());
		int y = inc + _functionHeight(_tree[value].getRight());
		if (x > y)
			return x;
		else
			return y;
	}
	else if (_tree[value].getLeft() == -1) {
		return (inc + _functionHeight(_tree[value].getRight()));
	}
	else if (_tree[value].getRight() == -1) {
		return (inc + _functionHeight(_tree[value].getLeft()));
	}
}

// height method of the tree
template <class DT>
int ArrayBST<DT>::Height() { 

	int currentPosition = _rootIndex;
	int count = (_rootIndex - _numNodes);
	int height = 0;
	count = count + 1;
	while (count < _rootIndex) {

		// guard
		if (_tree[_rootIndex].getLeft() == -1 && _tree[_rootIndex].getRight() == -1) {
			height++;
			return height;
			break;
		}

		// 1. The below if statement helps to call - 
		//				- the helper method "_functionHeight", which is recursive
		// 2. If the condition statisfies, first the left value, later the right value - 
		//				- will be kept on recursion in "_functionHeight" helper function
		// 3. The return values will be compared
		// 4. The highest value will be returned, which is the 'height of the tree'
		if (_tree[currentPosition].getLeft() != -1 && _tree[currentPosition].getRight() != -1) {
			int indexLeft = _functionHeight(_tree[currentPosition].getLeft());
			int indexRight = _functionHeight(_tree[currentPosition].getRight());
			if (indexLeft > indexRight) {
				height = height + indexLeft + 1;
				return height;
			}
			else {
				height = height + indexRight + 1;
				return height;
			}
		}

		else if (_tree[currentPosition].getLeft() == -1) {
			currentPosition = _tree[currentPosition].getRight();
			height++;
			count++;
		}

		else if (_tree[currentPosition].getRight() == -1) {
			currentPosition = _tree[currentPosition].getLeft();
			height++;
			count++;
		}
	}
	return height;
}

template <class DT>
int ArrayBST<DT>::Size() { // this method returns the leftover spaces
	return (maxSize() - _numNodes);
}

template <class DT>
int ArrayBST<DT>::rootIndex() {	// root index value will be returned
	return _rootIndex;
}

template <class DT>
int ArrayBST<DT>::maxSize() { // maximum size of the vector can be retrieved
	return _size;
}

// Mutator Methods
template <class DT>
void ArrayBST<DT>::setData(int index, DT& value) { // setting the info
	_tree[index].setInfo(value);
}

template <class DT>
void ArrayBST<DT>::setLeft(int index, int value) { 
	// setting the left value for the vector _tree using index
	_tree[index].setLeft(value);
}

template <class DT>
void ArrayBST<DT>::setRight(int index, int value) {
	// setting the right value for the vector _tree using index
	_tree[index].setRight(value);
}

// Display methods and traversals
template <class DT>
void ArrayBST<DT>::display(ostream& os) {
	cout << "Information in Tree: " << "\n" << "Pre Order Traversal : " << endl;
	displayPreOrder(os);
	cout << endl;
	cout << "In Order Traversal: " << endl;
	displayInOrder(os);
	cout << endl;
}


// helper method for -- displayPreOrder -- method
// here the recursion takes place multiple times
template <class DT>
int ArrayBST<DT>::_functionPreOrder(int value) {
	int inc = 1;
	if (_tree[value].getLeft() == -1 && _tree[value].getRight() == -1) {
		cout << *(_tree[value].getInfo()) << " ";
		return inc;
	}
	else if (_tree[value].getLeft() != -1 && _tree[value].getRight() != -1) {
		cout << *(_tree[value].getInfo()) << " ";
		int x = inc + _functionPreOrder(_tree[value].getLeft());
		_functionPreOrder(_tree[value].getRight());
		return (x);
	}
	else if (_tree[value].getLeft() == -1) {
		cout << *(_tree[value].getInfo()) << " ";
		return (inc + _functionPreOrder(_tree[value].getRight()));
	}
	else if (_tree[value].getRight() == -1) {
		cout << *(_tree[value].getInfo()) << " ";
		return (inc + _functionPreOrder(_tree[value].getLeft()));
	}
}

// The idea behind this method is,
//			printing the values before it gets into any direction
template <class DT>
void ArrayBST<DT>::displayPreOrder(ostream& os) {
	int currentPosition = _rootIndex;
	int indexPosition = (_rootIndex - _numNodes);

	while (indexPosition != _rootIndex && currentPosition != -1) {
		// guard
		if (_tree[_rootIndex].getLeft() == -1 && _tree[_rootIndex].getRight() == -1) {
			cout << *(_tree[_rootIndex].getInfo()) << endl;
			break;
		}

		// 1. The below if statement helps to call - 
		//				- the helper function "_functionPreOrder", which is recursive
		// 2. If the condition statisfies, the left value - 
		//				- will be kept on recursion in "_functionPreOrder" helper function
		if (_tree[currentPosition].getLeft() != -1 && _tree[currentPosition].getRight() != -1) {
			cout << *(_tree[currentPosition].getInfo()) << " ";
			int indexes = _functionPreOrder(_tree[currentPosition].getLeft());
			currentPosition = _tree[currentPosition].getRight();
			indexPosition = indexPosition + indexes + 1;
		}

		// If below condition satisfies, the traverse happens towards the right side
		// ----------- GO RIGHT ----------------
		else if (_tree[currentPosition].getLeft() == -1) {
			cout << *(_tree[currentPosition].getInfo()) << " ";
			currentPosition = _tree[currentPosition].getRight();
			indexPosition++;
		}

		// If below condition satisfies, the traverse happens towards the left side
		// ----------- GO LEFT ----------------
		else if (_tree[currentPosition].getRight() == -1) {
			cout << *(_tree[currentPosition].getInfo()) << " ";
			currentPosition = _tree[currentPosition].getLeft();
			indexPosition++;
		}
	}
}

// helper method for -- displayInOrder -- method
// here the recursion takes place multiple times
template <class DT>
int ArrayBST<DT>::_functionInOrder(int value) {
	int inc = 1;
	if (_tree[value].getLeft() == -1 && _tree[value].getRight() == -1) {
		cout << *(_tree[value].getInfo()) << " ";
		return inc;
	}
	else if (_tree[value].getLeft() != -1 && _tree[value].getRight() != -1) {
		int x = inc + _functionInOrder(_tree[value].getLeft());
		cout << *(_tree[value].getInfo()) << " ";
		int y = inc + _functionInOrder(_tree[value].getRight());
		return (x+y);
	}
	else if (_tree[value].getLeft() == -1) {
		cout << *(_tree[value].getInfo()) << " ";
		int y = inc + _functionInOrder(_tree[value].getRight());
		return y;
	}
	else if (_tree[value].getRight() == -1) {
		int z = inc + _functionInOrder(_tree[value].getLeft());
		cout << *(_tree[value].getInfo()) << " ";
		return z;
	}
}

// The idea behind this method is,
//			printing the values only if there is no left child, 
//			if there a left child, we traverse till the deeper child, 
//			and printing the elements from back
template <class DT>
void ArrayBST<DT>::displayInOrder(ostream& os)  {
	int currentPosition = _rootIndex;
	int indexPosition = (_rootIndex - _numNodes);
	while (indexPosition < _rootIndex && currentPosition != -1) {
		// guard
		if (_tree[_rootIndex].getLeft() == -1 && _tree[_rootIndex].getRight() == -1) {
			cout << *(_tree[_rootIndex].getInfo()) << endl;
			break;
		}

		// 1. The below if statement helps to call - 
		//				- the helper function "_functionInOrder", which is recursive
		// 2. If the condition statisfies, the left value - 
		//				- will be kept on recursion in "_functionInOrder" helper function
		if (_tree[currentPosition].getLeft() != -1 && _tree[currentPosition].getRight() != -1) {
			int indexes = _functionInOrder(_tree[currentPosition].getLeft());
			cout << *(_tree[currentPosition].getInfo()) << " ";
			currentPosition = _tree[currentPosition].getRight();
			indexPosition = indexPosition + indexes + 1;
		}

		// If below condition satisfies, the traverse happens towards the right side
		// ----------- GO RIGHT ----------------
		else if (_tree[currentPosition].getLeft() == -1) {
			cout << *(_tree[currentPosition].getInfo()) << " ";
			currentPosition = _tree[currentPosition].getRight();
			indexPosition++;
		}

		// If below condition satisfies, the traverse happens towards the left side
		// ----------- GO LEFT ----------------
		else if (_tree[currentPosition].getRight() == -1) {
			int indexes = _functionInOrder(_tree[currentPosition].getLeft());
			cout << *(_tree[currentPosition].getInfo()) << " ";
			currentPosition = _tree[currentPosition].getLeft();
			indexPosition = indexPosition + indexes + 1;
		}

	}
}

// 1. The method printRaw() is used to display the -
//					- inserted information in the vector
// 2. Also it displays the remainaing free places using the stack
template <class DT>
void ArrayBST<DT>::printRaw() {
	int stackSize = _freeLocations.size();
	int decrement = _rootIndex;

	cout << "Raw Data: " << endl;
	// Raw data display using while loop
	while (stackSize <= _rootIndex) {
		cout << "Index " << stackSize << ": ";
		_tree[stackSize].display(); // calling the ArrayBTNode display method

		// alternate way of printing the raw output
		/*cout << "Index " << stackSize << ": ";
			<< "Info: " << *(_tree[stackSize].getInfo()) << ", "
			<< "Left: " << _tree[stackSize].getLeft() << ", "
			<< "Right: " << _tree[stackSize].getRight() << endl;*/
		stackSize++;
		decrement--;
	}

	// Printing the available of free indexes
	cout << "Free Indexes:  " << endl;
	if (decrement < 0)
		cout << "None" << endl;
	else {
		while (decrement > -1) {
			if (decrement > 0) {
				cout << decrement << ", ";
				decrement--;
			}
			else {
				cout << decrement;
				decrement--;
			}
		}
		cout << endl;
	}
}

// BST Specific Methods

// Insert method to insert the values into the vector _tree
template <class DT>
void ArrayBST<DT>::insert(DT& object) {
	
	// checking whether the allocated memory of the vector is full or not
	// If it is not full, the below condition will be bypassed
	if (_size <= _numNodes) {
		cout << "Cannot insert data, BST Full." << endl;
		return;
	}
	// fixing the position and taking out the value everytime, using stack STL methods
	int indexPosition = _freeLocations.top();
	_freeLocations.pop();
	_numNodes++; // updaing the number of nodes for each insertion - 
					//    - using this again in the display preOrder and - 
					   //    - display InOrder to set the indexPosition variable

	setData(indexPosition, object); // setting the info calling the setData method
	int currentPosition = _rootIndex;

	if (_rootIndex != indexPosition) {
		while (true) {
			// The below if statements are useful to set the 
			//			- left and right index positions of - 
			//							- every inserted value
			if (_tree[currentPosition] > _tree[indexPosition]) {
				if (_tree[currentPosition].getLeft() == -1) {
					setLeft(currentPosition, indexPosition);
					break;
				}
				else
					currentPosition = _tree[currentPosition].getLeft();
			}
			else {
				if (_tree[currentPosition].getRight() == -1) {
					setRight(currentPosition, indexPosition);
					break;
				}
				else
					currentPosition = _tree[currentPosition].getRight();
			}
		}
	}
}

// Find method - to check whether particular value is available in the tree or not
template <class DT>
bool ArrayBST<DT>::find(DT& object) {
	// calling the helper _find method recursivly to check the -
	//			- existance of the number or not.
	return _find(object, rootIndex());
}
// helper method to find the value
// it returns the boolean value, based on it, the index position check will happen
template <class DT>
bool ArrayBST<DT>::_find(DT& object, int pos) {
	if (*(_tree[pos].getInfo()) == object) return true;
	if (*(_tree[pos].getInfo()) < object) {
		if ((_tree[pos]).getRight() != -1) {
			return _find(object, _tree[pos].getRight());
		}
		return false;
	}
	else {
		if ((_tree[pos]).getLeft() != -1) {
			return _find(object, _tree[pos].getLeft());
		}
		return false;
	}
}

// findIndex method will be called only if the value exists in the tree
template <class DT>
int ArrayBST<DT>::findIndex(DT& object) {
	return _findIndex(object, rootIndex());
}

// helper method to find the index of the found value
// it returns the position of the value
template <class DT>
int ArrayBST<DT>::_findIndex(DT& object, int pos) {
	if (*(_tree[pos].getInfo()) == object) return pos;
	if (*(_tree[pos].getInfo()) < object) {
		if ((_tree[pos]).getRight() != -1) {
			return _findIndex(object, _tree[pos].getRight());
		}
	}
	else {
		if ((_tree[pos]).getLeft() != -1) {
			return _findIndex(object, _tree[pos].getLeft());
		}
	}
}

// destructor
template <class DT>
ArrayBST<DT>::~ArrayBST() {

}


////////////////////////////////////////////////////////////////////////////////////////
// Main Method
////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Get input for the size of the tree
	int inputSize;
	cin >> inputSize;

	cout << "Number of maximum nodes : " << inputSize << '\n' << endl;

	// Create a BST of the size inputSize
	ArrayBST<int> myBST = ArrayBST<int>(inputSize);

	// input loop for commands
	char command;
	int value;
	cin >> command;
	while (!cin.eof()) {
		switch (command) {
		case 'I': { // insert
			
			cin >> value;
			cout << "Inserting " << value << endl;
			myBST.insert(value); // calling the insert method in ArrayBSTNode class to insert values
			cout << endl;
			break;
		}
		// height of the tree
		/*case 'H': { 
		//	int x = myBST.Height();
		//	cout << "Height: " << x << endl;
		//	break;
		}*/
		case 'O': { // output the tree using the ostream operator
			
			cout << myBST << endl;;
			break;
		}
		case 'A': { //output using DisplayRaw method

			myBST.printRaw(); // calling the printRaw method
			cout << endl;
			break;
		}
		case 'F': { // search -- checking the number exist, if it exists, check the index --
			
			cin >> value;
			bool boolean;
			cout << "Finding " << value << endl;
			boolean = myBST.find(value);
			if (boolean == true) // this checks where to go with findIndex method or not
				cout << "Number found at index " << myBST.findIndex(value) << "." 
								<< "\n" << endl;
			else
				cout << "Number not found." << "\n" << endl;
			break;
		}
		default: { // default case
			cout << "invalid command!!!!!!" << endl;
			break;
		}
		}
		cin >> command;
	}
	return 0;
}