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
int test_Lambda_ULLMultiplication(){
    std::vector<unsigned long long int> value_vec;
    unsigned long long int prime = 1000000009;

    SegmentTree<unsigned long long int> s_tree2{
        1LL,
        6,
        [&prime]
            (unsigned long long int& a, unsigned long long int& b)
            { return (a * b) % prime; },
        true
    };

    for(int i = 0; i < 6; i++){
        value_vec.push_back(rand() % prime);
        s_tree2.Update(value_vec[i], i);
    }

    SegmentTree<unsigned long long int> s_tree{
        value_vec, 
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
        auto s_tree2_ans = s_tree2.Query(l_ind, r_ind);

        unsigned long long int brute_force_ans = value_vec[l_ind];
        for(int j = l_ind + 1; j <= r_ind; j++){
            brute_force_ans = (brute_force_ans * value_vec[j]) % prime;
        }

        if(brute_force_ans != s_tree_ans){
            std::cerr << "test_RecursiveLambda_ULLMultiplication:\n\tQueries before update do not match "
                "for vector initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree2_ans){
            std::cerr << "test_RecursiveLambda_ULLMultiplication:\n\tQueries before update do not match "
                "for value initialized segment tree.\n";
            return 0;
        }
    }

    for(int i = 0; i < 10; i++){
        int ind = rand() % 6;
        unsigned long long int val = rand() % prime;
        value_vec[ind] = val;
        s_tree.Update(val, ind);
        s_tree2.Update(val, ind);
    }

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 6;
        int l_ind = rand() % (6 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree_ans = s_tree.Query(l_ind, r_ind);
        auto s_tree2_ans = s_tree2.Query(l_ind, r_ind);

        unsigned long long int brute_force_ans = value_vec[l_ind];
        for(int j = l_ind + 1; j <= r_ind; j++){
            brute_force_ans = (brute_force_ans * value_vec[j]) % prime;
        }

        if(brute_force_ans != s_tree_ans){
            std::cerr << "test_RecursiveLambda_ULLMultiplication:\n\tQueries after update do not match "
                "for vector initialized segment tree.\n";
            return 0;
        }
        if(brute_force_ans != s_tree2_ans){
            std::cerr << "test_RecursiveLambda_ULLMultiplication:\n\tQueries after update do not match "
                "for value initialized segment tree.\n";
            return 0;
        }
    }

    return 1;
}

/*
 *  ---------------------------
 *  TEST3 : std::string concatenation 
 *  --------------------------
 */
struct addString {
    std::string operator()(std::string &a, std::string &b){
        return a + b;
    }
};

int test_Functor_StringConcatenation()
{
    std::vector<std::string> value_vec = {"aa", "", "lasWAS", "hehe", "BOOOSSSSt", "\n"};

    SegmentTree<std::string> s_tree1 = {value_vec, addString{}, true};
    SegmentTree<std::string> s_tree2 = {value_vec, addString{}, false};
    SegmentTree<std::string> s_tree3 = {"", 6, addString{}, true};
    SegmentTree<std::string> s_tree4 = {"", 6, addString{}, false};

    for(int i = 0; i < 6; i++){
        s_tree3.Update(value_vec[i], i);
        s_tree4.Update(value_vec[i], i);
    }

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 6;
        int l_ind = rand() % (6 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree1_ans = s_tree1.Query(l_ind, r_ind);
        auto s_tree2_ans = s_tree2.Query(l_ind, r_ind);
        auto s_tree3_ans = s_tree3.Query(l_ind, r_ind);
        auto s_tree4_ans = s_tree4.Query(l_ind, r_ind);

        std::string brute_force_ans = "";
        for(int j = l_ind; j <= r_ind; j++){
            brute_force_ans += value_vec[j];
        }

        if(brute_force_ans != s_tree1_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for recursive vector initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree2_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for iterative vector initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree3_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for recursive value initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree4_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for iterative value initialized segment tree.\n";
            return 0;
        }

    }

    int ind = rand() % 6;
    s_tree1.Update("PaaMAwI", ind);
    s_tree2.Update("PaaMAwI", ind);
    s_tree3.Update("PaaMAwI", ind);
    s_tree4.Update("PaaMAwI", ind);
    value_vec[ind] = "PaaMAwI";

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 6;
        int l_ind = rand() % (6 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree1_ans = s_tree1.Query(l_ind, r_ind);
        auto s_tree2_ans = s_tree2.Query(l_ind, r_ind);
        auto s_tree3_ans = s_tree3.Query(l_ind, r_ind);
        auto s_tree4_ans = s_tree4.Query(l_ind, r_ind);

        std::string brute_force_ans = "";
        for(int j = l_ind; j <= r_ind; j++){
            brute_force_ans += value_vec[j];
        }

        if(brute_force_ans != s_tree1_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for recursive vector initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree2_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for iterative vector initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree3_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for recursive value initialized segment tree.\n";
            return 0;
        }

        if(brute_force_ans != s_tree4_ans){
            std::cerr << "test_Functor_StringConcatenation:\n\tQueries before update do not match "
                "for iterative value initialized segment tree.\n";
            return 0;
        }

    }

    return 1;
}

/*
 *  ---------------------------
 *  TEST4 : Maximum sum (empty/non-empty) subarray in range
 *  --------------------------
 */

