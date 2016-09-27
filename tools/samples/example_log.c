#include "gdyshi_includes.h"
#include "gdyshi_log.h"

#undef __MODULE_NAME__
#define __MODULE_NAME__     "log_example"
#undef LOG_VALUE
#define LOG_VALUE   GDYSHI_LOG_LEVEL_INFO | GDYSHI_LOG_LITE_MODULE | GDYSHI_LOG_LITE_TIME | \
                    GDYSHI_LOG_LITE_FILE | GDYSHI_LOG_LITE_LINE | GDYSHI_LOG_LITE_FUNC

int main()
{
    gdyshi_s32 i = 0;
    GDYSHI_LOG_INIT("log.log");
    GDYSHI_DEBUG_POS();
    GDYSHI_DEBUG_INFO("info\n");
    GDYSHI_DEBUG_WARNING("info\n");
    GDYSHI_DEBUG_ERROR("info\n");
    GDYSHI_DEBUG_FATAL("info\n");
    GDYSHI_PERROR("info\n");
    GDYSHI_ASSERT(0 == i, GDYSHI_EINVAL, "info\n");
    GDYSHI_ASSERT(1 == i, GDYSHI_EINVAL, "info\n");
    
}
