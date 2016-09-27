#include "gdyshi_includes.h"
#include "gdyshi_comm_conf.h"
#include "gdyshi_link_layer.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "LINK_LAYER"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_FUNC | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_TIME

#define LINK_LAYER_HEAD_LEN (sizeof(sync_t))
#define MAX_LINK_LAYER_DATA_LEN (MAX_COMMUNICATE_LEN - LINK_LAYER_HEAD_LEN)

gdyshi_u8 communicate_send_array[MAX_COMMUNICATE_LEN] = {0};
gdyshi_u8 communicate_recv_array[MAX_COMMUNICATE_LEN] = {0};
link_layer_t link_layer = 
{
    (link_layer_buffer_t *)&communicate_send_array,
    (link_layer_buffer_t *)&communicate_recv_array,
    link_layer_send,
    link_layer_do_recv,
};

gdyshi_smcu link_layer_send(gdyshi_u8 * data, gdyshi_u16 len)
{
    gdyshi_smcu result = 0;
    link_layer_buffer_t * buffer = link_layer->send_link_layer_buffer;
    
    GDYSHI_ASSERT(len<=MAX_LINK_LAYER_DATA_LEN, "data too len!");
    memcpy(buffer->sync, SYNC_VAL, LINK_LAYER_HEAD_LEN);
    if(data != &buffer->data[0])
    {
        memcpy(&buffer->data[0], data, len);
    }
    result = send(buffer, len+LINK_LAYER_HEAD_LEN);
    
    return result;
}
gdyshi_smcu link_layer_check_pack(gdyshi_u8 * data, gdyshi_u16 len)
{
    gdyshi_smcu result = 0;
    gdyshi_u16 i = 0;
    gdyshi_u8 * src = data;
    GDYSHI_ASSERT(len>LINK_LAYER_HEAD_LEN, "data too small!");

    for(i=0; i<(len-LINK_LAYER_HEAD_LEN); i++)
    {
        /* 查找同步标志 */
        if(0 == memcmp(&src[i], SYNC_VAL, sizeof(SYNC_VAL)))
        {
            link_layer_buffer_t * buffer = &src[i];
            result = network_layer.check_pack(buffer->data, len-LINK_LAYER_HEAD_LEN);
        }
    }
    
    
    return result;
}
gdyshi_smcu link_layer_do_recv(gdyshi_u8 * data, gdyshi_u16 len)
{
    gdyshi_smcu result = 0;
    gdyshi_u16 i = 0;
    gdyshi_u8 * src = data;
   
    result = link_layer.check_pack(data, len);
    if(result != len)
    {
        result = -1;
        goto err;
    }

    for(i=0; i<(len-LINK_LAYER_HEAD_LEN); i++)
    {
        /* 查找同步标志 */
        if(0 == memcmp(&src[i], SYNC_VAL, sizeof(SYNC_VAL)))
        {
            
        }
    }
    GDYSHI_ASSERT(len<=MAX_LINK_LAYER_DATA_LEN, "data too len!");
    memcpy(link_layer->sync, SYNC_VAL, sizeof(SYNC_VAL));
    if(data != &link_layer->data[0])
    {
        memcpy(&link_layer->data[0], data, len);
    }
    send(communicate_array, len+sizeof(sync_t));
err:
    return result;
}

