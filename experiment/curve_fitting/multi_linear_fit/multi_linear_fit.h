#ifndef __GDYSHI_MULTI_LINEAR_FIT_H
#define __GDYSHI_MULTI_LINEAR_FIT_H
/* ������� */
#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
    gdyshi_s32 measured_value;/* ����ֵ */
    gdyshi_s32 actual_value;/* ʵ��ֵ */
}gdyshi_measure_t;
/* measured_value��С�������� */
gdyshi_s32 multi_linear_fit_init(gdyshi_measure_t * measure_array, gdyshi_u8 array_num);
gdyshi_s32 multi_linear_fit_get_data(gdyshi_s32 measured_value);

#ifdef __cplusplus
}
#endif

#endif
