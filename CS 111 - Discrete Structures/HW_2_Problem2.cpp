//Tejas Shah SID: 862237516
//Daniel Castellanos SID: 862238994

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

bool isPrime(int num) {
  if (num == 1 || num == 0 || num < 0) { //1 and 0 arent prime
    return false;
  }
  for (unsigned i = 2; i <= num/2; ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true; //passed checker loop without returning, is a prime
}

/*
int findD(int phi, int e) {
  int temp = phi;
  int d = 0;

  while(d == 0) {
    if (temp % e == (e-1)) {
      d = ((temp + 1)/e);
    }
    else {
      temp += temp;
    }
  }

  return d;
}
*/

void squareMethod(int base, int power, int modu, int & output, int carryOver) {
  if (power < 1) {
    std::cout << "error";
  }
  if (power == 1) { //base case, last possible even
    output = (carryOver * base) % modu;
    return;
  }
  if (power == 2) { //base case, last possible even
    output = (carryOver * base * base) % modu;
    return;
  }
  if (power == 3) { //base case, last possible odd
    output = (carryOver * base * base * base) % modu;
    return;
  }

  int temp = 0;
  if (power % 2 == 0) { //even
    power = power/2;
    temp = (base * base) % modu; //ex: (832^2 rem901) = 256
    base = temp; //new base for next problem, will be in format 256^166
    //debugRep(base, power, modu, output, carryOver);
    squareMethod(base, power, modu, output, carryOver);
  }
  else { //odd
    power = (power - 1)/2; //ex: 333 -> 166
    temp = (base * base) % modu; //ex: (832^2 rem901) = 256
    if (carryOver == 0) {
      carryOver = base; //first time
    }
    else {
      carryOver = (carryOver * base) % modu; //ex: (832 * 256) rem 901, result is: 356 * 664^83
    }
    base = temp; //new base for next problem, will be in format 256^166

    //debugRep(base, power, modu, output, carryOver);
    squareMethod(base, power, modu, output, carryOver);
  }
}

int gcd(int x, int y)  {
   if (y == 0) {
    return x; 
   }
   else {
    return gcd(y, x % y);
   }
}

bool isPublicKeyValid(int p, int q, int e, int n, int phi) {
  if (p == q) {
    return false;
  }
  if (p == 1 || q == 1 || p == 0 || q == 0) {
    return false;
  }
  if (gcd(e, phi) != 1) { //coprime check
    return false;
  }

  return true;
}

int cCracker(int e, int n, int c) {
  //finds p & q
  int p = 0;
  int q = 0;
  int temp = 0;
  
  for (unsigned i = 3; i <= n/2; i = (i + 2)) { //i starts at 3 because if n is divisible by an even the resulting number can't be prime, increments by 2 to be odd
    if (isPrime(i)) {
      if (n % i == 0) { //possible p and q found
        temp = n / i; //the q
        if (isPrime(temp)) {
          p = i;
          q = temp;
          break;
        }
      }
    }
  }

  //finds phi
  int phi = 0;
  phi = (p - 1) * (q - 1);

  //checks if public key is valid
  if (!isPublicKeyValid(p, q, e, n, phi)) {
    std::cout << "Public key not valid!";
    return -1; //error code
  }

  //finds d
  int d = 0;
  for (int i = 1; i < phi; i++) {
        if (((e%phi) * (i%phi)) % phi == 1)
        {
            d = i;
        }
  }

  //finds M
  int M = -1;
  squareMethod(c, d, n, M, 0);
  return M;
}

void outputPQPhiD(int e, int n, int c) { //this program repeats the cCracker code without finding M to print output
  int p = 0;
  int q = 0;
  int temp = 0;
  
  for (unsigned i = 3; i <= n/2; i = (i + 2)) {
    if (isPrime(i)) {
      if (n % i == 0) {
        temp = n / i;
        if (isPrime(temp)) {
          p = i;
          q = temp;
          break;
        }
      }
    }
  }
  int phi = 0;
  phi = (p - 1) * (q - 1);
  int d = 0;
  for (int i = 1; i < phi; i++) {
        if (((e%phi) * (i%phi)) % phi == 1)
        {
            d = i;
        }
  }

  //outputs p, q, phi, and d
  std::cout << p << " " << q << " " << phi << " " << d << std::endl;
}

char messageToASCII(int mes) {
  if (mes >= 3 && mes <= 28) {
    return mes + 62; //corresponding letter
  }
  if (mes == 29) {
    return ' '; //space
  }
  if (mes == 30) {
    return '\"'; //quotes
  }
  if (mes == 31) {
    return '.'; //period
  }
  if (mes == 32) {
    return ','; //comma
  }
  if (mes == 33) {
    return '\''; //apostrophe
  }

  return '!'; //error
}

int main() {
  int e;
  int n;
  int mCount;

  std::cin >> e;
  std::cin >> n;
  std::cin >> mCount;

  std::vector<int> messages; //will hold proceeding integers
  int currM;

  if (mCount <= 0) { //check if mCount is valid
      std::cout << "error";
      return 0;
  }

  for (unsigned i = 0; i < mCount; ++i) {
    std::cin >> currM;
    messages.push_back(currM);
  }
  
  int c;
  int result;

  c = messages.at(0);
  result = cCracker(e, n, c);
  if (result == -1) {
    return 0;
  }
  outputPQPhiD(e, n, c);

  for (unsigned i = 0; i < messages.size(); ++i) {
    c = messages.at(i);
    result = cCracker(e, n, c); //integer result

    if (result >= 3 && result <= 33) { //output integer if not errornious, should reject errors before getting here
      std::cout << result; //integer
      if (i != messages.size() - 1) {
        std::cout << " ";
      }
    }
  }
  std::cout << std::endl;

  for (unsigned i = 0; i < messages.size(); ++i) {
    c = messages.at(i);
    result = cCracker(e, n, c); //integer result

    if (result >= 3 || result <= 33) { //output integer if not errornious, should reject errors before getting here
      std::cout << (messageToASCII(result)); //text
    }
  }
  
  return 0;
}