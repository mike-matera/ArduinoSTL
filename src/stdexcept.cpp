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

#include <exception>
#include <stdexcept>

#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__

namespace std{

	logic_error::logic_error() throw() : mstring(){

	}

	logic_error::logic_error(const string& what_arg) : mstring(what_arg){

	}

	logic_error::~logic_error() throw(){

	}

	const char * logic_error::what(){
		return mstring.c_str();
	}


	out_of_range::out_of_range() : logic_error(){

	}

	out_of_range::out_of_range(const string & what_arg) : logic_error(what_arg) {
	
	}

	out_of_range::~out_of_range() throw() {
	
	}


	runtime_error::runtime_error() : mstring(){

	}

	runtime_error::runtime_error(const string& what_arg) : mstring(what_arg){

	}

	runtime_error::~runtime_error(){

	}

	const char * runtime_error::what(){
		return mstring.c_str();
	}

};

#endif

