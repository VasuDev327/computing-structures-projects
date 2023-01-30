// Project 4
// Fall 2022
// Computing Structures
// Vasu Deva Sai Nadha Reddy Janapala

#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list

using namespace std;

class GL; // prototype for class GL

// node class to store char and generalized linked list called down
class node
{
protected:
    char* charVariable; // single char variable pointer (not an array)
    GL* down;           // going down to the next level

public:
    node(); // default constructor

    // setters
    void setCharVariable(char var);
    void setDown(GL* d);

    // getters
    char* getChar();
    GL* getDown();

    // display
    void displayChar();
};

// default constructor
node::node() {
    charVariable = NULL;
    down = NULL;
}

// setter - charVariable
void node::setCharVariable(char var) {
    charVariable = new char();
    *charVariable = var;
}

// setter - for down pointer
void node::setDown(GL* d) {
    down = d;
}

// getter for charVariable
char* node::getChar() {
    return charVariable;
}

// getter for down pointer
GL* node::getDown() {
    return down;
}

// displayChar -  to display the characters
void node::displayChar() {
    cout << charVariable;
}


// class Generalized List
class GL
{
protected:
    list<node> head; // head of the list - each object is of type node class

public:
    GL();                                         // default constructor
    void buildGL(string l);                       // to build the generalized list
    bool findCharInExpression(char findThisChar); // given a char, find it in a given expression
    int heightOfGL();                             // return the height of the GL using the GL
    int LCAdistance(char char1, char char2);      // find the LCA distance of two char in the expression
    void searchDuplicates();                      // print all the duplicates in the GL
    void display();                               // display list
    string stringFunction();                      // user defined helper method
    
};

// default GL constructor
GL::GL() {

}

// buildGL method - to build the generalized list
void GL::buildGL(string l) {

    string expression = l;
    /*
        counter to count the open parenthesis -
                - and decrement the same when close parenthesis comes
    */
    int counter = 0;
    int nullCounter = 0;
    size_t length = expression.length();
    size_t i, k;
    node tempNode;
    GL* tempGl = new GL();
    string newString = ""; // empty string to filter the inner strings
    // filtering data from the parenthesis looping 
    for (i = 0; i < length; i++) {
        // the below if statement to avoid initial open parethesis
        if (expression[i] == '(') {
            counter++;
            if (counter > 1)
                newString = newString + expression[i];
        }
        // below else if statement to decrement the counter when a close parenthesis occurs
        else if (expression[i] == ')') {
            counter--;
        }
        // the below else if statement helps to set the down pointer
        else if ((expression[i] != '(' || expression[i] != ')') && (counter > 1)) {

            k = i;
            while (nullCounter + 1 < counter) {
                newString = newString + expression[k];
                if (expression[k] == ')')
                    nullCounter++;
                k++;
            }
            // recursion method buildGL for the newString(sub string)
            tempGl->buildGL(newString);
            i = k - 1;
            tempNode.setCharVariable(NULL);
            tempNode.setDown(tempGl);
            head.push_back(tempNode);
            counter = counter - nullCounter;
        }
        // the below else if statement set the character variable 
        else if (expression[i] != '(' || expression[i] != ')') {
            tempNode.setCharVariable(expression[i]);
            tempNode.setDown(NULL);
            head.push_back(tempNode);
        }
    }
}



// LCAdistance method to find the Least Common Ancestor -
//              - between two characters in an expression
int GL::LCAdistance(char char1, char char2) {
    list<node>::iterator it;
    int levelCharA = 0;
    int levelCharB = 0;
    int countA = 0;
    int countB = 0;
    for (it = head.begin(); it != head.end(); ++it) {
        if (*(it->getChar()) == NULL) {
            if (levelCharA == 0 || levelCharB == 0) {
                if (levelCharA <= 0) {
                    countA++;
                    levelCharA = levelCharA + it->getDown()->LCAdistance(char1, '\0');
                }
                if (levelCharB <= 0) {
                    countB++;
                    levelCharB = levelCharB + it->getDown()->LCAdistance('\0', char2);

                }
                if ((levelCharA == levelCharB) && (countA > 0 && countB > 0))
                    return levelCharA;
                else
                {
                    if (countB > 0)
                        levelCharB++;
                    if (countA > 0)
                        levelCharA++;
                }
            }
        }
        else {
            if (*(it->getChar()) == char1) {
                levelCharA++;
                continue;
            }
            else if (*(it->getChar()) == char2) {
                levelCharB++;
                continue;
            }
        }
        if ((levelCharA != 0 && levelCharB != 0) && (levelCharA == levelCharB)) {
            return levelCharA;
        }
    }
    while (it == head.end()) {
        if (levelCharA < levelCharB)
            return levelCharB;
        else if (levelCharA == levelCharB)
            return levelCharA;
        else if (levelCharA > levelCharB)
            return levelCharA;
    }
}

