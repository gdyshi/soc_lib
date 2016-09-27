/******************************************************************************
 * ZQ_ECG_filter.c
 * 
 * Copyright 2012 Wuhan Zoncare Electronics Co.,Ltd.
 * 
 * Description:  
 * - This file implements the follow functions:
 * - 
 * 
 * Author: gdyshi 
 * Date:  11:48am, 15.May.2014
 * Modification History
 * --------------------
 * Date              Modifier    Problem N.O.                 Description
 * --------------------
 ******************************************************************************/
//---------------------------------------------------------------------------
#ifndef __UTEST
#define GDYSHI_LIST_LOG
#endif /* __UTEST */
#include "gdyshi_includes.h"
#include "gdyshi_filter.h"
#include "gdyshi_filter_internal.h"
#include "gdyshi_filter_parm.h"

ZQ_ECG_filt_arg_t * current_filt_array[MAX_FILT_NUM] = {0};/* 要执行的滤波序列，定义指针的数组 */
/* 高通滤波缓冲 */
filt_temp_t hpass_filt_in_buffer[MAX_FILT_LEAD_NUM][2 * MAX_HPASS_NUM_NUM+1] = {0};
filt_temp_t hpass_filt_out_buffer[MAX_FILT_LEAD_NUM][2 * MAX_HPASS_DEN_NUM] = {0};
/* 低通滤波缓冲 */
filt_temp_t lpass_filt_in_buffer[MAX_FILT_LEAD_NUM][2 * MAX_LPASS_NUM_NUM+3] = {0};
filt_temp_t lpass_filt_out_buffer[MAX_FILT_LEAD_NUM][2 * MAX_LPASS_DEN_NUM] = {0};
/* 陷波滤波缓冲 */
filt_temp_t trap_filt_in_buffer[MAX_FILT_LEAD_NUM][2 * MAX_TRAP_NUM_NUM+5] = {0};
filt_temp_t trap_filt_out_buffer[MAX_FILT_LEAD_NUM][2 * MAX_TRAP_DEN_NUM] = {0};
#ifdef FILT_USE_EMG
/* 肌电滤波缓冲 */
filt_temp_t emg_filt_in_buffer[MAX_FILT_LEAD_NUM][2 * MAX_EMG_NUM_NUM+7] = {0};
filt_temp_t emg_filt_out_buffer[MAX_FILT_LEAD_NUM][2 * MAX_EMG_DEN_NUM] = {0};
#endif /* FILT_USE_EMG */

ZQ_ECG_filt_buf_t filt_buffer[MAX_FILT_NUM] = {0};

//---所有全局函数---------------------------------------------------------------------------
/******************************************************************************
 * Function:     do_filt_type_a
 * Description:  顺序计算的滤波
 * Input:        unsigned short lead_num， filt_temp_t in_data  
 * Output:       none
 * Return:       filt_temp_t 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
filt_temp_t do_filt_type_a(filt_temp_t * in_buf, filt_temp_t * out_buf, ZQ_ECG_filt_arg_t * filt_arg)
{
    int i = 0;
    int loop_num = 0;/* 循环次数 */
    int num_loop_down = 0;/* 分子循环下限 */
    int num_loop_up = 0;/* 分子循环上限 */
    double temp_result = 0;/* 中间结果 */
    filt_temp_t * temp_buf = NULL;        
    filt_type_a_par_t * par_p = (filt_type_a_par_t *)filt_arg->ZQ_ECG_filt_type_par;
    filt_temp_t * num_den_data_p = NULL;
    /* 函数表达式
        DEN_NUM                      NUM_NUM          
        -----                         -----                             
        \                             \                                   
         \                             \                              
         /                             /                                 
        /     denData(i)*output(i) =  /     numData(i)*input(i)       
        -----                         -----                          
         i=0                          i=0                             
    */
    
    /* 分子计算
                NUM_NUM
                ----- 
                \
                 \
                 /
                /     numData(i)*input(i)   .其中numData为倒序排列
     result =   -----
                i=0            
    */
    loop_num = par_p->num_num - par_p->zero_num/2;
    num_den_data_p = par_p->numData;
    temp_buf = in_buf;
    for (i=par_p->zero_num/2; i<loop_num; i++)
    {
        //temp_result += (*num_den_data_p++) * (*temp_buf++);
        temp_result += (double)num_den_data_p[i] * temp_buf[i];
    }
