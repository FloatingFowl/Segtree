#include <iostream>
#include <cstring>
#include <vector>
#include <sys/time.h>
#include "segtree.h"

using namespace std;
typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp ()
{
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

template <typename T>
class BruteForce {
    vector<T> arr_;
    std::function<T(T&,T&)> fun_;
    size_t len_;
    public:
        BruteForce(vector<T> &init_vec, std::function<T(T&,T&)> fun)
            : fun_(fun)
            , len_(init_vec.size())
        {
            arr_ = init_vec;
        }
        BruteForce(T &init_val, size_t sz, std::function<T(T&,T&)> fun)
            : fun_(fun)
            , len_(sz)
        {
            for (int i = 0; i < len_; i++)
                arr_.push_back(init_val);
        }
        void Update(size_t pos, T val){
            arr_[pos] = val;
        }
        T Query(size_t l_ind, size_t r_ind){
            if (l_ind == r_ind)
                return arr_[l_ind];
            T ret = fun_(arr_[l_ind], arr_[l_ind + 1]);
            int i = l_ind + 2;
            while(i <= r_ind)
                ret = fun_(ret, arr_[i++]);
            return ret;
        }
};

vector<tuple <int, int, int>> queries;
vector<int> init_val;

int main(int argc, char *argv[])
{
    std::cout<<fixed;
    std::cout.precision(10);
    if (argc != 3)
    {
        cout<<"Usage: performance_testing <Process Option> <Number of Elements>\n";
        cout<<"Process Option: (1) Only query (2) Only update (3) Random queries and updates\n";
        return 0;
    }

    srand(time(NULL));

    int limit = atoi(argv[2]);

    if (strcmp(argv[1], "1") == 0)
    {
        for (int i = 0; i < 100000; i++)
        {
            int l = rand()%limit;
            int r = l + rand()%(limit - l);
            queries.push_back(make_tuple(0, l, r));
        }
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        for (int i = 0; i < 100000; i++)
        {
            int l = rand()%limit;
            int val = rand()%5000;
            queries.push_back(make_tuple(1, l, val));
        }
    }
    else
    {
        for (int i = 0; i < 100000; i++)
        {
            int x = rand()%2;
            if (x == 0){
                int l = rand()%limit;
                int r = l + rand()%(limit - l);
                queries.push_back(make_tuple(0, l, r));
            }
            else{
                int l = rand()%limit;
                int val = rand()%5000;
                queries.push_back(make_tuple(1, l, val));
            }
        }
    }

    init_val.clear();
    for (int i=0; i < limit; i++)
    {
        int val = rand()%500;
        init_val.push_back(val);
    }

    {
        timestamp_t t0 = get_timestamp();
        //Segment Tree Iterative
        SegmentTree<int> st{init_val, [](int& f, int& s){return f+s;}, false};  
        for (int i = 0; i < 100000; i++)
        {
            if(get<0>(queries[i]) == 0){
                auto ans = st.Query(get<1>(queries[i]), get<2>(queries[i]));
                //cout<<ans<<'\n';
            }
            else
                st.Update(get<2>(queries[i]), get<1>(queries[i]));
        }
        timestamp_t t1 = get_timestamp();
        cout<<(t1 - t0)/1000000.0L<<'\n';
    }

    {
        timestamp_t t0 = get_timestamp();
        //Segment Tree Recursive
        SegmentTree<int> st{init_val, [](int& f, int& s){return f+s;}, true};  
        for (int i = 0; i < 100000; i++)
        {
            if(get<0>(queries[i]) == 0){
                auto ans = st.Query(get<1>(queries[i]), get<2>(queries[i]));
                //cout<<ans<<'\n';
            }
            else
                st.Update(get<2>(queries[i]), get<1>(queries[i]));
        }
        timestamp_t t1 = get_timestamp();
        cout<<(t1 - t0)/1000000.0L<<'\n';
    }

    {
        timestamp_t t0 = get_timestamp();
        //Segment Tree Recursive
        BruteForce<int> st{init_val, [](int& f, int& s){return f+s;}};  
        for (int i = 0; i < 100000; i++)
        {
            if(get<0>(queries[i]) == 0){
                auto ans = st.Query(get<1>(queries[i]), get<2>(queries[i]));
                //cout<<ans<<'\n';
            }
            else
                st.Update(get<1>(queries[i]), get<2>(queries[i]));
        }
        timestamp_t t1 = get_timestamp();
        cout<<(t1 - t0)/1000000.0L<<'\n';

    }
}
