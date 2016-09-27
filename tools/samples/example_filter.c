//---------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ZQ_ECG_filter.h"
int do_set(char *arg)
{
    int result = 0;
    int arg_val = 0;
    arg_val = atoi(arg);
    switch(arg_val)
    {
        case 0:
            result |= ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_HPASS, ZQ_ECG_FILT_VAL_NONE);
            result |= ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_TRAP, ZQ_ECG_FILT_VAL_NONE);
            result |= ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_NONE);
            break;
        case 5:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_HPASS, ZQ_ECG_FILT_VAL_HPASS_005);
            break;
        case 3:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_HPASS, ZQ_ECG_FILT_VAL_HPASS_03);
            break;
        case 6:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_HPASS, ZQ_ECG_FILT_VAL_HPASS_06);
            break;
            
        case 50:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_TRAP, ZQ_ECG_FILT_VAL_TRAP_50);
            break;
        case 60:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_TRAP, ZQ_ECG_FILT_VAL_TRAP_60);
            break;
            
        case 25:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_25);
            break;
        case 35:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_35);
            break;
        case 45:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_45);
            break;
        case 75:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_75);
            break;
        case 100:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_100);
            break;
        case 150:
            result = ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_150);
            break;
        default:
            printf("%s enter_default!\n"__FUNCTION__);
            result = -1;
    }
    return result;
}
int do_clear(char *arg)
{
    int result = 0;
    int arg_val = 0;
    arg_val = atoi(arg);
    
    result = ZQ_ECG_FILTER_clear_filter_ch(arg_val);
    
    return result;
}

int TYPE_129X_2_uv(unsigned char * in)
{
	int result = (signed char)in[0];
    result = ((result<<16)|(((unsigned int)in[1])<<8)|((unsigned int)in[2]));
    return result*2/25;
    //return result;
}
int do_do(char *arg)
{
    short in_val[12],out_val[12];
	char str[32] = {0};
	unsigned char readdate[18*3] = {0};
    int value = 0;
	int loop_count = 0;
    FILE *fp_read, *fp_write;
    
    fp_read= fopen(arg,"rb+");
    if (NULL == fp_read)
	{		
		printf("\n Can't open %s\n", arg);
		return -1;
	}    
    strncpy(str, arg, 30);
    strncat(str, "_f", 2);
    
    fp_write= fopen(str,"wb");
    if (NULL == fp_write)
	{		
		printf("\n Can't open %s\n", str);
		return -1;
	}
    if(-1 == fseek(fp_read,4648*3*18-1,SEEK_SET))
		    //if(-1 == fseek(fp_read,3*18-1,SEEK_SET))
    {
        printf("seek error\n");
        fclose(fp_read);
		return -1;
    }
    while(18 == fread((void *)readdate,3,18,fp_read))
    {
        
		if (4000 == loop_count)
		{
			printf("620\n");
		}

        in_val[0] = TYPE_129X_2_uv(&readdate[2*3]);
        in_val[1] = TYPE_129X_2_uv(&readdate[3*3]);
        in_val[2] = TYPE_129X_2_uv(&readdate[4*3]);
        in_val[3] = TYPE_129X_2_uv(&readdate[5*3]);
        in_val[4] = TYPE_129X_2_uv(&readdate[6*3]);
        in_val[5] = TYPE_129X_2_uv(&readdate[7*3]);
        in_val[6] = TYPE_129X_2_uv(&readdate[8*3]);
        in_val[7] = TYPE_129X_2_uv(&readdate[9*3]);
        out_val[0] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[0],ZQ_ECG_FILT_LEAD_I);        
#if 1
        out_val[1] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[1],ZQ_ECG_FILT_LEAD_II);    
        out_val[6] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[2],ZQ_ECG_FILT_LEAD_V1);   
        out_val[7] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[3],ZQ_ECG_FILT_LEAD_V2);        
        out_val[8] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[4],ZQ_ECG_FILT_LEAD_V3);        
        out_val[9] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[5],ZQ_ECG_FILT_LEAD_V4);        
#if 1
        out_val[10] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[6],ZQ_ECG_FILT_LEAD_V5);  
        out_val[11] = (short)ZQ_ECG_FILTER_do_filter((int)in_val[7],ZQ_ECG_FILT_LEAD_V6);      
#endif /* if 0 end */
#endif /* if 0 end */

        fwrite((void *)&out_val, 2, 12, fp_write);   
		loop_count++;
    }
   
    fclose(fp_write);
    fclose(fp_read);
    return 0;
}
int main(int argc, char **argv)
{
    int result = 0;    
    char arg1[20] = {0};
    char arg2[20] = {0};
    
    result = ZQ_ECG_FILTER_init();
    for(;;)
    {
        printf("\ninput command:[cmd] [arg]\n");
        printf("cmd: set, arg: 005,03,06,25,35,45,75,100,150,50,60\n");
        printf("cmd: set, arg: 0 to clear filt set\n");
        printf("cmd: clear, arg: 0~7\n");
        printf("cmd: do, arg: filename\n>");
        scanf("%s%s",arg1,arg2);
        printf("command is:%s<->%s\n",arg1,arg2);
        if(0 == strncmp(arg1,"set",strlen("set")))
        {
            result = do_set(arg2);
        }
        else if(0 == strncmp(arg1,"clear",strlen("clear")))
        {
            result = do_clear(arg2);
        }
        else if(0 == strncmp(arg1,"do",strlen("do")))
        {
            result = do_do(arg2);
        }
        else
        {
            printf("command error!\n");
        }
    }
    return result;
}

