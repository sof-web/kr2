#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class MinBinaryHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l] < heap[smallest])
            smallest = l;
        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    bool isEmpty() const {
        return heap.empty();
    }

    int getMin() const {
        if (isEmpty())
            throw runtime_error("Heap is empty");
        return heap[0];
    }

    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (isEmpty())
            throw runtime_error("Heap is empty");

        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return root;
    }

    void print() const {
        if (isEmpty()) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Heap: ";
        for (int val : heap)
            cout << val << " ";
        cout << "\n";
    }
};

int main() {
    MinBinaryHeap heap;
    int choice, value;

    cout << "Binary Min-Heap Operations:\n";
    while (true) {
        cout << "\n1. Insert\n2. Extract Min\n3. Get Min\n4. Print Heap\n5. Exit\n";
        cout << "Choose operation: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> value;
                    heap.insert(value);
                    cout << "Inserted " << value << "\n";
                    break;
                case 2:
                    value = heap.extractMin();
                    cout << "Extracted min: " << value << "\n";
                    break;
                case 3:
                    value = heap.getMin();
                    cout << "Current min: " << value << "\n";
                    break;
                case 4:
                    heap.print();
                    break;
                case 5:
                    cout << "Exiting.\n";
                    return 0;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}
