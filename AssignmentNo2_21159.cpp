#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class bt
{
public:

    int value;
    bt *left;
    bt *right;

    bt(int val)
    {
    	value=val;
    	left=NULL;
		right=NULL;
    }
    bt()
    {}
    void inorder_itr(bt*);
    void postorder_itr(bt *root);
    void preorder_itr(bt*);
    void inorder(bt *);
    void preorder(bt *);
    void postorder(bt *root);

    void swap(bt *root);
    void swap_itr(bt *);

    int height(bt*);
    int height_itr(bt*);

    void erase(bt*);
    void erase_itr(bt*);

    int count_leafnodes(bt *root);
    int count_non_leafnodes(bt *root);
    int count_leafnodes_itr(bt *root);
    int count_non_leafnodes_itr(bt *root);

    bt* copyBinaryTree(bt*); 
    friend class node;
};

class node
{
    int value;
    node* next;

public:
    node() : next(nullptr) {}
    node *create_LL(node *);
    //void dis(node *);
    bt* createBalancedBinaryTree(node* );
    void insert_node(int, node **);
};

bt* node :: createBalancedBinaryTree(node* head)
{
    if (!head)
    {
        return nullptr;
    }

    queue<bt*> q;
    bt* root = new bt(head->value);
    q.push(root);
    head = head->next;

    while (!q.empty() && head) 
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++)
        {
            bt* parent = q.front();
            q.pop();

            if (head)
            {
                bt* leftnode = new bt(head->value);
                parent->left = leftnode;
                q.push(leftnode);
                head = head->next;
            }

            if (head)
            {
                bt* rightnode = new bt(head->value);
                parent->right = rightnode;
                q.push(rightnode);
                head = head->next;
            }
        }
    }
    return root;
}
//Recursively
void bt :: inorder(bt *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    { 
        inorder(root->left);
        cout<<"\t"<<root->value;
        inorder(root->right);
    }
}

bt* bt :: copyBinaryTree(bt* root) 
{
    if (root == NULL) 
    {
        return NULL;
    }

    bt* newRoot = new bt(root->value);
    newRoot->left = copyBinaryTree(root->left);
    newRoot->right = copyBinaryTree(root->right);

    return newRoot;
}

void bt :: preorder(bt *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        cout<<"\t"<<root->value;
        preorder(root->left);
        preorder(root->right);  
    }
}

void bt :: postorder(bt *root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        postorder(root->left);
        postorder(root->right);
        cout<<"\t"<<root->value;
    }
}

void bt :: swap(bt *root)
 {
    bt *node= root;
    bt *node1;

    if(node==NULL)
    {
        return;
    }
    else
    {
        node1=node->right;
        node->right=node->left;
        node->left=node1;

        swap(node->left);
        swap(node->right);
    }
}

void bt :: swap_itr(bt *root)
 {
    bt *node= root;
    stack <bt *> st;

    if(node==NULL)
        cout<<"\nTree is empty";
    else
    {
        st.push(root);
        while(!st.empty()) 
        {
            bt* curr= st.top();
            st.pop();

            bt* temp = curr->left;
            curr->left = curr->right;
            curr->right = temp;

            if(curr->left) 
                st.push(curr->left);
            if (curr->right) 
                st.push(curr->right);
        }
    }
}

node *node :: create_LL(node *head)
{
    int n,val;
    cout<<"\nEnter the number of elements you want to insert in a tree\n";
    cin>>n;

    cout<<"\nEnter the values\n";

    for(int i=0;i<n;i++)
    {
         cin>>val;
         insert_node(val,&head);
    }
    return head;
}

void node :: insert_node(int value, node **head)
{
    node *start= *head;
    node *temp= new node;
    temp->value= value;

    if(*head==NULL)
    {
        *head=temp;
    }
    else
    {
        while(start->next!=NULL)
        {
            start=start->next;
        }
        start->next=temp;
    }
}
//Iterative
void bt :: inorder_itr(bt *root)
{
    stack <bt*> st;
    bt *temp = root;
    
    if(temp==NULL)
		cout<<" Tree is empty";
    else
    {
        while (temp != NULL || !st.empty())
        {
            if (temp != NULL)
            {
                st.push(temp);
                temp = temp->left;
            }
            else
            {
                temp = st.top();
                st.pop();
                cout<<"\t"<<temp->value;
                temp=temp->right;
            }
        }
    }
}

