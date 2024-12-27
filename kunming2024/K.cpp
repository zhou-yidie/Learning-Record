#include <bits/stdc++.h>


using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")


#ifndef _MBTI_CONVERTER_HPP
#define _MBTI_CONVERTER_HPP

#include <cstdint>
#include <array>
#include <random>

class MbtiConverter;

using MbtiTranformer = uint32_t (MbtiConverter::*)(uint32_t);

static constexpr int TRANSFORMER_NUM = 19;

class MbtiConverter{
 public:
  // private:
    static const uint32_t __p[16];
    static const uint32_t __rotr1[8];
    static const MbtiTranformer __transformers[TRANSFORMER_NUM];

    static uint32_t __arrToVal(std::array<uint32_t,8> arr){
        uint32_t val = 0;
        for(int i=0;i<8;i++){
            val |= arr[i] << (4*i);
        }
        return val;
    }

    static std::array<uint32_t,8> __valToArr(uint32_t val){
        std::array<uint32_t,8> arr;
        for(int i=0;i<8;i++){
            arr[i] = val & 0xf;
            val >>= 4;
        }
        return arr;
    }

    uint32_t k;

    uint32_t __xor(uint32_t in){
        return in ^ k;
    }

    uint32_t __perm(uint32_t in){
        uint32_t out = 0;
        out |= __p[(in >> 0) & 0xf] << 0;
        out |= __p[(in >> 4) & 0xf] << 4;
        out |= __p[(in >> 8) & 0xf] << 8;
        out |= __p[(in >> 12) & 0xf] << 12;
        out |= __p[(in >> 16) & 0xf] << 16;
        out |= __p[(in >> 20) & 0xf] << 20;
        out |= __p[(in >> 24) & 0xf] << 24;
        out |= __p[(in >> 28) & 0xf] << 28;
        return out;
    }

    uint32_t __mix(uint32_t in_arg){
        uint32_t in[8], t[8];
        for(int i=0;i<8;i++){
            in[i] = in_arg & 0xf;
            in_arg >>= 4;
            if(in[i] & 0x8){
                t[i] = (in[i] << 1) ^ 0x13;
            }else{
                t[i] = in[i] << 1;
            }
        }
        uint32_t out = 0;
        for(int i=0;i<8;i++){
            out |= ((in[__rotr1[i]])^(t[__rotr1[i]^1])) << (4*i);
        }
        return out;
    }

  public:
    MbtiConverter(){
        this->setRandomKey();
    }
    MbtiConverter(uint32_t k){
        this->setKey(k);
    }

    void setRandomKey(){
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);
        this->k = dist(gen);
    }

    void setKey(uint32_t k){
        this->k = k;
    }

    bool check(uint32_t k){
        return this->k == k;
    }

    uint32_t run(uint32_t in){
        for(auto structure:__transformers){
            in = (this->*structure)(in);
        }
        return in;
    }

    std::array<uint32_t,8> run(std::array<uint32_t,8> in){
        return __valToArr(run(__arrToVal(in)));
    }

    uint32_t runBetween(uint32_t in, int start, int end){
        for(int i = start; i < end; ++i){
            in = (this->*__transformers[i])(in);
        }
        return in;
    }

    std::array<uint32_t,8> runBetween(std::array<uint32_t,8> in, int start, int end){
        return __valToArr(runBetween(__arrToVal(in), start, end));
    }

    uint32_t runFrom(uint32_t in, int start){
        return runBetween(in, start, TRANSFORMER_NUM);
    }

    std::array<uint32_t,8> runFrom(std::array<uint32_t,8> in, int start){
        return __valToArr(runFrom(__arrToVal(in), start));
    }

    uint32_t runUntil(uint32_t in, int end){
        return runBetween(in, 0, end);
    }

    std::array<uint32_t,8> runUntil(std::array<uint32_t,8> in, int end){
        return __valToArr(runUntil(__arrToVal(in), end));
    }
};


const uint32_t MbtiConverter::__p[16] = {0x7,0x0,0x5,0x6,0xb,0xf,0x4,0x3,0x1,0xd,0xc,0xe,0x8,0x9,0xa,0x2};
const uint32_t MbtiConverter::__rotr1[8] = {0x0,0x4,0x1,0x5,0x2,0x6,0x3,0x7};
const MbtiTranformer MbtiConverter::__transformers[TRANSFORMER_NUM] = {
    &MbtiConverter::__xor,
    &MbtiConverter::__perm,
    &MbtiConverter::__mix,
    &MbtiConverter::__xor,
    &MbtiConverter::__perm,
    &MbtiConverter::__mix,
    &MbtiConverter::__xor,
    &MbtiConverter::__perm,
    &MbtiConverter::__mix,
    &MbtiConverter::__xor,
    &MbtiConverter::__perm,
    &MbtiConverter::__mix,
    &MbtiConverter::__xor,
    &MbtiConverter::__perm,
    &MbtiConverter::__mix,
    &MbtiConverter::__xor,
    &MbtiConverter::__perm,
    &MbtiConverter::__mix,
    &MbtiConverter::__xor
};

#endif


