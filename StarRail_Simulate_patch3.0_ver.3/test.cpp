
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define F first
#define S second
#define DMG_CAL 12
#define K_const 10000
using std::cout ;
#include"Setup.cpp"
class Super{
    public:
    int a;
    Super(){
        cout<<"Hello"<<endl;
    }
    Super(int s){
        cout<<"Hello1"<<endl;
    }
    static void print(){
        cout<<555;
    }
    void print1(){
        cout<<5551;
    }
};
class Sub : public Super{
    public:
    Sub(){
        Super();
        cout<<"dsd"<<endl;
    }
    Sub(int s){
        Super(1);
        cout<<"dsd1"<<endl;
    }
    static void print(){
        cout<<444;
    }
};
int main() {
    // Loop through all possible values for the first unit
    for (int x = 0; x <= 20; x++) {
        for (int y = 0; y <= 20; y++) {
            int z = 20 - x - y; // Calculate the third unit to ensure the sum is 20
            
            // Check if z is within the valid range
            if (z >= 0 && z <= 20) {
                cout << "(" << x << ", " << y << ", " << z << ")" << endl;
            }
        }
    }

    return 0;
}
