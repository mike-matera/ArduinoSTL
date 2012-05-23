#include <iostream>
#include <sstream>

int main(){
	std::cout << "Beginning sstream test\n";
	
	std::stringstream a;
	float f;
	int i;
	std::string s;
	char c;

	a << "Starting testing ";
	a << 2 ;
	a << " " << 2.0;

	std::cout << a.str() << std::endl;

	a.str("abcdefg");
	a.get(c);
	std::cout << "Character getted: " << c << std::endl;
	a.get(c);
	std::cout << "Character getted: " << c << std::endl;

	s = a.str();
	std::cout << "input buffer: " << s << std::endl;
	std::cout << "Character 0: " << s[0] << ", character 1: " << s[1] << std::endl;



	a.str("2.35 5 Test");

	a >> f >> i >> s;

	std::cout << "f (should be 2.35): " << f << std::endl;
	std::cout << "i (should be 5): " << i << std::endl;
	std::cout << "s (should be Test): " << s << std::endl;

	a.clear();
	std::cout << "Buffer after flag clear: " << a.str() << std::endl;

	std::cout <<"Combining read and write activities\n";
	a.str("Testing data");
	s = "";
	a << 2.5 << " ";// << 't' << "T";
	a >> s;
	std::cout << "Read out: " << "'" << s << "'" << std::endl;
	a >> s;
	std::cout << "Read out: " << "'" << s << "'" << std::endl;
	std::cout << "Current buffer value: " << a.str() << std::endl;

	std::cout << "Appending more text by a number of methods\n";
	a << "trd" << std::endl << std::endl;
	a.put(10);
	a << "4635";
	std::cout << "String stream text:" << a.str() << std::endl;
	std::cout << "String stream test:" << a.str().c_str() << std::endl;


	std::cout << "Checking ostringstream" << std::endl;

	std::ostringstream o;

	s = "This is a test string";
	s = "Test string";
	
	o << "Test string ";
	o << 5 << " ";
	o << 3.5 << " ";
	o << "Another test string";
	o << " " << std::endl << "abcdefghiojklmnopqrstuvwxyz";
	o << " " << std::endl << "abcdefghiojklmnopqrstuvwxyz";
	o << " " << std::endl << "abcdefghiojklmnopqrstuvwxyz";
	o << " " << std::endl << "abcdefghiojklmnopqrstuvwxyz";
	o << " " << std::endl << s << std::endl;

	std::cout << o.str() << std::endl;

	{
	std::stringstream ss;
	if (ss.flags() &~ (std::ios_base::skipws | std::ios_base::dec))
		std::cout << "ERROR: stream constructor with invalid additional flags "
			<< (ss.flags() &~ (std::ios_base::skipws | std::ios_base::dec))
			<< " set" << std::endl;
	}

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif
	/* test __istream_readin<traits, char, bool>
	   Check that we handle boolalpha correctly
	 */
	std::cout << "Checking __istream_readin<traits, char, bool>" << std::endl;
	struct tests_s {
		unsigned format;
		std::string input;
		std::string output;
		bool b;
		bool fail;
	};
	struct tests_s tests[] = {
		{0, "true", "0", 0, 1},
		{0, "True", "0", 0, 1},
		{0, "TRUE", "0", 0, 1},
		{0, "false", "0", 0, 1},
		{0, "-1", "1", 1, 1},
		{0, "0", "0", 0, 0},
		{0, "1", "1", 1, 0},
		{0, "2", "1", 1, 1},

		{3, "true", "0", 0, 1},
		{3, "True", "0", 0, 1},
		{3, "TRUE", "0", 0, 1},
		{3, "false", "1", 1, 1},
		{3, "-0x1", "1", 1, 1},
		{3, "0x0", "0", 0, 0},
		{3, "0x1", "1", 1, 0},
		{3, "0x2", "1", 1, 1},

		{1, "true", "0", 0, 1},
		{1, "True", "0", 0, 1},
		{1, "TRUE", "0", 0, 1},
		{1, "false", "0", 0, 1},
		{1, "-1", "1", 1, 1},
		{1, "0", "0", 0, 0},
		{1, "1", "1", 1, 0},
		{1, "2", "1", 1, 1},

		{2, "true", "1", 1, 0},
		{2, "True", "0", 0, 1},
		{2, "TRUE", "0", 0, 1},
		{2, "false", "0", 0, 0},
		{2, "-1", "0", 0, 1},
		{2, "0", "0", 0, 1},
		{2, "1", "0", 0, 1},
		{2, "2", "0", 0, 1},
	};
	for (unsigned int i = 0; i < ARRAY_SIZE(tests); i++) {
		struct tests_s *test = tests + i;
		std::string brief;
		std::stringstream ss;
		bool b;

		if (test->format == 3) {
				brief = "no manip., hex";
				ss << std::hex;
				if (!(ss.flags() & ss.hex))
					std::cout << "FAILED to set hex via operator<<"
						<< std::endl;
		} else if (test->format == 2) {
				brief = "boolalpha     ";
				ss << std::boolalpha;
				if (!(ss.flags() & ss.boolalpha))
					std::cout << "FAILED to set boolalpha via operator<<"
						<< std::endl;
		} else if (test->format == 1) {
				brief = "noboolalpha   ";
				ss << std::noboolalpha;
				if (ss.flags() & ss.boolalpha)
					std::cout << "FAILED to unset boolalpha via operator<<"
						<< std::endl;
		} else {
				brief = "no manipulator";
		}
		ss.str(test->input);
		ss >> b;
		std::ostringstream os;
		os << b;
		std::cout << brief << ": "
			<< test->input << " >> bool == \"" << os.str() << "\""
			<< " (expected " << test->output << ")"
			<< ((os.str() == test->output && ss.fail() == test->fail)
				? ", ok" : ", FAILED")
			<< std::endl;
		if (b != test->b)
			std::cout
				<< "WRONG intermediate result bool(" << int(b)
				<< "), expected " << int(test->b)
				<< " for input " << test->input
				<< std::endl;
		if (ss.fail() != test->fail)
			std::cout
				<< "WRONG failbit " << int(ss.fail())
				<< ", expected " << int(test->fail)
				<< " for input " << test->input
				<< std::endl;
	}
	std::cout << std::endl;
	return 0;
}