void exper() {
  MbtiConverter mc(998244353);
  mt19937_64 rng(58);
  for (int n = 1; n <= 6; ++n) {
    const unsigned base = rng();
    for (int i0 = 0; i0 < 8; ++i0) for (int i1 = i0 + 1; i1 < 8; ++i1) {
      int freq[8][16] = {};
      for (unsigned a0 = 0; a0 < 16; ++a0) for (unsigned a1 = 0; a1 < 16; ++a1) {
        const unsigned y = mc.runBetween(base ^ a0 << (i0*4) ^ a1 << (i1*4), 0, n * 3);
        for (int i = 0; i < 8; ++i) ++freq[i][y >> (i*4) & 15];
      }
      for (int i = 0; i < 8; ++i) {
        if (count(freq[i], freq[i] + 16, 16) == 16) {
          cerr << "n = " << n << "; " << i0 << "," << i1 << " -> " << i << ": ";
          pv(freq[i], freq[i] + 16);
        }
        // n = 4; {0,1}, {2,3}, {4,5}, {6,7}
      }
    }
  }
}

unsigned invP[16];
unsigned invPerm(unsigned y) {
  unsigned x = 0;
  for (int i = 0; i < 8; ++i) x |= invP[y >> (i*4) & 15] << (i*4);
  return x;
}

unsigned MOD[32];
pair<unsigned, unsigned> UNMIX[16][16];
unsigned invMix(unsigned y) {
  constexpr int ROT[8] = {0, 2, 4, 6, 1, 3, 5, 7};
  unsigned x = 0;
  for (int i = 0; i < 8; i += 2) {
    const unsigned a = y >> (ROT[i]*4) & 15;
    const unsigned b = y >> (ROT[i+1]*4) & 15;
    x |= UNMIX[a][b].first << (i*4);
    x |= UNMIX[a][b].second << ((i+1)*4);
  }
  return x;
}

void unittest() {
  MbtiConverter mc(998244353);
  mt19937_64 rng(58);
  for (int t = 0; t < 32; ++t) {
    const unsigned x = rng();
    const unsigned y = mc.runBetween(x, 1, 2);
    assert(invPerm(y) == x);
  }
  for (int t = 0; t < 32; ++t) {
    const unsigned x = rng();
    const unsigned y = mc.runBetween(x, 2, 3);
    assert(invMix(y) == x);
  }
}

vector<pair<unsigned, unsigned>> tests;
unsigned ask(unsigned x) {
#ifdef LOCAL
  // MbtiConverter mc(998244353);
  MbtiConverter mc(1'000'000'007);
  const unsigned y = mc.run(x);
#else
  printf("? %08x\n", x);
  fflush(stdout);
  unsigned y;
  scanf("%08x", &y);
#endif
  tests.emplace_back(x, y);
  return y;
}

bool check(unsigned k) {
  MbtiConverter mc(k);
  for (const auto &test : tests) {
    if (mc.run(test.first) != test.second) return false;
  }
  return true;
}

#include <chrono>
#ifdef LOCAL
mt19937_64 rng(58);
#else
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#endif

int main() {
  // exper(); return 0;
  
  for (unsigned a = 0; a < 16; ++a) invP[MbtiConverter::__p[a]] = a;
  for (unsigned a = 0; a < 16; ++a) MOD[a] = a;
  for (unsigned a = 0; a < 16; ++a) MOD[a ^ 16] = a ^ 3;
  for (unsigned a = 0; a < 16; ++a) for (unsigned b = 0; b < 16; ++b) UNMIX[a ^ MOD[b << 1]][b ^ MOD[a << 1]] = make_pair(a, b);
  unittest();
  
  // {0,2,4,6}, {1,3,5,7}
  vector<unsigned> kss[2];
  for (int h = 0; h < 2; ++h) {
    const unsigned mask = 0x0f0f0f0fU << (h*4);
    for (unsigned k = mask; ; --k &= mask) {
      kss[h].push_back(k);
      if (!k) break;
    }
  }
  
  {
    const unsigned base = rng();
    const int i0 = (rng() & 3) << 1;
    const int i1 = i0 + 1;
    vector<unsigned> ys;
    for (unsigned a0 = 0; a0 < 16; ++a0) for (unsigned a1 = 0; a1 < 16; ++a1) {
      const unsigned x = base ^ a0 << (i0*4) ^ a1 << (i1*4);
      const unsigned y = ask(x);
      ys.push_back(y);
    }
    for (int h = 0; h < 2; ++h) {
      vector<unsigned> ks;
      for (const unsigned k : kss[h]) {
        int freq[16] = {};
        for (const unsigned y : ys) {
          unsigned x = y;
          x ^= k;
          x = invMix(x);
          x = invPerm(x);
          x ^= k;
          x = invMix(x);
          x = invPerm(x);
          x ^= k;
          if (++freq[x >> (h*7*4) & 15] > 16) {
            goto failed;
          }
        }
        ks.push_back(k);
       failed:{}
      }
      kss[h].swap(ks);
    }
cerr<<"|kss[*]| = "<<kss[0].size()<<" "<<kss[1].size()<<endl;
  }
  
  for (; (int)tests.size() < 4096; ) ask(rng());
  
  for (const unsigned k0 : kss[0]) for (const unsigned k1 : kss[1]) {
    const unsigned k = k0 | k1;
    if (check(k)) {
      printf("! %u\n", k);
      fflush(stdout);
      exit(0);
    }
  }
  return 0;
}