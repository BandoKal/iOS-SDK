//
//   ______     _   _                 _          _____ _____  _  __
//  |  ____|   | | (_)               | |        / ____|  __ \| |/ /
//  | |__   ___| |_ _ _ __ ___   ___ | |_ ___  | (___ | |  | | ' /
//  |  __| / __| __| | '_ ` _ \ / _ \| __/ _ \  \___ \| |  | |  <
//  | |____\__ \ |_| | | | | | | (_) | ||  __/  ____) | |__| | . \
//  |______|___/\__|_|_| |_| |_|\___/ \__\___| |_____/|_____/|_|\_\
//
//
//  Version: 3.2.1
//  Copyright (c) 2015 Estimote. All rights reserved.

#import <Foundation/Foundation.h>
#import "ESTDefinitions.h"
#import "ESTNearable.h"
#import "ESTBeaconVO.h"

/**
 *  ESTCloudManager class is responsible for Estimote Cloud integration. It allows you to invoke 
 *  available Estimote Cloud API methods using block pattern to handle result.
 */
@interface ESTCloudManager : NSObject

#pragma mark - Configuration

/**
 * Sets App ID and App Token, enabling communication with the Estimote Cloud API.
 *
 * You can find your API App ID and API App Token in the Account Settings section of the Estimote Cloud.
 *
 * @param appID The API App ID.
 * @param appToken The API App Token.
 */
+ (void)setupAppID:(NSString *)appID andAppToken:(NSString *)appToken;

/**
 * Checks if App ID and App Token were set.
 */
+ (BOOL)isAuthorized;

/**
 *  Enables analytics requests on Enter/Exit monitoring events. Analytics data
 *  is collected in the Estimote Cloud.
 *
 *  @param enable flag indicating if analytics should be enabled
 */
+ (void)enableAnalytics:(BOOL)enable __attribute ((deprecated(("Staring from SDK 3.2.0 use enableMonitoringAnalytics: or enableRangingAnalytics: instead."))));

/**
 *  Enables analytics requests on Enter/Exit monitoring events. Analytics data
 *  is collected in the Estimote Cloud.
 *
 *  @param enable flag indicating if analytics for monitoring should be enabled
 */
+ (void)enableMonitoringAnalytics:(BOOL)enable;

/**
 *  Enables analytics requests for ranging events. 
 *  Information about beacons and their Proximity is collected
 *  in the Estimote Cloud.
 *
 *  @param enable flag indicating if analytics for ranging should be enabled
 */
+ (void)enableRangingAnalytics:(BOOL)enable;

/**
 *  When GPS Positioning is turned on analytics events
 *  contains information about GPS Location.
 *
 *  @param enable flag indicating if GPS Positioning should be enabled
 */
+ (void)enableGPSPositioningForAnalytics:(BOOL)enable;

/**
 *  Indicates current state of analytics.
 *
 *  @return flag that indicates if analytics is enabled
 */
+ (BOOL)isAnalyticsEnabled __attribute ((deprecated(("Staring from SDK 3.2.0 use enableMonitoringAnalytics: or enableRangingAnalytics: instead."))));

/**
 *  Indicates current state of monitoring analytics.
 *
 *  @return flag that indicates if analytics is enabled
 */
+ (BOOL)isMonitoringAnalyticsEnabled;

/**
 *  Indicates current state of ranging analytics.
 *
 *  @return flag that indicates if analytics is enabled
 */
+ (BOOL)isRangingAnalyticsEnabled;

#pragma mark - Fetching beacons/nearables informations

/**
 *  Collects all the nearables assigned to your Estimote Cloud account.
 *  Nearables are delivered as NSArray containing ESTNearable objects.
 *
 *  @param completion completion block invoked with fetching is done
 */
- (void)fetchEstimoteNearablesWithCompletion:(ESTArrayCompletionBlock)completion;

/**
 *  Collects all the beacons assigned to your Estimote Cloud account.
 *  Beacons are delivered as NSArray containing ESTBeaconVO objects.
 *
 *  @param completion completion block invoked with fetching is done
 */
- (void)fetchEstimoteBeaconsWithCompletion:(ESTArrayCompletionBlock)completion;

/**
 *  Collects details of particular beacon device stored in Estimote Cloud.
 *  You can use both Mac Address or ProximityUUID:Major:Minor.
 *
 *  @param beaconUID  Identifier of particular device
 *  @param completion completion block invoked with fetching is done
 */
- (void)fetchBeaconDetails:(NSString *)beaconUID completion:(ESTObjectCompletionBlock)completion;

/**
 *  Collects color of particular beacon device stored in Estimote Cloud.
 *  Authorization is not required to access device color.
 *
 *  @param beacon        iBeacon device
 *  @param completion    completion block with NSNumber class object containing ESTColor value.
 */
- (void)fetchColorForBeacon:(CLBeacon *)beacon
                 completion:(ESTObjectCompletionBlock)completion;

/**
 *  Collects color of particular beacon device stored in Estimote Cloud.
 *  Authorization is not required to access device color.
 *
 *  @param proximityUUID iBeacon ProximityUUID of the device
 *  @param major         iBeacon Major of the device
 *  @param minor         iBeacon Minor of the device
 *  @param completion    completion block with NSNumber class object containing ESTColor value.
 */
- (void)fetchColorForBeaconWithProximityUUID:(NSUUID *)proximityUUID
                                       major:(CLBeaconMajorValue)major
                                       minor:(CLBeaconMinorValue)minor
                                  completion:(ESTObjectCompletionBlock)completion;

/**
 *  Collects color of particular beacon device stored in Estimote Cloud. 
 *  Authorization is not required to access device color.
 *
 *  @param macAddress Mac Address of the device
 *  @param completion completion block with NSNumber class object containing ESTColor value.
 */
- (void)fetchColorForBeaconWithMacAddress:(NSString *)macAddress
                                completion:(ESTObjectCompletionBlock)completion;

#pragma mark - Saving beacon location

/**
 *  Assigns provided GPS location to the beacon.
 *
 *  @param location   CLLocation object with latitude and longitude included
 *  @param beacon     CLBeacon to which location should be assigned
 *  @param completion result information with assigned location provided
 */
- (void)assignGPSLocation:(CLLocation *)location
                 toBeacon:(CLBeacon *)beacon
               completion:(ESTObjectCompletionBlock)completion;

/**
 *  Assigns current GPS location to provided beacon.
 *  Location is obtained internally using single CLLocation manger scan.
 *
 *  @param beacon beacon to which location should be assigned
 *  @param completion completion block with assigned location provided
 */
- (void)assignCurrentGPSLocationToBeacon:(CLBeacon *)beacon
                              completion:(ESTObjectCompletionBlock)completion;

#pragma mark - Bulk Updater

/**
 *  Registers device in Estimote Cloud to enable Estimote Remote Beacon Management.
 *
 *  @param deviceToken token of the device received from iOS
 *  @param completion  completion block
 */
- (void)registerDeviceForRemoteManagement:(NSData *)deviceToken
                               completion:(ESTCompletionBlock)completion;

/**
 *  Allows to fetch all pending settings applied to the beacons in Estimote.
 *  Array returned in completion block can be used directly by ESTBulkUpdater class.
 *
 *  @param completion completion block returning Array of ESTBeaconUpdateInfo object
 */
- (void)fetchPendingBeaconsSettingsWithCompletion:(ESTArrayCompletionBlock)completion;


@end
