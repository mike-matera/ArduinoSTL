#include <locale>
#include <cstring>
#include <string>
#include <stdexcept>
#include <cctype>

namespace std{

	//Static class members
	size_t locale::id::max_index;
	locale::id ctype<char>::id;
	locale::id num_put<char, ostreambuf_iterator<char> >::id;


	//Global default locale to use
	locale __locale_global_classic = locale::classic();
	locale __locale_global_default = locale::classic();


	//Global Facet objects required to implement locales

	num_put<char, ostreambuf_iterator<char> > __facet_num_put_classic_implementation;
	ctype<char> __facet_ctype_classic_implementation;



	locale::locale() throw() : lName(), locImp(0) {
		lName = __locale_global_default.lName;
		locImp = __locale_global_default.locImp;
		locImp->references++;
	}

	locale::locale(const locale& other) throw() : lName( other.lName), locImp(other.locImp){
//		lName = other.lName;
//		locImp = other.locImp;
		locImp->references++;
	}

	locale::locale(const char* std_name): lName(std_name), locImp(0){
		if(std_name == 0 || (strcmp(std_name, "") !=0 && strcmp(std_name,"C") !=0) ){
			throw runtime_error();
		}


		/*Do implementation-specific things here*/
//		lName = std_name;
		if(lName == "C"){
			locImp = __locale_global_classic.locImp;
			locImp->references++;
		}
	}

	locale::locale(const locale& other, const char* std_name, category c): lName(std_name), locImp(0){
		locImp = new localeImplementation();
		//Do copying of facet pointers but do *not* update facet references yet

		locImp->facetCount = other.locImp->facetCount;
		locImp->facets = new facet*[locImp->facetCount];
		locImp->references=1;

		for(size_t i = 0; i < locImp->facetCount;i++){
			locImp->facets[i] = other.locImp->facets[i];
		}

		//Now copy over stuff
		if(strcmp(std_name, "C")==0){	//"C" locale
			//Find the highest number in the standard locale which we can use
			size_t max_facets = 0;
			for(size_t i = __locale_global_classic.locImp->facetCount; i>0;i--){
				if(__locale_global_classic.locImp->facets[i] !=0 &&
					__locale_global_classic.locImp->facets[i]->c & c >0)
				{
					max_facets = i;
					i = 0;
				}
			}
			//Max sure we have space for the required number of facets
			max_facets++;
			locImp->reserveFacets(max_facets);
			//Loop throuh and copy over the facets, as required
			for(size_t i = 0 ; i < max_facets; i++){
				if(__locale_global_classic.locImp->facets[i]!=0 &&
					__locale_global_classic.locImp->facets[i]->c & c >0)
				{
					locImp->facets[i] = __locale_global_classic.locImp->facets[i];
				}
			}

		}

		//Now adjust all of the reference counts for stuff
		for(size_t i =0; i < locImp->facetCount;i++){
			locImp->facets[i]->references++;
		}
	}

	locale::~locale() throw(){
		locImp->references--;
		if(locImp->references == 0){
			delete locImp;
		}
	}

	const locale& locale::operator=(const locale& other) throw(){
		if(&other == this){
			return *this;
		}
		locImp->references--;
		if(locImp->references == 0){
			delete locImp;
		}
		lName = other.lName;
		locImp = other.locImp;
		locImp->references++;
		return *this;
	}

	basic_string<char> locale::name() const{
		return lName.c_str();
	}


	bool locale::operator==(const locale& other) const{
		if(lName == other.lName){
			return true;
		}
		return false;
	}
	
	bool locale::operator!=(const locale& other) const{
		if(lName != other.lName){
			return true;
		}
		return false;
	}

	template <class charT, class Traits, class Allocator>
		bool locale::operator()(const basic_string<charT,Traits,Allocator>& s1,
		const basic_string<charT,Traits,Allocator>& s2) const
	{
//		return use_facet< collate<charT> > 
//			(*this).compare(s1.data(), s1.data()+s1.size(), s2.data(), s2.data()+s2.size()) < 0;

	}


	locale locale::global(const locale& loc){
		locale retval = __locale_global_default;
		__locale_global_default = loc;
		return retval;
	}

	const locale& locale::classic(){
		if( __locale_global_classic.locImp == 0){	//Starting from scratch
			__locale_global_classic.locImp = new locale::localeImplementation;
			__locale_global_classic.lName = "C";

			//Assign facets?

			__locale_global_classic.locImp->reserveFacets(locale::id::max_index);

			__locale_global_classic.locImp->facets[__facet_num_put_classic_implementation.id.index] 
				= &__facet_num_put_classic_implementation;
			__locale_global_classic.locImp->facets[__facet_ctype_classic_implementation.id.index] 
				= &__facet_ctype_classic_implementation;

		}
		return __locale_global_classic;
	}

