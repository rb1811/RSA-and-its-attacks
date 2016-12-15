#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <iostream>
#include <math.h>
#include <gmpxx.h>
//#include "initialize.h"
using namespace std;

class RSA {

	public:
	mpz_t prime_P,prime_Q,zero,temp,cipher_text,plain_text,message,positive_1,n_value,z_value,d_value,e_value,negative_1;
	unsigned long int seed;
    gmp_randstate_t r_state;
	int width_of_p;
	int width_of_q;
	int check_prime;
	void calculate_P_and_Q();
	void calculate_N_and_Z();
	void calculate_Public_Key();
	void calculate_Private_Key();
	void Encrypt();
	void Decrypt();
	RSA();
	
};

RSA::RSA()
{
	width_of_p = 13;
	width_of_q = 7;
	int check_prime;
	char str1[] = "1";
	char str0[] = "0";
	char strn[] = "-1";
	
	gmp_randclass w(gmp_randinit_default);
	
	mpz_init(prime_P);
	mpz_init(prime_Q);
	mpz_init(n_value);
	mpz_init(z_value);
	mpz_init(d_value);
	mpz_init(e_value);
	mpz_init(temp);
	mpz_init(cipher_text);
	mpz_init(plain_text);
	mpz_init(message);
	mpz_init (positive_1);
	mpz_init (negative_1);
	mpz_init(zero);
	
    seed = time(NULL);

	gmp_randinit_default (r_state);
    gmp_randseed_ui(r_state, seed);
    mpz_set_str ( positive_1, str1, 10 );
    mpz_set_str ( zero, str0, 10 );
	mpz_set_str ( negative_1, strn, 10 );
}
	
void RSA::calculate_P_and_Q()
{
	mpz_urandomb(prime_P,r_state,width_of_p);

	check_prime = mpz_probab_prime_p ( prime_P, check_prime );
	while(check_prime==0)
	{
	   mpz_add(prime_P,prime_P,positive_1);
	   check_prime = mpz_probab_prime_p ( prime_P, check_prime );
	}
	check_prime = mpz_probab_prime_p ( prime_P, check_prime );

    mpz_urandomb(prime_Q,r_state,width_of_q);

	check_prime = mpz_probab_prime_p ( prime_Q, check_prime );
	while(check_prime==0)
	{
	   mpz_add(prime_Q,prime_Q,positive_1);
	   check_prime = mpz_probab_prime_p ( prime_Q, check_prime );
	}
	
	check_prime = mpz_probab_prime_p ( prime_Q, check_prime );

	
}

void RSA::calculate_N_and_Z()
{
	mpz_mul(n_value,prime_P,prime_Q);
	
    mpz_sub(prime_P, prime_P, positive_1);
	mpz_sub(prime_Q, prime_Q, positive_1);
	mpz_mul(z_value,prime_P,prime_Q);
	
	
}


void RSA::calculate_Public_Key()
{
	  do
	  {
		   mpz_urandomb(temp,r_state,width_of_p);
		   mpz_nextprime(e_value,temp);
	  }while(mpz_cmp(e_value,z_value)> 0);
     
	 
}

void RSA::calculate_Private_Key()

{
	 
	 mpz_invert(d_value, e_value, z_value);
	 
	
	
}


void RSA::Encrypt()
{
	// Cipher text generation.
	mpz_powm(cipher_text, message, e_value, n_value);
	cout << "Cipher Text: " <<cipher_text<<endl;			
}

void RSA::Decrypt()
{
		// Plain text generation.
		mpz_powm(plain_text, cipher_text, d_value, n_value);
		cout<< "Decrypted Text: " <<plain_text<<endl;
}



int main()
{	

    RSA r1,r2;
	mpz_t temp;
	mpz_t x1,x2,y,cx,cy;
	
   	 mpz_init(x1);
	 mpz_init(x2);
	 mpz_init(y);
	 mpz_init(cx);
	 mpz_init(cy);
	 
	mpz_init(temp);
	
	
    r1.calculate_P_and_Q();
	r1.calculate_N_and_Z();
	r1.calculate_Public_Key();
	r1.calculate_Private_Key();
	
	cout<<"The value of n:" <<r1.n_value<<endl;
	cout<<"E1 value:"<<r1.e_value<<endl;  
	
	
	//select the message
	mpz_set_ui(r1.message,12345);	
	mpz_set_ui(r2.message,12345);
	
	
	mpz_set(r2.z_value,r1.z_value);
    mpz_set(r2.n_value,r1.n_value);
    
	r2.calculate_Private_Key();
	do {
		r2.calculate_Public_Key();
		mpz_gcd (temp, r1.e_value, r2.e_value);
	}while(mpz_cmp(temp,r1.positive_1)!=0);
	
	cout<<"E2 value:"<<r2.e_value<<endl;  
	cout<<"GCD value:"<<temp<<endl;
	
	r1.Encrypt();
	r2.Encrypt();
	
	
	 mpz_invert(x1,r1.e_value,r2.e_value);
	 mpz_mul(temp,x1,r1.e_value);
	 mpz_sub(temp,r1.positive_1,temp);
     mpz_mul(temp,temp,r2.negative_1);
	 
	 mpz_cdiv_q(x2,temp,r2.e_value);
	
	 
	 mpz_invert(y,r2.cipher_text,r1.n_value);
	 mpz_powm(cx, r1.cipher_text,x1, r1.n_value);
	 mpz_powm(cy, y,x2, r1.n_value);
	 mpz_mul(temp,cx,cy);
	 mpz_mod(temp,temp,r1.n_value);
	 cout<<"Actual Message:"<<temp<<endl;
}


