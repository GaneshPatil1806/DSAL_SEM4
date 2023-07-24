#include<iostream>
#include<algorithm>
using namespace std;

class Heap
{
    int *arr;
    int size;

public:
    Heap(int n)
    {
        size = n;
        arr = new int[n];
    }
    void input();
    void build_max_heap();
    void build_min_heap();
    void heapify(int,int);
    void heapify_min(int,int);
    void heapsort();
    void display();
};

void Heap ::input()
{
    cout<< "\nEnter the elements"<< endl;
    for(int i = 0; i< size; i++)
    {
        cin >> arr[i];
    }
}

void Heap ::build_max_heap()
{
    for(int j =(size/2-1); j >= 0; j--)
    {
        heapify(j,size-1);
    }
}

void Heap ::build_min_heap()
{

    for(int j =(size/2-1); j >= 0; j--)
    {
        heapify_min(j,size-1);
    }
}

void Heap::heapify(int i,int s)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int index = i;

    if(l<=(s) && arr[l] > arr[index])
    {
       // cout<<arr[l]<<" > "<<arr[i]<<endl;
        index = l;
    }
    if(r<=(s) && arr[r] > arr[index])
    {
        // cout<<arr[r]<<" > "<<arr[i]<<endl;
        index = r;
    }
    if(index != i)
    {
       // cout<<"swap performed between "<<arr[i]<<"and "<<arr[index]<<endl;
        swap(arr[i], arr[index]);
        heapify(index,s);
    }
}

void Heap::heapify_min(int i,int s)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int index = i;

    if(l<=(s) && arr[l] < arr[index])
        index = l;
    if(r<=(s) && arr[r] < arr[index])
        index = r;
    if(index != i)
    {
       // cout<<"swap performed between "<<arr[i]<<"and "<<arr[index]<<endl;
        swap(arr[i], arr[index]);
        heapify_min(index,s);
    }
}

void Heap::heapsort()
{
    for (int i = (size/2- 1); i >= 0; i--)
    {
        heapify(i, size - 1);
    }

    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(0, i - 1);
    }
}

void Heap::display()
{
    for(int i = 0; i< size; i++)
    {
        cout<< "\t"<< arr[i];
    }
    cout<< endl;
}

int main()
{
    cout<< "\nEnter the number of elements"<< endl;
    int n;
    cin >> n;
    Heap obj(n);
    obj.input();
    int ch;

    while(1)
    {
        cout<< "\nEnter the operation"<< endl;
        cout<< "1.Maxheap"<< endl;
        cout<< "2.Minheap"<< endl;
        cout<< "3.Heapsort"<< endl;
        cout<< "4.Exit"<< endl;
        cin >> ch;
        cout<< endl;
        switch(ch)
        {
            case 1:
            {
                cout<< "Maxheap ";
                obj.build_max_heap();
                obj.display();
                break;
            }
            case 2:
            {
                cout<< "Minheap ";
                obj.build_min_heap();
                obj.display();
                break;
            }
            case 3:
            {
                cout<< "Sorted array ";
                obj.heapsort();
                obj.display();
                break;
            }
            case 4:
            {
                cout<< "Exit"<< endl;
                exit(0);
                break;
            }
            default:
                cout<< "\nInvalid input"<< endl;
        }
    }
    return 0;
}