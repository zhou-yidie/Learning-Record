#include <bits/stdc++.h>
#include <iostream>
#include <set>

using namespace std;

set<int> seen;

int main()
{
    seen.insert(1);
    seen.insert(2);
    seen.insert(3);
    seen.insert(5);
    seen.insert(8);

    set<int>::iterator it=seen.begin();    
    for(int i=0;i<1000;i++)
    {
        int x=*it;
        seen.insert(3*x+2);
        seen.insert(5*x+3);
        seen.insert(8*x+5);
        it++;
    }
    int i=0;
    for(it=seen.begin();it!=seen.end();it++)
    {
        i++;
        if(i==2020)
            cout<<*it<<endl;
    }
    cout << "\n\n\n";
    return 0;
}
