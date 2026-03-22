# SnapeAV: Endpoint Protection Utility 🛡️

A lightweight system monitoring tool developed in C++ using Windows API. Designed to enforce security policies by managing running processes and preventing unauthorized software execution.

## ✨ Key Features
* **Real-time Monitoring:** Low-level process scanning using `CreateToolhelp32Snapshot`.
* **Blacklist Enforcement:** Automatically terminates forbidden processes (calculators, miners, unauthorized tools).
* **Memory Efficient:** Optimized polling loop with minimal CPU overhead.
* **Security Focused:** Implements basic integrity checks for system stability.

## 🛠 Tech Stack
* **Language:** C++17
* **Platform:** Windows (WinAPI, TlHelp32)
* **Build System:** MinGW / MSVC

## 📂 Project Structure
* `/src` — Core source code (`main.cpp`).
* `blacklist.txt` — Example configuration file for process filtering.
* `.gitignore` — Standard C++ exclusion rules.

## 🚀 How it Works
The utility iterates through the system process tree, normalizes process names, and compares them against a configurable `blacklist.txt`. Upon detection, it acquires a handle with `PROCESS_TERMINATE` rights and safely closes the target application.

## ⚖️ License
This project is licensed under the MIT License.
