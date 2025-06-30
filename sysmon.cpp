#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

class Stats{
public:
    long user=0,nice=0,system=0,idle=0,iowait=0,irq=0,softirq=0,MemTotal=0,MemAvailable=0;

    long total() const{
       return user + nice + system + idle + iowait + irq + softirq;
    }

    long idleTime() const {
        return idle + iowait;
    }

    float rusage() const{
        if (MemTotal == 0) return 0;
        return (MemTotal - MemAvailable)/(float)MemTotal;
    }
    
};

Stats cpuRead(){
    ifstream statFile("/proc/stat");
    string line;
    Stats stats;
    if(statFile .is_open()){
        getline(statFile,line);
//        cout<<line;
    }
    else{
        cout<<"smth broke";
    }
    istringstream iss(line);
    string label;
    
    iss >> label >> stats.user >>  stats.nice >> stats.system >> stats.idle >> stats.iowait >> stats.irq >> stats.softirq;
    return stats;
}
Stats ramRead(){
    ifstream statFile("/proc/meminfo");
    string line;
    Stats stats;
    if(statFile.is_open()){
        while(getline(statFile,line)){
            istringstream iss(line);
            string key;
            long value;

            iss>>key>>value;

            if(key == "MemTotal:"){
                stats.MemTotal = value;
            }
            else if(key == "MemAvailable:"){
                stats.MemAvailable = value;
            }
            if (stats.MemTotal && stats.MemAvailable)
            break;

        }
    }
    else{
        cout<<"cant read ram";
    }
    cout << "DEBUG: MemTotal = " << stats.MemTotal << ", MemAvailable = " << stats.MemAvailable << endl;

    return stats;
}

int main(){
    while(true){
        Stats s1 = cpuRead();
        sleep(1);
        Stats s2 = cpuRead();
        long deltaTotal = s2.total() - s1.total();
       long deltaIdle  = s2.idleTime() - s1.idleTime();

        
        float cpuUsage = (deltaTotal - deltaIdle) / (float)deltaTotal * 100.0;

        Stats s3 = ramRead();
        float ramUsage = s3.rusage()*100.0;
        
        system("clear");
       cout<<"CPU Usage: "<<cpuUsage<<"% [";
       int bars = cpuUsage / 2;  // max 50 bars = 100%

        for (int i = 0; i < 50; ++i) {
            if (i < bars)
                cout << "█";
            else
                cout << "░";
        }
        cout << "]" << endl;
        cout << "RAM Usage: " << ramUsage << "% [";
        int ramBars = ramUsage / 2;
        for (int i = 0; i < 50; ++i) {
        if (i < ramBars)
            cout << "█";
        else
            cout << "░";
        }
        cout<<"]"<<endl;
        


    }
}