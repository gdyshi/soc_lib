#include "gdyshi_includes.h"
#include "gdyshi_comm_conf.h"
#include "gdyshi_network_layer.h"
#include "gdyshi_link_layer.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "NETWORK_LAYER"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

#define MAX_NETWORK_LAYER_DATA_LEN (MAX_LINK_LAYER_DATA_LEN - sizeof(network_layer_t))
#define NETWORK_TYPE_IP     (1)
#define NETWORK_TYPE_ARP     (2)
#define NETWORK_TYPE_ICMP     (3)

network_layer_t network_layer = 
{
    (network_layer_buffer_t *)&link_layer->send_link_layer->data[0],
    (network_layer_buffer_t *)&link_layer->recv_link_layer->data[0],
    network_layer_send_ip,
    network_layer_send_arp,
    network_layer_send_icmp,
    network_layer_do_recv,
};

static gdyshi_smcu network_layer_crc8(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len)
{
}

gdyshi_smcu network_layer_send_ip(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len)
{
    network_layer_buffer_t * buffer = network_layer.send_network_layer_buffer;
    GDYSHI_ASSERT(len<=MAX_NETWORK_LAYER_DATA_LEN, "data too len!");

    buffer->type = NETWORK_TYPE_IP;
    buffer->len = len + sizeof(network_layer_t);
    
    memcpy(buffer->dst_addr, addr, sizeof(addr_t));
    memcpy(buffer->src_addr, buffer, sizeof(addr_t));
    if(data != &buffer->data[0])
    {
        memcpy(&buffer->data[0], data, len);
    }
    buffer->crc8 = network_layer_crc8(buffer,buffer->len);
    link_layer.send(buffer, buffer->len);
}
gdyshi_smcu network_layer_send_arp(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len)
{
}
gdyshi_smcu network_layer_send_icmp(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len)
{
}
gdyshi_smcu network_layer_do_recv(addr_t addr, gdyshi_u8 * data, gdyshi_u16 len)
{
}

