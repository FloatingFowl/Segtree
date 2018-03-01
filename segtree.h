#include<vector>
#include<iostream>
#include<functional>
#include<cmath>

#ifndef _SEGMENTTREE_H_
#define _SEGMENTTREE_H_

template <typename base>
class SegmentTree {

    private:
        // Private Data Members
        std::vector<base>                   tree_;
        std::function<base(base&, base&)>   bin_func_;
        std::size_t                         len_; 
        // Private Member Functions 
        void BuildTree(std::size_t l_index, std::size_t r_index, std::vector<base> const &init_values, std::size_t tree_index);

    public:
        SegmentTree(std::vector<base> const &init_values, std::function<base(base&, base&)> bin_func);
        static size_t GetTreeSize(size_t const &len);
        void DebugPrint();

};

#include "segtree.cpp"
#endif