/*
    findCharInExpression - from the given expression,
                a character can be found using this method
                                        return type is boolean....
*/
bool GL::findCharInExpression(char findThisChar) {
    list<node>::iterator it;
    bool check = false;
    for (it = head.begin(); it != head.end(); ++it) {
        if (*(it->getChar()) == NULL)
            // recursive findCharInExpression
            check = it->getDown()->findCharInExpression(findThisChar);
        else if (*(it->getChar()) == findThisChar) {
            return true;
            break;
        }
    }
    if (check)
        return check;
    else
        return false;
}

// heightOfGL method - returns the height of the required expression
int GL::heightOfGL() {
    list<node>::iterator it;
    int count = 1;
    for (it = head.begin(); it != head.end(); ++it) {
        if (*(it->getChar()) == NULL)
            // recursive heightOfGL method
            count = count + it->getDown()->heightOfGL();
    }
    return count;
}

// user defined helper method to create a string and passing the -
//                   -  string to the searchDuplicates method
string GL::stringFunction() {
    list<node>::iterator it;
    string newString = "";
    string dummyString = "";
    for (it = head.begin(); it != head.end(); ++it) {
        if (*(it->getChar()) == NULL) {
            // recursion of stringFunction method
            dummyString = it->getDown()->stringFunction();
            newString = newString + dummyString;
        }
        else
            newString = newString + *(it->getChar());
    }
    return newString;
}


// searchDuplicates method to find number of duplicates in a given expression
void GL::searchDuplicates() {
    list<node>::iterator it;
    // calling helper stringFunction method to get the entire expression in the form of string
    string checking = stringFunction();
    int count = 0;
    int stringLength = checking.length();
    // using nested loop to check the duplicates
    for (int i = 0; i < stringLength; i++) {
        for (int j = i + 1; j < stringLength; j++) {
            if (checking[i] == checking[j]) {
                count++;
                cout << checking[i] << " "; // in case if there are multiple duplicates
                break;
            }
        }
    }
    if (count == 0)
        cout << "No duplicates" << endl;
}

// display method to print all the characters present in the entire expression
void GL::display() {
    list<node>::iterator it;
    for (it = head.begin(); it != head.end(); ++it) {
        if (*(it->getChar()) == NULL) {
            // recursing the display method to print the characters
            //                               under the down pointer
            it->getDown()->display();
        }
        else
            // printing characters
            cout << *(it->getChar()) << " ";
    }
}

// main
int main()
{
    int numExpressions; // number of expressions
    char option;        // command from the input file

    int expressionNumber; // to read a number from a redirected input file
    char character;       // to read a character from a redirected input file
    char charA, charB;    // to read the characters from a redirected input file for LCA

    // read the number of expressions given
    cin >> numExpressions;
    cout << "Number of expressions: " << numExpressions << endl;

    GL* expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects
    string expression;
    // read one line/expression at a time and call the buildGL method for each expression[i]
    for (int i = 0; i < numExpressions; i++) {
        cin >> expression;
        expressions[i].buildGL(expression);
    }

    cout << endl;


    // read in and process all the options using switch case
    cin >> option;
    while (!cin.eof()) {
        switch (option) {
        // case D to display every character in the expression
        case 'D': {
            cout << "Displaying all expressions: " << endl;
            for (int i = 0; i < numExpressions; i++) {
                cout << "Expression " << i << " : ";
                expressions[i].display(); // calling display function in the GL class
                cout << endl;
            }
            break;
        }
        // case F to check whether the given character is present in an expression or not 
        case 'F': {
            cin >> expressionNumber;
            cin >> character;
            bool check;
            // calling findCharInExpression method in the class GL
            check = expressions[expressionNumber].findCharInExpression(character);
            if (check)
                cout << "Find " << character << " in "
                << expressionNumber << ": " << "found" << endl;
            else
                cout << "Find " << character << " in "
                << expressionNumber << ": " << "not found" << endl;
            break;
        }
        // case H to check the height of every expression
        case 'H': {
            cin >> expressionNumber;
            int heightValue;
            // calling the heightOfGL method in the class GL
            heightValue = expressions[expressionNumber].heightOfGL();
            cout << "Height of expression "
                << expressionNumber << " : " << heightValue << endl;
            break;
        }
        // case U to check the duplicates exists or not in the given expression
        case 'U': {
            cin >> expressionNumber;
            cout << "Duplicates in " << expressionNumber << " : ";
            // calling the searchDuplicates method in the class GL
            expressions[expressionNumber].searchDuplicates();
            break;
        }
        // case L to check the least common ancestor between the two characters
        case 'L': {
            cout << endl;
            cin >> expressionNumber;
            cin >> charA >> charB;
            int lcaDistance;
            // calling LCAdistance method in the class GL
            lcaDistance = expressions[expressionNumber].LCAdistance(charA, charB);
            cout << "LCA distance between " << charA << " and " << charB << " in expression "
                << expressionNumber << " : "
                << lcaDistance << endl;
            break;
        }
        // default - in case of invalid input
        default: {
            cout << "invalid input character" << endl;
        }
        }
        cout << endl;
        cin >> option;
    }
    return 0;
}
