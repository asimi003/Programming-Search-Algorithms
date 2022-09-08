#include <iostream>
#include <string>
#include <vector>
#include "problem.cpp"
#include "problem.h"
#include "searchAlgorithms.cpp"

using namespace std;


void convertStrtoArr(string str, vector<int> &arr)
{
    int j = 0, i;
    // Traverse the string
    for (i = 0; str[i] != '\0'; i++) {
        // if str[i] is ', ' then split
        if (str[i] == ',')
            continue;
         if (str[i] == ' '){
            // Increment j to point to next
            // array location
            j++;
        }
        else {
            // subtract str[i] by 48 to convert it to int
            // Generate number by multiplying 10 and adding
            // (int)(str[i])
            arr[j] = arr[j] * 10 + (str[i] - 48);
        }
    }
}

int main() {
    //menu for the program
    cout << "Welcome to Angelica's 8 puzzle solver.\n";
    cout << "Type \"1\" to use default puzzle, or \"2\" to enter your own puzzle.\n";
    int puzzleChoice;
    cin >> puzzleChoice;
    cin.ignore();

    vector<int> beginningPuzzle(9,0);

    if(puzzleChoice == 1) {
        int defaultPuzzle;
        cout << "Choose a default puzzle:\n";
        cout << "1.Trivial	2.Easy		3.Very Easy\n";
        cout << "1 2 3		1 2 0		1 2 3\n";
        cout << "4 5 6		4 5 3		4 5 6\n";
        cout << "7 8 0		7 8 6		7 0 8\n\n";
        cout << "4.Doable	5.Oh Boy	6.Impossible\n";
        cout << "0 1 2		8 7 1		1 2 3\n";
        cout << "4 5 3		6 0 2		4 5 6\n";
        cout << "7 8 6		5 4 3		8 7 0\n";
        cin >> defaultPuzzle;
        cin.ignore();
        switch (defaultPuzzle) {
            case 1:
                beginningPuzzle = {1, 2, 3, 4, 5, 6, 7, 8, 0};
                break;
            case 2:
                beginningPuzzle = {1, 2, 0, 4, 5, 3, 7, 8, 6};
                break;
            case 3:
                beginningPuzzle = {1, 2, 3, 4, 5, 6, 7, 0, 8};
                break;
            case 4:
                beginningPuzzle = {0, 1, 2, 4, 5, 3, 7, 8, 6};
                break;
            case 5:
                beginningPuzzle = {8, 7, 1, 6, 0, 2, 5, 4, 3};
                break;
            case 6:
                beginningPuzzle = {1, 2, 3, 4, 5, 6, 8, 7, 0};
                break;
            }
    }
    else if(puzzleChoice == 2) {
        cout << "Enter your puzzle, use a zero to represent the blank\n";
        cout << "Enter the array, put a comma and a space after each number except the last\n";
        cout << "Example: 1, 2, 3, 4, 5, 6, 7, 8, 0\n";
        string custom_puzzle;
        getline(cin, custom_puzzle);
        convertStrtoArr(custom_puzzle,beginningPuzzle);
    } 

    //we now have an array with our values of the puzzle loaded into it
    //now we need to create a problem class object
    problem* start_state = new problem(beginningPuzzle);

    //we need arrays for the queue, solution states, and repeated states to be used in our search algorithms
    //we also need to keep track of the nodes expanded, depth, and max queue size to be printed later 
    vector<problem*> queue;
    vector<problem*> solutionstates;
    vector<problem*> repeatedstates;
    queue.push_back(start_state);
    repeatedstates.push_back(start_state);
    int nodes_expanded = 0;
    int max_queue_size = 0;
    int solution_depth = 0;   //solution depth is going to be the same as the g(n) of the leaf/solution node

    //choosing which type of search algorithm to apply to the puzzle
    cout << "Enter your choice of algorithm\n";
    cout << "1. Uniform Cost Search\n";
    cout << "2. A* with the Misplaced Tile heuristic.\n";
    cout << "3. A* with the Eucledian distance heuristic.\n";
    int algorithm; 
    cin >> algorithm;
    if(algorithm == 1) {
        uniform_cost_search(start_state, queue, solutionstates, max_queue_size, nodes_expanded, repeatedstates); //uniform cost search
    }
    if(algorithm == 2) {
        aStar_misplaced_tile(start_state, queue, solutionstates, max_queue_size, nodes_expanded, repeatedstates); //A* with misplaced tile
    }
    if(algorithm == 3) {
         aStar_euclidean_distance(start_state, queue, solutionstates, max_queue_size, nodes_expanded, repeatedstates); //A* with eucledian distance
    }
    if(!solutionstates.size()){ 
        cout<< "\n\nPuzzle is impossible to solve!" <<endl;
    }
    else{
        // Printing out the number of nodes expanded, depth, and max queue size after search is complete
        arrangequeue(solutionstates);
        solution_depth = solutionstates.at(0)->gn;
        cout << "\nTo solve this problem the search algorithm expanded a total of " << nodes_expanded << " nodes.\n";
        cout << "The maximum number of nodes in the queue at any one time: " << max_queue_size << ".\n";
        cout << "The depth of the goal node was " << solution_depth <<".";
    }

    return 0;
}
