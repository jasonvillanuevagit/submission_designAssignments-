#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void print(vector <int> const &a) {
   for(int i=0; i < a.size(); i++)
      cout << a.at(i) << ' ';
}

int main()
{
    int array[200];
    for(int i=0; i<200;i++){
        array[i] = i+26;
    }
    
    vector<int> divboth;
    vector<int> div7;
    vector<int> div3;
    vector<int> divnone;
    
    for(int i=0; i<200; i++){
        if(array[i]%7==0 && array[i]%3){
            //cout<<"both"<<endl;
            divboth.push_back(array[i]);
        }
        else if(array[i]%7==0){
            //cout<<"seven"<<endl;
            div7.push_back(array[i]);
        }
        else if(array[i]%3==0){
            //cout<<"three"<<endl;
            div3.push_back(array[i]);
        }
        else{divnone.push_back(array[i]);}
            //cout<<array[i]<<endl;}
            
    }
    
    int bothsum = accumulate(divboth.begin(), divboth.end(), 0);
    int sevsum = accumulate(div7.begin(), div7.end(), 0);
    int threesum = accumulate(div3.begin(), div3.end(), 0);
    int nonesome = accumulate(divnone.begin(), divnone.end(), 0);
    
    cout<<"Div by 7\n ";
    print(div7);
    cout<<endl;
    cout<<"sum div by 7 = "<<sevsum<<endl;
    cout<<"Div by 3\n ";
    print(div3);
    cout<<endl;
    cout<<"sum div by 3 = "<<threesum<<endl;
    cout<<"Div by both\n ";
    print(divboth);
    cout<<endl;
    cout<<"sum div by both = "<<bothsum<<endl;
    cout<<"Div by none\n ";
    print(divnone);
    cout<<endl;
    cout<<"sum div by non = "<<nonesome<<endl;
    return 0;
}
