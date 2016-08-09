#include <functional>
#include <cstdio>

class Foo{
public:
	Foo() : q(0) {  }
	Foo(int d) : q(d) {  }
	Foo(const Foo & f): q(f.q) {  }
	~Foo() {  }

	Foo & operator=(const Foo & f){
		q = f.q;
		return *this;
	}
	bool operator==(const Foo & f) const{
		return (q == f.q);
	}
	bool operator!=(const Foo & f) const{
		return (q != f.q);
	}
	bool operator<(const Foo & f) const{
		return (q < f.q);
	}
	bool operator<=(const Foo & f) const{
		return (q <= f.q);
	}
	bool operator>(const Foo & f) const{
		return (q > f.q);
	}
	bool operator>=(const Foo & f) const{
		return (q >= f.q);
	}
	Foo operator+(const Foo & rhs) const{
		return Foo(q + rhs.q);
	}
	Foo operator-(const Foo & rhs) const{
		return Foo(q - rhs.q);
	}
	Foo operator*(const Foo & rhs) const{
		return Foo(q * rhs.q);
	}
	Foo operator/(const Foo & rhs) const{
		return Foo(q / rhs.q);
	}
	Foo operator%(const Foo & rhs) const{
		return Foo(q % rhs.q);
	}
	Foo operator-() const{
		return Foo(-q);
	}
	bool operator&&(const Foo & rhs) const{
		return q && rhs.q;
	}
	bool operator||(const Foo & rhs) const{
		return q || rhs.q;
	}
	bool operator!() const{
		return !q;
	}
	void printout(const int i) const{
		printf("%i", i);
	}

private:
	long int q;
};

