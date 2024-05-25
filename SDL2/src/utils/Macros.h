#ifdef DEBUG
	#define DEBUG_LOG(x) std::cout << x << std::endl; __debugbreak()
#else
	#define DEBUG_LOG(x)
#endif