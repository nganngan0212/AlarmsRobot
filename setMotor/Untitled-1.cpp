#include <iostream>
#include <string.h>

using namespace std;

bool check(string s, int hour, int minutes)
{
    int len = s.length();
    if(len != 5)
    {
        cout<< "Error!";
        return false;
    }
    else{
        int h = s[0]*10 + s[1];
        int m = s[3]*10 + s[4];
        if(h == hour && m == minutes)
        {
            return  true;
        } 
        else{
            return false;
        }
    }
}
int main()
{
    string S;
    cin>> S;
    int hour, minutes;
    cin>> hour >> minutes;
    bool ans = check(S, hour, minutes);
    cout<< ans;
    return 0;
}