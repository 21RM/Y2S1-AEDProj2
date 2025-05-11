//
// Created by alexandre on 22-12-2023.
//

#ifndef AED_PROJ_2_GRAPH_H
#define AED_PROJ_2_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <memory>
#include <algorithm>
#include <unordered_set>
#include "Airline.h"
#include "Airport.h"


using namespace std;

class Edge;
class Graph;
class Vertex;

/**
 * @class Vertex
 *
 * @brief Represents a vertex in the graph with auxiliary fields and methods.
 */
class Vertex {
    Airport info; /**< Contents of the vertex. */
    std::vector<Edge> adj; /**< List of outgoing edges. */
    bool visited; /**< Auxiliary field for visit status. */
    bool processing; /**< Auxiliary field for processing status. */
    int indegree; /**< Auxiliary field for indegree. */
    int num; /**< Auxiliary field for numerical value. */
    int low; /**< Auxiliary field for low value. */

    /**
     * @brief Adds an edge from the current vertex to the specified destination vertex.
     *
     * @param dest Destination vertex.
     * @param w Edge weight.
     * @param airline Airline associated with the edge.
     */
    void addEdge(std::shared_ptr<Vertex> dest, double w, const Airline &airline);

    /**
     * @brief Removes the edge from the current vertex to the specified destination vertex.
     *
     * @param d Destination vertex to remove the edge to.
     * @return True if the edge is successfully removed, false otherwise.
     */
    bool removeEdgeTo(std::shared_ptr<Vertex> d);

public:
    /**
     * @brief Constructs a Vertex object with the given airport information.
     *
     * @param in Airport information.
     */
    Vertex(Airport in);

    /**
     * @brief Gets the airport information of the vertex.
     *
     * @return Airport information.
     */
    Airport &getInfo();

    /**
     * @brief Gets the constant airport information of the vertex.
     *
     * @return Constant airport information.
     */
    Airport getInfo() const;

    /**
     * @brief Sets the airport information of the vertex.
     *
     * @param in New airport information.
     */
    void setInfo(Airport in);

    /**
     * @brief Checks if the vertex has been visited.
     *
     * @return True if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Sets the visit status of the vertex.
     *
     * @param v Visit status to set.
     */
    void setVisited(bool v);

    /**
     * @brief Checks if the vertex is currently being processed.
     *
     * @return True if the vertex is being processed, false otherwise.
     */
    bool isProcessing() const;

    /**
     * @brief Sets the processing status of the vertex.
     *
     * @param p Processing status to set.
     */
    void setProcessing(bool p);

    /**
     * @brief Gets the list of outgoing edges from the vertex.
     *
     * @return List of outgoing edges.
     */
    const std::vector<Edge> &getAdj() const;

    /**
     * @brief Sets the list of outgoing edges for the vertex.
     *
     * @param adj List of outgoing edges to set.
     */
    void setAdj(const std::vector<Edge> &adj);

    /**
     * @brief Gets the indegree of the vertex.
     *
     * @return Indegree of the vertex.
     */
    int getIndegree() const;

    /**
     * @brief Sets the indegree of the vertex.
     *
     * @param indegree New indegree value to set.
     */
    void setIndegree(int indegree);

    /**
     * @brief Gets the numerical value of the vertex.
     *
     * @return Numerical value of the vertex.
     */
    int getNum() const;

    /**
     * @brief Sets the numerical value of the vertex.
     *
     * @param num New numerical value to set.
     */
    void setNum(int num);

    /**
     * @brief Gets the low value of the vertex.
     *
     * @return Low value of the vertex.
     */
    int getLow() const;

    /**
     * @brief Sets the low value of the vertex.
     *
     * @param low New low value to set.
     */
    void setLow(int low);

    /**
     * @brief Gets the number of different airlines associated with outgoing edges.
     *
     * @return Number of different airlines.
     */
    size_t getNumDifferentAirlines();

    friend class Graph; // Allow Graph class to access private members of Vertex.

};