int main(){
	Foo result;
	Foo a(0);
	Foo b(1);
	Foo c(5);	
	Foo d;
	Foo e(6);
	const Foo f(12);

	std::plus<Foo> foo_plus;
	d = foo_plus(a, c);

	if(d == c){
		printf("d == c (correct)\n");
	}else{
		printf("d !== c (WRONG)\n");
	}

	d = foo_plus(b, c);
	if(d == Foo(6)){
		printf("d == 6 (correct)\n");
	}else{
		printf("d !== 6 (WRONG)\n");
	}

	std::minus<Foo> foo_minus;
	d = foo_minus(c, a);
	if(d == c){
		printf("d == c (correct)\n");
	}else{
		printf("d !== c (WRONG)\n");
	}

	d = foo_minus(c, b);
	if(d == Foo(4)){
		printf("d == 4 (correct)\n");
	}else{
		printf("d !== 4 (WRONG)\n");
	}

	std::multiplies<Foo> foo_multiplies;
	d = foo_multiplies(c, b);
	if(d == c){
		printf("d == c (correct)\n");
	}else{
		printf("d !== c (WRONG)\n");
	}

	d = foo_multiplies(c, c);
	if(d == Foo(25)){
		printf("d == 25 (correct)\n");
	}else{
		printf("d !== 25 (WRONG)\n");
	}

	std::divides<Foo> foo_divides;
	d = foo_divides(c, b);
	if (d == c){
		printf("d == c (correct)\n");
	}else{
		printf("d !== c (WRONG)\n");
	}

	d = foo_divides(c, c);
	if (d == b){
		printf("d == b (correct)\n");
	}else{
		printf("d !==b (WRONG)\n");
	}

	std::modulus<Foo> foo_modulus;
	d = foo_modulus(c, c);
	if(d == a){
		printf("d == a (correct)\n");
	}else{
		printf("d !==a (WRONG)\n");
	}
	
	d = foo_modulus(e, c);
	if(d == b){
		printf("d == b (correct)\n");
	}else{
		printf("d !== b (WRONG)\n");
	}

	std::negate<Foo> foo_negate;
	d = foo_negate(c);
	if( d == Foo(-5)){
		printf("d == -5 (correct)\n");
	}else{
		printf("d !== -5 (WRONG)\n");
	}

	d = foo_negate(b);
	if(d == Foo(-1)){
		printf("d == -1 (correct)\n");
	}else{
		printf("d !== -1 (WRONG)\n");
	}

	std::equal_to<Foo> foo_equal_to;
	if(foo_equal_to(c, Foo(5))){
		printf("c == 5 (correct)\n");
	}else{
		printf("c !== 5 (WRONG)\n");
	}

	if(foo_equal_to(a, a)){
		printf("a == a (correct)\n");
	}else{
		printf("a !== a (WRONG)\n");
	}

	if(foo_equal_to(a, b)){
		printf("a == b (WRONG)\n");
	}else{
		printf("a !==b (correct)\n");
	}

	std::not_equal_to<Foo> foo_not_equal_to;

	if(foo_not_equal_to(a, b)){
		printf("a != b (correct)\n");
	}else{
		printf("a !!=b (WRONG)\n");
	}

	if(foo_not_equal_to(c, c)){
		printf("a != b (WRONG)\n");
	}else{
		printf("a !!=b (correct)\n");
	}

	std::greater<Foo> foo_greater;
	if(foo_greater(c, b)){
		printf("c > b (correct)\n");
	}else{
		printf("c !> b (WRONG)\n");
	}

	if(foo_greater(a, a)){
		printf("a > a (WRONG)\n");
	}else{
		printf("a !>a (correct)\n");
	}

	std::less<Foo> foo_less;
	if(foo_less(b, c)){
		printf("b < c (correct)\n");
	}else{
		printf("b !< c (WRONG)\n");
	}

	if(foo_less(c, c)){
		printf("c < c (WRONG)\n");
	}else{
		printf("c !< c (correct)\n");
	}

	std::greater_equal<Foo> foo_greater_equal;
	if(foo_greater_equal(c, b)){
		printf("c >= b (correct)\n");
	}else{
		printf("c !>= b (WRONG)\n");
	}

	if(foo_greater_equal(b, b)){
		printf("b >= b (correct)\n");
	}else{
		printf("b !>= b (WRONG)\n");
	}

	if(foo_greater_equal(b, c)){
		printf("b >= c (WRONG)\n");
	}else{
		printf("b !>= c (correct)\n");
	}

	std::less_equal<Foo> foo_less_equal;
	if(foo_less_equal(b, c)){
		printf("b <= c (correct)\n");
	}else{
		printf("b !<= c (WRONG)\n");
	}

	if(foo_less_equal(c, b)){
		printf("c >= b (WRONG)\n");
	}else{
		printf("c !>= b (correct)\n");
	}

	if(foo_less_equal(b, b)){
		printf("b >= b (correct)\n");
	}else{
		printf("b !>= b (WRONG)\n");
	}

	std::logical_and<Foo> foo_logical_and;
	if(foo_logical_and(c, c)){
		printf("c && c (correct)\n");
	}else{
		printf("c !&& c (WRONG)\n");
	}
	

	if(foo_logical_and(c, b)){
		printf("c && b (correct)\n");
	}else{
		printf("c !&& b (WRONG)\n");
	}

	if(foo_logical_and(a, b)){
		printf("a && b (WRONG)\n");
	}else{
		printf("a !&& b (correct)\n");
	}

	if(foo_logical_and(a, a)){
		printf("a && a (WRONG)\n");
	}else{
		printf("a !&& a (correct)\n");
	}

	std::logical_or<Foo> foo_logical_or;
	if(foo_logical_or(c, c)){
		printf("c || c (correct)\n");
	}else{
		printf("c !|| c (WRONG)\n");
	}
	

	if(foo_logical_or(c, b)){
		printf("c || b (correct)\n");
	}else{
		printf("c !|| b (WRONG)\n");
	}

	if(foo_logical_or(a, b)){
		printf("a || b (correct)\n");
	}else{
		printf("a !|| b (WRONG)\n");
	}

	if(foo_logical_or(a, a)){
		printf("a || a (WRONG)\n");
	}else{
		printf("a !|| a (correct)\n");
	}

	std::logical_not<Foo> foo_logical_not;
	if(foo_logical_not(a)){
		printf("!a (correct)\n");
	}else{
		printf("!!a (WRONG)\n");
	}

	if(foo_logical_not(b)){
		printf("!a (WRONG)\n");
	}else{
		printf("!!a (correct)\n");
	}

	//Checking out std::not1
	if(std::not1(foo_logical_not)(b)){
		printf("!!b (correct)\n");
	}else{
		printf("!!!b (WRONG)\n");
	}
	if(std::not1(foo_logical_not)(c)){
		printf("!!b (correct)\n");
	}else{
		printf("!!!b (WRONG)\n");
	}
	if(std::not1(foo_logical_not)(a)){
		printf("!!b (WRONG)\n");
	}else{
		printf("!!!b (correct)\n");
	}

	//Checking out std::not2
	if(std::not2(std::equal_to<Foo>())(c, c)){
		printf("c !== c (WRONG)\n");
	}else{
		printf("c !!== c (correct)\n");
	}

	if(std::not2(std::equal_to<Foo>())(a, b)){
		printf("a !== b (correct)\n");
	}else{
		printf("a !!== b (WRONG)\n");
	}

	if(std::binder1st<std::less<Foo> >(std::less<Foo>(), b)(c)){
		printf("b < c (correct)\n");
	}else{
		printf("b !< c (WRONG)\n");
	}

	if(std::binder1st<std::less<Foo> >(std::less<Foo>(), c)(c)){
		printf("c < c (WRONG)\n");
	}else{
		printf("c !< c (correct)\n");
	}

	if(std::binder1st<std::less<Foo> >(std::less<Foo>(), c)(a)){
		printf("c < a (WRONG)\n");
	}else{
		printf("c !< a (correct)\n");
	}

	if(std::binder2nd<std::less<Foo> >(std::less<Foo>(), c)(a)){
		printf("a < c (correct)\n");
	}else{
		printf("a !< c (WRONG)\n");
	}

	if(std::binder2nd<std::less<Foo> >(std::less<Foo>(), b)(c)){
		printf("c < b (WRONG)\n");
	}else{
		printf("c !< b (correct)\n");
	}

	if(std::binder2nd<std::less<Foo> >(std::less<Foo>(), c)(c)){
		printf("c < c (WRONG)\n");
	}else{
		printf("c !< c (correct)\n");
	}


	
	printf("The following should print 7:");
	std::mem_fun(&Foo::printout)(&c, 7);
	printf("\n");

	printf("The following should print 12:");
	std::mem_fun(&Foo::printout)(&f, 12);
	printf("\n");

	return 0;
}

