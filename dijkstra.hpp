#pragma once

#include <utility>
#include <vector>
#include <functional>
#include "graph.hpp"
 
#define myPair std::pair<double,std::size_t>
 
template<typename V, typename E>
std::pair<double,std::vector<std::size_t>> dijkstra(const Graph<V,E>& g, std::size_t start_idx, std::size_t end_idx, std::function<void(const E&)> func)
{
    std::vector<double> d(g.nrOfVertices(),std::numeric_limits<double>::infinity());
    std::vector<double> prev(g.nrOfVertices(),-1);
 
    d[start_idx] = 0;
 
    auto cmp = [](const myPair & lhs, const myPair & rhs) { return lhs.first > rhs.first;};
    std::priority_queue<myPair,std::vector<myPair>,decltype(cmp)> Q(cmp);
 
    for(std::size_t i=0; i<g.nrOfVertices(); ++i){
        Q.push(std::make_pair(d[i],i));
    }
 
    while(!Q.empty()){
        auto u = Q.top().second;
        Q.pop();
 
        if(u == end_idx){
            if(d[end_idx] == std::numeric_limits<double>::infinity()){
                return std::make_pair(d[end_idx],std::vector<std::size_t>());
            }
 
            std::vector<std::size_t> path;
            std::size_t temp = end_idx;
 
            while(temp != start_idx){
                path.push_back(temp);
                temp = prev[temp];
            }
            path.push_back(temp);
           
            std::reverse(path.begin(),path.end());
 
            return std::make_pair(d[end_idx],path);
        }
 
       
        for(std::size_t v = 0; v<g.nrOfVertices(); ++v){
            if(!g.edgeExist(u,v) || u==v) continue;
 
            if(d[v] > d[u] + g.getEdge(u,v)){
                d[v] = d[u] + g.getEdge(u,v);
                prev[v] = u;
                Q.push(std::make_pair(d[v],v));
            }
        }
    }
}