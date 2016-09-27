#ifndef __GDYSHI_CPN_H
#define __GDYSHI_CPN_H

#ifdef __cplusplus
extern "C" {
#endif
typedef double nn_type;

typedef struct  {
    /* 学习用原始数据 */
	nn_type * i;/* 学习用目标输入数据 */
	nn_type * o;/* 学习用目标输出数据 */
    unsigned short learn_num;
    unsigned short learn_times;
    
	nn_type * x;/* 输入向量 */
    unsigned short x_num;/* 输入向量个数 */
    
	nn_type * b;/* 竞争向量 */
    unsigned short b_num;/* 竞争向量个数 */
	nn_type * w;/* 竞争连接权向量 */
	nn_type * w_next;/* 下次学习时的竞争连接权向量 */
    nn_type b_adjust;/* 竞争调节系数 */
    
	nn_type * y;/* 输出层神经元数组 */
    unsigned short y_num;/* 输出层神经元个数 */
	nn_type * v;/* 输出连接权向量 */
	nn_type * v_next;/* 下次学习时的输出连接权向量 */
    nn_type y_adjust;/* 输出调节系数 */
}gdyshi_cpn_t;


void cpn_init(unsigned short x_num, /* 输入向量个数 */
                    unsigned short b_num, /* 竞争向量个数 */
                    unsigned short y_num, /* 输出层神经元个数 */
                    nn_type b_adjust, /* 竞争调节系数 */
                    nn_type y_adjust/* 输出调节系数 */
                    );
void cpn_get_learn_data(char * filename, unsigned short learn_num);
void cpn_do_learn(void);
void cpn_deinit(void);

#ifdef __cplusplus
}
#endif

#endif
