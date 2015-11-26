#include <iostream>
#include <string>

using namespace std;

int main()
{

    string input;
    cin >> input;

    for(auto letter:input){
        cout << letter << endl;
    }
    cout << "CR check" << endl;
    return 0;
}
