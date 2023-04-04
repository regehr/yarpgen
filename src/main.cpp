/*
Copyright (c) 2015-2020, Intel Corporation
Copyright (c) 2019-2020, University of Utah

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

//////////////////////////////////////////////////////////////////////////////
#include "options.h"
#include "program.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <vector>

using namespace yarpgen;

int main(int argc, char *argv[]) {
    OptionParser::initOptions();
    OptionParser::parse(argc, argv);

    Options &options = Options::getInstance();
    rand_val_gen = std::make_shared<RandValGen>(options.getSeed());
    options.setSeed(rand_val_gen->getSeed());

    if (options.getMutationKind() == MutationKind::EXPRS ||
        options.getMutationKind() == MutationKind::ALL) {
        rand_val_gen->setMutationSeed(options.getMutationSeed());
    }

    /*
    auto lhs = std::make_shared<ConstantExpr>(IRValue(IntTypeID::INT, IRValue::AbsValue{false, 1757564140}));
    auto rhs = std::make_shared<ConstantExpr>(IRValue(IntTypeID::INT, IRValue::AbsValue{true, 887964283}));
    auto expr = std::make_shared<BinaryExpr>(BinaryOp::ADD, lhs, rhs);
    EvalCtx ctx;
    expr->evaluate(ctx);
    auto tmp = std::static_pointer_cast<ScalarVar>(expr->getValue())->getCurrentValue();
    std::cout << static_cast<int>(tmp.getUBCode()) << std::endl;

    return 0;
    */

    ProgramGenerator new_program;
    new_program.emit();

    return 0;
}
