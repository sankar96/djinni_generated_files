// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#include "NativeMyClientInterface.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeMyClientInterface::NativeMyClientInterface() : ::djinni::JniInterface<::dependency_evaluator::MyClientInterface, NativeMyClientInterface>() {}

NativeMyClientInterface::~NativeMyClientInterface() = default;

NativeMyClientInterface::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeMyClientInterface::JavaProxy::~JavaProxy() = default;

void NativeMyClientInterface::JavaProxy::log_string(const std::string & c_str) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeMyClientInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_logString,
                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c_str)));
    ::djinni::jniExceptionCheck(jniEnv);
}

}  // namespace djinni_generated
