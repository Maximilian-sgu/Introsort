
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<ctime>

using namespace std;

void swapValue(int* a, int* b){//����� �������� ����������
    int* temp = a;
    a = b;
    b = temp;
}
void InsertionSort(int arr[], int* begin, int* end){//���������� ���������
    int left = begin - arr; //����� ������ ����������
    int right = end - arr; //������ ������ ����������
    for (int i = left + 1; i <= right; i++){
        int key = arr[i];
        int j = i - 1;
            while (j >= left && arr[j] > key) { //����������� ��������� ������� �� 0 �� i-1, ������� ������ ��� ����, �� ���� ������� ������.
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        arr[j + 1] = key;
    }
}
int* Quicksort(int arr[], int low, int high){ //������� ����������
    int pivot = arr[high];    // �����
    int i = (low - 1);  // ������ �������� ��������
    for (int j = low; j <= high - 1; j++){// ���� ������� ������� ������ ��� ����� pivot
        if (arr[j] <= pivot) {
            i++;// ����������� ������ �������� ��������
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1); //����� ���������
}

int* MedianOfThree(int* a, int* b, int* c){//�-� ���������� "������� ����", ������� �������� �������� ����� ����������� a,b,c � ���������� ���� ���������
    if (*a < *b && *b < *c)
        return (b);
    if (*a < *c && *c <= *b)
        return (c);
    if (*b <= *a && *a < *c)
        return (a);
    if (*b < *c && *c <= *a)
        return (c);
    if (*c <= *a && *a < *b)
        return (a);
    if (*c <= *b && *b <= *a)
        return (b);
}

void IntrosortUtil(int arr[], int* begin,int* end, int depthLimit){// ���������� ���������� introsort
    int size = end - begin;// ���������� ���������� ���������
    if (size < 16){ // ���� ������ ������� �������, ������ ���������� ���������
        InsertionSort(arr, begin, end);
        return;
    }
    if (depthLimit == 0){// ���� ������� ����� ����, ���������� heapsort
        make_heap(begin, end + 1);
        sort_heap(begin, end + 1); //���������� heapsort �� STL
    }
    int* pivot = MedianOfThree(begin, begin + size / 2, end); // ����� ���������� ��������� ������� ���� � ������� ������� ����� ��� ���������
    swapValue(pivot, end);    // ������ ��������, ��������� ����� �����������
    int* partitionPoint = Quicksort(arr, begin - arr, end - arr);// ��������� ������� ����������
    IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
    IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);
}

void Introsort(int arr[], int* begin, int* end){ //������������� ����������
    int depthLimit = 2 * log(end - begin);
    IntrosortUtil(arr, begin, end, depthLimit); // ��������� ����������� ���������
}

void printArray(int arr[], int n){// ��������������� ������� ������ ������� �� �����
    for (int i = 0; i < n; i++)
        cout << arr[i]<<" ";
}
int main() {
    int n;
    srand(time(NULL));
    cout << "N = ";
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    cout << "\n |INPUT|: ";
    printArray(arr, n);
    Introsort(arr, arr, arr + n - 1);
    cout << "\n |SORTED|: ";
    printArray(arr, n);
    return(0);
}
