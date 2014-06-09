//
//  URLDownload.m
//  CoreSNG
//
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import "URLDownload.h"

@implementation URLDownload

@synthesize recvData = recvData_;
@synthesize dataLength = dataLength_;
@synthesize isError = isError_;

- (id)initWithRequest:(NSURLRequest *)_req delegate:(id<URLDownloadDeleagte, NSObject>)_dg
{
	self = [super init];
	if (self) {
		request			= [_req retain];
		delegate		= [_dg retain];
		con = [[NSURLConnection alloc] initWithRequest:request delegate:self];
		self.recvData	= [NSMutableData data];
		dataLength_		= NSURLResponseUnknownLength;
		isError_		= FALSE;
	}
	return self;
}

- (void)dealloc {
	[request release];
	[delegate release];
	[con release];
	[recvData_ release];
	//self.recvData = nil;
	[super dealloc];
}

- (void)cancel {
	[con cancel];
}

// NSURLConnection delegate
// 通信開始
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
	NSHTTPURLResponse *hres		= (NSHTTPURLResponse *)response;
	//int statusCode				= [hres statusCode];
	dataLength_					= [hres expectedContentLength];
	//NSLog(@" ==== dataLength_ %lld ", dataLength_);
	//if( statusCode == 200 )
	//if( 200 <= statusCode && statusCode < 400 )
	//{
	//	// return TRUE;
	//} else {
	//	isError_				= TRUE;	// ステータスのエラーが一つでもあったらフラグを立てておく
	//}
	if ([delegate respondsToSelector:@selector(download: didReceiveResponse:)]){
		[delegate download:self didReceiveResponse:response];
	}
}

// 通信失敗
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
#ifdef DEBUG
	NSLog(@"connection  didFailWithError %@", [error localizedDescription]);
#endif
	isError_				= TRUE;
	if ([delegate respondsToSelector:@selector(download: didFailWithError:)]){
		[delegate download:self didFailWithError:error];
	}
}

// 受信処理
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
	@try {
		[self.recvData appendData:data];
		//NSLog(@" <========= connection ====> size = %d ", [self.recvData length]);
		if ([delegate respondsToSelector:@selector(download: didReceiveDataOfLength:)]){
			[delegate download:self didReceiveDataOfLength:[data length]];
		}
	}
	@catch (NSException * e) {
#ifdef DEBUG
		NSLog(@"connection  didReceiveData %@", [e reason]);
#endif
		[connection cancel];
		isError_				= TRUE;
		[delegate download:self didCancelBecauseOf:e];
	}
}
// 通信終了処理
- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
	if( !isError_ ){
		if( dataLength_ != NSURLResponseUnknownLength ){
			if( dataLength_ != (int64_t)[self.recvData length] ){
				isError_		= TRUE;
#ifdef DEBUG
				NSLog(@" connectionDidFinishLoading date length ERROR headLen = %lld  recvDataLen = %lld ", dataLength_, (int64_t)[self.recvData length]);
#endif
			}
		}
	}
	[delegate downloadDidFinish:self];
}


@end
