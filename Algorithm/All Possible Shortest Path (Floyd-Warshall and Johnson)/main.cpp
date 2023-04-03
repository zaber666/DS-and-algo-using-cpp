#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
# define NULL -999999
#define epsilon 0.0000001

bool fileI = false;
bool fileO = true;

ofstream fout("output.txt", ios::out);
ifstream fin("input.txt", ios::in);

class Edge
{

public:
    int source, destination;
    double weight;

    Edge(int s, int d, double w)
    {
        source = s;
        destination = d;
        weight = w;
    }
    int getSource()
    {
        return source;
    }
    int getDestination()
    {
        return destination;
    }
    double getWeight()
    {
        return weight;
    }
    void setWeight(double val)
    {
        weight = val;
    }

};

class comparatorCls
{
public:
    int operator()(const Edge& edge1, const Edge& edge2)
    {
        return edge1.weight > edge2.weight;
    }
};




//bool operator<(const Edge& edge1, const Edge& edge2)
//{
//    return edge1.weight > edge2.weight;
//}


class Graph
{
    int nVertices;
    vector<Edge> *adjList;
    vector<Edge> *modifiedAdjList;
    double** distanceMatrix;
    int** parentMatrix;
    vector<int>bellmanH;
public:
    Graph()
    {

    }
    void setnVertices(int V)
    {
        nVertices = V;
        adjList = new vector<Edge>[nVertices];
        modifiedAdjList = new vector<Edge>[nVertices+1];

        distanceMatrix = new double*[nVertices];
        parentMatrix = new int*[nVertices];
        for(int i=0; i<nVertices; i++)
        {
            distanceMatrix[i] = new double[nVertices];
            parentMatrix[i] = new int[nVertices];
            for(int j=0; j<nVertices; j++)
            {
                distanceMatrix[i][j] = INF;
                parentMatrix[i][j] = -1;

            }
        }

    }
    bool addEdge(int u, int v, double w)
    {
        adjList[u].push_back(Edge(u, v, w));
    }
    void printGraph()
    {

        fout<< "Graph:"<<endl;
        for(int u=0; u<nVertices; u++)
        {

            fout << u+1 << ":   ";
            int len = adjList[u].size();
            int c = 0;
            for(Edge edge: adjList[u])
            {
                c++;
                fout<< edge.getDestination()+1 << "(" << edge.getWeight() << ")";
                if(c<len)
                    fout<< "-->";
            }
            fout<<endl;
        }
        fout<< endl;
    }
    int isEdge(int u, int v)
    {
        int index = 0;
        for(Edge edge: adjList[u])
        {
            if(edge.getDestination() == v)
                return index;
            index++;
        }
        return -1;
    }
    void removeEdge(int u, int v)
    {
        int position = isEdge(u, v);
        if(position != -1)
        {
            adjList[u].erase(adjList[u].begin() + position);
        }
    }
    Edge* searchEdge(int u, int v)
    {
        int len = adjList[u].size();
        Edge* ptr = adjList[u].data();
        for(int i=0; i<len; i++)
        {
            if(ptr->getDestination() == v)
                return ptr;
            ptr++;
        }
        return nullptr;
    }
    void reweightEdge(int u, int v, double w)
    {
        Edge *edge = searchEdge(u,v);
        edge->setWeight(w);

    }
    double getWeight(int u, int v)
    {
        Edge *edge = searchEdge(u,v);
        if(edge == nullptr)
            return NULL;
        else
            return edge->getWeight();
    }

