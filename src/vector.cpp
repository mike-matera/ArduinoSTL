#include <vector>

namespace std{


#ifdef EXPAND_VECTOR_FOR_CHAR

	template<> void vector<char, allocator<char> >::reserve(size_type n){
		__vector_helper_functions<char, allocator<char> >::
			reserve(a, data, elements, data_size, n);
	}
/*	template<> void vector<unsigned char, allocator<unsigned char> >::reserve(size_type n){
		__vector_helper_functions<unsigned char, allocator<unsigned char> >::
			reserve(a, data, elements, data_size, n);
	}*/

#endif




};
