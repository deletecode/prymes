#include <iostream>
//#include <vector>
#include <cstring>
//#include "string.h"
#include <algorithm>
using namespace std;

// Copyright Techman88 5/21/2021+


class PrimeFac {
	public:
	long long fact, power;
};

const int MAX_PRIMEFACS=500;
class PrimeFacs {
	public:
	long num;
	PrimeFac facs[MAX_PRIMEFACS];
	PrimeFacs () {
		num=0;
		memset(facs, -64857832, sizeof(facs));
	}
	void Add(long long nfactor, long long npower) {
		PrimeFac &n=facs[num++];
		n.fact=nfactor;
		n.power=npower;
	}
	auto operator[] (int i) {
		return facs[i];
	}
	
#ifdef DO_ITERATORS
	// i didn't feel like doing this today lol.
	// not a fan of the "standard" library.
	class iterator {
	public:
		iterator() {
			cur=-1;
			facs=0;
		}
		iterator(int cur,PrimeFacs *t) {
			iterator ret;
			ret.cur=cur;
			ret.facs=t;
		}
		int cur;
		PrimeFacs *facs;
		int operator++() {
			cur++;
			return cur;
		}
		/*PrimeFac operator* const () {
			return facs->facs[cur];
		}*/
	};
	iterator begin() {
		return iterator(0,this);
	}
	iterator end() {
		return iterator(num,this);
	}
#endif
	
};


PrimeFacs factorize2(long n) {
	
		
	// Based on rosettacode impl.
    PrimeFacs fs;
	if(n==0)
		return fs;
    int cnt = 0;
	
    for (;n%2==0; n/=2) cnt++;    // optimized by compiler
    if (cnt > 0)
		fs.Add(2,cnt);

    for (long i=3; i*i<=n; i+=2) {
        cnt = 0;
        for (;n%i==0; n/=i) cnt++;
        if (cnt>0)
			fs.Add(i,cnt);
    }
    if (n>1)
		fs.Add(n,1);
    return fs;
}

long long min_factor(long long n) {
	return factorize2(n)[0].fact;
}

int main() {
	cout << "Hello, world!" << endl;
	for(long long i=0;i<100;i++) {
		//printf("%lld: %lld %lld | ", i, factorize2(i).num, min_factor(i));
		printf("%lld: ", i);
		auto fs=factorize2(i);
		bool firstfactor=true;
		for(int i=0;i<fs.num;i++) {
			auto fp=fs[i];
			 if(true) {
				if(!firstfactor)
					cout << " * ";
				
				cout<<fp.fact;
				if(fp.power!=1)
					cout << "^" << fp.power <<"";
			} else {
				if(!firstfactor)
					cout << " ";
				
				cout<<fp.power;
			}
			firstfactor=false;
		}
		printf("\n");
	}
	
	int cnt=0;
	printf("Counting primes...\n");
	for(long long i=1;i<1000000;i++) {
		if((i%100000)==0)
			printf("%d\n",i);
		if(factorize2(i).num==1)
			cnt++;
	}
	
	printf("%d",cnt);
	return 0;
}
