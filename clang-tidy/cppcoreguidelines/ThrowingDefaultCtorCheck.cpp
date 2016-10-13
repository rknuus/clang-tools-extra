//===--- ThrowingDefaultCtorCheck.cpp - clang-tidy-------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ThrowingDefaultCtorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace cppcoreguidelines {

void ThrowingDefaultCtorCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(cxxConstructorDecl(isDefaultConstructor(), unless(isNoThrow()),
                                        unless(hasDescendant(compoundStmt()))).bind("ctor"), this);
  Finder->addMatcher(cxxConstructorDecl(isDefaultConstructor(), unless(isNoThrow()),
                                        hasDescendant(compoundStmt().bind("body"))).bind("ctor"), this);
}

const char *DiagMessage = "C.44: throwing default constructor %0";

void ThrowingDefaultCtorCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *CtorDecl = Result.Nodes.getNodeAs<CXXMethodDecl>("ctor");
  const auto *CtorBody = Result.Nodes.getNodeAs<CompoundStmt>("body");
  const auto Loc = CtorBody ? CtorBody->getLocStart() : Lexer::getLocForEndOfToken(CtorDecl->getLocEnd(), 0, *Result.SourceManager, Result.Context->getLangOpts());
  const auto Insertion = CtorBody ? "noexcept " : " noexcept";
  const auto FixCtorEnd = FixItHint::CreateInsertion(Loc, Insertion);
  diag(CtorDecl->getLocStart(), DiagMessage) << CtorDecl << FixCtorEnd;
}

} // namespace cppcoreguidelines
} // namespace tidy
} // namespace clang
