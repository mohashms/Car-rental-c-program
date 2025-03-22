#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits> // For INT_MAX
using namespace std;

// PART (A) - Data Optimization


// Binary Search (works on sorted arrays)
int binarySearch(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1; // Target not found
}

// Merge Sort (Divides, sorts, and merges)
void merge(vector<int> &arr, int left, int mid, int right) {
    vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] < rightPart[j]) arr[k++] = leftPart[i++];
        else arr[k++] = rightPart[j++];
    }
    while (i < leftPart.size()) arr[k++] = leftPart[i++];
    while (j < rightPart.size()) arr[k++] = rightPart[j++];
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Task Scheduler (Min-Heap for priority-based processing)
class TaskScheduler {
private:
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
public:
    void addTask(int priority, string task) {
        pq.push({priority, task});
    }
    void processTask() {
        if (!pq.empty()) {
            cout << "Processing Task: " << pq.top().second << endl;
            pq.pop();
        } else {
            cout << "No tasks to process.\n";
        }
    }
};

// Hash Table for quick key-value storage
class DataStorage {
private:
    unordered_map<string, string> data;
public:
    void store(string key, string value) {
        data[key] = value;
    }
    string retrieve(string key) {
        return data.count(key) ? data[key] : "Not Found";
    }
};

// Dijkstra's Algorithm for shortest path
void dijkstra(unordered_map<char, unordered_map<char, int>> &graph, char start) {
    unordered_map<char, int> distances;
    for (auto &node : graph) distances[node.first] = INT_MAX;
    distances[start] = 0;

    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        char currNode = pq.top().second;
        pq.pop();

        for (auto &neighbor : graph[currNode]) {
            int newDist = currDist + neighbor.second;
            if (newDist < distances[neighbor.first]) {
                distances[neighbor.first] = newDist;
                pq.push({newDist, neighbor.first});
            }
        }
    }

    cout << "Shortest Paths from " << start << ":\n";
    for (auto &d : distances) {
        cout << "To " << d.first << ": " << d.second << endl;
    }
}

// PART (B) - Order Processing System

// Linked List Node for Queue
class OrderNode {
public:
    int orderID;
    string customerName;
    OrderNode* next;
    OrderNode(int id, string name) : orderID(id), customerName(name), next(nullptr) {}
};

// Queue Using Linked List
class OrderQueue {
private:
    OrderNode* front;
    OrderNode* rear;

public:
    OrderQueue() : front(nullptr), rear(nullptr) {}

    // Add an order to the queue
    void addOrder(int orderID, string customerName) {
        OrderNode* newOrder = new OrderNode(orderID, customerName);
        if (!rear) front = rear = newOrder;
        else {
            rear->next = newOrder;
            rear = newOrder;
        }
        cout << "Order " << orderID << " added for " << customerName << ".\n";
    }

    // Cancel an order by ID
    void cancelOrder(int orderID) {
        if (!front) {
            cout << "No orders in queue.\n";
            return;
        }

        OrderNode *temp = front, *prev = nullptr;
        while (temp && temp->orderID != orderID) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Order " << orderID << " not found.\n";
            return;
        }

        if (prev) prev->next = temp->next;
        else front = temp->next;

        if (temp == rear) rear = prev;
        delete temp;

        cout << "Order " << orderID << " cancelled.\n";
    }

    // Display all pending orders
    void displayOrders() {
        if (!front) {
            cout << "No pending orders.\n";
            return;
        }
        cout << "Pending Orders:\n";
        for (OrderNode* temp = front; temp; temp = temp->next)
            cout << "Order ID: " << temp->orderID << ", Customer: " << temp->customerName << endl;
    }
};


// TESTING THE IMPLEMENTATION


int main() {
    // (A) Data Optimization Example
    vector<int> numbers = {20, 5, 3, 50, 2, 1};
    mergeSort(numbers, 0, numbers.size() - 1);

    cout << "Sorted Numbers: ";
    for (int num : numbers) cout << num << " ";
    cout << endl;

    cout << "Binary Search (Finding 5): " << binarySearch(numbers, 5) << endl;

    // Task Scheduler Example
    TaskScheduler scheduler;
    scheduler.addTask(2, "Process Order");
    scheduler.addTask(1, "Ship Order");
    scheduler.processTask();

    // Hash Table Example
    DataStorage storage;
    storage.store("user1", "Alice");
    cout << "Retrieve user1: " << storage.retrieve("user1") << endl;

    // Graph Example - Dijkstra's Algorithm
    unordered_map<char, unordered_map<char, int>> graph = {
        {'A', {{'B', 1}, {'C', 4}}},
        {'B', {{'A', 1}, {'C', 2}, {'D', 5}}},
        {'C', {{'A', 4}, {'B', 2}, {'D', 1}}},
        {'D', {{'B', 5}, {'C', 1}}}
    };
    dijkstra(graph, 'A');

    // (B) Order Processing System Example
    OrderQueue queue;
    queue.addOrder(101, "Alice");
    queue.addOrder(102, "Bob");
    queue.displayOrders();
    queue.cancelOrder(102);
    queue.displayOrders();

    return 0;
}
