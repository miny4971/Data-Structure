#include<iostream>
#include<map>
#include<string>
using namespace std;
 
int main(void){
    
    map<int, string> m;
    
    m.insert(pair<int, string>(40, "me"));
    m.insert(pair<int, string>(35, "Show"));
    m.insert(pair<int, string>(10, "Dok2"));
    m.insert(pair<int, string>(90, "6"));
    m.insert(pair<int, string>(65, "money"));
    m.insert(pair<int, string>(20, "ZICO"));
    m.insert(pair<int, string>(50, "the"));
 
    
    map<int, string>::iterator iter;
    
    //접근방법 1 
    for(iter = m.begin(); iter != m.end(); iter++){
        cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
    cout << endl;
    

    
    
    return 0;    
}
