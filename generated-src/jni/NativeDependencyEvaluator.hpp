// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#pragma once

#include "dependency_evaluator.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeDependencyEvaluator final : ::djinni::JniInterface<::dependency_evaluator::DependencyEvaluator, NativeDependencyEvaluator> {
public:
    using CppType = std::shared_ptr<::dependency_evaluator::DependencyEvaluator>;
    using CppOptType = std::shared_ptr<::dependency_evaluator::DependencyEvaluator>;
    using JniType = jobject;

    using Boxed = NativeDependencyEvaluator;

    ~NativeDependencyEvaluator();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeDependencyEvaluator>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeDependencyEvaluator>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeDependencyEvaluator();
    friend ::djinni::JniClass<NativeDependencyEvaluator>;
    friend ::djinni::JniInterface<::dependency_evaluator::DependencyEvaluator, NativeDependencyEvaluator>;

};

}  // namespace djinni_generated
