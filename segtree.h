/**
 * This class provides an interface to a segment (or an interval) tree
 * that operates on generic data using a generic function.
 *
 */

#ifndef _SEGMENTTREE_H_
#define _SEGMENTTREE_H_

#include <vector>
#include <functional>

template <typename Base>
class SegmentTree
{

public:

    /**
     * Creates a SegmentTree from given vector
     *
     * init_values  : Initial vector of leaf values
     * bin_func     : Lambda that represents a binary closed operation 
     *                of init_values type
     * type         : False, if iterative segment tree
     *                True, if recursive segment tree
     *
     */
    SegmentTree(std::vector<Base> const             &init_values, 
                std::function<Base(Base&, Base&)>   bin_func, 
                bool                                type);

    /**
     * Creates a SegmentTree from given leaf value and size
     * 
     * init_value   : Initial value of all leaf nodes 
     * len          : Number of leaves in the segment tree
     * bin_func     : Lambda that represents a binary closed operation 
     *                of init_values type
     * type         : False, if iterative segment tree
     *                True, if recursive segment tree
     *
     */
    SegmentTree(Base const                          &init_value, 
                std::size_t const                   &len, 
                std::function<Base(Base&, Base&)>   bin_func, 
                bool                                type);

    /**
     * Queries on SegmentTree on range [l_index, r_index]
     *
     * l_index, r_index: Inclusive left and right ranges, zero-indexed.
     * 
     * Returns solution to query of Base template type.
     *
     */
    Base Query(std::size_t  l_index, 
               std::size_t  r_index); 

    /**
     * Performs update on a SegmentTree leaf
     *
     * new_value    : New value of leaf
     * index        : Index of the leaf (zero indexed)
     *
     */
    void Update(Base const          &new_value, 
                std::size_t const   &index);

    /**
     * Static method that returns the total size necessary
     * to store a SegmentTree
     *
     * len  : Number of leaf nodes
     *
     */
    static size_t GetTreeSize(size_t const &len);

    /**
     * Updates the current lambda that operates of the SegmentTree
     *
     * bin_func : To lambda to update the SegmentTree.
     *
     * TODO: Improve or change utility of this function.
     *
     */ 
    void UpdateFunction(std::function<Base(Base&, Base&)> bin_func);

    /**
     * For developing purposes, print segment tree values.
     */
    void DebugPrint();


private:

    /**
     * Build the segment tree with given vector for all leaf values
     * in recursive fashion.
     *
     * l_index, r_index : [l_index, r_index] 0-indexed denotes current
     *                    sub-tree range
     * init_values      : vector required for the leaf node values
     * tree_index       : index of the current node of tree_ vector
     *
     */
    void BuildTreeRecursive(std::size_t             l_index, 
                            std::size_t             r_index, 
                            std::vector<Base> const &init_values, 
                            std::size_t             tree_index);

    /**
     * Build the segment tree with given vector for all leaf values
     * in recursive fashion.
     *
     * l_index, r_index : [l_index, r_index] 0-indexed denotes current
     *                    sub-tree range
     * init_values      : vector required for the leaf node values
     * tree_index       : index of the current node of tree_ vector
     *
     * TODO : possible integration of this with above method using
     * vector of single size
     *
     */
    void BuildTreeRecursive(std::size_t l_index, 
                            std::size_t r_index, 
                            Base const  &init_value, 
                            std::size_t tree_index);

    /**
     * Builds segment tree with given vector in iterative fashion.
     *
     * init_values  : vector for leaf nodes of the tree.
     *
     */
    void BuildTreeIterative(std::vector<Base> const &init_values);

    /**
     * Builds segment tree with given vector in iterative fashion.
     *
     * init_values  : vector for leaf nodes of the tree.
     *
     */
    void BuildTreeIterative(Base const &init_value);

    /**
     * Queries for the bin_func_ value of all the nodes in the range
     * [l_qbound, r_qbound] in recursive fashion.
     *
     * l_qbound, r_qbound   : [l_qbound, r_qbound] 0-index denotes
     *                        range of subtree required for processing query
     * l_index, r_index     : [l_index, r_index] 0-indexed denotes current
     *                        sub-tree range
     * tree_index           : index of the current node of tree_ vector
     *
     */
    Base QueryRecursive(std::size_t l_qbound, 
                        std::size_t r_qbound, 
                        std::size_t l_index, 
                        std::size_t r_index, 
                        std::size_t tree_index);

    /**
     * Queries for the bin_func_ value of all the nodes in the range
     * [l_qbound, r_qbound] in iterative fashion.
     *
     * l_qbound, r_qbound   : [l_qbound, r_qbound] 0-index denotes
     *                        range of leaves required for processing query
     *
     */
    Base QueryIterative(std::size_t &l_qbound, 
                        std::size_t &r_qbound);

    /**
     * Recursively updates leaf node with given value and applies
     * change along the tree.
     *
     * new_value            : new_value of the leaf node
     * final_index          : index of the leaf (0-indexed) to update
     * l_index, r_index     : [l_index, r_index] 0-indexed denotes current
     *                        sub-tree range
     * tree_index           : index of the current node of tree_ vector
     *
     */
    void UpdateRecursive(Base const         &new_value,
                         std::size_t const  &final_index, 
                         std::size_t        l_index, 
                         std::size_t        r_index, 
                         std::size_t        tree_index);

    /**
     * Iteratively updates leaf node with given value and applies
     * change along the tree.
     *
     * new_value        : new_value of the leaf node
     * index            : index of the leaf (0-indexed) to update
     *
     */
    void UpdateIterative(Base const         &new_value, 
                         std::size_t const  &index);

    // Private Data Members
    std::vector<Base>                   tree_;      ///< vector that stores tree values
    std::function<Base(Base&, Base&)>   bin_func_;  ///< function that operates on tree
    std::size_t                         len_;       ///< number of leaves in tree
    bool                                type_;      ///< True for recursive, else iterative
};

#include "segtree.cpp"  //To include template members

#endif
