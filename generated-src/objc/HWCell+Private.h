// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#import "HWCell.h"
#include "cell.hpp"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class HWCell;

namespace djinni_generated {

struct Cell
{
    using CppType = ::dependency_evaluator::Cell;
    using ObjcType = HWCell*;

    using Boxed = Cell;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCpp(const CppType& cpp);
};

}  // namespace djinni_generated
