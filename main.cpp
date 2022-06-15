#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct breakpointVec{
    int x;
    bool breakpoint;    
};

void takeInput(vector<int> &vec){
    int temp;
    while(!cin.eof()){
        cin >> temp;
        vec.push_back(temp);
    }
    vec.push_back((int)vec.size());
}

void constructBreakpointVec(vector<int> vec, vector<breakpointVec> &breakpointVec){
    for(unsigned long i = 0; i < vec.size(); ++i){
        breakpointVec.push_back({vec[i], false});
    }
}

void changeBreakpointVec(vector<int> vec, vector<breakpointVec> &breakpointVec){
    for(unsigned long i = 0; i < vec.size(); ++i){
        breakpointVec[i].x = vec[i];
    }
} 

int checkBreakpoints(vector<breakpointVec> &vec, int breakpointCount){
    breakpointCount = 0;
    for(unsigned long i = 0; i < vec.size()-1; ++i){
        if(abs(vec[i].x-vec[i+1].x) != 1){
            vec[i].breakpoint = true;
            breakpointCount++;
        }
        else{
            vec[i].breakpoint = false;
            breakpointCount--;
        }
    }
    return breakpointCount;
}


bool dfs(vector<breakpointVec> &breakVec, vector<int> &vec, vector<int> target, int &count, vector<pair<int, int>> &result){
    if(vec == target){
        return true;
    }
    else{
        for(int i = 0; i < (int)breakVec.size(); ++i){
            if(breakVec[i].breakpoint == true){
                for(int j = 0; j < (int)breakVec.size(); ++j){
                    if(breakVec[j].x == i+1){
                        for(;j < (int)breakVec.size();++j){
                            if(breakVec[j].breakpoint == true)
                                break;
                        }
                        reverse(vec.begin()+i+1, vec.begin()+j+1);
                        changeBreakpointVec(vec, breakVec);
                        checkBreakpoints(breakVec, count);
                        count++;
                        result.push_back({i+1,j});
                        if(dfs(breakVec, vec, target, count,result)){
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
}


int main(){
    vector<int> vec = {0};
    vector<int> target;
    vector<pair<int, int>> result;
    vector<breakpointVec> breakVec;
    int count = 0;
    int breakpointCount = 0;
    takeInput(vec);
    target = vec;
    sort(target.begin(), target.end());
    constructBreakpointVec(vec, breakVec);
    breakpointCount = checkBreakpoints(breakVec, breakpointCount);
    dfs(breakVec, vec, target, count, result);
    cout <<  count << endl;
    for(auto i = 0; i < result.size(); ++i){
        cout << result[i].first << " " << result[i].second << endl;
    }
    return 0;
}