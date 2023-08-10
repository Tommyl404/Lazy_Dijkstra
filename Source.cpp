#include <iostream>

using namespace std;

//first function - min_Dist
//this function will find the min distance.
//input - the distance array of type int and a bool array that means if we visited the vertex or not.
//output - index that represent the vertex.

int min_Dist(int dist[], bool Visited_Or_Not_Set[])
{
	int index;
	int the_min_dist = INT_MAX; //this is like setting the min_dist to be infinity.

	for (int i = 0; i < 7; i++)
	{
		if (Visited_Or_Not_Set[i] == false && dist[i] <= the_min_dist) //if we have not visited the vertex and it's smaller or equal to the_min_dist
		{
			the_min_dist = dist[i];
			index = i;
		}
	}
	return index;
}


//the main algo. it's named like this because of the time complexity that i made here!
//in the normal dijkstra's algo we can have a time complexity of O(E*Log(V)) with binary heap and and represent the graph with adjacency list.
//since i represent the graph with a matrix and didn't use an adjacency list, the time complexity is O(V^2).
//input - the graph (a matrix) of type int and a source to start with.
//output - NONE. this is a void function.
void Lazy_dijkstra(int graph[7][7], int source)
{
	if (source > 6 || source < 0)
	{
		cout << "error in source input, ending..." << endl;
	}

	else {
		//first we need to make 2 arrays:
		int distance[7]; // here we will store the min dist for each vertex
		bool vis_or_not[7]; //bool array that will mark if a vertex was visited or not (1 = visited, 0 = not)

		//startup - make the distance array to be all INT_MAX values
		//make distance[source] = 0 (since it took 0 steps to be in the start)
		//make vis_or_not mark mark all vertexs as false (0)

		for (int i = 0; i < 7; i++)
		{
			distance[i] = INT_MAX;
			vis_or_not[i] = false;
		}

		distance[source] = 0;

		//the heart of the algo.
		//since we are using a metrix i will use a nested loop for this algo.
		//outer loop:
		for (int i = 0; i < 7; i++)
		{
			int index_vertex_used_this_iteration = min_Dist(distance, vis_or_not); //this is how we choose the vertex to use in the iteration
			vis_or_not[index_vertex_used_this_iteration] = true; //the algo is working on this vertex so we say we visited him.
			for (int j = 0; j < 7; j++)
			{
				//now we need to update the distance of the neighbouring vertex
				//so the flags that needs to "turn on" so we will update the distance array are:
				//A. we have NOT visited this vertex yet
				//B. you have an edge that connect the 2 vertex's in the grapth itself
				//C. the distance[index_vertex_used_this_iteration] is not INT_MAX (This is because INT_MAX is the maximum value of INT. If we try to *pass over it* we actually break the INT type)
				//D. distance[index_vertex_used_this_iteration]+graph[index_vertex_used_this_iteration][j]<distance[j] is true.

				if (!vis_or_not[i] && //A
					(graph[index_vertex_used_this_iteration][j] != 0) && //B
					(distance[index_vertex_used_this_iteration] != INT_MAX) && //C
					(distance[index_vertex_used_this_iteration] + graph[index_vertex_used_this_iteration][j] < distance[j]) //D
					)
				{
					distance[j] = distance[index_vertex_used_this_iteration] + graph[index_vertex_used_this_iteration][j];
				}
			}


		}
		//now all we have to do is print!
		cout << "Vertex\t\tDistance from source vertex" << endl;
		for (int k = 0; k < 7; k++)
		{
			char ascii_cheat = 65 + k; //65 for ascii is A. so A,B,C,D,E,F.....
			cout << ascii_cheat << "\t\t\t";
			if (distance[k] == INT_MAX)
			{
				cout << "infinity" << endl;
			}
			else
			{
				cout << distance[k] << endl;
			}
		}
	}
}



void main()
{
	int graph[7][7] = {
	{ 0, 9, 0, 2, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 6, 0 },
	{ 3, 0, 0, 35, 3, 0, 1 },
	{ 0, 2, 0, 0, 2, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 9, 0, 0, 2 },
	{ 0, 0, 44, 57, 0, 0, 0 } 
	};
	Lazy_dijkstra(graph, 2);
}