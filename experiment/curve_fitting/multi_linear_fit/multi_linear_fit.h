#ifndef __GDYSHI_MULTI_LINEAR_FIT_H
#define __GDYSHI_MULTI_LINEAR_FIT_H
/* 线性拟合 */
#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
    gdyshi_s32 measured_value;/* 测量值 */
    gdyshi_s32 actual_value;/* 实际值 */
}gdyshi_measure_t;
/* measured_value从小到大排列 */
gdyshi_s32 multi_linear_fit_init(gdyshi_measure_t * measure_array, gdyshi_u8 array_num);
gdyshi_s32 multi_linear_fit_get_data(gdyshi_s32 measured_value);

#ifdef __cplusplus
}
#endif

#endif
