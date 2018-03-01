#include "segtree.h"

#ifndef _SEGMENTTREE_CPP_
#define _SEGMENTTREE_CPP_

template <typename Base>
SegmentTree<Base>::SegmentTree(std::vector<Base> const &init_values, std::function<Base(Base&, Base&)> bin_func)
    : bin_func_(bin_func)
    , len_(init_values.size())
{
    tree_.resize(GetTreeSize(len_));
    //BuildTreeRecursive(0, len_ - 1, init_values, 0);
    BuildTreeIterative(init_values);
    DebugPrint();
}


template <typename Base>
void SegmentTree<Base>::BuildTreeRecursive(std::size_t l_index, std::size_t r_index, std::vector<Base> const &init_values, std::size_t tree_index)
{
    if (l_index == r_index)
    {
        tree_[tree_index] = init_values[l_index];
        return;
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;
    
    BuildTreeRecursive(l_index, boundary, init_values, next_tree_index);
    BuildTreeRecursive(boundary + 1, r_index, init_values, next_tree_index + 1);
    tree_[tree_index] = bin_func_(tree_[next_tree_index], tree_[next_tree_index + 1]);
}


template <typename Base>
void SegmentTree<Base>::BuildTreeIterative(std::vector<Base> const &init_values)
{
    for(size_t i = 0; i < len_; i++)
    {
        tree_[len_ + i] = init_values[i];
    }
    for(size_t i = len_ - 1; i > 0; i--)
    {
        tree_[i] = bin_func_(tree_[i << 1], tree_[(i << 1) | 1]);
    }
}


template <typename Base>
Base SegmentTree<Base>::QueryRecursive(std::size_t l_qbound, std::size_t r_qbound, std::size_t l_index, std::size_t r_index, std::size_t tree_index)
{
    if (l_qbound <= l_index && r_index <= r_qbound)
    {
        return tree_[tree_index];
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;

    if (r_qbound <= boundary)
    {
        return QueryRecursive(l_qbound, r_qbound, l_index, boundary, next_tree_index);
    }
    else if (l_qbound > boundary)
    {
        return QueryRecursive(l_qbound, r_qbound, boundary + 1, r_index, next_tree_index + 1);
    }
    else
    {
        Base l_query = QueryRecursive(l_qbound, boundary, l_index, boundary, next_tree_index);
        Base r_query = QueryRecursive(boundary + 1, r_qbound, boundary + 1, r_index, next_tree_index + 1);
        return bin_func_(l_query, r_query);
    }
}


template <typename Base>
Base SegmentTree<Base>::QueryIterative(std::size_t &l_qbound, std::size_t &r_qbound)
{
    r_qbound += 1;
    Base l_query{};
    Base r_query{};

    std::size_t l_ind = l_qbound + len_, r_ind = r_qbound + len_;

    while (l_ind < r_ind)
    {
        if (l_ind & 1)
        {
            l_query = bin_func_(l_query, tree_[l_ind]);
            l_ind += 1;
        }
        if (r_ind & 1)
        {
            r_ind -= 1;
            r_query = bin_func_(tree_[r_ind], r_query);
        }
        
        l_ind >>= 1;
        r_ind >>= 1;
    }

    return bin_func_(l_query, r_query);
}


template <typename Base>
void SegmentTree<Base>::UpdateRecursive(Base const &new_value, std::size_t const &final_index, std::size_t l_index, std::size_t r_index, std::size_t tree_index)
{
    if (l_index == r_index)
    {
        tree_[tree_index] = new_value;
        return;
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;

    if (final_index <= boundary)
    {
        UpdateRecursive(new_value, final_index, l_index, boundary, next_tree_index);
    }
    else
    {
        UpdateRecursive(new_value, final_index, boundary + 1, r_index, next_tree_index + 1);
    }
    tree_[tree_index] = bin_func_(tree_[next_tree_index], tree_[next_tree_index + 1]);
}


template <typename Base>
void SegmentTree<Base>::UpdateIterative(Base const &new_value, std::size_t const &index)
{
    std::size_t i = index + len_;
    tree_[i] = new_value;
    i >>= 1;

    while (i > 0)
    {
        tree_[i] = bin_func_(tree_[i << 1], tree_[(i << 1) | 1]);
        i >>= 1;
    }
}


template <typename Base>
Base SegmentTree<Base>::Query(std::size_t l_qbound, std::size_t r_qbound)
{
    if (l_qbound < 0 || l_qbound >= len_ || r_qbound < 0 || r_qbound >= len_)
    {
        throw std::out_of_range("The indices must be within the range of the segment tree.");
    }
    if (l_qbound > r_qbound)
    {
        throw std::out_of_range("The left index must be smaller than the right index.");
    }
    //return QueryRecursive(l_qbound, r_qbound, 0, len_ - 1, 0);
    return QueryIterative(l_qbound, r_qbound);
}

template <typename Base>
void SegmentTree<Base>::Update(Base const &new_value, std::size_t const &index)
{
    if (index < 0 || index > len_)
    {
        throw std::out_of_range("The index must be within the range of the segment tree.");
    }
    //UpdateRecursive(new_value, index, 0, len_ - 1, 0);
    UpdateIterative(new_value, index);
}


template <typename Base>
size_t SegmentTree<Base>::GetTreeSize(size_t const &len)
{
    return 2 * std::pow(2, std::ceil(std::log2(len))) - 1;
}


template <typename Base>
void SegmentTree<Base>::DebugPrint()
{
    //int limit = GetTreeSize(len_);
    int limit = 2*len_;
    //for (int i = 0; i < limit; i++){
    for (int i = 1; i <= limit; i++){
        std::cout<<tree_[i]<<"\t";
    }
    std::cout<<'\n';
}

#endif
