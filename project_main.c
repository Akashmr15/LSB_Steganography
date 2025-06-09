#include<stdio.h>
#include<stdlib.h>
#include"encode.h"
#include"common.h"
#include<string.h>
#include"types.h"
#include"decode.h"
OperationType check_operation(char argv[]);
Status validate(int argc,char argv[]);
Status decode_validate(int argc,char argv[]);
int main(int argc,char *argv[])
{
    if(argc >0)
    {
	if(check_operation(argv[1]) == e_encode)
	{
	    if(validate(argc,argv[2]) == e_success)
	    {
		printf("Command line argument + BMP validation successfull\n");
		printf("------------------\n");
		printf("Encoding started\n");
		printf("------------------\n");
		EncodeInfo encInfo;
		encInfo.src_image_fname=argv[2];
		encInfo.secret_fname=argv[3];
		if(argv[4] != NULL)
		{
		    encInfo.stego_image_fname=argv[4];
		}
		else
		{
		    encInfo.stego_image_fname="output.bmp";
		}
		if(do_encoding(&encInfo) == e_success)
		{
		    printf("Encoding is success\n");
		}
		else
		{
		    printf("Encoding is unsuccess\n");
		}
	    }
	    else
	    {
		printf("Insufficient comand line argument (or) BMP file verification is unsuccess\n");
		printf("Enter like --> ./a.out -e beatiful.bmb sectret.txt output.bmp(optional)\n");
		printf("CLA --> 4 mandatory\n");
	    }


	}
	else if(check_operation(argv[1])== e_decode)
	{
	    if(decode_validate(argc,argv[2]) == e_success)
	    {
		printf("Command line argument + BMP validation successfull\n");
		printf("---------------------\n");
		printf("Decoding is started\n");
		printf("---------------------\n");
		DecodeInfo decInfo;
		decInfo.out_image_fname = argv[2];
		if(argv[3] != NULL)
		{
		    decInfo.decode_msg_fname = malloc(15);
		    decInfo.decode_msg_fname = argv[3];
		}
		else
		{
		    decInfo.decode_msg_fname = malloc(15);
		    strcpy(decInfo.decode_msg_fname,"decoded_msg");
		}
		if(do_decoding(&decInfo) == e_success)
		{
		    printf("Decoding is successful\n");
		}
		else
		{
		    printf("Decoding is unsuccessful\n");
		}
	    }

	    else
	    {
		printf("Insufficient comand line argument (or) BMP file verification is unsuccess\n");
		printf("Enter like --> ./a.out -d output.bmp output(optional)\n");
		printf("CLA --> 3mandatory\n");
	    }
	}
    }
    else
	printf("ERROR : Invalid input enter the sufficient arguments\n");
}
Status validate(int argc,char argv[])
{
    if(argc == 4 || argc == 5 )
    {
	if(strstr(argv,".bmp") == NULL)
	{
	    return e_failure;
	}
	else if(!strcmp(strstr(argv,".bmp"),".bmp"))
	{
	    return e_success;

	}
	else
	{
	    return e_failure;
	}
    }
    else
    {
	return e_failure;
    }
}
OperationType check_operation(char argv[])
{
    if(!strcmp(argv,"-e"))
    {
	return e_encode;
    }
    else if (!strcmp(argv,"-d"))
    {
	return e_decode;
    }
    else
	return e_unsupported;
}
Status decode_validate(int argc,char argv[])
{
    if( argc == 3 || argc == 4)
    {
	if(strstr(argv,".bmp") == NULL)
	{
	    return e_failure;
	}
	else if(!strcmp(strstr(argv,".bmp"),".bmp"))
	{
	    return e_success;
	}
	else
	{
	    return e_failure;
	}
    }
}
