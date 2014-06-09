//
//  NSDataCrypt.h
//  Roulette
//
//  Created by JP10553 on 11/04/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

@interface NSData (Crypt) 

- (NSData*) encryptByAESAndHash:(const NSString*)aesKey macKey:(const NSString*)macKey;
- (NSData*) decryptByAESAndHash:(const NSString*)aesKey macKey:(const NSString*)macKey;

- (NSData *)AES256EncryptWithKey:(const NSString *)key;
- (NSData *)AES256DecryptWithKey:(const NSString *)key;


@end
