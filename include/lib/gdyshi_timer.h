#ifndef __GDYSHI_TIMER_H__
#define __GDYSHI_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif



typedef struct GDYSHI_TIMER
{
    volatile struct
    {
        gdyshi_u8 is_busy:1;/* æ���������� */
        gdyshi_u8 is_in_timing:1;/* ��ʱ�����ڹ��� */
        gdyshi_u8 is_repeat:1;/* �ظ���ʱ */
    }statu;
    volatile gdyshi_u32 aim_tics;/* Ŀ��TICKֵ */
    gdyshi_u16 time_ms;/* ��ʱʱ�� */
    gdyshi_smcu (*fun)(struct GDYSHI_TIMER * this_timer, void * arg);/* ��ʱ���� */
    void * arg;
}gdyshi_timer_t;
typedef gdyshi_smcu (*timer_callback)(gdyshi_timer_t * this_timer, void * arg);
gdyshi_smcu gdyshi_init_timer(void);
gdyshi_timer_t * gdyshi_new_timer(gdyshi_u16 time_ms, timer_callback fun, void * arg);
gdyshi_smcu gdyshi_del_timer(gdyshi_timer_t * timer);
gdyshi_smcu gdyshi_start_timer(gdyshi_timer_t * timer);
gdyshi_smcu gdyshi_restart_timer(gdyshi_timer_t * timer);
gdyshi_smcu gdyshi_stop_timer(gdyshi_timer_t * timer);
gdyshi_smcu gdyshi_tick_process(void);

#ifdef __cplusplus
}
#endif

#endif
