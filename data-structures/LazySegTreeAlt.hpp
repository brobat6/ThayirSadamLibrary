#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

// Source: Me
// Tested on: ???
// More general segtree. Remember to set identities.
struct LazySegTree {
  struct F { // Lazy update
    ll inc = 0;
    F() {} // identity
    F(int x) : inc(x) {}
    F& operator *= (const F& a) { // Compose a onto this (a is new)
      inc += a.inc;
      return *this;
    }
  };
  struct T { // Segtree data
    ll sz = 1, sum = 0;
    T() {} // identity
    T(int x) : sum(x) {}
    friend T operator+(const T& a, const T& b) { // Combine two data
      T res;
      res.sz = a.sz + b.sz;
      res.sum = a.sum + b.sum;
      return res;
    }
    T& operator*=(const F& a) { // Apply lazy onto data
      sum += sz*a.inc;
      return *this;
    }
  };
  int n;
  vector<T> t;
  vector<F> lz;

  LazySegTree() {}
  LazySegTree(vector<T>& v) {
    n = 1;
    while(n < v.size()) n *= 2;
    t.resize(2*n);
    lz.resize(2*n);
    for (int i = 0; i < v.size(); i++) t[n+i] = v[i];
    for (int i = n-1; i >= 1; i--) pull(i);
  }
  
  void push(int node) {
    t[node] *= lz[node];
    if (node < n) {
      lz[2*node] *= lz[node];
      lz[2*node+1] *= lz[node];
    }
    lz[node] = F();
  }
  void pull(int node) {
    t[node] = t[2*node] + t[2*node+1];
  }
  T query(int l, int r) {
    return query(l,r,1,0,n-1);
  }
  T query(int l, int r, int node, int tl, int tr) {
    push(node);
    if (tr < l || tl > r) return T();
    if (l <= tl && tr <= r) return t[node];
    int tm = (tl+tr)/2;
    return query(l,r,2*node,tl,tm) + query(l,r,2*node+1,tm+1,tr);
  }
  void apply(int l, int r, F val) {
    apply(l,r,val,1,0,n-1);
  }
  void apply(int l, int r, F val, int node, int tl, int tr) {
    push(node);
    if (tr < l || tl > r) return;
    if (l <= tl && tr <= r) {
      lz[node] = val;
      push(node);
      return;
    }
    int tm = (tl+tr)/2;
    apply(l,r,val,2*node,tl,tm);
    apply(l,r,val,2*node+1,tm+1,tr);
    pull(node);
  }
};
