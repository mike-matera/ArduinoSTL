/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <ios>
#include <ostream>
#include <istream>
#include <cstdio>
#include <fstream>

namespace std{


#ifdef __UCLIBCXX_SUPPORT_CDIR__
	int ios_base::Init::init_cnt;	//Needed to ensure the static value is created

//Create buffers first
#ifdef __UCLIBCXX_SUPPORT_COUT__
	filebuf _cout_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
	filebuf _cin_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
	filebuf _cerr_filebuf;
#endif

//Then create streams
#ifdef __UCLIBCXX_SUPPORT_COUT__
	ostream cout(&_cout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
	istream cin(&_cin_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
	ostream cerr(&_cerr_filebuf);
#endif


	ios_base::Init::Init(){
		if(init_cnt == 0){	//Need to construct cout et al
#ifdef __UCLIBCXX_SUPPORT_COUT__
			_cout_filebuf.fp = stdout;
			_cout_filebuf.openedFor = ios_base::out;
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
			_cerr_filebuf.fp = stderr;
			_cerr_filebuf.openedFor = ios_base::out;
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
			_cin_filebuf.fp = stdin;
			_cin_filebuf.openedFor = ios_base::in;

#ifdef __UCLIBCXX_SUPPORT_COUT__
			cin.tie(&cout);
#endif

#endif
		}
		init_cnt++;
	}

	ios_base::Init::~Init(){
		--init_cnt;
		if(init_cnt==0){

		}
	}
#endif

	ios_base::fmtflags ios_base::flags(fmtflags fmtfl){
		fmtflags temp = mformat;
		mformat = fmtfl;
		return temp;
	}

	ios_base::fmtflags ios_base::setf(fmtflags fmtfl){
		return flags(flags() | fmtfl);
	}







}


