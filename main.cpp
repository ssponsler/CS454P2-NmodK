#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

/*
*/
//N > 0 such that N%k = 0 and N uses only the digits from the set S. 
//delta(i,a) = (10i+a)%N
string FindString(int k, vector<int> S);
int delta(int i, int a, int k) {
    return ((10*i)+a)%k;
}


string FindString(int k, vector<int> S) {
    string solution = "";
    int start = 0;
    vector<int> states;
    for (int i = 0; i < k; i++) {
        states.push_back(i);
    }
    vector<int> label(k);
    vector<bool> visited(k, false);
    vector<int> parent(k);
    queue<int> q;
    q.push(start);
    visited[0] = true;
    int current;
    int next;
    int found = false;

    while (!q.empty()) {
        current = q.front();
        q.pop();
        for (int i = 0; i < S.size(); i++) {
            next = delta(current, S[i], k); //delta(i,a,k): i = state, a = symbol, k = N elements
            if (next == 0) { //if next is accepting state
                label[next] = S[i];
                parent[next] = current;
                found = true;
                visited[current] = true;
                break;
            }
            else {
                if (visited[next] == 0) {
                    parent[next] = current;
                    visited[next] = 1;
                    label[next] = S[i];
                    q.push(next);
                }
            }
        }
    }
    if (!found) {
        //return no solution
        return "no solution";   
    }
    //else use parent pointers and label to find shortest string accepted
    else {
        int idx = 0;
        while (parent[idx] != 0) {
            solution = to_string(label[idx]) + solution;
            idx = parent[idx];
        }
    }
    return solution;
}



int main() {
    int k;
    int in;
    vector<int> S;
    cout << "Enter integer N: ";
    cin >> k;
    cout << "Enter digits allowed (0 <= input <= 9) (-1 to exit): " << endl;
    do {
        cin >> in;
        S.push_back(in);
    }
    while (in != -1);

    cout << FindString(k, S) << endl;

    return 0;
}
