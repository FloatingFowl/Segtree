# Testing

Apart from testing the static methods and public member functions, tests were done (with maximum coverage) by choosing various types of data and functions for the Segment Tree.

Such tests involved creation and testing of multiple segment trees such that all the following were tested:
- Recursive segment tree where initial leaves have some single value
- Recursive segment tree where initial leaves are read from a `std::vector`
- Iterative segment tree where initial leaves have some single value
- Iterative segment tree where initial leaves are read from a `std::vector`

Various examples use different methods of the required `std::function<Data(Data &, Data &)>` instance as the binary function for the tree. 

All the following tests involve creating the tree, querying on it, updating on it, and querying yet again.

### Test 1 - `test_Lambda_ULLMultiplication`

Data : `unsigned long long int`
Function : Lambda that performs the operation `(a * b) mod P`
Notes : Only done for recursive type since `long long int{}` returns an instance with value 0. However the identity for the above lambda is 1. Special constructor must be added for invoking with default value in case of recursive type.

### Test 2 - `test_Functor_StringConcatenation`

Data : `std::string`
Function : Functor that returns the operation `a + b`, where both `a` and `b` are instances of `std::string`
Notes : Works for recursive and iterative type since `std::string{}` returns `""` which is the identity of the above functor.

### Test 3 - `test_FunctionPointer_MaximumSubarray`

Data : user-defined `struct`
Function : Pointer to function that returns maximum contiguous sum empty/non-empty subarray in a range, given two sibling range nodes of the form `[a - (b-1)], [b - c]`.
Notes : A standard segment tree application/problem implemented using both recursive and iterative versions.
