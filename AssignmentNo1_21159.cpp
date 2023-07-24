/*Beginning with an empty binary search tree, Construct binary search tree by inserting
the data in the order given. After constructing a binary tree -
i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data
value found in the tree, iv. Change a tree so that the roles of the left and right pointers
are swapped at every node, v. Search a value*/

#include<iostream>
#include<stack>
using namespace std;

class  bst
{
    bst *left,*right;
    int data;
    
public:

    bst()
    {
        left=right=NULL;
        data=0;
    }

    void insert_node(int, bst **);
    bst *create_bst(bst *);
    void inorder(bst *);
    void inorder_itr(bst *);
    void preorder(bst *);
    void postorder(bst *);
    int min_element(bst *);
    int max_element(bst *);
    void search(bst *root,int key);
    int height(bst *root);
    void swap(bst *);
    bst* successor(bst *);
    bst* delete_element(bst *,int);
};

void bst :: insert_node(int data,bst **root)
{
    bst *start= *root;
    bst *temp= new bst;
    temp->data= data;

    if(*root==NULL)
    {
        *root=temp;
        return ;
    }
    else
    {
        while(1)
        {
            if(data<=start->data)
            {
                if(start->left!=NULL)
                {
                    start=start->left;
                }
                
                else
                {
                    start->left=temp;
                    return;
                }
            }
            else
            {
                if(start->right!=NULL)
                {
                     start=start->right;
                     
                }
                
                else
                {
                    start->right=temp;
                    return;
                }
            }
        }
    }
}

bst *bst :: create_bst(bst *root)
{
    int n,val;
    cout<<"\nEnter the number of elements you want to insert in a tree\n";
    cin>>n;

    cout<<"\nEnter the data\n";

    for(int i=0;i<n;i++)
    {
         cin>>val;
         insert_node(val,&root);
    }
    
  return root;
}

void bst :: inorder(bst *root)
{
    if(root==NULL)
    {
        return;
    }
        
    else
    { 
        inorder(root->left);
        cout<<"\t"<<root->data;
        inorder(root->right);
    }
}

void bst :: inorder_itr(bst *root)
{
	stack <bst *> st;
	bst *temp= root;

	while(temp!= NULL || !st.empty())
	{
		while (temp != NULL)
		{
			st.push(temp);
			temp= temp->left;
		}

		temp = st.top();
		st.pop();

		cout<<"\t"<<temp->data;
        temp= temp->right;
	} 
}

void bst :: preorder(bst *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        cout<<"\t"<<root->data;
        preorder(root->left);
        preorder(root->right);  
    }
}

void bst :: postorder(bst *root)
{
    if(root==NULL)
    {
        return;
    }    
    else
    {
        postorder(root->left);
        postorder(root->right);
        cout<<"\t"<<root->data;
    }
}

int bst :: min_element(bst *root)
{
    bst *temp= root;

    if(temp==NULL)
        return -1;
    else if(temp->left==NULL && temp->right==NULL)
        return root->data;
    else
    {
         while(temp->left!=NULL)
        {
            temp= temp->left;
        }
        return temp->data;
    }
 }

 int bst :: max_element(bst *root)
 {
    bst *temp= root;

    if(temp==NULL)
        return -1;
    else if(temp->right==NULL && temp->left==NULL)
        return root->data;
    else
    {
         while(temp->right!=NULL)
        {
            temp= temp->right;
        }
        return temp->data;
    }
 }

void bst :: swap(bst *root)
 {
    bst *temp= root;
    bst *temp1;
    
    if(temp==NULL)
    {
        return;
    } 
    else
    {
        temp1=temp->right;
        temp->right=temp->left;
        temp->left=temp1;

        swap(temp->left);
        swap(temp->right);
    }
}
 
void bst :: search(bst *root,int key)
{
    bst *temp= root;
    bool flag=0;

    if(temp==NULL)
        cout<<"\nKey cannot be found as root is equals to NULL";
    else
    {
        while(temp!=NULL)
        {
            if(key==temp->data)
            {
                flag=1;
                break;
            } 
            else if(key<temp->data)
                temp=temp->left;
            else if(key>temp->data)
                temp=temp->right;
        }
    }
    if(flag) 
        cout<<"\nFound";
    else
        cout<<"\nNot Found";

}

int bst :: height(bst *root)
{
    int count;
    bst *temp= root;

    if (temp == NULL)
        return 0;
    else
    {
        int l = height(temp->left);
        int r = height(temp->right);
 
        count= max(l+1,r+1);
        return count;
    }
}

