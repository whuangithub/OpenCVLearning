# Variable

## Declaring Variable

`type variable_name = values;`<br>
Example: `int my_number = 8;`

Or declare many same type variables in a same line

```
int x = 2, y = 3, z = 4;
cout << x + y + z
```

## **constant**

add the `const` keyword if you don't want others (or yourself) to override existing values. **unchangeable and read-only**

```
const int myNum = 15;  // myNum will always be 15
myNum = 10;  // error: assignment of read-only variable 'myNum'
```

## Display Variables

The cout object is used together with the << operator to display variables.

```
int myAge = 17;
cout << "I am " << myAge << " years old.";
```

# User Input

`cout` (pronounce: see-out) is used to output (print) values.<br>
Now we will use `cin` （see-in） to get user input.

`cin` is a predefined variable that reads data from the keyboard with the extraction operator (`>>`).

Example

```
int x;
cout << "Type a number";
cin >> x;
cout << "The number is" << x;
```

# Data Types

```
int myNum = 5;               // Integer (whole number)
float myFloatNum = 5.99;     // Floating point number
double myDoubleNum = 9.98;   // Floating point number
char myLetter = 'D';         // Character
//ASCII values for char
char a = 65                  // a = 'A'
bool myBoolean = true;       // Boolean
//add #include <string> to use string type
string myText = "Hello";     // String

float f1 = 35e3;             // Scientific Numbers 'e'
```

# Operators

## Arithmetic Operators

%: Returns the division remainder 5%2 => 1<br>
++: Increases the value of a variable by 1 (++x)<br>
--: Decreases the value of a variable by 1 (--x)

## Assignment Operators

```
=       x = 5        x = 5          
+=      x += 3       x = x + 3
-=      x -= 3       x = x - 3    
*=      x *= 3       x = x * 3
/=      x /= 3       x = x / 3
%=      x %= 3       x = x % 3      reminder
&=      x &= 3       x = x & 3      Bitwise AND
|=      x |= 3       x = x | 3      Bitwise OR
^=      x ^= 3       x = x ^ 3      Bitwise XOR
>>=     x >>= 3      x = x >> 3     Bitwise left shift assignment
<<=     x <<= 3      x = x << 3     Bitwise right shift assignment
```

## Comparison Operators

## Logical Operators

```
&&      Logical and
||      Logical or
!       Logical not
```

# String

Must include `<string>` library<br>
String concatenation: `+`<br>
String length: `text.length()`<br>
Access string: `[]`<br>
Changing Character in a string: `txt[1] = 'A'`<br>
getting imput: `getline(cin,var_name)`

# Math

`max(x,y)` `min(x,y)`<br>
`<cmath>` Header

# Booleans

# If...Else

## If statement

## Else statement

## Else if statement

```
if (condition1) {
// block of code to be executed if condition1 is true
} else if (condition2) {
// block of code to be executed if the condition1 is false and condition2 is true
} else {
// block of code to be executed if the condition1 is false and condition2 is false
}
```

## Short Hand If...else

Syntax: `variable = (condition) ? expressionTrue : expressionFalse;`<br>
Example:

```
string greeting = (time < 18)? "Good day":"Good evening";
```

# Switch

Use the `switch` statement to select one of many code blocks to be executed.<br>
Syntax

```
switch(expression) {
case x:
// code block
break;
case y:
// code block
break;
default:
// code block
}
```

When C++ reaches a `break` keyword, it breaks out of the switch block.

# While loop

## While Loop

```
while (condition) {
// code block to be executed
}
```

## Do/While loop

```
do {
// code block to be executed
}
while (condition);
```

# For Loop

```
for (statement 1 (initialize); statement 2(condition); statement 3(update)) {
// code block to be executed
}
```

`Statement 1` is executed (one time) before the execution of the code block.<br>
`Statement 2` defines the condition for executing the code block.<br>
`Statement 3` is executed (every time) after the code block has been executed.

# Break and Continue

The `break` statement can be used to jump out of a loop.<br>
The `continue` statement breaks one iteration (in the loop), if a specified condition occurs, and continues with the next iteration in the loop.

# Arrays

To declare an `array`, define the variable type, specify the name of the array followed by `[]` and specify the number of elements it should store.<br>
Example: `string cars[4]`

Assign values:`string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};`

## Access the elements in a array

