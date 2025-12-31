// Scalable Task Scheduler
// Language: C++
// Description: Priority-based task scheduling using heap and hash map
#include <iostream>
#include <queue>
#include <unordered_map>
#include <ctime>

using namespace std;

class Task {
public:
    int id;
    int priority;
    long long createdAt;
    bool valid;

    Task(int taskId, int p)
        : id(taskId), priority(p), createdAt(time(nullptr)), valid(true) {}
};

struct SchedulerOrder {
    bool operator()(const Task* a, const Task* b) const {
        if (a->priority == b->priority) {
            return a->createdAt > b->createdAt;
        }
        return a->priority < b->priority;
    }
};

class PriorityTaskScheduler {
private:
    priority_queue<Task*, vector<Task*>, SchedulerOrder> queue;
    unordered_map<int, Task*> index;

    void cleanup() {
        while (!queue.empty() && !queue.top()->valid) {
            queue.pop();
        }
    }

public:
    void add(int id, int priority) {
        if (index.find(id) != index.end()) {
            return;
        }
        Task* t = new Task(id, priority);
        queue.push(t);
        index[id] = t;
    }

    void cancel(int id) {
        auto it = index.find(id);
        if (it == index.end()) {
            return;
        }
        it->second->valid = false;
        index.erase(it);
    }

    void changePriority(int id, int newPriority) {
        auto it = index.find(id);
        if (it == index.end()) {
            return;
        }
        it->second->valid = false;
        Task* updated = new Task(id, newPriority);
        queue.push(updated);
        index[id] = updated;
    }

    Task* next() {
        cleanup();
        if (queue.empty()) {
            return nullptr;
        }
        return queue.top();
    }

    void execute() {
        Task* t = next();
        if (!t) {
            cout << "No task available\n";
            return;
        }
        cout << "Executing task " << t->id
             << " with priority " << t->priority << "\n";
        t->valid = false;
        index.erase(t->id);
        queue.pop();
    }

    bool empty() const {
        return index.empty();
    }
};
int main() {
    PriorityTaskScheduler scheduler;
    int choice;

    while (true) {
        cout << "\n--- Task Scheduler Menu ---\n";
        cout << "1. Add Task\n";
        cout << "2. Cancel Task\n";
        cout << "3. Change Task Priority\n";
        cout << "4. Execute Next Task\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, priority;
            cout << "Enter task id: ";
            cin >> id;
            cout << "Enter priority: ";
            cin >> priority;
            scheduler.add(id, priority);
            cout << "Task added\n";
        }
        else if (choice == 2) {
            int id;
            cout << "Enter task id to cancel: ";
            cin >> id;
            scheduler.cancel(id);
            cout << "Task cancelled (if it existed)\n";
        }
        else if (choice == 3) {
            int id, newPriority;
            cout << "Enter task id: ";
            cin >> id;
            cout << "Enter new priority: ";
            cin >> newPriority;
            scheduler.changePriority(id, newPriority);
            cout << "Priority updated\n";
        }
        else if (choice == 4) {
            scheduler.execute();
        }
        else if (choice == 5) {
            cout << "Exiting scheduler\n";
            break;
        }
        else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}



