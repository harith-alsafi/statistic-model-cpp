#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    const string empty = " ";
    const string uparrow = "▲";
    const string block = "█";
    const string point = "⬤";
    const string downarrow = "▼";
    const string hline = "━━";
    const string vline = "┃";
    const string rightarrow = "▶";
    const string leftarrow = "◀"; 
    cout << leftarrow << hline << point << hline << rightarrow << "\n";
    cout << uparrow << "\n" << vline << "\n"  << vline << "\n" << downarrow << "\n";
    cout << point << point << "\n" << empty << point << "\n" << point << "\n";
    return 0;
}
