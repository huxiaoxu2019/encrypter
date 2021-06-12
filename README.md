# encrypter

You could use this simple tool to encrypt any file. The theory of encrypting is using symmetric encryption method, just `xor` between the data and the key you defined in the source file.

So, you could encrypt and decrypt one file as the same way. The usages are as follow(encrypter is the binary name):

Encrypt one file
```
encypter original_file_name encrypted_file_name
```

Decrypt one file

```
encypter encrypted_file_name original_file_name
```
