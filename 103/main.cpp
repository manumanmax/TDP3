#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>    // std::sort
#include <map>
using namespace std;

// classes
/************************************BOX***************************************/

class Box{
public:
    Box(int dimension,string s);
    bool canFitBox(Box& b);
    void printBox();
    bool equals(Box b){
        int i = 0;
        if(dimension == b.dimension){
            for(int s:sizes){
                if(s != sizes[i++]) return false;
            }
            return true;
        }
        return false;
    }
    bool isSorted(){
        return sorted;
    }
    void sortDimensions(){
        sorted = true;
        sort(sizes.begin(),sizes.end());
    }
    bool canFitInto(Box& b){
        return b.canFitBox(*this);
    };
    void addFitableBox(Box b){
        fitable.push_back(b);
    }
    bool isFitableEmpty(){
        if(fitable.size() > 0) return false;
        return true;
    }
    bool operator<(const Box& b){
        for (int i = 0; i != this->sizes.size(); i++) {
            if (b.sizes[i] >= this->sizes[i]) {
                return false;
            }
        }
        return true;
    }
    vector<Box> fitable;
private:
    bool sorted;
    int dimension;
    vector<int> sizes;

};
// Structs


typedef struct{
    vector<Box> boxes;
    vector<int> quantity;

} Nest;

/************************************SEQUENCE**********************************/
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
    int solveOne();
    int findMaxNestNumber(vector<Box> fitableBoxes);
    int maxIndexInNest();
    void printNest();
    Nest nest; // TODO :change this
private:
    vector<Box> boxes;
    int boxesSize;
    int numberOfBoxes;
    void calculateBoxNest(Box& box);

};



/***********************GLOBAL FUNCTIONS************/

void extractString(string s, char* str, int& position){
        int i = 0;
        while(s[position] != ' ' && s[position] != '\n'){
            str[i++] = s[position++];
        }
        str[i++] = '\n';
        while(s[position] == ' ') position++;
}

int contains(Nest n, Box b){ // return this indice of the box, -1 otherwise
    for(int i = 0; i < n.boxes.size(); i++){
        if(b.equals(n.boxes[i])) return i;
    }
    return -1;
}


/******************************* FUNCTIONS ***********************/
// BOX'S functions

bool Box::canFitBox(Box& b){
    if(!sorted){
        this->sortDimensions();
    }
    if(!b.isSorted()){
        b.sortDimensions();
    }
    for (unsigned int i = 0; i != this->sizes.size(); i++) {
        if (b.sizes[i] >= this->sizes[i]) {
            return false;
        }
    }
    return true;
}

void Box::printBox(){
    for(int i:this->sizes){
        printf("%d ",i);
    }
    cout << endl;
}

Box::Box(int dimension,string s){
    this->dimension = dimension;
    this->sorted = false;
    int position = 0;
    char buffer[4] = "";
    for(int i = 0; i < dimension; i++){
        extractString(s,buffer, position);
        sizes.push_back(atoi(buffer));
    }
}

// SEQUENCE's functions

//
int Sequence::findMaxNestNumber(vector<Box> fBoxes){
    int indexMax = 0;
    for(Box b: fBoxes){
        int index = contains(nest,b);
        if(index == -1){
            continue;
        }else{
            if(nest.quantity[index] > nest.quantity[indexMax])
                indexMax = index;
        }
    }
    return indexMax;
}

//

void Sequence::calculateBoxNest(Box& box){
    //std::find(nest.begin(), nest.end(), box) != nest.end()
    int boxIndex = contains(nest,box);
    if(boxIndex != -1){
        return;
    }
    for(Box b:boxes){
        if(b.canFitInto(box)){
            box.addFitableBox(b);
        }
    }
    if(box.isFitableEmpty()){
        nest.boxes.push_back(box);
        nest.quantity.push_back(1);
        return;
    }
    for(Box b:box.fitable){
        if(contains(nest,box) == -1){
            calculateBoxNest(b);
        }
    }
    int indexBMax = findMaxNestNumber(box.fitable);
    nest.quantity[indexBMax]++;

}

int Sequence::solveOne(){
    for(Box box:boxes){
        this->calculateBoxNest(box);
    }
    return maxIndexInNest();
}

void Sequence::addBox(string s){

    boxes.push_back(Box(this->boxesSize,s));

}

int Sequence::maxIndexInNest(){
    if(nest.quantity.size() == 0) return -1;
    int maxIndex = 0;
    for(int i = 0; i < nest.quantity.size(); i++){
        if(nest.quantity[i] > nest.quantity[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
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

void Sequence::printNest(){
    for(Box b: nest.boxes){
        b.printBox();
    }

}
/********************** MAIN **********************/





int main()
{
    vector<string> inputs = {"5 2\n","3 7\n","8 10\n","5 2\n","9 11\n","21 18\n"};
    Sequence s(inputs);
    s.printBoxes();
    printf("%d\n",s.solveOne());

    printf("precedent : %d\n",s.findMaxNestNumber(s.nest.boxes[s.solveOne()].fitable));
    s.printNest();
    return 0;
}
