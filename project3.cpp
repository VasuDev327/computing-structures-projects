// DSA 5005 - Computing Structures
// Fall 2022
// Vasu Deva Sai Nadha Reddy Janapala 
// Project 3

#include <iostream>
#include <string>  // for the string fields
#include <vector>  // to store data
#include <fstream> // to read the csv file

using namespace std;


// class to store one row's information
class DFrow
{
protected:
	// all the fields to store information of a row
	string name;
	char sex;
	int age;
	int height;
	int weight;
	string city;

public:
	DFrow(); // default constructor
	DFrow(string n, char c, int one, int two, int three, string ci); // non-default constructor
	
	// getters
	string getName();
	char getSex();
	int getAge();
	int getHeight();
	int getWeight();
	string getCity();


	// setters
	void setName(string n);
	void setSex(char c);
	void setAge(int one);
	void setHeight(int two);
	void setWeight(int three);
	void setCity(string ci);

	// friend function to display the output
	friend ostream& operator<<(ostream& stream, const DFrow row)
	{
		stream
			<< row.name << " "
			<< row.sex << " "
			<< row.age << " "
			<< row.height << " "
			<< row.weight << " "
			<< row.city << endl;

		return stream;
	}

	// destructor
	~DFrow();
};

// default DFrow constructor
DFrow::DFrow()
{
	name = " ";
	sex = ' ';
	age = -1;
	height = -1;
	weight = -1;
	city = " ";
}

// non-default constructor
DFrow::DFrow(string n, char c, int one, int two, int three, string ci)
{
	name = n;
	sex = c;
	age = one;
	height = two;
	weight = three;
	city = ci;
}

// setName method
void DFrow::setName(string n)
{
	name = n;
}

// getName method
string DFrow::getName()
{
	return name;
}

// setSex method
void DFrow::setSex(char c)
{
	sex = c;
}

// getSex method
char DFrow::getSex()
{
	return sex;
}

// setAge method
void DFrow::setAge(int one)
{
	age = one;
}

// getAge method
int DFrow::getAge()
{
	return age;
}

// setHeight method
void DFrow::setHeight(int two)
{
	height = two;
}

// getHeight method
int DFrow::getHeight()
{
	return height;
}

// setWeight method
void DFrow::setWeight(int three)
{
	weight = three;
}

// getWeight method
int DFrow::getWeight()
{
	return weight;
}

// setCity method
void DFrow::setCity(string ci)
{
	city = ci;
}

// getCity method
string DFrow::getCity()
{
	return city;
}

// Destructor
DFrow::~DFrow()
{
}

// class to store the entire dataframe
class DataFrame
{
protected:
	vector<DFrow> data; // field storeing all the data
	vector<string> headers; // field to only the headers
	int nRows, nCols; // store the number of rows and cols

public:
	// Constructors
	DataFrame();
	DataFrame(int rows, int cols);

	// Overload the [] operator to access data in DF
	DFrow operator[](int i);

	// File reading Method
	void readCSV(string filename, string headerPresence);

	// Output Method
	void display();

	// Search Record
	DFrow searchRecord(string name);

	// Setters
	void setColName(int col, char* name); // change the name of a header/column

	// Getters
	int getNumberRows();                                              // returns the number of rows
	int getNumberCols();                                              // returns the number of columns
	DataFrame* getRows(int* rows, int rLen);                          // returns a data frame with a set of rLen number of rows
	string getHeader(int i);                                          // returns the header name given a index position

	// Find info of a given column
	double findAverage(int colNumber); // returns the average of the given column
	double findMax(int colNumber);     // returns the max of the given column
	double findMin(int colNumber);     // returns the min of the given column
	double frequency(int colNumber);   // displays the frequency of the unique values

	// Destructor
	~DataFrame();
};

// default dataframe constructor
DataFrame::DataFrame() {
	data = {};
	headers = {};
	nRows = -1;
	nCols = -1;
}

// non-default constructor
DataFrame::DataFrame(int rows, int cols) {
	data = {};
	headers = {};
	nRows = rows;
	nCols = cols;
}

// Overload the [] operator to access data in DF
DFrow DataFrame::operator[](int i) {
	return data[i];
}