void bt :: preorder_itr(bt *root)
{
	stack <bt *> st;
	bt *node= root;

	if(node==NULL)
		cout<<" Tree is empty";
	else
	{
		while(node!= NULL || !st.empty())
		{
			while (node != NULL)
			{
				cout<<"\t"<<node->value;
				st.push(node);
				node= node->left;
			}

			node = st.top();
			st.pop();

			node= node->right;
		}
	}
}

void bt :: postorder_itr(bt *root)
{
	stack <bt *> st1;
	stack <bt *> st2;
	bt *temp= root;

	if(temp==NULL)
		cout<<" Tree is empty";
	else
    {
        st1.push(temp);
        while(!st1.empty())
        {
            temp= st1.top();
            st1.pop();
            st2.push(temp);
    
            if (temp->left!=NULL)
                st1.push(temp->left);
            if (temp->right!=NULL)
                st1.push(temp->right);
        }
    
        while(!st2.empty()) 
        {
            temp= st2.top();
            st2.pop();
            cout<<"\t"<<temp->value;
        }
    }
}
//Recursive
int bt :: height(bt *root)
{
    int count;
    bt *node= root;

    if (node == NULL)
        return 0;
    else
    {
        int l = height(node->left);
        int r = height(node->right);

        count= max(l+1,r+1);
        return count;
    }
}

int bt :: height_itr(bt* root) 
{
    queue <bt *> q;
    int height = 0;
    bt *node=NULL;

    if (root == NULL) 
        return 0;
    
    q.push(root);
    while (!q.empty()) 
    {
        int size = q.size();
        while (size--) 
        {
            bt* node = q.front();
            q.pop();
            if (node->left != NULL) 
                q.push(node->left);

            if (node->right != NULL) 
                q.push(node->right);
        }
        height++;
    }
    return height;
}

int bt :: count_leafnodes(bt *root)
{
    if (root == NULL) 
        return 0;

    if (root->left == NULL && root->right == NULL) 
        return 1;

    return count_leafnodes(root->left) + count_leafnodes(root->right);
}

int bt :: count_leafnodes_itr(bt *root)
{   
    if (root == NULL) 
        return 0;

    stack<bt*> s;
    s.push(root);
    int leafNodes = 0;
    while (!s.empty()) 
    {
        bt* node = s.top();
        s.pop();
        if (node->left == NULL && node->right == NULL) 
            leafNodes++;
        else 
        {
            if (node->left != NULL) 
            {
                s.push(node->left);
            }
            if (node->right != NULL) 
            {
                s.push(node->right);
            }
        }
    }
    return leafNodes;
}

int bt :: count_non_leafnodes_itr(bt *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL)) 
        return 0;

    stack<bt*> s;
    s.push(root);
    int nonLeafNodes = 0;
    while (!s.empty()) 
    {
        bt* node = s.top();
        s.pop();
        if (node->left != NULL || node->right != NULL) 
        {
            nonLeafNodes++;
            if (node->left != NULL) 
                s.push(node->left);
            if (node->right != NULL) 
                s.push(node->right);
        }
    }
    return nonLeafNodes;
}

int bt :: count_non_leafnodes(bt *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL)) 
        return 0;
    
    return 1 + count_non_leafnodes(root->left) + count_non_leafnodes(root->right);
}
void bt :: erase(bt* root) 
{
    if (!root)
        return;

    erase(root->left);
    erase(root->right);
    root->left=root->right=nullptr;
    root=NULL;
    delete root;
}

void bt :: erase_itr(bt* root) 
{
    if (!root) 
        return;
    else
    {
        stack<bt*> s;
        s.push(root);
        while (!s.empty()) 
        {
            bt* node = s.top();
            s.pop();
            if (node->left != NULL) 
                s.push(node->left);

            if (node->right != NULL) 
                s.push(node->right);

            delete node;
        }
    }
}

