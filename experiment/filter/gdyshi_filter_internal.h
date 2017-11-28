/******************************************************************************
 * ZQ_ECG_filter_internal.h
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

#ifndef __ZQ_GDYSHI_INTERNAL_H
#define __ZQ_GDYSHI_INTERNAL_H
//#define FILT_USE_EMG /* 肌电的单独滤波功能(目前不用开通，因为肌电滤波与高通共用) */
/* -------------------------------------------------------------------------- */
/* ---------------------------------- 常量定义区 ---------------------------- */
/* -------------------------------------------------------------------------- */
typedef double filt_temp_t;/* 中间参数类型 */
//typedef float filt_temp_t;/* 中间参数类型 */
typedef int filt_io_t;/* 外部接口类型 */
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0])) 
#endif
#if !defined(NULL)
#define NULL ((void *)0) 
#endif
#define FILT_INTERNAL_TYPE_HPASS       (0)/* 楂橀�?*/
#define FILT_INTERNAL_TYPE_LPASS       (1)/* 浣庨�?*/
#define FILT_INTERNAL_TYPE_TRAP        (2)/* 闄锋尝鍣?*/
#define FILT_INTERNAL_TYPE_EMG         (3)/* 鑲岀數婊ゆ尝 */

/* 最大滤波器个数 */
#ifdef FILT_USE_EMG
#define MAX_FILT_NUM     (4)
#else
#define MAX_FILT_NUM     (3)/* 最大滤波器个数 */
#endif /* FILT_USE_EMG */
#define MAX_HPASS_NUM_NUM     (4000)/* 最大高通滤波分子个数 */
#define MAX_HPASS_DEN_NUM     (50)/* 最大高通滤波分母个数 */
#define MAX_LPASS_NUM_NUM     (500)/* 最大低通滤波分子个数 */
#define MAX_LPASS_DEN_NUM     (50)/* 最大低通滤波分子个数 */
#define MAX_TRAP_NUM_NUM     (4000)/* 最大陷波滤波分子个数 */
#define MAX_TRAP_DEN_NUM     (50)/* 最大陷波滤波分子个数 */
#ifdef FILT_USE_EMG
#define MAX_EMG_NUM_NUM     (1)/* 最大肌电滤波分子个数 */
#define MAX_EMG_DEN_NUM     (1)/* 最大肌电滤波分子个数 */
#endif /* FILT_USE_EMG */

#define NAME_FILT_HPASS_005    "hpass 0.05"
#define NAME_FILT_HPASS_03     "hpass 0.3"
#define NAME_FILT_HPASS_05     "hpass 0.5"
#define NAME_FILT_HPASS_06     "hpass 0.6"

#define NAME_FILT_LPASS_150    "lpass 150"
#define NAME_FILT_LPASS_100    "lpass 100"
#define NAME_FILT_LPASS_75     "lpass 75"
#define NAME_FILT_LPASS_45     "lpass 45"
#define NAME_FILT_LPASS_35     "lpass 35"
#define NAME_FILT_LPASS_25     "lpass 25"

#define NAME_FILT_TRAP_50      "trap 50"
#define NAME_FILT_TRAP_60      "trap 60"

#define NAME_FILT_EMG_25       "emg 25"
#define NAME_FILT_EMG_35       "emg 35"
#define NAME_FILT_EMG_45       "emg 45"

#define NAME_FILT_COMB_50_03       "comb 50 0.3"
#define NAME_FILT_COMB_50_06       "comb 50 0.6"

#define FILT_TYPE_A     (1)/* 顺序计算的滤波类型 */
#define FILT_TYPE_B     (2)/* 跳跃计算的滤波类型 */
/* 滤波器A类参数类型定义 */
typedef struct
{
    int filt_type;/* 滤波器类型 */
    
    filt_temp_t  *numData;/* 分子参数 */
    int num_num;/* 分子参数个数 */
    int zero_num;/* 分子参数中0的个数 */
    int one_num;/* 分子参数中1的个数 */
    
    filt_temp_t  *denData;/* 分母参数 */
    int den_num;/* 分母参数个数 */    
}filt_type_a_par_t;

/* 滤波器B类参数类型定义 */
typedef struct
{
    int  seq;/* 序号，此序号为matlab序号(从1起始) */
    filt_temp_t  data;/* 参数值 */
}filt_b_ele_t;

typedef struct
{
    int filt_parm_type;/* 滤波参数类型 */

    int num_num;/* 分子参数总个数 */
    int num_num_valid;/* 分子参数中有效数据个数 */
    filt_b_ele_t  *numData;/* 分子参数 */    
    
    int den_num;/* 分母参数总个数 */    
    int den_num_valid;/* 分母参数中有效数据个数 */
    filt_b_ele_t  *denData;/* 分母参数 */
}filt_type_b_par_t;

/* 滤波器类型定义 */
typedef struct ZQ_ECG_FILT_ARG
{
    char * name;/* 滤波器名称 */    
    int filt_type;/* 滤波器类型 */    
    /* 滤波函数 */
    filt_temp_t (*zq_do_filt)(filt_temp_t * in_buf, filt_temp_t * out_buf, struct ZQ_ECG_FILT_ARG * filt_arg);
    
    filt_temp_t gain_num;/* 参数增益(分子) */
    filt_temp_t gain_den;/* 参数增益(分母) */
    
    void  *ZQ_ECG_filt_type_par;/* 参数列表 */
}ZQ_ECG_filt_arg_t;

typedef struct
{
    int buf_idx;/* 缓冲区指针 */
}ZQ_ECG_filt_buf_len_t;

typedef struct
{
    filt_temp_t * in_buf;/* 输入缓冲区 */
    int in_buf_total_len;/* 输入缓冲区总长度(单位filt_temp_t) */
    int in_buf_min_cal_len;/* 输入缓冲区最小运算单元长度(单位filt_temp_t) */
    int in_buf_idx[MAX_FILT_LEAD_NUM];/* 输入缓冲区指针 */
    filt_temp_t * out_buf;/* 输出缓冲区 */
    int out_buf_total_len;/* 输出缓冲区总长度(单位filt_temp_t) */
    int out_buf_min_cal_len;/* 输出缓冲区最小运算单元长度(单位filt_temp_t) */
    int out_buf_idx[MAX_FILT_LEAD_NUM];/* 输出缓冲区指针 */
}ZQ_ECG_filt_buf_t;

/* -------------------------------------------------------------------------- */
/* -------------------------------- 宏表达式定义区 -------------------------- */
/* -------------------------------------------------------------------------- */
filt_temp_t do_filt_type_a(filt_temp_t * in_buf, filt_temp_t * out_buf, struct ZQ_ECG_FILT_ARG * filt_arg);
filt_temp_t do_filt_type_b(filt_temp_t * in_buf, filt_temp_t * out_buf, struct ZQ_ECG_FILT_ARG * filt_arg);


/* -------------------------------------------------------------------------- */
/* -------------------------------- 数据类型定义区 -------------------------- */
/* -------------------------------------------------------------------------- */

#endif /* _AMP_COMM_FORMAT_H_ */
/*----------------------------------END OF FILE szpathName-------------------------------*/

