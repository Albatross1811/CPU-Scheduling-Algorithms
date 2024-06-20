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

## Working Screenshots
![Screenshot 2024-06-20 113951](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/e4bac760-7c76-4042-8bba-be8601a64e77)
![image](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/1bfdce69-1217-42df-a26a-90f80d4402d5)
![image](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/48ada044-217a-46e0-a785-112108a9800f)
![image](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/69208eea-067d-427b-a26d-c865309f329d)
![image](https://github.com/Albatross1811/CPU-Scheduling-Algorithms/assets/173333540/d625396b-a338-4a3c-b5f6-1eda043582f9)

# Key Takeaways from This Project

1. **Understanding Scheduling Algorithms:**
   - Gained knowledge of various CPU scheduling algorithms, including FCFS, SJF, RR, and SJRF.
   - Differentiated between preemptive and non-preemptive methods.

2. **Practical Implementation:**
   - Developed skills in implementing algorithms in C++ using data structures like queues and maps.

3. **Performance Analysis:**
   - Analyzed and compared metrics such as Turn Around Time and Waiting Time for each algorithm.

4. **Handling Random Data:**
   - Implemented functionality for generating random process data to simulate various scenarios.

5. **Code Organization:**
   - Emphasized clean, modular code for better readability and maintenance.

6. **Simulation of Real-World Scenarios:**
   - Simulated real-world process scheduling, providing insights into CPU resource management in operating systems.
  
# References
  - https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/
  - https://www.youtube.com/playlist?list=PLBlnK6fEyqRitWSE_AyyySWfhRgyA-rHk

