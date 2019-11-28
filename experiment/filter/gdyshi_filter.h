/******************************************************************************
 *
 *
 * Description:  
 * - This file implements the follow functions:
 * - 
 * 
 * Author: gdyshi 
 * Date:  15:41pm, 05.Jun.2013
 * Modification History
 * --------------------
 * Date              Modifier    Problem N.O.                 Description
 * --------------------
 ******************************************************************************/

#ifndef __GDYSHI_FILTER_H
#define __GDYSHI_FILTER_H

/* 导联号定义,对应函数 ZQ_ECG_FILTER_set_filter 中的参数 filter_type */
#define ZQ_ECG_FILT_TYPE_HPASS       (1)/* 高通 */
#define ZQ_ECG_FILT_TYPE_LPASS       (2)/* 低通 */
#define ZQ_ECG_FILT_TYPE_TRAP        (3)/* 陷波器 */
#define ZQ_ECG_FILT_TYPE_EMG         (4)/* 肌电滤波 */

/* 导联号定义,对应函数 ZQ_ECG_FILTER_set_filter 中的参数 filter_type */
#define ZQ_ECG_FILT_VAL_NONE         (0)/* 表示此类滤波器关闭 */

#define ZQ_ECG_FILT_VAL_HPASS_005    (50)/* 高通0.05HZ */
#define ZQ_ECG_FILT_VAL_HPASS_03     (300)/* 高通0.3HZ */
#define ZQ_ECG_FILT_VAL_HPASS_05     (500)/* 高通0.5HZ */
#define ZQ_ECG_FILT_VAL_HPASS_06     (600)/* 高通0.5HZ */

#define ZQ_ECG_FILT_VAL_LPASS_150    (150)/* 低通150HZ */
#define ZQ_ECG_FILT_VAL_LPASS_100    (100)/* 低通150HZ */
#define ZQ_ECG_FILT_VAL_LPASS_75     (75) /* 低通150HZ */
#define ZQ_ECG_FILT_VAL_LPASS_45       (45)/* 肌电45HZ */
#define ZQ_ECG_FILT_VAL_LPASS_35       (35)/* 肌电35HZ */
#define ZQ_ECG_FILT_VAL_LPASS_25       (25)/* 肌电25HZ */

#define ZQ_ECG_FILT_VAL_TRAP_50      (50)/* 陷波50HZ */
#define ZQ_ECG_FILT_VAL_TRAP_60      (60)/* 陷波60HZ */

#define ZQ_ECG_FILT_VAL_EMG_25       (25)/* 肌电25HZ */
#define ZQ_ECG_FILT_VAL_EMG_35       (35)/* 肌电35HZ */
#define ZQ_ECG_FILT_VAL_EMG_45       (45)/* 肌电45HZ */

/* 导联号定义,对应函数 ZQ_ECG_FILTER_do_filter 中的参数 lead_num */
#define ZQ_ECG_FILT_LEAD_I       (0)
#define ZQ_ECG_FILT_LEAD_II      (1)
#define ZQ_ECG_FILT_LEAD_V1      (2)
#define ZQ_ECG_FILT_LEAD_V2      (3)
#define ZQ_ECG_FILT_LEAD_V3      (4)
#define ZQ_ECG_FILT_LEAD_V4      (5)
#define ZQ_ECG_FILT_LEAD_V5      (6)
#define ZQ_ECG_FILT_LEAD_V6      (7)
#define ZQ_ECG_FILT_LEAD_V7      (9)
#define ZQ_ECG_FILT_LEAD_V8      (10)
#define ZQ_ECG_FILT_LEAD_V9      (11)
#define ZQ_ECG_FILT_LEAD_C3R      (12)
#define ZQ_ECG_FILT_LEAD_C4R      (13)
#define ZQ_ECG_FILT_LEAD_C5R      (14)
#define MAX_FILT_LEAD_NUM       (ZQ_ECG_FILT_LEAD_C5R+1)

int ZQ_ECG_FILTER_init(void);

/******************************************************************************
 * Function:     ZQ_ECG_FILTER_clear_filter_ch
 * Description:  清除对应通道的滤波缓冲区
 * Input:        u8 lead_num  导联号
 * Output:       none
 * Return:       s32 返回0表示设置成功
 * Author:       gdyshi
 * Date:         2013/6/5
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_clear_filter_ch(unsigned short lead_num);

/******************************************************************************
 * Function:     ZQ_ECG_FILTER_set_filter
 * Description:  设置滤波参数
 * Input:        u16 filter_type  滤波类型
                 u16 filter_value  滤波值设置
 * Output:       none
 * Return:       s32 返回0表示设置成功
 * Author:       gdyshi
 * Date:         2013/6/5
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_set_filter(unsigned short filter_type, unsigned short filter_value);

/******************************************************************************
 * Function:     ZQ_ECG_FILTER_do_filter
 * Description:  执行滤波操作
 * Input:        filter_t in_val  滤波器输入值
                 u8 lead_num  导联号
 * Output:       none
 * Return:       filter_t 滤波输出值
 * Author:       gdyshi
 * Date:         2013/6/5
 * Others:       none
 ******************************************************************************/
int ZQ_ECG_FILTER_do_filter(int in_val, unsigned char lead_num);

#endif
/*----------------------------------END OF FILE gdysi_filter.h-------------------------------*/

