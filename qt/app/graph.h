#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <QVector>
#include "dbmanager.h"

/***********************************************************************
 * Edge struct
 *   This struct represents a Edge object. It manages 4 attributes:
 *   u, v, discoverEdge, weight.
 ***********************************************************************/
template<typename T>
struct Edge {
	T u;    // start
	T v;    // end
	bool discoverEdge;
	int weight;

	/***************************************************************
	 * Edge();
	 *   Constructor; Initialize class attributes
	 *   Parameters: none
	 *   Return: none
	 ***************************************************************/
	Edge()
			: u(T{}), v(T{}), discoverEdge(false), weight(0) {}

	/***************************************************************
	 * Edge(T u, T v, int weight)
	 *   Constructor; Initialize class attributes
	 *   Parameters: none
	 *   Return: none
	 ***************************************************************/
	Edge(T u, T v, int weight)
			: u{u}, v{v}, discoverEdge{false}, weight{weight} {}

	bool operator==(const Edge<T> &rhs) const {
		return u == rhs.v && v == rhs.u;
	}

	bool operator!=(const Edge<T> &rhs) const { return !operator==(rhs); }
};

/***********************************************************************
* Vertex struct
*   This struct represents a Vertex object. It manages 3 attributes:
*   vert, visited, edgeList.
***********************************************************************/
template<typename T>
struct Vertex {

	T vert;
	bool visited;
	std::vector<Edge<T>> edgeList;

	/***************************************************************
	 * Vertex();
	 *   Constructor; Initialize class attributes
	 *   Parameters: none
	 *   Return: none
	 ***************************************************************/
	Vertex() : vert(T{}), visited(false) {}

	/***************************************************************
	 * Vertex(T vert, bool visited)
	 *   Constructor; Initialize class attributes
	 *   Parameters: none
	 *   Return: none
	 ***************************************************************/
	Vertex(T vert, bool visited) : vert{vert}, visited{visited} {}

	/*******************************************************************
	 * int NumOfEdges() const
	 *
	 *   Accessor; number of edges
	 *------------------------------------------------------------------
	 *   Parameter: (none)
	 *------------------------------------------------------------------
	 *   Return: (int) - number of edges
	 *******************************************************************/
	int NumOfEdges() const { return edgeList.size(); }
};

/***********************************************************************
* Graph class
*   This struct represents a Graph object. It manages 2 attributes:
*   distance, graph.
***********************************************************************/
template<typename T>
class Graph {
public:
	/***************************************************************
	 * Graph();
	 *   Constructor; Initialize class attributes
	 *   Parameters: none
	 *   Return: none
	 ***************************************************************/
	Graph();

	/*********************************************************************
	 * ~Graph();
	 *   Destructor; deallocates any allocated memory
	 *   Parameters: none
	 *   Return: none
	 *********************************************************************/
	~Graph() = default;

	void generateGraph();
	/*******************************************************************
	 * bool empty() const
	 *
	 *   Accessor; checks if list is empty
	 *------------------------------------------------------------------
	 *   Parameter: (none)
	 *------------------------------------------------------------------
	 *   Return: (bool) - isEmpty
	 *******************************************************************/
	bool empty() const;

	/*******************************************************************
	 * int size() const
	 *
	 *   Accessor; number of nodes
	 *------------------------------------------------------------------
	 *   Parameter: (none)
	 *------------------------------------------------------------------
	 *   Return: (int) - number of nodes in skip list
	 *******************************************************************/
	int size() const;

	/*******************************************************************
	 * void insertVertex(T vert)
	 *
	 *   Mutator; adds vert to graph
	 *------------------------------------------------------------------
	 *   Parameter: (T) - vertex
	 *------------------------------------------------------------------
	 *   Return: (void) - nothing
	 *******************************************************************/
	void insertVertex(const T &vert);

	/*******************************************************************
	 * int findVertex(T vert) const
	 *
	 *   Mutator; index of vert in graph
	 *------------------------------------------------------------------
	 *   Parameter: (T) - vert
	 *------------------------------------------------------------------
	 *   Return: (void) - nothing
	 *******************************************************************/
	int findVertex(const T &vert) const;

	/*******************************************************************
	 * void insertEdge(T u, T v, int weight)
	 *
	 *   Mutator; adds vert to graph
	 *------------------------------------------------------------------
	 *   Parameter: (T) - starting vert
	 *              (T) - end vert
	 *              (int) - distance between
	 *------------------------------------------------------------------
	 *   Return: (void) - nothing
	 *******************************************************************/
	void insertEdge(const T &u, const T &v, int weight);

	/*******************************************************************
	 * std::vector<T> vertices() const
	 *
	 *   Mutator; finds all the verts
	 *------------------------------------------------------------------
	 *   Parameter: none
	 *------------------------------------------------------------------
	 *   Return: (std::vector<T>) - return all verts
	 *******************************************************************/
	std::vector<T> vertices() const;

