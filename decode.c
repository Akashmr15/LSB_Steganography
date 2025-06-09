#include<stdio.h>
#include<string.h>
#include"types.h"
#include"decode.h"
#include"common.h"
#include<unistd.h>
Status do_decoding(DecodeInfo *decInfo)
{
    if(Open_files(decInfo) == e_success)
    {
	printf(" * Files opened successfully\n");
    }
    else
    {
	printf(" ->ERROR: Unable to open the file\n");
	return e_failure;
    }
    if(decode_magic_string(MAGIC_STRING,decInfo) == e_success)
    {
	printf(" * Magic_string founded go ahead\n");
    }
    else
    {
	printf(" -> ERROR: Magic_string not founded\n");
	return e_failure;
    }
    if(decode_secret_file_ext(decInfo) == e_success)
    {
	printf(" * Secret file extension size founded,go ahead\n");
	printf(" * Secret file extension founded,go ahead\n");
	decInfo -> fptr_decode_msg = fopen(decInfo -> decode_msg_fname,"w");
	if( decInfo -> fptr_decode_msg != NULL)
	{
	    printf(" * Output secret msg file opened successfully\n");
	}
	else
	{
	    printf(" -> ERROR : Output secret file not opened\n");
	}


    }
    else
    {
	printf(" -> ERROR : secret file extension is not founded\n");
	return e_failure;
    }
    if(decode_secret_file(decInfo) == e_success)
    {
	printf(" ------- Secter message are successfully decoded -------- \n");
	printf(" *** Messege are stored in %s file\n",decInfo -> decode_msg_fname);
    }
    else
    {
	printf(" -> ERROR : secret file are not decoded successfully\n");
	return e_failure;
    }

    return e_success;
}
Status Open_files(DecodeInfo *decInfo)
{
    sleep(1);
    printf("-> Openening the encoded image file\n");
    decInfo -> fptr_out_image = fopen(decInfo -> out_image_fname,"r");
    if( decInfo -> fptr_out_image == NULL)
    {
	return e_failure;
    }
    else
	return e_success;
}
Status decode_magic_string(char *magic_string,DecodeInfo *decInfo)
{
    fseek(decInfo -> fptr_out_image,54,SEEK_SET);
    char buffer[32];
    fread(buffer,32,1,decInfo -> fptr_out_image);
    int len = strlen(magic_string);
    int res= decode_size_lsb(buffer);
    //      printf("len = %d\n",len);
    //      printf("res len  = %d\n",res);
    if(len == res)
    {
	printf(" * Magic string length is same\n");
    }
    else
    {
	printf(" * Magic string length is not same\n");
	return e_failure;
    }
    char decode_string[len+1];
    for(int i=0;i<len;i++)
    {
	char buffer[8];
	fread(buffer,8,1,decInfo -> fptr_out_image);
	decode_string[i] = decode_byte_lsb(buffer);
    }
    decode_string[len] = '\0';
    //      printf("%s\n",decode_string);
    return e_success;
}
Status decode_size_lsb(char *buffer)
{
    int len=0;
    for(int i=0;i<32;i++)
    {
	len =len | ((buffer[i] & 1) <<(31 -i));
    }
    return len;
}
Status decode_byte_lsb(char *buffer)
{
    char ch=0;
    for(int i=0;i<8;i++)
    {
	ch = ch | ((buffer[i] & 1) << (7-i));
    }
    return ch;
}
Status decode_secret_file_ext(DecodeInfo *decInfo)
{
    //      for decoding secret file length
    char buffer[32];
    fread(buffer,1,32,decInfo -> fptr_out_image);
    int res = decode_size_lsb(buffer);
    //      printf(" sec = %d\n",res);
    //      for decode secret file extension
    char decode_ext[res+1];
    for(int i =0;i<res;i++)
    {
	char buffer[8];
	fread(buffer,1,8,decInfo -> fptr_out_image);
	decode_ext[i] = decode_byte_lsb(buffer);
    }
    decode_ext[res] = '\0';
    //      printf("ext = %s\n",decode_ext);
    //      for merge the secret file extension in output file;
    //      printf("%s\n",decInfo -> decode_msg_fname);
          strcat(decInfo -> decode_msg_fname,decode_ext);
    //      printf("%s\n",decInfo -> decode_msg_fname);
    return e_success;
}
Status decode_secret_file(DecodeInfo * decInfo)
{
    //      for secret file data len
    char buffer[32];
    fread(buffer,1,32,decInfo -> fptr_out_image);
    int res = decode_size_lsb(buffer);
    //      printf("%d\n",res);
    //      for decode secret file data
    char secret_msg[res+1];
    for(int i =0;i<res;i++)
    {
	char buffer[8];
	fread(buffer,1,8,decInfo -> fptr_out_image);
	secret_msg[i] = decode_byte_lsb(buffer);
    }
    secret_msg[res] = '\0';
    fwrite(secret_msg,res,1,decInfo -> fptr_decode_msg);
    return e_success;

}
