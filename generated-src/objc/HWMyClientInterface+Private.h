// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#include "my_client_interface.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol HWMyClientInterface;

namespace djinni_generated {

class MyClientInterface
{
public:
    using CppType = std::shared_ptr<::dependency_evaluator::MyClientInterface>;
    using CppOptType = std::shared_ptr<::dependency_evaluator::MyClientInterface>;
    using ObjcType = id<HWMyClientInterface>;

    using Boxed = MyClientInterface;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated
