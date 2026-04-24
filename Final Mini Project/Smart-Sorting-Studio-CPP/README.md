# Smart Sorting Studio

**Smart Sorting Studio** is a robust educational and benchmarking application designed to compare and analyze the performance of various sorting algorithms on different datasets. 

## Features
* **Multiple Algorithms**: Implementations of Merge Sort, Quick Sort, Heap Sort, Counting Sort, Radix Sort, and Bucket Sort.
* **Real-World Datasets**: Test algorithms on different types of CSV data, such as Marks, Sales, and Logs.
* **Performance Metrics**: Accurately measures and reports:
  * Execution Time (ms)
  * Number of Comparisons
  * Number of Swaps
  * Algorithm Stability
* **Dual Execution Modes**:
  * **C++ CLI**: A fast, terminal-based tool for immediate results.
  * **Web Application**: A modern UI (React/Vite) powered by a Node.js backend.

## Technologies Used
* **Core Application**: C++
* **Web Frontend**: React.js, Vite
* **Web Backend**: Node.js

## How to Run

### 1. C++ Terminal Application
1. Compile the C++ files using a standard C++ compiler (e.g., MinGW/GCC):
   ```bash
   g++ main.cpp sorting_algorithms.cpp dataset_utils.cpp -o app
   ```
2. Run the executable:
   ```bash
   app.exe
   ```
3. Follow the on-screen prompts to select a dataset and a sorting algorithm.

### 2. Web Application
1. Ensure you have **Node.js** installed on your system.
2. First, ensure the web dependencies are installed (if not done previously, you might need to run `npm install` inside the `web/frontend` and `web/backend` folders).
3. Run the provided batch script to start both the backend API and frontend UI:
   ```cmd
   run_web.bat
   ```
4. The script will automatically open the web interface in your default browser.

## File Structure
* `main.cpp`, `sorting_algorithms.cpp`, `dataset_utils.cpp`: Core C++ logic and terminal UI.
* `web/`: Contains the frontend UI and backend API for the web version.
* `sample_*.csv`: Datasets used for sorting benchmarks.
* `run_web.bat`: Startup script for the web application.
