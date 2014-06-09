//
//  NSDataCrypt.h
//  Roulette
//
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

@interface NSData (Crypt) 

- (NSData*) encryptByAESAndHash:(const NSString*)aesKey macKey:(const NSString*)macKey;
- (NSData*) decryptByAESAndHash:(const NSString*)aesKey macKey:(const NSString*)macKey;

- (NSData *)AES256EncryptWithKey:(const NSString *)key;
- (NSData *)AES256DecryptWithKey:(const NSString *)key;


@end
