#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits.h>
using namespace std;

void reset_graph(int[][5], int);
void print_graph(int[][5], string[], int);
void add_edge(int[][5], string[], int);
void delete_edge(int[][5], string[], int);
void dashboard(int[][5], string[], int);
void generateRandomEdge(int[][5], string[], int);
void generateRandomVertices(int&, int&);
void checkValidity(bool&, int[][5], string[], int, int, int);
void add_distance(int[][5], string[], int, int, int);

//Function 1
bool checkConnectivity(int[][5], int);
void graphTranspose(int[][5], int);
void dfs(int, int[][5], bool[]);
void function1(int[][5], string[], int);

//Function 2
bool hasCycle(int[][5], string[], int);
bool cycleDetectionDFS(int[][5], string[], int, int v, bool[], bool[]);
void function2(int[][5], string[], int);

//Function 3
void function3(int[][5], string[], int);
int minDistance(int[], bool[]);
void printShortestPath(int[], int[], int, int, string[]);

//Function 4
void function4(int[][5], string[], int);
void undirected(int[][5], int);
bool exists_MST(int[][5], int);
int minKey(int[], bool);
void printMST(int[], int[][5]);
void primFindMST(int[][5]);

int main() {
	/*
		0 - BJ - Beijing, China
		1 - TP - Taipei, Taiwan
		2 - BK - Bangkok, Thailand
		3 - KL - Kuala Lumpur, Malaysia
		4 - JK - Jakarta, Indonesia
	*/

	//Adjacency Matrix **2D Array
	const int SIZE = 5;
	int graph[SIZE][SIZE] = {};

	//Array **Country Name
	string city_name[SIZE] = { "BJ", "TP", "BK", "KL", "JK" };

	//Reset Graph
	reset_graph(graph, SIZE);

	//Dashboard
	dashboard(graph, city_name, SIZE);

	//Print Graph //Checking
	//print_graph(graph, city_name, SIZE);

	//Add Edge
	//add_edge(graph, city_name, SIZE);

	//Generate Random Edges
	//generateRandomEdge(graph, city_name, SIZE);

	return 0;
}

void dashboard(int graph[][5], string city_name[], int SIZE) {

	print_graph(graph, city_name, SIZE);

	int option;
	cout << endl << endl;
	cout << "\t\t[Dashboard]\n" << endl;
	cout << "\t[1] RESET GRAPH" << endl;
	cout << "\t[2] ADD EDGE" << endl;
	cout << "\t[3] DELETE EDGE " << endl;
	cout << "\t[4] STRONG CONNECTIVITY " << endl;
	cout << "\t[5] CYCLE DETECTION " << endl;
	cout << "\t[6] SHORTEST PATH " << endl;
	cout << "\t[7] MINIMUM SPANNING TREE " << endl;
	cout << "\t[8] EXIT " << endl;
	cout << "\n\tENTER: ";
	cin >> option;

	if (option == 1) {
		reset_graph(graph, SIZE);
		dashboard(graph, city_name, SIZE);
	}
	else if (option == 2) {
		add_edge(graph, city_name, SIZE);
	}
	else if (option == 3) {
		delete_edge(graph, city_name, SIZE);
	}
	else if (option == 4) {
		function1(graph, city_name, SIZE);
	}
	else if (option == 5) {
		function2(graph, city_name, SIZE);
	}
	else if (option == 6) {
		function3(graph, city_name, SIZE);
	}
	else if (option == 7) {
		function4(graph, city_name, SIZE);
	}
	else {
		system("CLS");
		cout << "\n\tThank You! The program ends here!\n";
	}
}

void reset_graph(int graph[][5], int SIZE) {

	/*
		0 - Beijing, China
		1 - Taipei, Taiwan
		2 - Bangkok, Thailand
		3 - Kuala Lumpur, Malaysia
		4 - Jakarta, Indonesia
	*/

	// Set all to 0 **No Edge
	for (int i = 0; i < SIZE; i++) {

		for (int j = 0; j < SIZE; j++)
		{
			graph[i][j] = 0;
		}
	}

	// Set edge
	graph[0][1] = 1725;
	graph[0][2] = 3298;
	graph[1][4] = 3812;
	graph[3][2] = 1186;
	graph[3][4] = 1182;
}

