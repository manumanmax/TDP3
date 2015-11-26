#include <iostream>
#include <string>

using namespace std;

bool counter(int& longestChain, const string input1, const string input2){
    int secondChainStartIndex = 0;
    bool subChain = false;
    int localMaximum = 0;
    for(auto letter1:input1){
        for(unsigned int i = secondChainStartIndex; secondChainStartIndex < input2.length(); i++){
            if(letter1 == input2[i]){
                cout << letter1 << " = " << input2[i] << " : " << i << std::endl;
                secondChainStartIndex = i;
                subChain = true;
                localMaximum++;
                break;
            }

        }
        if(localMaximum > longestChain){
            longestChain = localMaximum;
        }
    }
    return subChain;
}


int main()
{
    int longestChain = 0;
    string input1;
    string input2;
    cin >> input1;
    cin >> input2;

    bool isSubChain = counter(longestChain,input1,input2);


    cout << longestChain << endl;
    return 0;
}