// reading both headers and data from readCSV method
void DataFrame::readCSV(string filename, string headerPresence)
{
	string records;
	fstream fVal;
	fVal.open(filename); // open the csv file

	// guards - checking if file is opening
	if (fVal.fail()) {
		cout << "no data!!!!" << endl;
	}
	// if file opens
	else {
		int count = 1;

		string x;
		string delimiter_char = ",";
		size_t pos = 0;
		string token;
		vector<string> storingData;

		// extracting the headers
		if (headerPresence == "true") {
			while (getline(fVal, records, '\n')) {
				x = records;
				break;
			}

			while ((pos = x.find(delimiter_char)) != string::npos && count < nCols) {
				token = x.substr(0, pos);
				x.erase(0, pos + delimiter_char.length());
				headers.push_back(token);
				count++;
			}
			if (count == nCols)
				headers.push_back(x);
		}

		// extracting the data
		for (int i = 0; i < nRows; i++) {
			getline(fVal, records, '\n');
			storingData.push_back(records);
		}

		// pushing the data
		for (int i = 0; i < nRows; i++) {
			int count1 = 0;
			DFrow rowData;
			while ((pos = storingData[i].find(delimiter_char)) != string::npos && count1 < nCols) {
				token = storingData[i].substr(0, pos);
				storingData[i].erase(0, pos + delimiter_char.length());
				count1++;

				// pushing the data based on the columns
				if (count1 == 1)
					rowData.setName(token);
				if (count1 == 2) {
					char charConvertion = token[0];
					rowData.setSex(charConvertion);
				}
				if (count1 == 3) {
					int intConvertion = stoi(token);
					rowData.setAge(intConvertion);
				}
				if (count1 == 4) {
					int intConvertion = stoi(token);
					rowData.setHeight(intConvertion);
				}
				if (count1 == 5) {
					int intConvertion = stoi(token);
					rowData.setWeight(intConvertion);
					count1++;
				}
				if (count1 == 6)
					rowData.setCity(storingData[i]);
			}
			data.push_back(rowData); // pushing or inserting the entire into the dfrow vector data
		}
	}	
}

// displaying the headers and data
void DataFrame::display()
{
	cout << " ";
	// headers loop
	for (int i = 0; i < nCols; i++)
	{
		cout << headers[i] << " ";
	}
	cout << endl;
	// data loop
	for (int i = 0; i < nRows; i++)
	{
		cout << data[i];
	}
	cout << endl;
}

// search a particular record based on the name
DFrow DataFrame::searchRecord(string name)
{
	DFrow temp;
	for (int i = 0; i < nRows; i++) {
		if (data[i].getName() == name)
			return data[i];
	}
	return temp;
}

void DataFrame::setColName(int col, char* name)
{

}

// getting the number of rows
int DataFrame::getNumberRows()
{
	return nRows;
}

// getting the number of columns
int DataFrame::getNumberCols()
{
	return nCols;
}

// using the method getRows to access particular rows

DataFrame* DataFrame::getRows(int* rows, int rLen) // Start, End
{
	//cout << "DEBUG: " << *rows << rLen << endl;

	// *rows will have the starting value, rLen tells the end value
	DataFrame* newData = new DataFrame(rLen - *rows, 0);
	for (int i = *rows; i < rLen; i++)
		newData->data.push_back(data[i]);

	return newData;
}

// getting the headers
string DataFrame::getHeader(int i)
{
	return headers[i];
}

/*this method findAverage helps to 
* find the average value of the entire numerical column
* based on the given column number
*/
double DataFrame::findAverage(int colNumber)
{
	int sum, avgValue, i;
	sum = 0;

	if (colNumber == 0)
		return -1;
	else if (colNumber == 1)
		return -1;
	else if (colNumber == 2)
	{
		for (i = 0; i < nRows; i++)
			sum = sum + data[i].getAge();
		avgValue = sum / i;
		return avgValue;
	}
	else if (colNumber == 3)
	{
		for (i = 0; i < nRows; i++)
			sum = sum + data[i].getHeight();
		avgValue = sum / i;
		return avgValue;
	}
	else if (colNumber == 4)
	{
		for (i = 0; i < nRows; i++)
			sum = sum + data[i].getWeight();
		avgValue = sum / i;
		return avgValue;
	}
	else if (colNumber == 5)
		return -1;
}