void print_graph(int graph[][5], string city_name[], int SIZE) {


	// Label
	std::cout << "\n\t";
	for (int i = 0; i < SIZE; i++) {
		cout << "[" << city_name[i] << "]" << "\t";
	}
	cout << endl;


	// Print Graph **2D array
	for (int i = 0; i < SIZE; i++) {

		cout << "[" << city_name[i] << "]" << "\t"; //Label

		for (int j = 0; j < SIZE; j++)
		{
			cout << graph[i][j] << "\t";
		}

		cout << endl;
	}

	// system("CLS");
}

void add_edge(int graph[][5], string city_name[], int SIZE) {

	system("CLS");
	print_graph(graph, city_name, SIZE);

	string origin, destination;
	int index_origin = 0;
	int index_des = 0;
	int option;

	cout << endl;
	cout << "[You may ADD edge from one city to another city]" << endl;
	cout << "\n\t[EXAMPLE]" << endl;
	cout << "\tOrigin:" << "\t\tBJ" << endl;
	cout << "\tDestination:" << "\tTP" << endl << endl;
	cout << "\t[YOUR CHOICE] " << endl;
	cout << "\tOrigin: ";
	cin >> origin;
	cout << "\tDestination: ";
	cin >> destination;

	//Convert name to get index
	//Because we are using 2D array
	for (int i = 0; i < SIZE; i++) {
		if (origin == city_name[i])
		{
			index_origin = i;
		}

		if (destination == city_name[i])
		{
			index_des = i;
		}
	}

	// Check validity and availability
	if (index_origin == index_des) {
		cout << endl;
		cout << "Error, Origin != Destination" << endl;
		cout << "Please select different origin and destination" << endl;

		cout << "\n[1] ADD EDGE AGAIN" << endl;
		cout << "[2] DASHBOARD" << endl;
		cout << "\nENTER: ";
		cin >> option;


		if (option == 1) {
			add_edge(graph, city_name, SIZE);
		}
		else if (option == 2) {
			dashboard(graph, city_name, SIZE);
		}
	}


	if (graph[index_origin][index_des] != 0) {
		cout << endl;
		cout << "Error, the edge already exits between "
			<< origin << "->" << destination << " or "
			<< destination << "->" << origin << endl;
		cout << "Please select different origin and destination" << endl;

		cout << "\n[1] ADD EDGE AGAIN" << endl;
		cout << "[2] DASHBOARD" << endl;
		cout << "\nENTER: ";
		cin >> option;


		if (option == 1) {
			add_edge(graph, city_name, SIZE);
		}
		else if (option == 2) {
			dashboard(graph, city_name, SIZE);
		}
	}

	add_distance(graph, city_name, SIZE, index_origin, index_des);
	dashboard(graph, city_name, SIZE);
}

