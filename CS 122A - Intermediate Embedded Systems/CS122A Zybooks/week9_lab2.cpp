#include <stdio.h>
#include <math.h>


// function templates
float generate_declaration(int);

int main() {
  
   int input_value;
   
   scanf("%d", &input_value);
   generate_declaration(input_value);
   
   return 0;
}



float generate_declaration(int num)
{
   /* TODO: complete the implementation of this function
     which given number num, prints the squre root 
     lookup table declaration for numbers between 0 and num
     (num included)*/
   
   printf("const float squareroot_table[%d] = {", num+1);
   
  for(int i = 0; i <= num; ++i)
  {
    printf(sqrt(i));
    if(i != num)
    {
        printf(", ");
    }
  }
   printf("};");
}
