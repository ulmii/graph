#include "graph.hpp"
#include <string>
#include<chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    Graph<std::string, int> g;

    g.edgeExist(-1, -1);

    g.insertVertex("V1");
    g.insertVertex("V2");
    g.insertVertex("V3");
    g.insertVertex("V4");

    g.insertEdge(0, 0, 1);
    g.insertEdge(0, 1, 2);
    g.insertEdge(1, 2, 3);
    g.insertEdge(2, 2, 4);
    g.insertEdge(3, 2, 5);
    g.insertEdge(3, 0, 6);
    g.insertEdge(0, 3, 7);
    g.insertEdge(1, 3, 8);

    std::cout << (g.removeEdge(0, 1) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << (g.removeEdge(1, 0) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << (g.removeVertex(2) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << (g.removeVertex(5) ? "Udalo sie" : "Nie udalo sie") << std::endl;
    std::cout << "Nr of vertices: " << g.nrOfVertices() << std::endl;
    std::cout << "Nr of edges: " << g.nrOfEdges() << std::endl;
    
    g.printNeighborhoodMatrix();

    for(auto it = g.beginVertices(); it != g.endVertices(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    for(auto it = g.beginEdges(); it != g.endEdges(); ++it) {
        std::cout << *it << " ";
    }
    
    std::cout << "\n\n";
    
    auto g2 = g;

    g2.printNeighborhoodMatrix();

    for(auto it = g2.beginVertices(); it != g2.endVertices(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    for(auto it = g2.beginEdges(); it != g2.endEdges(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n\n";
    
    Graph<std::string, int> g3;

    g3 = std::move(g2);

    g3.printNeighborhoodMatrix();

    for(auto it = g3.beginVertices(); it != g3.endVertices(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    for(auto it = g3.beginEdges(); it != g3.endEdges(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << "\n\n";

    auto end = std::chrono::high_resolution_clock::now();

    std::cout<< "Czas " << std::chrono::duration<double>(end-start).count() << std::endl;

}