#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <iostream>
#include <string>
#include <lexer.h>

int main() {
    std::string sourceCode = "func main() { let *a = 2; return a; }";
    auto tokens = tokenize(sourceCode);
    for (const auto &token : tokens) {
        std::cout << "Token: " << token.value << ", Type: " << token.type << "\n";
    }

    llvm::LLVMContext Context;
    llvm::Module *Module = new llvm::Module("QLC", Context);
    llvm::IRBuilder<> Builder(Context);

    llvm::FunctionType *FuncType = llvm::FunctionType::get(Builder.getInt32Ty(), false);
    llvm::Function *MainFunction = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "main", Module);

    llvm::BasicBlock *EntryBB = llvm::BasicBlock::Create(Context, "entry", MainFunction);
    Builder.SetInsertPoint(EntryBB);

    llvm::Value *ReturnValue = llvm::ConstantInt::get(Builder.getInt32Ty(), 42);
    Builder.CreateRet(ReturnValue);

    Module->print(llvm::errs(), nullptr);

    delete Module;
    return 0;
}