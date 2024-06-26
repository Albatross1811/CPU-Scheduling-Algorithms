# CPU Scheduling Algorithms

This project showcases the implementation of several CPU scheduling algorithms in C++, considering the arrival time of processes. These algorithms manage the execution order of processes to optimize performance metrics like turnaround time and waiting time. The implemented algorithms include:

* First Come First Served (FCFS)
* Shortest Job First (SJF)
* Round Robin (RR)
* Shortest Job Remaining First (SJRF)

Key features of the project:

- Consideration of process Arrival Time: Ensures that the scheduling decisions respect the order in which processes arrive.
- Capability to randomly generate process data: Provides flexibility to simulate various scenarios without manual data entry.
- Detailed display of process data: Outputs comprehensive information for each process, including Turn Around Time (TAT) and Waiting Time (WT), in a tabular format.
- Calculation of average metrics: Computes and displays the average Turn Around Time and Waiting Time, providing insight into the overall performance of each scheduling algorithm.

## First Come First Served (FCFS)

FCFS is one of the simplest scheduling algorithms where processes are attended to in the order they arrive. This algorithm is **non-preemptive**, meaning once a process starts its execution, it runs to completion without interruption. Processes are sorted by their arrival times and executed sequentially. The simplicity of FCFS makes it easy to implement, but it can lead to the "convoy effect," where short processes get stuck waiting behind long ones, increasing the average waiting time.

## Shortest Job First (SJF)

SJF scheduling selects the process with the shortest burst time for execution next, making it a highly efficient scheduling method. This algorithm is **non-preemptive**. Upon arrival, processes are enqueued, and the scheduler picks the one with the shortest burst time. By focusing on shorter tasks first, SJF reduces the average waiting time for processes. However, it requires accurate knowledge of the burst times in advance, which may not always be feasible.

## Round Robin (RR)

The Round Robin scheduling algorithm assigns each process a fixed time slice or quantum for execution, cycling through the processes in a fair manner. This algorithm is **preemptive**, meaning that after the time quantum expires, the currently running process is moved to the back of the queue, and the next process is given CPU time. This approach ensures that all processes receive a fair share of CPU time, reducing the risk of starvation for any single process. Round Robin is particularly effective in time-sharing systems where response time is crucial.

## Shortest Job Remaining First (SJRF)

SJRF is a **preemptive** version of the SJF algorithm. In this method, the process with the shortest remaining burst time is selected for execution. If a new process arrives with a shorter burst time than the currently running process, the CPU preempts the current process and switches to the new one. This continuous prioritization of the shortest jobs minimizes the waiting time for shorter processes and is optimal in terms of average waiting time. However, like SJF, it requires precise knowledge of burst times and can be complex to implement due to its preemptive nature.

# Procedure
1. Open the index.html file in your default web browser.
2. Select the number of processes.
3. Select the scheduling algorithm from the drop down list.
4. In case of Round Robin algorithm select thr time quantum.
5. Click on generate process inputs.
6. Either manually give values of arrival and burst time, or generate them randomly.
7. Run Scheduling Algorithm.

## Working Screenshots
![image](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/24233dd9-3b1a-45dd-8b69-d193739438f5)
![image](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/aceeea44-c686-4b81-99f2-230bc0e4676d)

# Key Takeaways

### 1. Algorithm Understanding
Gain practical knowledge of CPU scheduling algorithms:
- **FCFS** (First Come First Served)
- **SJF** (Shortest Job First)
- **RR** (Round Robin)
- **SJRF** (Shortest Job Remaining First)

Understand how each algorithm impacts system performance and scheduling efficiency.

### 2. Data Structures
Utilize arrays and objects to manage processes:
- Store attributes such as arrival time, burst time, completion time, turnaround time, and waiting time.

### 3. JavaScript Proficiency
Implement frontend (HTML/CSS) and backend (JavaScript) for:
- User interface (UI) interactions and updates.
- Algorithmic logic for CPU scheduling simulations.

### 4. Visualization Skills
Create Gantt charts dynamically using:
- CSS for styling and layout.
- JavaScript for dynamic content generation and visualization.

### 5. Project Management
Practice effective project management skills:
- Task organization, iteration planning, and implementation.
- Debugging, testing, and refining solutions.

### 6. Performance Analysis
Compare metrics such as:
- Turnaround time and waiting time across different scheduling algorithms.
- Understand the trade-offs and performance characteristics of each algorithm.

### 7. Problem-Solving
Handle edge cases and adapt solutions:
- Manage varying inputs and algorithm parameters effectively.
- Debug and optimize code for efficiency and correctness.
  
# References
  - https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/
  - https://www.youtube.com/playlist?list=PLBlnK6fEyqRitWSE_AyyySWfhRgyA-rHk

