#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class node
{
    node *next;
    string name;
    int val, indegree, outdegree;
    int cost;

public:
    node() {}

    node(int v, string s, int cost)
    {
        name = s;
        val = v;
        cost = 0;
        next = nullptr;
        indegree = outdegree = 0;
    }
    friend class linked_list;
    friend class graph;
};

class linked_list
{
    node *head, *tail;

public:
    linked_list()
    {

        head = tail = nullptr;
    }

    void insert(int, string, int);
    void inserth(node *);
    void display();
    bool empty();
    friend class graph;
};

bool linked_list::empty()
{
    bool i = true;
    if (!head)
        return i;
    return !i;
}

void linked_list ::insert(int val, string name, int cost)
{
    node *t = new node(val, name, cost);

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

void linked_list ::inserth(node *t)
{
    node *f = new node(t->val, t->name, t->cost);

    if (!head)
    {
        head = tail = f;
    }
    else
    {
        tail->next = f;
        tail = tail->next;
    }
}

void linked_list::display()
{
    node *ptr = head;

    while (ptr != nullptr)
    {
        cout << "\t" << ptr->name << ": " << ptr->val;
        ptr = ptr->next;
    }
}

class graph
{
    linked_list *arr;
    bool *visitedarr;
    int size;

public:
    graph(int n)
    {
        size = n;
        arr = new linked_list[100];
        visitedarr = new bool[n];
    }

    void read();
    void display();
    void bfs();
    void dfs();
    void inout();
};

void graph::read()
{
    int m = 0;
    int c = 0;
    string s;

    for (int i = 0; i < size; i++)
    {
        cout << "\nEnter the name of the node " << i << endl;
        cin >> s;
        arr[i].insert(i, s, c);
    }

    for (int i = 0; i < size; i++)
    {
        cout << "\nEnter the number of nodes adjecent to {" << arr[i].head->name << "}" << endl;
        cin >> m;

        if (m <= size)
        {
            for (int j = 0; j < m; j++)
            {
                cout << "\nEnter the adjecent element name ";
                cin >> s;
                // cout << "\nEnter the cost " << i << endl;
                // cin >> c;
                int t = 0;
                node *k = arr[0].head;
                k->cost = c;
                while (k->name != s)
                {
                    t++;
                    k = arr[t].head;
                }

                if (k->name == s)
                    arr[i].inserth(k);
                else
                {
                    cout << "\nElement not present in graph re-enter" << endl;
                    i--;
                }
            }
        }
        else
        {
            cout << "\nSize error!!" << endl;
            i--;
        }
    }
}

void graph::display()
{
    for (long long p = 0; p < size; p++)
    {
        if (!arr[p].empty())
        {
            cout << "---------------------------------------------" << endl;
            arr[p].display();
            cout << endl;
        }
    }
}

void graph::dfs()
{
    stack<node *> st;
    int start;
    int x;
    vector<bool> visited(size, false);
    cout << "Enter the starting vertex number: ";
    cin >> start;
    node *p = arr[start].head;
    st.push(p);
    cout << "DFS\t";
    while (!st.empty())
    {
        p = st.top();
        st.pop();
        x = p->val;
        cout << x << ":" << p->name << "\t";
        visited[x] = true;
        node *t = arr[x].head;
        while (t)
        {
            if (visited[t->val] == false)
            {
                st.push(t);
                visited[t->val] = true;
            }
            t = t->next;
        }
    }
}

void graph::bfs()
{
    queue<node *> q;
    int start;
    vector<bool> visited(size, false);
    cout << "Enter the starting vertex number: ";
    cin >> start;
    node *p = arr[start].head;
    q.push(p);
    cout << "BFS\t";
    while (!q.empty())
    {
        int x;
        p = q.front();
        q.pop();
        x = p->val;
        //visited[x] = true;
        cout << x << ":" << p->name << "\t";
        node *t = arr[x].head;
        while (t)
        {
            if (visited[t->val] == false)
            {
                qt);
                v.push(isited[t->val] = true;
            }
            t = t->next;
        }
    }
}

void graph::inout()
{
    for (int i = 0; i < size; i++)
    {
        node *t = arr[i].head;

        while (t != nullptr)
        {
            arr[arr[i + 1].head->val].head->outdegree++;
            t = t->next;
        }
    }

    cout << "In-degree and Out-degree" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << arr[i].head->name << " "
             << "In-degree " << arr[i].head->indegree << endl;
        cout << arr[i].head->name << " "
             << "Out-degree " << arr[i].head->outdegree << endl;
    }
}

int main()
{
    int n, ch;
    cout << "\nEnter the number of elements you want to insert in the graph" << endl;
    cin >> n;

    graph obj(n);
    obj.read();

    while (1)
    {
        cout << "\nEnter the operation you want to perform" << endl;
        cout << "1.BFS" << endl;
        cout << "2.DFS" << endl;
        cout << "3.In-degree and out-degree" << endl;
        cout << "4.Display" << endl;
        cout << "5.Exit" << endl;

        cin >> ch;
        switch (ch)
        {
        case 1:
            obj.bfs();
            break;
        case 2:
            obj.dfs();
            break;
        case 3:
            obj.inout();
            break;
        case 4:
            cout << "===========Graph===========" << endl;
            obj.display();
            break;
        case 5:
            cout << "Exit" << endl;
            exit('0');
        default:
            cout << "Wrong input!!!" << endl;
            break;
        }
    }
    return 0;
}