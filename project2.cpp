// Computing Structures Fall 2022
// DSA 5005
// Project 2
// Vasu Deva Sai Nadha Reddy Janapala

#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
template <class DT>  // template for Node class
class Node
{
protected:
	int nodeNumber;  // field to store node's number
	string nodeInfo; // field to store node's information
	DT yearCreated;  // field to store the year of the node created
	string location; // field to store the location

public:
	Node(); // default constructor

	// getters
	string getNodeInfo();
	int getNodeNumber();
	DT getYearCreated();
	string getLocation();

	// setters
	void setNodeInfo(string newInfo, DT newYearCreated, string newLoc);
	void setNodeNumber(int newNum);
	void setYearCreated(DT newYearCreated);
	void setLocation(string newLocation);

	void display(); // display node details

	~Node(); // destructor
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//default constructor
template <class DT>
Node<DT>::Node()
{
	nodeNumber = -1;
	nodeInfo = " ";
	yearCreated = -1;
	location = " ";
}

// Function - setNodeNumber - to set the node number
template <class DT>
void Node<DT>::setNodeNumber(int newNum)
{
	nodeNumber = newNum;
}

// Function - getNodeNumber - to get the Node Number
template <class DT>
int Node<DT>::getNodeNumber()
{
	return nodeNumber;
}

// Function - setNodeInfo - to set the node Information
template <class DT>
void Node<DT>::setNodeInfo(string newInfo, DT newYearCreated, string newLoc)
{
	nodeInfo = newInfo;
	yearCreated = newYearCreated;
	location = newLoc;
}

// Function - getNodeInfo - to get the Node Information
template <class DT>
string Node<DT>::getNodeInfo()
{
	return nodeInfo;
}

// display function to print both node number and node information
template <class DT>
void Node<DT>::display()
{
	cout << nodeNumber << ": " << nodeInfo << endl;
}

//  Function - setYearCreated - to set the Year Created
template <class DT>
void Node<DT>::setYearCreated(DT newYearCreated)
{
	yearCreated = newYearCreated;
}

// Function - getYearCreated - to get the Year Created
template <class DT>
DT Node<DT>::getYearCreated()
{
	return yearCreated;
}

// Function - setLocation - to set the location of each node
template <class DT>
void Node<DT>::setLocation(string newLocation)
{
	location = newLocation;
}

// Function - getLocation - to get the location
template <class DT>
string Node<DT>::getLocation()
{
	return location;
}

// node Destructor
template <class DT>
Node<DT>::~Node()
{
}

// class to store one edge's details
template <class DT>	 // template for Edge class
class Edge
{
protected:
	Node<DT>* u;     // field to store source node pointer
	Node<DT>* v;     // field to store destination node pointer
	string edgeInfo; // field to store edge information
	DT yearsKnown;   // u and v - years known

public:
	Edge(); // default constructor
	// getters
	Node<DT>* getu();
	Node<DT>* getv();
	string getEdgeInfo();
	DT getYearsKnown();

	// setters
	void setu(Node<DT>* newu);
	void setv(Node<DT>* newv);
	void setEdgeInfo(string newInfo, DT newYearsKnown);
	void setYearsKnown(DT newYear);

	void display(); // display edge details

	~Edge(); // destructor
};

// Edge default constructor
template <class DT>
Edge<DT>::Edge()
{
	Node<DT>* u = NULL;
	Node<DT>* v = NULL;
	edgeInfo = "";
	yearsKnown = -1;
}

// Function - setu - to read the value
template <class DT>
void Edge<DT>::setu(Node<DT>* newu)
{
	u = newu;
}

// Function - setv - to read the value
template <class DT>
void Edge<DT>::setv(Node<DT>* newv)
{
	v = newv;
}

// Function - setEdgeInfo - to read the string
template <class DT>
void Edge<DT>::setEdgeInfo(string newInfo, DT newYearsKnown)
{

	edgeInfo = newInfo;
	yearsKnown = newYearsKnown;
}

// Function - getu - to return the value
template <class DT>
Node<DT>* Edge<DT>::getu()
{
	return u;
}

// Function - getv - to return the value
template <class DT>
Node<DT>* Edge<DT>::getv()
{
	return v;
}

// Function - getEdgeInfo - to return the string
template <class DT>
string Edge<DT>::getEdgeInfo()
{
	return edgeInfo;
	//return localVar;
}

// Function - display
template <class DT>
void Edge<DT>::display()
{
	// displays the edge array when the display function in the GraphDB class calls
	if (u != NULL && v != NULL)
	{
		cout << u->getNodeInfo() << " - " << v->getNodeInfo()
			<< " " << edgeInfo << endl;
	}
}

// Function - setYearsKnown - to set the years known between each node
template <class DT>
void Edge<DT>::setYearsKnown(DT newYear)
{
	yearsKnown = newYear;
}

// Function - getYearsKnown - to get the years known
template <class DT>
DT Edge<DT>::getYearsKnown()
{
	return yearsKnown;
}


// Edge destructor
template <class DT>
Edge<DT>::~Edge()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph
template <class DT>	   // template for GraphDB class
class GraphDB
{
	//ostream operator for displaying myNodes and myEdges
	friend ostream& operator<<(ostream& os, GraphDB& gDB)
	{
		gDB.display();
		return os;
	}
protected:
	Node<DT>* myNodes; // array of nodes
	Edge<DT>* myEdges; // array of edges
	int numNodes;      // number of nodes
	int numEdges;      // number of edges
	int maxEdges;      // store the max number of edges (array size)

public:
	GraphDB(int nNodes, int nEdges); // non-default constructor
	// setters
	void setNode(Node<DT>& newNode);
	void setEdge(Edge<DT>& newEdge);
	void setNodeInfo(int u, string newInfo);
	void setEdgeInfo(int u, int v, string newInfo);

