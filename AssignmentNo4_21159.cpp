/*Consider telephone book dataabase of N clients. Make use of a hash
table implementation to quickly look up client’s telephone number.
Make use of two collision handling techniques and compare them using
number of comparisons required to find a set of telephone numbers
(Note: Use linear probing with replacement and without replacement)*/

#include <iostream>
#include <string>
using namespace std;

class dataa
{
public:
    long long teleno;
    string name;
    bool collision;

    dataa()
    {
        name = " ";
        teleno = -1;
        collision = false;
    }
    friend class hashing;
};

class hashing
{
    dataa *arr;
    long long size;

public:
    hashing(int n)
    {
        size = n;
        arr = new dataa[size];
    }

    long long hash(long long);
    void insertwor(dataa);
    void insertwr(dataa);
    void compare(long long int);
    void delete_(long long int);
    void display();
};

long long hashing ::hash(long long num)
{
    long long key;
    key = num % size;
    return key;
}

void hashing ::insertwor(dataa c)
{
    long long h = hash(c.teleno);
    bool flag = 0;

    if (!arr[h].collision)
    {
        arr[h].teleno = c.teleno;
        arr[h].name = c.name;
        arr[h].collision = true;
    }
    else
    {
        for (long long i = (h + 1); i < size; i++)
        {
            if (!arr[i].collision)
            {
                arr[i].teleno = c.teleno;
                arr[i].name = c.name;
                arr[i].collision = true;
                flag = 1;
                break;
            }
        }
        for (long long i = 0; (i < h && flag == 0); i++)
        {
            if (!arr[i].collision)
            {
                arr[i].teleno = c.teleno;
                arr[i].name = c.name;
                arr[i].collision = true;
                flag = 1;
                break;
            }
        }
    }
}

void hashing ::insertwr(dataa c)
{
    long long h = hash(c.teleno);
    bool flag = 0;

    if (!arr[h].collision)
    {
        arr[h].teleno = c.teleno;
        arr[h].name = c.name;
        arr[h].collision = true;
    }
    else if (arr[h].collision && hash(arr[h].teleno) == h)
    {
        for (long long i = (h + 1); i < size; i++)
        {
            if (!arr[i].collision)
            {
                arr[i].teleno = c.teleno;
                arr[i].name = c.name;
                flag = 1;
                arr[i].collision = true;
                break;
            }
        }
        for (long long i = 0; (i < h && flag == 0); i++)
        {
            if (!arr[i].collision)
            {
                arr[i].teleno = c.teleno;
                arr[i].name = c.name;
                flag = 1;
                arr[i].collision = true;
                break;
            }
        }
    }
    else if (arr[h].collision && hash(arr[h].teleno) != h)
    {
        string n1;
        long long t;
        n1 = arr[h].name;
        t = arr[h].teleno;
        arr[h].name = c.name;
        arr[h].teleno = c.teleno;

        for (long long i = (h + 1); i < size; i++)
        {
            if (!arr[i].collision)
            {
                arr[i].name = n1;
                arr[i].teleno = t;
                arr[i].collision = true;
                flag = 1;
                break;
            }
        }
        for (long long i = 0; (i < h && flag == 0); i++)
        {
            if (!arr[i].collision)
            {
                arr[i].name = n1;
                arr[i].teleno = t;
                flag = 1;
                arr[i].collision = true;
                break;
            }
        }
    }
}

void hashing::compare(long long int t)
{
    int i = t % size;
    int count = 1;
    bool flag=0;

    while(count<=size)
    {
        if (arr[i].teleno == t)
        {
            cout<<"Telephone number present at index "<<i<<endl;
            cout << "Number of comparisons : " << count << endl;
            flag=1;
            break;
        }
        i++;
        i%=size;
        count++;
    }
    if(!flag)
        cout<<"\nElement not present";
}

void hashing ::display()
{
    for (int i = 0; i < size; i++)
    {
        if (!arr[i].collision)
            cout << "index: "<<i<<"  Element: "<<"Not present" << endl;
        else
        {
            cout << "index: "<<i<<"  Element: "<<arr[i].teleno << endl;
        }
    }
}

void hashing:: delete_(long long int t)
{
    long long i = hash(t);
    int n=0;
    bool flag=0;

    while(n<size)
    {
        if (arr[i].teleno==t)
        {
            arr[i].name = " ";
            arr[i].teleno = -1;
            arr[i].collision = false;
            flag=1;
        }
        n++;
        i++;
        i%=size;
    }
    if(!flag)
        cout<<"\nElement not present";
}

int main()
{
    int a, b, p, ch;
    cout << "Enter the size of hash table h1: " << endl;
    cin >> a;
    cout << "Enter the size of hash table h2: " << endl;
    cin >> b;
    hashing l(a), m(b);

    cout << "\nEnter the number of clients" << endl;
    cin >> p;
    for (int i = 0; i < p; i++)
    {
        dataa c;
        cout << "Enter Name " << (i + 1) << " :" << endl;
        cin >> c.name;
        cout << "Enter Telephone Number " << (i + 1) << " :" << endl;
        cin >> c.teleno;
        l.insertwor(c);
        m.insertwr(c);
    }

    while (true)
    {
        cout << "\nEnter the operation" << endl;
        cout << "1.Display" << endl;
        cout << "2.Search and number of comparisons" << endl;
        cout << "3.Delete" << endl;
        cout << "4.Exit" << endl;
        cin >> ch;
        switch (ch)
        {
            case 1:
            {
                cout<<"\n=========================="<<endl;
                cout<<"\nWithout replacement"<<endl;
                l.display();
                cout<<"\n=========================="<<endl;
                cout<<"\nWith replacement"<<endl;
                m.display();
                cout<<"\n=========================="<<endl;
                break;
            }
            case 2:
            {
                long long h;
                cout<<"\nEnter the element you want to search"<<endl;
                cin>>h;
                cout<<"\n=========================="<<endl;
                cout<<"\nWithout replacement"<<endl;
                l.compare(h);
                cout<<"\n=========================="<<endl;
                cout<<"\nWith replacement"<<endl;
                m.compare(h);
                cout<<"\n=========================="<<endl;
                break;
            }
            case 3:
            {
                long long h;
                cout<<"\nEnter the element you want to delete"<<endl;
                cin>>h;
                l.delete_(h);
                m.delete_(h);
                cout<<"\nElement deleted successfully!"<<endl;
                break;
                
            }
            case 4:
                exit('0');
            
            default:
                cout << "\nWrong input!";
        }
    }
    return 0;
}