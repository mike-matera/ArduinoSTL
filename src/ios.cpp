#include <ios>
#include <ostream>
#include <istream>
#include <cstdio>
#include <fstream>

namespace std{

	int ios_base::Init::init_cnt;	//Needed to ensure the static value is created

	filebuf _cout_filebuf;
	filebuf _cin_filebuf;

	ostream cout(&_cout_filebuf);
	istream cin(&_cin_filebuf);


	ios_base::Init::Init(){
		if(init_cnt == 0){	//Need to construct cout et al
			_cout_filebuf.fp = stdout;
			_cout_filebuf.openedFor = ios_base::out;
			_cin_filebuf.fp = stdin;
			_cin_filebuf.openedFor = ios_base::in;
		}
		init_cnt++;
	}

	ios_base::Init::~Init(){
		--init_cnt;
		if(init_cnt==0){

		}
	}

//	short unsigned int ios_base::flags() const{
//	ios_base::fmtflags ios_base::flags() const{
//		return mformat;
//	}

	ios_base::fmtflags ios_base::flags(fmtflags fmtfl){
		fmtflags temp = mformat;
		mformat = fmtfl;
		return temp;
	}

	ios_base::fmtflags ios_base::setf(fmtflags fmtfl){
		return flags(flags() | fmtfl);
	}







};


