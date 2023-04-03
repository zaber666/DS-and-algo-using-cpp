#include<bits/stdc++.h>
using namespace std;

# define INF 0x3f3f3f3f
# define NULL -999999
#define epsilon 0.0000001


bool fileO = false;
bool fileI = true;
ofstream fout("output.txt", ios::out);
ifstream in("input0.txt", ios::in);

class Edge
{
public:
    int u,v,w;
    Edge(int u, int v, int w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    bool operator<(const Edge& r) const
	{
		return w < r.w;
	}
};






struct Node
{
    int rank,parent;
    Node()
    {
        rank=-1;
        parent=-1;
    }
};



class disjoint_set
{
    Node* arr;
    int len;
public:
    disjoint_set(int n)
    {
        arr=new Node[n];
        len=n;
    }
    void make_set(int x)
    {
        if(arr[x].rank!=-1)
        {
            cout<< "The element already exists."<<endl;
            return;
        }
        arr[x].parent=x;
        arr[x].rank=0;
        //cout<< "Insertion Successful"<<endl;
    }
    int find_set(int x)
    {
        if(arr[x].parent == -1)
        {
            return -1;
        }
        if(arr[x].parent!=x)
            arr[x].parent=find_set(arr[x].parent);
        return arr[x].parent;
    }
    void union_set(int x,int y)
    {
        int parent1=find_set(x);
        int parent2=find_set(y);

        if(parent1==-1 || parent2 ==-1)
        {
            cout<< "Error!!"<<endl;
            return;
        }

        if(parent1==parent2)
            return;

        if(arr[parent1].rank > arr[parent2].rank)
            arr[parent2].parent = parent1;
        else
        {
            arr[parent1].parent = parent2;
            if(arr[parent1].rank == arr[parent2].rank)
                arr[parent2].rank++;
        }
        //cout<< "Union Completed"<<endl;
    }
    void print_set(int x)
    {
        int u=find_set(x);

        if(u==-1)
        {
            cout<< "No set"<<endl;
            return;
        }

        cout<< "The elements in set "<<x<< " is :"<<endl;

        for(int i=0;i<len;i++)
        {
            if(find_set(i) == u)
                cout<< i<< "  ";
        }
        cout<<endl;
    }



};

class Graph
{
    int nVertices;
    vector< pair<int, int> > *adjList;
    vector<Edge> edgeList;
    int mstCost;
public:
    Graph()
    {
        mstCost = 0;
    }
    void setnVertices(int V, int E)
    {
        nVertices = V;
        adjList = new vector< pair<int, int> > [nVertices];

    }
    void addEdge(int u, int v, int w)
    {
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
        edgeList.push_back(Edge(u,v,w));
    }
    void printPath(vector<int>& parent, int root)
    {
        for(int i=0; i<nVertices ; i++)
        {
            if(i!=root)
            {
               if(!fileO)
                    cout<< i << "  "<< parent[i] <<endl;
                else
                    fout<< i << "  "<< parent[i] <<endl;
            }

        }

    }
    void prim()
    {
        int root = rand()%nVertices;
        priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > >pq;
        vector<int>dist(nVertices, INF);
        vector<int>parent(nVertices, NULL);
        vector<bool>visited(nVertices, false);
        dist[root] = 0;
        pq.push(make_pair(0, root));
        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            if(visited[u])
                continue;
            visited[u] = true;
            for(pair<int, int> p : adjList[u])
            {
                int v = p.first;
                int w = p.second;
                if(dist[v] > w && visited[v]==false)
                {
                    dist[v] = w;
                    parent[v] = u;
                }
                pq.push(make_pair(dist[v], v));

            }
        }

        if(!fileO)
        {
            cout<< "Prim's Algorithm:"<<endl;
            cout<< "Root Node:  "<<root<<endl;
        }
        else
        {
            fout<< "Prim's Algorithm:"<<endl;
            fout<< "Root Node:  "<<root<<endl;
        }

        printPath(parent, root);

    }



    void kruskal()
    {
        vector<Edge> selected;
        disjoint_set djs(nVertices);

        for(int i=0; i<nVertices; i++)
            djs.make_set(i);

        sort(edgeList.begin(), edgeList.end() );

        for(Edge edge: edgeList)
        {
            int parentU = djs.find_set(edge.u);
            int parentV = djs.find_set(edge.v);
            if(parentU != parentV)
            {
                djs.union_set(parentU, parentV);
                selected.push_back(edge);
                mstCost+=edge.w;
            }
        }
        if(!fileO)
        {
            cout<< mstCost<<endl;
            cout<< "Kruskal's Algorithm:"<<endl;
        }
        else
        {
            fout<< mstCost<<endl;
            fout<< "Kruskal's Algorithm:"<<endl;
        }

        for(Edge edge:selected)
        {
            if(!fileO)
                cout<< edge.u << "  "<< edge.v <<endl;
            else
                fout<< edge.u << "  "<< edge.v <<endl;
        }

    }

};



vector<string> tokenize(string& line)
{
    vector<string> vect;
    int len = line.size();
    //cout<<line<< "  "<< len<<endl;
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
    int V,E;
    Graph g;


    if(!fileI)
    {
        cin>> V>>E;
        g.setnVertices(V,E);
        for(int i=0; i<E; i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            g.addEdge(u,v,w);
        }
    }
    else
    {
        int numLine = 0;
        //ifstream in("input.txt", ios::in);
        string line;
        while(!in.eof())
        {
            getline(in, line);
            vector<string>lines;
            lines = tokenize(line);
            if(numLine==0)
            {
                V = stoi(lines[0]);
                E = stoi(lines[1]);
                g.setnVertices(V,E);
                numLine++;
            }
            else
            {
                int u = stoi(lines[0]);
                int v = stoi(lines[1]);
                int w = stoi(lines[2]);
                g.addEdge(u,v,w);
                numLine++;
            }
        }
    }

    g.kruskal();
    g.prim();
}
