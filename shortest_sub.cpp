//
//  main.cpp
//  shortestpath
//
//  Created by Jun Seub Lim on 24/11/2019.
//  Copyright © 2019 Jun Seub Lim. All rights reserved.
//
#include <iostream>
#include <vector>

using namespace std;

int V, E;

vector<vector<int>> graph;

vector<int> dijkstra(int total)
{
    vector<int> visited,d;

    visited.assign(V,false);
    d.assign(V,total+1);
    d[0] = 0;

    while(true)
    {
        int m = total+1, N=-1;
        for(int j=0;j<V; j++)
        {
            if(!visited[j] && (m>d[j]))
            {
                m = d[j];
                N = j;
            }
        }
        if(m == total+1)
            break;
        visited[N] = true;
        for(int j=0;j<V;j++)
        {
            if(visited[j] || graph[N][j] == 0) continue;
            int via = d[N] + graph[N][j];

            if(d[j] > via){
                d[j] = via;
            }
        }
    }
    return d;
}
int main()
{
    while(true)  {
        cin>>V>>E;
        int total =0;
        bool wronginput = false;
        if (cin.fail()) break;
        graph.assign(V, vector<int>(V,0));
        while(E--)
        {
            int u,v,w;

            cin>>u>>v>>w;
            if (cin.fail()) {
                wronginput = true;
                break;
            }
            graph[u-1][v-1] = w;
            graph[v-1][u-1] = w;
            total += w;
        }
        if (wronginput) break;
        vector<int> d = dijkstra(total);
        cout<<d[V-1]<<endl;
    }
    return 0;
}
