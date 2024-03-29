# Segment Tree

##### Usage:

Add `SegmentTree` class to your code by including the file `segtree.h`.

For running the `main.cpp` example program in `examples/`, run `cmake ..` in the `bin/` directory, followed by `make`. In the same directory, the executable `example1` is created.

For running the tests described in `tests/`, run `cmake ..` and `make` as above in the `bin/` directory. The executable `tests` is then created in the same directory.

Similarly, for performance testing, do the same as above and run `./performancetests <option> <number of elements>` where `<option>` may be 
- 1) Only queries
- 2) Only updates
- 3) Queries and Updates

The operations on the segment tree will equal 10^5.

---

###### To create a `SegmentTree` object:

From a `vector<Data>` variable named `vec_tree` which contains the leaf values, and a function pointer / functor / lambda / `std::function` type variable named `binary_function`:

``` c++
SegmentTree<Data> sTree{
    vec_tree,
    binary_function,
    bool_val
};
```
    
`bool_val`, if `True`, sets the tree to recursive mode, otherwise to iterative mode. Make sure that `binary_function` is representable of the form `std::function<Data(Data&, Data&)>`.

From a `Data` type variable named `init_value` which is the default value of all leaf nodes, and a function pointer / functor / lambda / `std::function` type variable named `binary_function`, and the number of leaves `n_leaves`:

``` c++
SegmentTree<Data> sTree{
    init_value,
    n_leaves,
    binary_function,
    bool_val
};
```

###### Querying

To query for the segment value across a range `[l_index, r_index]` of the leaves (zero-indexed):

``` c++
sTree.Update(
    l_index,
    r_index
)
```
    
###### Updating

To update the leaf value at an index (zero-indexed) `t_index` of the tree with `Data` type variable of name `new_value`:

``` c++
sTree.Query(
    new_value,
    t_value
);
```

*More information on the functions can be found in the header file (`segtree.h`)*
