#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int isSimilar(string,string);
int main()
{
    vector<string>lis;
    string input;
    cin>>input;
    //11?¡§¡ä¨º¦Ì?
    while(input!="#"){
        lis.push_back(input);
        cin>>input;
    }

   string searchWord;
   cin>>searchWord;
   while(searchWord!="#"){
        vector<string>::iterator s=find(lis.begin(),lis.end(),searchWord);
        if(s!=lis.end()) cout<<searchWord<<" is correct"<<endl;
        else{
            cout<<searchWord<<": ";
            int s = lis.size();
            int i=0;
            while(i<s){
                if(isSimilar(searchWord,lis[i])==1) cout<<lis[i]<<" ";
                i++;
            }
            cout<<endl;
        }
        cin>>searchWord;
   }
   return 0;
}

//0>> equal;1>>similar;-1>>not similar;
int isSimilar(string s1,string s2)
{
    if(s1==s2) return 0;

    if(s1.length()<s2.length()){
       string tmp;
       tmp= s1;
        s1=s2;
        s2=tmp;
    }
    int a = s1.length();
    int b = s2.length();
    if(abs(a-b)>1) return -1;
    if(a>b){
        int i=0;
        while(i<a)
        {
            string tmp = s1.substr(0,i)+s1.substr(i+1,b-i);
            if(tmp==s2) return 1;
            else i++;
        }
        return -1;
    } else{
        int counter = 0;
        int i=0;
        while(i<a){
            if(s1[i]!=s2[i]) counter++;
            i++;
        }
        if(counter<=1) return 1;
        else return -1;
    }
}
