#ifndef __GDYSHI_LINK_LAYER_H
#define __GDYSHI_LINK_LAYER_H
/* Á´Â·²ã */
#ifdef __cplusplus
extern "C" {
#endif
#pragma pack(1)
typedef struct
{
    sync_t sync;
    gdyshi_u8 data[0];
}link_layer_buffer_t;
#pragma pack()
typedef struct
{
    link_layer_buffer_t * send_link_layer_buffer;
    link_layer_buffer_t * recv_link_layer_buffer;
    gdyshi_smcu send(gdyshi_u8 * data, gdyshi_u16 len);
    gdyshi_smcu do_recv(gdyshi_u8 * data, gdyshi_u16 len);    
    gdyshi_u16 valid_ckeck();
}link_layer_t;

link_layer_t link_layer;


#ifdef __cplusplus
}
#endif

#endif
