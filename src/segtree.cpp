#ifndef _SEGMENTTREE_CPP_
#define _SEGMENTTREE_CPP_

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "segtree.h"


template <typename Base>
SegmentTree<Base>::SegmentTree(
            std::vector<Base> const             &init_values, 
            std::function<Base(Base&, Base&)>   bin_func, 
            bool                                type
)
    : bin_func_(bin_func)
    , len_(init_values.size())
    , type_(type)
{

    if (type_ == true)
    {
        // Chosing to store and operate on the segment
        // tree in a recursive fashion
        tree_.resize(GetTreeSize(len_));
        BuildTreeRecursive(0, len_ - 1, init_values, 0);
    }
    else
    {
        // Chosing to store and operate on the segment
        // tree in a iterative fashion
        tree_.resize(len_ * 2);
        BuildTreeIterative(init_values);
    }
}


template <typename Base>
SegmentTree<Base>::SegmentTree(
            Base const                          &init_value, 
            std::size_t const                   &len, 
            std::function<Base(Base&, Base&)>   bin_func, 
            bool                                type
)
    : bin_func_(bin_func)
    , len_(len)
    , type_(type)
{

    if (type_ == true)
    {
        // Chosing to store and operate on the segment
        // tree in a recursive fashion
        tree_.resize(GetTreeSize(len_));
        BuildTreeRecursive(0, len_ - 1, init_value, 0);
    }
    else
    {
        // Chosing to store and operate on the segment
        // tree in a iterative fashion
        tree_.resize(len_ * 2);
        BuildTreeIterative(init_value);
    }
}



