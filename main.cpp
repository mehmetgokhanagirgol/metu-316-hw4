#include <iostream>
#include <vector>

using namespace std;

void takeInput(vector<int> &vec){
    int n;
    while(cin >> n){
        vec.push_back(n);
    }
}

int main(){
    vector<int> vec;
    takeInput(vec);
    return 0;
}