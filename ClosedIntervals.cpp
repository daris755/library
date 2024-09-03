struct ClosedIntervals {
    // https://rsk0315.hatenablog.com/entry/2020/10/11/125049

    // private:
    //  整数の集合を閉区間で管理
    set<pair<ll, ll>> s;

    // public:
    //  番兵
    ClosedIntervals() {
        s.emplace(infl, infl);
        s.emplace(-infl, -infl);
    }

    // x が集合に含まれるか
    bool contains(ll x) const {
        // x が含まれる区間があれば、それは辞書順で make_pair(x + 1, x + 1) 未満で最大の区間
        // make_pair(0, 0) を追加して make_pair(0, 0) を二分探索すればわかる
        auto [l, u] = *prev(s.lower_bound(make_pair(x + 1, x + 1)));
        return l <= x && x <= u;
    }

    // { ..., [l, u], [x, x], [nl, nu], ... }
    bool insert(ll x) {
        auto nit = s.lower_bound(make_pair(x + 1, x + 1));
        auto it = prev(nit);
        auto [l, u] = *it;
        auto [nl, nu] = *nit;
        // l <= x <= u なら { [l, u], [x, x], [nl, nu] } = { [l, u], [nl, nu] }
        if (l <= x && x <= u) return false;
        if (u == x - 1) {
            // { [l, u], [x, x], [nl, nu] } = { [l, nu] }
            if (nl == x + 1) {
                s.erase(it);
                s.erase(nit);
                s.emplace(l, nu);
            }
            // { [l, u], [x, x], [nl, nu] } = { [l, x], [nl, nu] }
            else {
                s.erase(it);
                s.emplace(l, x);
            }
        } else {
            // { [l, u], [x, x], [nl, nu] } = { [l, u], [x, nu] }
            if (nl == x + 1) {
                s.erase(nit);
                s.emplace(x, nu);
            }
            // { [l, u], [x, x], [nl, nu] } = { [l, u], [x, x], [nl, nu] }
            else
                s.emplace(x, x);
        }
        return true;
    }

    // { ..., [l, u], ... }
    void erase(ll x) {
        auto it = prev(s.lower_bound(make_pair(x + 1, x + 1)));
        auto [l, u] = *it;
        // l <= x <= u でないなら警告
        // 警告文を消すと何もせずに終了
        if (!(l <= x && x <= u)) {
            // cout << "not erase" << '\n';
            return;
        }
        // { [l = x, u = x] } = {}
        else if (l == x && u == x) {
            s.erase(it);
        }
        // { [l < x, u = x] } = { [l, x - 1] }
        else if (l < x && u == x) {
            s.erase(it);
            s.emplace(l, x - 1);
        }
        // { [l = x, u > x] } = { [l + 1, u] }
        else if (l == x && u > x) {
            s.erase(it);
            s.emplace(l + 1, u);
        }
        // { [l < x, u > x] } = { [l, x - 1], [x + 1, u] }
        else if (l < x && u > x) {
            s.erase(it);
            s.emplace(l, x - 1);
            s.emplace(x + 1, u);
        }
        return;
    }

    // mex は s （集合）に含まれない最小の（０を含む）自然数
    ll mex(ll x = 0) const {
        // 0 が集合に含まれているか判定すればよい
        auto [l, u] = *prev(s.lower_bound(make_pair(x + 1, x + 1)));
        return l <= x && x <= u ? u + 1 : x;
    }
};