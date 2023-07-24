#include <iostream>
using namespace std;

class node {
    node* l;
    node* r;
    int data;

public:
    node()
    {
        l = r = nullptr;
        data = 0;
    }
    friend class avl;
};

class avl {
public:
    node* insert(node*, int);
    int height(node*);
    int bf(node*);
    node* rightr(node*);
    node* leftr(node*);
    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    node* delete_(node*, int);
    node* success(node*);
};

node* avl::rightr(node* r)
{
    node* x = r->l;
    node* y = x->r;
    x->r = r;
    r->l = y;
    return x;
}

node* avl::leftr(node* r)
{
    node* x = r->r;
    node* y = x->l;
    x->l = r;
    r->r = y;
    return x;
}

void avl::inorder(node* r)
{
    if (r == nullptr)
        return;

    inorder(r->l);
    cout << "\t" << r->data;
    inorder(r->r);
}

void avl::preorder(node* r)
{
    if (r == nullptr)
        return;

    cout << "\t" << r->data;
    preorder(r->l);
    preorder(r->r);
}

void avl::postorder(node* r)
{
    if (r == nullptr)
        return;

    postorder(r->l);
    postorder(r->r);
    cout << "\t" << r->data;
}

int avl::bf(node* r)
{
    if (r == nullptr)
        return 0;
    return (height(r->l) - height(r->r));
}

int avl::height(node* r)
{
    if (r == nullptr)
        return 0;

    int a = height(r->l);
    int b = height(r->r);

    return max(a, b) + 1;
}

node* avl::insert(node* r, int data)
{
    if (r == nullptr) {
        node* r = new node();
        r->data = data;
        return r;
    }
    if (data < r->data)
        r->l = insert(r->l, data);
    else
        r->r = insert(r->r, data);

    int baf = bf(r);

    if (baf == 2) {
        if (bf(r->l) == 1)
            return rightr(r);
        else {
            r->l = leftr(r->l);
            return rightr(r);
        }
    }
    if (baf == -2) {
        if (bf(r->r) == -1)
            return leftr(r);
        else {
            r->r = rightr(r->r);
            return leftr(r);
        }
    }
    return r;
}

node* avl::delete_(node* r, int key)
{
    if (r == nullptr)
        return nullptr;
    else if (key < r->data)
        r->l = delete_(r->l, key);
    else if (key > r->data)
        r->r = delete_(r->r, key);
    else {
        if (r->l == nullptr || r->r == nullptr) {
            node* t = nullptr;
            if (!r->l)
                t = r->r;
            else
                t = r->l;
            delete r;
            return t;
        } 
        else {
            node* t = success(r->r);
            r->data = t->data;
            r->r = delete_(r->r, t->data);
        }
    }

    int baf = bf(r);

    if (baf == 2) {
        if (bf(r->l) == 1)
            return rightr(r);
        else {
            r->l = leftr(r->l);
            return rightr(r);
        }
    }
    if (baf == -2) {
        if (bf(r->r) == -1)
            return leftr(r);
        else {
            r->r = rightr(r->r);
            return leftr(r);
        }
    }
    return r;
}

node* avl::success(node* r)
{
    if (r == nullptr || r->l == nullptr)
        return r;
    return success(r->l);
}

int main()
{
    node* r = nullptr;
    int n, ele;
    cin >> n;

    avl obj;

    for (int i = 0; i < n; i++) {
        cin >> ele;
        r = obj.insert(r, ele);
    }

    
    obj.inorder(r);
    return 0;
}