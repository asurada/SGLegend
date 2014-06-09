//
//  URLDownload.h
//  CoreSNG
//
//  Created by JP10553 on 11/04/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * ファイルをダウンロードするクラスです。
 */
@class URLDownload;

@protocol URLDownloadDeleagte
- (void)downloadDidFinish:(URLDownload *)download;
- (void)download:(URLDownload *)download didCancelBecauseOf:(NSException *)exception;
- (void)download:(URLDownload *)download didFailWithError:(NSError *)error;
@optional
- (void)download:(URLDownload *)download didReceiveDataOfLength:(NSUInteger)length;		// 
- (void)download:(URLDownload *)download didReceiveResponse:(NSURLResponse *)response;	// URLリクエストの戻り

@end

@interface URLDownload : NSObject {
	id <URLDownloadDeleagte, NSObject> delegate;
	NSURLRequest *request;
	NSURLConnection *con;
	
	NSMutableData* recvData_;
	int64_t dataLength_;
	BOOL isError_;
}
@property (readwrite, retain) NSMutableData* recvData;
@property (readwrite) int64_t dataLength;
@property (readwrite) BOOL isError;

- (id)initWithRequest:(NSURLRequest *)_req delegate:(id<URLDownloadDeleagte, NSObject>)_dg;
//- (void)dealloc;
- (void)cancel;

// NSURLConnection delegate
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
@end