#if 0
    num_loop_down = filt_arg.zero_num;
    num_loop_up = filt_arg.num_num - num_loop_down;
    for (i=num_loop_down; i<num_loop_up; i++)
    {
        //temp_result += (*num_den_data_p++) * (*temp_buf++);
        temp_result += num_den_data_p[i] * temp_buf[i];
    }
#endif /* if 0 end*/
    
    /* 分母计算
                DEN_NUM
                ----- 
                \
                 \
                 /
                /     denData(i)*output(i)   .其中denData为倒序排列
     result -=  -----
                i=0            
    */
    loop_num = par_p->den_num;
    num_den_data_p = par_p->denData;
    temp_buf = out_buf;
    /* 分母参数的第一个数据不参与运算 */
    //temp_buf--;
    for (i=1; i<loop_num; i++)
    {
        //temp_result -= (*num_den_data_p++) * (*temp_buf++);
        temp_result -= (double)num_den_data_p[i] * temp_buf[i];
    }
    temp_result /= par_p->denData[0];
    
    return (filt_temp_t)temp_result;
}

/******************************************************************************
 * Function:     do_filt_type_b
 * Description:  跳跃计算的滤波
 * Output:       none
 * Return:       ZQ_ECG_DO_FILT 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
filt_temp_t do_filt_type_b(filt_temp_t * in_buf, filt_temp_t * out_buf, ZQ_ECG_filt_arg_t * filt_arg)
{
    int i = 0;
    int loop_num = 0;/* 循环次数 */
    double temp_result = 0;/* 中间结果 */
    filt_temp_t * temp_buf = NULL;        
    filt_type_b_par_t * par_p = (filt_type_b_par_t *)filt_arg->ZQ_ECG_filt_type_par;
    filt_b_ele_t * par_ele_p = NULL;
    /* 函数表达式
        DEN_NUM                      NUM_NUM          
        -----                         -----                             
        \                             \                                   
         \                             \                              
         /                             /                                 
        /     denData(i)*output(i) =  /     numData(i)*input(i)       
        -----                         -----                          
         i=0                          i=0                             
    */
    
    /* 分子计算
                NUM_NUM
                ----- 
                \
                 \
                 /
                /     numData(i)*input(i)   .其中numData为倒序排列
     result =   -----
                i=0            
    */
    loop_num = par_p->num_num_valid;
    par_ele_p = par_p->numData;
    temp_buf = in_buf;
    for (i=0; i<loop_num; i++)
    {
        temp_result += (double)par_ele_p[i].data * temp_buf[par_ele_p[i].seq-1];
    }
    
    /* 分母计算
                DEN_NUM
                ----- 
                \
                 \
                 /
                /     denData(i)*output(i)   .其中denData为倒序排列
     result -=  -----
                i=0            
    */
    loop_num = par_p->den_num_valid;
    par_ele_p = par_p->denData;
    temp_buf = out_buf;
    /* 分母参数的第一个数据不参与运算 */
    //temp_buf--;
    for (i=1; i<loop_num; i++)
    {        
        temp_result -= (double)par_ele_p[i].data * temp_buf[par_ele_p[i].seq-1];
    }
    temp_result /= par_ele_p[0].data;
    
    return (filt_temp_t)temp_result;
}



