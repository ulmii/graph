#include "graph.hpp"
#include <string>
#include <chrono>
#include <functional>
#include <stack>

template <typename V, typename E>
void DFSRecur(const Graph<V, E> &graph, std::size_t start_idx, std::function<void(const V &)> func)
{
    std::vector<bool> visited(graph.nrOfVertices(), false);
    visited[start_idx] = true;

    std::cout << "DFS starting from point: " << start_idx << std::endl;
    func(graph.getVertex(start_idx));

    for (int i = 0; i < graph.nrOfVertices(); i++)
        if (graph.edgeExist(start_idx, i) && !visited[i])
            DFSUtil(visited, graph, i, func);

    std::cout << std::endl;
}

template <typename V, typename E>
void DFSUtil(std::vector<bool> &visited, const Graph<V, E> &graph, std::size_t start_idx, std::function<void(const V &)> func)
{
    visited[start_idx] = true;
    func(graph.getVertex(start_idx));

    for (int i = 0; i < graph.nrOfVertices(); ++i)
        if (graph.edgeExist(start_idx, i) && !visited[i])
            DFSUtil(visited, graph, i, func);
}

template <typename V, typename E>
void DFS(const Graph<V, E> &graph, std::size_t start_idx, std::function<void(const V &)> func)
{
    std::stack<int> s; // Create a stack of ints
    std::vector<bool> visited(graph.nrOfVertices(), false);

    s.push(start_idx);         // Push the vertex onto the stack
    visited[start_idx] = true; // Mark this node as visited

    std::cout << "DFS starting from index: " << start_idx << std::endl;

    if (start_idx >= graph.nrOfVertices()) // End the function if we're at our destination
    {
        std::cout << std::endl;
        return;
    }

    while (!s.empty()) // While the stack is not empty
    {
        int k = s.top(); // Save the top element before popping it off
        s.pop();

        if (k == graph.nrOfVertices()) // Break out of the loop if we've reached our destination
            break;

        func(graph.getVertex(k));

        for (int i = graph.nrOfVertices(); i >= 0; --i) // For all adjacent vertices
            if (graph.edgeExist(k, i) && !visited[i]) // If they're connected and we haven't visited it yet
            {
                s.push(i); // Add it to our stack, and mark that we've visited it
                visited[i] = true;
            }
    }

    std::cout << std::endl;
}

int main()
{
    Graph<std::string, double> g;

    for (std::size_t i = 0u; i < 6u; ++i)
    {
        g.insertVertex("data " + std::to_string(i));
    }

    for (std::size_t i = 0u; i < g.nrOfVertices(); ++i)
    {
        for (std::size_t j = 0u; j < g.nrOfVertices(); ++j)
        {
            if ((i + j) & 1u || i & 1u)
            {
                g.insertEdge(i, j, ((i != j) ? (i + j) / 2. : 1.));
            }
        }
    }

    g.insertEdge(0, 2, 4.);

    std::cout << (g.removeVertex(1) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << (g.removeEdge(2, 2) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << (g.removeEdge(2, 3) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << (g.removeEdge(4, 3) ? "Udalo sie" : "Nie udalo sie") << std::endl;

    std::cout << "Nr of vertices: " << g.nrOfVertices() << std::endl;
    std::cout << "Nr of edges: " << g.nrOfEdges() << std::endl;
    std::cout << std::endl;

    g.printNeighborhoodMatrix();

    std::cout << std::endl;
    std::cout << "Vertices data:" << std::endl;

    for (auto v_it = g.beginVertices(); v_it != g.endVertices(); ++v_it)
    {
        std::cout << *v_it << ", ";
    }

    std::cout << std::endl
              << std::endl;

    std::cout << "Edges data:" << std::endl;

    for (auto e_it = g.beginEdges(); e_it != g.endEdges(); ++e_it)
    {
        std::cout << *e_it << ", ";
    }
    std::cout << std::endl
              << std::endl;

    DFS<std::string, double>(g, 0u, [](const std::string &v) -> auto {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    DFS<std::string, double>(g, 1u, [](const std::string &v) -> auto {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    DFS<std::string, double>(g, 2u, [](const std::string &v) -> auto {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    DFS<std::string, double>(g, 3u, [](const std::string &v) -> auto {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    DFS<std::string, double>(g, 4u, [](const std::string &v) -> auto {
        std::cout << v << " ";
    });
    std::cout << std::endl;
}