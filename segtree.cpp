#include "segtree.h"

#ifndef _SEGMENTTREE_CPP_
#define _SEGMENTTREE_CPP_

template <typename base>
SegmentTree<base>::SegmentTree(std::vector<base> const &init_values, std::function<base(base&, base&)> bin_func)
    : bin_func_(bin_func)
    , len_(init_values.size())
{
    tree_.resize(GetTreeSize(len_));
    BuildTree(0, len_ - 1, init_values, 0);
    DebugPrint();
}

template <typename base>
void SegmentTree<base>::BuildTree(std::size_t l_index, std::size_t r_index, std::vector<base> const &init_values, std::size_t tree_index)
{
    if (l_index == r_index)
    {
        tree_[tree_index] = init_values[l_index];
        return;
    }

    std::size_t boundary = (l_index + r_index) >> 1;
    std::size_t next_tree_index = (tree_index << 1) + 1;
    
    BuildTree(l_index, boundary, init_values, next_tree_index);
    BuildTree(boundary + 1, r_index, init_values, next_tree_index + 1);
    tree_[tree_index] = bin_func_(tree_[next_tree_index], tree_[next_tree_index + 1]);
}


template <typename base>
size_t SegmentTree<base>::GetTreeSize(size_t const &len)
{
    return 2 * std::pow(2, std::ceil(std::log2(len))) - 1;
}


template <typename base>
void SegmentTree<base>::DebugPrint()
{
    int limit = GetTreeSize(len_);
    for (int i = 0; i < limit; i++){
        std::cout<<tree_[i]<<"\t";
    }
}

#endif