	/*******************************************************************
	 * std::vector<std::string> edges() const
	 *
	 *   Mutator; finds all the edges
	 *------------------------------------------------------------------
	 *   Parameter: none
	 *------------------------------------------------------------------
	 *   Return: (std::vector<T>) - return all edges
	 *******************************************************************/
	std::vector<T> edges() const;

	/*******************************************************************
	 * int dfs(T start, std::vector<T> &list)
	 *
	 *   Mutator; find path between all verts
	 *------------------------------------------------------------------
	 *   Parameter: (T) - starting vert
	 *              (std::vector<>) - empty list to contain dfs results
	 *------------------------------------------------------------------
	 *   Return: (int) - total distance
	 *******************************************************************/
	void DijkstraPathFinder(const T &u,
							std::vector<T> &loadGraph,
							int *costs, int *parent);

	/*******************************************************************
	 * std::vector<T> returnPath(const T& u, ...
	 *
	 *   Mutator; gets the path between two points in graph
	 *------------------------------------------------------------------
	 *   Parameter: (T) - starting vert
	 *              (T) - ending vert
	 *              (int) - parent array used to backtrack
	 *------------------------------------------------------------------
	 *   Return: (std::vector<>) - shortest path between the two points
	 *******************************************************************/
	std::vector<T> returnPath(const T &u,
							  const T &v,
							  const int parent[]);

private:
	std::vector<Vertex<T>> graph;
	int distance;

	// fills the vector with the next closest vertex
	// used in dijkstra algorithm
	void findClosest(std::vector<T> &loadGraph, int costs[], int parent[]);

	int distanceFromStart(const T &u, int costs[], int parent[]);

	// returns the index for the smallest edge from a vertex
	int smallestEdge(int vertex);

	// returns distance as an int between two vertices in the graph
	// u denotes starting point and v is ending point
	int distanceBetween(int u, int v);

	// returns the number of verts visited
	// used to check if search is completed
	int verticesVisited();

	// returns the number of edges visited
	// returns 0 is nothing found
	int edgesDiscovered(int currentVert);
};



/*
 *
 *
 *	IMPLEMENTATION SECTION
 *
 *
 */



template<typename T>
Graph<T>::Graph() : distance(0) {}

template<typename T>
void Graph<T>::generateGraph()
{
	QSqlQuery query;
	QString queryString = "SELECT id,distanceTo "
						  "FROM distance "
						  "WHERE beginStadium "
						  "IN(SELECT endStadium FROM distance WHERE id = :id) "
						  "AND endStadium = (SELECT beginStadium FROM distance WHERE id = :id) "
						  "AND id!=:id ";

	query.prepare(queryString);

	if constexpr (std::is_same<T, QString>::value) {
		QStringList teams;
		DBManager::instance()->GetTeams(teams);

		for (int i = 1; i <= teams.size(); i++) {
			insertVertex(teams[i - 1]);
			query.bindValue(":id", i);
			if(!query.exec()) {
				qDebug() << "DBManager::generateGraph vertex: " << i << " failed";
			} else {
				while(query.next())
					insertEdge(teams[i - 1], teams[query.value(0).toInt() - 1], query.value(1).toInt());
			}
		}
	} else if constexpr (std::is_same<T, int>::value) {
		int numTeams = DBManager::instance()->GetNumTeams();

		int i = 1;
		while (i <= numTeams) {
			insertVertex(i);
			query.bindValue(":id", i);
			if(!query.exec()) {
				qDebug() << "DBManager::generateGraph vertex: " << i << " failed";
			} else {
				while(query.next())
					insertEdge(i, query.value(0).toInt(), query.value(1).toInt());
				i++;
			}
		}
	}
}

template<typename T>
bool Graph<T>::empty() const { return graph.empty(); }

template<typename T>
int Graph<T>::size() const { return graph.size(); }

template<typename T>
void Graph<T>::insertVertex(const T &vert) {
	if (findVertex(vert) == size())
		graph.push_back(Vertex<T>{vert, false});
}

template<typename T>
int Graph<T>::findVertex(const T &vert) const {
	int index = 0;

	while (index < size()) {
		if (graph.at(index).vert == vert)
			return index;
		index++;
	}
	return index;
}

template<typename T>
void Graph<T>::insertEdge(const T &u, const T &v, int weight) {
	int index = findVertex(u);

	if (index == size()) {
		insertVertex(u);
		insertEdge(u, v, weight);
	} else {
		graph.at(index).edgeList.push_back(Edge<T>{u, v, weight});
	}
}

template<typename T>
std::vector<T> Graph<T>::vertices() const {
	std::vector<T> temp;
	for (auto a: graph)
		temp.push_back(a.vert);
	return temp;
}

template<typename T>
std::vector<T> Graph<T>::edges() const {
	std::vector<std::string> temp;
	for (size_t i = 0; i < size(); i++) {
		if (graph.at(i).NumOfEdges() != 0) {
			for (size_t j = 0;
				 j < graph.at(i).NumOfEdges(); j++) {
				temp.push_back(
						"(" + std::to_string(graph.at(i).edgeList.at(j).u) +
						", " +
						std::to_string(graph.at(i).edgeList.at(j).v) + ")");
			}
		}
	}
	return temp;
}

