//
//  NSDataCrypt.m
//  Roulette
//
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import "NSDataCrypt.h"

#import <CommonCrypto/CommonCryptor.h>
#import <CommonCrypto/CommonDigest.h>

@implementation NSData (Crypt)

@class NSString; 

static void getHash(NSData* src, const NSString* macKey, unsigned char* result) {
	NSMutableData* data = [[NSMutableData alloc] init];//]WithLength:[macKey length] + [src length] + 1];
	[data setData:[macKey dataUsingEncoding:NSUTF8StringEncoding]];
	[data appendData:[@" " dataUsingEncoding:NSUTF8StringEncoding]];
	[data appendData:src];
	
	int bytesLen = [data length];
	const char* bytes = [data mutableBytes];
	unsigned char sha[CC_SHA1_DIGEST_LENGTH];
	CC_SHA1(bytes, bytesLen, sha);

	const char* macKeyBytes = [macKey UTF8String];
	int macKeyBytesLen = strlen(macKeyBytes);
	
	int bytes2len = macKeyBytesLen + CC_SHA1_DIGEST_LENGTH;
	char* bytes2 = malloc(bytes2len);
	memcpy(bytes2, macKeyBytes, macKeyBytesLen);
	memcpy(&bytes2[macKeyBytesLen], sha, CC_SHA1_DIGEST_LENGTH);
	
	CC_SHA1(bytes2, bytes2len, result);

	free(bytes2);
	[data release];
}

- (NSData*) encryptByAESAndHash:(const NSString*)aesKey macKey:(const NSString*)macKey
{
	unsigned char* hash = malloc(CC_SHA1_DIGEST_LENGTH);
	getHash(self, macKey, hash);
	NSMutableData* temp = [[NSMutableData alloc] init];
	[temp appendBytes:hash length:CC_SHA1_DIGEST_LENGTH];
	[temp appendBytes:[self bytes] length:[self length]];
	
	NSData* encData = [temp AES256EncryptWithKey:aesKey];
	
	free(hash);
	[temp release];
	return encData;
}	

- (NSData*) decryptByAESAndHash:(const NSString*)aesKey macKey:(const NSString*)macKey
{
	NSData* decData = [self AES256DecryptWithKey:aesKey];
	if (decData == nil) {
		return nil;
	}
	
	int bodyLen = [decData length] - CC_SHA1_DIGEST_LENGTH;
	NSRange range;
	
	range.location = 0;
	range.length = CC_SHA1_DIGEST_LENGTH;
	char hash[CC_SHA1_DIGEST_LENGTH];
	[decData getBytes:hash range:range];

	range.location = CC_SHA1_DIGEST_LENGTH;
	range.length = bodyLen;	
	char* body = malloc(bodyLen);
	[decData getBytes:body range:range];
	
	NSData* bodyData = [NSData dataWithBytesNoCopy:body length:bodyLen];
	unsigned char compare[CC_SHA1_DIGEST_LENGTH];
	getHash(bodyData, macKey, compare);
	
	if (0 != memcmp(hash, compare, CC_SHA1_DIGEST_LENGTH)) {
		NSLog(@"hash check failed");
		abort();
	}

	return bodyData;
}


- (NSData *)AES256EncryptWithKey:(const NSString *)key
{
//	char keyPtr[kCCKeySizeAES256+1];
	char keyPtr[kCCKeySizeAES128+1];
	bzero(keyPtr, sizeof(keyPtr));
	
	[key getCString:keyPtr maxLength:sizeof(keyPtr) encoding:NSUTF8StringEncoding];
	
	NSUInteger dataLength = [self length];
	
	size_t bufferSize = dataLength + kCCBlockSizeAES128;
	void *buffer = malloc(bufferSize);
	
	size_t numBytesEncrypted = 0;
	CCCryptorStatus cryptStatus = CCCrypt(kCCEncrypt, kCCAlgorithmAES128,	   
										  kCCOptionPKCS7Padding | kCCOptionECBMode,
										  keyPtr, kCCBlockSizeAES128,
										  NULL,
										  [self bytes], dataLength,
										  buffer, bufferSize,
										  &numBytesEncrypted);
	if (cryptStatus == kCCSuccess) {
		return [NSData dataWithBytesNoCopy:buffer length:numBytesEncrypted];
	}
	free(buffer);
	return nil;
}

- (NSData *)AES256DecryptWithKey:(const NSString *)key
{
//	char keyPtr[kCCKeySizeAES256+1];
	char keyPtr[kCCKeySizeAES128+1];
	bzero(keyPtr, sizeof(keyPtr));
	
	[key getCString:keyPtr maxLength:sizeof(keyPtr) encoding:NSUTF8StringEncoding];
	
	NSUInteger dataLength = [self length];
	
	size_t bufferSize = dataLength + kCCBlockSizeAES128;
	void *buffer = malloc(bufferSize);
	
	size_t numBytesDecrypted = 0;
	CCCryptorStatus cryptStatus = CCCrypt(kCCDecrypt, kCCAlgorithmAES128, 
										  kCCOptionPKCS7Padding | kCCOptionECBMode,
										  keyPtr, kCCBlockSizeAES128,
										  NULL,
										  [self bytes], dataLength,
										  buffer, bufferSize,
										  &numBytesDecrypted);
	
	if (cryptStatus == kCCSuccess) {
		return [NSData dataWithBytesNoCopy:buffer length:numBytesDecrypted];
	}
	free(buffer);
	return nil;
}
@end