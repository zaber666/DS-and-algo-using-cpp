#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};


class binary_Search_Tree
{
    Node* root;

    Node* insert_inside(Node* root, int val)
    {
        if(root==NULL)
        {
            Node* newNode=new Node;
            newNode->data=val;
            newNode->left=NULL;
            newNode->right=NULL;
            root=newNode;
        }
        else
        {
            if(root->data < val)
                 root->right = insert_inside(root->right,val);
            else
                root->left = insert_inside(root->left,val);
        }
        return root;
    }


    void inorder(Node* root)
    {
        if(root==NULL)
            return ;
        inorder(root->left);
        cout<< root->data << "  ";
        inorder(root->right);
    }


    void preorder(Node* root)
    {
        if(root==NULL)
            return ;
        cout<< root->data << "  ";
        preorder(root->left);
        preorder(root->right);
    }

    bool inSearch(Node* root, int x)
    {

        if(root==NULL)
            return false;
        else if(root->data==x)
            return true;
        else
        {
            if(root->data < x)
                inSearch(root->right,x);
            else
                inSearch(root->left,x);
        }
    }


    Node* findMin(Node* root)
    {
        if(root->left==NULL)
            return root;
        else
            return findMin(root->left);
    }


    Node* delete_inside(Node* root, int x)
    {
        if(root->data < x)
            root->right=delete_inside(root->right,x);
        else if( root->data > x)
            root->left=delete_inside(root->left,x);
        else if(   (root->left!=NULL)  &&  (root->right!=NULL)   )
        {
            Node* temp=findMin(root->right);
            root->data=temp->data;
            root->right=delete_inside(root->right,temp->data);
        }
        else
        {
            Node* temp=root;
            if(root->left==NULL)
                root=root->right;
            else if(root->right==NULL)
                root=root->left;
            delete temp;
        }

        return root;
    }



public:


    binary_Search_Tree()
    {
        root=NULL;
    }


    void Insert(int x)
    {
        if(inSearch(root,x))
            cout<< "The Element is Already Present. Insertion did not happened."<<endl;
        else
        {
            root=insert_inside(root,x);
            cout<< "Successful Insertion."<<endl;
        }
    }

    void Inorder()
    {
        inorder(root);
    }

    void Preorder()
    {
        preorder(root);
    }

    bool Search(int x)
    {
        return (inSearch(root,x)?true:false);
    }


    void Delete(int x)
    {
        if(!inSearch(root,x))
            cout<< "There is no such Element."<<endl;
        else
        {
            root=delete_inside(root,x);
            cout<< "Element Deleted"<<endl;
        }

    }



};


int main()
{
    binary_Search_Tree bst;
    cout<< "                                                BINARY SEARCH TREE "<<endl<< "Operations: "<<endl;
    cout<< "1.Search"<<endl << "2.Insert"<<endl<< "3.Delete"<<endl<< "4.Inorder traversal"<< endl<< "5.Preorder traversal"<<endl<< "6.Quit"<<endl;
    int num;
    cout<<endl;
    while(1)
    {
        cout<< "Enter your Choice: ";
        int optn;
        cin>>optn;
        if(optn==6)
            break;
        else if(optn==1)
        {
            cout<< "Number To Be Searched: ";
            cin>>num;
            if(bst.Search(num))
                cout<< "The Number Is Present"<<endl;
            else
                cout<< "The Number Is not Present"<<endl;
        }
        else if(optn==2)
        {
            cout<< "Number To be Inserted: ";
            cin>>num;
            bst.Insert(num);
        }
        else if(optn==3)
        {
            cout<< "Number to be deleted: ";
            cin>>num;
            bst.Delete(num);
        }
        else if(optn==4)
        {
            cout<< "Inorder:   ";
            bst.Inorder();
            cout<<endl;
        }
        else if(optn==5)
        {
            cout<< "Preorder:   ";
            bst.Preorder();
            cout<<endl;
        }
        cout<<endl;
    }


}
