#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    // Вспомогательные функции для работы с индексами
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    // Просеивание вверх (для вставки)
    void heapifyUp(int i) {
        while (i > 0 && heap[i] < heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Просеивание вниз (для удаления корня)
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        int n = heap.size();

        if (left < n && heap[left] < heap[smallest])
            smallest = left;

        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Проверка на пустоту
    bool isEmpty() const {
        return heap.empty();
    }

    // Вставка элемента
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    // Извлечение минимального элемента
    int extractMin() {
        if (isEmpty())
            throw runtime_error("Heap is empty");

        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!isEmpty())
            heapifyDown(0);

        return root;
    }

    // Показать текущую кучу
    void display() const {
        if (isEmpty()) {
            cout << "Heap is empty.\n";
            return;
        }
        for (int val : heap)
            cout << val << " ";
        cout << endl;
    }
};

int main() {
    MinHeap heap;
    int choice, value;

    cout << "=== Min-Heap Implementation in C++ ===\n";

    while (true) {
        cout << "\n1. Insert element\n";
        cout << "2. Extract minimum element\n";
        cout << "3. Display heap\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                cout << "Inserted " << value << " into heap.\n";
                break;
            case 2:
                try {
                    int minVal = heap.extractMin();
                    cout << "Extracted minimum element: " << minVal << endl;
                } catch (const runtime_error& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 3:
                cout << "Current heap (array representation): ";
                heap.display();
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