/******************************************************************************
 * Function:     print_current_filt_array
 * Description:  打印滤波执行数组
 * Input:        void  
 * Output:       none
 * Return:       static void 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
static void print_current_filt_array(void)
{
    int i = 0;
    printf("current_filt_array:\n");
    for (i=0; i<ARRAY_SIZE(current_filt_array); i++)
    {
        printf("[%d]:",i);
        if (NULL == current_filt_array[i])
        {
            printf("NULL\n");
        }
        else
        {
            printf("%s\n",current_filt_array[i]->name);
        }
    }    
    printf("current_filt_array done!\n");
}
/******************************************************************************
 * Function:     check_comb_filt
 * Description:  检查是否启用梳状滤波器
 * Input:        void  
 * Output:       none
 * Return:       int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
static int check_comb_filt(void)
{
    int result = 0;
    printf("%s\n",__FUNCTION__);
	if (NULL == current_filt_array[FILT_INTERNAL_TYPE_TRAP])
	{
		return result;
	}
    if (0 == strcmp(NAME_FILT_TRAP_50,current_filt_array[FILT_INTERNAL_TYPE_TRAP]->name))
    {
        if (NULL == current_filt_array[FILT_INTERNAL_TYPE_HPASS])
		{
			return result;
		}
		/* 切换到03的梳状滤波器 */
        if (0 == strcmp(NAME_FILT_HPASS_03,current_filt_array[FILT_INTERNAL_TYPE_HPASS]->name))
        {
            printf("change to comb_50_03\n");
            current_filt_array[FILT_INTERNAL_TYPE_TRAP] = &comb_50_03;
            current_filt_array[FILT_INTERNAL_TYPE_HPASS] = NULL;
        }
        /* 切换到06的梳状滤波器 */
        else if (0 == strcmp(NAME_FILT_HPASS_06,current_filt_array[FILT_INTERNAL_TYPE_HPASS]->name))
        {
            printf("change to comb_50_06\n");
            current_filt_array[FILT_INTERNAL_TYPE_TRAP] = &comb_50_06;
            current_filt_array[FILT_INTERNAL_TYPE_HPASS] = NULL;
        }
    }
    
    return result;
}

/******************************************************************************
 * Function:     do_set_hpass_filter
 * Description:  设置高通滤波
 * Input:        unsigned short filter_value  
 * Output:       none
 * Return:       static int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
static int do_set_hpass_filter(unsigned short filter_value)
{
    int result = 0;
    printf("%s:%d\n",__FUNCTION__,filter_value);
    switch(filter_value)
    {
        case ZQ_ECG_FILT_VAL_NONE:
            current_filt_array[FILT_INTERNAL_TYPE_HPASS] = NULL;
            break;
        case ZQ_ECG_FILT_VAL_HPASS_005:
            current_filt_array[FILT_INTERNAL_TYPE_HPASS] = &h_pass_005;
            break;
        case ZQ_ECG_FILT_VAL_HPASS_03:
            current_filt_array[FILT_INTERNAL_TYPE_HPASS] = &h_pass_03;
            break;
        case ZQ_ECG_FILT_VAL_HPASS_06:
            current_filt_array[FILT_INTERNAL_TYPE_HPASS] = &h_pass_06;
            break;
        case ZQ_ECG_FILT_VAL_HPASS_05:
        default:
            printf("%s enter_default!\n",__FUNCTION__);
            result = -1;
    }
    return result;
}

/******************************************************************************
 * Function:     do_set_lpass_filter
 * Description:  设置低通滤波
 * Input:        unsigned short filter_value  
 * Output:       none
 * Return:       static int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
static int do_set_lpass_filter(unsigned short filter_value)
{
    int result = 0;
    printf("%s:%d\n",__FUNCTION__,filter_value);
    switch(filter_value)
    {
        case ZQ_ECG_FILT_VAL_NONE:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = NULL;
            break;
        case ZQ_ECG_FILT_VAL_LPASS_150:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = &l_pass_150;
            break;
        case ZQ_ECG_FILT_VAL_LPASS_100:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = &l_pass_100;
            break;
        case ZQ_ECG_FILT_VAL_LPASS_75:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = &l_pass_75;
            break;
        case ZQ_ECG_FILT_VAL_LPASS_45:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = &l_pass_45;
            break;
        case ZQ_ECG_FILT_VAL_LPASS_35:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = &l_pass_35;
            break;
        case ZQ_ECG_FILT_VAL_LPASS_25:
            current_filt_array[FILT_INTERNAL_TYPE_LPASS] = &l_pass_25;
            break;
        default:
            printf("%s enter_default!\n",__FUNCTION__);
            result = -1;
    }
    return result;
}

/******************************************************************************
 * Function:     do_set_trap_filter
 * Description:  设置陷波
 * Input:        unsigned short filter_value  
 * Output:       none
 * Return:       static int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
static int do_set_trap_filter(unsigned short filter_value)
{
    int result = 0;
    printf("%s:%d\n",__FUNCTION__,filter_value);
    switch(filter_value)
    {
        case ZQ_ECG_FILT_VAL_NONE:
            current_filt_array[FILT_INTERNAL_TYPE_TRAP] = NULL;
            break;
        case ZQ_ECG_FILT_VAL_TRAP_50:
            current_filt_array[FILT_INTERNAL_TYPE_TRAP] = &trap_50;
            break;
        case ZQ_ECG_FILT_VAL_TRAP_60:
            current_filt_array[FILT_INTERNAL_TYPE_TRAP] = &trap_60;
            break;
        default:
            printf("%s enter_default!\n",__FUNCTION__);
            result = -1;
    }
    return result;
}

#ifdef FILT_USE_EMG
/******************************************************************************
 * Function:     do_set_emg_filter
 * Description:  设置肌电滤波
 * Input:        unsigned short filter_value  
 * Output:       none
 * Return:       int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
static int do_set_emg_filter(unsigned short filter_value)
{
    int result = 0;
    printf("%s:%d\n",__FUNCTION__,filter_value);
    switch(filter_value)
    {
        case ZQ_ECG_FILT_VAL_NONE:
        case ZQ_ECG_FILT_VAL_EMG_25:
        case ZQ_ECG_FILT_VAL_EMG_35:
        case ZQ_ECG_FILT_VAL_EMG_45:
            current_filt_array[FILT_INTERNAL_TYPE_EMG] = NULL;
            break;
        default:
            printf("%s enter_default!\n",__FUNCTION__);
            result = -1;
    }
    return result;
}
#endif /* FILT_USE_EMG */


