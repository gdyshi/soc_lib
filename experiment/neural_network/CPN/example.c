#include "gdyshi_cpn.h"

void main(void)
{
    unsigned short i = 0;
    cpn_init(4, /* 输入向量个数 */
            4, /* 竞争向量个数 */
            4, /* 输出层神经元个数 */
            (nn_type)0.1, /* 竞争调节系数 */
            (nn_type)0.1/* 输出调节系数 */
            );
    cpn_get_learn_data("data.txt",2);

    for(i=0; i<1000; i++)
    {
        cpn_do_learn();
    }
    
    cpn_deinit();
    
}

