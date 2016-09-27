#ifndef __GDYSHI_CPN_H
#define __GDYSHI_CPN_H

#ifdef __cplusplus
extern "C" {
#endif
typedef double nn_type;

typedef struct  {
    /* ѧϰ��ԭʼ���� */
	nn_type * i;/* ѧϰ��Ŀ���������� */
	nn_type * o;/* ѧϰ��Ŀ��������� */
    unsigned short learn_num;
    unsigned short learn_times;
    
	nn_type * x;/* �������� */
    unsigned short x_num;/* ������������ */
    
	nn_type * b;/* �������� */
    unsigned short b_num;/* ������������ */
	nn_type * w;/* ��������Ȩ���� */
	nn_type * w_next;/* �´�ѧϰʱ�ľ�������Ȩ���� */
    nn_type b_adjust;/* ��������ϵ�� */
    
	nn_type * y;/* �������Ԫ���� */
    unsigned short y_num;/* �������Ԫ���� */
	nn_type * v;/* �������Ȩ���� */
	nn_type * v_next;/* �´�ѧϰʱ���������Ȩ���� */
    nn_type y_adjust;/* �������ϵ�� */
}gdyshi_cpn_t;


void cpn_init(unsigned short x_num, /* ������������ */
                    unsigned short b_num, /* ������������ */
                    unsigned short y_num, /* �������Ԫ���� */
                    nn_type b_adjust, /* ��������ϵ�� */
                    nn_type y_adjust/* �������ϵ�� */
                    );
void cpn_get_learn_data(char * filename, unsigned short learn_num);
void cpn_do_learn(void);
void cpn_deinit(void);

#ifdef __cplusplus
}
#endif

#endif
