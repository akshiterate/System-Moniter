# SysMon++

SysMon++ is a lightweight terminal-based system resource monitor written in C++ for Linux systems. It provides real-time CPU and RAM usage statistics by parsing information from the /proc filesystem.

## Features

- Live CPU usage monitoring based on /proc/stat
- RAM usage calculation using /proc/meminfo
- Text-based progress bars for visual clarity
- Clean, simple terminal interface
- Built using only standard C++ libraries

## How It Works

### CPU Usage

CPU statistics are retrieved from `/proc/stat`. The application reads CPU times at two different intervals (1 second apart) and calculates the usage percentage using the formula:

```
CPU Usage = (Delta Total Time - Delta Idle Time) / Delta Total Time * 100
```

### RAM Usage

Memory statistics are read from `/proc/meminfo`. The program parses `MemTotal` and `MemAvailable` to compute:

```
RAM Usage = (MemTotal - MemAvailable) / MemTotal * 100
```

## Build and Run

### Prerequisites

- A Linux environment (e.g., Ubuntu, WSL)
- g++ compiler

### Compile

```bash
g++ sysmon.cpp -o sysmon
```

### Run

```bash
./sysmon
```

This will display a continuously updating view of CPU and RAM usage in the terminal.

## File Structure

- `sysmon.cpp` — Main program source file
- `notes.md` — Development log and learning journal
- `README.md` — Project overview and setup instructions

## Potential Enhancements

- Add support for process monitoring
- Improve UI with `ncurses` for better formatting
- Export usage statistics to log files
- Display system uptime and swap usage

