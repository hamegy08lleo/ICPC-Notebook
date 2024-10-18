#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <class type1>
using ordered_set = tree<type1, null_type, less_equal<type1>, rb_tree_tag, tree_order_statistics_node_update>;
.insert(x); // insert x
.order_of_key(val + 1) - .order_of_key(val) > 0; // check val exists
.erase(.find_by_order(.order_of_key(c))) // erase c , should check exists before
.find_by_order(pos) // s[pos] : 0-indexed
.order_of_key(x) // n.o element less than x
