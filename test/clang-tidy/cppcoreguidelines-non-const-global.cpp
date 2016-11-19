// RUN: %check_clang_tidy %s cppcoreguidelines-non-const-global %t

int i;
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: found non-constexpr variable 'i' [cppcoreguidelines-non-const-global]
const int j {0};
constexpr int k {0};

struct S {
  int l;
};

void f() {
  int m;
}
