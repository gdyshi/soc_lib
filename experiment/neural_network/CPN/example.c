#include "gdyshi_cpn.h"

void main(void)
{
    unsigned short i = 0;
    cpn_init(4, /* ������������ */
            4, /* ������������ */
            4, /* �������Ԫ���� */
            (nn_type)0.1, /* ��������ϵ�� */
            (nn_type)0.1/* �������ϵ�� */
            );
    cpn_get_learn_data("data.txt",2);

    for(i=0; i<1000; i++)
    {
        cpn_do_learn();
    }
    
    cpn_deinit();
    
}

