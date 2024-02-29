#include<iostream>
#include <cstdlib>
using namespace std;

int main(int argc,char *argv []){
    
    double sum;
    if (argc==1)
    {
        cout<< "Please input numbers to find average.";
    } else {
        cout<< "---------------------------------\n";
        for (int i = 1; i < argc; i++)
        {
            double num = atof(argv[i]);
            sum += num;
        }
        double average = sum/(argc-1);
        cout << "Average of " << argc-1 << " numbers = " << average;
        cout<< "\n---------------------------------";
    }

    return 0;

}
