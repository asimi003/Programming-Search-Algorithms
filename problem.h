#ifndef __PROBLEM_H__
#define __PROBLEM_H__
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class problem{
    public:
        //vector holding current state of the puzzle
        vector<int> current_puzzle;
        //vector holding final state of the puzzle, 0 in the bottom right corner
        vector<int> final_puzzle;
        //variables holding values for f(n) h(n) and g(n)
        double fn;           
        double hn;           
        double gn;
        //parent pointer from child to parent
        problem* parent; 
        //string holding the steps for the solution path
        string movement;
        //size of the puzzle
        const int rows = 3 ; 
        const int columns = 3;
        const int puzzlesize = rows*columns;
  
        //constructors
        problem();
        problem(std::vector<int> start);

        //deconstructor
        ~problem();

        //function to track the movement of the 0 in the puzzle
        int track0();

        //function to check if the current puzzle is the same as the final puzzle
        bool checksolution();

        //functions to move the 0 in the puzzle and create child nodes
        problem* moveUp();
        problem* moveDown();
        problem* moveLeft();
        problem* moveRight();

        //functions to calculate the heuristic costs
        int misplaced_tile();
        int euclidean_distance();

        //function to create final state of the puzzle
        void make_final_state(std::vector<int> &stop);

        //function to print out the current state of the puzzle
        void print_puzzle();
};

#endif