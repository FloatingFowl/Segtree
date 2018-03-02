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
    // Private Data Members
    std::vector<Base>                   tree_;
    std::function<Base(Base&, Base&)>   bin_func_;
    std::size_t                         len_; 
    bool                                type_;

    // Private Member Functions 
    void    BuildTreeRecursive(std::size_t l_index, std::size_t r_index, std::vector<Base> const &init_values, std::size_t tree_index);
    void    BuildTreeRecursive(std::size_t l_index, std::size_t r_index, Base const &init_value, std::size_t tree_index);
    void    BuildTreeIterative(std::vector<Base> const &init_values);
    void    BuildTreeIterative(Base const &init_value);
    Base    QueryRecursive(std::size_t l_qbound, std::size_t r_qbound, std::size_t l_index, std::size_t r_index, std::size_t tree_index);
    Base    QueryIterative(std::size_t &l_qbound, std::size_t &r_qbound);
    void    UpdateRecursive(Base const &new_value, std::size_t const &final_index, std::size_t l_index, std::size_t r_index, std::size_t tree_index);
    void    UpdateIterative(Base const &new_value, std::size_t const &index);

};

#include "segtree.cpp"  //To include template members

#endif
