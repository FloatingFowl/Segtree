# Segment Tree Repo

##### Usage:

Add `SegmentTree` class to your code by including the file `segtree.h`.

For running the basic file `main.cpp`, run `make` in the directory and then run the generated executable as `./segTree` from within the directory.

Similarly, compile `performance_testing.cpp` and run it for some performance testing. Usage is as `./performanceTesting <option> <number of elements>` where `<option>` may be 
- 1) Only queries
- 2) Only updates
- 3) Queries and Updates

The operations on the segment tree will equal the number of elements.

###### To create a `SegmentTree` object:

From a `vector<Data>` variable named `vec_tree` which contains the leaf values, and a function pointer / functor / lambda / `std::function` type variable named `binary_function`:

	SegmentTree<Data> sTree{
        vec_tree,
        binary_function,
        bool_val
    }
    
`bool_val`, if `True`, sets the tree to recursive mode, otherwise to iterative mode. Make sure that `binary_function` is representable of the form `std::function<Data(Data&, Data&)>`.

From a `Data` type variable named `init_value` which is the default value of all leaf nodes, and a function pointer / functor / lambda / `std::function` type variable named `binary_function`, and the number of leaves `n_leaves`:

	SegmentTree<Data> sTree{
        init_value,
        n_leaves,
        binary_function,
        bool_val
    }

###### Querying

To query for the segment value across a range `[l_index, r_index]` of the leaves (zero-indexed):

	sTree.Update(
        l_index,
        r_index
    )
    
###### Updating

To update the leaf value at an index (zero-indexed) `t_index` of the tree with `Data` type variable of name `new_value`:

	sTree.Query(
        new_value,
        t_value
    )

---

##### Possible TODOs:

*Apart from the few mentioned in the code*

- Performance testing (Have to present data)
- Constructors
  - ~~`(vector of initial values of same type, function pointer or lambda)`~~
  - ~~`(initial value, function pointer or lambda)`~~
  - ~~Possible choice of iterative or recursive~~
  - From begin and end iterators
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

