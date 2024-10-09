#include<iostream>
#include<list>
using namespace std;
int main(){
    //Q.1:- Initializes a list of strings containing the names of 5 cities.
    list<string>string1={"Delhi","Mumbai","Agra","Ayodhya","Mathura"};
    //Q.2:-Displays the contents of the list.
    cout<<"Cities : ";
    for(list<string >::iterator it=string1.begin();it!=string1.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    //Q.3:-Prompts the user to add a new city to the front and the back of the
    //list.
    string1.push_front("Chennai");
    string1.push_back("Kolkata");
    cout<<"List after adding elements : ";
    for(list<string>::iterator ite=string1.begin();ite!=string1.end();ite++){
        cout<<*ite<<" ";
    }
    cout<<endl;
    //Q.4:-Deletes a city by name (use std::remove() and erase() for this).Sorts
    //the list alphabetically.
    string1.remove("Agra");
    cout<<"List after deleting  elements : ";
    for(list<string>::iterator ite=string1.begin();ite!=string1.end();ite++){
        cout<<*ite<<" ";
    }
    cout<<endl;
    string1.sort();
    cout<<"Sorted list : ";
    for(list<string>::iterator ite=string1.begin();ite!=string1.end();ite++){
        cout<<*ite<<" ";
    }
    cout<<endl;
    //Q.5:-Reverses the list.
    string1.reverse();
    cout<<"Reversed list : ";
    for(list<string>::iterator ite=string1.begin();ite!=string1.end();ite++){
        cout<<*ite<<" ";
    }

  return 0;
}