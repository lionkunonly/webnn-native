// Copyright 2021 The WebNN-native Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

// See the License for the specific language governing permissions and
// limitations under the License.

#include "webnn_native/Operand.h"

#include "common/Assert.h"
#include "common/Log.h"
#include "webnn_native/GraphBuilder.h"

namespace webnn_native {

    OperandBase::OperandBase(GraphBuilderBase* graphBuilder, OperatorBase* operatorBase)
        : ObjectBase(graphBuilder->GetContext()),
          mOperator(operatorBase),
          mType(ml::OperandType::Float32),
          mRank(0) {
        if (mOperator->Inputs().size() >= 1) {
            auto primaryInput = mOperator->Inputs()[0];
            // The type and rank is the same as input[0] by default.
            mType = primaryInput->Type();
            mRank = primaryInput->Rank();
        }
    }

    OperandBase::OperandBase(GraphBuilderBase* graphBuilder, ObjectBase::ErrorTag tag)
        : ObjectBase(graphBuilder->GetContext(), tag) {
    }

    // static
    OperandBase* OperandBase::MakeError(GraphBuilderBase* GraphBuilder) {
        return new OperandBase(GraphBuilder, ObjectBase::kError);
    }

}  // namespace webnn_native