template<typename T>
void Graph<T>::DijkstraPathFinder(const T &u, std::vector<T> &loadGraph,
								  int *costs, int *parent) {
	if (verticesVisited() == size()) {
		for (auto &i : graph) {
			i.visited = false;

			for (auto &j : i.edgeList)
				j.discoverEdge = false;
		}
	}

	int currVert = findVertex(u);

	loadGraph.push_back(graph[currVert].vert);

	costs[currVert] = 0;
	parent[currVert] = -1;

	graph[currVert].visited = true;

	while (loadGraph.size() != size())
		findClosest(loadGraph, costs, parent);
}

template<typename T>
std::vector<T>
Graph<T>::returnPath(const T& /*u*/, const T &v, const int *parent) {
	std::vector<T> path;

	int vertex = findVertex(v);

	while (parent[vertex] != -1) {
		path.push_back(graph[vertex].vert);
		vertex = parent[vertex];
	}

	path.push_back(graph[vertex].vert);

	std::reverse(path.begin(), path.end());

	return path;
}

template<typename T>
void
Graph<T>::findClosest(std::vector<T> &loadGraph, int *costs, int *parent) {
	if (loadGraph.size() == 1) {
		int frontVer = findVertex(loadGraph.front());

		int nextVer = smallestEdge(frontVer);

		costs[nextVer] = distanceBetween(frontVer, nextVer);
		parent[nextVer] = frontVer;

		graph[nextVer].visited = true;

		loadGraph.push_back(graph[nextVer].vert);
	} else {
		int smallID = 0;
		int comparatorID = smallID + 1;

		int smallDistance;
		int comparatorDistance;

		int size = loadGraph.size();

		while (comparatorID < size) {
			int smallVer = findVertex(loadGraph[smallID]);
			int compVer = findVertex(loadGraph[comparatorID]);

			if (graph[smallVer].NumOfEdges() == edgesDiscovered(smallVer)) {
				smallID++;
			} else {
				if (graph[compVer].NumOfEdges() !=
					edgesDiscovered(compVer)) {
					smallDistance = distanceBetween(smallVer,
													smallestEdge(smallVer))
									+
									distanceFromStart(graph[smallVer].vert,
													  costs,
													  parent);

					comparatorDistance =
							distanceBetween(compVer, smallestEdge(compVer))
							+ distanceFromStart(graph[compVer].vert, costs,
												parent);

					if (smallDistance > comparatorDistance) {
						smallID = comparatorID;
						smallDistance = comparatorDistance;
					}
				}
			}
			comparatorID++;
		}

		int smallestVertex = smallestEdge(findVertex(loadGraph[smallID]));

		costs[smallestVertex] = smallDistance;
		parent[smallestVertex] = findVertex(loadGraph[smallID]);

		graph[smallestVertex].visited = true;

		loadGraph.push_back(graph[smallestVertex].vert);
	}
}

template<typename T>
int Graph<T>::distanceFromStart(const T &u, int *costs, int *parent) {
	int distance = 0;

	int vertex = findVertex(u);

	while (costs[vertex] != 0) {
		distance += distanceBetween(vertex, parent[vertex]);
		vertex = parent[vertex];
	}

	return distance;
}

template<typename T>
int Graph<T>::smallestEdge(int vertex) {
	int smallestIndex = 0;
	int compIndex = smallestIndex + 1;

	int size = graph.at(vertex).NumOfEdges();

	while (compIndex < size) {
		int smallestVertex = findVertex(
				graph.at(vertex).edgeList.at(smallestIndex).v);

		int compVertex = findVertex(
				graph.at(vertex).edgeList.at(compIndex).v);

		if (graph.at(smallestVertex).visited) {
			smallestIndex++;
		} else {
			if (!(graph.at(compVertex).visited)) {
				if (graph.at(vertex).edgeList.at(smallestIndex).weight >=
					graph.at(vertex).edgeList.at(compIndex).weight)
					smallestIndex = compIndex;
			}
		}
		compIndex++;
	}
	smallestIndex = findVertex(
			graph.at(vertex).edgeList.at(smallestIndex).v);

	return smallestIndex;
}

template<typename T>
int Graph<T>::distanceBetween(int u, int v) {
	int i = 0;
	while (graph[u].edgeList[i].v != graph[v].vert) i++;
	return graph[u].edgeList[i].weight;
}

template<typename T>
int Graph<T>::verticesVisited() {
	int visits = 0;

	typename std::vector<Vertex<T>>::iterator graphIt = graph.begin();

	while (graphIt != graph.end()) {
		if (graphIt->visited) visits++;
		graphIt++;
	}

	return visits;
}

template<typename T>
int Graph<T>::edgesDiscovered(int currentVert) {
	int visits = 0;

	for (int i = 0; i < graph.at(currentVert).NumOfEdges(); i++) {
		if (graph.at(
				findVertex(graph.at(currentVert).edgeList.at(i).v)).visited)
			visits++;
	}

	return visits;
}
#endif //GRAPH_H
