// name: 박소민 studentID: 201811553 major: 통계학과 contact info:01023143857

#include<iostream>
#include<fstream>
#include<string>
#include<stack>
#include<stdlib.h>

using namespace std;

//Convert character(0~9 or a~f) which is Hexadecimal, To Decimal
int Hex2Dec(char ch){
    int result=0;
    if ( ch >= 'a' && ch <= 'f' )                
        result =  ch - 'a' + 10;//10~15
    else if ( ch >= '0' && ch <= '9' )            
        result = ch - '0';//0~9
    return result;
}

string decoder(string str){
    stack<int> repeatstack; //Push converted Hexadecimal to this stack
    stack<char> stringstack; //Push characters, "{" , and "}" to this stack
    string temp = "", result = "";
    int i;
    for(i=0;i<str.length();i++) {
        int cnt=0;

        if(str[i]=='{'){
            if((str[i-1]>='0' && str[i-1]<='9') || (str[i-1]>='a'&&str[i-1]<='f')){
                repeatstack.push(Hex2Dec(str[i-1]));//Push a hexadecimal into repeatstack
                stringstack.pop();//Erase hexadecimal from stringstack
                stringstack.push(str[i]);//Push { into stringstack
            }
            else {
                break;//Str[i-1] is not Hexadecimal -> Error: Invalid input
            }
        }

        else if(str[i]=='}'){
            temp="";//Initialize the string to be repeated

            if(! repeatstack.empty()){
                cnt=repeatstack.top(); //Number to repeat
                repeatstack.pop(); //Erase after define count(cnt)
            }
            while(! stringstack.empty() && stringstack.top()!='{'){
                temp=stringstack.top() + temp;//Combine character
                stringstack.pop();//Erase after combine
            }
            if(! stringstack.empty() && stringstack.top() == '{')
                stringstack.pop();//Erase "{"
            if(cnt==0){
                result="";//If the number in front of "{" is 0, repeat anything
                continue;
            }
            else{
                for (int j = 0; j < cnt; j++)
                    result = result + temp;//Repeat the combined string using cnt 
    
                for (int j = 0; j < result.length(); j++)
                    stringstack.push(result[j]); //Push repeated string into stack again
    
                result = "";//Initialize result
            }
        }

        else{
            stringstack.push(str[i]);//The character which is not Hexa or { or } is pushed into string stack
        }
    }
    
    if(i!=str.length()) {
        result="ERROR: Invalid input"; //Wrong input
        return result;
    }

    else{
        while (! stringstack.empty()){
            result = stringstack.top() + result; //Created final string
            stringstack.pop();//Erase the character for next trial
        }
        return result;
    }
}

int main(void){
    string filePath = "decoded.txt";
    ifstream readFile;
    ofstream writeFile(filePath.data());
    
    string filename;
    cout<<"INPUT_FILE_NAME: ";
    cin>>filename;//Input file path

    readFile.open(filename);
    string line;

    if(readFile.is_open()){
        while(!readFile.eof())
        {   
            getline(readFile,line);//Read one line for each trial
            if( writeFile.is_open() ){
                writeFile << decoder(line)<<"\n";
            }
        }
    }
    else{
        cout<<"filename is err"<<endl;
    }
    readFile.close();
    writeFile.close();
    return 0;
}