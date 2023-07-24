/*
You have a business with several offices; you want to lease phone lines to connect them up with each other;
and the phone company charges different amounts of money to connect different pairs of cities. You want a 
set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting 
appropriate data structures.
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class node
{
	bool visited;
	int cost;
	string root;

public:
	node()
	{
		visited=false;
		cost=999;
	}
	friend class graph;
};

class graph
{
	//Array for taking input of graph
	int arr[50][50];
	//For kruskal's
	vector<vector<int>> vect;

	int edges;
	int vertices;
	string name[50];

public:
	graph(int v,int e)
	{
		edges=e;
		vertices=v;
		for(int i=0;i<v;i++)
			for(int j=0;j<v;j++)
				arr[i][j]=0;
	}
	void create();
	void prims();
	void kruskals();
	void display();
};

void graph :: create()
{
	bool flag=0;
	cout<<"Enter the vertices"<<endl;
	for(int i=0;i<vertices;i++)
	{
		cin>>name[i];
	}

	cout<<"Is the graph directed?y/n"<<endl;
	char dir;
	cin>>dir;
	if(dir=='y')
		flag=1;

	string s,d;
	int u,v,w;
	for(int j=0;j<edges;j++)
	{
		cout<<"Enter source vertex,destination vertex,cost"<<endl;
		cin>>s>>d>>w;

		//find the vertex indices in name[] array
		for(int i=0;i<vertices;i++)
		{
			if(s==name[i])
			{
				u=i;
			}
		}

		for(int i=0;i<vertices;i++)
		{
			if(d==name[i])
			{
				v=i;
			}
		}
		//Adding cost
		arr[u][v]=w;
		vect.push_back({ w,u,v});
		if(dir)
			arr[v][u]=w;
	}
}

void graph :: display()
{
	cout<<" ";
	for(int i=0;i<vertices;i++)
		cout<<" "<<name[i];
	cout<<endl;

	for(int i=0;i<vertices;i++)
	{
		cout<<name[i]<<" ";
		for(int j=0;j<vertices;j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}

void graph :: prims()
{
	int min_cost=0;
	vector<node*> v;
	string na;
	int u;
	
	for(int i=0;i<vertices;i++)
	{
		node *t=new node();
		v.push_back(t);
	}

	cout<<"\nEnter the starting vertex name"<<endl;
	cin>>na;

	for(int i=0;i<vertices;i++)
	{
		if(na==name[i])
			u=i;
	}
	//Initiated from a specific vertex
	v[u]->cost=0;
	v[u]->visited=true;
	int index_min=u;
	
	for(int i=0;i<vertices-1;i++)
	{
		for(int j=0;j<vertices;j++)
		{
			if(arr[index_min][j]!=0)
			{
				if(arr[index_min][j]<v[j]->cost)
				{
					v[j]->cost=arr[index_min][j];
					v[j]->root=name[index_min];
				}
			}
		}

		int min=999;
		//Now find the minimum cost in vector
		for(int k=0;k<vertices;k++)
		{
			if(!v[k]->visited && v[k]->cost<min)
			{
				min=v[k]->cost;
				index_min=k;
			}
		}

		min_cost+=min;
		v[index_min]->visited=true;
		//cout<<"min_ "<<min<<endl;
	}
	cout<<"The minimum cost by prim's algorithm is "<<min_cost<<endl;
}

void graph::kruskals()
{
    int min_cost = 0;
    sort(vect.begin(), vect.end());

    vector<int> visited(vertices); // Initialize with size and default value
    for (int i = 0; i < vertices; i++)
        visited[i] = i;

    vector<pair<int, pair<int, int>>> mst; // Stores the edges of the minimum spanning tree

    for (auto edge : vect)
    {
        int w = edge[0];
        int u = edge[1];
        int v = edge[2];

        if (visited[u] != visited[v])
        {
            min_cost += w;
            int src = visited[u];
            int dest = visited[v];
            for (int i = 0; i < vertices; i++)
            {
                if (visited[i] == dest)
                {
                    visited[i] = src;
                }
            }
            mst.push_back(make_pair(w, make_pair(u, v)));
        }
    }

    cout << "The minimum cost by Kruskal's algorithm is " << min_cost << endl;

    cout << "Minimum Spanning Tree Edges:\n";
    for (auto edge : mst)
    {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        cout << u << " - " << v << " : " << w << endl;
    }
}

int main()
{
	int v,e,ch;
	cout<<"Enter the number of vertices"<<endl;
	cin>>v;
	cout<<"Enter the number of edges"<<endl;
	cin>>e;

	graph obj(v,e);

	while(5)
	{
		cout<<"\nEnter the operation you want to perform"<<endl;
		cout<<"1.Read graph"<<endl;
		cout<<"2.Prims"<<endl;
		cout<<"3.Kruskals"<<endl;
		cout<<"4.Display"<<endl;
		cout<<"5.Exit"<<endl;
		cin>>ch;

		switch (ch)
		{
			case 1:
			{
				obj.create();
				break;
			}
			case 2:
			{
				obj.prims();
				break;
			}
			case 3:
			{
				obj.kruskals();
				break;
			}
			case 4:
			{
				obj.display();
				break;
			}
			case 5:
			{
				cout<<"Exit"<<endl;
				exit(0);
				break;
			}
			default:
				break;
		}
	}
}