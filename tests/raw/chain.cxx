
// Test 1: Simple chain of operations

using real_t = double;

int main() {
  real_t a = 10.;
  real_t b = 4.7;
  real_t c = a * b;
  real_t d = 12.;
  real_t e = c * d;

  return e != 564.;
}

