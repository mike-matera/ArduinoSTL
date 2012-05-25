#include <iostream>
#include <valarray>

bool check_array(std::valarray<int>& a, int b[]) {
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != b[i]) {
			std::cout << "[" << i << "] "
				<< a[i] << " != " << b[i] << std::endl;
			return false;
		}
	return true;
}

void print_array(std::string s, std::valarray<bool>& a) {
	std::cout << s;
	for (size_t i = 0; i < a.size(); ++i){
		std::cout << " " << a[i];
	}
	std::cout << std::endl;
}
void print_array(std::string s, std::valarray<int>& a) {
	std::cout << s;
	for (size_t i = 0; i < a.size(); ++i){
		std::cout << " " << a[i];
	}
	std::cout << std::endl;
}
void print_array(std::string s, std::valarray<double>& a) {
	std::cout << s;
	for (size_t i = 0; i < a.size(); ++i){
		std::cout << " " << a[i];
	}
	std::cout << std::endl;
}
void print_array(std::string s, std::valarray<float>& a) {
	std::cout << s;
	for (size_t i = 0; i < a.size(); ++i){
		std::cout << " " << a[i];
	}
	std::cout << std::endl;
}
#if defined __UCLIBCXX_HAS_LONG_DOUBLE__ || defined _GLIBCXX_USE_C99_MATH_TR1
void print_array(std::string s, std::valarray<long double>& a) {
	std::cout << s;
	for (size_t i = 0; i < a.size(); ++i){
		std::cout << " " << a[i];
	}
	std::cout << std::endl;
}
#endif

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

	print_array("Value of valarray<int> a:", a);

	std::valarray<int> sl(a[std::slice(1, 5, 2)]);
	print_array("Value of slice_array:", sl);

	std::cout << std::endl;
	std::cout << "valarray operators" << std::endl;
	std::valarray<int> c = -a;
	print_array("Value of -a:", c);
	c = +a;
	print_array("Value of +a:", c);
	c = ~a;
	print_array("Value of ~a:", c);

	std::valarray<bool> b = !a;
	print_array("valarray<bool> = !a:", b);
	std::cout << "(valarray<bool> = !valarray<int>).max() = " << b.max() << std::endl;
	std::cout << "(valarray<bool> = !valarray<int>).min() = " << b.min() << std::endl;

	std::cout << std::endl;
	std::cout << "valarray algo" << std::endl;
	std::cout << "valarray.max() = " << a.max() << std::endl;
	c = abs(a);
	print_array("Result of abs(a):", c);

	double dd;
	float ff;
	std::valarray<double> d(10), ret_d(10);
	std::valarray<float> f(10), ret_f(10);
	d[0] = 0;
	d[1] = 1;
	d[2] = 2;
	d[3] = 3;
	d[4] = 4;
	d[5] = 5;
	d[6] = 6;
	d[7] = 7;
	d[8] = 8;
	d[9] = 9;
	f[0] = 0.0;
	f[1] = 1.1;
	f[2] = 2.2;
	f[3] = 3.3;
	f[4] = 4.4;
	f[5] = 5.5;
	f[6] = 6.6;
	f[7] = 7.7;
	f[8] = 8.8;
	f[9] = 9.9;
#if defined __UCLIBCXX_HAS_LONG_DOUBLE__ || defined _GLIBCXX_USE_C99_MATH_TR1
	long double ldld;
	std::valarray<long double> ld(10), ret_ld(10);
	ld[0] = 0;
	ld[1] = 1;
	ld[2] = 65536;
	ld[3] = 43046721;
	ld[4] = 4294967296;
	ld[5] = 152587890625;
	ld[6] = 2821109907456;
	ld[7] = 33232930569601;
	ld[8] = 281474976710656;
	ld[9] = 1853020188851841;
# define MAYBE_LD_1(fn) \
	ret_ld = fn(ld); \
	print_array("Result of " # fn "(ld):", ret_ld);
# define MAYBE_LD_2(fn) \
	ldld = ld[0]; \
	ret_ld = fn(ld, ld); \
	print_array("Result of " # fn "(ld, ld):", ret_ld); \
	ret_ld = fn(ldld, ld); \
	print_array("Result of " # fn "(type, ld):", ret_ld); \
	ret_ld = fn(ld, ldld); \
	print_array("Result of " # fn "(ld, type):", ret_ld);
#else
# define MAYBE_LD_1(fn) /**/
# define MAYBE_LD_2(fn) /**/
#endif
#define DO_1(fn) \
	ret_d = fn(d); \
	print_array("Result of " # fn "(d):", ret_d); \
	ret_f = fn(f); \
	print_array("Result of " # fn "(f):", ret_f); \
	MAYBE_LD_1(fn)
#define DO_2(fn) \
	dd = d[0]; \
	ret_d = fn(d, d); \
	print_array("Result of " # fn "(d, d):", ret_d); \
	ret_d = fn(dd, d); \
	print_array("Result of " # fn "(type, d):", ret_d); \
	ret_d = fn(d, dd); \
	print_array("Result of " # fn "(d, type):", ret_d); \
	ff = f[0]; \
	ret_f = fn(f, f); \
	print_array("Result of " # fn "(f, f):", ret_f); \
	ret_f = fn(ff, f); \
	print_array("Result of " # fn "(type, f):", ret_f); \
	ret_f = fn(f, ff); \
	print_array("Result of " # fn "(f, type):", ret_f); \
	MAYBE_LD_2(fn)

	DO_1(acos)
	DO_1(asin)
	DO_1(atan)
	DO_2(atan2)
	DO_1(cos)
	DO_1(cosh)
	DO_1(exp)
	DO_1(log)
	DO_1(log10)
	DO_2(pow)
	DO_1(sin)
	DO_1(sinh)
	DO_1(sqrt)
	DO_1(tan)
	DO_1(tanh)
	std::cout << std::endl;

	return 0;
}
