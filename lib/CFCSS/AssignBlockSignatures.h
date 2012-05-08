/**
 * @author Hermann Loose <hermannloose@gmail.com>
 *
 * TODO(hermannloose): Add description.
 */
#pragma once

#include "llvm/ADT/DenseMap.h"
#include "llvm/Constants.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace cfcss {
  typedef DenseMap<BasicBlock*, ConstantInt*> SignatureMap;
  typedef DenseMap<BasicBlock*, bool> FaninMap;

  class AssignBlockSignatures : public FunctionPass {
    public:
      static char ID;

      AssignBlockSignatures();

      virtual void getAnalysisUsage(AnalysisUsage &AU) const;
      virtual bool runOnFunction(Function &F);

      ConstantInt* getSignature(BasicBlock * const BB);
      bool isFaninNode(BasicBlock * const BB);

    private:
      SignatureMap blockSignatures;
      SignatureMap signatureUpdateSources;
      FaninMap blockFanin;
      unsigned long nextID;
  };

}
