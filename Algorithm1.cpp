#include<iostream>
#include<vector>
#include<Algorithm>
using namespace std;
int main(){
    //creating a vector of int type
    vector<int>vector1={1,2,3,4,5,6,7,8,9,0};
    //print vector elements using ranged loop
    for(int vector1 : vector1 ){
        cout<< vector1 <<" ";
        
     
    }
    cout<<endl;
    //creating vector of char type
    vector<char>vector2={'a','b','c','d','e','f','g','h','i'};
    //print vector elements  using ranged loop
    for(char i=0;i<vector2.size();i++){
        cout<<vector2[i]<<" ";
    }
    cout<<endl;
    //vector iterator
    //intialise the vector iterator to the first element of vector
    vector<int>::iterator it=vector1.begin();
    cout<<"First Element : "<<*it<<" "<<endl;
    //changing the value of the iterator
    it=vector1.end()-1;
    cout<<"Last Element : "<<*it<<endl;
    //C++ ALgorithms
    //creating a vector of int type 
    vector<int>vector3={100,27,39,14,05,36,27,8,91,00,90};
    //sorting vector in ascending order
    sort(vector3.begin(),vector3.end());
    cout<<"Sorted Vector : ";
    //print the element of vector in sorted order
    for( int vector3 : vector3){
        cout  <<vector3<<" ";
    }
    cout<<endl;
    vector<int>vector4={34,45,65,23,4,5,67,7,899,34,23,9,90,78,89};
    //sorting  vector in descending order
    sort(vector4.rbegin(),vector4.rend());
    cout<<"Reverse Vector : ";
    //print the element of the sorted vector
    for(int vector4 : vector4){
        cout<<vector4<<" ";
    }
    cout<<endl;
    //intialising vector that has same value 
    vector<int>vector5(20,10);
    cout<<"Vector of Same Element : ";
    for(int vector5 : vector5){
        cout<<vector5<<" ";
    }
    cout<<endl;
    //Adding element to the vector
    vector<int>vector6={1,2,3,4,5,6,7,8,9,0};
    vector6.push_back(11);//Add element by using vector.push_back()
    cout<<"Added Element : ";
    cout<<vector6[10]<<endl;;
    //vector6.insert(56);//Add element by using insert()
    //cout<<"Added Element : ";
    //cout<<vector6[11]<<endl;
    //vector::emplace(12);//Add element by using emplace()
   // cout<<"Added Element : ";
    //cout<<vector6[12]<<endl;

    //Accessing element of the vector
    vector<int>vector7={1,2,3,4,5,76,8,9,0,789,89};
    cout<<"Element at index 4 :"<<vector7.at(4)<<endl;
    cout<<"Element at index 9 :"<<vector7.at(9)<<endl;
    cout<<"Element at index 8 :"<<vector7.at(8)<<endl;
    //Changing the vector element at some indexes
    vector<int>vector8={23,45,6,77,89,56,34,12};
    cout<<"Initial vector : ";
    for(int vector8 : vector8){
        cout<<vector8<<" ";
    }
    cout<<endl;
    vector8.at(6)=39;
    vector8.at(4)=88;
    cout<<"After changing the vector at 6 and 4 indexes : ";
    for(int vector8 : vector8){
        cout<<vector8<<" ";
    }
    cout<<endl;
    //Deleting the element from the vector from indexes 
    vector<int>vector9={4,5,6,7,8,8,9};
    cout<<"Intial Vector : ";
    for(int vector9 : vector9){
        cout<<vector9<<" ";
    }
    cout<<endl;
    vector9.pop_back();
    cout<<"After deleting the last element : ";
    for(int vector9 : vector9){
        cout<<vector9<<" ";
    }
    cout<<endl;
    //Some other functions
    vector<int>vector10={23,4,5,56,7,8,90,23,56};
    cout<<"Size of the vector : ";
    cout<<vector10.size()<<endl;
    cout<<"Front Element : ";
    cout<<vector10.front()<<endl;
    cout<<"Check that vector is empty or not  : ";
    cout<<vector10.empty()<<endl;
    cout<<"Capacity of a vector : ";
    cout<<vector10.capacity()<<endl;
    
    vector10.clear();
    cout<<"After clerring the vector : ";
   cout<<vector10.empty()<<endl;
    
    //Iterator in vector
    vector<int>vector11={2,3,4,5,6,7,8,9};
    vector<int>::iterator ite;
    ite=vector11.begin();
    cout<<"First element of the vector :  "<<*ite<<endl;
    ite=vector11.end()-1;
    cout<<"Last element of the vector : "<<*ite<<endl;
    cout<<"Iterated vector : ";
    for(vector<int>::iterator it = vector11.begin();it!=vector11.end();it++){
        cout<<*it<<" ";
    }

    return 0;

}