/*this method findMax helps to
* find the maximum value of the entire numerical column
* based on the given column number
*/
double DataFrame::findMax(int colNumber)
{
	double count, maxValue, i;
	count = 0;

	if (colNumber == 0)
		return -1;
	else if (colNumber == 1)
		return -1;
	else if (colNumber == 2)
	{
		maxValue = data[count].getAge();
		for (i = 1; i < nRows; i++) {
			if (maxValue < data[i].getAge()) {
				maxValue = data[i].getAge();
			}
		}
		return maxValue;
	}
	else if (colNumber == 3)
	{
		maxValue = data[count].getHeight();
		for (i = 1; i < nRows; i++) {
			if (maxValue < data[i].getHeight()) {
				maxValue = data[i].getHeight();
			}
		}
		return maxValue;
	}
	else if (colNumber == 4)
	{
		maxValue = data[count].getWeight();
		for (i = 1; i < nRows; i++) {
			if (maxValue < data[i].getWeight()) {
				maxValue = data[i].getWeight();
			}
		}
		return maxValue;
	}
	else if (colNumber == 5)
		return -1;
}


/*this method findMin helps to
* find the minimum value of the entire numerical column
* based on the given column number
*/
double DataFrame::findMin(int colNumber)
{
	double count, minValue, i;
	count = 0;

	if (colNumber == 0)
		return -1;
	else if (colNumber == 1)
		return -1;
	else if (colNumber == 2)
	{
		minValue = data[count].getAge();
		for (i = 1; i < nRows; i++) {
			if (minValue > data[i].getAge()) {
				minValue = data[i].getAge();
			}
		}
		return minValue;
	}
	else if (colNumber == 3)
	{
		minValue = data[count].getHeight();
		for (i = 1; i < nRows; i++) {
			if (minValue > data[i].getHeight()) {
				minValue = data[i].getHeight();
			}
		}
		return minValue;
	}
	else if (colNumber == 4)
	{
		minValue = data[count].getWeight();
		for (i = 1; i < nRows; i++) {
			if (minValue > data[i].getWeight()) {
				minValue = data[i].getWeight();
			}
		}
		return minValue;
	}
	else if (colNumber == 5)
		return -1;
}


/*this method frequency helps to
* find the number of occurences of the entire categorical column
* based on the given column number
*/
double DataFrame::frequency(int colNumber)
{
	double i, j, count = 0;
	string outerString, innerString;
	vector<char> tempCharVector;
	vector<string> tempStringVector;

	if (colNumber == 0)
	{
		for (i = 0; i < nRows; i++) {
			outerString = data[i].getName();
			for (j = 0; j < i; j++) {
				innerString = data[j].getName();
				if (outerString == innerString)
					break;
			}
			if (i == j)
				tempStringVector.push_back(data[j].getName());
		}
		int size = tempStringVector.size();
		for (i = 0; i < size; i++) {
			for (j = 0; j < nRows; j++) {
				if (tempStringVector[i] == data[j].getName())
					count++;
			}
			cout << tempStringVector[i] << ": " << count << endl;
			count = 0;
		}
		return 0;
	}

	if (colNumber == 1)
	{
		for (i = 0; i < nRows; i++) {
			outerString = data[i].getSex();
			for (j = 0; j < i; j++) {
				innerString = data[j].getSex();
				if (outerString == innerString)
					break;
			}
			if (i == j)
				tempCharVector.push_back(data[j].getSex());
		}
		int size = tempCharVector.size();
		for (i = 0; i < size; i++) {
			for (j = 0; j < nRows; j++) {
				if (tempCharVector[i] == data[j].getSex())
					count++;
			}
			cout << tempCharVector[i] << ": " << count << endl;
			count = 0;
		}
		return 0;
	}

	else if (colNumber == 5)
	{
		for (i = 0; i < nRows; i++) {
			outerString = data[i].getName();
			for (j = 0; j < i; j++) {
				innerString = data[j].getName();
				if (outerString == innerString)
					break;
			}
			if (i == j)
				tempStringVector.push_back(data[j].getName());
		}
		int size = tempStringVector.size();
		for (i = 0; i < size; i++) {
			for (j = 0; j < nRows; j++) {
				if (tempStringVector[i] == data[j].getName())
					count++;
			}
			cout << tempStringVector[i] << ": " << count << endl;
			count = 0;
		}
		return 0;
	}
	else {
		cout << "checking on numerical coulmns is invalid!!!!!" << endl;
		return 0;
	}
}

