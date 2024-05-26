#ifdef DEBUG
	#define LOG(x) std::cout << x << std::endl
	#define DEBUG_LOG(x) std::cout << x << std::endl; __debugbreak()
#else
	#define DEBUG_LOG(x)
#endif