bst* bst :: successor(bst *r)
{
    //Here r=current
    while(r->left!=NULL)
        r=r->left;

    return r;
}

bst* bst :: delete_element(bst *root,int key)
{
    bool flag=0;
    bst *parent=root;
    bst *current=root;

	while(current!=NULL)
    {
        if(key==current->data)
        {
            flag=1;
            break;
        } 
        else if(key<current->data)
        {
            parent=current;
            current=current->left;
        }
        else if(key>current->data)
        {
            parent=current;
            current=current->right;
        }
    }

    if(flag)
    {
        //Leaf node or root node
        if(current->left==NULL && current->right==NULL)	
        {
			if(parent->left==current)
			{
                delete current;
                parent->left=NULL;	
			}
			else if(parent->right==current)
			{
                delete current;
				parent->right=NULL;
            }
            else if(root==current)
                delete current;
		}
        //Right child only
		else if(current->right!=NULL && current->left==NULL)	
		{
			if(parent->right==current)					
            {
				parent->right=current->right;
				delete current;
			}
			else if(parent->left==current)
			{
				parent->left=current->right;
				delete current;
			}
            //Parent itself is current
            else
            {
                root=root->right;
                current->right=NULL;
                delete current;
            }
		}
        //Left child only
		else if(current->left!=NULL && current->right==NULL)	
		{
			if(parent->right==current)
			{
				parent->right = current->left;
				delete current;
			}
			else if(parent->left==current)
			{
				parent->left=current->left;
				delete current;
			}
            else
            {
                root=root->left;
                current->left=NULL;
                delete current;
            }
		}
		else if(current->left!=NULL && current->right!=NULL)
		{
            bst *s=NULL;
            s=successor(current->right);
			int h= s->data;
			delete_element(current,s->data);
            current->data=h;
		}
    }
    else
        cout<<"\nEntered element is not present in the tree";

    return root;
}

int main()
{   
    int ch,key;
    bst tr;
    bst *r=NULL;

    while(ch!=11)
    {
        cout<<endl;
        cout<<"\nEnter your choice";
        cout<<"\n1.Create BST";
        cout<<"\n2.Insert a node";
        cout<<"\n3.Find the number of nodes in the longest path";
        cout<<"\n4.Minimum/Maximum data data found in the tree";
        cout<<"\n5.Change a tree so that the roles of the left and right pointers are swapped at every node";
        cout<<"\n6.Search data";
        cout<<"\n7.Inorder traversal";
        cout<<"\n8.Preorder traversal";
        cout<<"\n9.Postorder traversal";
        cout<<"\n10.Delete element";
        cout<<"\n11.Exit\n";
        cin>>ch;

        switch (ch)
        {
            case 1:
            {
                r=tr.create_bst(r);
                cout<<"Inorder ";
                tr.inorder(r);
                break;
            }
            case 2:
            {
                int o;
                cout<<"\nEnter the element you want to insert >> ";
                cin>>o;
                tr.insert_node(o,&r);
                break;
            }
            case 3:
            {
                int h= tr.height(r);
                cout<<"Height "<<h;
                break;
            }
            case 4:
            {
                int a= tr.min_element(r);
                int b= tr.max_element(r);
                cout<<"\nMinimum= "<<a<<" "<<"Maximum= "<<b;
                break;
            }
            case 5:
            {
                cout<<"\nBefore ";
                tr.inorder(r);
                tr.swap(r);
                cout<<"\nAfter ";
                tr.inorder(r);
                break;
            }
            case 6:
            {
                cout<<"\nEnter the key you want to search in the tree\n";
                cin>>key;
                tr.search(r,key);
                break;
            }
            case 7:
            {
                cout<<"\nInorder ";
                //Inorder by iteration
                tr.inorder_itr(r);
                break;
            }
            case 8:
            {
                cout<<"\nPreorder ";
                tr.preorder(r);
                break;
            }
            case 9:
            {
                cout<<"\nPostorder ";
                tr.postorder(r);
                break;
            }
            case 10:
            {
                int h;
            	cout<<"\nEnter the element which you want to delete >> ";
                cin>>h;
                r=tr.delete_element(r,h);
            }
            case 11:
            {
            	cout<<"\nExit\n";
                break;
            }  
            default:
                break;
        }
    }
    return 0;
}