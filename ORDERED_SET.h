#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 

template<typename num_t>
struct ordered_set
{   
    tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update> vals;
    
    ordered_set() {}
    ordered_set(std::initializer_list<num_t> l) { for (auto& e : l) vals.insert(e); }

    void insert(num_t val) { vals.insert(val); }
    void insert(std::initializer_list<num_t> l) { for (auto& e : l) vals.insert(e); }

    template<typename T>void erase(T val) { vals.erase(val); }
    
    num_t operator[](int k) {return *vals.find_by_order(k); }
    int order_of_key(num_t k) { return vals.order_of_key(k); }

    auto begin() { return vals.begin(); }
    auto end() { return vals.end(); }
    auto rbegin() { return vals.rbegin(); }
    auto rend() { return vals.rend(); }

    auto find(num_t val) { return vals.find(val);}

    auto lower_bound(num_t k) { return vals.lower_bound(k); }
    auto upper_bound(num_t k) { return vals.upper_bound(k); }

    int size() { return vals.size(); }
    void clear() { vals.clear(); }
};

template <typename num_t>
struct ordered_multiset 
{
    tree<pair<num_t, int>, null_type, less<pair<num_t, int>>, rb_tree_tag, tree_order_statistics_node_update> vals;
    set<pair<num_t, int>> best;

    // ordered_set() {}
    // ordered_set(std::initializer_list<num_t> l) { for (auto& e : l) vals.insert(e); }

    // void insert(num_t val) { vals.insert(val); }
    // void insert(std::initializer_list<num_t> l) { for (auto& e : l) vals.insert(e); }

    // template<typename T>void erase(T val) { vals.erase(val); }

    void insert(num_t val) 
    {
        if (vals.find(make_pair(val, -1)) != vals.end()) 
        { 
            int loc = (*best.upper_bound(make_pair(val - 1, 0))).second;
            best.erase(make_pair(val, loc));
            best.insert(make_pair(val, loc - 1));
            vals.insert(make_pair(val, loc - 1));
        } 
        else 
        { 
            best.insert(make_pair(val, -1));
            vals.insert(make_pair(val, -1));
        }
    }
    
    void erase(num_t val) // erases one 
    {
        if (vals.find(make_pair(val, -1)) == vals.end()) return;

        num_t loc = (*best.upper_bound(make_pair(val - 1, 0))).second;
        
        best.erase(make_pair(val, loc));
        vals.erase(make_pair(val, loc));
        if (loc != -1) best.insert(make_pair(val, loc + 1));
    }
    
    num_t operator[](int k) { return (*vals.find_by_order(k)).first; }
    int order_of_key(num_t k) { return vals.order_of_key(make_pair(k - 1, 0)); }

    auto begin() { return vals.begin(); }
    auto end() { return vals.end(); }
    auto rbegin() { return vals.rbegin(); }
    auto rend() { return vals.rend(); }

    auto find(num_t val) { return vals.find(make_pair(val, -1));}

    auto lower_bound(num_t k) { return vals.lower_bound(make_pair(k - 1, 0)); }
    auto upper_bound(num_t k) { return vals.upper_bound(make_pair(k, 0)); }

    int size() { return vals.size(); }
    int count(num_t k) { return vals.order_of_key({k, 0}) - vals.order_of_key({k - 1, 0}); }
    void clear() { vals.clear(); best.clear(); }

};