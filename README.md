# Segment Tree Repo

##### Usage:

Add `SegmentTree` class to your code by including the file `segtree.h`.

For running the basic file `main.cpp`, run `make` in the directory and then run the generated executable as `./segTree` from within the directory.

Similarly, compile `performance_testing.cpp` and run it for some performance testing. Usage is as `./performanceTesting <option> <number of elements>` where `<option>` may be 
- 1) Only queries
- 2) Only updates
- 3) Queries and Updates
The operations on the segment tree will equal the number of elements.

*Instructions on how to create the `SegmentTree` object and such will be added here soon.*

---

##### Things to be added:

- Performance testing (Have to present data)
- Code commentary/annotation
- ~~`Init` Functions (size later)~~
  - ~~`(vector of initial values of same type, function pointer or lambda)`~~
  - ~~`(initial value, function pointer or lambda)`~~
  - ~~Possible choice of iterative or recursive~~
- ~~`build` function~~
- ~~`query` function~~
- ~~`update` function~~
- ~~method to change function pointer or lambda~~
- ~~`print` method for testing~~

---

##### Files:

- `segtree.h` - Class declaration
- `segtree.cpp` - Members Functions definition of `SegmentTree` class
- `main.cpp` - Basic testing during development
- `Makefile` - Simple Makefile to use with `make`
- `performance_testing.cpp` - Contains performance testing for all three types
