#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void takeInput(vector<int> &vec){
    int n;
    while(cin >> n){
        vec.push_back(n);
    }
}


bool dfs(vector<int> &vec, int limit, vector<int> targetVec, vector<pair<int,int>> &stack){
    if(vec == targetVec){
        return true;
    }
    else{
        for(unsigned long i = 0; i < vec.size(); ++i){
            for(unsigned long j = i+1; j < vec.size(); ++j){
                reverse(vec.begin()+i, vec.begin()+j);
                stack.push_back({i,j});
                if(dfs(vec, limit, targetVec, stack)){
                    return true;
                }
                stack.pop_back();
                reverse(vec.begin()+i, vec.begin()+j);
            }
        }
        return false;
    }
}

int main(){
    vector<int> vec;
    vector<int> targetVec;
    vector<pair<int,int>> stack;
    takeInput(vec);
    sort(vec.begin(), vec.end());
    targetVec = vec;
    for(int limit = 1; dfs(vec, limit, targetVec, stack) == false; ++limit);
    for(unsigned long i = 0; i < stack.size(); ++i){
        cout << stack[i].first << " " << stack[i].second << endl;
    }
    return 0;
}