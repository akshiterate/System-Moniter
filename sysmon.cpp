#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

class Stats{
public:
    long user,nice,system,idle,iowait,irq,softirq;

    long total() const{
       return user + nice + system + idle + iowait + irq + softirq;
    }

    long idleTime() const {
        return idle + iowait;
    }
};

Stats read(){
    ifstream statFile("/proc/stat");
    string line;
    Stats stats;
    if(statFile .is_open()){
        getline(statFile,line);
//        cout<<line;
    }
    else{
        cout<<"gay";
    }
    istringstream iss(line);
    string label;
    
    iss >> label >> stats.user >>  stats.nice >> stats.system >> stats.idle >> stats.iowait >> stats.irq >> stats.softirq;
    return stats;
}

int main(){
    Stats s1 = read();
    sleep(1);
    Stats s2 = read();
    long deltaTotal = s2.total() - s1.total();
    long deltaIdle  = s2.idleTime() - s1.idleTime();

    
    float cpuUsage = (deltaTotal - deltaIdle) / (float)deltaTotal * 100.0;
    cout<<"Usage: "<<cpuUsage<<"%"<<endl;

}