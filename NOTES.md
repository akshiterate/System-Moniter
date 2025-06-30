# SysMon Notes

A log of all the bugs, questions, and discoveries made while building this system monitor.

---

## Project Start

- *Can I use Code Runner and still run C++ in WSL?*
  - Yes, but you need to make sure Code Runner is using the **WSL path** and not your Windows compiler. I eventually just used `code .` in WSL to launch VS Code in the right environment.

---

## CPU Usage (from `/proc/stat`)

- *What does `cat /proc/stat | head -n 1` show?*
  - Shows the first line of `/proc/stat`, which starts with `cpu` followed by 10+ numbers:
    - `user nice system idle iowait irq softirq steal guest guest_nice`

- *Why does user time change even when I’m the only user?*
  - It’s not tied to your login user — it’s system time spent in "user mode" (all processes).

- *Initial file read gave blank output.*
  - Fixed by checking `statFile.is_open()` and reading with `getline()`.

- *Splitting line in C++?*
  - Used `istringstream` to tokenize the string just like `split()`.

---

## Live CPU Usage Calculation

- Formula used:
  ```cpp
  (deltaTotal - deltaIdle) / (float)deltaTotal * 100.0;
  ```

## RAM Usage (from `/proc/meminfo`)

- *RAM usage showed absurdly high or negative values.*
  - Root cause: `MemAvailable` was never set → uninitialized `long` → garbage.
  - Fixed by:
    - Initializing all fields in `Stats` with `= 0`
    - Only reading `key` and `value` (skip unit safely)
    - Ensuring key matches `"MemTotal:"` and `"MemAvailable:"` (with colon)

---

## Final Result

- CPU and RAM usage now update every second
- Shows clean usage bars with `█` and `░`
- Outputs like:

  ```
  CPU Usage: 3.1%  [██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░]
  RAM Usage: 41.6% [█████████████████████░░░░░░░░░░░░░░░░░░░░░░░░]
  ```

---

## What I Learned

- Parsing Linux system files using C++
- Realtime performance monitoring logic
- Difference between user/system/idle time
- Handling string splitting with `istringstream`
- Importance of initializing class members in C++

---

## Library Confusions & Clarifications

- *Which header do I need for file reading?*
  - `#include <fstream>` — for `ifstream`, used to read `/proc/stat` and `/proc/meminfo`.

- *What about string manipulation and split?*
  - `#include <string>` — for `std::string`
  - `#include <sstream>` — for `std::istringstream` which lets us "split" strings in C++.

- *Why do we use `using namespace std;`?*
  - It helps avoid writing `std::` repeatedly. But in bigger projects, it's better to avoid it in headers to prevent name collisions.

- *How do I sleep in C++?*
  - `#include <unistd.h>` — for `sleep(seconds)` in Linux/WSL.

---

## General Lessons

- Always initialize class variables to prevent garbage values.
- Use `getline()` to safely read entire lines from files.
- Use `istringstream` to split a string based on whitespace.
- When working with system files like `/proc`, verify field names carefully (`MemAvailable:` with colon!).
