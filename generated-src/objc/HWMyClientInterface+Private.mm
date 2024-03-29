// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#import "HWMyClientInterface+Private.h"
#import "HWMyClientInterface.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"
#include <stdexcept>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class MyClientInterface::ObjcProxy final
: public ::dependency_evaluator::MyClientInterface
, private ::djinni::ObjcProxyBase<ObjcType>
{
    friend class ::djinni_generated::MyClientInterface;
public:
    using ObjcProxyBase::ObjcProxyBase;
    void log_string(const std::string & c_str) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() logString:(::djinni::String::fromCpp(c_str))];
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto MyClientInterface::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto MyClientInterface::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return dynamic_cast<ObjcProxy&>(*cpp).djinni_private_get_proxied_objc_object();
}

}  // namespace djinni_generated
