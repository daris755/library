template <typename T>
struct BinaryIndexedTree {
    // https://scrapbox.io/pocala-kyopro/BIT

    int n;
    vector<T> bit;

    BinaryIndexedTree(int n) : n(n), bit(n + 1) {}

    // 一点更新
    void add(int k, T v) {
        // i & -i で立っている最下位ビットを取りだす
        for (int i = k; i <= n; i += i & -i) bit[i] += v;
    }

    // １～ｎまでの和を求める
    ll sum(int k) {
        ll res = 0;
        for (int i = k; 0 < i; i -= i & -i) res += bit[i];
        return res;
    }
    
    // 転倒数
    // v:0-based index -> origin=1(BITは1-based indexで管理)
    template<typename S>
    ll inversion (vector<S>& v, S origin = 0) {
        int vsz = v.size();
        ll ret = 0;
        for (int i = 0; i < vsz; i++) {
            v[i] += origin;
            ret += i - sum(v[i]); // BITの総和 - 自分より左 = 自分より右側
            add(v[i], 1); // 自分の位置に1を足す
        }
        return ret;
    }
};

template <class T>
using BIT = BinaryIndexedTree<T>;