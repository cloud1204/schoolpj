#include <bits/stdc++.h>
#define ll long long
#define double long double
#define fi first
#define se second
using namespace std;
void db() {cout << '\n';}
template <typename T, typename ...U> void db(T a, U ...b) {cout << a << ' ', db(b...);}
#ifdef Cloud
#define file freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#else
#define file ios::sync_with_stdio(false); cin.tie(0)
#endif
const int N = 2e5 + 1, inf = 1e9, mod = 998244353;
auto SEED = chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(SEED);
double pi = 3.1415926535897932384626433832;
int rand(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}
double calculate_angle(double a, double b, double c){
    double tmp = (b * b + c * c - a * a) / (2 * b * c);
    return acos(tmp);
}
double calculate_edge(double a, double b, double theta){
    return sqrt(a * a + b * b - 2 * a * b * cos(theta));
}
struct qua {
    int t;
    double edge[4] = {1, 1, 1, 1}, angle[4] = {pi / 2, pi / 2, pi / 2, pi / 2};
    vector<pair<int, int>> history;
    bool cut(int tar, int dir, double _area){ // target angle 0, 1, 2, 3; back 0 front 1
        if (dir == 0){
            double &side = edge[tar];
            double &theta = angle[(tar + 3) % 4];
            double cutlen = 2 * _area / (side * sin(theta));
            double newside = calculate_edge(side, cutlen, theta);
            if (cutlen > edge[(tar + 3) % 4]) return false;
            angle[tar] -= calculate_angle(cutlen, side, newside);
            side = newside;
            edge[(tar + 3) % 4] -= cutlen;
            theta = 2 * pi - angle[tar] - angle[(tar + 1) % 4] - angle[(tar + 2) % 4];
        }
        else{
            double &side = edge[(tar + 1) % 4];
            double &theta = angle[(tar + 1) % 4];
            double cutlen = 2 * _area / (side * sin(theta));
            double newside = calculate_edge(side, cutlen, theta);
            if (cutlen > edge[(tar + 2) % 4]) return false;
            angle[tar] -= calculate_angle(cutlen, side, newside);
            side = newside;
            edge[(tar + 2) % 4] -= cutlen;
            theta = 2 * pi - angle[tar] - angle[(tar + 2) % 4] - angle[(tar + 3) % 4];
        }
        history.push_back({tar, dir});
        assert(min({angle[0], angle[1], angle[2], angle[3]}) > 0);
        assert(min({edge[0], edge[1], edge[2], edge[3]}) > 0);
        t--;
        return 1;
    }
    double area(int tar){
        return edge[tar] * edge[(tar + 1) % 4] * sin(angle[tar]) / 2;
    }
    double split(){
        double a = area(0), b = area(1), c = area(2), d = area(3);
        if (t % 2 == 0) return min(abs(a - c), abs(b - d)) * 2 / t;
        else{
            if (a < c) swap(a, c);
            if (b < d) swap(b, d);
            return min(abs(a / (t + 1 >> 1) - c / (t >> 1)), abs(b / (t + 1 >> 1) - c / (t >> 1)));
        }
    }
    void print(){
        for (auto i : history) db(i.fi, i.se);
        /*
        for (double i : edge) cout << i << ' ';
        for (double i : angle) cout << i << ' ';
        cout << '\n';
        */
    }
    qua (int _t) : t(_t){}
};
double randcut(int n){
    qua cur(n), best = cur;
    double piece = 1.0 / n;
    for (int i = 0; i < n - 2; i++){
        while (1){
            bool success = cur.cut(rand(0, 3), rand(0, 1), piece);
            if (success) break;
        }
        if (cur.split() < best.split()) best = cur;
    }
    return best.split();
}
void find_bestcut(int n){
    qua best(n);
    for (int msk = 0; msk < 1 << (n - 2) * 3; msk++){
        qua cur(n);
        double piece = 1.0 / n;
        bool bad = 0;
        for (int i = 0, j = msk; i < n - 2; i++, j >>= 3){
            int tar = j % 4;
            bool dir = j & 4;
            bool success = cur.cut(tar, dir, piece);
            if (!success) {
                bad = 1;
                break;
            }
            //if (cur.split() < best.split()) best = cur;
        }
        if (bad) continue;
        if (cur.split() < best.split()) best = cur;
    }

    db("n =", n, "best:", best.split());
    db("cuts:");
    best.print();
}
signed main(){
    file;
    cout << fixed << setprecision(10);
    int n;
    cin >> n;
    find_bestcut(n);
}