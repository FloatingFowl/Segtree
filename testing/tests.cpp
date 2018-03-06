#include <iostream>
#include <cstdlib>
#include "segtree.h"


/*
 *  ---------------------------
 *  TEST1 : Static Method GetTreeSize()
 *  --------------------------
 */

int test_GetTreeSize()
{
    // Tree with no leaves does not require any nodes at a minimum.
    int ans = SegmentTree<bool>::GetTreeSize(0);
    if (ans < 0) {
        std::cerr << "test_GetTreeSize:\n\t`GetTreeSize(0)` did not return an integer greater than or equal to zero.\n";
        return 0;
    }
    ans = SegmentTree<bool>::GetTreeSize(2);
    if (ans < 3) {
        std::cerr << "test_GetTreeSize:\n\t`GetTreeSize(7)` did not return an integer greater than 2.\n";
        return 0;
    }
    ans = SegmentTree<bool>::GetTreeSize(7);
    if (ans < 15) {
        std::cerr << "test_GetTreeSize:\n\t`GetTreeSize(7)` did not return an integer greater than 14.\n";
        return 0;
    }
    ans = SegmentTree<bool>::GetTreeSize(8);
    if (ans < 15) {
        std::cerr << "test_GetTreeSize:\n\t`GetTreeSize(7)` did not return an integer greater than 14.\n";
        return 0;
    }
    ans = SegmentTree<bool>::GetTreeSize(104729);
    if (ans < 262143) {
        std::cerr << "test_GetTreeSize:\n\t`GetTreeSize(7)` did not return an integer greater than 262142.\n";
        return 0;
    }
    return 1;
}


/*
 *  ---------------------------
 *  TEST2 : unsigned long long int multiplication 
 *  --------------------------
 */
int test_RecursiveLambda_ULLMultiplication(){
    std::vector<unsigned long long int> value_vec;
    unsigned long long int prime = 1000000009;

    for(int i = 0; i < 6; i++){
        value_vec.push_back(rand() % prime);
    }

    SegmentTree<unsigned long long int> s_tree{value_vec, 
        [&prime]
            (unsigned long long int& a, unsigned long long int& b)
            { return (a * b) % prime; },
        true
    };

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 6;
        int l_ind = rand() % (6 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree_ans = s_tree.Query(l_ind, r_ind);

        unsigned long long int brute_force_ans = value_vec[l_ind];
        for(int j = l_ind + 1; j <= r_ind; j++){
            brute_force_ans = (brute_force_ans * value_vec[j]) % prime;
        }

        if(brute_force_ans != s_tree_ans){
            std::cerr << "test_RecursiveLambda_ULLMultiplication:\n\tQueries before update do not match.\n";
            return 0;
        }
    }

    for(int i = 0; i < 10; i++){
        int ind = rand() % 6;
        unsigned long long int val = rand() % prime;
        value_vec[ind] = val;
        s_tree.Update(val, ind);
    }

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 6;
        int l_ind = rand() % (6 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree_ans = s_tree.Query(l_ind, r_ind);

        unsigned long long int brute_force_ans = value_vec[l_ind];
        for(int j = l_ind + 1; j <= r_ind; j++){
            brute_force_ans = (brute_force_ans * value_vec[j]) % prime;
        }

        if(brute_force_ans != s_tree_ans){
            std::cerr << "test_RecursiveLambda_ULLMultiplication:\n\tQueries after update do not match.\n";
            return 0;
        }
    }

    return 1;
}

int main(){
    srand(time(NULL));

    int successful_tests = 0;
    int total_tests = 2;

    // GetTreeSize testing
    successful_tests += test_GetTreeSize();

    // Recursive ULL multiplication mod prime using lambdas
    successful_tests += test_RecursiveLambda_ULLMultiplication();

    if(total_tests == successful_tests){
        std::cout << "\033[1;32mALL ("<< total_tests <<") TESTS PASSED\033[0m\n";
    }
    else{
        std::cout << "\033[1;31m"<< total_tests - successful_tests <<" TESTS FAILED. MORE DETAILS IN LOG.TXT\033[0m\n";
    }
}
