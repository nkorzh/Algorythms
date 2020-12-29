/* Hamiltonian path in oriented graph */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

const ll M = 5e3 + 100;

#define pb push_back

vector<int> hamPath, hamCycle;
set<int> unused;
bool g[M][M];
vector<bool> used;
int n;

struct lamp {
    set<int> less, more;
};

vector<lamp> lamps;

vector<int> concat(vector<int> a, int b, vector<int> c) {
    vector<int> res;
    for (const auto &it : a) {
        res.pb(it);
    }
    res.pb(b);
    for (const auto &it : c) {
        res.pb(it);
    }

    return res;
}

string isMore(int a, int b) {
    return g[a][b] ? "YES" : "NO";
}

void print(set<int> s) {
    cout << "s: " << endl;
    for (const auto &it : s) {
        cout << it << " ";
    }
    cout << endl;
}

vector<int> split(set<int> s) {
    string answer;

    if (s.empty()) {
        return vector<int>();
    }


    auto it = s.begin();
    int v = *it;
    s.erase(it);

    if (s.empty()) {
        vector<int> res;
        res.pb(v);
        return res;
    }

    if (s.size() == 1) {
        answer = isMore(*s.begin(), v);

        vector<int> res;
        if (answer == "YES") {
            res.pb(*s.begin());
            res.pb(v);
        } else {
            res.pb(v);
            res.pb(*s.begin());
        }
        return res;
    }

    for (const auto &it : s) {
        answer = isMore(it, v);
        if (answer == "YES") {
            lamps[v].less.insert(it);
        } else {
            lamps[v].more.insert(it);
        }
    }

    return concat(split(lamps[v].less), v, split(lamps[v].more));
}

void dfs(int v) {
    used[v] = true;

    for (int i = 0; i < n; i++) {
        if (g[v][i] && !used[i]) {
            dfs(i);
        }
    }

    hamCycle.pb(v);
}

void createCycle() {
    for (int i = 0; i < hamPath.size(); i++) {
        hamCycle.clear();
        used.clear();
        used.resize(n, false);
        dfs(i);
        if (g[hamCycle.front()][hamCycle.back()]) {
            reverse(hamCycle.begin(), hamCycle.end());
            break;
        }
    }
}

int main() {
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);

    cin >> n;
    string s;
    getline(cin, s);

    for (int i = 2; i <= n; ++i) {
        v.push_back(i);
        g[i].resize(n + 1, false);
        cin >> input;
        for (int j = 1; j < i; ++j)
            if (IS_EDGE(input[j - 1])) g[j][i] = g[i][j] = 1;
    }

//    for (int i = 0; i < n; i++) {
//        string s;
//        getline(cin, s);
//        g[i][i] = 0;
//        for (int j = 0; j < s.size(); j++) {
//            g[i][j] = (s[j] == '1');
//            g[j][i] = (s[j] == '0');
//        }
//    }

    lamps.resize(n);

    int start = 0;
    string answer;
    for (int i = 1; i < n; i++) {
        if (i == start) continue;
        answer = isMore(i, start);


        if (answer == "YES") {
            lamps[start].less.insert(i);
        } else {
            lamps[start].more.insert(i);
        }
    }

    hamPath = concat(split(lamps[start].less), start, split(lamps[start].more));

    createCycle();

    for (const auto &it : hamCycle) {
        cout << it + 1 << " ";
    }

    fclose(stdin);
    fclose(stdout);
}