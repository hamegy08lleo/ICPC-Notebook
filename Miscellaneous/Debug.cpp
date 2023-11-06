#ifdef hvmegy
#define dbg(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
	cerr << "[" << vars << " : ";
	string delim = "";
	(..., (cerr << delim << values, delim = ", "));
	cerr << "]" << '\n'; 
}
#else
#define dbg(...)
#endif
