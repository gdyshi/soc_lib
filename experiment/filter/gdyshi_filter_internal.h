/******************************************************************************
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
//#define FILT_USE_EMG /* ����ĵ����˲�����(Ŀǰ���ÿ�ͨ����Ϊ�����˲����ͨ����) */
/* -------------------------------------------------------------------------- */
/* ---------------------------------- ���������� ---------------------------- */
/* -------------------------------------------------------------------------- */
typedef double filt_temp_t;/* �м�������� */
//typedef float filt_temp_t;/* �м�������� */
typedef int filt_io_t;/* �ⲿ�ӿ����� */
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0])) 
#endif
#if !defined(NULL)
#define NULL ((void *)0) 
#endif
#define FILT_INTERNAL_TYPE_HPASS       (0)/* 高�?*/
#define FILT_INTERNAL_TYPE_LPASS       (1)/* 低�?*/
#define FILT_INTERNAL_TYPE_TRAP        (2)/* 陷波�?*/
#define FILT_INTERNAL_TYPE_EMG         (3)/* 肌电滤波 */

/* ����˲������� */
#ifdef FILT_USE_EMG
#define MAX_FILT_NUM     (4)
#else
#define MAX_FILT_NUM     (3)/* ����˲������� */
#endif /* FILT_USE_EMG */
#define MAX_HPASS_NUM_NUM     (4000)/* ����ͨ�˲����Ӹ��� */
#define MAX_HPASS_DEN_NUM     (50)/* ����ͨ�˲���ĸ���� */
#define MAX_LPASS_NUM_NUM     (500)/* ����ͨ�˲����Ӹ��� */
#define MAX_LPASS_DEN_NUM     (50)/* ����ͨ�˲����Ӹ��� */
#define MAX_TRAP_NUM_NUM     (4000)/* ����ݲ��˲����Ӹ��� */
#define MAX_TRAP_DEN_NUM     (50)/* ����ݲ��˲����Ӹ��� */
#ifdef FILT_USE_EMG
#define MAX_EMG_NUM_NUM     (1)/* ��󼡵��˲����Ӹ��� */
#define MAX_EMG_DEN_NUM     (1)/* ��󼡵��˲����Ӹ��� */
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

#define FILT_TYPE_A     (1)/* ˳�������˲����� */
#define FILT_TYPE_B     (2)/* ��Ծ������˲����� */
/* �˲���A��������Ͷ��� */
typedef struct
{
    int filt_type;/* �˲������� */
    
    filt_temp_t  *numData;/* ���Ӳ��� */
    int num_num;/* ���Ӳ������� */
    int zero_num;/* ���Ӳ�����0�ĸ��� */
    int one_num;/* ���Ӳ�����1�ĸ��� */
    
    filt_temp_t  *denData;/* ��ĸ���� */
    int den_num;/* ��ĸ�������� */    
}filt_type_a_par_t;

/* �˲���B��������Ͷ��� */
typedef struct
{
    int  seq;/* ��ţ������Ϊmatlab���(��1��ʼ) */
    filt_temp_t  data;/* ����ֵ */
}filt_b_ele_t;

typedef struct
{
    int filt_parm_type;/* �˲��������� */

    int num_num;/* ���Ӳ����ܸ��� */
    int num_num_valid;/* ���Ӳ�������Ч���ݸ��� */
    filt_b_ele_t  *numData;/* ���Ӳ��� */    
    
    int den_num;/* ��ĸ�����ܸ��� */    
    int den_num_valid;/* ��ĸ��������Ч���ݸ��� */
    filt_b_ele_t  *denData;/* ��ĸ���� */
}filt_type_b_par_t;

/* �˲������Ͷ��� */
typedef struct ZQ_ECG_FILT_ARG
{
    char * name;/* �˲������� */    
    int filt_type;/* �˲������� */    
    /* �˲����� */
    filt_temp_t (*zq_do_filt)(filt_temp_t * in_buf, filt_temp_t * out_buf, struct ZQ_ECG_FILT_ARG * filt_arg);
    
    filt_temp_t gain_num;/* ��������(����) */
    filt_temp_t gain_den;/* ��������(��ĸ) */
    
    void  *ZQ_ECG_filt_type_par;/* �����б� */
}ZQ_ECG_filt_arg_t;

typedef struct
{
    int buf_idx;/* ������ָ�� */
}ZQ_ECG_filt_buf_len_t;

typedef struct
{
    filt_temp_t * in_buf;/* ���뻺���� */
    int in_buf_total_len;/* ���뻺�����ܳ���(��λfilt_temp_t) */
    int in_buf_min_cal_len;/* ���뻺������С���㵥Ԫ����(��λfilt_temp_t) */
    int in_buf_idx[MAX_FILT_LEAD_NUM];/* ���뻺����ָ�� */
    filt_temp_t * out_buf;/* ��������� */
    int out_buf_total_len;/* ����������ܳ���(��λfilt_temp_t) */
    int out_buf_min_cal_len;/* �����������С���㵥Ԫ����(��λfilt_temp_t) */
    int out_buf_idx[MAX_FILT_LEAD_NUM];/* ���������ָ�� */
}ZQ_ECG_filt_buf_t;

/* -------------------------------------------------------------------------- */
/* -------------------------------- ����ʽ������ -------------------------- */
/* -------------------------------------------------------------------------- */
filt_temp_t do_filt_type_a(filt_temp_t * in_buf, filt_temp_t * out_buf, struct ZQ_ECG_FILT_ARG * filt_arg);
filt_temp_t do_filt_type_b(filt_temp_t * in_buf, filt_temp_t * out_buf, struct ZQ_ECG_FILT_ARG * filt_arg);


/* -------------------------------------------------------------------------- */
/* -------------------------------- �������Ͷ����� -------------------------- */
/* -------------------------------------------------------------------------- */

#endif /* _AMP_COMM_FORMAT_H_ */
/*----------------------------------END OF FILE szpathName-------------------------------*/

