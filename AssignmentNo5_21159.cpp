#include <iostream>
using namespace std;

class node
{
    node *next;
    string key, value;

public:
    node(string k, string val)
    {
        key = k;
        value = val;
        next = NULL;
    }
    friend class linked_list;
};

class linked_list
{
    node *head, *tail;

public:
    linked_list()
    {
        head = tail = NULL;
    }
    void insert(string, string);
    void delete_(string);
    bool search(string);
    void display();
    void update(string, string);
    bool empty();
};

void linked_list ::insert(string key, string value)
{
    node *t = new node(key, value);

    if (!head)
    {
        head = tail = t;
    }
    else
    {
        tail->next = t;
        tail = tail->next;
    }
}

void linked_list ::delete_(string key)
{
    node *ptr = head;
    if (ptr->key == key)
    {
        if (head == tail)
        {
            head = tail = nullptr;
            delete ptr;
            return;
        }
        head = head->next;
        delete ptr;
        return;
    }
    node *frnd = ptr;
    while (ptr->key != key || ptr == nullptr)
    {
        frnd = ptr;
        ptr = ptr->next;
    }
    frnd->next = ptr->next;
    if (ptr == tail)
    {
        tail = frnd;
    }
    delete ptr;
    return;
}

bool linked_list ::search(string key)
{
    node *t = head;
    node *p = NULL;
    int ct = 1;

    while (t && t->key != key)
    {
        ct++;
        p = t;
        t = t->next;
    }

    if (t)
    {
        cout << "\nKey is found! " << endl;
        cout << "\nNumber of comparisons " << ct << endl;
        return 1;
    }
    else
        cout << "\nKey not found" << endl;

    return 0;
}

void linked_list::update(string key, string value)
{
    node *ptr = head;
    while (ptr->key != key)
    {
        ptr = ptr->next;
    }
    ptr->value = value;
}

void linked_list::display()
{
    node *ptr = head;

    while (ptr != nullptr)
    {
        cout << "\t" << ptr->key << ": " << ptr->value;
        ptr = ptr->next;
    }
}

bool linked_list::empty()
{
    bool i = true;
    if (!head)
        return i;
    return !i;
}

class hashTable
{
    long long size;
    linked_list *arr;

public:
    hashTable(long long s)
    {
        size = s;
        arr = new linked_list[s];
    }

    int hash(string);
    void insert(string, string);
    void display();
    void delete_(string);
    void search(string key);
};

int hashTable::hash(string key)
{
    int i = 0;
    for (auto p : key)
    {
        i += int(p);
    }
    cout << "Hash Value for " << key << " is " << i << endl;
    return i % size;
}

void hashTable::insert(string key, string value)
{
    int i = hash(key);
    if (arr[i].search(key))
    {
        cout << "\nKey already present! " << endl;
    }
    else
    {
        arr[i].insert(key, value);
        cout << "\nElement Added Successfully!" << endl;
    }
}

void hashTable::display()
{
    for (long long p = 0; p < size; p++)
    {
        if (!arr[p].empty())
        {
            cout << "---------------------------------------------" << endl;
            cout << "index " << p << "\t";
            arr[p].display();
            cout << endl;
        }
    }
}

void hashTable ::delete_(string key)
{
    int i = hash(key);
    if (arr[i].search(key))
    {
        arr[i].delete_(key);
        cout << "Delete Successful!" << endl;
    }
}

void hashTable ::search(string key)
{
    int i = hash(key);
    arr[i].search(key);
    cout << endl;
}

int main()
{
    cout << "Enter the size of hash table ";
    long long s;
    cin >> s;
    hashTable t1(s);

    while (true)
    {
        cout << "\nEnter the operation you want to perform " << endl;
        cout << "1. Add Elements" << endl;
        cout << "2. Search Key" << endl;
        cout << "3. Display" << endl;
        cout << "4. Delete" << endl;
        cout << "5.End" << endl;

        int ch = 0;
        cin >> ch;
        cout << endl;

        switch (ch)
        {
        case 1:
        {
            int n;
            cout << "Enter the number of elements " << endl;
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter key: ";
                string key = "";
                cin >> key;
                cout << "Enter value: ";
                string value = "";
                cin >> value;
                t1.insert(key, value);
            }

            break;
        }
        case 2:
        {
            cout << "Enter key: ";
            string key = "";
            cin >> key;
            t1.search(key);
            break;
        }
        case 3:
        {
            t1.display();
            break;
        }
        case 4:
        {
            cout << "Enter key: ";
            string key = "";
            cin >> key;
            t1.delete_(key);
            break;
        }
        case 5:
        {
            cout << "Exit ";
            exit('0');
            break;
        }
        default:
        {
            cout << "\nInvalid choice" << endl;
            break;
        }
            cout << endl;
        }
    }
    return 0;
}