// RUN: %check_clang_tidy %s cppcoreguidelines-throwing-default-ctor %t

// manual invocation:
// ninja clang-tidy
// ninja FileCheck
// ./clang-tidy ../../llvm/tools/clang/tools/extra/test/clang-tidy/cppcoreguidelines-throwing-default-ctor.cpp -checks='cppcoreguidelines-*' -extra-arg='-std=c++11'
// set PATH $PATH (pwd)/bin  # fish shell
// ./bin/llvm-lit ../llvm/tools/clang/tools/extra/test/clang-tidy/cppcoreguidelines-throwing-default-ctor.cpp -v
//
// to see AST:
// clang-check -ast-dump ~/tmp/ctor_pure_decl.cpp -- --std=c++11
//
// to develop a matcher:
// clang-query /Users/rkn/Projects/Experiments/CppCoreGuidelines_Linter/llvm/tools/clang/tools/extra/test/clang-tidy/cppcoreguidelines-throwing-default-ctor.cpp -extra-arg='-std=c++11'

class A {
public:
    A() {}
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: C.44: throwing default constructor 'A' [cppcoreguidelines-throwing-default-ctor]
};
// CHECK-FIXES: A() noexcept {}

class B {
public:
    B();
// CHECK-MESSAGES: :[[@LINE-1]]:5: warning: C.44: throwing default constructor 'B' [cppcoreguidelines-throwing-default-ctor]
};
// CHECK-FIXES: B() noexcept;

class C {
public:
    C() noexcept;
};

class D {
public:
    D() noexcept(true);
};

class E {
public:
    E() noexcept/*(true)*/;
};

class F {
public:
    F() noexcept/*(false)*/;
};

// class G {
// public:
//     G() noexcept(false);
// // HECK-MESSAGES: :[[@LINE-1]]:5: warning: C.44: throwing default constructor 'G' [cppcoreguidelines-throwing-default-ctor]
// };
// // HECK-FIXES: G() noexcept;

class I {
public:
    I() throw();
};

// class J {
// public:
//     J() throw(A);
// // HECK-MESSAGES: :[[@LINE-1]]:5: warning: C.44: throwing default constructor 'J' [cppcoreguidelines-throwing-default-ctor]
// };

class K {
public:
    K(const int i=0) noexcept;
};
