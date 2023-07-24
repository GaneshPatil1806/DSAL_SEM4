/*Create an In-ordered threaded binary tree and perform In-order and Pre-order traversals.
 Analyze time and space complexity of the algorithm.*/

#include<iostream>
using namespace std;

class node
{
    node *left,*right;
    int data;
    bool rbit,lbit;

public:
    node()
    {
        left=right=NULL;
        data=0;
        lbit=rbit=0;
    }
    friend class tbt;
};

class tbt
{
public:
    node* create();
    void insert(node*,node*);
    void inorder(node*);
    void preorder(node*);
    node* delete_node(node*,int);
};

node* tbt :: create()
{
    node *root=NULL;
    node *head=new node();
    int b;
    cout<<"\nEnter the number of elements you want in threaded binary tree\n";
    cin>>b;

    cout<<"\nEnter the elements\n";
    for(int i=0;i<b;i++)
    {
        node *temp=new node();
        cin>>temp->data;

        if(root==NULL)
        {
            root=temp;
            head->data=-999;
            head->right=head;
            head->rbit=1;
            head->left=root;
            head->lbit=1;
            root->left=head;
            root->right=head;
        }
        else
        {
            insert(root,temp);
        }
    }
    return head;
}

void tbt :: insert(node *root,node *temp)
{
    if(temp->data<root->data)
    {
        if(root->lbit==0)
        {
            temp->left=root->left;
            temp->right=root;
            root->left=temp;
            root->lbit=1;
        }
        else
        {
            insert(root->left,temp);
        }
    } 

    if(temp->data>root->data)
    {
        if(root->rbit==0)
        {
            temp->right=root->right;
            temp->left=root;
            root->right=temp;
            root->rbit=1;
        }
        else
        {
            insert(root->right,temp);
        }
    }  
}

void tbt :: inorder(node *head)
{
    node* t=head->left;

    do
    {
        while(t->lbit!=0)
        {
            t= t->left;
        }
        cout<<t->data<<" ";

        while(t->rbit==0)
        {
            t= t->right;
            if(t==head)
                break;
            cout<<t->data<<" ";
        }
        t=t->right;

    }while (t!=head);
}

void tbt :: preorder(node *head)
{
    node* t=head->left;

    do
    {
        while(t->lbit!=0)
        {
            cout<<t->data<<" ";
            t= t->left;
        }

        cout<<t->data<<" ";

        while(t->rbit==0)
        {
            t= t->right;
            if(t==head)
                break;
        }
        t=t->right;
    }while (t!=head);
}

node* tbt :: delete_node(node *head,int key)
{
    node *curr=head->left;
    node *par=head->left;
    bool flag=0;

    while(curr!=head)
    {
        if(key==curr->data)
        {
            flag=1;
            break;
        } 
        else if(key<curr->data)
        {
            par=curr;
            curr=curr->left;
        }
        else if(key>curr->data)
        {
            par=curr;
            curr=curr->right;
        }
    }

    if(flag)
    {
        //Leaf node right or left
        if(curr->lbit==0 && curr->rbit==0)	
        {
			if(par->left==curr)
			{
                par->left=curr->left;	
                par->lbit=0;
			}
			else if(par->right==curr)
			{
                par->right=curr->right;	
                par->rbit=0;
            }
            else if(head->left==curr)
            {
                cout<<"\nRoot can't be deleted";
            }
            delete curr;
		}
        //Right child only
		else if(curr->rbit!=0 && curr->lbit==0)	
		{
			if(par->right==curr)					
            {
				par->right=curr->right;
                curr->right->left=par;
                curr->left=curr->right=NULL;
				delete curr;
			}x
			else if(par->left==curr)
			{
				par->left=curr->right;
                curr->right->right=par;
                curr->right->left=curr->left;
                curr->left=curr->right=NULL;
				delete curr;
			}
            //par itself is root
            else
            {
                cout<<"\nRoot can't be deleted";
            }
		}
        //Left child only
		else if(curr->lbit!=0 && curr->rbit==0)	
		{
			if(par->right==curr)					
            {
				par->right=curr->left;
                curr->right->left=par;
                curr->right->right=curr->left;
                curr->left=curr->right=NULL;
				delete curr;
			}
			else if(par->left==curr)
			{
				par->left=curr->left;
                curr->left->right=par;
                curr->left=curr->right=NULL;
				delete curr;
			}
            //par itself is root
            else
            {
                cout<<"\nRoot can't be deleted";
            }
		}
		else if(curr->lbit!=0 && curr->rbit!=0)
		{
            node *s=NULL;
            s=curr->right;
            while(s->lbit!=0)
            {
                s=s->left;
            }
			int h= s->data;
			delete_node(head,s->data);
            curr->data=h;
		}
    }
    else
        cout<<"\nEntered element is not present in the tree";

    return head;
}

int main()
{
    tbt t;
    node *head=NULL;
	int ch;

	while(true)
	{
		cout<<"\n------------THREADED BINARY TREE------------"<<endl;
		cout<<"1. Create threaded binary tree"<<endl;
		cout<<"2. Traversals of TBT"<<endl;
		cout<<"3. Delete an element from TBT"<<endl;
		cout<<"4. Exit"<<endl;
		cout<<"Enter Choice:"<<endl;
		cin>>ch;
        
		switch(ch)
		{
            case 1:
            {
                head=t.create();
                cout<<"\nInorder ";
                t.inorder(head);
                break;
            }
            case 2:
            {
                int n;
                cout<<"\nEnter the Choice";
                cout<<"\n1.Inorder ";
                cout<<"\n2.Preorder\n";
                cin>>n;

                if(n==1)
                {
                    cout<<"\nInorder ";
                    t.inorder(head);
                    cout<<endl;
                }
                else if(n==2)
                {
                    cout<<"\nPreorder ";
                    t.preorder(head);
                    cout<<endl;
                }
                else
                    cout<<"\nWrong Choice";
                break;
            }
            case 3:
            {
                int h;
                cout<<"\nEnter the element which you want to delete >> ";
                cin>>h;
                head=t.delete_node(head,h);
                break;
            }
            case 4:
                exit('0');
            default:
            {
                cout<<"Wrong Choice!!!"<<endl;
                break;
            }
		}
	}
    return 0;
}
