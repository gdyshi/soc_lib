#ifndef __GDYSHI_COMMU_CONF_H
#define __GDYSHI_COMMU_CONF_H

#ifdef __cplusplus
extern "C" {
#endif
#define MAX_COMMUNICATE_LEN (100)
#define SYNC_VAL (0XCC)

#pragma pack(1)
typedef gdyshi_u8 sync_t;
typedef gdyshi_u32 addr_t;
#pragma pack()

addr_t g_communicate_addr;


#ifdef __cplusplus
}
#endif

#endif
