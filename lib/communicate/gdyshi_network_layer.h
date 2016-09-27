#ifndef __GDYSHI_NETWORK_LAYER_H
#define __GDYSHI_NETWORK_LAYER_H
/* ÍøÂç²ã */
#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
typedef struct
{
    gdyshi_u8 version:2;
    gdyshi_u8 type:6;
    gdyshi_u8 crc8;
    gdyshi_u16 len;
    gdyshi_u32 dst_addr;
    gdyshi_u32 src_addr;
    gdyshi_u8 data[0];
}network_layer_buffer_t;
#pragma pack()

typedef struct
{
    network_layer_buffer_t * send_network_layer_buffer;
    network_layer_buffer_t * recv_network_layer_buffer;
    gdyshi_smcu send_ip(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len);
    gdyshi_smcu send_arp(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len);
    gdyshi_smcu send_icmp(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len);
    gdyshi_smcu do_recv(gdyshi_u8 * data, gdyshi_u16 len);
}network_layer_t;

network_layer_t network_layer;


#ifdef __cplusplus
}
#endif

#endif
