#include <iostream>
#include <sstream>
#include "graphiso.h"

using namespace std;

// ================= Complete - Begin Graph class implementation ===================
Graph::Graph(std::istream& istr)
{
    string aline;
    while(getline(istr,aline))
    {
        istringstream iss(aline);
        string u, v;
        if(iss >> u){
            VERTEX_SET_T neighbors;
            while(iss >> v)
            {
                neighbors.insert(v);
            }
            adj_.insert(std::make_pair(u,neighbors));
        }
    }
}


bool Graph::edgeExists(const VERTEX_T& u, const VERTEX_T& v) const
{
    if((adj_.find(u) != adj_.end()) && (adj_.at(u).find(v) != adj_.at(u).end()))
    {
        return true;
    }
    return false;
}
const VERTEX_SET_T& Graph::neighbors(const VERTEX_T& v) const
{
    if(adj_.find(v) == adj_.end()){
        throw std::invalid_argument("Neighbors: invalid vertex - not in  map");
    }
    return adj_.at(v);
}
VERTEX_LIST_T Graph::vertices() const
{
    VERTEX_LIST_T verts;
    for(const auto& p : adj_)
    {
        verts.push_back(p.first);
    }
    return verts;
}
// ================= Complete - End Graph class implementation ===================

// Prototype and helper functions here
bool graphIso_helper(int g1idx, const VERTEX_LIST_T& g1verts, VERTEX_SET_T& g2used, const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping);
// To be completed
bool isConsistent(const Graph& g1, const Graph& g2, const VERTEX_ID_MAP_T& mapping)
{
    // Feel free to change or remove this starter code
    VERTEX_LIST_T g1verts = g1.vertices();
    for(const auto& g1u : g1verts)
    {
        if (mapping.find(g1u) != NULL)
        {
            if (g1.neighbors(g1u).size() != g2.neighbors(mapping[g1u]).size())
            {
                return false;
            }
            for (const auto& g1v : g1.neighbors(g1u))
            {
                if (mapping.find(g1v) != NULL)
                {
                    if (! g2.edgeExists(mapping[g1u], mapping[g1v]))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Add any helper functions you deem useful

bool graphIso_helper(int g1idx, const VERTEX_LIST_T& g1verts, VERTEX_SET_T& g2used, const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    if (g1idx >= int(g1verts.size()))
    {
        return true;
    }
    VERTEX_T g1v = g1verts[g1idx];
    for (auto g2v : g2.vertices())
    {
        if (g2used.find(g2v) == g2used.end())
        {
            mapping.insert({g1v, g2v});
            if (isConsistent(g1, g2, mapping))
            {
                g2used.insert(g2v);
                if (graphIso_helper(g1idx+1, g1verts, g2used, g1, g2, mapping))
                {
                    return true;
                }
            }
            mapping.remove(g1v);
            g2used.erase(g2v);
        }
    }
    return false;
}

// To be completed
bool graphIso(const Graph& g1, const Graph& g2, VERTEX_ID_MAP_T& mapping)
{
    VERTEX_LIST_T g1verts = g1.vertices();
    VERTEX_LIST_T g2verts = g2.vertices();
    VERTEX_SET_T g2used;
    if(g1verts.size() != g2verts.size())
    {
        return false;
    }
    return graphIso_helper(0, g1verts, g2used, g1, g2, mapping);
}

