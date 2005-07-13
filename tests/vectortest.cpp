#include <vector>
#include <string>
#include <iostream>

class myclass{
private:
	int num;
public:
	myclass() : num(0) {  }
	myclass(int i): num(i) {  }
	~myclass() {
		std::cout << "Calling destructor with num: " << num << std::endl;
		num = -1;
	}
	
	void printout() const {
		std::cout << num << std::endl;
	}
	int getNum() const {
		return num;
	}
	void setNum(int i){
		num = i;
	}
};


int main(){
	std::vector<char, std::allocator<char> > ctest;
	std::string stest;
	ctest.push_back('t');

	std::vector<int> test;
	std::vector<int> test1;
	unsigned int temp;
	std::vector<int>::iterator i,j;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);

	std::cout << "Element 0: " << test[0] << std::endl;
	std::cout << "Element 1: " << test[1] << std::endl;
	std::cout << "Element 2: " << test[2] << std::endl;
	std::cout << "Element 3: " << test[3] << std::endl;
	std::cout << "Element 4: " << test[4] << std::endl;

	test.pop_back();

	std::cout << "Testing at(int)\n";
	std::cout << "Element 0: " << test.at(0) << std::endl;
	std::cout << "Element 1: " << test.at(1) << std::endl;
	std::cout << "Element 2: " << test.at(2) << std::endl;
	std::cout << "Element 3: " << test.at(3) << std::endl;
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator insert\n";
	i = test.begin();
	++i;
	++i;
	i = test.insert(i, 12);
	std::cout << "Return value points to: " << *i << ", should be 12\n";
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator multi-insert\n";
	i = test.begin();
	++i;
	temp = 23;
	test.insert(i, 3, temp);
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}


	std::cout << "Testing iterator erase\n";
	i = test.begin();
	++i;
	++i;
	test.erase(i);
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator multierase\n";
	i = test.begin();
	j = test.begin();
	++i;
	++i;
	j+=4;
	test.erase(i, j);
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator range insert\n";
	test1.clear();
	test1.insert(test1.begin(), test.begin(), test.end());
	std::cout << "The following should be the same as the above:\n";
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}


	std::cout << std::endl << "Testing vectors of pointers\n";

	myclass m1(1);
	myclass m2(2);
	myclass m3(3);
	myclass m4(4);
	myclass m5(5);

	std::vector<myclass *> mcp;
	mcp.push_back(&m1);
	mcp.push_back(&m2);
	mcp.push_back(&m3);
	mcp.push_back(&m4);
	mcp.push_back(&m5);

	mcp[0]->printout();
	mcp[1]->printout();
	mcp[2]->printout();
	mcp[3]->printout();
	mcp[4]->printout();

	std::vector<myclass *>::iterator mcpi;
	mcpi = mcp.end();
	while(mcpi != mcp.begin()){
		--mcpi;
		(*mcpi)->printout();
	}

	mcp.pop_back();
	mcpi = mcp.end();
	while(mcpi != mcp.begin()){
		--mcpi;
		(*mcpi)->printout();
	}

	mcp.clear();

	std::cout << "Pushing back instances of myclass created with new" << std::endl;

	mcp.push_back(new myclass());
	mcp.push_back(new myclass());
	mcp.push_back(new myclass());
	mcp.push_back(new myclass());
	mcp.push_back(new myclass());
	mcp.push_back(new myclass());

	std::cout << "Deleting instances of myclass directly from iterator" << std::endl;

	for(mcpi = mcp.begin(); mcpi != mcp.end(); ++mcpi){
		std::cout << "Deleteing myclass instance" << std::endl;
		delete *mcpi;
	}

	std::cout << "Delete completed on myclass instances" << std::endl;

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 4" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;

	std::cout << "Testing resize()" << std::endl;
	mcp.resize(1, &m5);

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 1" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;

	mcp.resize(95, &m4);

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 95" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;


	mcp.resize(1, &m4);

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 1" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;

	mcp.push_back(&m3);

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 2" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;

	for(int j = 0; j < 100; ++j){
		mcp.push_back(&m2);
	}

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 102" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;

	myclass * m6 = new myclass(6);

	mcp.push_back(m6);

	std::cout << "The following two lines should be identical:" << std::endl;
	std::cout << "Vector size: 103" << std::endl;
	std::cout << "Vector size: " << mcp.size() << std::endl;

	mcp.clear();
	delete m6;

	return 0;
}
