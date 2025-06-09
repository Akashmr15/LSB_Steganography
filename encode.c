#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"
Status do_encoding(EncodeInfo *encInfo)
{
    if(open_files(encInfo) == e_success)
    {
	printf("file open is successfull\n");
    }
    else
    {
	printf("file open is unsuccessfull\n");
	return e_failure;
    }
    if(copy_bmp_header(encInfo) == e_success)
    {
	printf("BMP header copy is successfull\n");
	printf("BMP size is = %ld\n",ftell(encInfo->fptr_stego_image));
    }
    else
    {
	printf("BMP header copy is unsuccessfull\n");
	return e_failure;
    }
    if(encode_magic_string(MAGIC_STRING,encInfo) == e_success)
    {
	printf("Magic string encoding is successfull\n");
	printf("Magic string size is = %ld\n",ftell(encInfo->fptr_stego_image));
    }
    else
    {
	printf("Magic string coding is unsuccessfull\n");
	return e_failure;
    }
    if(encode_secret_file_extn(strstr(encInfo->secret_fname,".txt"),encInfo) == e_success)
    {
	printf("Encode secret file extension is successfull\n");
	printf("Encode secret file size is = %ld\n",ftell(encInfo->fptr_stego_image));
    }
    else
    {
	printf("Encode secret file extension is unsuccessfull\n");
	return e_failure;
    }
    if(encode_secret_file_data(encInfo) == e_success)
    {
	printf("Encoding secret file data is successfull\n");
	printf("Encoding secret file size = %ld\n",ftell(encInfo->fptr_stego_image));
    }
    else
    {
	printf("Encoding secert file data is unsuccessfull\n");
	return e_failure;
    }
    if(copy_remaining_img_data(encInfo) == e_success)
    {
	printf("copy remaining data is completed\n");
    }
    else
    {
	printf("copy remaining data is unsuccessfull\n");
	return e_failure;
    }
    return e_success;
}
Status open_files(EncodeInfo *encInfo)
{
    encInfo->fptr_src_image=fopen(encInfo->src_image_fname,"r");
    if(encInfo->fptr_src_image == NULL)
    {
	return e_failure;
    }
    encInfo->fptr_secret=fopen(encInfo->secret_fname,"r");
    if(encInfo->fptr_secret == NULL)
    {
	return e_failure;
    }
    encInfo->fptr_stego_image=fopen(encInfo->stego_image_fname,"w");
    if(encInfo->fptr_stego_image == NULL)
    {
	return e_failure;
    }
    else
    {
	return e_success;
    }
}
Status copy_bmp_header(EncodeInfo *encInfo)
{
    char buffer[54];
    fread(buffer,1,54,encInfo->fptr_src_image);
    fwrite(buffer,1,54,encInfo->fptr_stego_image);
    return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    int len=strlen(magic_string);
    char buffer[32];
    fread(buffer,1,32,encInfo->fptr_src_image);
    encode_size_lsbi(len,buffer);
    fwrite(buffer,1,32,encInfo->fptr_stego_image);
    printf("Encoding magic string length is done\n");
    for(int i=0;i<len;i++)
    {
	char buffer[8];
	fread(buffer,1,8,encInfo->fptr_src_image);
	encode_size_lsbc(magic_string[i],buffer);
	fwrite(buffer,1,8,encInfo->fptr_stego_image);
    }
    return e_success;
}
Status encode_size_lsbc(char data,char *image_buffer)
{
    int j=0;
    for(int i=7;i>=0;i--)
    {
	if(data & (1<<i))
	{
	    image_buffer[j] = image_buffer[j] | 1;
	}
	else
	{
	    image_buffer[j] = image_buffer[j] & (~1);
	}
	j++;
    }
    return e_success;
}
Status encode_secret_file_extn(const char *file_extn,EncodeInfo *encInfo)
{
    int len=strlen(file_extn);
    char buffer[32];
    fread(buffer,1,32,encInfo->fptr_src_image);
    encode_size_lsbi(len,buffer);
    fwrite(buffer,1,32,encInfo->fptr_stego_image);
    for(int i=0;i<len;i++)
    {
	char buffer[8];
	fread(buffer,1,8,encInfo->fptr_src_image);
	encode_size_lsbc(file_extn[i],buffer);
	fwrite(buffer,1,8,encInfo->fptr_stego_image);
    }
    return e_success;
}
Status encode_size_lsbi(int len,char *buffer)
{
    int j=0;
    for(int i=31;i>=0;i--)
    {
	if(len & (1<<i))
	{
	    buffer[j] = buffer[j] | 1;
	}
	else
	{
	    buffer[j] = buffer[j] & (~1);
	}
	j++;
    }
    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    //for encoding size
    fseek(encInfo->fptr_secret,0,SEEK_END);
    int len = ftell(encInfo->fptr_secret)-1;
    char buffer[32];
    fread(buffer,1,32,encInfo->fptr_src_image);
    encode_size_lsbi(len,buffer);
    fwrite(buffer,1,32,encInfo->fptr_stego_image);
    //printf("%d\n",len);
    //for encoding data;
    rewind(encInfo->fptr_secret);
    for(int i=0;i<len;i++)
    {
	char buffer[8];
	fread(buffer,1,8,encInfo->fptr_src_image);
	encode_size_lsbc(fgetc(encInfo->fptr_secret),buffer);
	fwrite(buffer,1,8,encInfo->fptr_stego_image);
    }
    return e_success;
}
Status copy_remaining_img_data(EncodeInfo *encInfo)
{
    char ch;
    while(fread(&ch,1,1,encInfo->fptr_src_image))
    {
	fwrite(&ch,1,1,encInfo->fptr_stego_image);
    }
    return e_success;
}