/**
 * @class Edge
 *
 * @brief Represents an edge in the graph connecting two vertices with weight and airline information.
 */
class Edge {
    std::shared_ptr<Vertex> dest; /**< Destination vertex of the edge. */
    double weight; /**< Edge weight. */
    Airline airline_; /**< Airline associated with the edge. */

public:
    /**
     * @brief Constructs an Edge object with the specified destination, weight, and airline.
     *
     * @param d Destination vertex of the edge.
     * @param w Edge weight.
     * @param airline Airline associated with the edge.
     */
    Edge(std::shared_ptr<Vertex> d, double w, const Airline &airline);

    /**
     * @brief Gets the destination vertex of the edge.
     *
     * @return Destination vertex of the edge.
     */
    std::shared_ptr<Vertex> getDest() const;

    /**
     * @brief Sets the destination vertex of the edge.
     *
     * @param dest New destination vertex to set.
     */
    void setDest(std::shared_ptr<Vertex> dest);

    /**
     * @brief Gets the weight of the edge.
     *
     * @return Weight of the edge.
     */
    double getWeight() const;

    /**
     * @brief Sets the weight of the edge.
     *
     * @param weight New weight to set.
     */
    void setWeight(double weight);

    /**
     * @brief Gets the airline associated with the edge.
     *
     * @return Airline associated with the edge.
     */
    const Airline &getAirline() const;

    friend class Graph; // Allow Graph and Vertex classes to access private members of Edge.
    friend class Vertex;

};

/**
 * @class Graph
 *
 * @brief Represents a graph with vertices, edges, and various graph algorithms.
 */
class Graph {
    std::unordered_map<std::string, std::shared_ptr<Vertex>> vertexSet; /**< Vertex set of the graph. */
    int _index_; /**< Auxiliary field for graph index. */
    std::stack<Vertex> _stack_; /**< Auxiliary field for stack operations. */
    std::list<std::list<Airport>> _list_sccs_; /**< Auxiliary field for strongly connected components. */
    size_t edgeCount_ = 0; /**< Number of edges in the graph. */

    /**
     * @brief Performs depth-first search (DFS) visit on the specified vertex.
     *
     * @param v Vertex to visit.
     * @param res Vector to store the result.
     */
    void dfsVisit(std::shared_ptr<Vertex> v, std::vector<Airport> &res) const;

    /**
     * @brief Checks if the graph represented by the specified vertex is a directed acyclic graph (DAG).
     *
     * @param v Vertex to start the check.
     * @return True if the graph is a DAG, false otherwise.
     */
    bool dfsIsDAG(std::shared_ptr<Vertex> v) const;

public:
    /**
     * @brief Finds the vertex in the graph based on the given airport information.
     *
     * @param in Airport information to search for.
     * @return Shared pointer to the found vertex, or nullptr if not found.
     */
    std::shared_ptr<Vertex> findVertex(const Airport &in) const;

    /**
     * @brief Gets the number of vertices in the graph.
     *
     * @return Number of vertices in the graph.
     */
    int getNumVertex() const;

    /**
     * @brief Adds a vertex to the graph based on the given airport information.
     *
     * @param in Airport information for the new vertex.
     * @return True if the vertex is successfully added, false otherwise.
     */
    bool addVertex(const Airport &in);

    /**
     * @brief Removes a vertex from the graph based on the given airport information.
     *
     * @param in Airport information for the vertex to be removed.
     * @return True if the vertex is successfully removed, false otherwise.
     */
    bool removeVertex(const Airport &in);

    /**
     * @brief Adds an edge between the source and destination airports with weight and airline information.
     *
     * @param sourc Source airport.
     * @param dest Destination airport.
     * @param w Edge weight.
     * @param airline Airline associated with the edge.
     * @return True if the edge is successfully added, false otherwise.
     */
    bool addEdge(const Airport &sourc, const Airport &dest, double w, const Airline &airline);