/******************************************************************************
 * Function:     ZQ_ECG_FILTER_init
 * Description:  none
 * Input:        void  
 * Output:       none
 * Return:       int 
 * Author:       gdyshi
 * Date:         2014/5/17
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_init(void)
{
    int result = 0;    
    int i = 0;
    ZQ_ECG_filt_buf_t * filt_buf_p = NULL;
    printf("%s\n",__FUNCTION__);

    /* HPASS滤波缓冲区初始化 */
    filt_buf_p = &filt_buffer[FILT_INTERNAL_TYPE_HPASS];
    
    filt_buf_p->in_buf = hpass_filt_in_buffer;    
    filt_buf_p->in_buf_total_len = sizeof(hpass_filt_in_buffer)/MAX_FILT_LEAD_NUM/sizeof(filt_temp_t);
    filt_buf_p->in_buf_min_cal_len = MAX_HPASS_NUM_NUM;
    for (i=0; i<MAX_FILT_LEAD_NUM; i++)
    {
        filt_buf_p->in_buf_idx[i] = filt_buf_p->in_buf_total_len - filt_buf_p->in_buf_min_cal_len + 1;
    }
    
    filt_buf_p->out_buf = hpass_filt_out_buffer;    
    filt_buf_p->out_buf_total_len = sizeof(hpass_filt_out_buffer)/MAX_FILT_LEAD_NUM/sizeof(filt_temp_t);
    filt_buf_p->out_buf_min_cal_len = MAX_HPASS_DEN_NUM;
    for (i=0; i<MAX_FILT_LEAD_NUM; i++)
    {
        filt_buf_p->out_buf_idx[i] = filt_buf_p->out_buf_total_len - filt_buf_p->out_buf_min_cal_len + 1;
    }
    
    /* LPASS滤波缓冲区初始化 */
    filt_buf_p = &filt_buffer[FILT_INTERNAL_TYPE_LPASS];
    
    filt_buf_p->in_buf = lpass_filt_in_buffer;    
    filt_buf_p->in_buf_total_len = sizeof(lpass_filt_in_buffer)/MAX_FILT_LEAD_NUM/sizeof(filt_temp_t);
    filt_buf_p->in_buf_min_cal_len = MAX_LPASS_NUM_NUM;
    for (i=0; i<MAX_FILT_LEAD_NUM; i++)
    {
        filt_buf_p->in_buf_idx[i] = filt_buf_p->in_buf_total_len - filt_buf_p->in_buf_min_cal_len + 1;
    }
    
    filt_buf_p->out_buf = lpass_filt_out_buffer;    
    filt_buf_p->out_buf_total_len = sizeof(lpass_filt_out_buffer)/MAX_FILT_LEAD_NUM/sizeof(filt_temp_t);
    filt_buf_p->out_buf_min_cal_len = MAX_LPASS_DEN_NUM;
    for (i=0; i<MAX_FILT_LEAD_NUM; i++)
    {
        filt_buf_p->out_buf_idx[i] = filt_buf_p->out_buf_total_len - filt_buf_p->out_buf_min_cal_len + 1;
    }
    
    /* TRAP滤波缓冲区初始化 */
    filt_buf_p = &filt_buffer[FILT_INTERNAL_TYPE_TRAP];
    
    filt_buf_p->in_buf = trap_filt_in_buffer;    
    filt_buf_p->in_buf_total_len = sizeof(trap_filt_in_buffer)/MAX_FILT_LEAD_NUM/sizeof(filt_temp_t);
    filt_buf_p->in_buf_min_cal_len = MAX_TRAP_NUM_NUM;
    for (i=0; i<MAX_FILT_LEAD_NUM; i++)
    {
        filt_buf_p->in_buf_idx[i] = filt_buf_p->in_buf_total_len - filt_buf_p->in_buf_min_cal_len + 1;
    }
    
    filt_buf_p->out_buf = trap_filt_out_buffer;    
    filt_buf_p->out_buf_total_len = sizeof(trap_filt_out_buffer)/MAX_FILT_LEAD_NUM/sizeof(filt_temp_t);
    filt_buf_p->out_buf_min_cal_len = MAX_TRAP_DEN_NUM;
    for (i=0; i<MAX_FILT_LEAD_NUM; i++)
    {
        filt_buf_p->out_buf_idx[i] = filt_buf_p->out_buf_total_len - filt_buf_p->out_buf_min_cal_len + 1;
    }

    /* 滤波序列初始化 */
    result |= ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_HPASS, ZQ_ECG_FILT_VAL_HPASS_06);
    result |= ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_TRAP, ZQ_ECG_FILT_VAL_TRAP_50);
    result |= ZQ_ECG_FILTER_set_filter(ZQ_ECG_FILT_TYPE_LPASS, ZQ_ECG_FILT_VAL_LPASS_25);

    return result;
}

