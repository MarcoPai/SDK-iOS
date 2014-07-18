//
//  SBKBeacon.h
//  Sensoro Beacon Kit
//
//  Created by Blankwonder on 6/12/14.
//  Copyright (c) 2014 Sensoro Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreLocation/CoreLocation.h>
#import "SBKBeaconID.h"

extern NSString * const SBKBeaconInRangeStatusUpdatedNotification;

/**
 *  Constants to indicate radio transmit power level.
 */
typedef NS_ENUM(int, SBKBeaconTransmitPower) {
    /**
     *  The level is unknown.
     */
    SBKBeaconTransmitPowerUnknown = 0,
    /**
     *  Minimum transmit power level.
     */
    SBKBeaconTransmitPowerMin,
    /**
     *  Low transmit power level.
     */
    SBKBeaconTransmitPowerLow,
    /**
     *  Medium transmit power level. This is the default value.
     */
    SBKBeaconTransmitPowerMedium,
    /**
     *  High transmit power level.
     */
    SBKBeaconTransmitPowerHigh,
    /**
     *  Maximum transmit power level.
     */
    SBKBeaconTransmitPowerMax
};

#define SBKBeaconTransmitPowerDefault SBKBeaconTransmitPowerMedium

/**
 *  Constants to indicate advertising interval.
 */
typedef NS_ENUM(int, SBKBeaconAdvertisingInterval) {
    /**
     *  The interval is unknown.
     */
    SBKBeaconAdvertisingIntervalUnknown = 0,
    /**
     *  Means advertising frequency is highest. This may causes your battery to drain quickly.
     */
    SBKBeaconAdvertisingIntervalMin,
    /**
     *  Means advertising frequency is high.
     */
    SBKBeaconAdvertisingIntervalLow,
    /**
     *  Means advertising frequency is medium. This is the default value.
     */
    SBKBeaconAdvertisingIntervalMedium,
    /**
     *  Means advertising frequency is low.
     */
    SBKBeaconAdvertisingIntervalHigh,
    /**
     *  Means advertising frequency is lowest. This is the most power saving option.
     */
    SBKBeaconAdvertisingIntervalMax
};

#define SBKBeaconAdvertisingIntervalDefault SBKBeaconAdvertisingIntervalMedium

/**
 *  Constants to indicate accelerometer sensitivity.
 */
typedef NS_ENUM(int, SBKBeaconAccelerometerSensitivity) {
    /**
     *  The accelerometer is unknown.
     */
    SBKBeaconAccelerometerSensitivityUnknown = 0,
    /**
     *  The accelerometer is disabled.
     */
    SBKBeaconAccelerometerSensitivityDisabled,
    /**
     *  The accelerometer sensitivity is low.
     */
    SBKBeaconAccelerometerSensitivityLow,
    /**
     *  The accelerometer sensitivity is medium.
     */
    SBKBeaconAccelerometerSensitivityMedium,
    /**
     *  The accelerometer sensitivity is high.
     */
    SBKBeaconAccelerometerSensitivityHigh
};

#define SBKBeaconAccelerometerSensitivityDefault SBKBeaconAccelerometerSensitivityDisabled

/**
 *  Constants to indicate connection status.
 */
typedef NS_ENUM(int, SBKBeaconConnectionStatus){
    /**
     *  The connection is disconnected.
     */
    SBKBeaconConnectionStatusDisconnected = 0,
    /**
     *  The connection is connecting.
     */
    SBKBeaconConnectionStatusConnecting,
    /**
     *  The connection is connected.
     */
    SBKBeaconConnectionStatusConnected
};

/**
 *  Constants to indicate authorization status.
 */
typedef NS_ENUM(int, SBKBeaconWritePermissionStatus){
    /**
     *  The authorization status is unknown.
     */
    SBKBeaconWritePermissionStatusUnknown = 0,
    /**
     *  This application is authorized to write value to the beacon.
     */
    SBKBeaconWritePermissionStatusAuthorized,
    /**
     *  This application is not authorized to write value to the beacon.
     */
    SBKBeaconWritePermissionStatusRestricted
};