refer to index number Example:

```
string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};
cout << cars[1];
// Outputs BMW
```

Change the value in a list by `cars[1]="Opel"`

## Omit array size

Don't have to specify the size of the array. And it will only be as big as the elements that are inserted into it:

```
string cars[] = {"Volvo", "BMW", "Ford"}; // size of array is always 3
```

If you want extra space for future elements, then you have to overwrite the existing values.<br>
If you specify the size, the array will reserve the extra space:

```
string cars[5] = {"Volvo", "BMW", "Ford"}; // size of array is 5, even though it's only three elements inside it
```

Now you can add a fourth and fifth element without overwriting the others:

```
string cars[3] = {"Mazda"};
string cars[4] = {"Tesla"};
```

# **References**

## Creating References

A reference variable is a "reference" to an existing variable, and it is created with the `&` operator:

```
string food = "Pizza";  // food variable
string &meal = food;    // reference to food
```

Now, we can use either the variable name `food` or the reference name `meal` to refer to the food variable.

## Memory address

In the example above, the `&` operator was used to create a reference variable. But it can also be used to get the memory address of a variable.

To access it, use the `&` operator, and the result will represent where the variable is stored:

```
string food = "Pizza";
cout << &food; // Outputs 0x6dfed4
```

`&` + var_name => memory address

# **Pointer**

A `pointer`, is a variable that **stores the memory address as its value**.

The **type** of the pointer has to match the type of the variable you're working with.

```
string food = "Pizza";  // A food variable of type string
string* ptr = &food;    // A pointer variable, with the name ptr, that stores the address of food. * is necessary

// Output the value of food (Pizza)
cout << food << "\n";

// Output the memory address of food (0x6dfed4)
cout << &food << "\n";

// Output the memory address of food with the pointer (0x6dfed4)
cout << ptr << "\n";
```

## Get Memory Address and Value

`*` + pointer_var => value of the variable<br>
`*` here is a new operator: the dereference operator

```
string food = "Pizza";  // Variable declaration
string* ptr = &food;    // Pointer declaration

// Reference: Output the memory address of food with the pointer (0x6dfed4)
cout << ptr << "\n";

// Dereference: Output the value of food with the pointer (Pizza)
cout << *ptr << "\n";
```

## Modify the Pointer Value

Assign new value to `*ptr` and the value of the variable will change as well

# Functions

## Create a Function

```
type_of_return myFunction() { // declaration
// the body of the function (definition)
}
```

It is possible to separate the `declaration` and the `definition` of the function - for code optimization.<br>
To have function declaration above `main()`, and function definition below `main()`.

```
// Function declaration
void myFunction();

// The main method
int main() {
myFunction();  // call the function
return 0;
}

// Function definition
void myFunction() {
cout << "I just got executed!";
}
```

## Parameters and Arguments

```
void functionName(type1 parameter1, type2 parameter2,type3 parameter3) {
// code to be executed
}
```

Example

```
void myFunction(string fname) {
cout << fname << " Refsnes\n";
}
```

### Default Parameter Values

```
void myFunction(string country = "Norway") {
cout << country << "\n";
}
```

### **Pass By Reference**

See [this link](https://www.mathwarehouse.com/programming/passing-by-value-vs-by-reference-visual-explanation.php)

When pass by value:<br>
The value in the memory is **copied** to another location to be used within the function

When pass by Reference:<br>
the **memory address** of the variable (a pointer to the memory location) is passed to the function => modify the original value directly

Example:

```
void swapNums(int &x, int &y) {
int z = x;
x = y;
y = z;
}

int main() {
int firstNum = 10;
int secondNum = 20;

cout << "Before swap: " << "\n";
cout << firstNum << secondNum << "\n";

// Call the function, which will change the values of firstNum and secondNum
swapNums(firstNum, secondNum);

cout << "After swap: " << "\n";
cout << firstNum << secondNum << "\n";

return 0;
}
```

If one delete the `&` sign in the code, the order of the numbers will not change.

#### _Function Overloading_

With **function overloading**, multiple functions can have the same name with different parameters:

```
int myFunction(int x)
float myFunction(float x)
double myFunction(double x, double y)
```

Instead of defining two functions that should do the same thing, it is better to overload one, like plus function.

### References

[Link](https://www.w3schools.com/cpp/default.asp)
