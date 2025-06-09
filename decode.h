#include<stdio.h>
#ifndef DECODE_H
#define DECODE_H
#include "types.h"
typedef struct _DecodeInfo
{
            char *out_image_fname;
	            FILE *fptr_out_image;
		            char *decode_msg_fname;
			            FILE *fptr_decode_msg;
}DecodeInfo;


Status do_decoding(DecodeInfo *decInfo);
Status Open_files(DecodeInfo *decInfo);
Status decode_magic_string(char *magic_string,DecodeInfo *decInfo);
Status decode_size_lsb(char *buffer);
Status decode_byte_lsb(char *buffer);
Status decode_secret_file_ext(DecodeInfo *decInfo);
Status decode_secret_file(DecodeInfo *decInfo);
#endif
