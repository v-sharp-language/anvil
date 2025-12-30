#include <anvil.hpp>
#include <fstream>

using namespace anvil::ir;

int main()
{
    Context ctx;
    Module mod("not");

    auto *i32 = ctx.getIntType(32);
    auto *fn = new Function(i32, "main");

    BasicBlock *entry = new BasicBlock("entry");
    IRBuilder builder(entry);

    Instruction *value = builder.CreateAdd(new Value(i32), new Value(i32));
    builder.CreateRet(value);

    fn->addBlock(entry);
    mod.addFunction(fn);

    std::ofstream out(mod.name() + ".ll");
    if (!out)
        return 1;

    mod.print(out);

    return 0;
}