	// getters
	Node<DT>* getNode(int nodeNum);
	string getNodeInfo(int nodeNum);
	Edge<DT>* getEdgeInfo(int u, int v);

	// operations
	bool isAnEdge(int u, int v);     // is this edge existent
	void addEdge(Edge<DT>& newEdge); // add an edge
	void deleteEdge(int u, int v);   // delete the edge
	void display();                  // display the contents of the two arrays
	int* findNeighbours(int u);      // returns an integer array of neighbours' nodeNum

	~GraphDB(); // destructor
};

// GraphDB non-default constructor
template <class DT>
GraphDB<DT>::GraphDB(int nNodes, int mEdges)
{
	myNodes = new Node<DT>[nNodes];
	myEdges = new Edge<DT>[mEdges];
	numNodes = 0;
	maxEdges = mEdges;
	numEdges = 0;
}

// Function definition of - setNode
template <class DT>
void GraphDB<DT>::setNode(Node<DT>& newNode)
{
	myNodes[numNodes] = newNode;
	numNodes++;
}

// Function definition of - setEdge
template <class DT>
void GraphDB<DT>::setEdge(Edge<DT>& newEdge)
{
	if (numEdges >= maxEdges)
	{
		addEdge(newEdge); // calling - addEdge - function	
	}
	myEdges[numEdges] = newEdge;
	numEdges++;
}

// Function definition of - setNodeInfo
template <class DT>
void GraphDB<DT>::setNodeInfo(int u, string newInfo)
{
	// Loop to insert the values into the 'myNodes' array
	for (int i = 0; i < numNodes; i++)
	{
		if (myNodes[i].getNodeNumber() == u)
		{
			myNodes[i].setNodeInfo(newInfo);
		}
	}
}

// Function definition of - setEdgeInfo
template <class DT>
void GraphDB<DT>::setEdgeInfo(int u, int v, string newInfo)
{
	// Loop to insert the values into the 'myEdges' array
	for (int i = 0; i < maxEdges; i++)
	{
		if (u == myEdges[i].getu().getNodeNumber() && v == myEdges[i].getv().getNodeNumber())
		{
			myEdges[i].setEdgeInfo(newInfo);
		}
	}
}

// Function definition of - getNode
template <class DT>
Node<DT>* GraphDB<DT>::getNode(int nodeNum)
{
	int counter = 0;
	for (int i = 0; i < numNodes; i++)
	{
		if (myNodes[i].getNodeNumber() == nodeNum)
			return &myNodes[i];
		else
			counter++;
	}
	if (counter == numNodes)
		return NULL;
}

// Function definition of - getNodeInfo
template <class DT>
string GraphDB<DT>::getNodeInfo(int nodeNum)
{
	// Loop to read the Node information (nodeInfo) and returning the values
	for (int i = 0; i < numNodes; i++)
	{
		if (myNodes[i].getNodeNumber() == nodeNum)
			return myNodes[i].getNodeInfo();
	}
}

// Function definition of - getEdgeInfo
template <class DT>
Edge<DT>* GraphDB<DT>::getEdgeInfo(int u, int v)
{
	// Loop to read the Edges and returning the values
	for (int i = 0; i < numNodes; i++)
	{
		if (u == myEdges[i].getu()->getNodeNumber() && v == myEdges[i].getu()->getNodeNumber())
			return &myEdges[i];
	}
}

/*
*  Function definition of - isAnEdge -
*	works on checking the existance of edge and displays accordingly
*/
template <class DT>
bool GraphDB<DT>::isAnEdge(int u, int v)
{
	// Edge Loop
	for (int i = 0; i < numEdges; i++)
	{
		if (u == myEdges[i].getu()->getNodeNumber() && v == myEdges[i].getv()->getNodeNumber())
		{
			cout << "Edge exists between " << myEdges[i].getu()->getNodeInfo()
				<< " and " << myEdges[i].getv()->getNodeInfo() << endl;
			cout << endl;
			return true;
		}
	}
	cout << "No edge exists between " << getNodeInfo(u) << " and " << getNodeInfo(v) << endl;
	cout << endl;
	return true;
}

// Function - addEdge 
template <class DT>
void GraphDB<DT>::addEdge(Edge<DT>& newEdge)
{
	// re allocation of memory happens here
	maxEdges += 1;
	Edge<DT>* tempEdges = new Edge<DT>[maxEdges];

	// Copy old edges to new edges
	for (int i = 0; i < numEdges; i++)
	{
		//tempEdges[i].setEdgesInfo(newEdge);
		tempEdges[i].setu(myEdges[i].getu());
		tempEdges[i].setv(myEdges[i].getv());
		tempEdges[i].setEdgeInfo(myEdges[i].getEdgeInfo(), myEdges[i].getYearsKnown());
	}
	delete[] myEdges;
	myEdges = tempEdges;
}

// Function - deleteEdge - where deletion of myEdge array happens
template <class DT>
void GraphDB<DT>::deleteEdge(int u, int v)
{
	// guard
	if (numEdges == 0)
		return;

	int store = maxEdges / 2;

	// If numEdges becomes half of maxEdges
	if (numEdges == store)
	{
		Edge<DT>* temp = new Edge<DT>[store];
		for (int i = 0; i < store; i++)
		{
			temp[i] = myEdges[i];
		}
		delete[] myEdges;
		myEdges = temp;
	}

	// 1. Find the index position of the edge
	int edge_idx = -1; // edge index

	for (int i = 0; i < numEdges; i++)
	{
		if (myEdges[i].getu()->getNodeNumber() == u && myEdges[i].getv()->getNodeNumber() == v)
		{
			edge_idx = i;
			break;
		}
	}

	// 2. If the edge index position is not updated
	if (edge_idx == -1)
	{
		cout << "Removing the item " << u << " " << v << endl;
		cout << "Edge does not exist to be deleted" << endl;
		cout << endl;
	}
	else
	{
		// 3. If edge index is found then swap
		for (int i = edge_idx + 1; i < numEdges; i++)
			myEdges[i - 1] = myEdges[i];
		cout << "Removing the item " << u << " " << v << endl;
		cout << endl;
		numEdges--;

		
	}		
}

// Function - findNeighbours - where finding of neighbours for particular node number
template <class DT>
int* GraphDB<DT>::findNeighbours(int u)
{
	// 1. Find the number of neighbours for the given node
	int neighbours_count = 0;

	for (int i = 0; i < numEdges; i++)
	{
		if (myEdges[i].getu()->getNodeNumber() == u)
			neighbours_count++;
		if (myEdges[i].getv()->getNodeNumber() == u)
			neighbours_count++;
	}

	int* neighbours = new int[neighbours_count+1];		// array to store the count and the neighbours
	neighbours[0] = neighbours_count;					// storing the 0th position with the count
	int curr_neighbour = 1;				
	for (int i = 0; i < numEdges; i++)
	{
		if (myEdges[i].getu()->getNodeNumber() == u)
			neighbours[curr_neighbour++] = myEdges[i].getv()->getNodeNumber();
		if (myEdges[i].getv()->getNodeNumber() == u)
			neighbours[curr_neighbour++] = myEdges[i].getu()->getNodeNumber();
	}
	return neighbours;									// updated neighbours array
}


// This display function has been called by the Ostream operator of this GraphDB class
template <class DT>
void GraphDB<DT>::display()
{
	// 1. Node display (it calls getter functions in the Node class)
	cout << "Displaying myNodes: " << endl;
	for (int i = 0; i < numNodes; i++)
	{
		cout << myNodes[i].getNodeNumber() << ": "
			<< myNodes[i].getNodeInfo() << ", "
			<< myNodes[i].getYearCreated() << ", "
			<< myNodes[i].getLocation() << endl;
	}

	// 2. Edge display (it calls getter functions present in both Node and Edge classes)
	cout << "Displaying myEdges: " << endl;
	for (int i = 0; i < numEdges; i++)
	{
		cout << myEdges[i].getu()->getNodeInfo() << " - "
			<< myEdges[i].getv()->getNodeInfo() << " "
			<< myEdges[i].getEdgeInfo() <<", "
			<< myEdges[i].getYearsKnown() << endl;
	}
	cout << endl;
}

// GraphDB destructor
template <class DT>
GraphDB<DT>::~GraphDB()
{
	delete[] myEdges;
	delete[] myNodes;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//template <class DT>
int main()
{
	int numNodes; // temp variable to store numNodes from input
	int maxEdges; // temp variable to store maxEdges from input

	string nodeLabel; // temp variable to store the string value from the input
	string edgeLabel; // temp variable to store the string value from the input

	int yearsKnown;
	char command;   // reading a character in the file

	int u, v;
	cin >> numNodes;    // read the number of nodes
	cin >> maxEdges;    // read the maximum number of edges
	cout << "numNodes: " << numNodes << endl;	// display number of nodes
	cout << "maxEdges: " << maxEdges << endl;	// display maximum nodes
	cout << endl;

	GraphDB<int>* masterGraphInt; // pointer object of GraphDB class
	masterGraphInt = new GraphDB<int>(numNodes, maxEdges); // allocate memory by calling non-default constructor

	Node<int> tempNodeInt = Node<int>();	// temporary node object 

	// Inserting nodes into array
	for (int i = 0; i < numNodes; i++)
	{
		int nodeNum, date;
		string location;

		// 1. Reading node number and node label from redirected input file
		cin >> nodeNum >> nodeLabel >> date >> location;

		// 2. Temporary node initialization to set the node label and node information
		tempNodeInt.setNodeNumber(nodeNum);
		tempNodeInt.setNodeInfo(nodeLabel, date, location);
		tempNodeInt.setYearCreated(date);
		tempNodeInt.setLocation(location);

		/*
		*  3. Calling the set node function in the GraphDB class
		*		to insert node elements into myNodes array from temporary node
		*/
		masterGraphInt->setNode(tempNodeInt);
	}
	cin >> command;  // reading the command from redirected input file

	/*
	*	1. While loop continuous till the end of file
	*	2. The input command will be checked using the switch statement
	*	3. Based on the input command the cases will be selected
	*/

	// Temporary edge (tempEdge) initialization to set the edge values and information
	Edge<int> tempEdgeInt = Edge<int>();
	while (!cin.eof())
	{
		switch (command)
		{
		case 'I':	// case I
		{
			//	1. Reading two integer values and a string from the redirected input file
			cin >> u >> v >> edgeLabel >> yearsKnown;

			/* 2. Exception handling when a non existing values are trying to insert
			*		Checking the existance of node numbers, if there is no number
			*		the exception will be thrown
			*/		
			try
			{
					if (masterGraphInt->getNode(u) != NULL && masterGraphInt->getNode(v) != NULL)
					{
						tempEdgeInt.setu(masterGraphInt->getNode(u));
						tempEdgeInt.setv(masterGraphInt->getNode(v));
						tempEdgeInt.setEdgeInfo(edgeLabel, yearsKnown);
						masterGraphInt->setEdge(tempEdgeInt);
						cout << "Inserting " << u << " " << v << ": " << edgeLabel << ", " << yearsKnown << endl;

					}
					else
					{
						throw runtime_error("Node not a part of the graph");
					}
			}
			catch (const std::exception& e)
			{
				cout << "Inserting " << u << " " << v << ": " << edgeLabel << ", " << yearsKnown << endl;
				cout << e.what() << endl;
			}

			cout << endl;
			break;
		}
		case 'N':	// case N
		{
			cin >> u;
			
			// Calling - findNeighbours - function in master grapghDB
			int* neighbors = masterGraphInt->findNeighbours(u);
			int counter = neighbors[0];

			cout << "Neighbours of " << u << ": ";
			for (int i = 1; i <= counter; i++)
			{
				cout << neighbors[i] << " ";
			}

			cout << endl;
			cout << endl;
			break;
		}
		case 'D':	// case D
		{
			// Calling - displayNodesEdges - function in master grapghDB
			cout << *masterGraphInt;
			break;
		}
		case 'E':	// case E
		{
			// Reading two integer values from the redirected input file
			cin >> u >> v;

			// Calling - isAnEdge - function in master grapghDB
			masterGraphInt->isAnEdge(u, v);
			break;
		}
		case 'R':	// case R
		{
			// Reading two integer values from the redirected input file
			cin >> u >> v;
			masterGraphInt->deleteEdge(u, v);
			break;
		}
		default:	// default case
			cout << "nothing matches!!!!";
			break;
		}
		cin >> command;
	}
	delete masterGraphInt; // deleting the dynamically created pointer object after the program execution completes
	return 0;
}
