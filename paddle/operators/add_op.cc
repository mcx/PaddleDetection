#include "paddle/operators/add_op.h"
#include "paddle/framework/op_registry.h"
#include "paddle/framework/tensor.h"

namespace paddle {
namespace operators {

class AddOp : public framework::OperatorWithKernel {
protected:
  void InferShape(
      const std::vector<const framework::Tensor *> &inputs,
      const std::vector<framework::Tensor *> &outputs) const override {
    PADDLE_ENFORCE(inputs.size() == 2, "Input size of AddOp must be two");
    PADDLE_ENFORCE(outputs.size() == 1, "Output size of AddOp must be one");
    PADDLE_ENFORCE(
        inputs[0] != nullptr && inputs[1] != nullptr && outputs[0] != nullptr,
        "Inputs/Outputs of AddOp must all be set");
    PADDLE_ENFORCE(inputs[0]->dims() == inputs[1]->dims(),
                   "Two input of Add Op's dimension must be same.");
    // Need set dims in Tensor
    // outputs[0]->set_dims(inputs[0]->dims())
  }
};

class AddOpMaker : public framework::OpProtoAndCheckerMaker {
public:
  AddOpMaker(framework::OpProto *proto, framework::OpAttrChecker *op_checker)
      : framework::OpProtoAndCheckerMaker(proto, op_checker) {
    AddInput("X", "The first input of add op");
    AddInput("Y", "The second input of add op");
    AddOutput("Out", "The output of add op");
    AddComment(R"DOC(
Two Element Add Operator.

The equation is: Out = X + Y
)DOC");
  }
};
}  // namespace operators
}  // namespace paddle

REGISTER_OP(add_two, paddle::operators::AddOp, paddle::operators::AddOpMaker);
typedef paddle::operators::AddKernel<::paddle::platform::CPUPlace, float>
    AddKernel_CPU_float;
REGISTER_OP_CPU_KERNEL(add_two, AddKernel_CPU_float);