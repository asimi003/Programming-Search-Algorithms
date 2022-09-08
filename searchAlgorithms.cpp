#include "problem.h"

using namespace std;

//function to order the queue from smallest to largest
void arrangequeue(vector<problem*> &queue){
    for(int i = 0; i<queue.size(); ++i){
        int mini= i;
        int minfn = queue.at(i)->fn;

        for(int k = i; k<queue.size(); ++k){
            if(queue.at(k)->fn < minfn){
                minfn = queue.at(k)->fn;
                mini = k;
            }
        }
        problem* curr = queue.at(i);
        queue.at(i) = queue.at(mini);
        queue.at(mini) = curr;
    }
}

//uniform cost search algorithm
void uniform_cost_search(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &max_queue_size, int &nodes_expanded, vector<problem*> &repeatedstates){
    //Expanding beginning state
    if(node->parent == NULL) {
        cout << "\nExpanding state";
        node->print_puzzle();
    }
    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > max_queue_size) { 
        max_queue_size = queue.size();
    }
    //checking to see if queue is empty
    if(queue.empty()) {
        return;
    }
    //popping the frontier of the queue before expanding further
    queue.erase(queue.begin());
    //checking to see if the node popped was the final solution
    if(node->checksolution()) {
        solutionstates.push_back(node); 
        return;
    }
    //expanding the node
    if(node->parent !=NULL) {
        cout << "\tExpanding this node...\n\n";
    }
    else { 
        cout << endl << endl;
    }
    //increment the number of nodes expanded after expanding the node
    ++nodes_expanded;

    //testing and seeing which directions we can move the blank node
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();
    bool upb=false, downb=false, leftb=false, rightb=false;

    if(up != NULL){
        up->movement = "Move Up";
        up->parent = node;
        up->fn = up->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(up->current_puzzle == repeatedstates.at(i)->current_puzzle){
                upb = true;
            }
        }
        if(!upb){
        repeatedstates.push_back(up);
        queue.push_back(up);}
    }
    if(down != NULL){
        down->movement = "Move Down";
        down->parent = node;
        down->fn = down->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(down->current_puzzle == repeatedstates.at(i)->current_puzzle){
                downb = true;
            }
        }
        if(!downb){
        repeatedstates.push_back(down);
        queue.push_back(down);}
    }
    if(left != NULL){
        left->movement = "Move Left";
        left->parent = node;
        left->fn = left->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(left->current_puzzle == repeatedstates.at(i)->current_puzzle){
                leftb = true;
            }
        }
        if(!leftb){
        repeatedstates.push_back(left);
        queue.push_back(left);}
    }
    if(right != NULL){
        right->movement = "Move Right";
        right->parent = node;
        right->fn = right->gn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(right->current_puzzle == repeatedstates.at(i)->current_puzzle){
                rightb = true;
            }
        }
        if(!rightb){
        repeatedstates.push_back(right);
        queue.push_back(right);}
    }
    //order the queue from smallest to largest
    arrangequeue(queue);
    
    //recursively continue the uniform cost search algorithm until solution is found
    cout << "The best state to expand with g(n) = " << queue.at(0)->gn << " and h(n) = ";
    cout << queue.at(0)->hn << " is...";
    queue.at(0)->print_puzzle();
    uniform_cost_search(queue.at(0), queue, solutionstates, max_queue_size, nodes_expanded, repeatedstates);
}

//A* with misplaced tile heuristic algorithm
void aStar_misplaced_tile(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &max_queue_size, int &nodes_expanded, vector<problem*> &repeatedstates){
    //Expanding beginning state
    if(node->parent == NULL) {
        cout << "\nExpanding state";
        node->print_puzzle();
    }
    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > max_queue_size) { 
        max_queue_size = queue.size();
    }
    //checking to see if queue is empty
    if(queue.empty()) {
        return;
    }
    //popping the frontier of the queue before expanding further
    queue.erase(queue.begin());
    //checking to see if the node popped was the final solution
    if(node->checksolution()) {
        solutionstates.push_back(node); 
        return;
    }
    //expanding the node
    if(node->parent !=NULL) {
        cout << "\tExpanding this node...\n\n";
    }
    else { 
        cout << endl << endl;
    }
    //increment the number of nodes expanded after expanding the node
    ++nodes_expanded;

    //testing and seeing which directions we can move the blank node
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();
    bool upb=false, downb=false, leftb=false, rightb=false;

    if(up != NULL){
        up->movement = "Move Up";
        up->parent = node;
        up->hn = up->misplaced_tile();
        up->fn = up->gn + up->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(up->current_puzzle == repeatedstates.at(i)->current_puzzle){
                upb = true;
                cout<< endl;
            }
        }
        if(!upb){
        repeatedstates.push_back(up);
        queue.push_back(up);}
    }
    if(down != NULL){ 
        down->movement = "Move Down";
        down->parent = node;
        down->hn = down->misplaced_tile();
        down->fn = down->gn + down->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(down->current_puzzle == repeatedstates.at(i)->current_puzzle){
                downb = true;
                cout<< endl;
            }
        }
        if(!downb){
        repeatedstates.push_back(down);
        queue.push_back(down);}
    }
    if(left != NULL){
        left->movement = "Move Left";
        left->parent = node;
        left->hn = left->misplaced_tile();
        left->fn = left->gn + left->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(left->current_puzzle == repeatedstates.at(i)->current_puzzle){
                leftb = true;
                cout<< endl;
            }
        }
        if(!leftb){
        repeatedstates.push_back(left);
        queue.push_back(left);}
    }
    if(right != NULL){
        right->movement = "Move Right";
        right->parent = node;
        right->hn = right->misplaced_tile();
        right->fn = right->gn + right->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(right->current_puzzle == repeatedstates.at(i)->current_puzzle){
                rightb = true;
                cout<< endl;
            }
        }
        if(!rightb){
        repeatedstates.push_back(right);
        queue.push_back(right);}
    }
     //order the queue from smallest to largest
    arrangequeue(queue);
    
    //recursively continue the A* with misplaced tile heuristic search algorithm until solution is found
    cout << "The best state to expand with g(n) = " << queue.at(0)->gn << " and h(n) = ";
    cout << queue.at(0)->hn << " is...";
    queue.at(0)->print_puzzle();
    aStar_misplaced_tile(queue.at(0), queue, solutionstates, max_queue_size, nodes_expanded, repeatedstates);
}

