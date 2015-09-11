/* ----------------------------------------------------------------------------
 * Copyright &copy; 2015 Thanh Phan <tphan2650@csu.fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * 
 *	--References--
 *	Sieve of Eratosethenes Algorithm from:
 *	http://www.quora.com/What-is-the-code-for-applying-sieve-of-eratosthenes-in
 *	-C-programming
 * ------------------------------------------------------------------------- */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::fstream;
using std::ios;
#include <math.h>

//Function Prototypes

//Find maximum unsigned integer within text file
int find_max(const char* infilename);

//Mark all prime indices in 'primes' as 'true'
void sieve(bool primes[], const int max);

//Read numbers from textfile, if they are prime, output them to a new text file 'primes'
int write_primes(bool primes[], const int max,
				 const char* infilename,
				 const char* outfilename);

//Read numbers from textfile, if they are composites, output them to a new text file 'composites'
int write_composites(bool primes[], const int max,
					 const char* infilename,
					 const char* outfilename);

int main ()
{
	
	int max = find_max("input.txt"); //Calls find_max function

	bool primes[max+1];
	
	sieve(primes,max+1); //Calls the sieve function

	int ret; //Stores return values, checks for error code

	ret =write_primes(primes,max+1, "input.txt","primes.txt");
	if (ret == -1) 
	{	cout << "ERROR in 'write_primes()" << endl;
		return 1; //error
	}

	ret = write_composites(primes,max+1, "input.txt","composites.txt");
	if (ret == -1) 
	{	cout << "ERROR in 'write_primes()" << endl;
		return 1; //error
	}

	return 0; //success
}

int find_max(const char* infilename)
{
	fstream file;
	int num[8];

	file.open(infilename,ios::in);

	for (int i=0;i<8;i++)
	{
		file >> num[i];
	}

	file.close();

	int max = num[0];

	//Find the max value within the file
	for (int i=0;i<8;i++)
	{
		if (num[i]>max) max = num[i];
	}

	return max;
}

void sieve(bool primes[], const int max)
{

	for (int i=0;i<max;i++)
	{
		primes[i]=true;
	}
	primes[0]=primes[1]=false;

	for (int i=2;i<sqrt(max);i++)
	{
		for (int j=i*i;j<max;j+=i)
		{
			primes[j]=false;
		}
	}
}

int write_primes(bool primes[], const int max,
				 const char* infilename,
				 const char* outfilename)
{

	int temp=0;

	fstream infile,outfile;

	infile.open(infilename,ios::in);

	outfile.open(outfilename,ios::out);

	infile >> temp;
	
	for (int i=0;!infile.eof();i++)
	{
		if (primes[temp]==true) 
		{
			outfile << temp << "\n";
		}
		infile >> temp;
	}

	return 0;
}

int write_composites(bool primes[], const int max,
					 const char* infilename,
					 const char* outfilename)
{
	int temp=0;

	fstream infile,outfile;

	infile.open(infilename,ios::in);

	outfile.open(outfilename,ios::out);

	infile >> temp;
	
	for (int i=0;!infile.eof();i++)
	{
		if (primes[temp]==false) 
		{
			outfile << temp << "\n";
		}
		infile >> temp;
	}

	return 0;
} 
