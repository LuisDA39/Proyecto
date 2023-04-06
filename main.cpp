#include <iostream>
#include <ctime>
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

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

int getMax(int arr[], int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)  mx = arr[i];
    return mx;
}

void CountSort(int arr[], int n, int exp){
    int output[n];
    int i, count[10] = {};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

class comeTacos {
public:
    int noDatos = 36500;
    unsigned t0, t1;
    int tacos[36500]{};
    double tiempos[9]{};
    string metodos[9] = {"Bubble", "Selection", "Insertion", "Counting", "Shell", "Quick", "Heap", "Merge", "Radix"};

public:
    void generarArreglo();
    void imprimirArreglo();
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
    for (int i = 0; i < noDatos; i++) {
        cout << tacos[i] << " ";
    }
}

void comeTacos::imprimirTiempos() {
    for(int i = 0; i < 9 ; i++){
        int min = i;
        for(int j = i + 1; j < 9; j++){
            if(tiempos[j] < tiempos[min]){
                min = j;
            }
        }
        string auxmetodos = metodos[i];
        metodos[i] = metodos[min];
        metodos[min] = auxmetodos;
        double auxtiempos = tiempos[i];
        tiempos[i] = tiempos[min];
        tiempos[min] = auxtiempos;
    }

    for (int i = 0; i < 9; i++) {
        cout << metodos[i] << ": ";
        cout << tiempos[i] << endl;
    }
}

void comeTacos::bubbleSort() {
    t0 = clock(); 

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

    t1 = clock();
    tiempos[0] = (double(t1-t0)/CLOCKS_PER_SEC);

}

void comeTacos::selectionSort() {
    t0 = clock(); 

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

    t1 = clock();
    tiempos[1] = (double(t1-t0)/CLOCKS_PER_SEC);
}

void comeTacos::insertionSort() {
    t0 = clock(); 

    for (int i = 0; i < noDatos; i++) {
        int pos = i;
        int aux = tacos[i];

        while ((pos > 0) && (tacos[pos - 1] > aux)) {
            tacos[pos] = tacos[pos - 1];
            pos--;
        }

        tacos[pos] = aux;

    }

    t1 = clock();
    tiempos[2] = (double(t1-t0)/CLOCKS_PER_SEC);
}

void comeTacos::countingSort() {
    t0 = clock(); 

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

    t1 = clock();
    tiempos[3] = (double(t1-t0)/CLOCKS_PER_SEC);
}

void comeTacos::shellSort() {
    t0 = clock(); 

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

    t1 = clock();
    tiempos[4] = (double(t1-t0)/CLOCKS_PER_SEC);
}

void comeTacos::quickSort(int arr[], int start, int end) {
    t0 = clock(); 

	if (start >= end)
		return;
	int p = partition(arr, start, end);
	quickSort(arr, start, p - 1);
	quickSort(arr, p + 1, end);

    t1 = clock();
    tiempos[5] = (double(t1-t0)/CLOCKS_PER_SEC);

}


void comeTacos::heapSort() {
    t0 = clock(); 

    for (int i = noDatos / 2 - 1; i >= 0; i--) {
        heapify(tacos, noDatos, i);
    }

    for (int i = noDatos - 1; i >= 0; i--) {
        swap(tacos[0], tacos[i]);
        heapify(tacos, i, 0);
    }

    t1 = clock();
    tiempos[6] = (double(t1-t0)/CLOCKS_PER_SEC);
}

void comeTacos::mergeSort(int arr[], int l, int r) {
    t0 = clock(); 

    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }

    t1 = clock();
    tiempos[7] = (double(t1-t0)/CLOCKS_PER_SEC);
}

void comeTacos::radixSort() {
    t0 = clock(); 

    int m = getMax(tacos, noDatos); 

    for (int exp = 1; m / exp > 0; exp *= 10)
        CountSort(tacos, noDatos, exp);
    
    t1 = clock();
    tiempos[8] = (double(t1-t0)/CLOCKS_PER_SEC);
}

int main() {
    comeTacos degustador1;

    degustador1.generarArreglo();
    degustador1.bubbleSort();

    degustador1.generarArreglo();
    degustador1.selectionSort();

    degustador1.generarArreglo();
    degustador1.insertionSort();

    degustador1.generarArreglo();
    degustador1.countingSort();

    degustador1.generarArreglo();
    degustador1.mergeSort(degustador1.tacos, 0, degustador1.noDatos);

    degustador1.generarArreglo();
    degustador1.radixSort();

    degustador1.generarArreglo();
    degustador1.shellSort();

    degustador1.generarArreglo();
    degustador1.heapSort();

    degustador1.generarArreglo();
    degustador1.quickSort(degustador1.tacos, 0, degustador1.noDatos);

    degustador1.imprimirTiempos();
}
