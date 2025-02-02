#include <iostream>
using namespace std;
int main()
{
  int temp,num;
  cin >> temp;
  for(int i = 1 ; i < temp ; i++)
  {
    for(int j = 1 ; j <= i ; j++)
    {
        num = i*j;
        int num_s = num / temp;
        int num_g = num % temp;

        if( i >= 10 )
          cout << char( 65 + i - 10 );
        else
          cout<<i;
        cout<<"*";

        if( j >= 10 )
          cout << char( 65 + j - 10 );
        else
          cout<<j;
        cout<<"=";

        if(num_s != 0)
          if( num_s - 10 >= 0)
            cout<< char( 65 + num_s - 10);
          else
            cout<< num_s;
        
        if( num_g - 10 >= 0)
          cout<< char( 65 + num_g - 10);
        else
          cout<< num_g;  

          cout<<" ";
    }
    cout << endl;
  }
  return 0;
}
