#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<long long, long long> Point;

long long ccw( Point a, Point b, Point c ) {
    a.first -= c.first; b.first -= c.first;
    a.second -= c.second; b.second -= c.second;

    return a.first * (long long)b.second - a.second * (long long) b.first;
}

vector<Point> ConvexHull( vector<Point> data ) {
    vector<Point> upper, lower;
    sort( data.begin(), data.end() );

    for( auto &v : data ) {
        while( upper.size() >= 2 && ccw( *next(upper.rbegin()), upper.back(), v) >= 0 ) upper.pop_back();
        while( lower.size() >= 2 && ccw( *next(lower.rbegin()), lower.back(), v) <= 0 ) lower.pop_back();

        upper.push_back( v );
        lower.push_back( v );
    }

    upper.insert( upper.end(), next(lower.rbegin()), prev(lower.rend()) );
    return upper;
}

int main() {
    int N;
    cin >> N;

    vector<Point> data(N);
    for( int i = 0; i < N; i ++ ) {
        cin >> data[i].first >> data[i].second;
    }

    vector<Point> convex = ConvexHull( data );
    return 0;
}
