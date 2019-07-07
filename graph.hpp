#pragma once

#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>
#include <optional>
#include <stack>
#include <queue>

template <typename V, typename E>
class Graph
{
    public:
        class VerticesIterator
        {
            friend class Graph<V, E>;

             public:
                VerticesIterator() = default;
                ~VerticesIterator() = default;
                VerticesIterator(const VerticesIterator&) = default;
                VerticesIterator(VerticesIterator&&) = default;

                VerticesIterator& operator=(const VerticesIterator&) = default;
                VerticesIterator& operator=(VerticesIterator&&) = default;

                bool operator==(const VerticesIterator &vi) const { return __graph_ptr->__vertexes == vi.__graph_ptr->__vertexes && __index == vi.__index; }
                bool operator!=(const VerticesIterator &vi) const { return !(*this == vi); }
                VerticesIterator& operator++() { ++__index; return *this; }
                VerticesIterator operator++(int) { VerticesIterator temp(*this); ++(*this); return temp; }
                V& operator*() const { return __graph_ptr->__vertexes[__index]; }
                V* operator->() const { return &__graph_ptr->__vertexes[__index]; }
                operator bool() const { return !(*this == __graph_ptr->endVertices()); }

            private:
                VerticesIterator(Graph<V, E>* graph, std::size_t current_vertex_id = 0u)
                    : __graph_ptr(graph), __index(current_vertex_id) {}

                Graph<V, E>* __graph_ptr;
                std::size_t __index{};
        };

        class EdgesIterator
        {
            friend class Graph<V, E>;

             public:
                EdgesIterator() = default;
                ~EdgesIterator() = default;
                EdgesIterator(const EdgesIterator&) = default;
                EdgesIterator(EdgesIterator&&) = default;

                EdgesIterator& operator=(const EdgesIterator&) = default;
                EdgesIterator& operator=(EdgesIterator&&) = default;

                bool operator==(const EdgesIterator &ei) const { return __graph_ptr->__adj == ei.__graph_ptr->__adj && __row == ei.__row && __col == ei.__col; }
                bool operator!=(const EdgesIterator &ei) const { return !(*this == ei); }
                EdgesIterator& operator++();
                EdgesIterator operator++(int) { EdgesIterator temp(*this); ++(*this); return temp; }
                E& operator*() const { return __graph_ptr->__adj[__row][__col].value(); }
                E* operator->() const { return &__graph_ptr->__adj[__row][__col].value(); }
                operator bool() const { return !(*this == __graph_ptr->endEdges()); }

            private:
                EdgesIterator(Graph<V, E>* graph, std::size_t nm_row = 0u, std::size_t nm_col = 0u)
                    : __graph_ptr(graph), __row(nm_row), __col(nm_col) {}

                Graph<V, E>* __graph_ptr;
                std::size_t __row{};
                std::size_t __col{};
        };

        class DFSIterator
        {
            friend class Graph<V, E>;

            public:
                DFSIterator() = default;
                ~DFSIterator() = default;
                DFSIterator(const DFSIterator&) = default;
                DFSIterator(DFSIterator&&) = default;

                DFSIterator& operator=(const DFSIterator&) = default;
                DFSIterator& operator=(DFSIterator&&) = default;

                bool operator==(const DFSIterator &other) const { return __graph_ptr == other.__graph_ptr && __index == other.__index; }
                bool operator!=(const DFSIterator &other) const { return !(*this == other); }
                DFSIterator& operator++();
                DFSIterator& operator++(int) { DFSIterator temp(*this); ++(*this); return temp; }
                V& operator*() const { return __graph_ptr->__vertexes[__index]; }
                V* operator->() const { return &__graph_ptr->__vertexes[__index]; }
                operator bool() const { return !(*this == __graph_ptr->endDFS()); }

            private:
                DFSIterator(Graph<V, E> *graph, std::size_t index)
                    : __graph_ptr(graph), __index(index)
                    {
                        __visited = std::vector<bool>(graph->__numberOfVertices, false);
                        __visited[index] = true;
                    }
                Graph<V, E> *__graph_ptr;
                std::size_t __index{};
                std::stack<int> __stack;
                std::vector<bool> __visited;
        };

