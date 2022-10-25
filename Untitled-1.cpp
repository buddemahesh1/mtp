#include<bits/stdc++.h>
#define int long long
#define F first
#define S second
#define double long double



using namespace std;

using ii = pair<int,int>;


double n,m;
vector<vector<double>> g;
pair<double,double> st,en;
vector<vector<pair<double,double>>> par;


int dx[] = {0,-1,-1,-1,0,1,1,1};
int dy[] = {1,1,0,-1,-1,-1,0,1};


vector<vector<double>> dist;

bool check(int i, int j){
    if(i<0 || i>=n || j<0 || j>=m)return 0;
    return 1;
}


void dijkstra(){
    dist = vector<vector<double>>(n,vector<double>(m,1000000000.1));
    priority_queue<array<double,3>,vector<array<double,3>>,greater<array<double,3>>> pq;
    dist[st.F][st.S] = 0.0;
    pq.push({0.0,st.F,st.S});
    
    while(!pq.empty()){
        auto temp = pq.top();
        pq.pop();
        double i = temp[1],j=temp[2],d = temp[0];
        
        for(int k=0;k<8;k++){
            double x = i+dx[k];
            double y = j+dy[k];
            int t = abs(dx[k])+abs(dy[k]);
            if(check(x,y)){
                if(g[i][j] != 0 && dist[x][y] > d+(((t==2)?1.414:1.0)/(1.0*g[i][j]))){
                    par[x][y] = {i,j};
                    dist[x][y] = d+(((t==2)?1.414:1.0)/(1.0*g[i][j]));
                    pq.push({dist[x][y],x,y});
                }
            }
        }
    }
    
    if(dist[en.F][en.S] >= 1e9){
        cout<<"NOT REACHABLE\n";
        return;
    }
    
    
    for(double i=0;i<n;i++){
        for(double j=0;j<m;j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    pair<double,double> cur = {en.F,en.S};
    vector<pair<double,double>> path;
    
    while(cur.F != st.F || cur.S != st.S){
        path.push_back(cur);
        auto temp = cur;
        cur.F = par[temp.F][temp.S].F;
        cur.S = par[temp.F][temp.S].S;
    }
    path.push_back(cur);
    reverse(path.begin(),path.end());
    
    cout<<dist[en.F][en.S]<<"\n";
    
    for(auto v:path){
        cout<<v.F<<" "<<v.S<<" -> ";
    }
    cout<<endl;
}

void solve(){
    cin>>n>>m;
    g = vector<vector<double>>(n,vector<double>(m));
    par = vector<vector<pair<double,double>>>(n,vector<pair<double,double>>(m));
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>g[i][j];
        }
    }
    
    cin>>st.F>>st.S;
    cin>>en.F>>en.S;
    
    dijkstra();
}


signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
}