/******************************************************************************
 * Function:     ZQ_ECG_FILTER_clear_filter_ch
 * Description:  清除滤波缓存
 * Input:        unsigned short lead_num  
 * Output:       none
 * Return:       int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_clear_filter_ch(unsigned short lead_num)
{
    int result = 0;    
    int i = 0;
    printf("%s:%d\n",__FUNCTION__,lead_num);
    if(MAX_FILT_LEAD_NUM <= lead_num)
    {
        printf("lead_num out of range!:%d\n", lead_num);
        return -1;
    }
    for (i=0; i<MAX_FILT_NUM; i++)
    {
        memset(filt_buffer[i].in_buf + lead_num*filt_buffer[i].in_buf_total_len,
            0, sizeof(filt_temp_t) * filt_buffer[i].in_buf_total_len);
        memset(filt_buffer[i].out_buf + lead_num*filt_buffer[i].out_buf_total_len,
            0, sizeof(filt_temp_t) * filt_buffer[i].out_buf_total_len);
    }

    return result;
}

/******************************************************************************
 * Function:     ZQ_ECG_FILTER_set_filter
 * Description:  设置滤波参数
 * Input:        unsigned short filter_type  
                unsigned short filter_value  
 * Output:       none
 * Return:       int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_set_filter(unsigned short filter_type, unsigned short filter_value)
{
    int result = 0;
    printf("%s:%d,%d\n",__FUNCTION__,filter_type,filter_value);
    print_current_filt_array();
    switch(filter_type)
    {
        case ZQ_ECG_FILT_TYPE_HPASS:
            result = do_set_hpass_filter(filter_value);
            break;
        case ZQ_ECG_FILT_TYPE_LPASS:
            result = do_set_lpass_filter(filter_value);
            break;
        case ZQ_ECG_FILT_TYPE_TRAP:
            result = do_set_trap_filter(filter_value);
            break;
#ifdef FILT_USE_EMG
        case ZQ_ECG_FILT_TYPE_EMG:
            result = do_set_emg_filter(filter_value);
            break;
#endif /* FILT_USE_EMG */
        default:
            printf("%s enter_default!\n",__FUNCTION__);
            result = -1;
    }
    /* 检查是否启用梳状滤波器 */
    result = check_comb_filt();
    print_current_filt_array();
    return result;
}
/******************************************************************************
 * Function:     do_filt_buffer_shift
 * Description:  缓冲区移位
 * Input:        filt_temp_t * buf  
                int total_len  
                int min_cal_len  
                int * idx  
 * Output:       none
 * Return:       static filt_temp_t * 
 * Author:       gdyshi
 * Date:         2014/5/17
 * Others:       none
 ******************************************************************************/
