#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int s=0;

class node {
    node* left;
    node* right;
    int data;

public:
    node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
    friend class obst;
};

class obj {
    int root;
    int freq;

public:
    obj() {
        root = freq = 0;
    }
    friend class obst;
};

class obst {
    obj arr[50][50];
    int size;

public:
    obst(int n) {
        size = n;
    }

    int sum(vector<int> freq, int i, int j);
    int getopt(vector<int> keys, vector<int> freq, int i, int j);
    void getobst(vector<int> keys, vector<int> freq);
    void Preorder(node* r);
    void Inorder(node* r);
    void Postorder(node* r);
    int getMinCost();
    node* create(int i, int j,vector<int>&);
};

int obst::sum(vector<int> freq, int i, int j) {
    int cost = 0;
    for (int k = i; k <= j; k++) {
        cost += freq[k];
    }
    return cost;
}

int obst::getopt(vector<int> keys, vector<int> freq, int i, int j)
{
    if (j < i)
        return 0;
    if (j == i)
    {
        return freq[i];
    }
    
    int minCost = INT_MAX;
    int rootIndex = -1;

    for (int r = i; r <= j; r++)
    {
        int cost = getopt(keys, freq, i, r - 1) + getopt(keys, freq, r + 1, j) + sum(freq, i, j);
        if (cost < minCost)
        {
            minCost = cost;
            rootIndex = r;
        }
    }

    arr[i][j].root = rootIndex; 

    return minCost;
}


void obst::getobst(vector<int> keys, vector<int> freq) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j].freq = getopt(keys, freq, i, j);
            if(i==j)
            {
                arr[i][j].root=keys[i];
            }
        }
    }

    cout << "frequencies obst" << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j].freq << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Root index obst" << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j].root << " ";
        }
        cout << endl;
    }
}

node* obst::create(int i, int j, vector<int>& keys) {
    if (i > j)
        return nullptr;

    if (i == j) {
        node* leaf = new node(keys[i]);
        return leaf;
    }

    int rootIndex = arr[i][j].root;
    node* root = new node(keys[rootIndex]);

    root->left = create(i, rootIndex - 1, keys);
    root->right = create(rootIndex + 1, j, keys);

    return root;
}


void obst::Postorder(node* r) {
    if (!r)
        return;

    Postorder(r->left);
    Postorder(r->right);
    cout << "\t" << r->data;
}

void obst::Preorder(node* r) {
    if (!r)
        return;
    cout << "\t" << r->data;
    Preorder(r->left);
    Preorder(r->right);
}

void obst::Inorder(node* r) {
    if (!r)
        return;

    Inorder(r->left);
    cout << "\t" << r->data;
    Inorder(r->right);
}

int obst::getMinCost() {
    return arr[0][size - 1].freq;
}

int main() {
    int n, ch;
    node* r = nullptr;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<int> keys(n);
    vector<int> freq(n);

    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the frequencies: ";
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
    }

    obst obj(n);
    obj.getobst(keys, freq);

    while (1) {
        cout << endl;
        cout << "\nEnter your choice";
        cout << "\n1.Find minimum cost";
        cout << "\n2.Create Obst";
        cout << "\n3.Preorder, Postorder, Inorder";
        cout << "\n4.Exit\n";
        cin >> ch;

        switch (ch) {
            case 1: {
                int minCost = obj.getMinCost();
                cout << "Minimum cost of constructing the BST: " << minCost << endl;
                break;
            }
            case 2: {
                r = obj.create(0, n - 1,keys);
                cout << "\nInorder\t";
                obj.Inorder(r);
                break;
            }
            case 3: {
                cout << endl;
                cout << "\nInorder\t";
                obj.Inorder(r);
                cout << endl;
                cout << "\nPreorder\t";
                obj.Preorder(r);
                cout << endl;
                cout << "\nPostorder\t";
                obj.Postorder(r);
                break;
            }
            case 4: {
                cout << "\nExit";
                exit(0);
                break;
            }
            default:
                break;
        }
    }
    return 0;
}