/**
 *  Constants to indicate energy saving mode.
 */
typedef NS_OPTIONS(u_int8_t, SBKBeaconEnergySavingMode) {
    /**
     *  Do not use any energy saving mode.
     */
    SBKBeaconEnergySavingModeNone = 0,
    /**
     *  Automatically reduce advertising frequency when ambient light level is dark.
     */
    SBKBeaconEnergySavingModeLightSensor = 1 << 0
};

typedef void (^SBKBeaconCompletionBlock)(NSError *error);

@protocol SBKBeaconDelegate;

/**
 *  The SBKBeacon class defines the interface of a sensoro beacon device. You can use instances of this class to get rssi, sensor data or configurate device settings. You do not create instances of this class directly. Use SBKBeaconManager to get SBKBeacon instances.
 *
 *  The identity of a beacon is defined by its beaconID properties.
 */
@interface SBKBeacon : NSObject

/**---------------------------------------------------------------------------------------
 * @name Setting and Getting the Delegate
 *  ---------------------------------------------------------------------------------------
 */

/**
 * The delegate of the app object.
 */
@property (readwrite, nonatomic, weak) id <SBKBeaconDelegate> delegate;

/**---------------------------------------------------------------------------------------
 * @name General Properties
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  A SBKBeaconID object identify the beacon. (read-only)
 */
@property (readonly, nonatomic, copy) SBKBeaconID * beaconID;

/**
 *  The beacon's hardware serial number. (read-only)
 */
@property (readonly, nonatomic, copy) NSString * serialNumber;

/**
 *  Returns a Boolean value that indicates whether the beacon is in range. (read-only) 
 *
 * @discussion Beacon will be marked out of range after approximate 8 second in order to prevent notifications delivering too frequently.
 */
@property (readonly, nonatomic, assign) BOOL inRange;


@property (readwrite, nonatomic, assign) NSInteger inRangeMinimumRssi;

/**
 *  The received signal strength of the beacon, measured in decibels. (read-only)
 *  
 *  @discussion If beacon is out of range, the value will be NSIntegerMin.
 */
@property (readonly, nonatomic, assign) NSInteger rssi;

/**
 *  The relative distance to the beacon. (read-only)
 *
 *  @discussion The value in this property gives a general sense of the relative distance to the beacon. Use it to quickly identify beacons that are nearer to the user rather than farther away.
 */
@property (readonly, nonatomic, assign) CLProximity proximity;

/**
 *  The battery charge level for the device. (read-only)
 *
 *  @discussion Battery level ranges from 0.0 to 1.0 (100% charged).
 */
@property (readonly, nonatomic, copy) NSNumber * batteryLevel;

/**
 *  The model of the device. (read-only)
 */
@property (readonly, nonatomic, copy) NSString * hardwareModelName;

/**
 *  The current firmware version for the device. (read-only)
 */
@property (readonly, nonatomic, copy) NSString * firmwareVersion;

/**---------------------------------------------------------------------------------------
 * @name Establishing or Canceling Connections with Beacon
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Establishes a connection to a beacon.
 *
 *  @param completion The block to execute after the connecting is completed. If error parameter is nil means connection has been established successfully.
 */
- (void)connectWithCompletion:(SBKBeaconCompletionBlock)completion;
/**
 *  Cancels an active or pending connection to a beacon.
 */
- (void)disconnect;
/**
 *  The current status of the connection.
 *
 *  @return A SBKBeaconConnectionStatus enum value.
 */
- (SBKBeaconConnectionStatus)connectionStatus;