void delete_edge(int graph[][5], string city_name[], int SIZE) {

	system("CLS");
	print_graph(graph, city_name, SIZE);

	string origin, destination;
	int index_origin, index_des;
	int option;

	cout << endl;
	cout << "[You may DELETE edge from one city to another city]" << endl;
	cout << "\n\t[EXAMPLE]" << endl;
	cout << "\tOrigin:" << "\t\tBJ" << endl;
	cout << "\tDestination:" << "\tTP" << endl << endl;
	cout << "\t[YOUR CHOICE] " << endl;
	cout << "\tOrigin: ";
	cin >> origin;
	cout << "\tDestination: ";
	cin >> destination;

	//Convert name to get index
	//Because we are using 2D array
	for (int i = 0; i < SIZE; i++) {
		if (origin == city_name[i])
		{
			index_origin = i;
		}

		if (destination == city_name[i])
		{
			index_des = i;
		}
	}

	// Check validity and availability
	if (index_origin == index_des) {
		cout << endl;
		cout << "Error, Origin != Destination" << endl;
		cout << "Please select different origin and destination" << endl;

		cout << "\n[1] DELETE EDGE AGAIN" << endl;
		cout << "[2] DASHBOARD" << endl;
		cout << "\nENTER: ";
		cin >> option;


		if (option == 1) {
			delete_edge(graph, city_name, SIZE);
		}
		else if (option == 2) {
			dashboard(graph, city_name, SIZE);
		}
	}

	if (graph[index_origin][index_des] == 0) {
		cout << endl;
		cout << "Error, the edge already doesn't exits" << endl;
		cout << "Please select different origin and destination" << endl;

		cout << "\n[1] DELETE EDGE AGAIN" << endl;
		cout << "[2] DASHBOARD" << endl;
		cout << "\nENTER: ";
		cin >> option;


		if (option == 1) {
			delete_edge(graph, city_name, SIZE);
		}
		else if (option == 2) {
			dashboard(graph, city_name, SIZE);
		}
	}

	graph[index_origin][index_des] = 0;

	cout << "\n\t[EDGE SUCCESSFULLY DELETED]\n\n";
	dashboard(graph, city_name, SIZE);
}

void generateRandomVertices(int& index_origin, int& index_des) {

	srand(time(0));

	index_origin = 0;
	index_des = 0;


	while (index_origin == index_des) {

		index_origin = rand() % 10;
		index_des = rand() % 10;

		if (index_origin > 4) {
			if (index_origin % 2 == 0) {
				index_origin = index_origin / 2;
			}
			else {
				index_origin = index_origin - 5;
			}
		}

		if (index_des > 4) {
			if (index_des % 2 == 0) {
				index_des = index_des / 2;
			}
			else {
				index_des = index_des - 5;
			}
		}
	}
}

void checkValidity(bool& edgeValid, int graph[][5], string city_name[], int SIZE, int index_origin, int index_des) {

	if (graph[index_origin][index_des] != 0) {

		edgeValid = false;
	}
	else {
		edgeValid = true;
	}
}

void generateRandomEdge(int graph[][5], string city_name[], int SIZE) {

	bool edgeValid = false;

	int index_origin;
	int index_des;

	generateRandomVertices(index_origin, index_des);

	checkValidity(edgeValid, graph, city_name, SIZE, index_origin, index_des);


	while (edgeValid == false) {

		generateRandomVertices(index_origin, index_des);
		checkValidity(edgeValid, graph, city_name, SIZE, index_origin, index_des);
	}

	add_distance(graph, city_name, SIZE, index_origin, index_des);
	print_graph(graph, city_name, SIZE);
	cout << endl;
	system("PAUSE");
	system("CLS");
}

