#! /usr/bin/env bash

### Configuration

# Djinni IDL file location
djinni_file="dependency_evaluator.djinni"

# C++ namespace for generated src
namespace="dependency_evaluator"

# Objective-C class name prefix for generated src
objc_prefix="HW"

# Java package name for generated src
java_package="com.example.sankar_5526.helloworld"


### Script

# get base directory
base_dir=$(cd "`dirname "0"`" && pwd)

# get java directory from package name
java_dir=$(echo $java_package | tr . /)

# output directories for generated src
cpp_out="$base_dir/generated-src/cpp"
objc_out="$base_dir/generated-src/objc"
jni_out="$base_dir/generated-src/jni"
java_out="$base_dir/generated-src/java/$java_dir"

# clean generated src dirs
rm -rf $cpp_out
rm -rf $jni_out
rm -rf $objc_out
rm -rf $java_out 

# execute the djinni command
/Users/sankar-5526/Desktop/deps/djinni/src/run \
   --java-out $java_out \
   --java-package $java_package \
   --ident-java-field mFooBar \
   --cpp-out $cpp_out \
   --cpp-namespace $namespace \
   --jni-out $jni_out \
   --ident-jni-class NativeFooBar \
   --ident-jni-file NativeFooBar \
   --objc-out $objc_out \
   --objc-type-prefix $objc_prefix \
   --objcpp-out $objc_out \
   --idl $djinni_file