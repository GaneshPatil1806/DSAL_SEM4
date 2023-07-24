#include<iostream>
#include<fstream>
using namespace std;

class dataa
{
    int key;
    int val;

public:
    dataa(int k = -1, int v = -2)
    {
        key = k;
        val = v;
    }
    friend class filehash;
};

class filehash
{
    int size;
public:
    filehash(int n)
    {
        size = n;
    }

    int hashfunc(int);
    void create();
    void insert(int, int);
    void delete_(int);
    void print();
    void search(int);
};

int filehash::hashfunc(int roll)
{
    return (roll % size);
}

void filehash::create()
{
    dataa a;
    fstream file("hello.dat", ios::binary | ios::out);
    if (file)
    {
        for (int i = 0; i < size; i++)
        {
            file.write((char*)&a, sizeof(a));
        }
        cout << "File created successfully" << endl;
    }
    file.close();
}

void filehash::insert(int key, int value)
{
    int index = hashfunc(key);
    dataa a(key,value);
    dataa t;
    fstream file("hello.dat", ios::binary | ios::in | ios::out);

    if (file)
    {
        file.seekg(index * sizeof(a), ios::beg);
        file.read((char*)&t, sizeof(t));

        if (t.key == -1)
        {
            file.seekp(index * sizeof(a), ios::beg);
            file.write((char*)&a, sizeof(a));
            cout << "dataa inserted successfully" << endl;
        }
        else
        {
            int next = hashfunc(index + 1);
            while (next != index)
            {
                file.seekg(next * sizeof(a), ios::beg);
                file.read((char*)&t, sizeof(t));

                if (t.key == -1)
                {
                    file.seekp(next * sizeof(a), ios::beg);
                    file.write((char*)&a, sizeof(a));
                    cout << "dataa inserted successfully" << endl;
                    break;
                }
                next++;
                next %= size;
            }
        }

        file.close();
    }
}

void filehash::delete_(int key)
{
    fstream file("hello.dat", ios::binary | ios::in | ios::out);
    dataa temp;
    dataa null(-1, -2);

    if (file)
    {
        int index = hashfunc(key);
        file.seekg(index * sizeof(temp), ios::beg);
        file.read((char*)&temp, sizeof(temp));

        if (temp.key == key)
        {
            file.seekp(index * sizeof(temp), ios::beg);
            file.write((char*)&null, sizeof(null));
            cout << "Deleted" << endl;
        }
        else
        {
            int next = hashfunc(index + 1);
            while (next != index)
            {
                file.seekg(next * sizeof(temp), ios::beg);
                file.read((char*)&temp, sizeof(temp));

                if (temp.key == key)
                {
                    file.seekp(next * sizeof(temp), ios::beg);
                    file.write((char*)&null, sizeof(null));
                    cout << "Deleted" << endl;
                }
                next++;
                next %= size;
            }
        }
    }
}

void filehash::print()
{
    dataa e;
    fstream file("hello.dat", ios::binary | ios::in);
    if (file)
    {
        for (int i = 0; i < size; i++)
        {
            file.read((char*)&e, sizeof(e));
            cout << e.key << " " << e.val << endl;
        }
        file.close();
    }
}

int main()
{
    int hashsize;
    cout << "Enter the size of the max number of records you want to store" << endl;
    cin >> hashsize;

    // Hash file creation
    filehash obj(hashsize);
    obj.create();

    // Insert
    obj.insert(1, 10);
    obj.insert(2, 11);
    obj.insert(23, 12);
    obj.insert(33, 13);
    obj.insert(43, 13);

    //Delete
    obj.delete_(3);
    obj.delete_(23);

    // Display
    obj.print();

    return 0;
}