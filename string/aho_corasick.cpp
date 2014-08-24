#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef int aho_val_t;

struct AhoCorasick {
    int K; // the number of character
    vector<vector<int> > trie;
    vector<int> fail, value;
    
    int convert(char c) { // implement this function
        return c - 'a';
    }

    AhoCorasick(const vector<pair<string, aho_val_t> >& data, int k) : 
            K(k), trie(1, vector<int>(k, 0)), value(1, 0) { 
        for(auto &s : data) {
            int now = 0;
            for(auto &c : s.first) {
                int &next = trie[now][convert(c)];
                if(!next) {
                    next = trie.size();
                    trie.push_back(vector<int>(K, 0));
                    value.push_back(0);
                }
                now = next;
            }
            value[now] = s.second;
        }

        fail = vector<int>(trie.size(), 0);

        queue<int> Q; Q.push(0);
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = 0; i < K; i ++) {
                if(trie[x][i]){
                    int now = fail[x];
                    int next = trie[x][i];
                    if(x) {
                        while(now && !trie[now][i]) {
                            now = fail[now];
                        }
                        now = trie[now][i];
                    }
                    fail[next] = now;
                    Q.push(next);
                }
            }
        }
    }

    bool match(const string &s) {
        int now = 0;
        for(auto &c : s) {
            while(now && !trie[now][convert(c)]) {
                now = fail[now];
            }
            now = trie[now][convert(c)];
            
            if(value[now]) {
                // matched! you can do something in here. 
                return true;
            }
        }
        return false;
    }
};
