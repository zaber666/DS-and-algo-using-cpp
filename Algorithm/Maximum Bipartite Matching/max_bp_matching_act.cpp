#include<bits/stdc++.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;


bool fileO = false;
bool fileI = false;
ofstream fout("output.txt", ios::out);
ifstream in("in10.txt", ios::in);



// ###################################################  QUEUE CLASS ###################################################


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



//################################################## END OF QUEUE CLASS ###########################################





// ############################################################ ARRAY LIST ##################################################



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
	void updateValue(int pos, int val);
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

void ArrayList::updateValue(int pos, int val)
{
    list[pos] = val;
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




// ############################################### END OF ARRAY LIST ################################################






// ###################################################### GRAPH #########################################################


class Graph
{
    int nVertices;
    ArrayList *adjVertex;
    ArrayList *adjWt;
    ArrayList *memoryVertex;
    ArrayList *memoryWt;
    ArrayList *init_list;
    ArrayList *mem_init;
    int* parent;
    int* color;
    int source, destination;
public:
    Graph()
    {

    }
    void setnVertices(int n)
    {
        nVertices = n+2;
        adjVertex = new ArrayList[nVertices];
        adjWt = new ArrayList[nVertices];
        memoryVertex = new ArrayList[nVertices];
        memoryWt = new ArrayList[nVertices];
        parent = new int[nVertices];
        color = new int[nVertices];
        init_list = new ArrayList[n];
        mem_init = new ArrayList[n];

    }
    void set_source_sink(int s, int t)
    {
        source = s;
        destination = t;
    }
    void addEdge_initial(int u, int v)
    {
        if(init_list[u].searchItem(v) == NULL_VALUE)
        {
            init_list[u].insertItem(v);
            mem_init[u].insertItem(v);
        }
        if(init_list[v].searchItem(u) == NULL_VALUE)
        {
            init_list[v].insertItem(u);
            mem_init[v].insertItem(u);
        }
    }
    void addEdge(int u, int v, int w)
    {
        if(isEdge(u, v))
        {
            int pos = adjVertex[u].searchItem(v);
            adjWt[u].updateValue(pos, w);
            memoryVertex[u].insertItem(v);
            memoryWt[u].insertItem(w);
        }
        else
        {
            adjVertex[u].insertItem(v);
            adjVertex[v].insertItem(u);
            adjWt[u].insertItem(w);
            adjWt[v].insertItem(0);
            memoryVertex[u].insertItem(v);
            memoryWt[u].insertItem(w);
        }
    }
    bool isEdge(int u, int v)
    {
        if(adjVertex[u].searchItem(v)!=NULL_VALUE)
            return true;
        return false;
    }
    void removeEdge(int u, int v)
    {
        int pos = adjVertex[u].searchItem(v);
        adjVertex[u].removeItem(v);
        adjWt[u].removeItemAt(pos);

        pos = adjVertex[v].searchItem(u);
        adjVertex[v].removeItem(u);
        adjWt[v].removeItemAt(pos);
    }
    bool is_bp()
    {
        int src = 0;
        for(int x=0; x<nVertices; x++)
            color[x] = -1;
        Queue q;
        color[src] = 0;
        q.enqueue(src);
        while(! q.empty())
        {
            int u = q.dequeue();
            int len = init_list[u].getLength();
            for(int i=0; i<len; i++)
            {
                int elem = init_list[u].getItem(i);
                init_list[elem].removeItem(u);
                if(color[elem] == color[u])
                {
                    return false;
                }
                if(color[elem] == -1)
                {
                    color[elem] = 1 - color[u];
                    q.enqueue(elem);
                }

            }

        }
        return true;
    }
    void construct_flow_network()
    {
        for(int i=0; i<nVertices-2; i++)
        {
            if(color[i] == 0)
            {
                addEdge(source, i, 1);
                int len = mem_init[i].getLength();
                for(int j=0; j<len; j++)
                {
                    int elem = mem_init[i].getItem(j);
                    addEdge(i, elem, 1);
                }
            }
            else
                addEdge(i, destination, 1);
        }
    }
    bool bfs()
    {
        bool visited[nVertices] = {false};
        Queue q;
        for(int i=0; i<nVertices; i++)
            parent[i] = -1;
        visited[source] = true;
        q.enqueue(source);
        while(!q.empty())
        {
            int u = q.dequeue();
            int len = adjVertex[u].getLength();
            for(int i=0; i<len; i++)
            {
                int elem = adjVertex[u].getItem(i);
                if( (!visited[elem]) && (adjWt[u].getItem(i)>0))
                {
                    q.enqueue(elem);
                    visited[elem] = true;
                    parent[elem] = u;
                }
            }

        }

        return (visited[destination]==true);
    }
    int ford_fulkerson()
    {
        int max_flow = 0;
        int chl, par;
        while(bfs())
        {

            int path_flow = INFINITY;
            for(chl=destination; chl!=source; chl=parent[chl])
            {
                par = parent[chl];
                int pos = adjVertex[par].searchItem(chl);
                path_flow =  min(path_flow, adjWt[par].getItem(pos));
            }

            for (chl=destination; chl!=source; chl=parent[chl])
            {
                par = parent[chl];
                int pos = adjVertex[par].searchItem(chl);
                adjWt[par].updateValue(pos, adjWt[par].getItem(pos)-path_flow);
                pos = adjVertex[chl].searchItem(par);
                adjWt[chl].updateValue(pos, adjWt[chl].getItem(pos)+path_flow);
            }
            max_flow += path_flow;
        }
        return max_flow;
    }
    void printInitList()
    {
        for(int i=0; i<nVertices-2; i++)
        {
            init_list[i].printList();
            cout<<endl;
        }
    }

    void printAllLists()
    {
        cout<< "Vertex List" <<endl;
        for(int i=0; i<nVertices; i++)
        {
            adjVertex[i].printList();
            cout<<endl;
        }
        cout<<endl<<endl;

        for(int i=0; i<nVertices; i++)
        {
            adjWt[i].printList();
            cout<<endl;
        }
    }
    void printEdges()
    {
        for(int u=0; u<nVertices; u++)
        {
            int len = memoryVertex[u].getLength();
            for(int j=0; j<len; j++)
            {
                int v = memoryVertex[u].getItem(j);
                int capacity = memoryWt[u].getItem(j);
                int pos = adjVertex[u].searchItem(v);
                int flow = capacity - adjWt[u].getItem(pos);
                if((flow == 1) && (u != nVertices-2) && (v != nVertices-1))
                    if(!fileO)
                        cout<< u << "    " << v << endl;
                    else
                        fout<< u << "    " << v << endl;
            }
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
    Graph g;
    int V,E;
    if(!fileI)
    {
        cin>>V>>E;
        g.setnVertices(V);
        for(int i=0; i<E; i++)
        {
            int u,v;
            cin>> u>>v;
            g.addEdge_initial(u,v);
        }

    }
    else
    {
        int numLine = 0;
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
                g.setnVertices(V);
                numLine++;
                //cout<< numLine << "  " << V << "   " << E <<endl;
            }
            else if(numLine <= E)
            {
                int u = stoi(lines[0]);
                int v = stoi(lines[1]);
                g.addEdge_initial(u, v);
                numLine++;
                //cout<< numLine << "  " << u << "   " << v <<endl;
            }

        }
    }

    g.set_source_sink(V, V+1);
    if( g.is_bp() == false )
    {
        if(!fileO)
            cout << "The graph is not bipartite."<<endl;
        else
            fout << "The graph is not bipartite."<<endl;
    }
    else
    {
        if(!fileO)
        {
            g.construct_flow_network();
            cout << g.ford_fulkerson()<<endl;
        }
        else
            fout << g.ford_fulkerson()<<endl;

        g.printEdges();
    }

}