    void cleanSPinfo()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                distanceMatrix[i][j] = INF;
                parentMatrix[i][j] = -1;
            }
        }
    }

    void floydWarshall()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(Edge edge: adjList[i])
            {
                int u = edge.getSource();
                int v = edge.getDestination();
                double w = edge.getWeight();
                distanceMatrix[u][v] = w;
                parentMatrix[u][v] = u;
            }
        }
        for(int i=0; i<nVertices; i++)
            distanceMatrix[i][i] = 0;

        for(int k = 0; k<nVertices; k++)
        {
            for(int i=0; i<nVertices; i++)
            {
                for(int j=0; j<nVertices; j++)
                {
                    if(distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j])
                    {
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j];
                    }
                }
            }
        }
    }

    bool BellmanFord(int src)
    {
        vector<int> dist(nVertices, 0);
        dist[src] = 0;


        for(int k=0; k<nVertices; k++)
        {
            for(int u=0; u<=nVertices; u++)
            {
                Edge* ptr = modifiedAdjList[u].data();
                int len = modifiedAdjList[u].size();
                for(int i=0; i<len; i++)
                {
                    int dest = ptr->getDestination();
                    double wt = ptr->getWeight();
                    if(   dist[dest]-dist[u]-wt > epsilon     )
                    {
                        dist[dest] = dist[u]+wt;
                    }

                    ptr++;
                }
            }
        }


        for(int u=0; u<=nVertices; u++)
        {
            Edge* ptr = modifiedAdjList[u].data();
            int len = modifiedAdjList[u].size();
            for(int i=0; i<len; i++)
            {
                int dest = ptr->getDestination();
                double wt = ptr->getWeight();
                if(   dist[dest]-dist[u]-wt > epsilon     )
                    return false;
                ptr++;
            }
        }
        for(int i=0; i<nVertices; i++)
        {
            bellmanH.push_back(dist[i]);
        }
        return true;
    }

    void dijkstra(int src)
    {
        vector<bool>visited(nVertices, false);
        priority_queue<Edge, vector<Edge>, comparatorCls> pq;
        distanceMatrix[src][src] = 0;
        pq.push(Edge(src, -1, 0));
        while(!pq.empty())
        {
            Edge edge = pq.top();
            pq.pop();
            int u = edge.getSource();
            if(visited[u] == true)
                continue;
            visited[u] = true;
            for(Edge edge: adjList[u])
            {
                int v = edge.getDestination();
                double wt = edge.getWeight();
                if( distanceMatrix[src][v] > distanceMatrix[src][u]+wt)
                {
                    distanceMatrix[src][v] = distanceMatrix[src][u]+wt;
                    parentMatrix[src][v] = u;
                }

                pq.push(Edge(v, -1, distanceMatrix[src][v]));
            }
        }
    }

    void johnsonsAlgo()
    {
        // ================Define New Edges==============
        for(int i=0; i<nVertices; i++)
        {
            for(Edge edge: adjList[i])
            {
                modifiedAdjList[i].push_back(edge);
            }
        }
        for(int i=0; i<nVertices; i++)
            modifiedAdjList[nVertices].push_back(Edge(nVertices, i, 0.0));



        bool flag = BellmanFord(nVertices);
        if(!flag)
        {
            fout<< "There is a negative weight cycle"<<endl;
            return;
        }


        for(int u=0; u<nVertices; u++)
        {
            Edge* ptr = adjList[u].data();
            int len = adjList[u].size();
            for(int i=0; i<len; i++)
            {
                int dest = ptr->getDestination();
                double wt = ptr->getWeight();
                ptr->setWeight(wt + bellmanH[u]-bellmanH[dest]);
                ptr++;
            }
        }

        for(int src=0; src<nVertices; src++)
        {
            dijkstra(src);
        }

        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(i!=j)
                    distanceMatrix[i][j] = distanceMatrix[i][j]-bellmanH[i]+bellmanH[j];
            }
        }

        for(int u=0; u<nVertices; u++)
        {
            Edge* ptr = adjList[u].data();
            int len = adjList[u].size();
            for(int i=0; i<len; i++)
            {
                int dest = ptr->getDestination();
                double wt = ptr->getWeight();
                ptr->setWeight(wt - bellmanH[u]+bellmanH[dest]);
                ptr++;
            }
        }
    }

    double getShortestPathWeight(int u, int v)
    {
        return distanceMatrix[u][v];
    }

    void printShortestPath(int u, int v)
    {

        if(parentMatrix[u][v]==-1)
        {
            fout<< v+1;
            return;
        }
        int x = parentMatrix[u][v];
        printShortestPath(u,x);
        fout<< "-->" << v+1 << "(" <<getWeight(x,v)<< ")";
    }

    void printDistanceMatrix()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(distanceMatrix[i][j]!=INF)
                    fout<< distanceMatrix[i][j]<< "   ";
                else
                    fout<< "INF"<< "   ";
            }
            fout<< endl;
        }
    }
    void printPredecessorMatrix()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(parentMatrix[i][j]==-1)
                    fout<< "NIL   ";
                else
                    fout<< parentMatrix[i][j]+1<< "   ";
            }
            fout<< endl;

        }
        fout<<endl;
    }

    ~Graph()
    {
        for(int i=0; i<nVertices; i++)
        {
            delete[] distanceMatrix[i];
            delete[] parentMatrix[i];
//            delete[] adjList[i];
//            delete[] modifiedAdjList[i];
        }
        delete[] distanceMatrix;
        delete[] parentMatrix;
        delete[] adjList;
        delete[] modifiedAdjList;
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
    Graph g;
    int V,E;
    if(!fileI)
    {
        cin>>V>>E;
        g.setnVertices(V);
        for(int i=0; i<E; i++)
        {
            int u,v;
            double w;
            cin>> u>>v>>w;
            g.addEdge(u-1,v-1,w);
        }
        fout<< "Graph Created"<<endl;
    }
    else{

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
    while(true)
    {
        int choice;
        cin >>choice;
        if(choice == 1)
        {
            g.cleanSPinfo();
            fout<< "ASAP matrices cleared."<<endl;
        }
        else if(choice==2)
        {
            g.floydWarshall();
            fout<< "Floyd-Warshall Algorithm Implemented"<<endl;
        }
        else if(choice == 3)
        {
            g.johnsonsAlgo();
            fout<< "Johnson's algorithm implemented"<<endl;
        }
        else if(choice==4)
        {
            int u,v;
            cin>>u>>v;
            if(g.getShortestPathWeight(u-1, v-1)==INF)
            {
                fout<< "No Path Exists."<<endl;
            }
            else
            {
                fout<< "Shortest Path Weight:  "<< g.getShortestPathWeight(u-1,v-1)<<endl;
                fout<< "Path:  ";
                g.printShortestPath(u-1,v-1);
                fout<<endl;
            }

        }
        else if(choice == 5)
        {
            g.printGraph();
        }
        else if(choice == 6)
        {
            fout<< "Distance Matrix:"<<endl;
            g.printDistanceMatrix();
        }
        else if(choice == 7)
        {
            fout<< "Predecessor Matrix:"<<endl;
            g.printPredecessorMatrix();
        }
        else
        {
            fout.close();
            return 0;
        }

    }





}


