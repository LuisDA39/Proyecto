#include <iostream>
using namespace  std;

int partition(int arr[], int start, int end) {
	int pivot = arr[start];
	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);
	int i = start, j = end;
	while (i < pivotIndex && j > pivotIndex) {
		while (arr[i] <= pivot) {
			i++;
		}
		while (arr[j] > pivot) {
			j--;
		}
		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}
	return pivotIndex;
}

class comeTacos {
public:
    int noDatos = 365;
    int tacos[365]{};
    unsigned tiempos[9]{};

public:
    void generarArreglo();
    void imprimirArreglo();
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void countingSort();
    void shellSort();
    void quickSort(int arr[], int start, int end);
    void heapSort();
    void mergeSort();
    void radixSort();

};

void comeTacos::generarArreglo() {
    srand(time(nullptr));

    for (int i = 0; i < noDatos; i++) {
            tacos[i] = (rand() % 10 + 1);
    }
}

void comeTacos::imprimirArreglo() {
    for (int i = 0; i < noDatos; i++) {
        cout << tacos[i] << " ";
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
                int aux = tacos[j];
                tacos[j] = tacos[j + 1];
                tacos[j + 1] = aux;
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
	if (start >= end)
		return;
	int p = partition(arr, start, end);
	quickSort(arr, start, p - 1);
	quickSort(arr, p + 1, end);
}


void comeTacos::heapSort() {

}

void comeTacos::mergeSort() {

}

void comeTacos::radixSort() {

}

int main() {
    comeTacos degustador1;

    cout << "Tacos comidos al dia desordenados: " << endl;

    degustador1.generarArreglo();
    degustador1.imprimirArreglo();

    cout <<endl << "Tacos comidos al dia ordenados: " << endl;
    //Prueba de quick sort
    int size = sizeof(degustador1.tacos)/sizeof(degustador1.tacos[0]);
    degustador1.quickSort(degustador1.tacos, 0, size);
    degustador1.imprimirArreglo();
}