int main()
{
    node *head=NULL;
    node p;
    bt tr;
    bt *temp=NULL,*root=NULL;
    int ch;

    while(ch!=8)
    {
        cout<<endl;
        cout<<"\nEnter your choice";
        cout<<"\n1.Create Binart Tree";
        cout<<"\n2.Inorder traversal, Preorder traversal, Postorder traversal";
        cout<<"\n3.Change a tree so that the roles of the left and right pointers are swapped at every node";
        cout<<"\n4.Height of tree";
        cout<<"\n5.Copy this tree into another";
        cout<<"\n6.Count the number of leaf, number of internal nodes ";
        cout<<"\n7.Erase all nodes";
        cout<<"\n8.Exit\n";
        cin>>ch;

        switch (ch)
        {
            case 1:
            {
                head=p.create_LL(head);
                root = p.createBalancedBinaryTree(head);
                cout<<"\nInorder"<<"\t";
                tr.inorder_itr(root);
                break;
            }
            case 2:
            {
                cout<<"\nIteratively";
                cout<<"\nInorder\t";
                tr.inorder_itr(root);
                cout<<"\nPreorder";
                tr.preorder_itr(root);
                cout<<"\nPostorder";
                tr.postorder(root);

                cout<<"\nRecurrsively";
                cout<<"\nInorder\t";
                tr.inorder(root);
                cout<<"\nPostorder";
                tr.preorder(root);
                cout<<"\nPostorder";
                tr.postorder(root);
                break;
            }
            case 3:
            {
                cout<<"\nIteratively";
                cout<<"\nBefore ";
                tr.inorder_itr(root);
                tr.swap(root);
                cout<<"\nAfter ";
                tr.inorder_itr(root);

                cout<<"\nRecurrsively";
                cout<<"\nBefore ";
                tr.inorder_itr(root);
                tr.swap_itr(root);
                cout<<"\nAfter ";
                tr.inorder_itr(root);
                break;
            }
            case 4:
            {
                cout<<"\nIteratively";
                int h= tr.height(root);
                cout<<"\nHeight "<<h;
                cout<<"\nRecurrsively";
                int k= tr.height_itr(root);
                cout<<"\nHeight  "<<k;
                break;
            }
            case 5:
            {
                cout<<"\nContents of first tree\t";
                tr.inorder_itr(root);
                bt *newRoot=tr.copyBinaryTree(root);
                cout<<"\nContents of second tree\t";
                tr.inorder_itr(newRoot);
                break;
            }
            case 6:
            {
                cout<<"\nIteratively";
                int m=tr.count_leafnodes_itr(root);
                int n=tr.count_non_leafnodes_itr(root);
                cout<<"\nLeaf nodes = "<<m<<" Internal nodes = "<<n;

                cout<<"\nRecurrsively";
                int h=tr.count_leafnodes(root);
                int p=tr.count_non_leafnodes(root);
                cout<<"\nLeaf nodes = "<<h<<" Internal nodes = "<<p;
                break;
            }
            case 7:
            {
                int l;
                cout<<"\nEnter the operation you want to perform";
                cout<<"\n1.Delete Iteratively";
                cout<<"\n2.Delete Recurrsively\n";
                cin>>l;
                
                if(l==1)
                {
                    cout<<"\nBefore ";
                    tr.inorder_itr(root);
                    root=nullptr;
                    tr.erase_itr(root);
                    cout<<"\nAfter ";
                    tr.inorder_itr(root);
                    exit('0');
                }
                else if(l==2)
                {
                    cout<<"\nBefore ";
                    tr.inorder_itr(root);
                    root=nullptr;
                    tr.erase(root);
                    cout<<"\nAfter ";
                    tr.inorder_itr(root);
                }
                break;
            }    
            case 8:
            {
                cout<<"\nExit";
                exit('0');
            }    
            default:
                break;
        }
    }
}