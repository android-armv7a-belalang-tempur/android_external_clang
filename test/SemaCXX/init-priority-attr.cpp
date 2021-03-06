// RUN: %clang_cc1 -fsyntax-only -verify %s

class Two {
private:
    int i, j, k;
public:
    static int count;
    Two( int ii, int jj ) { i = ii; j = jj; k = count++; };
    Two( void )           { i =  0; j =  0; k = count++; };
    int eye( void ) { return i; };
    int jay( void ) { return j; };
    int kay( void ) { return k; };
};

extern Two foo;
extern Two goo;
extern Two coo[];
extern Two koo[];

Two foo __attribute__((init_priority(101))) ( 5, 6 );

Two goo __attribute__((init_priority(2,3))) ( 5, 6 ); // expected-error {{attribute takes one argument}}

Two coo[2]  __attribute__((init_priority(3)));	// expected-error {{init_priority attribute requires integer constant between 101 and 65535 inclusive}}

Two koo[4]  __attribute__((init_priority(1.13))); // expected-error {{'init_priority' attribute requires integer constant}}


Two func()  __attribute__((init_priority(1001))); // expected-error {{can only use 'init_priority' attribute on file-scope definitions of objects of class type}}

int i  __attribute__((init_priority(1001))); // expected-error {{can only use 'init_priority' attribute on file-scope definitions of objects of class type}}

int main() {
	Two foo __attribute__((init_priority(1001)));	// expected-error {{can only use 'init_priority' attribute on file-scope definitions of objects of class type}}
}