/**---------------------------------------------------------------------------------------
 * @name Beacon Configuration
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  The dictionary of beacon base configuration attributes. (read-only)
 *
 *  @discussion This property will be available after connect. For available options, see SBKBeaconBaseSettings.
 *
 *  @see writeBaseSettings:completion:
 */
@property (readonly, nonatomic) NSDictionary *baseSettings;

/**
 *  The dictionary of sensor configuration attributes. (read-only)
 *
 *  @discussion This property will be available after connect. For available options, see SBKBeaconSensorSettings.
 *
*  @see writeSensorSettings:completion:
 */
@property (readonly, nonatomic) NSDictionary *sensorSettings;

/**
 *  Updates proximity UUID of this beacon.
 *
 *  @param proximityUUID Proximity UUID in NSUUID object.
 *  @param completion    The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this writing operation be executed.
 */
- (BOOL)writeProximityUUID:(NSUUID *)proximityUUID completion:(SBKBeaconCompletionBlock)completion;

/**
 *  Updates major and minor of this beacon.
 *
 *  @param major      The major value.
 *  @param minor      The minor value.
 *  @param completion The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this writing operation be executed.
 */
- (BOOL)writeMajor:(NSNumber *)major minor:(NSNumber *)minor completion:(SBKBeaconCompletionBlock)completion;

/**
 *  Updates base settings of this beacon.
 *
 *  @param settings   Configuration attributes you try to update in a dictionary. For available options, see SBKBeaconBaseSettings.
 *  @param completion The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this writing operation be executed.
 */
- (BOOL)writeBaseSettings:(NSDictionary *)settings completion:(SBKBeaconCompletionBlock)completion;

/**
 *  Updates sensor settings of this beacon.
 *
 *  @param settings   Configuration attributes you try to update in a dictionary. For available options, see SBKBeaconSensorSettings.
 *  @param completion The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this writing operation be executed.
 */
- (BOOL)writeSensorSettings:(NSDictionary *)settings completion:(SBKBeaconCompletionBlock)completion;

/**
 *  Resets beacon to factory settings. This will reset proximityUUID, major, minor, baseSettings and sensorSettings to original values.
 *
 *  @param completion The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this writing operation be executed.
 */
- (BOOL)resetToFactorySettingsWithCompletion:(SBKBeaconCompletionBlock)completion;

/**---------------------------------------------------------------------------------------
 * @name Writing Authorization
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Indicates if the application has permission to write setting to the beacon.
 */
@property (readonly, nonatomic) SBKBeaconWritePermissionStatus writePermissionStatus;

/**
 *  You should use this method to request write permission if writePermissionStatus property is restricted.
 *
 *  @param password   Password string.
 *  @param completion The block to execute after the operation is completed. If error parameter is nil means success.
 *
 *  @see writePermissionStatus
 *
 *  @return Can this operation be executed.
 */
- (BOOL)requireWritePermissionWithPassword:(NSString *)password completion:(SBKBeaconCompletionBlock)completion;

/**
 *  Changes the beacon's password.
 *
 *  @param password   New password string.
 *  @param completion The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this writing operation be executed.
 */
- (BOOL)updateWritePassword:(NSString *)password completion:(SBKBeaconCompletionBlock)completion;


/**---------------------------------------------------------------------------------------
 * @name Temperature, Light and Accelerometer Sensor
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  Causes beacon to reload temperature and light sensors data immediately.
 *
 *  @param completion The block to execute after the operation is completed. If error parameter is nil means success.
 *
 *  @return Can this operation be executed.
 */
- (BOOL)reloadSensorDataWithCompletion:(SBKBeaconCompletionBlock)completion;

- (BOOL)isTemperatureSensorAvailable;
- (BOOL)isLightSensorAvailable;
- (BOOL)isAccelerometerAvailable;

/**
 *  Temperature value in Celsius
 */
@property (readonly, nonatomic, copy) NSNumber * temperature;

/**
 *  The ambient light level in lux.
 */
@property (readonly, nonatomic, copy) NSNumber * light;