    /**
     * @brief Removes the edge between the source and destination airports.
     *
     * @param sourc Source airport.
     * @param dest Destination airport.
     * @return True if the edge is successfully removed, false otherwise.
     */
    bool removeEdge(const Airport &sourc, const Airport &dest);

    /**
     * @brief Gets the vertex set of the graph.
     *
     * @return Vertex set of the graph.
     */
    std::unordered_map<std::string, std::shared_ptr<Vertex>> getVertexSet() const;

    /**
     * @brief Performs depth-first search (DFS) on the graph and returns the result.
     *
     * @return Vector of airports representing the result of DFS.
     */
    std::vector<Airport> dfs() const;

    /**
     * @brief Performs depth-first search (DFS) starting from the specified airport and returns the result.
     *
     * @param source Source airport for DFS.
     * @return Vector of airports representing the result of DFS.
     */
    std::vector<Airport> dfs(const Airport &source) const;

    /**
     * @brief Performs breadth-first search (BFS) starting from the specified airport and returns the result.
     *
     * @param source Source airport for BFS.
     * @return Vector of airports representing the result of BFS.
     */
    std::vector<Airport> bfs(const Airport &source) const;

    /**
     * @brief Performs topological sorting on the graph and returns the result.
     *
     * @return Vector of airports representing the result of topological sorting.
     */
    std::vector<Airport> topsort() const;

    /**
     * @brief Checks if the graph is a directed acyclic graph (DAG).
     *
     * @return True if the graph is a DAG, false otherwise.
     */
    bool isDAG() const;

    /**
     * @brief Gets the number of edges in the graph.
     *
     * @return Number of edges in the graph.
     */
    size_t getNumEdge() const;

    /**
     * @brief Performs breadth-first search (BFS) starting from the specified airport and returns the result
     *        up to a specified step.
     *
     * @param source Source airport for BFS.
     * @param step Maximum step to traverse.
     * @return Vector of airports representing the result of BFS up to the specified step.
     */
    std::vector<Airport> bfsWithSteps(const Airport &source, int step) const;

    /**
     * @brief Finds the furthest vertices from the specified source airport using BFS.
     *
     * @param source Source airport for BFS.
     * @return Vector of pairs representing the furthest vertices and their distances.
     */
    std::vector<std::pair<Airport, int>> bfsFurthestVertices(const Airport &source) const;

    /**
     * @brief Finds the shortest path between two airports using BFS.
     *
     * @param source Source airport.
     * @param destination Destination airport.
     * @return Vector of vectors representing the shortest paths between the source and destination airports.
     */
    std::vector<std::vector<Airport>> bfsShortestPath(const Airport &source, const Airport &destination) const;

    /**
     * @brief Finds the shortest path between two vertices using BFS.
     *
     * @param source Source vertex.
     * @param destination Destination vertex.
     * @return Vector of vectors representing the shortest paths between the source and destination vertices.
     */
    std::vector<std::vector<Airport>> bfsShortestPath(std::shared_ptr<Vertex> source,
                                                      std::shared_ptr<Vertex> destination) const;

    /**
     * @brief Finds the shortest path between two airports using BFS, considering forbidden airlines.
     *
     * @param source Source airport.
     * @param destination Destination airport.
     * @param forbidden Vector of forbidden airlines.
     * @return Vector of vectors representing the shortest paths between the source and destination airports.
     */
    std::vector<std::vector<Airport>> bfsShortestPath(const Airport &source, const Airport &destination,
                                                      const std::vector<Airline> forbidden) const;

    /**
     * @brief Finds the shortest path between two airports using BFS, considering forbidden airlines.
     * @param source Source airport
     * @param destination Destination airport
     * @param forbidden Vector of forbidden airlines.
     * @return Vector of vectors representing the shortest paths between the source and destination airports.
     */
    vector<vector<Airport>> bfsShortestPath(shared_ptr<Vertex> source, shared_ptr<Vertex> destination,
                                            const std::vector<Airline> forbidden) const;
};

#endif //AED_PROJ_2_GRAPH_H
