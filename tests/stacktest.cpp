#include <iostream>
#include <stack>
#include <vector>
#include "testframework.h"


unsigned long int checkStackSize(){
	std::stack<int, std::deque<int> > s;
	s.push(42);
	s.push(101);
	s.push(69);
	return s.size();
}

bool checkStackPop(){
	std::stack<int, std::deque<int> > s;
	s.push(42);
	s.push(101);
	s.push(69);

	int i;

	i = s.top();
	if(69 != i){
		printf("Popped %i instead of 69\n", i);
		return false;
	}
	s.pop();
	i = s.top();
	if(101 != i){
		printf("Popped %i instead of 101\n", i);
		return false;
	}
	s.pop();
	i = s.top();
	if(42 != i){
		printf("Popped %i instead of 42\n", i);
		return false;
	}
	s.pop();

	return s.size() == 0;
}

bool checkStackEquality(){
	std::stack<int, std::deque<int> > s, t;
	s.push(42);
	s.push(101);
	s.push(69);
	t.push(42);
	t.push(101);
	t.push(69);
	
	return s == t;
}


int main(){

	std::cout<<"Starting stack test" << std::endl;

	TestFramework::init();

	TestFramework::AssertReturns<unsigned long int>(checkStackSize, 3);
	TestFramework::AssertReturns<bool>(checkStackPop, true);
	TestFramework::AssertReturns<bool>(checkStackEquality, true);

	TestFramework::results();

	return 0;
}
