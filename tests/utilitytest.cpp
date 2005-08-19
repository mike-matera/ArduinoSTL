#include <utility>
#include <cstdio>

//using namespace std::rel_ops;

void test_rel_ops();
void test_pair_ops();

class Foo{
public:
	Foo(int i) : q(new int(i)) { }

	Foo(const Foo & f) : q(new int( *(f.q))) {  }

	~Foo(){
		delete q;
	}

	bool operator< (const Foo & rhs) const{
		if(*q < *(rhs.q)){
			return true;
		}
		return false;
	}

	Foo & operator=(Foo & rhs){
		if( & rhs == this){
			return *this;
		}
		*q = *(rhs.q);
		return *this;
	}

	bool operator==(const Foo & rhs) const{
		return ( *q == *(rhs.q));
	}

private:
	int * q;

};


int main(){
	test_rel_ops();
	test_pair_ops();

	Foo a(1);
	Foo b(2);
	Foo c(3);

	std::pair<Foo, Foo> p(a, b);
	std::pair<Foo, Foo> q(a, b);

	if(p == q){
		printf("p == q (correct)\n");
	}else{
		printf("p != q (WRONG)\n");
	}

	if(q == p){
		printf("p == q (correct)\n");
	}else{
		printf("p != q (WRONG)\n");
	}

	if(p < q){
		printf("p < q (WRONG)\n");
	}else{
		printf("p !< q (correct)\n");
	}

	if(q < p){
		printf("q < p (WRONG)\n");
	}else{
		printf("q !< p (correct)\n");
	}

//The required operations aren't being generated from rel_ops 

	if(p > q){
		printf("p > q (WRONG)\n");
	}else{
		printf("p !>q (correct)\n");
	}

	if( p != q ){
		printf("p != q (WRONG)\n");
	}else{
		printf("p !!= q (correct)\n");
	}

	if(q != p){
		printf("q != p (WRONG)\n");
	}else{
		printf("q !!= p (correct)\n");
	}


	std::pair<Foo, Foo> r = std::make_pair(a, b);
	if(p == r){
		printf("p == r (correct)\n");
	}else{
		printf("p != r (WRONG)\n");
	}



	return 0;
}



void test_rel_ops(){
	using namespace std::rel_ops;

	Foo a(5);
	Foo b(5);
	Foo c(6);

	if( a != b){
		printf("a != b (WRONG)\n");
	}else{
		printf("a !!= b (correct)\n");
	}

	if( b != a){
		printf("b != a (WRONG)\n");
	}else{
		printf("b !!= a (correct)\n");
	}

	if( a != c){
		printf("a != c (correct)\n");
	}else{
		printf("a !!=c (WRONG)\n");
	}

	if( c != a){
		printf("a != c (correct)\n");
	}else{
		printf("a !!=c (WRONG)\n");
	}

	if( a > b){
		printf("a > b (WRONG)\n");
	}else{
		printf("a !> b (correct)\n");
	}

	if( b > a){
		printf("b > a (WRONG)\n");
	}else{
		printf("b !> a (correct)\n");
	}

	if( a > c){
		printf("a > c (WRONG)\n");
	}else{
		printf("a !> c (correct)\n");
	}

	if( c > a){
		printf("c > a (correct)\n");
	}else{
		printf("c !> a (wrong)\n");
	}

	if( a <= b){
		printf("a <= b (correct)\n");
	}else{
		printf("a !<= b (WRONG)\n");
	}

	if( b <= a){
		printf("b <= a (correct)\n");
	}else{
		printf("b !<= a (WRONG)\n");
	}
	
	if( c <= a ){
		printf("c <= a (WRONG)\n");
	}else{
		printf("c !<= a (correct)\n");
	}

	if( a <= c ){
		printf("a <= c (correct)\n");
	}else{
		printf("a !<= c (WRONG)\n");
	}

	if(a >= b){
		printf("a >= b (correct)\n");
	}else{
		printf("a !>= b (WRONG)\n");
	}

	if(b >= a){
		printf("b >= a (correct)\n");
	}else{
		printf("b !>= a (WRONG)\n");
	}

	if(a >= c){
		printf("a >= c (WRONG)\n");
	}else{
		printf("a !>= c (correct)\n");
	}

	if(c >= a){
		printf("c >= a (correct)\n");
	}else{
		printf("c !>= a (WRONG)\n");
	}
}


void test_pair_ops(){
	std::pair<char, int> a;
	std::pair<char, int> b;

	a = std::pair<char, int>('a', 7531);
	b = a;
	
	printf("Pair a (should be a, 7531): %i, %i\n", a.first, a.second);
	printf("Pair b (should be a, 7531): %i, %i\n", b.first, b.second);

	b.second=61473;
	b.first='b';
	printf("Pair b (should be b, 61473): %i, %i\n", b.first, b.second);

	std::pair<char, int> c(b);
	printf("Pair c (should be c, 61473): %i, %i\n", c.first, c.second);


	std::pair<Foo, Foo> d = std::pair<Foo, Foo>(5, 18);
	std::pair<Foo, Foo> e(d);

	e = d;

	if(std::pair<Foo, Foo>(5, 18) == e){
		printf("e == (5, 18)\n");
	}else{
		printf("e !== (5, 18)\n");
	}


}
