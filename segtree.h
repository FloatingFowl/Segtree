#include <vector>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <cmath>

#ifndef _SEGMENTTREE_H_
#define _SEGMENTTREE_H_

template <typename Base>
class SegmentTree {

    private:
        // Private Data Members
        std::vector<Base>                   tree_;
        std::function<Base(Base&, Base&)>   bin_func_;
        std::size_t                         len_; 
        // Private Member Functions 
        void BuildTreeRecursive(std::size_t l_index, std::size_t r_index, std::vector<Base> const &init_values, std::size_t tree_index);
        void BuildTreeIterative(std::vector<Base> const &init_values);
        Base QueryRecursive(std::size_t l_qbound, std::size_t r_qbound, std::size_t l_index, std::size_t r_index, std::size_t tree_index);
        Base QueryIterative(std::size_t &l_qbound, std::size_t &r_qbound);
        void UpdateRecursive(Base const &new_value, std::size_t const &final_index, std::size_t l_index, std::size_t r_index, std::size_t tree_index);
        void UpdateIterative(Base const &new_value, std::size_t const &index);

    public:
        SegmentTree(std::vector<Base> const &init_values, std::function<Base(Base&, Base&)> bin_func);
        Base Query(std::size_t l_index, std::size_t r_index); 
        void Update(Base const &new_value, std::size_t const &index);
        static size_t GetTreeSize(size_t const &len);
        void DebugPrint();

};

#include "segtree.cpp"
#endif
