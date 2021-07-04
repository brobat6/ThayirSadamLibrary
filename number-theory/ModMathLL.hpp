#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull  = unsigned long long;

// Source: KACTL
// Tested On:
// Perform opertations modulo a 64 bit integer

// Modulo operations when modulo is up to 1e18
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}
