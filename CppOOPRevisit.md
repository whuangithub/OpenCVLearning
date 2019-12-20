# Classes and Objects

_Attributes_ and _methods_ are basically _variables_ and _functions_ that belongs to the class.

**class**: a user-defined data type, works as an object constructor.

## Create a Class

```
class MyClass {       // The class
	public:             // Access specifier
		int myNum;        // Attribute (int variable)
		string myString;  // Attribute (string variable)
};
```
## Create an Object

```
class MyClass {       // The class
	public:             // Access specifier
		int myNum;        // Attribute (int variable)
		string myString;  // Attribute (string variable)
};

int main() {
	MyClass myObj;  // Create an object of MyClass

	// Access attributes and set values
	myObj.myNum = 15;
	myObj.myString = "Some text";

	// Print attribute values
	cout << myObj.myNum << "\n";
	cout << myObj.myString;
	return 0;
}
```

# Methods

**Methods** are functions that belongs to the class.

## Inside Class Method

```
class MyClass {        // The class
	public:              // Access specifier
		void myMethod() {  // Method/function defined inside the class
			cout << "Hello World!";
		}
};

int main() {
	MyClass myObj;     // Create an object of MyClass
	myObj.myMethod();  // Call the method
	return 0;
}
```

## Outside Class Method

To define a function _outside_ the class definition, declare it inside the class and then define it outside of the class. Use `name_of_class::name_of_function`.
```
class MyClass {        // The class
	public:              // Access specifier
		void myMethod();   // Method/function declaration
};

// Method/function definition outside the class
void MyClass::myMethod() {
	cout << "Hello World!";
}

int main() {
	MyClass myObj;     // Create an object of MyClass
	myObj.myMethod();  // Call the method
	return 0;
}
```

## Class Constructor

A **constructor** in C++ is a special method that is automatically called when an object of a class is created.

To create a constructor, use the _same name as the class_, followed by parentheses `()`.
```
class MyClass {     // The class
	public:           // Access specifier
		MyClass() {     // Constructor
			cout << "Hello World!";
		}
};

int main() {
	MyClass myObj;    // Create an object of MyClass (this will call the constructor)
	return 0;
}
```

**Constructors** can also take parameters (just like regular functions), which can be useful for setting initial values for attributes.

```
class Car {        // The class
	public:          // Access specifier
		string brand;  // Attribute
		string model;  // Attribute
		int year;      // Attribute
		Car(string x, string y, int z) { // Constructor with parameters
			brand = x;
			model = y;
			year = z;
		}
};

int main() {
	// Create Car objects and call the constructor with different values
	Car carObj1("BMW", "X5", 1999);
	Car carObj2("Ford", "Mustang", 1969);

	// Print values
	cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << "\n";
	cout << carObj2.brand << " " << carObj2.model << " " << carObj2.year << "\n";
	return 0;
}
```
## Access Specifiers
```
class MyClass {  // The class
	public:        // Access specifier
		// class members goes here
};
```
The `public` keyword is an **access specifier**. **Access specifiers** define how the members (attributes and methods) of a class can be accessed.

* public - members are accessible from outside the class
* private - members cannot be accessed (or viewed) from outside the class (**default**)
* protected - members cannot be accessed from outside the class, however, they can be accessed in inherited classes.

## Encapsulation (封装 verb: encapsulate)

The meaning of **Encapsulation**, is to make sure that "sensitive" data is hidden from users. To achieve this, you must declare class variables/attributes as _private_ (cannot be accessed from outside the class). If you want others to read or modify the value of a private member, you can provide _public_ `get` and `set` methods.

```
#include <iostream>
using namespace std;

class Employee {
	private:
		// Private attribute
		int salary;

	public:
		// Setter
		void setSalary(int s) {
			salary = s;
		}
		// Getter
		int getSalary() {
			return salary;
		}
};

int main() {
	Employee myObj;
	myObj.setSalary(50000);
	cout << myObj.getSalary();
	return 0;
}
```

## Inheritance

To inherit from a class, use the `:` symbol.

```
// Base class
class Vehicle {
	public:
		string brand = "Ford";
		void honk() {
			cout << "Tuut, tuut! \n" ;
		}
};

// Derived class
// Car: child class
// Vehicle: parent class
class Car: public Vehicle {
	public:
		string model = "Mustang";
};

int main() {
	Car myCar;
	myCar.honk();
	cout << myCar.brand + " " + myCar.model;
	return 0;
}
// output:
// Tuut, tuut!
// Ford Mustang
```

### Multilevel Inheritance

parent -> child -> grandchild
### Multiple Inheritance

A class can also be derived from more than one base class, using a **comma-separated list**

```
// Base class
class MyClass {
	public:
		void myFunction() {
			cout << "Some content in parent class." ;
		}
};

// Another base class
class MyOtherClass {
	public:
		void myOtherFunction() {
			cout << "Some content in another class." ;
		}
};

// Derived class
// !!!!!!!!!!!!!!!!!!!!!!!!
class MyChildClass: public MyClass, public MyOtherClass {
};

int main() {
	MyChildClass myObj;
	myObj.myFunction();
	myObj.myOtherFunction();
	return 0;
}
```

### Access Specifiers
`protected`: can be accessed in the inherited class

## Polymorphism （多态）

override

## Files

`fstream` library

### Create and Write To a File

```
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	// Create and open a text file
	ofstream MyFile("filename.txt");

	// Write to the file
	// use << to write
	MyFile << "Files can be tricky, but it is fun enough!";

	// Close the file
	MyFile.close();
}
```

### Read a File
```
// Create a text string, which is used to output the text file
string myText;

// Read from the text file
ifstream MyReadFile("filename.txt");

// Use a while loop together with the getline() function to read the file line by line
while (getline (MyReadFile, myText)) {
	// Output the text from the file
	cout << myText;
}

// Close the file
MyReadFile.close();
```

## Exceptions

Exception handling in C++ consist of three keywords: `try`, `throw` and `catch`.

* The `try` statement allows you to define a block of code to be tested for errors while it is being executed.
* The `throw` keyword throws an exception when a problem is detected, which lets us create a custom error.
* The `catch` statement allows you to define a block of code to be executed, if an error occurs in the try block.

### try and catch
```
try {
	// Block of code to try
	throw exception; // Throw an exception when a problem arise
}
catch () {
	// Block of code to handle errors
}
```

```
try { // test some code with try               
	int age = 15;
	if (age > 18) {
		cout << "Access granted - you are old enough.";
	} else {
		throw (age); // throw an exception
	}
}
catch (int myNum) { //catch statement takes a parameter
	cout << "Access denied - You must be at least 18 years old.\n";
	cout << "Age is: " << myNum;
}
```

### Handle Any Type of Exceptions `(...)`

If one is not sure about the `throw` type, use `(...)`

```
try {
	int age = 15;
	if (age > 18) {
		cout << "Access granted - you are old enough.";
	} else {
		throw 505;
	}
}
catch (...) {
	cout << "Access denied - You must be at least 18 years old.\n";
}
``` 


### References

[Link](https://www.w3schools.com/cpp/default.asp)
