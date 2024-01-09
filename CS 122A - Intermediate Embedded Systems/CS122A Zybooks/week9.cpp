#include <stdio.h>
#include <math.h>


// the array that stores the square root of values
// TODO: fill in the ... with additional values, rounded to hundredths as shown. 
const float squareroot_table[17] = {0.00, 1.00, 1.41,1.73,2.00,2.24,2.45,2.65,2.83,3.00,3.16,3.32,3.46,3.61,3.74,3.87,4.00}; 

// function templates
float sqrt_lookup(int);

int main() {
  
   int input_value;
   
   scanf("%d", &input_value);
   printf("%.4f\n", sqrt_lookup(input_value)); // Don't change this; it outputs to four decimal places
   
   return 0;
}



float sqrt_lookup(int num)
{
  if(num <= 16)
  {
    return squareroot_table[num];
  }
  else
  {
    return sqrt(num);
  }
   
}
