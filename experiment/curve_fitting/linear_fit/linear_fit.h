#ifndef __GDYSHI_LINEAR_FIT_H
#define __GDYSHI_LINEAR_FIT_H
/* 线性拟合 */
#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
    gdyshi_s32 measured_value;/* 测量值 */
    gdyshi_s32 actual_value;/* 实际值 */
}gdyshi_measure_t;
gdyshi_s32 linear_fit_init(gdyshi_measure_t * measure1,gdyshi_measure_t * measure2);
gdyshi_s32 linear_fit_get_data(gdyshi_s32 measured_value);

#ifdef __cplusplus
}
#endif

#endif