void add_distance(int graph[][5], string city_name[], int SIZE, int index_origin, int index_des) {

	// TP -> BJ or BJ -> TP, 1725 km (0,1)
	if ((index_origin == 0 && index_des == 1) || (index_origin == 1 && index_des == 0)) {
		graph[index_origin][index_des] = 1725;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// BK -> BJ or BJ -> BK, 3298 km (0,2)
	if ((index_origin == 0 && index_des == 2) || (index_origin == 2 && index_des == 0)) {
		graph[index_origin][index_des] = 3298;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// BJ -> KL or KL -> BJ, 4348 km
	if ((index_origin == 0 && index_des == 3) || (index_origin == 3 && index_des == 0)) {
		graph[index_origin][index_des] = 4348;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// BJ -> JK or JK -> BJ, 5220 km
	if ((index_origin == 0 && index_des == 4) || (index_origin == 4 && index_des == 0)) {
		graph[index_origin][index_des] = 5220;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// TP -> BK or BK -> TP, 2525 km
	if ((index_origin == 1 && index_des == 2) || (index_origin == 2 && index_des == 1)) {
		graph[index_origin][index_des] = 2525;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// TP -> KL or KL -> TP, 3221 km
	if ((index_origin == 1 && index_des == 3) || (index_origin == 3 && index_des == 1)) {
		graph[index_origin][index_des] = 3221;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// TP -> JK or JK -> TP, 3812 km (1,4)
	if ((index_origin == 1 && index_des == 4) || (index_origin == 4 && index_des == 1)) {
		graph[index_origin][index_des] = 3812;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// KL -> BK or BK -> KL, 1186 km (2,3)
	if ((index_origin == 2 && index_des == 3) || (index_origin == 3 && index_des == 2)) {
		graph[index_origin][index_des] = 1186;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// BK -> JK or JK -> BK, 2323 km
	if ((index_origin == 2 && index_des == 4) || (index_origin == 4 && index_des == 2)) {
		graph[index_origin][index_des] = 2323;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}

	// KL -> JK or JK -> KL, 1182 km (3,4)
	if ((index_origin == 3 && index_des == 4) || (index_origin == 4 && index_des == 3)) {
		graph[index_origin][index_des] = 1182;
		cout << "\n\t[EDGE SUCCESSFULLY ADDED]\n\n";
	}
}

/*
=============================================================================================================================================================
																FUNCTION 1
=============================================================================================================================================================
*/

void function1(int graph[][5], string city_name[], int SIZE) {

	system("CLS");

	//Variable to check whether the graph is connected
	bool connectivity = false;
	do {

		// Perform the first round of traversal 
		connectivity = checkConnectivity(graph, SIZE);

		// Check if the graph is all connected
		if (connectivity == true) {

			cout << endl;

			// Reverse the edges of the graph
			graphTranspose(graph, SIZE);

			// Using the same starting vertex, perform another rounf of traversal
			connectivity = checkConnectivity(graph, SIZE);

			// Check if the graph is all connected
			if (connectivity == true) {

				cout << "\n\t[THE GRAPH IS STRONGLY CONNECTED]\n\n";

				// Reverse the edges to the original graph
				graphTranspose(graph, SIZE);

				// Print result
				cout << "\n Result:\n";
				print_graph(graph, city_name, SIZE);
				cout << endl;
				system("pause");
				system("CLS");

				// Call dashboard function
				dashboard(graph, city_name, SIZE);
			}
			else {
				cout << "\n\t[THE GRAPH IS NOT STRONGLY CONNECTED]\n\n";

				// Reverse the edges to the original graph				
				graphTranspose(graph, SIZE);

				// Generate random edges
				cout << "\n\t[ADDING EDGES]\n";
				generateRandomEdge(graph, city_name, SIZE);
			}
		}
		else {
			cout << "\n\t[THE GRAPH IS NOT STRONGLY CONNECTED]\n";

			// Generate random edges			
			cout << "\n\t\t[ADDING EDGES]\n";
			generateRandomEdge(graph, city_name, SIZE);
		}
	} while (connectivity == false); // Continue to loop until the graph is proved as strongly connected

}

bool checkConnectivity(int graph[][5], int SIZE) {

	// Mark all the vertices as not visited
	bool vertex[5];
	for (int i = 0; i < 5; i++) {
		vertex[i] = false;
	}

	//Do Traversal
	dfs(0, graph, vertex);

	//Check whether it is connected
	bool stronglyConnected = true;

	for (int i = 0; i < SIZE; i++) {
		if (vertex[i] == false) {
			stronglyConnected = false;
		}
	}

	// Return the result
	return stronglyConnected;

}

void dfs(int v, int graph[][5], bool vertex[5]) {

	// Mark the current vertex as visited
	vertex[v] = true;

	// For every node of the graph
	for (int i = 0; i < 5; i++) {

		// If some vertex is adjacent and not been visited, then visit
		if (graph[v][i] > 0 && (!vertex[i])) {
			dfs(i, graph, vertex);
		}
	}
}

void graphTranspose(int graph[][5], int size) {

	// Create temperory 2D array
	int tempGraph[5][5] = {};

	// Transpose the Matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tempGraph[j][i] = graph[i][j];
		}
	}

	// Assign the value from temporary matix to original matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			graph[i][j] = tempGraph[i][j];
		}
	}

	cout << "\t\t[REVERSE EDGES]\n";
}

/*
=============================================================================================================================================================
																FUNCTION 2
=============================================================================================================================================================
*/

void function2(int graph[][5], string city_name[], int SIZE) {

	system("CLS");

	while (!hasCycle(graph, city_name, SIZE)) {
		system("CLS");
		cout << endl << "\t[THE GRAPH DOES NOT CONTAIN CYCLE]";
		cout << endl << "\n\t[GENERATING AN EDGE]\n";
		generateRandomEdge(graph, city_name, SIZE);
	}

	if (hasCycle(graph, city_name, SIZE))
	{
		cout << "\n\t[CYCLE IS DETECTED!]\n\n";
		cout << "Result" << endl;
		print_graph(graph, city_name, SIZE);
	}
	system("PAUSE");
	system("CLS");
	dashboard(graph, city_name, SIZE);

}

bool hasCycle(int graph[][5], string city_name[], int SIZE) {
	bool* visited = new bool[SIZE];
	bool* recursionStack = new bool[SIZE];

	// Mark all the vertices as not visited 
	// and not part of recursion stack at the begining 
	for (int i = 0; i < SIZE; i++)
	{
		visited[i] = false;
		recursionStack[i] = false;
	}

	// Call the recursive helper funcion
	// to detect cycle in different DFS trees.
	for (int i = 0; i < SIZE; i++)
	{
		if (cycleDetectionDFS(graph, city_name, SIZE, i, visited, recursionStack))
		{
			return true;
		}
	}
	return false;
}

bool cycleDetectionDFS(int graph[][5], string city_name[], int SIZE, int v, bool visited[], bool recursionStack[]) {
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
		recursionStack[v] = true;

		for (int i = 0; i < SIZE; i++)
		{
			// if there are nodes adjacent to the current node
			if (graph[v][i] > 0)
			{
				// If the node has not been visited, we make a recursive call
				if (!(visited[i]) && cycleDetectionDFS(graph, city_name, SIZE, i, visited, recursionStack)) {
					return true;
				}

				// Check whether the visited node is a part of recursion stack 
				else if (recursionStack[i]) {
					return true;	// If yes, return true and cycle found
				}
			}
		}

	}
	recursionStack[v] = false;	// remove the vertex from the recursion stack
	return false;
}


/*
=============================================================================================================================================================
																FUNCTION 3
=============================================================================================================================================================
*/

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void function3(int graph[5][5], string city_name[], int SIZE) {
	system("cls");
	print_graph(graph, city_name, SIZE);

	string origin, destination;
	int index_origin = 0;
	int index_des = 0;

	cout << endl;
	cout << "[You may find the SHORTEST PATH from one city to another city]" << endl;
	cout << "\n\t[EXAMPLE]" << endl;
	cout << "\tOrigin:" << "\t\tBJ" << endl;
	cout << "\tDestination:" << "\tTP" << endl << endl;
	cout << "\t[YOUR CHOICE] " << endl;
	cout << "\tOrigin: ";
	cin >> origin;
	cout << "\tDestination: ";
	cin >> destination;

	for (int i = 0; i < SIZE; i++) {
		if (origin == city_name[i])
		{
			index_origin = i;
		}

		if (destination == city_name[i])
		{
			index_des = i;
		}
	}

	int dist[5]; // The output array.  dist[i] will hold the shortest
	// distance from src to i
	int path[5];

	bool visited[5]; // visited[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	do {
		// Initialize all distances as INFINITE and visited[] as false
		for (int i = 0; i < SIZE; i++)
		{
			dist[i] = INT_MAX, visited[i] = false;
			path[i] = -1;
		}

		// Distance of source vertex from itself is always 0
		dist[index_origin] = 0;
		path[index_origin] = -1;

		print_graph(graph, city_name, SIZE);

		// Find shortest path for all vertices
		for (int count = 0; count < SIZE - 1; count++) {

			// Pick the minimum distance vertex from the set of vertices not
			// yet processed. u is always equal to src in the first iteration.
			int u = minDistance(dist, visited);

			// Mark the picked vertex as processed
			visited[u] = true;

			// Update dist value of the adjacent vertices of the picked vertex.
			for (int v = 0; v < 5; v++)
			{
				// Update dist[v] only if is not in visited, there is an edge from
				// u to v, and total weight of path from src to  v through u is
				// smaller than current value of dist[v]
				if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
					&& dist[u] + graph[u][v] < dist[v])
				{
					dist[v] = dist[u] + graph[u][v];
					path[v] = u;
				}
			}
		}

		if (dist[index_des] == INT_MAX)
		{
			cout << "\n\t[THERE IS NO PATH TO DESTINATION]\n\n";

			// Generate random edges			
			cout << "\n\t\t[ADDING EDGES]\n";
			generateRandomEdge(graph, city_name, SIZE);
		}
	} while (dist[index_des] == INT_MAX);

	// print the constructed distance array
	printShortestPath(path, dist, index_origin, index_des, city_name);

	system("PAUSE");
	system("CLS");
	dashboard(graph, city_name, SIZE);
}

void printShortestPath(int path[], int distance[], int origin, int destination, string city_name[]) {
	string ori, dest;
	ori = city_name[origin];
	dest = city_name[destination];
	cout << "\nShortest Path from " << ori << " to " << dest << " is ";

	int find = destination;

	int shortestPath[5], x = 0;
	while (find != -1)
	{
		shortestPath[x] = find;
		find = path[find];
		x = x + 1;
	}

	for (int y = x - 1; y >= 0; y--)
	{
		cout << city_name[shortestPath[y]];
		if (y != 0)
		{
			cout << " -> ";
		}
	}
	cout << "\nTotal distance from origin: " << distance[destination] << "km" << endl;
}

int minDistance(int dist[], bool visited[]) {

	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < 5; v++)
		if (visited[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

/*
=============================================================================================================================================================
																FUNCTION 4
=============================================================================================================================================================
*/

void function4(int graph[][5], string city_name[], int SIZE) {

	int graphNEW[5][5] = {}; // New temporary graph to store few sellected edges
	bool checkMST = true; // Availability of MST
	string origin, destination;
	int index_origin = 0;
	int index_des = 0;

	print_graph(graph, city_name, SIZE);

	cout << endl << endl;
	cout << "--------- [MINIMUM SPANNING TREE]--------- \n" << endl;
	cout << "\n\t[You are allow to choose 4 edges.]";
	cout << "\n\t[The program will generate MST.]";

	// ASK user to sellect 3 edges
	for (int i = 0; i < 3; i++) {

		bool checkValid = false; // Availability of edge
		cout << endl;

		// While the sellected edge by user is not available
		while (checkValid == false) 
		{
			//ASK user to sellect edge again
			cout << "\n\t\t-- [" << i + 1 << "] edge --" << endl;
			cout << "\t\tOrigin: ";
		std:cin >> origin;
			cout << "\t\tDestination: ";
			cin >> destination;

			//Temporary set the checkValid to true
			checkValid = true;

			//Convert name to get index
			//Because we are using 2D array
			for (int i = 0; i < 5; i++) {
				if (origin == city_name[i])
				{
					index_origin = i;
				}

				if (destination == city_name[i])
				{
					index_des = i;
				}
			}

			// IF origin same as destination
			if (index_origin == index_des) {
				cout << endl;
				cout << "Error, Origin != Destination" << endl;
				cout << "Please select different origin and destination" << endl;
				checkValid = false; // SET checkValid to FALSE to run while loop again
			}

			// IF sellected edge doesn't exists
			if (graph[index_origin][index_des] == 0) {
				cout << endl;
				cout << "Error, the edge doesn't exits" << endl;
				cout << "Please select different origin and destination" << endl;
				checkValid = false; // SET checkValid to FALSE to run while loop again
			}

			// IF sellected is exists, can be select
			if (checkValid == true) {

				// Copy edge from OLD graph to NEW temporary graph
				graphNEW[index_origin][index_des] = graph[index_origin][index_des];
			}
		}
	}

	// Set Original Graph to 0
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			graph[i][j] = 0;
		}
	}

	undirected(graphNEW, SIZE);

	// Copy graphNEW to graph
	// We have to use OLD graph to do further action
	// This is because the OLD graph is being passed in whole program
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			graph[i][j] = graphNEW[i][j];
		}
	}

	// If MST doesn't exits, add random edges
	while (exists_MST(graph, SIZE) == false) {
		cout << endl << "--------- [THE GRAPH DOES NOT CONTAIN MST] ---------";
		cout << endl << "\n\t[GENERATING AN EDGE]\n";
		generateRandomEdge(graph, city_name, SIZE);

		cout << endl << "--------- [COPY THE EDGE IN OPPOSITE DIRECTION] ---------";
		cout << endl << "\n\t\t[MAKE IT UNDIRECTED]\n";

		undirected(graph, SIZE); // Make the graph become undirected *2 Direction

		print_graph(graph, city_name, SIZE);
		cout << endl;
		system("pause");
		system("CLS");
	}

	// IF the graph contain MST, print MST
	if (exists_MST(graph, SIZE) == true) {
		cout << endl << "--------- [THE GRAPH CONTAIN MST] ---------";
		cout << endl << "\n\t\t[RESULT]\n\n";
	}

	primFindMST(graph);
	dashboard(graph, city_name, SIZE);
}

