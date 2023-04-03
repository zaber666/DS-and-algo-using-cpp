#include<bits/stdc++.h>
#define RED 1
#define BLACK 0
using namespace std;


bool fileO = false;
ofstream fout("output.txt", ios::out);
ifstream in("input.txt", ios::in);


struct Node{
    int key;
    int color;
    Node* p;
    Node* left;
    Node* right;
};


class RedBlackTree
{

public:
    Node* root;
    Node* NIL;

    RedBlackTree()
    {
        NIL = new Node();
        NIL->color = BLACK;
        NIL->key = -999999;
        NIL->p = NULL;
        NIL->left = NULL;
        NIL->right = NULL;
        root = NIL;
    }

    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if(y->left != NIL)
            y->left->p = x;
        y->p = x->p;
        if(x->p == NIL)
            root = y;
        else if(x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
        y->left = x;
        x->p = y;
    }

    void rightRotate(Node* y)
    {
        Node* x = y->left;
        y->left = x->right;
        if(x->right != NIL)
            x->right->p = y;
        x->p = y->p;
        if(y->p == NIL)
            root = x;
        else if(y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;

        x->right = y;
        y->p = x;
    }

    void insert_(int val)
    {
        Node* node = new Node;
        node->key = val;
        node->color = -1;
        node->p = NULL;
        node->left = NULL;
        node->right = NULL;
        redBlackInsert(node);
    }
    void printNode(Node* z)
    {
        cout << z->key << "   " <<z->color<<endl;
    }

    void redBlackInsert(Node* z)
    {

        Node* y = NIL;
        Node* x = root;
        while(x != NIL)
        {
            y = x;
            if(z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->p = y;
        if(y == NIL)
            root = z;
        else if(z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = NIL;
        z->right = NIL;
        z->color = RED;
        redBlackInsertFixup(z);
    }

    void redBlackInsertFixup(Node* z)
    {
        if(z->p == root)
        {
            z->p->color = BLACK;
            return;
        }
        while(z->p->color == RED)
        {

            if(z->p == z->p->p->left)
            {

                Node* y = z->p->p->right;
                if(y->color == RED)
                {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else
                {
                    if(z == z->p->right)
                    {
                        z = z->p;
                        leftRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    rightRotate(z->p->p);
                }
            }
            else
            {

                Node* y = z->p->p->left;
                if(y->color == RED)
                {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                }
                else
                {

                    if(z == z->p->left)
                    {
                        z = z->p;
                        rightRotate(z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    leftRotate(z->p->p);
                }
            }
        }
        if(root->color == RED)
            root->color = BLACK;

    }

    void redBlackTransplant(Node* u, Node* v)
    {
        if(u->p == NIL)
            root = v;
        else if(u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;
        v->p = u->p;
    }

    void redBlackDelete(Node* z)
    {

        Node* y = z;
        Node* x = NIL;
        int y_orig_color = y->color;
        if(z->left == NIL)
        {
            x = z->right;
            redBlackTransplant(z, z->right);
        }
        else if(z->right == NIL)
        {
            x = z->left;
            redBlackTransplant(z, z->left);
        }
        else
        {
            y = tree_min(z->right);
            y_orig_color = y->color;
            x = y->right;
            if(y->p == z)
                x->p = y;
            else
            {
                redBlackTransplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            redBlackTransplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }
        if(y_orig_color == BLACK)
            redBlackDeleteFixup(x);
    }

    void redBlackDeleteFixup(Node* x)
    {
        while( (x != root ) && (x->color == BLACK) )
        {
            if(x == x->p->left)
            {
                Node* w = x->p->right;
                if(w->color == RED)
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if( (w->left->color == BLACK) && (w->right->color == BLACK) )
                {
                    w->color = RED;
                    x = x->p;
                }
                else
                {

                    if(w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->p->right;
                    }

                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->right->color = BLACK;

                    leftRotate(x->p);
                    x = root;
                }
            }
            else
            {

                Node* w = x->p->left;
                if(w->color == RED)
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if( (w->right->color == BLACK) && (w->left->color == BLACK) )
                {
                    w->color = RED;
                    x = x->p;
                }
                else
                {
                    if(w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    bool searchValue(int val, Node* node)
    {
        if(node == NIL)
            return false;
        else if(node->key == val)
            return true;
        else
        {
            if(val < node->key)
                searchValue(val, node->left);
            else
                searchValue(val, node->right);
        }
    }


    Node* searchNode(int val, Node* node)
    {
        if(node == NIL)
            return NIL;
        else if(node->key == val)
            return node;
        else
        {
            if(val < node->key)
                searchNode(val, node->left);
            else
                searchNode(val, node->right);
        }
    }

    void delete_(int val)
    {
        Node* node = searchNode(val, root);
        if(node != NIL)
            redBlackDelete(node);
    }

    Node* tree_min(Node* z)
    {
        if(z->left == NIL)
            return z;
        return tree_min(z->left);
    }
    void printGraph(Node* node)
    {
        if(node == NIL)
            return;

        if(!fileO)
            cout << node->key << ":";
        else
            fout << node->key << ":";

        if(node->color == RED)
        {
            if(!fileO)
                cout << "r";
            else
                fout << "r";
        }
        else
        {
            if(!fileO)
                cout << "b";
            else
                fout << "b";
        }

        if((node->left == NIL) && (node->right == NIL))
            return;
        else
        {
            if(!fileO)
                cout << "(";
            else
                fout << "(";

            printGraph(node->left);

            if(!fileO)
                cout << ")(" ;
            else
                fout << ")(";
            printGraph(node->right);
            if(!fileO)
                cout << ")";
            else
                fout << ")";
        }



    }




};


vector<string> tokenize(string& line)
{
    vector<string> vect;
    int len = line.size();
    int start=0;
    int index=0;
    while(true && start<len)
    {

        if(line.at(index)== ' ' || line.at(index)== '\n' || index == len-1)
        {
            if(index==len-1)
            {
                vect.push_back(line.substr(start, index-start+1));
                index++;
            }
            else
            {
                vect.push_back(line.substr(start, index-start));
                index++;
                start = index;
            }

        }
        else
            index++;
        if(index >= len)
            break;


    }
    return vect;
}


int main()
{
    RedBlackTree T;
    string line;
    while(!in.eof())
    {
        getline(in, line);
        vector<string>lines;
        lines = tokenize(line);

        if(lines[0] == "I")
        {
            int val = stoi(lines[1]);
            T.insert_(val);
            T.printGraph(T.root);
            if (!fileO)
                cout<<endl;
            else
                fout<<endl;
        }
        else if(lines[0] == "D")
        {
            int val = stoi(lines[1]);
            T.delete_(val);
            T.printGraph(T.root);
            if (!fileO)
                cout<<endl;
            else
                fout<<endl;
        }
        else if(lines[0] == "F")
        {
            int val = stoi(lines[1]);
            if(T.searchValue(val, T.root))
            {
                if(!fileO)
                    cout << "True" << endl;
                else
                    fout << "True" << endl;
            }

            else
            {
                if(!fileO)
                    cout << "False" << endl;
                else
                    fout << "False" << endl;
            }

        }



    }
}
