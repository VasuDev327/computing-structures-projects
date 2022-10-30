// Computing Structures Fall 2022
// DSA 5005
// Project 1
// Vasu Deva Sai Nadha Reddy Janapala

// headers
#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
class Node {
protected:
	int nodeNumber; // field to store node's number
	string nodeInfo; // field to store node's information
public:
	Node (); // default constructor
	// getters
	string getNodeInfo ();
	int getNodeNumber ();
	// setters
	void setNodeInfo (string newInfo);
	void setNodeNumber (int newNum);

	void display (); // display node details

};

//default constructor
Node :: Node ()
{
	nodeNumber = -1;
	nodeInfo = " ";
}

//Set Node Number
void Node::setNodeNumber(int newNum)
{
	nodeNumber = newNum;
}

//get Node Number
int Node::getNodeNumber()
{
	return nodeNumber;
}

//Set Node Information
void Node::setNodeInfo(string newInfo)
{
	nodeInfo = newInfo;
}

//Get Node Information
string Node :: getNodeInfo ()
{
	return nodeInfo;
}

// Display function to print both node number and node information
void Node :: display ()
{
	cout << nodeNumber << ": " << nodeInfo << endl;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store one edge's details
class Edge {
protected:
	Node* u; // field to store source node pointer
	Node* v; // field to store destination node pointer
	string edgeInfo; // field to store edge information
public:
	Edge (); // default constructor
	// getters
	Node& getu ();
	Node& getv ();
	string getEdgeInfo();
	// setters
	void setu (Node* newu);
	void setv (Node* newv);
	void setEdgeInfo (string newInfo);

	void display(); // display edge details


	
};

// Edge default constructor
Edge :: Edge ()
{
	Node* u = NULL;
	Node* v = NULL;
	edgeInfo = "";
}

// Function - setu - to read the value
void Edge :: setu (Node* newu)
{
	u = newu;
}

// Function - setv - to read the value
void Edge :: setv (Node* newv)
{
	v = newv;
}

// Function - setEdgeInfo - to read the string
void Edge::setEdgeInfo(string newInfo)
{
	edgeInfo = newInfo;
}

// Function - getu - to return the value
Node& Edge :: getu()
{
	return *u;
}

// Function - getv - to return the value
Node& Edge::getv()
{
	return *v;
}

// Function - getEdgeInfo - to return the string
string Edge::getEdgeInfo()
{
	return edgeInfo;
}

// Function - display
void Edge::display()
{
	// displays the edge array when the display function in the GraphDB class calls
	if (u != NULL && v != NULL)
	{
		cout << u->getNodeInfo() << " - " << v->getNodeInfo()
			<< " " << edgeInfo << endl;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph database
class GraphDB {
	protected:
		Node* myNodes; // array of nodes
		Edge* myEdges; // array of edges
		int numNodes; // number of nodes
		int numEdges; // current number of edges
		int maxEdges; // store the max number of edges (array size)
	public:
		GraphDB (int nNodes, int mEdges); // non-default constructor
		//setters
		void setNode (Node& newNode);
		void setEdge (Edge& newEdge);
		void setNodeInfo (int u, string newInfo);
		void setEdgeInfo (int u, int v, string newInfo);

		// getters
		Node* getNode (int nodeNum);
		string getNodeInfo (int nodeNum);
		Edge* getEdgeInfo (int u, int v);

		// operations
		bool isAnEdge (int u, int v); // is this edge existent
		void addEdge (Edge& newEdge); // add an edge
		void deleteEdge (int u, int v); // delete/remove the edge

		// display
		void displayNodesEdges();

};


// GraphDB non-default constructor
GraphDB :: GraphDB(int nNodes, int mEdges)
{
	myNodes = new Node[nNodes];
	myEdges = new Edge[mEdges];
	numNodes = 0;
	maxEdges = mEdges;
	numEdges = 0;
}

// Function definition of - setEdge
void GraphDB :: setNode(Node& newNode)
{
	myNodes[numNodes] = newNode;
	numNodes++;
}

// Function definition of - setEdge
void GraphDB :: setEdge(Edge& newEdge)
{
	if (numEdges >= maxEdges)
	{
		addEdge(newEdge); // calling - addEdge - function	
	}
	myEdges[numEdges] = newEdge;
	numEdges++;
}

// Function definition of - setNodeInfo
void GraphDB :: setNodeInfo(int u, string newInfo)
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
void GraphDB :: setEdgeInfo(int u, int v, string newInfo)
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
Node* GraphDB :: getNode(int nodeNum)
{
	// Loop to read the Nodes and return the values
	for (int i = 0; i < numNodes; i++)
	{
		if (myNodes[i].getNodeNumber() == nodeNum)
			return &myNodes[i];
	}
	
}
 // Function definition of - getNodeInfo
string GraphDB :: getNodeInfo(int nodeNum)
{
	// Loop to read the Node information (nodeInfo) and returning the values
	for (int i = 0; i < numNodes; i++)
	{
		if (myNodes[i].getNodeNumber() == nodeNum)
			return myNodes[i].getNodeInfo();
	}
}

// Function definition of - getEdgeInfo 
Edge* GraphDB :: getEdgeInfo(int u, int v)
{
	// Loop to read the Edges and returning the values
	for (int i = 0; i < numNodes; i++)
	{
		if (u == myEdges[i].getu().getNodeNumber() && v == myEdges[i].getu().getNodeNumber())
			return &myEdges[i];
	}
}

/* 
*  Function definition of - isAnEdge -
*	works on checking the existance of edge and displays accordingly
*/
bool GraphDB :: isAnEdge(int u, int v)
{
	// Edge Loop
	for (int i = 0; i < numEdges; i++)
	{
		if (u == myEdges[i].getu().getNodeNumber() && v == myEdges[i].getv().getNodeNumber())
		{
			cout << "Edge exists between " << myEdges[i].getu().getNodeInfo()
				<< " and " << myEdges[i].getv().getNodeInfo() << endl;
			cout << endl;
			return true;
		}
	}
	cout << "No edge exists between " << getNodeInfo(u) << " and " << getNodeInfo(v) << endl;
	cout << endl;
	return true;
}

// Function - addEdge 
void GraphDB :: addEdge(Edge& newEdge)
{
	// re allocation of memory happens here
	maxEdges += 1;
	Edge* tempEdges = new Edge[maxEdges];

	// Copy old edges to new edges
	for (int i = 0; i < numEdges; i++)
	{
		tempEdges[i].setu(&myEdges[i].getu());
		tempEdges[i].setv(&myEdges[i].getv());
		tempEdges[i].setEdgeInfo(myEdges[i].getEdgeInfo());
	}
	myEdges = tempEdges;
}

// Function - deleteEdge - where deletion of myEdge array happens
void GraphDB :: deleteEdge(int u, int v)
{
	// guard
	if (numEdges == 0)
		return;

	// 1. Find the idx position of the edge
	int edge_idx = -1;
	for (int i = 0; i < maxEdges; i++)
	{
		if (myEdges[i].getu().getNodeNumber() == u && myEdges[i].getv().getNodeNumber() == v)
		{
			edge_idx = i;
			break;
		}
	}
	
	// 2. If found, then swap swap swap
	for (int i = edge_idx + 1; i < numEdges; i++)
		myEdges[i - 1] = myEdges[i];
	cout << "Removing " << u << " " << v << endl;
	cout << endl;
	numEdges--;
}

// Function to display both nodes and edges
void GraphDB :: displayNodesEdges()
{
	// 1. Node display (it calls getter functions in the Node class)
	cout << "Displaying myNodes: " << endl;
	for (int i = 0; i < numNodes; i++)
	{
		cout << myNodes[i].getNodeNumber() << ":" << myNodes[i].getNodeInfo() << endl;
	}

	// 2. Edge display (it calls getter functions present in both Node and Edge classes)
	cout << "Displaying myEdges: " << endl; 
	for (int i = 0; i < numEdges; i++)
	{
		cout << myEdges[i].getu().getNodeInfo() << " - "
			<< myEdges[i].getv().getNodeInfo() << " "
			<< myEdges[i].getEdgeInfo() << endl;
	}
	cout << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Main Function
int main()
{
	int numNodes; // temp variable to store numNodes from input
	int maxEdges; // temp variable to store maxEdges from input

	string nodeLabel; // temp variable to store the string value from the input
	string edgeLabel; // temp variable to store the string value from the input

	char command;   // reading a character in the file

	int u, v;
	cin >> numNodes;    // read the number of nodes
	cin >> maxEdges;    // read the maximum number of edges
	cout << "numNodes: " << numNodes << endl;	// display number of nodes
	cout << "maxEdges: " << maxEdges << endl;	// display maximum nodes
	cout << endl;

	GraphDB* masterGraph; // pointer object of GraphDB class
	masterGraph = new GraphDB(numNodes, maxEdges); // allocate memory by calling non-default constructor

	// Inserting nodes into array
	for (int i = 0; i < numNodes; i++)
	{
		int nodeNum; 

		// 1. Reading node number and node label from redirected input file
		cin >> nodeNum >> nodeLabel; 

		// 2. Temporary node initialization to set the node label and node information
		Node tempNode = Node(); 
		tempNode.setNodeInfo(nodeLabel);
		tempNode.setNodeNumber(nodeNum);

		/* 
		*  3. Calling the set node function in the GraphDB class
		*		to insert node elements into myNodes array from temporary node
		*/
		masterGraph->setNode(tempNode);
	}

	cin >> command;  // reading the command from redirected input file

	/* 
	*	1. While loop continuous till the end of file
	*	2. The input command will be checked using the switch statement
	*	3. Based on the input command the cases will be selected
	*/
	while (!cin.eof())
	{
		switch (command)
		{
		case 'I':	// case I
		{
			//	1. Reading two integer values and a string from the redirected input file
			cin >> u >> v >> edgeLabel;
			
			//  2. Temporary edge (tempEdge) initialization to set the edge values and information
			Edge tempEdge = Edge();
			tempEdge.setu(masterGraph->getNode(u));
			tempEdge.setv(masterGraph->getNode(v));
			tempEdge.setEdgeInfo(edgeLabel);

			/*
			*	3. Calling the set edge function in the GraphDB class
			*		to insert edge elements into myEdges array from temporary edge
			*/
			masterGraph->setEdge(tempEdge);

			//	4. Displaying the inserted values
			cout << "Inserting " << u << " " << v << ": " << edgeLabel << endl;
			cout << endl;
			break;
		}
		case 'D':	// case D
		{
			// Calling - displayNodesEdges - function in master grapghDB
			masterGraph->displayNodesEdges();
			break;
		}
		case 'E':	// case E
		{
			// Reading two integer values from the redirected input file
			cin >> u >> v;

			// Calling - isAnEdge - function in master grapghDB
			masterGraph->isAnEdge(u, v);
			break;
		}
		case 'R':	// case R
		{
			// Reading two integer values from the redirected input file
			cin >> u >> v;

			// Calling - deleteEdge - function in master grapghDB
			masterGraph->deleteEdge(u, v);
			break;
		}
		default:	// default case
			cout << "nothing matches!!!!";
			break;
		}
	cin >> command;
	}
	return 0;
}
