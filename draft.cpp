// #define _GLIBCXX_DEBUG

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<double, double> pdd;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;

int const MAX = 1e5 + 100;
int const MOD = 1e9 + 7;
int const pppower = 179;
int const INFint = 2e9 + 1000;
long long INF = 3e16;

#define int ll
#pragma GCC optimize("-ffast-math")

[[noreturn]] void solve();

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); srand(time(0));
#ifdef STRONG
    //freopen("a.in", "r", stdin);
#endif
    solve();
    return 0;
}
string s;
int brackEnds = 1;
bool ok = true;

bool operation(string now), operand(string now), expression(string now);


bool operation(string& now) {
    return now == "not" | now == "and" | now == "or";
}

bool funcStart(int ind, int oper = -1) {
    if (oper == -1) {
        char n = s[0];
        if (n == 'a' && s[1] == 'n' && s[2] == 'd' && s[3] == '(') {
            bool x = funcStart(ind + 4, 2);
            return x;
        } else if (n == 'n' && s[1] == 'o' && s[2] == 't' && s[3] == '(') {
            bool x = funcStart(ind + 4, 1);
            return x;
        } else if (n == 'o' && s[1] == 'r' && s[2] == '(') {
            bool x = funcStart(ind + 3, 3);
            return x;
        } else {
            cout << "not an operator" << endl;
            ok = false;
        }
    }

    if (!ok) return false;
    bool ret = true;
    if (ind + 4 >= s.size() && brackEnds != 0) {
        cout << "А где буквы" << endl;
        ok = false;
    }

    char n = s[ind];
    if (n != 't' && n != 'f') {
        if (n == 'a' && s[ind + 1] == 'n' && s[ind + 2] == 'd' && s[ind + 3] == '(') {
            bool x = funcStart(ind + 4, 2);
            switch (oper) {
                case 1:
                    return !x;
                default:
                    return x;
            }
        } else if (n == 'n' && s[ind + 1] == 'o' && s[ind + 2] == 't' && s[ind + 3] == '(') {
            bool x = funcStart(ind + 4, 1);
            switch (oper) {
                case 1:
                    return !x;
                default:
                    return x;
            }
        } else if (n == 'o' && s[ind + 1] == 'r' && s[ind + 2] == '(') {
            bool x = funcStart(ind + 3, 3);
            switch (oper) {
                case 1:
                    return !x;
                default:
                    return x;
            }
        } else {
            cout << "not an operator" << endl;
            ok = false;
        }
    }

    if (!ok) return false;
    string snow = "";
    for (int ch = ind; ch < ind + 4; ++ch) {
        snow += s[ch];
    }
    if (snow == "fals") {
        snow += s[ind + 4];
    } else if (snow == "not(") {
        ++brackEnds;
        return ! funcStart(ind + 4, 1);
    }

    if (!ok) return false;
    if (snow != "true" && snow != "false") {
        cout << "not true/false" << endl;
        ok = false;
    }

    if (!ok) return false;
    if (snow == "false") ++ind;
    if (ind + 4 == s.size()) {
        if (brackEnds != 0) {
            cout << "Not enought brackets" << endl;
            ok = false;
        } else {
            return snow == "true";
        }
    }

    if (!ok) return false;
    ret = snow == "true";
    ind += 4;
    n = s[ind];
    if (n == ',') {
        bool x = funcStart(ind + 1, oper);
        switch (oper) {
            case 2:
                return ret & x;
            case 3:
                return ret | x;
        }
    }
    if (!ok) return false;
    if (n == ')') {
        --brackEnds;
        return ret;
    }

    if (!ok) return false;
    ++brackEnds;
    if (n == 'a' && s[ind + 1] == 'n' && s[ind + 2] == 'd' && s[ind + 3] == '(') {
        bool x = funcStart(ind + 4, 2);
        return x & snow == "true";
    } else if (n == 'n' && s[ind + 1] == 'o' && s[ind + 2] == 't' && s[ind + 3] == '(') {
        bool x = funcStart(ind + 4, 1);
        return snow == "true" & (! x);
    } else if (n == 'o' && s[ind + 1] == 'r' && s[ind + 2] == '(') {
        bool x = funcStart(ind + 3, 3);
        return snow == "true" | x;
    } else {
        cout << "not an operator" << endl;
        ok = false;
    }
}

[[noreturn]] void solve() {
    for (;;) {
        getline(cin, s);
        ok = true;
        bool now = funcStart(0);
        if (ok) {
            cout << now << endl;
        }
    }
}