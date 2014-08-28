#include <vector>
#include <algorithm>

using namespace std;

typedef int val_t;

struct MaximumFlow {
    int size;

    vector<val_t> visit;
    vector< pair<int, int> > path;
    vector< vector< pair<int, val_t> > > edge;

    MaximumFlow() {}

    void init() {
        size = 0;
        visit.clear();
        path.clear();
        edge.clear();
    }
    
    int newVertex() {
        edge.push_back( vector< pair<int, val_t> >(0) );
        visit.push_back( 0 );
        return size ++;
    }
    void makeEdge( int s, int e, val_t v ) {
        edge[ s ].emplace_back( e, v );
    }
    
    val_t dfs( int now, int sink, val_t value, val_t chkv ) {
        if( visit[ now ] == chkv || value == 0 ) {
            return 0;
        }
        if( now == sink ) {
            for( auto &v : path ) {
                edge[ v.first ][ v.second ].second -= value;
                edge[ edge[ v.first ][ v.second ].first ].emplace_back( v.first, value );
            }
            return value;
        }
        visit[ now ] = chkv;

        for( int i = 0; i < (int)edge[ now ].size(); i ++ ) {
            auto &v = edge[ now ][ i ];

            path.emplace_back( now, i );
            if( val_t rr = dfs( v.first, sink, min( value, v.second ), chkv ) ) {
                return rr;
            }
            path.pop_back();
        }

        return 0;
    }

    val_t getflow( int source, int sink ) {
        val_t rr = 0;

        while( true ) {
            path.clear();
            val_t now = dfs( source, sink, 2147483647, rr + 1 );
            if( now == 0 ) {
                break;
            }
            rr += now;
        }
        
        return rr;
    }
};


