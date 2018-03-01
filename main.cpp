#include "segtree.h"
#include<vector>

using namespace std;

int main(){
    //For Testing Purposes
    vector<int> temp = {1,2,3,4};
    SegmentTree<int> st{temp, [](int& fi, int& se){return fi + se;}};
    cout<<st.Query(0,2)<<'\n';
    st.Update(5,1);
    st.DebugPrint();
    cout<<st.Query(0,3)<<'\n';
    //cout<<st.Query(0,4)<<'\n';
}
