# Dev Notes

## Reading /proc/stat

- `/proc/stat` contains CPU statistics since boot
- We access it using `ifstream` in C++:
  ```cpp
  ifstream statFile("/proc/stat");
  getline(statFile, line);

- We parse the line using istringstream (from <sstream>):
```cpp
    istringstream iss(line);
    string label;
    long user, nice, system, idle;
    iss >> label >> user >> nice >> system >> idle;