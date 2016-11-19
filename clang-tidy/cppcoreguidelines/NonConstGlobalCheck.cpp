//===--- NonConstGlobalCheck.cpp - clang-tidy------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "NonConstGlobalCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace cppcoreguidelines {

void NonConstGlobalCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(varDecl(hasGlobalStorage(),
                             unless(hasType(isConstQualified()))).bind("glob"),
                     this);
}

// TODO(KNR): why is the following code prone to the warning that parameter 'Result' is allegedly unused?
//
// guidelines/NonConstGlobalCheck.cpp:32:65: warning: parameter 'Result' is unused [misc-unused-parameters]
// void NonConstGlobalCheck::check(const MatchFinder::MatchResult &Result) {
//                                                                 ^
//                                                                  /*Result*/
void NonConstGlobalCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("glob");
  diag(MatchedDecl->getLocation(), "found non-constexpr variable %0")
      << MatchedDecl;
}

} // namespace cppcoreguidelines
} // namespace tidy
} // namespace clang
