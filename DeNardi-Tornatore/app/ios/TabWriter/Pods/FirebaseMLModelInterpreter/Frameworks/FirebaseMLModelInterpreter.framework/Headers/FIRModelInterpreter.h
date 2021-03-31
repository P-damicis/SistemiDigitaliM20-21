#import <Foundation/Foundation.h>

@class FIRCustomLocalModel;
@class FIRCustomRemoteModel;
@class FIRModelInputOutputOptions;
@class FIRModelInputs;
@class FIRModelOutputs;

NS_ASSUME_NONNULL_BEGIN

/**
 * A block containing an array of custom model inference outputs, or nil if there's an error.
 *
 * @param outputs An array of results of model inference. Returns nil when there is an error.
 * @param error The error, if any, while running the custom model inference, including
 *     `MachineLearningErrorDomainCode.InvalidArgument` when:
 *     - `options` are nil.
 *     - Either input or outoutput data formats in `options` are empty.
 *     - The number of inputs do not match the data options.
 *     - The input byte buffer does not have the expected size.
 *     - The input data is neither a byte buffer (`NSData`) nor an array.
 *     - The input dimension does not match the input format specified in `options`.
 *     - The input element type in the data options is unexpected.
 *     - The input element type is not a number as specified in the data options.
 *     - The input type specified in the data options does not match the model.
 *     - Dimension of input data does not match the data options.
 *     - An element type in the data options does not match the actual output.
 *     - The total size in bytes specified in the data options does not match the actual output.
 *     - The number of dimensions in the data options does not match the actual output.
 *     - The shape in the data optinos does not match the actual output.
 *     - The output element type in the data options is unexpected.
 *     `MachineLearningErrorDomainCode.OutOfRange` when:
 *     - An input index in `options` is out of range.
 *     - An output index in `options` is out of range.
 *     `MachineLearningErrorDomainCode.Unknown` when:
 *     - No output was generated by the custom model.
 *     - There are no tensors matching an output index in the data options.
 *     `MachineLearningErrorDomainCode.Internal` when:
 *     - An input tensor cannot be located.
 */
typedef void (^FIRModelInterpreterRunCallback)(FIRModelOutputs *_Nullable outputs,
                                               NSError *_Nullable error)
    NS_SWIFT_NAME(ModelInterpreterRunCallback) DEPRECATED_MSG_ATTRIBUTE(
        "This API is deprecated. Please see updated custom model implementation instructions at "
        "https://firebase.google.com/docs/ml/ios/use-custom-models");

/**
 * A block containing the index for an input or an output op.
 *
 * @param index The index, as an `unsignedIntValue`, for an input or output op or `nil` if there was
 * an error.
 * @param error An error while getting the index or `nil`.
 */
typedef void (^FIRModelInterpreterInputOutputOpIndexCallback)(NSNumber *_Nullable index,
                                                              NSError *_Nullable error)
    NS_SWIFT_NAME(ModelInterpreterInputOutputOpIndexCallback) DEPRECATED_MSG_ATTRIBUTE(
        "This API is deprecated. Please see updated custom model implementation instructions at "
        "https://firebase.google.com/docs/ml/ios/use-custom-models");

/** A Firebase interpreter for a custom model. */
NS_SWIFT_NAME(ModelInterpreter)
DEPRECATED_MSG_ATTRIBUTE(
    "This API is deprecated. Please see updated custom model implementation instructions at "
    "https://firebase.google.com/docs/ml/ios/use-custom-models")
@interface FIRModelInterpreter : NSObject

/**
 * Enables stats collection in ML Kit model interpreter. The stats include API call counts, errors,
 * API call durations, options, etc. No personally identifiable information is logged.
 *
 * <p>The setting is per `FirebaseApp`, and therefore per `ModelInterpreter`, and it is persistent
 * across launches of the app. It means if the user uninstalls the app or clears all app data, the
 * setting will be erased. The best practice is to set the flag in each initialization.
 *
 * <p>By default the logging is enabled. You have to specifically set it to false to disable
 * logging.
 */
@property(nonatomic, getter=isStatsCollectionEnabled) BOOL statsCollectionEnabled;

/**
 * Gets an instance of a custom model interpreter for the given `localModel` and the default
 * Firebase app. The default Firebase app instance must be configured before calling this method;
 * otherwise, raises `FIRAppNotConfigured` exception. The returned interpreter is thread safe.
 * Custom models hosted in non-default Firebase apps are currently not supported.
 *
 * @param localModel Custom local model.
 * @return A custom model interpreter with the given options and the default Firebase app.
 */
+ (instancetype)modelInterpreterForLocalModel:(FIRCustomLocalModel *)localModel
    NS_SWIFT_NAME(modelInterpreter(localModel:));

/**
 * Gets an instance of a custom model interpreter for the given `remoteModel` and the default
 * Firebase app. The default Firebase app instance must be configured before calling this method;
 * otherwise, raises `FIRAppNotConfigured` exception. The returned interpreter is thread safe.
 * Custom models hosted in non-default Firebase apps are currently not supported.
 *
 * @discussion It is recommended that the `CustomRemoteModel` be downloaded before creating a new
 *     instance of `ModelInterpreter`. To download the remote model, invoke the `ModelManager`'s
 *     `download(_:conditions:)` method and monitor the returned `Progress` and/or listen for the
 *      download notifications defined in `FIRModelDownloadNotifications.h`.
 *
 * @param remoteModel Custom remote model.
 * @return A custom model interpreter with the given options and the default Firebase app.
 */
+ (instancetype)modelInterpreterForRemoteModel:(FIRCustomRemoteModel *)remoteModel
    NS_SWIFT_NAME(modelInterpreter(remoteModel:));

/** Unavailable. */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Runs model inference with the given inputs and data options asynchronously. Inputs and data
 * options should remain unchanged until the model inference completes.
 *
 * @param inputs Inputs for custom model inference.
 * @param options Data options for the custom model specifiying input and output data types and
 *     dimensions.
 * @param completion Handler to call back on the main thread with `ModelOutputs` or error.
 */
- (void)runWithInputs:(FIRModelInputs *)inputs
              options:(FIRModelInputOutputOptions *)options
           completion:(FIRModelInterpreterRunCallback)completion
    NS_SWIFT_NAME(run(inputs:options:completion:));

/**
 * Gets the index of an input op with the given name.
 *
 * @param opName The name of the input op.
 * @param completion Handler to call back on the main thread with input op index as an
 *     `unsignedIntValue` or error.
 */
- (void)inputIndexForOp:(NSString *)opName
             completion:(FIRModelInterpreterInputOutputOpIndexCallback)completion
    NS_SWIFT_NAME(inputIndex(opName:completion:));

/**
 * Gets the index of an output op with the given name.
 *
 * @param opName The name of the output op.
 * @param completion Handler to call back on the main thread with output op index as an
 *     `unsignedIntValue` or error.
 */
- (void)outputIndexForOp:(NSString *)opName
              completion:(FIRModelInterpreterInputOutputOpIndexCallback)completion
    NS_SWIFT_NAME(outputIndex(opName:completion:));

@end

NS_ASSUME_NONNULL_END