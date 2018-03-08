// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dependency_evaluator.djinni

#import <Foundation/Foundation.h>

@interface HWUpdatedValues : NSObject
- (nonnull instancetype)initWithRow:(int32_t)row
                             column:(int32_t)column
                        actualValue:(nonnull NSString *)actualValue
                       formulaValue:(nonnull NSString *)formulaValue;
+ (nonnull instancetype)updatedValuesWithRow:(int32_t)row
                                      column:(int32_t)column
                                 actualValue:(nonnull NSString *)actualValue
                                formulaValue:(nonnull NSString *)formulaValue;

@property (nonatomic, readonly) int32_t row;

@property (nonatomic, readonly) int32_t column;

@property (nonatomic, readonly, nonnull) NSString * actualValue;

@property (nonatomic, readonly, nonnull) NSString * formulaValue;

@end