// CHECK whether the graph contains MST
// IF every edges is connected, able to generate MST
// ELSE unable to generate MST
bool exists_MST(int graph[][5], int SIZE) {

	bool check_MST = true;

	for (int i = 0; i < SIZE; i++) {
		if (graph[i][0] == 0 && graph[i][1] == 0 && graph[i][2] == 0 && graph[i][3] == 0 && graph[i][4] == 0) {
			check_MST = false;
		}
	}

	return check_MST;
}


// Make the graph become undirected *2 Direction
// This is because the randomly generated edge
// Only in one direction
void undirected(int graph[][5], int SIZE) {

	for (int i = 0; i < SIZE; i++) {

		for (int j = 0; j < SIZE; j++) {

			if (graph[i][j] != 0) {

				graph[j][i] = graph[i][j];
			}
		}
	}
}


int minKey(int key[], bool mstSet[]) {
	// Initialize min value
	int min = INT_MAX;
	int min_index;

	for (int v = 0; v < 5; v++)
		if (mstSet[v] == false && key[v] < min)
		{
			min = key[v];
			min_index = v;
		}

	return min_index;
}

// PRINT constructed MST stored in parent[]
void printMST(int parent[], int graph[5][5]) {
	cout << "\t    [Edge] \t[DISTANCE]\n";
	for (int i = 1; i < 5; i++)
		cout << "\t    " << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";

	cout << "--------------------------------------------";
}

// Function to construct MST
// Prim’s algorithm
void primFindMST(int graph[5][5]) {
	
	int parent[5]; // Array to store constructed MST

	int key[5]; // Key values used to pick minimum weight edge in cut

	bool mstSet[5]; // To represent set of vertices included in MST

	// Initialize all keys as INFINITE
	for (int i = 0; i < 5; i++) {
		key[i] = INT_MAX;
		mstSet[i] = false;
	}

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first vertex.
	key[0] = 0; // No distance for the source vertex, key = 0
	parent[0] = -1; // First node is always root of MST, doesn't have any parent

	// The MST will have 5 vertices
	for (int count = 0; count < 5 - 1; count++)
	{
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < 5; v++)

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
				parent[v] = u;
				key[v] = graph[u][v];
			}
	}

	// print the constructed MST
	printMST(parent, graph);
}
