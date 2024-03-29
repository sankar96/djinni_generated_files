// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#import "HWMyRecord.h"


@implementation HWMyRecord

- (nonnull instancetype)initWithKey1:(int32_t)key1
                                key2:(nonnull NSString *)key2
                                key3:(nonnull NSArray<NSArray<NSString *> *> *)key3
{
    if (self = [super init]) {
        _key1 = key1;
        _key2 = [key2 copy];
        _key3 = [key3 copy];
    }
    return self;
}

+ (nonnull instancetype)myRecordWithKey1:(int32_t)key1
                                    key2:(nonnull NSString *)key2
                                    key3:(nonnull NSArray<NSArray<NSString *> *> *)key3
{
    return [[self alloc] initWithKey1:key1
                                 key2:key2
                                 key3:key3];
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p key1:%@ key2:%@ key3:%@>", self.class, (void *)self, @(self.key1), self.key2, self.key3];
}

@end
