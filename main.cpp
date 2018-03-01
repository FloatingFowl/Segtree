#include "segtree.h"
#include<vector>

using namespace std;

int main(){
    //For Testing Purposes
    vector<int> temp = {0,1,2,3};
    SegmentTree<int> st{2, 5, [](int& fi, int& se){return fi + se;}, true};
    cout<<st.Query(0,2)<<'\n';
    st.DebugPrint();
    st.Update(5,1);
    st.DebugPrint();
    cout<<st.Query(0,3)<<'\n';
    st.Update(5,0);
    st.DebugPrint();
    cout<<st.Query(0,3)<<'\n';
}