struct NodeEle{
    int bst, pre, pos, tot;
    NodeEle():bst(0),pos(0),pre(0),tot(0){}
    NodeEle(int val):bst(val),pos(val),pre(val),tot(val){
        if (val < 0)
            bst = pre = pos = 0;
    }
};

NodeEle combine(NodeEle &a, NodeEle &b){
    NodeEle ret;
    ret.tot = a.tot + b.tot;
    ret.pre = std::max(a.pre, a.tot + b.pre);
    ret.pos = std::max(a.pos + b.tot, b.pos);
    ret.bst = std::max(std::max(a.bst, b.bst), a.pos + b.pre);

    return ret;
}

int test_FunctionPointer_MaximumSubarray(){
    SegmentTree<NodeEle> s_tree3 = {NodeEle(), 10, combine, true};
    SegmentTree<NodeEle> s_tree4 = {NodeEle(), 10, combine, false};

    std::vector<NodeEle> value_vec;
    for(int i = 0; i < 10; i++){
        value_vec.push_back(NodeEle(-500 + rand()%1000));
        s_tree3.Update(value_vec[i], i);
        s_tree4.Update(value_vec[i], i);
    }

    SegmentTree<NodeEle> s_tree1 = {value_vec, combine, true};
    SegmentTree<NodeEle> s_tree2 = {value_vec, combine, false};

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 10;
        int l_ind = rand() % (10 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree1_ans = s_tree1.Query(l_ind, r_ind);
        auto s_tree2_ans = s_tree2.Query(l_ind, r_ind);
        auto s_tree3_ans = s_tree3.Query(l_ind, r_ind);
        auto s_tree4_ans = s_tree4.Query(l_ind, r_ind);

        int ans = 0, cur = 0;
        for(int i = l_ind; i <= r_ind; i++){
            cur += value_vec[i].tot;
            ans = std::max(ans, cur);
            if (cur < 0) cur = 0;
        }

        if(ans != s_tree1_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries before update do not match "
                "for recursive vector initialized segment tree.\n";
            return 0;
        }
        if(ans != s_tree2_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries before update do not match "
                "for iterative vector initialized segment tree.\n";
            return 0;
        }
        if(ans != s_tree3_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries before update do not match "
                "for recursive value initialized segment tree.\n";
            return 0;
        }
        if(ans != s_tree4_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries before update do not match "
                "for iterative value initialized segment tree.\n";
            return 0;
        }
    }

    for(int i = 0; i < 5; i++){
        int ind = rand() % 10;
        value_vec[ind] = NodeEle(-500 + rand()%1000);
        s_tree1.Update(value_vec[ind], ind);
        s_tree2.Update(value_vec[ind], ind);
        s_tree3.Update(value_vec[ind], ind);
        s_tree4.Update(value_vec[ind], ind);
    }

    for(int i = 0; i < 10; i++){
        int r_ind = rand() % 10;
        int l_ind = rand() % (10 - r_ind);
        if(l_ind > r_ind) std::swap(l_ind, r_ind);

        auto s_tree1_ans = s_tree1.Query(l_ind, r_ind);
        auto s_tree2_ans = s_tree2.Query(l_ind, r_ind);
        auto s_tree3_ans = s_tree3.Query(l_ind, r_ind);
        auto s_tree4_ans = s_tree4.Query(l_ind, r_ind);

        int ans = 0, cur = 0;
        for(int i = l_ind; i <= r_ind; i++){
            cur += value_vec[i].tot;
            ans = std::max(ans, cur);
            if (cur < 0) cur = 0;
        }

        if(ans != s_tree1_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries after update do not match "
                "for recursive vector initialized segment tree.\n";
            return 0;
        }
        if(ans != s_tree2_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries after update do not match "
                "for iterative vector initialized segment tree.\n";
            return 0;
        }
        if(ans != s_tree3_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries after update do not match "
                "for recursive value initialized segment tree.\n";
            return 0;
        }
        if(ans != s_tree4_ans.bst){
            std::cerr << "test_FunctionPointer_MaximumSubarray:\n\tQueries after update do not match "
                "for iterative value initialized segment tree.\n";
            return 0;
        }
    }

    return 1;
}


/*
 *  ---------------------------
 *  Main Function, calls every test 
 *  --------------------------
 */

int main(){
    srand(time(NULL));

    int successful_tests = 0;
    int total_tests = 4;

    // GetTreeSize testing
    successful_tests += test_GetTreeSize();

    // Recursive ULL multiplication mod prime using lambdas (only recursive)
    // TODO: Incorporate for iterative cases after adding iterative constructor
    successful_tests += test_Lambda_ULLMultiplication();

    // std::string concatenation using functor (recursive and iterative)
    successful_tests += test_Functor_StringConcatenation();
    
    // maximum contiguous sum using function pointer (recursive and iterative)
    successful_tests += test_FunctionPointer_MaximumSubarray();

    if(total_tests == successful_tests){
        std::cout << "\033[1;32mALL ("<< total_tests <<") TESTS PASSED\033[0m\n";
    }
    else{
        std::cout << "\033[1;31m"<< total_tests - successful_tests <<"OF " << total_tests << " TESTS FAILED\033[0m\n";
    }
}