	//Locale localeImplementation

	locale::localeImplementation::localeImplementation() : references(1), facetCount(DEFAULT_ALLOC_UNITS), facets(0){
//		references = 1;
//		facetCount = DEFAULT_ALLOC_UNITS;
		facets = new facet*[facetCount];
		for(size_t i =0; i < facetCount;i++){
			facets[i] = 0;
		}
	}

	locale::localeImplementation::localeImplementation(const localeImplementation & copyFrom) :
		references(1), facetCount(copyFrom.facetCount), facets(0)
	{
//		facetCount = copyFrom.facetCount;
		facets = new facet*[facetCount];
//		references = 1;
		for(size_t i =0; i<facetCount;i++){
			facets[i] = copyFrom.facets[i];
			facets[i]->references++;
		}
	}

	locale::localeImplementation::~localeImplementation(){
		for(size_t i =0; i < facetCount;i++){
			if(facets[i] !=0){
				// If we are the only refernce to a facet, delete it
				if(facets[i]->references == 1){
					delete facets[i];
					facets[i] = 0;
				}else{	//Decrease reference count
					facets[i]->references--;
				}
			}
		}
		delete facets;
	}

	locale::localeImplementation & locale::localeImplementation::operator=(const locale::localeImplementation & other){
		if(this == &other){
			return *this;
		}
		//Destroy all of the existing references in the localeImplemanetion
		//Copied from destructor above
		for(size_t i =0; i < facetCount;i++){
			if(facets[i] !=0){
				// If we are the only refernce to a facet, delete it
				if(facets[i]->references == 1){
					delete facets[i];
					facets[i] = 0;
				}else{	//Decrease reference count
					facets[i]->references--;
				}
			}
		}
		delete facets;

		//Call constructor code
		facetCount = other.facetCount;
		facets = new facet*[facetCount];
		references = 1;
		for(size_t i =0; i<facetCount;i++){
			facets[i] = other.facets[i];
			facets[i]->references++;
		}
		return *this;
	}

	void locale::localeImplementation::reserveFacets(size_t numFacets){
		if(facetCount <= numFacets ){
			facet ** temp = new facet*[numFacets+1];
			for(size_t i =0; i<facetCount;i++){
				temp[i] = facets[i];
			}
			for(size_t i=facetCount;i<numFacets;i++){
				temp[i]=0;
			}
			delete [] facets;
			facets = temp;
			facetCount = numFacets;
		}
	}


	//locale::id object

	locale::id::id(){
		++max_index;
		index = max_index;
	}


	//Facet object

	locale::facet::facet(size_t t) : manager(t), references(0), c(none){
//		manager = t;
//		references = 0;
		return;
	}

	locale::facet::~facet(){
		return;
	}


	//Ctype information

	//template <> class ctype<char> : public locale::facet, public ctype_base

	ctype<char>::ctype(size_t refs) : facet(refs){
		references = 1;
		c = locale::ctype;
		return;
	}


	bool ctype<char>::is(mask m, char c) const{
		return do_is(m,c);
	}
	const char* ctype<char>::is(const char* low, const char* high, mask* vec) const{
		return do_is(low, high, vec);
	}
	const char* ctype<char>::scan_is(mask m, const char* low, const char* high) const{
		return do_scan_is(m, low, high);
	}
	const char* ctype<char>::scan_not(mask m, const char* low, const char* high) const{
		return do_scan_not(m, low, high);
	}
	char ctype<char>::toupper(char c) const{
		return do_toupper(c);
	}
	const char* ctype<char>::toupper(char* low, const char* high) const{
		return do_toupper(low, high);
	}
	char ctype<char>::tolower(char c) const{
		return do_tolower(c);
	}
	const char* ctype<char>::tolower(char* low, const char* high) const{
		return do_tolower(low, high);
	}
	char ctype<char>::widen(char c) const{
		return do_widen(c);
	}
	const char* ctype<char>::widen(const char* low, const char* high, char* to) const{
		return do_widen(low, high, to);
	}
	char ctype<char>::narrow(char c, char dfault) const{
		return do_narrow(c, dfault);
	}
	const char* ctype<char>::narrow(const char* low, const char* high, char dfault, char* to) const{
		return do_narrow(low, high, dfault, to);
	}

	ctype<char>::~ctype(){
		return;
	}


