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
	width_of_p = 1024;
	width_of_q = 1024;
	
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
	int check_prime=0;
	
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
	mpz_t p_temp,q_temp;
	mpz_init(p_temp);
	mpz_init(q_temp);
	mpz_set(p_temp,prime_P);
	mpz_set(q_temp,prime_Q);
	
	mpz_mul(n_value,p_temp,q_temp);
	
    mpz_sub(p_temp, p_temp, positive_1);
	mpz_sub(q_temp, q_temp, positive_1);
	mpz_mul(z_value,p_temp,q_temp);
	
	
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

    RSA *r1 = new RSA;
	
	
	do{
    r1->calculate_P_and_Q();
	}while(mpz_cmp(r1->prime_P,r1->prime_Q)==0);
	r1->calculate_N_and_Z();

	do{
	r1->calculate_Public_Key();
	}while(mpz_cmp_ui(r1->e_value,65537)<1);
	
	r1->calculate_Private_Key();
	
	cout<<"The value of prime_P:" <<r1->prime_P<<endl;
	cout<<"The value of prime_Q:" <<r1->prime_Q<<endl;
	cout<<"The value of n:" <<r1->n_value<<endl;
	cout<<"The value of Z:" <<r1->z_value<<endl;
	cout<<"E value:"<<r1->e_value<<endl;  
	cout<<"D value:"<<r1->d_value<<endl;
	
	//select the message
	mpz_set_ui(r1->message,12);	

	unsigned int m;
	cout<<"Enter message:";
	cin>>m;
	/*
	signed int m;
	cout<<"Enter message:";
	cin>>m;
	
	while(m<1){
	cout<<"Please enter postive number:";
	cin>>m;
	}
	*/
	mpz_set_ui(r1->message,m);
	
	r1->Encrypt();
	r1->Decrypt();
	
   delete r1;
}


