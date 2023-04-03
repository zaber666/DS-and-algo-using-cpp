#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

ofstream fout("output.txt", ios::out);

class Graph
{
    int nVertices;
    vector<pair<int, int>> *adjList;
    int dest_;
public:
    Graph();
    void setup(int V);
    void addEdge(int u, int v, int w);
    void Bellman_ford(int src, int destination);
    void dijkstra(int src, int destination);
    void printPath(vector<int>& vect, int dest);
};

Graph::Graph()
{
    cout<< "created"<<endl;
}
void Graph::setup(int V)
{
    nVertices = V;
    adjList = new vector<pair<int, int>>[nVertices];
}

void Graph::printPath(vector<int>& vect, int dest)
{
    if(vect[dest]!=-1)
        printPath(vect, vect[dest]);
    if(dest != dest_)
        fout<< dest << " -> ";
    else
        fout<<dest;
}

void Graph::addEdge(int u, int v, int w)
{
    adjList[u].push_back(make_pair(v, w));
}

void Graph::Bellman_ford(int src, int destination)
{
    vector<int> dist(nVertices, INF);
    vector<int> parent(nVertices, -1);
    dist[src] = 0;
    for(int i=0; i<nVertices-1; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            for(pair<int, int> p: adjList[j])
            {
                int u = j;
                int v = p.first;
                if (dist[v] > dist[u]+p.second)
                {
                    dist[v] = dist[u]+p.second;
                    parent[v] = u;
                }

            }
        }
    }

    fout<< "Bellman Ford Algorithm."<<endl;
    int x = 0;

    for(int j=0; j<nVertices; j++)
    {

        for(pair<int, int>p:adjList[j])
        {
            int u = j;
            int v = p.first;
            if(dist[v]>dist[u]+p.second)
            {
                fout<< "Negative Cycle Present."<<endl;
                x=1;
                break;
            }
        }
        if(x==1)
            break;
    }
    if(x==0)
    {
        fout<<dist[destination]<<endl;
        dest_ = destination;
        printPath(parent, destination);
        fout<<endl;
    }

}

void Graph::dijkstra(int src, int destination)
{
    vector<int> dist(nVertices, INF);
    vector<int> parent(nVertices, -1);
    vector<bool> visited(nVertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > q;
    dist[src] = 0;
    q.push(make_pair(0, src));
    while(!q.empty())
    {
        int u = q.top().second;
        q.pop();
        if(visited[u] == true)
            continue;
        visited[u] = true;
        //cout<<u<<endl;
        for(pair<int, int>p:adjList[u])
        {
            int w = abs(p.second);
            int v = p.first;
            //cout<<v << "   "<<w<<endl;
            if(dist[v]>dist[u]+w)
            {
                dist[v] = dist[u]+w;
                parent[v] = u;
            }

            q.push(make_pair(dist[v], v));
        }
        //break;
    }
    fout<< "Dijkstra Algorithm."<<endl;
    fout<<dist[destination]<<endl;
    dest_ = destination;
    printPath(parent, destination);
    fout<<endl;


}



vector<string> tokenize(string& line)
{
    vector<string> vect;
    int len = line.size();
    int start=0;
    int index=0;
    while(true)
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
//    int V,E;
//    cin>>V>>E;
//    Graph g;
//    g.setup(V);
//    cout<<E<<endl;
//    for(int i=0;i<E;i++)
//    {
//        int u,v,w;
//        cin>>u>>v>>w;
//        g.addEdge(u,v,w);
//    }
//    int src, dest;
//    cin>>src>>dest;
//    g.Bellman_ford(src, dest);
//    g.dijkstra(src, dest);


//    string str = "Iam Zaber";
//    bool a = (str[2] == 'm') ;
//    cout<< a;
//    return 0;


    ifstream in("input.txt", ios::in);
    int numLine = 0;
    int V=0, E=0, src=0, dest=0;
    Graph g;
    string line;
    while(!in.eof())
    {
        getline(in, line);

        vector<string>lines;
        lines = tokenize(line);
//        for(int i=0; i<lines.size(); i++)
//            cout<< lines[i]<< "         ";
//        cout<< endl;
        if(numLine==0)
        {
            V = stoi(lines[0]);
            E = stoi(lines[1]);
            g.setup(V);
            numLine++;
        }
        else if(numLine <= E)
        {
            int u = stoi(lines[0]);
            int v = stoi(lines[1]);
            int w = stoi(lines[2]);
            //cout<< u << "  "<< v << "  "<< w << endl;
            g.addEdge(u,v,w);
            numLine++;
        }
        else
        {
            src = stoi(lines[0]);
            dest = stoi(lines[1]);
        }


    }

    g.Bellman_ford(src, dest);
    g.dijkstra(src, dest);
    in.close();
    fout.close();

}