	bool ctype<char>::do_is(mask m, char c) const{
		//Check each datatype.  If we want that datatype and the character passed 
		//doesn't meet the requirements then we return false
		if(m & space && !isspace(c)){
			return false;
		}
		if(m & print && !isprint(c)){
			return false;
		}
		if(m & cntrl && !iscntrl(c)){
			return false;
		}
		if(m & upper && !isupper(c)){
			return false;
		}
		if(m & lower && !islower(c)){
			return false;
		}
		if(m & alpha && !isalpha(c)){
			return false;
		}
		if(m & digit && !isdigit(c)){
			return false;
		}
		if(m & punct && !ispunct(c)){
			return false;
		}
		if(m & xdigit && !isxdigit(c)){
			return false;
		}
		return true;
	}

	const char* ctype<char>::do_is(const char* low, const char* high, mask* vec) const{
		mask M;
		for(int i = 0; high - low; i++){
			M = static_cast<mask>(upper & lower);		//Clear
			if(isspace(low[i])){
				M = static_cast<mask>( M | space);
			}
			if(isprint(low[i])){
				M = static_cast<mask>( M | print);
			}
			if(iscntrl(low[i])){
				M = static_cast<mask>( M | cntrl);
			}
			if(isupper(low[i])){
				M = static_cast<mask>( M | upper);
			}
			if(islower(low[i])){
				M = static_cast<mask>( M | lower);
			}
			if(isalpha(low[i])){
				M = static_cast<mask>( M | alpha);
			}
			if(isdigit(low[i])){
				M = static_cast<mask>( M | digit);
			}
			if(ispunct(low[i])){
				M = static_cast<mask>( M | punct);
			}
			if(isxdigit(low[i])){
				M = static_cast<mask>( M | xdigit);
			}
			vec[i] = M;
		}
		return high;
	}
	const char* ctype<char>::do_scan_is(mask m, const char* low, const char* high) const{
		for(int i=0;i<high-low;i++){
			if(do_is(m, low[i])){
				return low + i;
			}
		}
		return high;
	}
	const char* ctype<char>::do_scan_not(mask m, const char* low, const char* high) const{
		for(int i=0;i<high-low;i++){
			if(!do_is(m, low[i])){
				return low+i;
			}
		}
		return high;
	}
	char ctype<char>::do_toupper(char c) const{
		return toupper(c);
	}
	const char* ctype<char>::do_toupper(char* low, const char* high) const{
		for(int i = 0; i < high-low; i++){
			low[i] = do_toupper(low[i]);	
		}
		return high;
	}
	char ctype<char>::do_tolower(char c) const{
		return tolower(c);
	}
	const char* ctype<char>::do_tolower(char* low, const char* high) const{
		for(int i = 0; i < high-low; i++){
			low[i]= do_tolower(low[i]);
		}
		return high;
	}

	//FIXME - I have no idea what these functions are supposed to do...
	char ctype<char>::do_widen(char c) const{
		return c;
	}
	const char* ctype<char>::do_widen(const char* low, const char* high, char* dest) const{
		for(int i=0 ; i<high-low; i++){
			dest[i] = low[i];
		}
		return dest;
	}
	char ctype<char>::do_narrow(char c, char dfault) const{
		char d;
		d = dfault;
		return c;
	}
	const char* ctype<char>::do_narrow(const char* low, const char* high, char dfault, char* dest) const{
		char d;
		d = dfault;
		for(int i=0 ; i<high-low; i++){
			dest[i] = low[i];
		}
		return dest;
	}


	//ctype_byname

	ctype_byname<char>::ctype_byname(const char* name, size_t refs) : ctype<char>(refs), locName(name){
//		locName = name;
		return;
	}

	ctype_byname<char>::~ctype_byname(){
		return;
	}

	char ctype_byname<char>::do_toupper(char c) const{
		return toupper(c);
	}
	const char* ctype_byname<char>::do_toupper(char* low, const char* high) const{
		for(int i =0; i < high-low; i++){
			low[i] = toupper(low[i]);
		}
		return high;
	}
	char ctype_byname<char>::do_tolower(char c) const{
		return tolower(c);
	}
	const char* ctype_byname<char>::do_tolower(char* low, const char* high) const{
		for(int i =0; i < high-low;i++){
			low[i] = toupper(low[i]);
		}
		return high;
	}
	char ctype_byname<char>::do_widen(char c) const{
		return c;
	}
	const char* ctype_byname<char>::do_widen(char* low, const char* high, char* to) const{
		for(int i =0; i < high-low;i++){
			to[i] = low[i];
		}
		return to;
	}
	char ctype_byname<char>::do_narrow(char c, char dfault) const{
		char d;
		d = dfault;
		return c;
	}
	const char* ctype_byname<char>::do_narrow(const char* low, const char* high, char dfault, char* dest) const{
		char d;
		d = dfault;
		for(int i = 0; i < high-low; i++){
			dest[i] = low[i];
		}
		return dest;
	}

};
