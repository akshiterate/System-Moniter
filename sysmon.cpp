#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    ifstream statFile("/proc/stat");
    string line;
    if(statFile .is_open()){
        getline(statFile,line);
//        cout<<line;
    }
    else{
        cout<<"gay";
    }
    string label,user,nice,system,idle,iowait,irq,softirq,steal,guest,guest_nice;
    istringstream iss(line);
    iss >> label >> user >>  nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    cout<<"Label:"<<label<<endl;;
    cout<<"user:"<<user<<endl;
    cout<<"idle:"<<idle;
    return 0;
}