        class BFSIterator
        {
            friend class Graph<V, E>;

            public:
                BFSIterator() = default;
                ~BFSIterator() = default;
                BFSIterator(const BFSIterator&) = default;
                BFSIterator(BFSIterator&&) = default;

                BFSIterator& operator=(const BFSIterator&) = default;
                BFSIterator& operator=(BFSIterator&&) = default;

                bool operator==(const BFSIterator &other) const { return __graph_ptr == other.__graph_ptr && __index == other.__index; }
                bool operator!=(const BFSIterator &other) const { return !(*this == other); }
                BFSIterator& operator++();
                BFSIterator& operator++(int) { BFSIterator temp(*this); ++(*this); return temp; }
                V& operator*() const { return __graph_ptr->__vertexes[__index]; }
                V* operator->() const { return &__graph_ptr->__vertexes[__index]; }
                operator bool() const { return !(*this == __graph_ptr->endDFS()); }

            private:
                BFSIterator(Graph<V, E> *graph, std::size_t index)
                    : __graph_ptr(graph), __index(index)
                    {
                        __visited = std::vector<bool>(graph->__numberOfVertices, false);
                        __visited[index] = true;
                    }
                Graph<V, E> *__graph_ptr;
                std::size_t __index{};
                std::queue<int> __queue;
                std::vector<bool> __visited;
        };

    public:
        Graph() = default;
        ~Graph() = default;
        Graph(const Graph&) = default;
        Graph(Graph&&) = default;

        Graph<V, E>& operator=(const Graph<V, E>&) = default;
        Graph<V, E>& operator=(Graph<V, E>&&) = default;

        VerticesIterator insertVertex(const V &vertex_data);
        std::pair<EdgesIterator, bool> insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
        bool removeVertex(std::size_t vertex_id);
        bool removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
        bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const { return vertex1_id < __numberOfVertices && vertex2_id < __numberOfVertices && __adj[vertex1_id][vertex2_id]; }
        std::size_t nrOfVertices() const { return __numberOfVertices; }
        std::size_t nrOfEdges() const { return __numberOfEdges; }
        void printNeighborhoodMatrix() const;
        V getVertex(std::size_t index) const { return __vertexes[index]; }
        E getEdge(std::size_t index1, std::size_t index2) const { return __adj[index1][index2].value(); }

        VerticesIterator vertex(std::size_t vertex_id) { return VerticesIterator(this, vertex_id); }
        EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id) { return EdgesIterator(this, vertex1_id, vertex2_id); }

        VerticesIterator begin() { return beginVertices(); }
        VerticesIterator end() { return endVertices(); }
        VerticesIterator beginVertices() { return VerticesIterator(this); }
        VerticesIterator endVertices() { return VerticesIterator(this, __numberOfVertices); }

        EdgesIterator beginEdges();
        EdgesIterator endEdges() { return EdgesIterator(this, __numberOfVertices, 0u); }

        DFSIterator beginDFS(std::size_t index = 0u) { return DFSIterator(this, index); }
        DFSIterator endDFS() { return DFSIterator(this, __numberOfVertices); }

        BFSIterator beginBFS(std::size_t index = 0u) { return BFSIterator(this, index); }
        BFSIterator endBFS() { return BFSIterator(this, __numberOfVertices); }
        
    private:
        std::vector<std::vector<std::optional<E>>> __adj;
        std::vector<V> __vertexes;
        std::size_t __numberOfEdges{};
        std::size_t __numberOfVertices{};
};

template <typename V, typename E>
auto Graph<V, E>::EdgesIterator::operator++() -> EdgesIterator&
{   
    while( !__graph_ptr->__adj[__row][++__col] || __col == __graph_ptr->__numberOfVertices )
    {
        if(__col >= __graph_ptr->__numberOfVertices)
        {
            ++__row;
            __col = 0u;
            
            if(*this == __graph_ptr->endEdges() || __graph_ptr->__adj[__row][__col]) 
                break;
        }
    }

    return *this;
}

