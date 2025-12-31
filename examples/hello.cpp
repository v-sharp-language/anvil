#include <anvil.hpp>
#include <fstream>

using namespace anvil::ir;

int main()
{
    Context ctx;
    Module mod("test");

    Function *fn = new Function(ctx.getInt32Ty(), "main");

    BasicBlock *entry = new BasicBlock("entry");
    IRBuilder builder(&ctx, entry);

    GlobalVariable *hello = mod.createStringLiteral(ctx, "Hello, world");
    ConstantInt *zero = new ConstantInt(ctx.getInt32Ty(), 0);
    Instruction *ptr = builder.CreateGEP(hello, {zero, zero});

    Instruction *value = builder.CreateAdd(new ConstantInt(ctx.getInt32Ty(), 42), new ConstantInt(ctx.getInt32Ty(), 58));
    builder.CreateRet(value);

    fn->addBlock(entry);
    mod.addFunction(fn);

    std::ofstream out(mod.name() + ".ll");
    if (!out)
        return 1;

    mod.print(out);

    return 0;
}