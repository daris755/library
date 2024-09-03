template <typename T>
class SegmentTree {
   private:
    using F = function<T(T, T)>;

    int n;
    vector<T> seg;
    const F f;
    const T e;

   public:
    SegmentTree(int n, const F f, const T& e) : n(n), seg(vector<T>(2 * n, e)), f(f), e(e) {}

    SegmentTree(const vector<T>& v, const F f, const T& e) : n(v.size()), seg(2 * n), f(f), e(e) {
        for (int i = 0; i < n; i++) {
            seg[n + i] = v[i];
        }
        for (int i = n - 1; i >= 1; i--) {
            seg[i] = f(seg[i << 1], seg[i << 1 | 1]);
        }
    }

    T operator[](const int i) const { return seg[i + n]; }

    void update(int i, const T& x) {
        i += n;
        seg[i] = x;
        while (i > 1) {
            i >>= 1;
            seg[i] = f(seg[i << 1], seg[i << 1 | 1]);
        }
    }

    T query(int l, int r) {
        l += n;
        r += n;
        T l_val = e;
        T r_val = e;
        while (l < r) {
            if (l & 1) {
                l_val = f(l_val, seg[l]);
                l++;
            }
            if (r & 1) {
                r--;
                r_val = f(seg[r], r_val);
            }
            l >>= 1;
            r >>= 1;
        }
        return f(l_val, r_val);
    }

    template <class S>
    int max_right(int l, S check) const { // max(r) s.t. check(query(l, r)) == true
        assert(0 <= l && l <= n);
        int r = l;
        l += n;
        int w = 1;
        T l_val = e;
        for (; r + w <= n; l >>= 1, w <<= 1) {
            if (l & 1) {
                if (check(f(l_val, seg[l]))) {
                    l_val = f(l_val, seg[l]);
                    r += w;
                    l++;
                } else {
                    break;
                }
            }
        }
        for (; w > 0; l <<= 1, w >>= 1) {
            if (r + w <= n && check(f(l_val, seg[l]))) {
                l_val = f(l_val, seg[l]);
                r += w;
                l++;
            }
        }
        return r;
    }

    template <class S>
    int min_left(int r, S check) const { // min(l) s.t. check(query(l, r)) == true
        assert(0 <= r && r <= n);
        int l = r;
        r += n;
        int w = 1;
        T r_val = e;
        for (; l - w >= 0; r >>= 1, w <<= 1) {
            if (r & 1) {
                if (check(f(seg[r - 1], r_val))) {
                    r_val = f(seg[r - 1], r_val);
                    l -= w;
                    r--;
                } else {
                    break;
                }
            }
        }
        for (; w > 0; r <<= 1, w >>= 1) {
            if (l - w >= 0 && check(f(seg[r - 1], r_val))) {
                r_val = f(seg[r - 1], r_val);
                l -= w;
                r--;
            }
        }
        return l;
    }
};