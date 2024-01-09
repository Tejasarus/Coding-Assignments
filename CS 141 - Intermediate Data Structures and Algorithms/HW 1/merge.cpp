#include <iostream>
using namespace std;

int candies = 0;

void print(int* a, int n)
{
    cout << "array: ";
    for(int i = 0; i < n; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int get_highest(int *scores, int n)
{
    int highest = 0;
    for(int i = 0; i < n; ++i)
    {
        if(highest < scores[i])
        {
            highest = scores[i];
        }   
    }
    return highest;
}

int* merge(int* A, int na, int* B, int nb)
{
    int* C = new int[na + nb];
    int p1 = 0, p2 = 0, p3 = 0;
    while((p1 < na) && (p2 < nb))
    {
        
        if(A[p1] < B[p2])
        {
            C[p3] = A[p1];
            ++p3;
            ++p1;
        }
        else
        {
            C[p3] = B[p2];
            ++p3;
            ++p2;
        }
    }
    
    while(p1 <= na)
    {
        C[++p3] = A[p1];
        ++p1;
    }
    while(p2 <= nb)
    {
        C[++p3] = B[p2];
        ++p2;
    }
    
    //print(C,p3);
    return C;
}

void mergesort(int *A, int n)
{
    if(n <=1)
    {
        return;
    }
    else
    {
        mergesort(A, n/2);
        mergesort(A+ (n/2), n-(n/2));
        A = merge(A, n/2, A+(n/2), n-(n/2));
        
    }
}

int main()
{
    int n, input;
    int *a = NULL;
    cin >> n;

    a = new int[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> input;
        a[i] = input;
    }

    mergesort(a, n);
    cout << candies << endl;

    for(int i = 0; i < n; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    delete [] a;
    a = NULL;
}
