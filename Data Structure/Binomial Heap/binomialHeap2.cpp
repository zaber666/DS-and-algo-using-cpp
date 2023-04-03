#include<bits/stdc++.h>
using namespace std;

bool fileO = false;
ofstream fout("output.txt", ios::out);
ifstream in("Offline_Binomial-Heap_Testcases/in3.txt", ios::in);


struct Node{
    int key;
    int degree;
    Node* p;
    Node* child;
    Node* sibling;
};


class BinomialHeap{

public:
    Node* H;
    Node* Hr;

    BinomialHeap()
    {
        H = makeBinomialHeap();
        Hr = makeBinomialHeap();

    }

    Node* makeBinomialHeap()
    {
        // Returns a pointer to a node

        Node* node;
        node = NULL;
        return node;
    }

    Node* binomialLink(Node* x, Node* y)
    {
        // Unites two B(k-1) to generate one B(k)
        x->p = y;
        x->sibling = y->child;
        y->child = x;
        y->degree = y->degree + 1;
    }

    void BinomialHeapInsert(int val)
    {
        //Insert a value

        // Make a node with given value and all pointer NULL
        Node* node = new Node;
        node->key = val;
        node->p = NULL;
        node->sibling = NULL;
        node->child = NULL;
        node->degree = 0;

        //Make another binomial heap and Union it with the original one
        Node* h1 = makeBinomialHeap();
        h1 = node;
        BinomialHeapUnion(h1);


    }

    void BinomialHeapUnion(Node* h2)
    {

        // Unites two heaps.
        Node* h = makeBinomialHeap();
        h = BinomialHeapMerge2(H, h2);
        if(h == NULL)
        {
            H = NULL;
            return;
        }

        Node* x = h; //current node I'm working with
        Node* prev_x = NULL;
        Node* next_x = x->sibling;


        while(next_x != NULL)
        {
            if(     (x->degree != next_x->degree) ||
                    ( (next_x->sibling != NULL) && (next_x->sibling->degree == x->degree) )
              )
            {

                // degree of x and next_x are different or,
                // x is the first of 3 equal degreed nodes

                prev_x = x;
                x = next_x;
            }
            else
            {
                // two consecutive equal degreed nodes

                if(x->key <= next_x->key)
                {
                    // x stores smaller value

                    x->sibling = next_x->sibling;
                    binomialLink(next_x, x);
                }
                else
                {
                    // next_x stores smaller value

                    if(prev_x == NULL)
                        h = next_x;
                    else
                        prev_x->sibling = next_x;
                    binomialLink(x, next_x);
                    x = next_x;

                }
            }
            next_x = x->sibling;
        }

        H = h;
    }

    Node* BinomialHeapMerge2(Node* h1, Node* h2)
    {
        //Will arrange the root nodes in the list in ascending order of degree.

        Node* h = makeBinomialHeap(); //h will hold the resulted root list.
        Node* temp = NULL;
        while(!(h1 == NULL && h2 == NULL))
        {
            if(h == NULL)
            {
                // We are inserting the first node in h
                if(h1 != NULL)
                {
                    if(h2 != NULL)
                    {
                        if(h1->degree < h2->degree)
                        {
                            h = h1;
                            h1 = h1->sibling;
                        }
                        else
                        {
                            h = h2;
                            h2 = h2->sibling;
                        }
                    }
                    else
                    {
                        h = h1;
                        h1 = h1->sibling;
                    }
                }
                else
                {
                    h = h2;
                    h2 = h2->sibling;

                }
                temp = h;
            }


            else
            {

                if(h1 != NULL)
                {
                    if(h2 != NULL)
                    {
                        if(h1->degree < h2->degree)
                        {
                            h->sibling = h1;
                            h = h->sibling;
                            h1 = h1->sibling;
                        }
                        else
                        {
                            h->sibling = h2;
                            h = h->sibling;
                            h2 = h2->sibling;
                        }
                    }
                    else
                    {
                        h->sibling = h1;
                        h = h->sibling;
                        h1 = h1->sibling;
                    }
                }
                else
                {
                    h->sibling = h2;
                    h = h->sibling;
                    h2 = h2->sibling;
                }
            }
        }
        return temp;
    }



