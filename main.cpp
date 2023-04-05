#include <iostream>
using namespace  std;

class tacosComidos {
private:
    int noDatos = 20000;
    int tacos[];
public:
    void generarArreglo();
    void imprimirArreglo();
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void countingSort();
    void shellSort();
    void quickSort();
    void heapSort();
    void mergeSort();
    void radixSort();
};

void tacosComidos::generarArreglo() {
    srand(time(nullptr));

    for (int i = 0; i < noDatos; i++) {
            tacos[i] = (rand() % 10 + 1);
    }
}

void tacosComidos::imprimirArreglo() {
    for (int i = 0; i < noDatos; i++) {
        cout << tacos[i];
    }
}

void tacosComidos::bubbleSort() {

}

void tacosComidos::selectionSort() {

}

void tacosComidos::insertionSort() {

}

void tacosComidos::countingSort() {

}

void tacosComidos::shellSort() {

}

void tacosComidos::quickSort() {

}

void tacosComidos::heapSort() {

}

void tacosComidos::mergeSort() {

}

void tacosComidos::radixSort() {

}

int main() {
    int h;
}
