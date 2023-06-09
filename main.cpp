#include <iostream>
#include <ctime>
#include "funciones.h"

using namespace  std;

unsigned t0, t1;

const int num = 36500; // 36500

void intercambiar(string& x, string& y) {
    string aux = x;
    x = y;
    y = aux;
}

class comeTacos {
public:
    int noDatos = num;
    
    int tacos[num]{};
    double tiemposTotales[9][5]{};
    string metodos[9] = {"Bubble", "Selection", "Insertion", "Counting", "Shell", "Quick", "Heap", "Merge", "Radix"};
    double promedios[9];

public:
    void generarArreglo();
    void imprimirArreglo();
    void ordenarTiempos();
    void imprimirTiempos();
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void countingSort();
    void shellSort();
    void quickSort(int arr[], int start, int end);
    void heapSort();
    void mergeSort(int arr[], int l, int r);
    void radixSort();

};

void comeTacos::generarArreglo() {
    srand(time(nullptr));
    for (int i = 0; i < noDatos; i++) {
            tacos[i] = (rand() % 11);
    }
}

void comeTacos::imprimirArreglo() {
    cout << "Arreglo: " << endl;
    for (int i = 0; i < noDatos; i++) {
        cout << tacos[i] << " ";
    }
}

void comeTacos::ordenarTiempos(){
    bool interruptor = true;
    int pasada, j;
    for (pasada = 0; pasada < 9 - 1 && interruptor; pasada++) {
        interruptor = false;
        for (j = 0; j < 9 - pasada - 1; j++)
            if (promedios[j] > promedios[j + 1]) {
                interruptor = true;
                intercambiarDouble(promedios[j], promedios[j + 1]);
                intercambiar(metodos[j], metodos[j + 1]);
            }
    }
    cout << "Tiempos ordenados en base a sus promedios: " << endl;
    for(int i = 0; i < 9; i++) {
        cout << metodos[i] << ": " << promedios[i] << endl;
    }
}

void comeTacos::imprimirTiempos() {
    double suma = 0;
    bool igual = true;
    cout << "Tiempos Totales: " << endl;
    for (int i = 0; i < 9; i++) {
        igual = true;
        suma = 0;
        cout << metodos[i] << ": ";
        for(int j = 0; j < 5; j++){
            if(tiemposTotales[j] == tiemposTotales[j+1] && igual) igual = true;
            else igual = false;
            cout << tiemposTotales[i][j] << endl;
            suma += tiemposTotales[i][j];
        }
        if(igual) cout << "No hubo cambios." << endl;
        else cout << "Hubo cambios." << endl;
        promedios[i] = suma/5.0;
    }
}

void comeTacos::bubbleSort() {
    bool interruptor = true;
    int pasada, j;
    for (pasada = 0; pasada < noDatos - 1 && interruptor; pasada++) {
        interruptor = false;
        for (j = 0; j < noDatos - pasada - 1; j++)
            if (tacos[j] > tacos[j + 1]) {
                interruptor = true;
                // int aux = tacos[j];
                // tacos[j] = tacos[j + 1];
                // tacos[j + 1] = aux;
                intercambiarArray(tacos[j], tacos[j + 1]);
            }
    }

}

void comeTacos::selectionSort() {
    for(int i = 0; i < noDatos; i++) {
        int min = i;
        for (int j = i + 1; j < noDatos; j++) {
            if (tacos[j] < tacos[min]) {
                min = j;
            }
        }
        int aux = tacos[i];
        tacos[i] = tacos[min];
        tacos[min] = aux;
    }
}

void comeTacos::insertionSort() {
    for (int i = 0; i < noDatos; i++) {
        int pos = i;
        int aux = tacos[i];
        while ((pos > 0) && (tacos[pos - 1] > aux)) {
            tacos[pos] = tacos[pos - 1];
            pos--;
        }
        tacos[pos] = aux;
    }
}

void comeTacos::countingSort() {
    int size = noDatos;
    int output[size];
    int count[11];
    int max = tacos[0];
    for (int i = 1; i < size; i++) {
        if (tacos[i] > max)
            max = tacos[i];
    }
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        count[tacos[i]]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        output[count[tacos[i]] - 1] = tacos[i];
        count[tacos[i]]--;
    }
    for (int i = 0; i < size; i++) {
        tacos[i] = output[i];
    }
}

void comeTacos::shellSort() {
    for (int gap = noDatos/2; gap > 0; gap /= 2) {
        for (int i = gap; i < noDatos; i++) {
            int temp = tacos[i];
            int j;
            for (j = i; j >= gap && tacos[j - gap] > temp; j -= gap){
                tacos[j] = tacos[j - gap];
            }
            tacos[j] = temp;
        }
    }
}

void comeTacos::quickSort(int arr[], int start, int end) {
    // t0 = clock(); 
	if (start >= end)
		return;
	int p = partition(arr, start, end);
	quickSort(arr, start, p - 1);
	quickSort(arr, p + 1, end);
}


void comeTacos::heapSort() {
    for (int i = noDatos / 2 - 1; i >= 0; i--) {
        heapify(tacos, noDatos, i);
    }
    for (int i = noDatos - 1; i >= 0; i--) {
        swap(tacos[0], tacos[i]);
        heapify(tacos, i, 0);
    }
}

void comeTacos::mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void comeTacos::radixSort() {
    int m = getMax(tacos, noDatos); 
    for (int exp = 1; m / exp > 0; exp *= 10)
        CountSort(tacos, noDatos, exp);
}

int main() {
    comeTacos degustador1;
    //Bubble sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.bubbleSort();
        t1 = clock();
        degustador1.tiemposTotales[0][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Selection sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.selectionSort();
        t1 = clock();
        degustador1.tiemposTotales[1][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Insertion sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.insertionSort();
        t1 = clock();
        degustador1.tiemposTotales[2][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Counting sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.countingSort();
        t1 = clock();
        degustador1.tiemposTotales[3][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Merge sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.mergeSort(degustador1.tacos, 0, degustador1.noDatos);
        t1 = clock();
        degustador1.tiemposTotales[4][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Radix sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.radixSort();
        t1 = clock();
        degustador1.tiemposTotales[5][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Shell sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.shellSort();
        t1 = clock();
        degustador1.tiemposTotales[6][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Heap sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.heapSort();
        t1 = clock();
        degustador1.tiemposTotales[7][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Quick sort
    for(int i = 0; i < 5; i++){
        degustador1.generarArreglo();
        t0 = clock(); 
        degustador1.quickSort(degustador1.tacos, 0, degustador1.noDatos);
        t1 = clock();
        degustador1.tiemposTotales[8][i] = (double(t1-t0)/CLOCKS_PER_SEC);
    }
    //Imprimir los tiemposTotales
    degustador1.imprimirTiempos();
    degustador1.ordenarTiempos();
}