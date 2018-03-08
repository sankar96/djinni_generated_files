// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#import "HWCell+Private.h"
#import "DJIMarshal+Private.h"
#include <cassert>

namespace djinni_generated {

auto Cell::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.formulaValue),
            ::djinni::String::toCpp(obj.actualValue),
            ::djinni::List<::djinni::String>::toCpp(obj.dependents),
            ::djinni::List<::djinni::String>::toCpp(obj.precedents),
            ::djinni::List<::djinni::String>::toCpp(obj.expressionTokens)};
}

auto Cell::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[HWCell alloc] initWithFormulaValue:(::djinni::String::fromCpp(cpp.formulaValue))
                                    actualValue:(::djinni::String::fromCpp(cpp.actualValue))
                                     dependents:(::djinni::List<::djinni::String>::fromCpp(cpp.dependents))
                                     precedents:(::djinni::List<::djinni::String>::fromCpp(cpp.precedents))
                               expressionTokens:(::djinni::List<::djinni::String>::fromCpp(cpp.expressionTokens))];
}

}  // namespace djinni_generated