template <typename Base>
void SegmentTree<Base>::BuildTreeRecursive(
            std::size_t             l_index, 
            std::size_t             r_index, 
            std::vector<Base> const &init_values, 
            std::size_t             tree_index
)
{

    if (l_index == r_index)
    {
        // Storing value into leaf node of the tree
        // from corresponding vector index
        tree_[tree_index] = init_values[l_index];
        return;
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;
    
    // build tree on left branch
    BuildTreeRecursive(l_index, boundary, init_values, next_tree_index);
    // build tree on right branch
    BuildTreeRecursive(boundary + 1, r_index, init_values, next_tree_index + 1);

    // storing value of the current tree node,
    // by merging left and right children
    tree_[tree_index] = bin_func_(tree_[next_tree_index], tree_[next_tree_index + 1]);
}


template <typename Base>
void SegmentTree<Base>::BuildTreeRecursive(
            std::size_t l_index, 
            std::size_t r_index, 
            Base const  &init_value, 
            std::size_t tree_index
)
{

    if (l_index == r_index)
    {
        // Storing value into leaf node of the tree
        // from default leaf node value 
        tree_[tree_index] = init_value;
        return;
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;
    
    // build tree on left branch
    BuildTreeRecursive(l_index, boundary, init_value, next_tree_index);
    // build tree on right branch
    BuildTreeRecursive(boundary + 1, r_index, init_value, next_tree_index + 1);

    // storing value of the current tree node,
    // by merging left and right children
    tree_[tree_index] = bin_func_(tree_[next_tree_index], tree_[next_tree_index + 1]);
}


template <typename Base>
void SegmentTree<Base>::BuildTreeIterative(
            std::vector<Base> const &init_values
)
{
    for(size_t i = 0; i < len_; i++)
    {
        // storing the leaf values into the tree
        // from initializing vector. Stored into the
        // last nLeaves indices
        tree_[len_ + i] = init_values[i];
    }
    for(size_t i = len_ - 1; i > 0; i--)
    {
        // getting the value of every tree node
        // in a reverse order by merging the two children
        // which have been calculated earlier
        tree_[i] = bin_func_(tree_[i << 1], tree_[(i << 1) | 1]);
    }
}


template <typename Base>
void SegmentTree<Base>::BuildTreeIterative(
            Base const &init_value
)
{
    for(size_t i = 0; i < len_; i++)
    {
        // storing the leaf values into the tree
        // with the given default value. Stored into the
        // last nLeaves indices
        tree_[len_ + i] = init_value;
    }
    for(size_t i = len_ - 1; i > 0; i--)
    {
        // getting the value of every tree node
        // in a reverse order by merging the two children
        // which have been calculated earlier
        tree_[i] = bin_func_(tree_[i << 1], tree_[(i << 1) | 1]);
    }
}


template <typename Base>
Base SegmentTree<Base>::QueryRecursive(
        std::size_t l_qbound, 
        std::size_t r_qbound, 
        std::size_t l_index, 
        std::size_t r_index, 
        std::size_t tree_index
)
{
    if (l_qbound <= l_index && r_index <= r_qbound)
    {
        // The current subtree of the segment tree
        // appears completely inside the range of the query. So the total
        // value stored at the root node of the subtree is returned.
        return tree_[tree_index];
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;

    if (r_qbound <= boundary)
    {
        // The current query range lies completely in the left subtree, so
        // the query is returned from the left subtree.
        return QueryRecursive(l_qbound, r_qbound, l_index, boundary, next_tree_index);
    }
    else if (l_qbound > boundary)
    {
        // The current query range lies completely in the right subtree, so
        // the query is returned from the right subtree.
        return QueryRecursive(l_qbound, r_qbound, boundary + 1, r_index, next_tree_index + 1);
    }
    else
    {
        // The query range intersects both children of the current root node,
        // so the query is sent across to both sub-trees and the result is combined.
        Base l_query = QueryRecursive(l_qbound, boundary, l_index, boundary, next_tree_index);
        Base r_query = QueryRecursive(boundary + 1, r_qbound, boundary + 1, r_index, next_tree_index + 1);
        return bin_func_(l_query, r_query);
    }
}


template <typename Base>
Base SegmentTree<Base>::QueryIterative(
            std::size_t &l_qbound, 
            std::size_t &r_qbound
)
{
    // setting OPEN right bound
    r_qbound += 1;

    // User Base type has to be initialized with default value
    // in the default constructor for usage in iterative code.
    Base l_query{};
    Base r_query{};

    std::size_t l_ind = l_qbound + len_, r_ind = r_qbound + len_;

    while (l_ind < r_ind)
    {
        if (l_ind & 1)
        {
            // l_ind is an odd index so its subtree is included
            // in the range.
            l_query = bin_func_(l_query, tree_[l_ind]);
            l_ind += 1;
        }
        if (r_ind & 1)
        {
            // r_ind (open end) is odd, so its subtree is not
            // included, however, r_ind - 1 subtree is.
            r_ind -= 1;
            r_query = bin_func_(tree_[r_ind], r_query);
        }
        
        // Moving l_ind, r_ind to their respective
        // parents.
        l_ind >>= 1;
        r_ind >>= 1;
    }

    // returning the query solution
    return bin_func_(l_query, r_query);
}


template <typename Base>
void SegmentTree<Base>::UpdateRecursive(
            Base const          &new_value, 
            std::size_t const   &final_index, 
            std::size_t         l_index, 
            std::size_t         r_index, 
            std::size_t         tree_index
)
{
    if (l_index == r_index)
    {
        // Leaf to be updated reached and updated
        // with the new value
        tree_[tree_index] = new_value;
        return;
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;

    if (final_index <= boundary)
    {
        // Recursively updating on the left subtree if
        // leaf exists in that subtree.
        UpdateRecursive(new_value, final_index, l_index, boundary, next_tree_index);
    }
    else
    {
        // Recursively updating on the right subtree if
        // leaf exists in that subtree.
        UpdateRecursive(new_value, final_index, boundary + 1, r_index, next_tree_index + 1);
    }

    // Updating ancestors of the leaf value updated
    // with latest values
    tree_[tree_index] = bin_func_(tree_[next_tree_index], tree_[next_tree_index + 1]);
}


template <typename Base>
void SegmentTree<Base>::UpdateIterative(
            Base const &new_value, 
            std::size_t const &index
)
{

    std::size_t i = index + len_;

    // Updating leaf node of tree with new value
    tree_[i] = new_value;

    i >>= 1;

    while (i != 0)
    {
        // Updating the values of each ancestor of
        // updated leaf node.
        
        // if i is even, i^1 is odd and similar if i is odd
        // updating parent of current node (i) by merging
        // siblings stored at i<<1 and (i<<1)^1 indices in tree_ vector.
        tree_[i] = bin_func_(tree_[i<<1], tree_[(i<<1) ^ 1]);

        // setting i to parent of current node by diving index by 2
        i >>= 1;
    }
}


template <typename Base>
Base SegmentTree<Base>::Query(
            std::size_t l_qbound, 
            std::size_t r_qbound
)
{
    if (l_qbound < 0 || l_qbound >= len_ || r_qbound < 0 || r_qbound >= len_)
    {
        // query bounds moving out of segment tree range
        throw std::out_of_range("The indices must be within the range of the segment tree.");
    }
    if (l_qbound > r_qbound)
    {
        // query left bound greater than query right bound
        throw std::out_of_range("The left index must be smaller than the right index.");
    }

    if (type_ == true)
        // Querying recursively
        return QueryRecursive(l_qbound, r_qbound, 0, len_ - 1, 0);
    else
        // Querying iteratively
        return QueryIterative(l_qbound, r_qbound);
}

template <typename Base>
void SegmentTree<Base>::Update(
            Base const &new_value, 
            std::size_t const &index
)
{
    if (index < 0 || index > len_)
    {
        // update node out of segment tree range
        throw std::out_of_range("The index must be within the range of the segment tree.");
    }

    if (type_ == true)
        // Recursive updating
        UpdateRecursive(new_value, index, 0, len_ - 1, 0);
    else
        // Iterative updating
        UpdateIterative(new_value, index);
}


template <typename Base>
size_t SegmentTree<Base>::GetTreeSize(
            size_t const &len
)
{
    if (len == 0)
    {
        // No leaves imply no nodes in the segment tree
        return 0;
    }

    // Returns >= minimum number of nodes required
    // for storing segment tree with `len` leaves
    return 2 * std::pow(2, std::ceil(std::log2(len))) - 1;
}


template <typename Base>
void SegmentTree<Base>::UpdateFunction(
            std::function<Base(Base&, Base&)> bin_func
)
{
    // Updating current segment tree operation /
    // merge function with new one
    bin_func_ = bin_func;
}


template <typename Base>
void SegmentTree<Base>::DebugPrint()
{
    int limit = GetTreeSize(len_);
    //int limit = 2*len_;
    for (int i = 0; i < limit; i++){
    //for (int i = 1; i <= limit; i++){
        std::cout<<tree_[i]<<"\t";
    }
    std::cout<<'\n';
}

#endif
