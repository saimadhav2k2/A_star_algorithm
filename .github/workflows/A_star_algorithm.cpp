#include<bits/stdc++.h>
#define ll long long int
#define ld long double
#define mod 1000000007 
#define N 100010
using namespace std;
int n,m;
//A* Algorithm code
struct cell{
    
    double f,g,h;
    int parent_x,parent_y;
    
};

bool isvalid(int x,int y){
    return (x>=0 )&& (y>=0) && (x<n) &&( y<m);
}

bool isUnblocked(int x,int y,vector<vector<int>> &grid){
    return grid[x][y]==1;    
}

bool isDest(int i,int j,int x,int y){
    return i==x && j==y;
}

double calculate_H_distance(int x,int y,int dest_x,int dest_y){
    
    return (double)sqrt(pow(x-dest_x,2)+sqrt(pow(y-dest_y,2)));
}

void trace(int dest_x,int dest_y,vector<vector<cell>> &details){
    
    stack<pair<int,int>> st;
    
    st.push({dest_x,dest_y});
    
    printf("The path is");
    while(!st.empty()){
        auto top=st.top();
        st.pop();
        
        int i=top.first;
        int j=top.second;
        printf("->(%d,%d)",i,j);
        if(details[i][j].parent_x==i && details[i][j].parent_y==j)return;
        
        st.push({details[i][j].parent_x,details[i][j].parent_y});
    }
}

