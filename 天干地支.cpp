#include <iostream>
using namespace std;

int year;

int main()
{
    cin >> year;
    string tiangan[10] = {"geng", "xin", "ren", "gui", "jia", "yi" , "bing", "ding", "wu", "ji"};
    string dizhi[12] = {"shen", "you", "xu", "hai", "zi", "chou", "yin", "mou", "chen", "si", "wu", "wei"};

    cout << tiangan[year % 10] << dizhi[year % 12] << endl;
}