    Node* ExtractMin()
    {
        Hr = NULL;
        Node* temp = NULL;
        Node* x = H;
        if(x == NULL)
        {
            return x;
        }

        //Search the min in the root list.
        int min_ = x->key;
        Node* p  = x;
        while(p->sibling != NULL)
        {
            if(p->sibling->key < min_)
            {
                min_ = p->sibling->key;
                temp = p;
                x = p->sibling;
            }
            p = p->sibling;
        }

        // x   ---->  Node with the smallest key
        // temp  -----> previous node of x. temp->sibling == x. if the first node of the list contained the smallest value temp==NULL.

        if(temp == NULL && x->sibling == NULL)
            //only one node in the root node list.
            H = NULL;
        else if(temp == NULL)
            // the smallest key was in first root node.
            H = x->sibling;
        else if(temp->sibling == NULL)

            temp = NULL;
        else
            temp->sibling = x->sibling;

        // temp holds the last root that connects every other nodes except x.

        if(x->child != NULL)
        {
            revertList(x->child);
            x->child->sibling = NULL;
        }
        BinomialHeapUnion(Hr);
        return x;


    }


    void revertList(Node* x)
    {
        if(x->sibling != NULL)
        {
            revertList(x->sibling);
            x->sibling->sibling = x;
        }
        else
            Hr = x;
    }

    Node* FindMin()
    {
        Node* temp = H;
        Node* x = NULL;
        if(temp == NULL)
            return temp;
        int min_ = temp->key;
        while(temp->sibling != NULL)
        {
            if(temp->sibling->key < min_)
            {
                min_ = temp->sibling->key;
                x = temp->sibling;
            }
            temp = temp->sibling;
        }
        if(x == NULL)
            return H;
        return x;
    }

    void printHeap()
    {
        Node* x = H;
        queue<Node*> heads;
        queue<Node*> temp;
        while(x != NULL)
        {
            if(fileO)
                fout<< "Binomial Tree, B"<<x->degree<<endl;
            else
                cout<< "Binomial Tree, B"<<x->degree<<endl;

            Node* y = new Node;
            y->child = x->child;
            y->degree = x->degree;
            y->key = x->key;
            y->p = x->p;
            y->sibling = NULL;
            y->sibling = NULL;
            heads.push(y);

            int level = 0;
            while(true)
            {
                if(heads.empty())
                    break;

                if(fileO)
                    fout<< "Level " << level << " : ";
                else
                    cout<< "Level " << level << " : ";

                while(!heads.empty())
                {
                    Node* node = heads.front();
                    while(node != NULL)
                    {
                        if(fileO)
                            fout<< node->key << " ";
                        else
                            cout<< node->key << " ";
                        if(node->child != NULL)
                            temp.push(node->child);
                        node = node->sibling;
                    }
                    heads.pop();
                }
                if(fileO)
                    fout<<endl;
                else
                    cout<<endl;
                while(!temp.empty())
                {
                    heads.push(temp.front());
                    temp.pop();
                }
                level += 1;
            }
            x = x->sibling;
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
    BinomialHeap bh;

    string line;
    while(!in.eof())
    {
        getline(in, line);
        vector<string>lines;
        lines = tokenize(line);


        if(lines[0] == "I")
        {
            int val = stoi(lines[1]);
            bh.BinomialHeapInsert(val);
        }
        else if(lines[0] == "F")
        {
            Node* x = bh.FindMin();
            if(x != NULL)
            {
                if(fileO)
                    fout << "Find-Min returned " << x->key << endl;
                else
                    cout << "Find-Min returned " << x->key << endl;
            }

        }
        else if(lines[0] == "E")
        {
            Node* x = bh.ExtractMin();
            if(x != NULL)
            {
                if(fileO)
                    fout << "Extract-Min returned " << x->key << endl;
                else
                    cout << "Extract-Min returned " << x->key << endl;
            }
        }
        else if(lines[0] == "P")
        {
            if(fileO)
                fout<< "Printing Binomial Heap..."<<endl;
            else
               cout<< "Printing Binomial Heap..."<<endl;
            bh.printHeap();
        }
        else
        {
            vector<int> vect;
            int len = lines.size();
            for(int i=1; i<len; i++)
                vect.push_back(stoi(lines[i]));

            BinomialHeap bh1;
            for(int i=0; i<len-1; i++)
                bh1.BinomialHeapInsert(vect[i]);
            bh.BinomialHeapUnion(bh1.H);
        }



    }



}
