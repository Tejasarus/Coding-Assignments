#include <iostream>
#include <list>
#include <math.h>
#include <cmath>
#include <string>
using namespace std;

int gcd(int x, int y) 
{
   if (y == 0)
   {
        return x; 
   }
   else
   {
    return gcd(y, x % y);
   }
   
}
bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
        
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
             return false;
        }
           
    }
    return true;
}
void RSA(int e, int n, int m)
{
    int q;
    int p;
    int n_temp = n;

    //factorize n
   int temp1;
   for (unsigned i = 3; i <= n/2; i = (i + 2)) { //i starts at 3 because if n is divisible by an even the resulting number can't be prime, increments by 2 to be odd
    if (isPrime(i)) {
      if (n % i == 0) { //possible p and q found
        temp1 = n / i; //the q
        if (isPrime(temp1)) {
          p = i;
          q = temp1;
          break;
        }
      }
    }
  }
    //Computer Eulers Totient function
    int totient;

    totient = (p-1) * (q-1);


    //calculate decryption key
    int d;
    for (int i = 1; i < totient; i++)
    {
        if (((e%totient) * (i%totient)) % totient == 1)
        {
            d = i;
        }
    }
    //check if the RSA is valid

    //check if p or q are prime
    if(!isPrime(p) || !isPrime(q))
    {
        cout << "Public key not valid!";
        return;
    }

    //check if coprime
    if(gcd(e, totient) != 1)
    {
        cout << "Public key not valid!";
                return;
    }

    //check if p = q
    if(p == q)
    {
        cout << "Public key not valid!";
        return;
    }

    //take in m inputs, decrypt the message
    long long input;
    list<long long> msgs;
    
    for(int i = 0; i < m; ++i)
    {
        cin >> input;

        long long t = 1;
        for(int k = 0; k < d; ++k)
        {
            t = (t*input)%n;
        }
        msgs.push_back(t);
    }
    
    //output everything

    std::cout << p << " " << q << " " << totient << " " << d << endl;
    //print out decoded message the list
    for (auto const &i: msgs) 
    {
        std::cout << i << " ";
    }

    std::cout << endl;
    //convert decrypted numbers to letters
    char characters[33] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' ','\"', '\"',',','\''};
    int index;
    for(int i = 0; i < m; ++i)
    {
        index = msgs.front();
        std::cout << characters[index-3];
        msgs.pop_front();
    }

    return;
}

int main()
{
    int e, n, m;
    cin >> e >> n;
    cin >> m;
    RSA(e,n,m);
}

