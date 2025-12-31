 Scalable Task Scheduler (C++)

This project is a simple priority-based task scheduler implemented in C++.
It allows tasks to be added, cancelled, updated, and executed based on their priority
through an interactive, menu-driven console program.

The goal of this project was to practice data structures and understand how
priority-based scheduling works internally.

 What the Project Does
- Lets the user add tasks with a task ID and priority
- Always executes the task with the highest priority first
- Allows cancelling tasks before execution
- Supports updating the priority of an existing task
- Runs interactively using a console menu

 Data Structures Used
- Priority Queue (Heap):  
  Used to select the next task to execute based on priority
- Hash Map:  
  Used to store active tasks and allow fast lookup, updates, and cancellation


Design Approach
The scheduler uses a lazy deletion approach.
When a task is cancelled or its priority is changed, it is marked invalid instead
of being immediately removed from the heap. Invalid tasks are skipped during execution.

This keeps heap operations efficient and avoids unnecessary reordering.


 Time Complexity
- Add task: O(log n)
- Execute task: O(log n)
- Cancel task: O(1)
- Update task priority: O(log n)

 User Interaction
The program runs in a loop and shows a menu with options to:
1. Add a task
2. Cancel a task
3. Change task priority
4. Execute the next task
5. Exit the program

All operations can be performed while the program is running.

How to Run
Compile and run the program using a standard C++ compiler.

Example:
g++ main.cpp -o scheduler
./scheduler

