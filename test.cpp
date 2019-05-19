#include "graph.hpp"
#include <string>
#include <chrono>
#include <functional>
#include <stack>
#include <queue>
#include <set>

template <typename V, typename E>
void DFS(const Graph<V, E> &graph, std::size_t start_idx, std::function<void(const V &)> func)
{
    std::stack<int> s; 
    std::vector<bool> visited(graph.nrOfVertices(), false);

    s.push(start_idx);         
    visited[start_idx] = true;

    std::cout << "DFS starting from index: " << start_idx << std::endl;

    if (start_idx >= graph.nrOfVertices()) 
    {
        std::cout << std::endl;
        return;
    }

    while (!s.empty()) 
    {
        int v = s.top();
        s.pop();

        if (v == graph.nrOfVertices())
            break;

        func(graph.getVertex(v));
        
        for (int i = graph.nrOfVertices(); i >= 0; --i)
        {
            if (graph.edgeExist(v, i) && !visited[i]) 
            {
                s.push(i);
                visited[i] = true;
            }
        }
    }

    std::cout << std::endl;
}

template <typename V, typename E>
void BFS(const Graph<V, E> &graph, std::size_t start_idx, std::function<void(const V &)> func)
{
    std::queue<int> s;
    std::vector<bool> visited(graph.nrOfVertices(), false);

    s.push(start_idx);      
    visited[start_idx] = true; 

    std::cout << "BFS starting from index: " << start_idx << std::endl;

    if (start_idx >= graph.nrOfVertices())
    {
        std::cout << std::endl;
        return;
    }

    while (!s.empty()) 
    {
        int k = s.front();
        s.pop();

        if (k == graph.nrOfVertices())
            break;

        func(graph.getVertex(k));
        
        for (int i = graph.nrOfVertices(); i >= 0; --i) 
            if (graph.edgeExist(k, i) && !visited[i])   
            {
                s.push(i);
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

    BFS<std::string, double>(g, 3u, [](const std::string &v) -> auto {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    for(auto dit = g.beginDFS(); dit != g.endDFS(); ++dit)
    {
        std::cout << *dit << " " << std::flush;
    }
    std::cout << std::endl;

    for(auto dit = g.beginBFS(3u); dit != g.endBFS(); ++dit)
    {
        std::cout << *dit << " " << std::flush;
    }
    std::cout << std::endl;

}