void A_Star(int x,int y,int dest_x,int dest_y,vector<vector<int>> &grid){
    
    if(!isvalid(x,y)){
        printf("1 invalid coordinates\n");
        return;
    }
    
    if(!isvalid(dest_x,dest_y)){
        printf("2 invalid coordinates\n");
        return;
    }
    
    if(!isUnblocked(x,y,grid) || !isUnblocked(dest_x,dest_y,grid)){
        printf("source or destination is unblocked\n");
        return;
    }
    
    if(isDest(x,y,dest_x,dest_y)){
        cout<<"Already at the destination\n";
        return;
    }
    
    set<pair<double,pair<int,int>>> openList;
    bool closedList[n][m];
    memset(closedList,false,sizeof closedList);
    
    vector<vector<cell>> details(n,vector<cell>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            details[i][j].f=FLT_MAX;
            details[i][j].g=FLT_MAX;
            details[i][j].h=FLT_MAX;
            details[i][j].parent_x=-1;
            details[i][j].parent_y=-1;
        }
    }
    
    int i,j;
    i=x,j=y;
    details[i][j].f=0.0;
    details[i][j].g=0.0;
    details[i][j].h=0.0;
    details[i][j].parent_x=x;
    details[i][j].parent_y=y;
    
    openList.insert({0.0,{x,y}});
    
    while(!openList.empty()){
        
        auto top=*openList.begin();
        openList.erase(openList.begin());
        
        int x1=top.second.first;
        int y1=top.second.second;
        //we can travel in 8 directions
        closedList[x1][y1]=true;
        //1
        if(isvalid(x1+1,y1) && isUnblocked(x1+1,y1,grid)){

            if(isDest(x1+1,y1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1+1][y1].parent_x=x1;
                details[x1+1][y1].parent_y=y1;
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1+1][y1]==false){
                    
                double h_new=calculate_H_distance(x1+1,y1,dest_x,dest_y);
                double g_new=details[x1+1][y1].g+1.0;
                double f_new=h_new+g_new;
                
                if(details[x1+1][y1].f==FLT_MAX||details[x1+1][y1].f>f_new){
                    details[x1+1][y1].parent_x=x1;
                    details[x1+1][y1].parent_y=y1;
                    details[x1+1][y1].f=f_new;
                    details[x1+1][y1].g=g_new;
                    details[x1+1][y1].h=h_new;
                    openList.insert({f_new,{x1+1,y1}});
                }
            }
        }
        
        //2
        if(isvalid(x1-1,y1) && isUnblocked(x1-1,y1,grid)){

            // cout<<closedList[x1-1][y1]<<endl;
            if(isDest(x1-1,y1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1-1][y1].parent_x=x1;
                details[x1-1][y1].parent_y=y1;
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1-1][y1]==false){
                // cout<<23<<endl;
                double h_new=calculate_H_distance(x1-1,y1,dest_x,dest_y);
                double g_new=details[x1-1][y1].g+1.0;
                double f_new=h_new+g_new;
                
                if(details[x1-1][y1].f==FLT_MAX||details[x1-1][y1].f>f_new){
                    // cout<<24<<endl;
                    details[x1-1][y1].parent_x=x1;
                    details[x1-1][y1].parent_y=y1;
                    details[x1-1][y1].f=f_new;
                    details[x1-1][y1].g=g_new;
                    details[x1-1][y1].h=h_new;
                    openList.insert({f_new,{x1-1,y1}});
                }
            }
        }
        //3        
        if(isvalid(x1,y1-1) && isUnblocked(x1,y1-1,grid)){

            if(isDest(x1,y1-1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1][y1-1].parent_x=x1;
                details[x1][y1-1].parent_y=y1;
                //trace()
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1][y1-1]==false){
                
                double h_new=calculate_H_distance(x1,y1-1,dest_x,dest_y);
                double g_new=details[x1][y1-1].g+1.0;
                double f_new=h_new+g_new;
                
                if(details[x1][y1-1].f==FLT_MAX||details[x1][y1-1].f>f_new){
                    details[x1][y1-1].parent_x=x1;
                    details[x1][y1-1].parent_y=y1;
                    details[x1][y1-1].f=f_new;
                    details[x1][y1-1].g=g_new;
                    details[x1][y1-1].h=h_new;
                    openList.insert({f_new,{x1,y1-1}});
                }
            }
        }
        
        //4
        if(isvalid(x1,y1+1) && isUnblocked(x1,y1+1,grid)){

            if(isDest(x1,y1+1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1][y1+1].parent_x=x1;
                details[x1][y1+1].parent_y=y1;
                // trace()
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1][y1+1]==false){
                
                double h_new=calculate_H_distance(x1,y1+1,dest_x,dest_y);
                double g_new=details[x1][y1+1].g+1.0;
                double f_new=h_new+g_new;
                
                if(details[x1][y1+1].f==FLT_MAX||details[x1][y1+1].f>f_new){
                    details[x1][y1+1].parent_x=x1;
                    details[x1][y1+1].parent_y=y1;
                    details[x1][y1+1].f=f_new;
                    details[x1][y1+1].g=g_new;
                    details[x1][y1+1].h=h_new;
                    openList.insert({f_new,{x1,y1+1}});
                }
            }
        }
        //5
        if(isvalid(x1+1,y1+1) && isUnblocked(x1+1,y1+1,grid)){

            if(isDest(x1+1,y1+1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1+1][y1+1].parent_x=x1;
                details[x1+1][y1+1].parent_y=y1;
                // trace();
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1+1][y1+1]==false){
                
                double h_new=calculate_H_distance(x1+1,y1+1,dest_x,dest_y);
                double g_new=details[x1+1][y1+1].g+1.414;
                double f_new=h_new+g_new;
                
                if(details[x1+1][y1+1].f==FLT_MAX||details[x1+1][y1+1].f>f_new){
                    details[x1+1][y1+1].parent_x=x1;
                    details[x1+1][y1+1].parent_y=y1;
                    details[x1+1][y1+1].f=f_new;
                    details[x1+1][y1+1].g=g_new;
                    details[x1+1][y1+1].h=h_new;
                    openList.insert({f_new,{x1+1,y1+1}});
                }
            }
        }
        //6
        if(isvalid(x1+1,y1-1) && isUnblocked(x1+1,y1-1,grid)){

            if(isDest(x1+1,y1-1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1+1][y1-1].parent_x=x1;
                details[x1+1][y1-1].parent_y=y1;
                // trace()
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1+1][y1-1]==false){
                
                double h_new=calculate_H_distance(x1+1,y1-1,dest_x,dest_y);
                double g_new=details[x1+1][y1-1].g+1.414;
                double f_new=h_new+g_new;
                
                if(details[x1+1][y1-1].f==FLT_MAX||details[x1+1][y1-1].f>f_new){
                    details[x1+1][y1-1].parent_x=x1;
                    details[x1+1][y1-1].parent_y=y1;
                    details[x1+1][y1-1].f=f_new;
                    details[x1+1][y1-1].g=g_new;
                    details[x1+1][y1-1].h=h_new;
                    openList.insert({f_new,{x1+1,y1-1}});
                }
            }
        }

        if(isvalid(x1-1,y1-1) && isUnblocked(x1-1,y1-1,grid)){

            if(isDest(x1-1,y1-1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1-1][y1-1].parent_x=x1;
                details[x1-1][y1-1].parent_y=y1;
                // trace()
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1-1][y1-1]==false){
                
                double h_new=calculate_H_distance(x1-1,y1-1,dest_x,dest_y);
                double g_new=details[x1-1][y1-1].g+1.414;
                double f_new=h_new+g_new;
                
                if(details[x1-1][y1-1].f==FLT_MAX||details[x1-1][y1-1].f>f_new){
                    details[x1-1][y1-1].parent_x=x1;
                    details[x1-1][y1-1].parent_y=y1;
                    details[x1-1][y1-1].f=f_new;
                    details[x1-1][y1-1].g=g_new;
                    details[x1-1][y1-1].h=h_new;
                    openList.insert({f_new,{x1-1,y1-1}});
                }
            }
        }
        //8
        if(isvalid(x1-1,y1+1) && isUnblocked(x1-1,y1+1,grid)){

            if(isDest(x1-1,y1+1,dest_x,dest_y)){
                printf("Destination Reached\n");
                details[x1-1][y1+1].parent_x=x1;
                details[x1-1][y1+1].parent_y=y1;
                // trace()
                trace(dest_x,dest_y,details);
                return;
            }
            else if(closedList[x1-1][y1+1]==false){
                
                double h_new=calculate_H_distance(x1-1,y1+1,dest_x,dest_y);
                double g_new=details[x1-1][y1+1].g+1.414;
                double f_new=h_new+g_new;
                
                if(details[x1-1][y1+1].f==FLT_MAX||details[x1-1][y1+1].f>f_new){
                    details[x1-1][y1+1].parent_x=x1;
                    details[x1-1][y1+1].parent_y=y1;
                    details[x1-1][y1+1].f=f_new;
                    details[x1-1][y1+1].g=g_new;
                    details[x1-1][y1+1].h=h_new;
                    openList.insert({f_new,{x1-1,y1+1}});
                }
            }
        }
    }
    
        printf("Destination not found\n");
}
void solve(){
    // int n,m;
    n=9,m=10;
    vector<vector<int>> grid={ { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
    
    A_Star(8,0,0,0,grid);
}
 
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    ll t=1;
    // cin>>1;
    while(t--){
        // cout<<setprecision(12)<<fixed;
        solve();
    }
}