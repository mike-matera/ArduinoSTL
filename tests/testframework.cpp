#include "testframework.h"

namespace TestFramework{
	unsigned long int goodcount;
	unsigned long int badcount;
	unsigned long int totalcount;

	unsigned long int getTotalTests(){
		return totalcount;
	}
	unsigned long int getBadTests(){
		return badcount;
	}
	unsigned long int getGoodTests(){
		return goodcount;
	}

	void init(){
		totalcount = 0;
		badcount = 0;
		goodcount = 0;
	}

	void results(){
		printf("\n");

		for(int i = 0; i < 30; ++i){
			printf("-");
		}

		printf("\nRan %lu tests\n", totalcount);
		if(goodcount == totalcount && 0 == badcount){
			printf("\nOK\n");
		}else{
			printf("\nPassed: %lu\nFailed: %lu\n", goodcount, badcount);
		}
	}


}