//A* with euclidean distance heurisitic algorithm
void aStar_euclidean_distance(problem* node, vector<problem*> &queue, vector<problem*> &solutionstates, int &max_queue_size, int &nodes_expanded, vector<problem*> &repeatedstates/*, int &poss*/){
    //Expanding beginning state
    if(node->parent == NULL) {
        cout << "\nExpanding state";
        node->print_puzzle();
    }
    //this will capture the max size the queue ever was, for the last 3 lines of the trace
    if(queue.size() > max_queue_size) { 
        max_queue_size = queue.size();
    }
    //checking to see if queue is empty
    if(queue.empty()) {
        return;
    }
    //popping the frontier of the queue before expanding further
    queue.erase(queue.begin());
    //checking to see if the node popped was the final solution
    if(node->checksolution()) {
        solutionstates.push_back(node); 
        return;
    }
    //expanding the node
    if(node->parent !=NULL) {
        cout << "\tExpanding this node...\n\n";
    }
    else { 
        cout << endl << endl;
    }
    //increment the number of nodes expanded after expanding the node
    ++nodes_expanded;

    //testing and seeing which directions we can move the blank node
    problem* up = node->moveUp();
    problem* down = node->moveDown();
    problem* left = node->moveLeft();
    problem* right = node->moveRight();
    bool upb=false, downb=false, leftb=false, rightb=false;

    if(up != NULL){
        up->movement = "Move Up";
        up->parent = node;
        up->hn = up->euclidean_distance();
        up->fn = up->gn + up->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(up->current_puzzle == repeatedstates.at(i)->current_puzzle){
                upb = true;
            }
        }
        if(!upb){
        repeatedstates.push_back(up);
        queue.push_back(up);}
    }
    if(down != NULL){
        down->movement = "Move Down";
        down->hn = down->euclidean_distance();
        down->parent = node;
        down->fn = down->gn + down->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(down->current_puzzle == repeatedstates.at(i)->current_puzzle){
                downb = true;
            }
        }
        if(!downb){
        repeatedstates.push_back(down);
        queue.push_back(down);}
    }
    if(left != NULL){
        left->movement = "Move Left";
        left->parent = node;
        left->hn = left->euclidean_distance();
        left->fn = left->gn + left->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(left->current_puzzle == repeatedstates.at(i)->current_puzzle){
                leftb = true;
            }
        }
        if(!leftb){
        repeatedstates.push_back(left);
        queue.push_back(left);}
    }
    if(right != NULL){
        right->movement = "Move Right";
        right->parent = node;
        right->hn = right->euclidean_distance();
        right->fn = right->gn + right->hn;
        for(int i=0; i<repeatedstates.size(); ++i){
            if(right->current_puzzle == repeatedstates.at(i)->current_puzzle){
                rightb = true;
            }
        }
        if(!rightb){
        repeatedstates.push_back(right);
        queue.push_back(right);}
    }
    //order the queue from smallest to largest
    arrangequeue(queue);
    
    //recursively continue the A* with euclidian distance heuristic search algorithm until solution is found
    cout << "The best state to expand with g(n) = " << queue.at(0)->gn << " and h(n) = ";
    cout << queue.at(0)->hn << " is...";
    queue.at(0)->print_puzzle();
    aStar_euclidean_distance(queue.at(0), queue, solutionstates, max_queue_size, nodes_expanded, repeatedstates/*, poss*/);
}
