#include <iostream>
#include "lhss.hpp"

using namespace lhss;
using namespace std;

int main(int argc, char** argv)
{
  if (argc < 4) {
    cout << "Usage: ./sample_bin m1 m2 m3" << endl;
    return 1;
  }

  Setup(64);
  Client c;
  auto public_key = c.GetPk();
  SkShare s0, s1;
  c.ShareSk(s0, s1);

  uint64_t m1 = stoi(argv[1]);
  uint64_t m2 = stoi(argv[2]);
  uint64_t m3 = stoi(argv[3]);

  HSSCtxt ct1, ct2, ct3;
  HSSEncrypt(public_key, m1, ct1);
  HSSEncrypt(public_key, m2, ct2);
  HSSEncrypt(public_key, m3, ct3);
 
  SkShare t0_out;
  {
    SkShare t0;
    Evaluator e0(public_key, s0);
    e0.ConvHSSCtxtToShare(ct1,  t0);
    e0.MultHSSCtxtAndShare(ct2, t0, t0_out);
    e0.ConvHSSCtxtToShare(ct3, t0);
    e0.AddShares(t0, t0_out);
  }

  SkShare t1_out;
  {
    SkShare t1;
    Evaluator e1(public_key, s1);
    e1.ConvHSSCtxtToShare(ct1,  t1);
    e1.MultHSSCtxtAndShare(ct2, t1, t1_out);
    e1.ConvHSSCtxtToShare(ct3, t1);
    e1.AddShares(t1, t1_out);
  }

  uint64_t res;
  ReconstShares(t0_out, t1_out, res);
  cout << "Result = " << res << endl;
  return 0;
}
