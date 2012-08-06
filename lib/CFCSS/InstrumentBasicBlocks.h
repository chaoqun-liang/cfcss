/**
 * @author Hermann Loose <hermannloose@gmail.com>
 *
 * TODO(hermannloose): Add description.
 */
#pragma once

#include "AssignBlockSignatures.h"

#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/Instructions.h"
#include "llvm/Module.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace cfcss {
  // FIXME(hermannloose): Remove duplication & is 64 sensible?
  typedef SmallPtrSet<BasicBlock*, 64> BlockSet;

  class InstrumentBasicBlocks : public ModulePass {

    public:
      static char ID;

      InstrumentBasicBlocks();

      virtual void getAnalysisUsage(AnalysisUsage &AU) const;
      virtual bool runOnModule(Module &M);

    private:
      AssignBlockSignatures *ABS;

      AllocaInst *GSR;
      AllocaInst *D;

      BlockSet ignoreBlocks;

      void instrumentEntryBlock(BasicBlock &entryBlock);
      BasicBlock* createErrorHandlingBlock(Function *F);

      Instruction* instrumentBlock(BasicBlock &BB, BasicBlock *errorHandlingBlock,
          Instruction *insertBefore);

      Instruction* insertRuntimeAdjustingSignature(BasicBlock &BB);

      GlobalVariable *interFunctionGSR;
  };

}