DataFrame::~DataFrame()
{

}

// main function
int main()
{
	int numRows, numCols;
	string fileName;
	string headerBool;
	char command;

	cin >> numRows >> numCols >> headerBool >> fileName; // reading from the rediredcted input file
	
	DataFrame *d = new DataFrame(numRows, numCols);
	DFrow catchingObj1, catchingObj2;

	d->readCSV(fileName, headerBool); // method to read in the data from the csv file

	// read the commands from the input file (redirected input)
	string label;
	cin >> command;
	string header;
	double x;

	// 
	while (!cin.eof()) {
		switch (command) {
		case 'F': // case F
		{
			//	1. Reading input value from the redirected input file
			cin >> label;

			/* 2. Exception handling when a non existing input values are trying to print
			*		Checking the existance of the record wth that input value, if there is no value
			*		the exception will be thrown
			*/
			try {
				catchingObj1 = d->searchRecord(label);
				if (catchingObj1.getAge() != catchingObj2.getAge())
					cout << "Record found:" << '\n' << "	" << catchingObj1 << endl;
				else
					throw runtime_error("Record not found!!!!");
			}
			catch(const std::exception& e) {
				cout << e.what() << '\n' << endl;
			}
			break;
		}
		case 'D': // case D
		{
			d->display(); // to display the data
			break;
		}
		case 'A': // case A
		{
			//	1. Reading input value from the redirected input file
			cin >> label;

			// 2. loop to check whether input value exist or not
			for (int m = 0; m < numCols; m++) {
				header = d->getHeader(m);

				//3. if input value is available it enters into the following
				//  	if statement and calls the findAverage method
				if (label == header) {
					x = d->findAverage(m);
					//4. if the value is not numerical the following if statement executes 
					if (x == -1)
						cout << "Average for " << header
						<< " cannot be found since it is nan" << endl;
					//5. if the value is numerical the following if statement executes
					else if(x >= 0)
						cout << "Average of " << header << " is " << x << endl;
					break;
				}
			}
			break;
		}
		case 'Q': // case Q
		{
			//	1. Reading input value from the redirected input file
			cin >> label;

			// 2. loop to check whether input value exist or not
			for (int i = 0; i < numCols; i++) {
				header = d->getHeader(i);
				//3. if it exist the following loop calls the frequency method
				//		where the outs are only on categorical columns
				if (label == header) {
					d->frequency(i);
					break;
				}
			}
			break;
		}
		case 'X': // case X
		{
			//	1. Reading input value from the redirected input file
			cin >> label;
			
			// 2. loop to check whether input value exist or not
			for (int i = 0; i < numCols; i++) {
				header = d->getHeader(i);

				//3. if input value is available it enters into the following
				//  	if statement and calls the findMax method
				if (label == header) {
					x = d->findMax(i);
					//4. if the value is not numerical the following if statement executes
					if (x == -1)
						cout << "Max for " << header
						<< " cannot be found since it is nan" << endl;
					//5. if the value is numerical the following if statement executes
					else if(x >= 0)
						cout << "Max of " << header << " is " << x << endl;
					break;
				}
			}
			break;
		}
		case 'I': // case I
		{
			//	1. Reading input value from the redirected input file
			cin >> label;

			// 2. loop to check whether input value exist or not
			for (int i = 0; i < numCols; i++) {
				header = d->getHeader(i);

				//3. if input value is available it enters into the following
				//  	if statement and calls the findMin method
				if (label == header) {
					x = d->findMin(i);
					//4. if the value is not numerical the following if statement executes
					if (x == -1)
						cout << "Min for " << header
						<< " cannot be found since it is nan" << endl;
					//5. if the value is numerical the following if statement executes
					else if (x >= 0)
						cout << "Min of " << header << " is " << x << endl;
					break;
				}
			}
			break;
		}
		case 'R': // case R
		{
			int start, end;

			// Reading input value from the redirected input file
			cin >> start >> end;
			//cout << endl;

			// calling the getRow method to display certain rows from the entire data
			DataFrame * tempDF = d->getRows(&start, end);
			tempDF->display();

			delete tempDF;
			break;
		}
		default:	// default case
			cout << "nothing matches!!!!" << endl;
			break;
		}
		cin >> command;
	}
	delete d;
	return 0;
}
