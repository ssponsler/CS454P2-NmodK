/** **********************************************************************************
 * Project 2
 * Sean Sponsler Evan Walters
 * CS 454
 * Prof: Dr. Ravikumar
 * Date: March 5th, 2023
 *
 * Description:	Given a postive integer N and a subset of digits from {0-9}.
 * Using a DFA outputs the smallest number divisble by N that only uses the given digits. 
 * Repeats process until a -1 is given.
 *************************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
using namespace std;

// prototypes
int delta(int i, int a, int k);
string FindString(const int k, const vector<int> S);

int main() {
  
    int k = 1;  // divisor

    // repeat process until -1 is entered for k
    while (k > 0) {
       
        int in;
        vector<int> S;
        cout << "Enter integer N (greater than 1) (-1 to quit): ";
        cin >> k;
        //we are ASSUMING k is in the range 1 to 99999
        while (cin.fail() || k == 0) { //invalid input (not integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer N greater than 1 (-1 to quit): ";
            cin >> k;
        }

        // use loop to obtain allowed digits, ends when -1 is given
        if (k > 0) {
            cout << "Enter single allowed digit followed by enter: (0 <= input <= 9) (-1 to execute): " << endl;
            do {
                cin >> in;
                while (cin.fail() || in < -1 || in > 9) { //invalid input (not integer)
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter single allowed digit (0 <= input <= 9) (-1 to execute): ";
                    cin >> in;
                }
                //check if input is already in vector, function will not work if this is the case
                bool duplicate = false;
                for (int i = 0; i < S.size(); i++) {
                    if (S[i] == in) duplicate = true;
                }
                while (duplicate) { //ensure the user does not continue to enter duplicate digits
                    cout << "Input already present in digits, please enter a unique allowed digit: ";
                    cin >> in;
                    while (cin.fail() || in < -1 || in > 9) { //invalid input (not integer)
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Enter single allowed digit (0 <= input <= 9) (-1 to execute): ";
                        cin >> in;
                    }
                    duplicate = false;
                    for (int i = 0; i < S.size(); i++) {
                        if (S[i] == in) duplicate = true;
                    }
                }
                S.push_back(in);
            } while (in != -1);
            S.pop_back(); //remove final -1
            cout << "Output: " << FindString(k, S) << endl;
        }
    }
    return 0;
}


//********************************************************************************
// Function: delta
// In: current state, next input, divisor N
// Return: resulting state/remainder
// DESC: Conatenates the next input to the current state number,
//      then modulos that with given N to find the remainder/next state
//********************************************************************************
int delta(int i, int a, int k) {
    return ((10 * i) + a) % k;
}


//********************************************************************************
// Function: FindString
// In: N for divisible number, vector of digits allowed to be used
// Return: string of numbers / no solution 
// DESC: Taking N and the allowed digits, uses a DFA to find the smalled number
//      divisible by N that uses only the allowed digits.
//********************************************************************************
string FindString(const int k, const vector<int> S) {
    // define some variables and parallel vectors
    string solution = "";
    int start = 0;
    int current;
    int next;
    int found = false;

    vector<int> label(k);
    vector<bool> visited(k, false); // initialize every state to false
    vector<int> parent(k);
    queue<int> q;

    visited[0] = true;  // set starting state as visited

    q.push(start);  // put startng state in queue

    // loop while queue isn't empty
    while (!q.empty()) {
        // set current then pop from queue
        current = q.front();
        q.pop();    

        // loop for each allowed digit
        for (int i = 0; i < S.size(); i++) {
            next = delta(current, S[i], k); //delta(i,a,k): i = state, a = symbol, k = divisor
            
            // if next is accepting state and current state isn't a final state
            if (next == 0 && current != 0) { 
                label[next] = S[i];
                parent[next] = current;
                found = true;   // found path for shortest string
                break;  // get out of for loop
            }

            // set it's various states, and push next onto queue
            else {
                if (visited[next] == 0) {
                    parent[next] = current;
                    visited[next] = 1;
                    label[next] = S[i];
                    q.push(next);
                }
            }
        }

        // in case shortest path is found, return the corresponding string
        if (found) {
            int idx = 0;

            // work backwards through parellel vectors: parent and label, until we are at starting state: 0
            do {
                solution = to_string(label[idx]) + solution;    // concatenate new digit to left of solution
                idx = parent[idx];
            } while (idx != 0);

            return solution;
        }
    }

    // for case that entire DFA is searched with no found solution
    return "no solution";
}
