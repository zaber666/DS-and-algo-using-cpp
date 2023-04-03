#include<iostream>
#include<cstdlib>
using namespace std;

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int* color;
	int* parent;
	int* dist;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u, bool out=true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    color = new int[nVertices];
    dist=new int[nVertices];
    parent = new int[nVertices];

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
    nEdges++;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return ;
    matrix[u][v]=0;
    if(!directed) matrix[v][u]=0;
    nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(matrix[u][v]==1)
        return true;
    return false;
}

int Graph::getDegree(int u,bool out)
{
    //returns the degree of vertex u
    int cnt=0;
    if(out)
    {
        for(int i=0;i<nVertices;i++)
        {
            if(matrix[u][i]==1)
                cnt++;
        }
    }
    else
    {
        if(!directed)
        {
            for(int i=0;i<nVertices;i++)
            {
                if(matrix[u][i]==1)
                    cnt++;
            }
        }
        else
        {
            for(int i=0;i<nVertices;i++)
            {
                if(matrix[i][u]==1)
                    cnt++;
            }
        }
    }
    return cnt;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i]==1)
            cout<<i << "  ";
    }
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i]==1)
        {
            if(matrix[v][i]==1)
                return true;
        }
    }
    return false;

}

void Graph::bfs(int source)
{
    //write this function
    for(int i=0;i<nVertices;i++)
    {
        if(i!=source)
        {
            color[i]= WHITE;
            dist[i]=INFINITY;
            parent[i]=NULL_VALUE;
        }
    }
    color[source]=GREY;
    dist[source]=0;
    parent[source]=NULL_VALUE;
    Queue q;
    q.enqueue(source);
    while(!q.empty())
    {
        int u=q.dequeue();
        for(int i=0;i<nVertices;i++)
        {
            if(matrix[u][i]==1&&color[i]==WHITE)
            {
                color[i]=GREY;
                dist[i]=dist[u]+1;
                parent[i]=u;
                q.enqueue(i);
            }
        }
        color[u]=BLACK;

    }


}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);

    return dist[v];
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    for(int i=0;i<nVertices;i++)
        delete[] matrix[i];
    delete[] matrix;
    delete[] color;
    delete[] parent;
    delete[] dist;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove Edge  \n3. isEdge  \n4. get Degree \n5.Print Adjacent Vertices \n6.Has Common adjacent Vertices \n7. Get Distance . \n8. Print Graph  \n9. Exit.\n");
        cout<<endl;
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            cout<< "Input 2 vertices:  ";
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
            cout<<"Edge Added."<<endl;
        }
        else if(ch==2)
        {
            int u, v;
            cout<< "Input 2 Vertices:  ";
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
            cout<< "Edge Removed."<<endl;
        }
        else if(ch==3)
        {
            int u, v;
            cout<< "Input 2 vertices:  ";
            scanf("%d%d", &u, &v);
            cout<<(g.isEdge(u,v)? "YES": "NO")<<endl;
        }
        else if(ch==4)
        {
            int u;
            cout<< "Enter Vertice:  ";
            cin>>u;
            cout<< "1.Out Degree\n2.In Degree"<<endl;
            int x;
            cin>>x;
            if(x==1)
                cout<<"Out Degree is: " <<g.getDegree(u)<<endl;
            else
                cout<< "In Degree is:  "<< g.getDegree(u,false)<<endl;
        }
        else if(ch==5)
        {
            int u;
            cout<< "Enter Vertice:  ";
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==6)
        {
            int u,v;
            cout<< "Enter 2 vertices:   ";
            cin>>u>>v;
            cout<< (g.hasCommonAdjacent(u,v)? "YES":"NO")<<endl;
        }
        else if(ch==7)
        {
            int u,v;
            cout<< "Enter 2 vertices:   ";
            cin>>u>>v;
            cout<< "Distance:  "<< g.getDist(u,v)<<endl;
        }
        else if(ch==8)
        {
            g.printGraph();
        }
        else if(ch==9)
        {
            break;
        }
    }

}