template <typename V, typename E>
auto Graph<V, E>::DFSIterator::operator++() -> DFSIterator&
{   
    for (int i = __graph_ptr->nrOfVertices(); i >= 0; --i)
        if (__graph_ptr->edgeExist(__index, i) && !__visited[i])   
        {
            __stack.push(i);
            __visited[i] = true;
        }

    if(!__stack.empty())
    {
        __index = __stack.top();
        __stack.pop();
    }
    else
        __index = __graph_ptr->__numberOfVertices;

    return *this;
}

template <typename V, typename E>
auto Graph<V, E>::BFSIterator::operator++() -> BFSIterator&
{   
    for (int i = 0; i < __graph_ptr->nrOfVertices(); ++i)
        if (__graph_ptr->edgeExist(__index, i) && !__visited[i])   
        {
            __queue.push(i);
            __visited[i] = true;
        }

    if(!__queue.empty())
    {
        __index = __queue.front();
        __queue.pop();
    }
    else
        __index = __graph_ptr->__numberOfVertices;

    return *this;
}

template <typename V, typename E>
auto Graph<V,E>::beginEdges() -> EdgesIterator
{
    std::size_t row{0u};
    std::size_t col{0u};
    
    while(row != __numberOfVertices && !__adj[row][col])
        if(++col >= __numberOfVertices)
        {
            ++row;
            col = 0u;
        }

    return EdgesIterator(this, row, col);    
}

template <typename V, typename E>
auto Graph<V,E>::insertVertex(const V &vertex_data) -> VerticesIterator
{
    __vertexes.emplace_back(vertex_data);
    
    __adj.emplace_back(std::vector<std::optional<E>>{});

    for(std::size_t i = 0u; i <= __numberOfVertices; ++i) 
    {
        if( i != __numberOfVertices )
            __adj[i].emplace_back( std::optional<E> {} );
        else
            for( std::size_t j = 0u; j <= i; ++j )
                __adj[i].emplace_back( std::optional<E> {} );
           
    }

    ++__numberOfVertices;

    return VerticesIterator(this, __numberOfVertices);
}

template <typename V, typename E>
auto Graph<V, E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label, bool replace) -> std::pair<EdgesIterator, bool>
{
    if( __numberOfVertices < vertex1_id || __numberOfVertices < vertex2_id)
        return std::pair<EdgesIterator, bool> (endEdges(), false);
    
    if( !replace && __adj[vertex1_id][vertex2_id] )
        return std::pair<EdgesIterator, bool> (EdgesIterator(this, vertex1_id, vertex2_id), false);

    __adj[vertex1_id][vertex2_id] = {label};
    ++__numberOfEdges;

    return std::pair<EdgesIterator, bool> (EdgesIterator(this, vertex1_id, vertex2_id), true);
}

template <typename V, typename E>
bool Graph<V, E>::removeVertex(std::size_t vertex_id)
{
    if( __numberOfVertices < vertex_id ) 
        return false;

    for( const auto &e : __adj[vertex_id] )
        if(e) --__numberOfEdges;

    __vertexes.erase( __vertexes.begin() + vertex_id );
    __adj.erase( __adj.begin() + vertex_id );

    for( std::size_t i = 0u; i < __adj.size(); ++i )
    {
        if( __adj[i][vertex_id] ) --__numberOfEdges;
        __adj[i].erase( __adj[i].begin() + vertex_id );
    }

    --__numberOfVertices;

    return true;
}

template <typename V, typename E>
bool Graph<V, E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id)
{
    if( __numberOfVertices < vertex1_id || __numberOfVertices < vertex2_id )
        return false;

    if( __adj[vertex1_id][vertex2_id] )
    {
        __adj[vertex1_id][vertex2_id].reset();
        --__numberOfEdges;
        return true;
    }
    
    return false;
}

template <typename V, typename E>
void Graph<V, E>::printNeighborhoodMatrix() const
{
    for ( const auto &row : __adj )
    {
        for ( const auto &el : row ) 
            std::cout << (el ? el.value() : 0) << ' ';

        std::cout << std::endl;
    }   
}