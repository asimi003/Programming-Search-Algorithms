#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "problem.h"

using namespace std;

//function to create final state of the puzzle
void problem::make_final_state(vector<int> &stop){
    for(int i = 1; i < 9; i++){
        stop.push_back(i);
    }
    stop.push_back(0);  //goal is to get the 0 in the bottom right of the puzzle
}

//default constructor
problem::problem(){
    parent = NULL;
    fn = 0;
    hn = 0;
    gn = 0;
    movement = " ";
    make_final_state(current_puzzle);
    make_final_state(final_puzzle);
}

//constructor
problem::problem(vector<int> start){
    parent = NULL;
    fn = 0;
    gn = 0;
    hn = 0;
    movement = " ";
    current_puzzle = start;
    make_final_state(final_puzzle);

}

//function to track the movement of the 0 in the puzzle
int problem::track0(){
    int index;
    for(int i = 0; i < puzzlesize; ++i){
        if(current_puzzle.at(i) == 0){
            index = i;
        }
    }
    return index;
}

//function to check if the current puzzle is the same as the final puzzle
bool problem::checksolution(){
    for(int i=0; i<puzzlesize; ++i){
        if(current_puzzle.at(i) != final_puzzle.at(i)){
            return false;
        }
    }
    return true;
}

//functions to move the 0 in the puzzle and create child nodes
problem* problem::moveUp(){
    problem* child = new problem(this->current_puzzle);
    int blank = track0();
    //checking to see if the 0 is already in the top row
    if(blank < 3){
        return NULL;
    }
    else{
        //switching positions of the 0 and the index above it
        swap(child->current_puzzle.at(blank), child->current_puzzle.at(blank- 3));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }

}

//functions to move the 0 in the puzzle and create child nodes
problem* problem::moveLeft(){
    problem* child = new problem(this->current_puzzle);
    int blank = track0();
    //checking to see if the 0 is already on the left side
    if(blank % 3 == 0){
        return NULL;
    }
    else{
        //switching positions of the 0 and the index to the left of it
        swap(child->current_puzzle.at(blank), child->current_puzzle.at(blank - 1));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }

}

//functions to move the 0 in the puzzle and create child nodes
problem* problem::moveDown(){
    problem* child = new problem(this->current_puzzle);
    int blank = track0();
    //checking to see if the 0 is already on the bottom side
    if(blank >= (3*(3 - 1))){
        return NULL;
    }
    else{
         //switching positions of the 0 and the index on the bottom of it
        swap(child->current_puzzle.at(blank), child->current_puzzle.at(blank + 3));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }
}

//functions to move the 0 in the puzzle and create child nodes
problem* problem::moveRight(){
    problem* child = new problem(this->current_puzzle);
    int blank = track0();
    //checking to see if the 0 is already on the right side
    if((blank + 1) % 3 == 0){
        return NULL;
    }
    else{
        //switching positions of the 0 and the index on the right of it
        swap(child->current_puzzle.at(blank), child->current_puzzle.at(blank + 1));
        child->parent = this;
        child->gn = this->gn + 1;
        return child;
    }
}

//function to calculate the misplaced tile heuristic, counting the number of misplaced tiles
int problem::misplaced_tile(){
    int count = 0;
    for(int i = 0; i < puzzlesize - 1; i++){
        if(current_puzzle.at(i) != final_puzzle.at(i)){
            count++;
        }
    }
    return count;
}

//function to calculate the euclidean distance heuristic, calculating the total distance of tiles in the wrong position to their correct positions
//formula is SQRT((X1-Y1)^2 + (X2-Y2)^2)
int problem::euclidean_distance(){
    int total;
    int count = 0;
    int X1, Y1;
    int X2, Y2;
    int X3, Y3;
    bool cY, tY = false;

    for(int i = 0; i < puzzlesize; i++){
        if(current_puzzle.at(i) == 0){
            continue;
        }
        else if(current_puzzle.at(i) != final_puzzle.at(i)){
            X1 = ((i+1) % 3 == 0) ? 3 : (i + 1) % 3;
            X2 = (current_puzzle.at(i) % 3 == 0) ? 3 : current_puzzle.at(i) % 3;
            cY = tY = false;

            for(int j = 1; j < 3 + 1; j++){
                if((i < j * 3) && !cY){
                    Y1 = j;
                    cY = true;
                }
                if((current_puzzle.at(i) < j * 3) && !tY){
                    Y2 = j;
                    tY = true;
                }
            }

            X3 = X1 - X2;
            Y3 = Y1 - Y2;

            X3 = abs(X3);
            Y3 = abs(Y3);

            total = sqrt(pow(X3, 2) + pow(Y3, 2));

            count += total;
        }
    }
    return count;
}

//function to print out the current state of the puzzle
void problem::print_puzzle(){
    for(int i = 0; i < puzzlesize; ++i){
        if(i % 3 == 0){
            cout << endl;
        }
        std::cout << current_puzzle.at(i) << " ";
    }
}

