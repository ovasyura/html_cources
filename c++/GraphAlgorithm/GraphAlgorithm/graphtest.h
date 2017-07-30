#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED


#include <random>
#include <algorithm>
#include <set>
#include <map>
#include <deque>

using namespace std;

class Graphtest{
public:
    void add_edge(const int&, const map<int, double>&);
    void add_edge(const int&, const int&, const double&);
    int edge_count();
    int vertex_count();
    void vertices();
    bool adjacentQ(const int&, const int&);
    bool connectQ(const int& x);
    set<int> get_neighbors(const int&);
    double get_edge_value(const int&, const int&);
    bool set_edge_value(const int&, const int&, const double&);
    void clear_edge(const int&, const int&);
    void clear_all();
    void set_graph(const int&, const double&, const int&);
    Graphtest(){};
    bool Dijkstra(const int&, map<int,double>&, map<int,int>&);
    double shortest_distance(const int&, const int&);
private:
    map<int, map<int, double>> adj;
};
void Graphtest::set_graph(const int& nVetex, const double& eDensity, const int& wRange){
    default_random_engine gen;
    uniform_real_distribution<double> pe(0.0, 1.0);
    uniform_int_distribution<int> pw(1, wRange);
    int weight;
    for(int i=0; i<nVetex; ++i){
        for(int j=i+1; j<nVetex; ++j){
            if(i==j)
                add_edge(i,j,0);
            else{
                if(pe(gen) < eDensity){
                    weight = pw(gen);
                    add_edge(i,j,weight);
                    add_edge(j,i,weight);
                }
            }
        }
    }
}
void Graphtest::clear_all(){
    adj.clear();
}
void Graphtest::vertices(){
//    for(auto i : adj){
//        cout<<i.first<<": \n";
//        for(auto j : i.second)
//            cout<<"("<<j.first<<","<<j.second<<")"<<endl;
//        cout<<endl;
//    }
}
double Graphtest::get_edge_value(const int& x, const int& y){
    if(adj.find(x)!=adj.end()){
        if(adj[x].find(y)!=adj[x].end()){
            return adj[x][y];
        }
    }
    return 0;
}
bool Graphtest::set_edge_value(const int& x, const int& y, const double& w){
    if(adj.find(x)!=adj.end()){
        if(adj[x].find(y)!=adj[x].end()){
            adj[x][y] = w;
            return true;
        }
    }
    return false;
};
set<int> Graphtest::get_neighbors(const int& x){
    set<int> nbr;
    if(adj.find(x)==adj.end()) return nbr;

    for(auto i : adj[x]){
        if(i.first!=x) nbr.insert(i.first);
    }
    return nbr;

}
void Graphtest::clear_edge(const int& x, const int& y){
    if(adj.find(x)!=adj.end()){
        if(adj[x].find(y)!=adj[x].end())
            adj[x].erase(y);
            if(adj[x].size()==0) adj.erase(x);
    }
}
bool Graphtest::adjacentQ(const int& x, const int& y){
    if(adj.find(x)!=adj.end()){
        if(adj[x].find(y)!=adj[x].end()){
            return true;
        }
    }
    if(adj.find(y)!=adj.end()){
        if(adj[y].find(x)!=adj[y].end()){
                return true;
        }
    }
    return false;
}
bool Graphtest::connectQ(const int& x){
    if(adj.find(x)==adj.end()) return false;

// v counts # vertices in the component of x.
// c contains the component of x. Not used here.
    deque<int> v{x};
    set<int> c{x};
    for(auto i=v.begin(); i!=v.end(); ++i){
        for(auto j : adj[*i]){
            c.insert(j.first);
            if(find(v.begin(),v.end(),j.first)==v.end())
                v.push_back(j.first);
        }
    }
    if(v.size() == static_cast<deque<int>::size_type> (vertex_count()))
        return true;
    else
        return false;
}
int Graphtest::vertex_count(){
    set<double> v;
    for(auto i : adj){
        v.insert(i.first);
        for(auto j : i.second)
            v.insert(j.first);
    }
    return v.size();
}
int Graphtest::edge_count(){
    int e=0;
    for(auto i : adj){
        for(auto j : i.second){
            if(i.first!=j.first) e++;
        }
    }
    return e/2;
}
void Graphtest::add_edge(const int& x, const map<int, double>& elist){
    adj[x] = elist;
}
void Graphtest::add_edge(const int& x, const int& y, const double& w){
    adj[x][y] = w;
}
bool Graphtest::Dijkstra(const int& x, map<int,double>& dist, map<int,int>& prev){
    if(adj.find(x)==adj.end()) return false;

    auto comp = [&](const int& lhs, const int& rhs)->bool {return dist[lhs]<=dist[rhs];};
    set<int, decltype(comp)> Q(comp);

    // Assign initial distances
    for(auto v : this->adj){
        if(v.first==x){
            dist[v.first] = 0.0;
        }
        else{
            dist[v.first] = numeric_limits<double>::max();
        }
        Q.insert(v.first);
    }

    while(!Q.empty()){
        auto v = *(Q.begin());              // min-distance vertex
        auto nbr = this->get_neighbors(v);  // check all neighbors
        Q.erase(Q.begin());
        for(auto i : nbr){
            int weight = dist[v] + this->get_edge_value(v,i);
            if(weight<dist[i]){
                dist[i] = weight;           // update distance
                prev[i] = v;                // set predecessor
                Q.insert(i);
            }
        }
    }
}

double Graphtest::shortest_distance(const int& x, const int& y){
    if(adj.find(x)==adj.end()||adj.find(y)==adj.end())
        return 0;

    map<int,double> dist;
    map<int,int> prev;
    this->Dijkstra(x,dist,prev);
    if(adj.find(prev[y])==adj.end())
        return 0;
    else
        return dist[y];

}

#endif // GRAPH_H_INCLUDED
