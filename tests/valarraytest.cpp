#include <iostream>
#include <valarray>


int main(){
	
	std::valarray<int> a(10);
	a[0] = 0;
	a[1] = 1;
	a[2] = 2;
	a[3] = 3;
	a[4] = 4;
	a[5] = 5;
	a[6] = 6;
	a[7] = 7;
	a[8] = 8;
	a[9] = 9;

	std::cout << "Value of valarray:" ;
	for(size_t i = 0; i < a.size(); ++i){
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	std::valarray<int> sl(a[std::slice(1, 5, 2)]);
	std::cout << "Value of slice_array:" ;
	for(size_t i = 0; i < sl.size(); ++i){
		std::cout << sl[i] << " ";
	}
	std::cout << std::endl;


	return 0;
}
