#include<iostream>
#include<list>
using namespace std;
int main(){
    list<int>list1={1,2,3,4,5,6,7,8,9};
    cout<<"List of integer type : ";
    for(int list1 : list1){
        cout<<list1<<"  ";
    }
    cout<<endl;
    list<char>list2={'a','d','e','f','g','h','i'};
    cout<<"List of char type : ";
    for( char list2 : list2){
        cout<<list2<<" ";
    }
    //Adding element in the list at front and back
    list2.push_back('q');
    list2.push_front('z');
    cout<<"Updated list : ";
    for( char list2 : list2){
        cout<<list2<<" ";
    }
    return 0;
}