#include <iostream>
#include <stack>
#include <vector>

int main(){


	std::cout<<"Starting stack test" << std::endl;
	std::stack<int, std::deque<int> > s;
	s.push(42);
	s.push(101);
	s.push(69);
	std::cout << "Size of stack: " << s.size() << std::endl;
	while(!s.empty()){
		std::cout << s.top() << " " << s.size() << std::endl;
		s.pop();
	}

	return 0;
}
