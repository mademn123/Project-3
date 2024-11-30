# Project-3

This project is a Task Scheduler application built using C++, Qt, and CLion. It allows users to manage tasks, add dependencies, visualize tasks in a graph, and generate schedules based on task priorities and dependencies. The application features a user-friendly GUI with support for task management, dependency handling, and interactive visualization.

Features
Add New Tasks: Input task details including name, due date, priority, description, and duration.

Manage Dependencies: Add or remove dependencies between tasks.

Generate Task Schedule: Automatically generate a schedule that respects task dependencies.

Task Visualization: Visualize tasks as nodes with edges representing dependencies.

Priority Graph: View the number of tasks by priority in a bar graph.

Task Sorting: Sort tasks by due date for better management.

Requirements
Qt 5 or 6 

CMake 

CLion IDE 

C++14

Usage
Add Tasks: Enter the task name, due date, priority, description, and duration. Click Add Task.

Add Dependencies: Select two tasks and create dependencies between them.

Visualize Tasks: Click Visualize Tasks to see a graphical representation of the tasks and their dependencies.

Generate Schedule: Click Generate Schedule to see a suggested order of task completion.

Save and Load Tasks: Save your tasks to a file or load existing tasks.

View Priority Graph: Click Show Priority Graph to visualize the number of tasks by priority.

File Structure
main.cpp: Entry point of the application.

Task.h/Task.cpp: Defines the Task structure and operations for adding/removing dependencies.

TaskItem.h/TaskItem.cpp: Represents the graphical item used for visualizing tasks.

TaskScheduler.h/TaskScheduler.cpp: Contains the main logic and GUI for the application.

Requirements for Running the Code
Ensure that Qt is properly installed and the environment variable Qt_DIR is set to the correct path.

Use a compatible compiler (e.g., MSVC for Windows, GCC for Linux/macOS) that matches the Qt version.

Make sure CMakeLists.txt is correctly configured with the appropriate paths.