static filt_temp_t * do_filt_buffer_shift(filt_temp_t * buf, int total_len, int min_cal_len, int * idx)
{
    filt_temp_t * ret_buf = NULL;

    if(0 < *idx)
    {
        (* idx)--;
    }
    /* 缓冲区翻转 */
    else if(0 == *idx)
    {
        memmove(&buf[total_len-min_cal_len+1], &buf[0], sizeof(filt_temp_t)*(min_cal_len-1));
        *idx = total_len-min_cal_len;
    }
    else
    {
        printf("%s idx[%d] error!\n",__FUNCTION__,*idx);
        memmove(&buf[total_len-min_cal_len+1], &buf[0], sizeof(filt_temp_t)*(min_cal_len-1));
        *idx = total_len-min_cal_len;
    }
    return &buf[*idx];
}

/******************************************************************************
 * Function:     ZQ_ECG_FILTER_do_filter
 * Description:  执行滤波
 * Input:        int in_val  
                unsigned char lead_num  
 * Output:       none
 * Return:       int 
 * Author:       gdyshi
 * Date:         2014/5/13
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_do_filter(int in_val, unsigned char lead_num)
{
    int result = 0;
    int out_val = 0;
    int i = 0;
    int j = 0;
    filt_temp_t temp_val = (filt_temp_t)in_val;
    filt_temp_t * in_buf = NULL;
    filt_temp_t * out_buf = NULL;
    //printf("%s:%d,%d\n",__FUNCTION__,in_val,lead_num);
    if(MAX_FILT_LEAD_NUM <= lead_num)
    {
        //printf("lead_num out of range!:%d\n", lead_num);
        return -1;
    }
    
    for (i=0; i<ARRAY_SIZE(current_filt_array); i++)
    {
        if (NULL != current_filt_array[i])
        {
            /* 获取缓冲区地址 */
            in_buf = filt_buffer[i].in_buf + lead_num*filt_buffer[i].in_buf_total_len;
            out_buf = filt_buffer[i].out_buf + lead_num*filt_buffer[i].out_buf_total_len;
            
            /* 输入缓冲区移位 */
            in_buf = do_filt_buffer_shift(in_buf,filt_buffer[i].in_buf_total_len,
                                        filt_buffer[i].in_buf_min_cal_len,&(filt_buffer[i].in_buf_idx[lead_num]));
            in_buf[0]=temp_val;
            
            /* 输出缓冲区移位 */
            out_buf = do_filt_buffer_shift(out_buf,filt_buffer[i].out_buf_total_len,
                                        filt_buffer[i].out_buf_min_cal_len,&(filt_buffer[i].out_buf_idx[lead_num]));

            /* 执行滤波函数 */
            temp_val = current_filt_array[i]->zq_do_filt(in_buf, out_buf, current_filt_array[i]);
            
            out_buf[0]=temp_val;

            temp_val *= current_filt_array[i]->gain_den;
        }
    }
    out_val = (int)temp_val;
    return(out_val);
}
