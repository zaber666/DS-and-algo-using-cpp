#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<chrono>
#include<typeinfo>
#include<fstream>
#include<string>
using namespace std;
using namespace std::chrono;

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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int* color;
	int* parent;
	int* dist;
	int* d_color;
	int* d_parent;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source);
	void dfs_visit(int source);

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) //delete previous list
    {
        delete[] adjList;
        //delete[] parent;
        //delete[] color;
        //delete[] dist;
    }
	adjList = new ArrayList[nVertices] ;
	parent = new int[nVertices];
	dist= new int[nVertices];
	color=new int[nVertices];
	d_color = new int[nVertices];
	d_parent = new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)  //vertex out of range
    {
        cout<< "Vertex Out of range"<<endl;
        return;
    }
    if(isEdge(u,v))
    {
        cout<< "Edge already exists."<<endl;
        return;
    }
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
	cout<< "Edge Added."<< endl;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout<< "Vertex Out of bound"<<endl;
        return;
    }
    if(!isEdge(u,v))
    {
        cout<< "No Edge Exists."<<endl;
        return;
    }
    this->nEdges-- ;
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
    cout<< "Edge Removed"<<endl;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)!=NULL_VALUE)
        return true;
    return false;

}

int Graph::getOutDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}

int Graph::getInDegree(int u)
{
    //returns the degree of vertex u
    if(!directed)
    {
        return adjList[u].getLength();
    }
    else
    {
        int cnt=0;
        for(int i=0;i<nVertices;i++)
        {
            if(adjList[i].searchItem(u)!=NULL_VALUE)
                cnt++;
        }
        return cnt;

    }
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    adjList[u].printList();
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int lenu=adjList[u].getLength();
    int lenv=adjList[v].getLength();
    for(int i=0;i<lenu;i++)
    {
        int node=adjList[u].getItem(i);
        if(adjList[v].searchItem(node)!=NULL_VALUE)
            return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
    for(int i=0;i<nVertices ;i++)
    {
        if(i!=source)
        {
            color[i]= WHITE;
            dist[i]=INFINITY;
            parent[i]=NULL_VALUE;
        }
    }
    color[source]=GREY;
    cout<< source << "   ";
    dist[source]=0;
    parent[source]=NULL_VALUE;
    Queue q;
    q.enqueue(source);
    while(!q.empty())
    {
        int u=q.dequeue();
        int len=adjList[u].getLength();
        for(int i=0;i<len;i++)
        {
            int element=adjList[u].getItem(i);
            if(color[element]==WHITE)
            {
                dist[element]=dist[u]+1;
                cout<< element << "   ";
                color[element]=GREY;
                parent[element]=u;
                q.enqueue(element);
            }
        }
        color[u]=BLACK;
    }

    cout<< endl ;
}

void Graph::dfs_visit(int u)
{
    d_color[u] = GREY;
    int len = adjList[u].getLength();
    cout<< u << "  ";
    for(int i=0;i<len;i++)
    {
        int element = adjList[u].getItem(i);
        if(d_color[element]==WHITE)
        {
            d_parent[element] = u;
            dfs_visit(element);
        }
    }
    d_color[u] = BLACK;
}


void Graph::dfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        d_color[i] = WHITE;
        d_parent[i] = NULL_VALUE;
    }
    dfs_visit(source);
    cout<< endl;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return dist[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    delete[] adjList;
    delete[] parent;
    delete[] color;
    delete[] dist;
    delete[] d_color;
    delete[] d_parent;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph    3. Runtime Calculation\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;
    else
    {

        cout<< "1. Directed Graph\n2. Undirected Graph\nEnter Choice:  ";
        int x;
        bool dir;
        cin>>x;
        if(x==1)
            dir = true;
        else if(x==2)
            dir = false;

        while(true)
        {
            cout<< "Enter Number Of Vertices:  ";
            int nVertices;
            cin>>nVertices;
            int maxx = ( (nVertices*nVertices) - nVertices )  /  8;

            ofstream fout("list"+to_string(nVertices)+".txt", ios::out);
            for(int i=nVertices; i<=maxx; i=i*2)
            {
                cout<<i <<endl;
                Graph graph(dir);
                graph.setnVertices(nVertices);

                int nEdges = i;
                int counts = 0;
                while(true)
                {

                    int u = rand()%nVertices;
                    int v = rand()%nVertices;
                    //cout<< u << "  "<<v << endl;
                    if( u!=v &&  !graph.isEdge(u,v) )
                    {
                        graph.addEdge(u,v);
                        counts+=1;
                        if(counts == nEdges)
                            break;
                    }

                }

                fout<< nEdges << "\n";
                for(int i=0; i<10; i++)
                {
                    int source = rand()%nVertices;
                    auto start = steady_clock::now();
                    graph.bfs(source);
                    auto stop = steady_clock::now();
                    auto duration = duration_cast<microseconds>(stop-start);
                    //total = total+duration;
                    fout<< duration.count()<< " ";
                }
                fout<<endl;
                cout<< "done...";

            }
            fout.close();
        }
    }

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove Edge  \n3. isEdge  \n4. get Out Degree  \n5. get In Degree. \n6.Print Adjacent Vertices \n7.Has Common adjacent Vertices \n8. Get Distance . \n9. Print Graph . \n10.  Run BFS . \n11.  Run DFS  \n12. Exit.\n");
        cout<<endl;
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            cout<< "Input 2 vertices:  ";
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            cout<< "Input 2 Vertices:  ";
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
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
            cout<<"Out Degree is: " <<g.getOutDegree(u)<<endl;
        }
        else if(ch==5)
        {
            int u;
            cout<< "Enter Vertice:   ";
            cin>>u;
            cout<< "In Degree is:   "<< g.getInDegree(u)<<endl;
        }
        else if(ch==6)
        {
            int u;
            cout<< "Enter Vertice:  ";
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==7)
        {
            int u,v;
            cout<< "Enter 2 vertices:   ";
            cin>>u>>v;
            cout<< (g.hasCommonAdjacent(u,v)? "YES":"NO")<<endl;
        }
        else if(ch==8)
        {
            int u,v;
            cout<< "Enter 2 vertices:   ";
            cin>>u>>v;
            cout<< "Distance:  "<< g.getDist(u,v)<<endl;
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==12)
        {
            break;
        }
        else if(ch==10)
        {
            cout<< "Enter Source:   ";
            int x;
            cin>>x;
            g.bfs(x);
        }
        else if(ch==11)
        {
            cout<< "Enter Source:   ";
            int x;
            cin>>x;
            g.dfs(x);
        }
    }

}
