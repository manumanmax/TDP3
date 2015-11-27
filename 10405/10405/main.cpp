#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

string getOneSubstring(string localString, int idx1, int idx2, const string s1, const string s2);

/*
int counter(int size, int index1, int index2, const string input1, const string input2){
    int elseLocalMin = 0;
    int localMaximum = 0;
    char buffer[10];
    for(unsigned int i = index1; i < input1.length(); i++){
        for(unsigned int j = index2; j < input2.length(); j++){
            if(input1[i] == input2[j]){
                index1 = i+1;
                index2 = j+1;
                size++;
                break;
            }else{
                cout << "go to read index1["; sprintf(buffer, "%d",index1); printf("%s",buffer);
                cout << "] and index2["; sprintf(buffer, "%d",index2 + 1); printf("%s",buffer);
                cout << "]" << endl;
                if(index1 < input1.length() && index2 < input2.length())
                    localMaximum = counter(size,index2+1 , index1 ,input2, input1);
            }
        }
    }
    if(localMaximum > size)
        return localMaximum;
    else
        return size;
}*/

string getSubstrings(vector<string>& vStrings, string substring, int idx1, int idx2, const string s1, const string s2){

    int localIdx2 = idx2;

    for(; idx1 < s1.length(); idx1++){
        for(idx2 = localIdx2; idx2 < s2.length(); idx2++){
            //printf("%d -> ",idx2);
            if(s1[idx1] == s2[idx2]){
                localIdx2 = idx2+1;
                substring.push_back(s1[idx1]);
                break;
            }

                //substring.push_back(s2[idx1]);
                //string localString = substring;


        }
         vStrings.push_back(getOneSubstring("", idx1, 0, s1, s2));

        //cout << endl;
    }
    return substring;

}

string getOneSubstring(string substring, int idx1, int idx2, const string s1, const string s2){

    int localIdx2 = idx2;
    for(; idx1 < s1.length(); idx1++){
        for(idx2 = localIdx2; idx2 < s2.length(); idx2++){
            //printf("%d -> ",idx2);
            if(s1[idx1] == s2[idx2]){
                localIdx2 = idx2+1;
                substring.push_back(s1[idx1]);
                break;
            }
        }
        //cout << endl;
    }
    return substring;
}




int main()
{
    string input1 = "bcacbcabbaccbab";
    string input2 = "bccabccbbabacbc";

    //cin >> input1;
    //cin >> input2;
    vector<string> vS;
    vS.push_back(getSubstrings(vS,"",0,0,input1,input2));
    vS.push_back(getSubstrings(vS,"",0,0,input2,input1));
    int sizeMax = 0;
    for(string str: vS){
            cout << str << endl;
        if(str.length() > sizeMax)
            sizeMax = str.length();
    }
    cout << sizeMax << endl;

    cout << getOneSubstring("",0,0,input2,input1) << endl;

    return 0;
}
