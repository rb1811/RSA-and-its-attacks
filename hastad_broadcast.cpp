#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <typeinfo>
#include <gmpxx.h>
using namespace std;



int main()
{	unsigned long int cmp =1;
	int x;
	gmp_randclass w(gmp_randinit_default);
	mpz_class EncM,EncM2,EncM3,DecM,DecM2,DecM3,m=10;
	mpz_t large,temp,n,nn2,nn3,z,z2,z3,dd,dd2,dd3,ee,ee2,ee3,i,j,p,p2,p3,q,q2,q3,zero,test,pp1,pp2,pp3,prod,inv1,inv2,inv3;
	int width_of_p = 8;
	int width_of_q = 4;
	vector<mpz_t> e,d;
	mpz_init(p);
	mpz_init(q);
	mpz_init(n);
	mpz_init(z);
	mpz_init(i);
	mpz_init(j);
	mpz_init(dd);
	mpz_init(ee);
	mpz_init(temp);
	mpz_init(large);
	mpz_init(zero);
	mpz_init(test);
	
	mpz_init(p2);
	mpz_init(q2);
	mpz_init(nn2);
	mpz_init(z2);
	mpz_init(dd2);
	mpz_init(ee2);
	
	
	mpz_init(p3);
	mpz_init(q3);
	mpz_init(nn3);
	mpz_init(z3);
	mpz_init(dd3);
	mpz_init(ee3);
	

	mpz_init(pp1);
	mpz_init(pp2);
	mpz_init(pp3);
	mpz_init(prod);
	mpz_init(inv1);
	mpz_init(inv2);
	mpz_init(inv3);
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
/* p and q calucation        -  start        */

    mpz_t p1;
	mpz_t q1;
	int check_prime;
	mpz_t n1;
	char str[] = "1";
	unsigned long int seed;
    gmp_randstate_t r_state;
	
	   mpz_init ( n1 );
	   mpz_set_str ( n1, str, 10 );

	mpz_t n2;
	char strn[] = "-1";
	   mpz_init ( n2 );
	   mpz_set_str ( n2, strn, 10 );
	 char str0[] = "0";
	 mpz_init ( zero );
	 mpz_set_str ( zero, str0, 10 );
	   
    seed = time(NULL);

    gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);

// calculating - p

    mpz_init(p1);
   
    mpz_urandomb(p1,r_state,width_of_p);

	check_prime = mpz_probab_prime_p ( p1, check_prime );
	while(check_prime==0)
	{
	   mpz_add(p1,p1,n1);
	   check_prime = mpz_probab_prime_p ( p1, check_prime );
	}
	check_prime = mpz_probab_prime_p ( p1, check_prime );

   
    mpz_init(q1);
   
    mpz_urandomb(q1,r_state,width_of_q);

	check_prime = mpz_probab_prime_p ( q1, check_prime );
	while(check_prime==0)
	{
	   mpz_add(q1,q1,n1);
	   check_prime = mpz_probab_prime_p ( q1, check_prime );
	}
	
	check_prime = mpz_probab_prime_p ( q1, check_prime );

	
    
/* p and q calculation       -  end          */	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	cout<<"The value of m:" <<m<<endl;
	
	mpz_set_ui(p,97);
    mpz_set_ui(q,23);
	
	mpz_mul(n,p,q);
	cout<<"The value of n:" <<n<<endl;
    mpz_sub(p, p, n1);
	mpz_sub(q, q, n1);
	mpz_mul(z,p,q);
	mpz_set_ui(ee,3);
	
			mpz_powm(EncM.get_mpz_t(), m.get_mpz_t(), ee, n);
			cout << "Cipher text 1: " <<EncM<<endl;
	
			
// Encryption 2

   mpz_urandomb(p1,r_state,width_of_p);

	check_prime = mpz_probab_prime_p ( p1, check_prime );
	while(check_prime==0)
	{
	   mpz_add(p1,p1,n1);
	   check_prime = mpz_probab_prime_p ( p1, check_prime );
	}
	check_prime = mpz_probab_prime_p ( p1, check_prime );

// caluculating - q	
    mpz_urandomb(q1,r_state,width_of_q);

	check_prime = mpz_probab_prime_p ( q1, check_prime );
	while(check_prime==0)
	{
	   mpz_add(q1,q1,n1);
	   check_prime = mpz_probab_prime_p ( q1, check_prime );
	}
	
	check_prime = mpz_probab_prime_p ( q1, check_prime );

	
    
/* p and q calculation       -  end          */	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	
	mpz_set(p2,p1);
    mpz_set(q2,q1);
	
	mpz_mul(nn2,p2,q2);
    mpz_sub(p2, p2, n1);
	mpz_sub(q2, q2, n1);
	mpz_mul(z2,p2,q2);
	
   mpz_set_ui(ee2,3);
	
			mpz_powm(EncM2.get_mpz_t(), m.get_mpz_t(), ee2, nn2);
			cout << "Cipher text 2: " <<EncM2<<endl;
			
	mpz_set_ui(p3,461);
    mpz_set_ui(q3,137);
	mpz_mul(nn3,p3,q3);
    mpz_sub(p3, p3, n1);
	mpz_sub(q3, q3, n1);
	mpz_mul(z3,p3,q3);
	mpz_set_ui(ee3,3);
	
			mpz_powm(EncM3.get_mpz_t(), m.get_mpz_t(), ee3, nn3);
			cout << "Cipher text 3: " <<EncM3<<endl;
	
     mpz_mul(prod,n,nn2);
	 mpz_mul(prod,prod,nn3);
	
	 mpz_div(pp1,prod,n);
	 mpz_div(pp2,prod,nn2);
	 mpz_div(pp3,prod,nn3);
	 
	 mpz_invert(inv1,pp1,n);
	 mpz_invert(inv2,pp2,nn2);
	 mpz_invert(inv3,pp3,nn3);
	 
	 mpz_mul(inv1,inv1,pp1);
	 mpz_mul(inv1,inv1,EncM.get_mpz_t());

     mpz_mul(inv2,inv2,pp2);
	 mpz_mul(inv2,inv2,EncM2.get_mpz_t());

     mpz_mul(inv3,inv3,pp3);
	 mpz_mul(inv3,inv3,EncM3.get_mpz_t());
	 
	 mpz_add(inv1,inv1,inv2);
	 mpz_add(inv1,inv1,inv3);
	 
	 mpz_mod(inv1,inv1,prod);
	 mpz_root(inv1,inv1,3);
	 cout<<inv1<<" : is the message broken"<<endl;
}