/**
 *  The number of accelerometer count.
 */
@property (readonly, nonatomic, copy) NSNumber * accelerometerCount;

/**
 *  Flag indicating accelerometer state, boolean value wrapped in NSNumber.
 */
@property (readonly, nonatomic, copy) NSNumber * isMoving;

/**
 *  Resets accelerometer counter value to zero.
 *
 *  @param completion The block to execute after the writing is completed. If error parameter is nil means writing successfully.
 *
 *  @return Can this operation be executed.
 */
- (BOOL)resetAccelerometerCountWithCompletion:(SBKBeaconCompletionBlock)completion;

/**---------------------------------------------------------------------------------------
 * @name Bridge to Core Bluetooth
 *  ---------------------------------------------------------------------------------------
 */

/**
 *  The CBPeripheral object assign to this beacon.
 */
@property (readonly, nonatomic, strong) CBPeripheral * assignedPeripheral;

@end

/**
 *  The delegate of a SBKBeacon object must adopt the SBKBeaconDelegate protocol. The delegate uses this protocol’s methods to monitor the connection state and sensor date changing of a beacon. There are no required methods in this protocol.
 */
@protocol SBKBeaconDelegate <NSObject>

@optional

/**
 *  Invoked when a connection is successfully created with a beacon.
 *
 *  @param beacon The beacon that has been connected.
 */
- (void)sensoroBeaconDidConnect:(SBKBeacon *)beacon;

/**
 *  Invoked when an existing connection with a beacon is torn down
 *
 *  @param beacon The beacon that has been disconnected.
 *  @param error  If an error occurred, the cause of the failure.
 */
- (void)sensoroBeaconDidDisconnect:(SBKBeacon *)beacon error:(NSError *)error;

/**
 *  Invoked when a beacon's RSSI changes.
 *
 *  @param beacon The beacon providing this information.
 *  @param rssi   The new rssi value.
 */
- (void)sensoroBeacon:(SBKBeacon *)beacon didUpdateRSSI:(NSInteger)rssi;;

/**
 *  Invoked when a beacon's temperature data changes.
 *
 *  @param beacon      The beacon providing this information.
 *  @param temperature New temperature value wrapped in NSNumber.
 */
- (void)sensoroBeacon:(SBKBeacon *)beacon didUpdateTemperatureData:(NSNumber *)temperature;

/**
 *  Invoked when a beacon's light lux changes.
 *
 *  @param beacon The beacon providing this information.
 *  @param light  New ambient light level in lux.
 */
- (void)sensoroBeacon:(SBKBeacon *)beacon didUpdateLightData:(NSNumber *)light;

/**
 *  Invoked when a beacon's accelerometer count changes.
 *
 *  @param beacon             The beacon providing this information.
 *  @param accelerometerCount New accelerometer count value.
 */
- (void)sensoroBeacon:(SBKBeacon *)beacon didUpdateAccelerometerCount:(NSNumber *)accelerometerCount;

/**
 *  Invoked when a beacon's moving state changes.
 *
 *  @param beacon   The beacon providing this information.
 *  @param isMoving New moving state.
 */
- (void)sensoroBeacon:(SBKBeacon *)beacon didUpdateMovingState:(NSNumber *)isMoving;

@end

extern NSString * const SBKBeaconBaseSettingsTransmitPowerKey;
extern NSString * const SBKBeaconBaseSettingsAdvertisingIntervalKey;
extern NSString * const SBKBeaconBaseSettingsEnergySavingModeKey;
extern NSString * const SBKBeaconBaseSettingsMeasuredPowerKey;

extern NSString * const SBKBeaconSensorSettingsTemperatureSamplingIntervalKey;
extern NSString * const SBKBeaconSensorSettingsLightSamplingIntervalKey;
extern NSString * const SBKBeaconSensorSettingsAccelerometerSensitivityKey;
