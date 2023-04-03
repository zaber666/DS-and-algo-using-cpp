#include<bits/stdc++.h>
using namespace std;


int ARRAY_SIZE = 10007;

string randomString()
{
    string alphabets = "qwertyuiopasdfghjklzxcvbnm";
    string result = "";
    for(int i=0; i<7; i++)
    {
        int num = rand()%26;
        result += alphabets[num];
    }
    return result;
}

static unsigned int JSHash(string str) {
	unsigned int hash = 1315423911;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash ^= ((hash << 5) + (str[i]) + (hash >> 2));
	}

	return hash%ARRAY_SIZE;
}


static unsigned int AuxHash(string str) {
    //ELFHash
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (hash << 4) + (str[i]);
		if ((x = hash & 0xF0000000) != 0)
		{
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}

	hash = hash%ARRAY_SIZE;
	if(hash == 0)
        hash = 7;
    return hash;
}

int doubleHash(string s, int iter)
{
    return (JSHash(s) + iter * AuxHash(s))%ARRAY_SIZE;
}

int customHash(string s, int iter)
{
    int C1 = 337;
    int C2 = 743;
    return (JSHash(s) + C1 * iter * AuxHash(s) + C2 * iter * iter)%ARRAY_SIZE;
}



class Node
{
public:
    int val;
    Node* next;
};


void chainingMethod()
{
    cout << "Calculating Results for Chaining Method..."<<endl;
    vector<Node*> vect(ARRAY_SIZE);
    vector<string> strings;

    int collision = 0;

    for(int i=0; i<ARRAY_SIZE; i++)
    {
        string s = randomString();
        strings.push_back(s);
        int hash = JSHash(s);

        if(vect[hash] == NULL)
        {
            Node* node = new Node();
            node->val = i;
            vect[hash] = node;
        }
        else
        {
            Node* node = new Node();
            node->val = i;

            Node* temp = vect[hash];
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = node;

            collision += 1;
        }
    }

    int probes = 0;
    for (int i=0; i<1000 ; i++)
    {
        int pos = rand()%ARRAY_SIZE;
        string s = strings[pos];
        int hash = JSHash(s);
        Node* temp = vect[hash];
        probes += 1;
        while(temp->val != pos)
        {
            temp = temp->next;
            probes += 1;
        }
    }

    cout << "Number of collisions : " << collision << endl;
    cout << "Average Probes : " << probes/1000.0 << endl << endl;
}


void doubleHashingMethod()
{
    cout << "Calculating Results for Double Hashing Method..." <<endl;
    vector<int> vect(ARRAY_SIZE, -1);
    vector<string> strings;

    int collision = 0;

    for(int i=0; i<ARRAY_SIZE; i++)
    {

        string s = randomString();
        strings.push_back(s);
        int iter = 0;
        while(true)
        {
            int hash = doubleHash(s, iter);
            if(vect[hash] == -1)
            {
                vect[hash] = i;
                break;
            }
            iter += 1;
            collision += 1;
        }

    }

    int probes = 0;
    for (int i=0; i<1000 ; i++)
    {
        int pos = rand()%ARRAY_SIZE;
        string s = strings[pos];
        int iter = 0;
        while(true)
        {
            int hash = doubleHash(s, iter);
            probes += 1;
            if(vect[hash] == pos)
                break;
            iter += 1;
        }
    }

    cout << "Number of collisions : " << collision << endl;
    cout << "Average Probes : " << probes/1000.0 << endl << endl;
}


void customHashingMethod()
{
    cout << "Calculating Results for Custom Hashing Method..." <<endl;
    vector<int> vect(ARRAY_SIZE, -1);
    vector<string> strings;

    int collision = 0;

    for(int i=0; i<ARRAY_SIZE; i++)
    {

        string s = randomString();
        strings.push_back(s);
        int iter = 0;
        while(true)
        {
            int hash = customHash(s, iter);
            if(vect[hash] == -1)
            {
                vect[hash] = i;
                break;
            }
            iter += 1;
            collision += 1;
        }

    }

    int probes = 0;
    for (int i=0; i<1000 ; i++)
    {
        int pos = rand()%ARRAY_SIZE;
        string s = strings[pos];
        int iter = 0;
        while(true)
        {
            int hash = customHash(s, iter);
            probes += 1;
            if(vect[hash] == pos)
                break;
            iter += 1;
        }
    }

    cout << "Number of collisions : " << collision << endl;
    cout << "Average Probes : " << probes/1000.0 << endl << endl;
}


int main()
{

    chainingMethod();
    doubleHashingMethod();
    customHashingMethod();


}

