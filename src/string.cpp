#include <string>
#include <string.h>

namespace std{

const char_traits<char>::char_type* char_traits<char>::find(const char_type* s, int n, const char_type& a){
	for(int i=0; i < n; i++){
		if(eq(s[i], a)){
			return (s+i);
		}
	}
	return 0;
}



#ifdef USE_WCHAR
const char_traits<wchar_t>::char_type* char_traits<wchar_t>::find(const char_type* s, int n, const char_type& a){
	for(int i=0; i < n; i++){
		if(eq(s[i], a)){
			return (s+i);
		}
	}
	return 0;
}

#endif


//Stuff for basic_string proper





};


