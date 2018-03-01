#include "segtree.h"
#include<vector>

using namespace std;

int main(){
    //For Testing Purposes
    vector<int> temp = {1,2,3,4};
    SegmentTree<int> st{temp, [](int& fi, int& se){return fi + se;}};
    cout<<SegmentTree<int>::GetTreeSize(5)<<'\n';
}
