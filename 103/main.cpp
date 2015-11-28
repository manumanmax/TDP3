#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;



void extractString(string s, char* str, int& position){
        int i = 0;
        while(s[position] != ' ' && s[position] != '\n'){
            str[i++] = s[position++];
        }
        str[i++] = '\n';
        while(s[position] == ' ') position++;
}


class Box{
public:
    Box(int dimension,string s);
    void printBox();
private:
    int dimension;
    vector<int> sizes;

};

void Box::printBox(){
    for(int i:this->sizes){
        printf("%d ",i);
    }
    cout << endl;
}

Box::Box(int dimension,string s){
    this->dimension = dimension;
    int position = 0;
    char buffer[4] = "";
    for(int i = 0; i < dimension; i++){
        extractString(s,buffer, position);
        sizes.push_back(atoi(buffer));
    }
}


class Sequence{
public:
    Sequence(vector<string> s);
    void addBox(string s);
    void printBoxes(){
      for(Box box:boxes){
        box.printBox();
      }
      cout << endl;
    };
private:
    vector<Box> boxes;
    int boxesSize;
    int numberOfBoxes;

};

void Sequence::addBox(string s){

    boxes.push_back(Box(this->boxesSize,s));

}

Sequence::Sequence(vector<string> strings){
    int pos = 0;
    char buffer[4] = "";
    extractString(strings[0],buffer,pos); this->numberOfBoxes = atoi(buffer);
    extractString(strings[0],buffer,pos); this->boxesSize = atoi(buffer);

    for(int i = 1; i <= numberOfBoxes; i++){
        this->addBox(strings[i]);
    }
}


int main()
{
    vector<string> inputs = {"5 2\n","3 7\n","8 10\n","5 2\n","9 11\n","21 18\n"};
    Sequence s(inputs);
    s.printBoxes();
    return 0;
}
