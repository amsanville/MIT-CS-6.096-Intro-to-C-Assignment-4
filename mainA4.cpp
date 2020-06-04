#include"myStack.h"
#include"myGraph.h"
#include<iostream>

/*
2.1
Compares to elements of the type T with the < operator returning the minimum
*/
template<class T>
T min(const T a, const T b) {
	return a < b ? a : b;
}

/*
2.2
Here I'm defining getMin in a preprocessor macro. This acts like a find and
replace for getMin. At compile time, it replaces all instances of getMin(a, b)
with a < b ? a : b.
*/
#define getMin(a, b) (a < b ? a : b)

/*
For testing purposes, I created a class that implements the < operator. In this
case, I use the point class from the previous assignment, with distance from
origin being the metric used for comparison.
*/
class Point {
private:
	double x, y;
public:
	Point(int u = 0, int v = 0) : x(u), y(v) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	// Accessors
	double getX() const { return x; }
	double getY() const { return y; }
	// Mutators
	void setX(int new_x) { x = new_x; }
	void setY(int new_y) { y = new_y; }

	// For Debugging
	void print() const {
		std::cout << "(" << x << ", " << y << ")";
	}
};

// Implementation of non-member operator overloading of <
inline bool operator<(const Point &lhs, const Point &rhs) {
	return (pow(lhs.getX(), 2.) + pow(lhs.getY(), 2.)) < (pow(rhs.getX(), 2.) + pow(rhs.getY(), 2.));
}

///////////////////////////////////////////////////////////////////////////////
/*
Simplified version of the Polygon class for the sake of playing around with
casting in Part 3. Mostly just want to play with casting between two child
classes.
*/
class Polygon {
protected:
	// Keeps track of vertices in the Polygon
	int* vertices;
	int size;
	// Keeps count of the number of Polygons instantiated
	static int count;
public:
	// Constructors
	// Default Constructor
	Polygon();
	// Constructor using array of points
	Polygon(const int arr[], int size);
	// Destructor
	~Polygon() { count--; }
	// Calculate the area
	virtual double area() const = 0;
	// Returns the number of polygons
	int getNumPolygons() { return count; };
	// Returns the number of sides
	int getNumSides() { return size; }
	// Returns the list of points
	const int* getPoints() { return vertices; }
};

// Initialize the count
int Polygon::count = 0;

// Constructor 1
Polygon::Polygon() : vertices(nullptr), size(0) {
	count++;
}

// Constructor 2
Polygon::Polygon(const int arr[], int size) {
	vertices = new int[size];
	for (int i = 0; i < size; i++) {
		vertices[i] = arr[i];
	}
	this->size = size;
	count++;
}

class Triangle : public Polygon {
public:
	// Constructor
	Triangle(int a, int b, int c);	
	// Made up area: negative sum of all the elements of the list of numbers
	double area() const {
		double totArea = 0;
		for (int i = 0; i < size; i++) {
			totArea -= vertices[i];
		}
		return (double)totArea;
	}
};

Triangle::Triangle(int a, int b, int c) {
	size = 3;
	vertices = new int[3];
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
}

class Rectangle : public Polygon {
public:
	Rectangle(int a, int b, int c, int d);
	// Made up area: sum of all the elements of the list of numbers
	double area() const {
		double totArea = 0;
		for (int i = 0; i < size; i++) {
			totArea += vertices[i];
		}
		return (double)totArea;
	}
};

Rectangle::Rectangle(int a, int b, int c, int d) {
	size = 4;
	vertices = new int[4];
	vertices[0] = a;
	vertices[1] = b;
	vertices[2] = c;
	vertices[3] = d;
}


int main() {
	// Initialize two points:
	Point a = Point(1, 1);
	Point b = Point(2, 2);
	
	// Run the tests
	std::cout << "Operator Overload test:" << std::endl;
	std::cout << "a < b: " << (a < b) << std::endl;

	// Template min
	std::cout << "\nTemplate minimum function:" << std::endl;
	std::cout << "Minimum of a, (1, 1), and b, (2, 2):  ";
	min(a, b).print();
	std::cout << std::endl;

	// Macro min
	std::cout << "\nMacro minimum function:" << std::endl;
	std::cout << "Minimum of a, (1, 1), and b, (2, 2): ";
	getMin(a, b).print();
	std::cout << std::endl;

	// 3 Casting
	Rectangle* rect = new Rectangle(1, 2, 3, 4);
	// This is an upcast
	Polygon* p = rect;
	// This is two types of downcasts
	Triangle* triS = static_cast<Triangle*>(p);
	Triangle* triD = dynamic_cast<Triangle*>(p);

	// 4 Stack
	// Test the stack
	Stack<int> testStack = Stack<int>();
	std::cout << "\nTesting Stack Class:" << std::endl;
	std::cout << "Empty: " << testStack.empty() << " (Expect 1)" << std::endl;
	testStack.push(25);
	std::cout << "Empty: " << testStack.empty() << " (Expect 0)" << std::endl;
	testStack.push(1);
	testStack.pop();
	std::cout << "Top: " << testStack.top() << " (Expect 25)" << std::endl;
	
	// Test the + operator
	testStack.pop();
	testStack.push(1);
	testStack.push(2);
	Stack<int> testStack2 = Stack<int>();
	testStack2.push(3);
	testStack2.push(4);
	Stack<int> testStack3 = Stack<int>();
	
	// Add two empty stacks together
	testStack3 = testStack3 + testStack3;
	std::cout << "Empty: " << testStack3.empty() << " (Expect 1)" << std::endl;
	// Add to testStack2
	testStack2 = testStack2 + testStack3;
	std::cout << "Empty: " << testStack3.empty() << " (Expect 0)" << std::endl;
	// Add to testStack
	testStack = testStack + testStack2;
	std::cout << "Empty: " << testStack3.empty() << " (Expect 0)" << std::endl;
	// Print out all in order of removal from the stack
	while (!testStack.empty()) {
		std::cout << "Top: " << testStack.top() << std::endl;
		testStack.pop();
	}

	// 5 Graphs
	// Initialize the graph in the pdf
	std::vector<int> starts = std::vector<int>({ 1, 1, 1, 5, 5, 4 });
	std::vector<int> ends = std::vector<int>({ 2, 3, 4, 4, 2, 2 });
	Graph testGraph = Graph(starts, ends);
	std::cout << "\nTest Graph Class:" << std::endl;
	std::cout << "Out-Going from 1: " << testGraph.numOutgoing(1) << "(Expect 3)" << std::endl;
	std::vector<int> outGoing1 = testGraph.adjacent(1);
	std::cout << "Out-Going nodes: " << std::endl;
	for (unsigned int i = 0; i < outGoing1.size(); i++) {
		std::cout << outGoing1[i] << ", ";
	}
	std::cout << "(Expect 2, 3, 4,)" << std::endl;

	// Try to make a poorly defined graph
	ends.push_back(1);
	try {
		Graph testGraph = Graph(starts, ends);
	}
	catch (std::invalid_argument & e) {
		std::cout << "Successfully caught!" << std::endl;
		std::cout << e.what() << std::endl;
	}
}