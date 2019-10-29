#include <iostream>
#include <string.h>

using namespace std;

bool checkTime(string msg, int hour, int minutes)
{
    int len = msg.length();
    if(len != 5) return false;
    else
    {
        int h = msg[0]*10 + msg[1];
        int m = msg[3]*10 + msg[4];
        
        if(h == hour && m == minutes) return  true; 
        else return false;
    }
}

int main()
{
    string msg;
    cin >> msg;
    int hour, minutes;
    cin >> hour >> minutes;
    cout << checkTime(msg, hour, minutes);
    return 0;
}