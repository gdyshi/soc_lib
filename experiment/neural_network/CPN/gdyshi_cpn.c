#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "math.h"
#include "gdyshi_cpn.h"

gdyshi_cpn_t cpn = {0};


void print_value(nn_type * vec, unsigned short num)
{
    unsigned short i = 0;

    for(i=0; i<num; i++)
    {
        if(0 == i%4)
        {
            printf("\n");
        }
        printf("%lf ",vec[i]);
    }
    printf("\n over \n");
    
}
/* 归一化函数 */
nn_type normalization(nn_type * vector, unsigned short num)
{
    nn_type sum = 0;
    unsigned short i = 0;

#if 0
    printf("before normalization\n");
    print_value(vector, num);
#endif /* if 0 end */
    for(i=0; i<num; i++)
    {
        sum += vector[i]*vector[i];
    }
    sum = sqrt(sum);
    for(i=0; i<num; i++)
    {
        vector[i] /= sum;
    }
#if 0
    printf("after normalization\n");
    print_value(vector, num);
#endif /* if 0 end */
    return 0;
}

/* 神经元状态和函数 */
nn_type nn_sum(nn_type * in_vector, nn_type * weight_vector, unsigned short num)
{
    nn_type sum = 0;
    unsigned short i = 0;

    for(i=0; i<num; i++)
    {
        sum += in_vector[i]*weight_vector[i];
    }
    return sum;
}
/* 获取最大向量函数 */
unsigned short nn_get_max_vector( nn_type * vector, unsigned short num)
{
    nn_type max = vector[0];
    unsigned short i = 0, max_idx = 0;

    for(i=0; i<num; i++)
    {
        if(max < vector[i])
        {
            max = vector[i];
            max_idx++;
        }
    }
    return max_idx;
}

/* 修正权向量函数 */
nn_type correct_w_vect(nn_type * in_vector, nn_type * weight_vector, 
                                nn_type * out_vector,
                                unsigned short num, nn_type adjust)
{
    nn_type sum = 0;
    unsigned short i = 0;

    for(i=0; i<num; i++)
    {
        out_vector[i] = weight_vector[i] + adjust*(in_vector[i]-weight_vector[i]);
    }
    return sum;
}
/* 修正权向量函数 */
nn_type correct_v_vect(nn_type * in_vector, nn_type * weight_vector,
                                nn_type * out_vector,  nn_type * o_vector,
                                unsigned short num, nn_type adjust)
{
    nn_type sum = 0;
    unsigned short i = 0;

    for(i=0; i<num; i++)
    {
        out_vector[i] = weight_vector[i] + adjust*(in_vector[i]-o_vector[i]);
    }
    return sum;
}
void cpn_get_learn_data(char * filename, unsigned short learn_num)
{
    unsigned short i=0, j = 0;
    FILE *fp;
    // TODO 获取数据
    fp = fopen(filename,"r");
    if(NULL == fp)
    {
        return ;
    }
    fseek(fp,0,SEEK_SET);
    cpn.i = malloc(learn_num * cpn.x_num * sizeof(nn_type));
    cpn.o = malloc(learn_num * cpn.y_num * sizeof(nn_type));
    cpn.learn_num = learn_num;
    for (i=0; i<learn_num; i++)
    {
        for (j=0;j<cpn.x_num;j++)
        {
            fscanf(fp,"%lf ", &cpn.i[i*cpn.x_num+j]);
        }
        for (j=0;j<cpn.y_num;j++)
        {
            fscanf(fp,"%lf ", &cpn.o[i*cpn.y_num+j]);
        }
    }
    fclose(fp);


    /* 1) 归一化输入 */
    for(j=0; j<cpn.learn_num; j++)
    {
        normalization(&cpn.i[j*cpn.x_num], cpn.x_num);
    }

    
    printf("标准输出数据:\n");
    print_value(&cpn.o[0], cpn.y_num * learn_num);
#if 0
    /* 1) 归一化输出 */
    for(j=0; j<cpn.learn_num; j++)
    {
        normalization(&cpn.o[j*cpn.y_num], cpn.y_num);
    }
#endif /* if 0 end */
}
/* 学习函数 */
void cpn_do_learn(void)
{
    unsigned short i = 0, max_idx = 0, j = 0;
    nn_type * temp_vector = NULL, *x=NULL;
    for(j=0; j<cpn.learn_num; j++)
    {
        x = &cpn.i[i*cpn.x_num];
        temp_vector = malloc(cpn.b_num * sizeof(nn_type));    
        for(i=0; i<cpn.b_num; i++)
        {
            /* 2) 归一化连接向量 */
            normalization(&cpn.w[i*cpn.x_num], cpn.x_num);
			printf("连接向量%d\n",i);
			print_value(&cpn.w[i*cpn.x_num], cpn.x_num);

            /* 3) 神经元状态和函数 */        
            temp_vector[i] = nn_sum(x, &cpn.w[i*cpn.x_num], cpn.x_num);
        }
        printf("神经元状态和\n");
        print_value(temp_vector, cpn.b_num);
        /* 4) 获取最大向量函数 */
        max_idx = nn_get_max_vector(temp_vector, cpn.x_num);
        free(temp_vector);
        
        /* 5) 格式化输出 */
        memset(cpn.b, 0, cpn.b_num * sizeof(nn_type));
        cpn.b[max_idx] = 1;
        printf("格式化输出\n");
        print_value(cpn.b, cpn.b_num);
        
        /* 6) 修正连接权向量 */
        correct_w_vect(x, &cpn.w[max_idx*cpn.x_num], &cpn.w_next[max_idx*cpn.x_num],
                        cpn.x_num, cpn.b_adjust);
        printf("修正连接权向量\n");
		print_value(&cpn.w_next[max_idx*cpn.x_num], cpn.x_num);
        
        /* 7) 归一化连接权向量 */
        normalization(&cpn.w[i*cpn.x_num], cpn.x_num);

        /* 8) 输出状态和 */
        temp_vector = malloc(cpn.y_num * sizeof(nn_type));    
        for(i=0; i<cpn.y_num; i++)
        {        
            //normalization(&cpn.v[i*cpn.y_num], cpn.y_num);
            temp_vector[i] = nn_sum(&cpn.v[i*cpn.b_num], cpn.b, cpn.b_num);
        }
        printf("输出状态和\n");
        print_value(temp_vector, cpn.y_num);
        
        /* 9) 修正输出权向量 */    
        for(i=0; i<cpn.y_num; i++)
        {        
            cpn.v_next[i*cpn.b_num + max_idx] = cpn.v[i*cpn.b_num + max_idx] + 
                //cpn.y_adjust*cpn.b[max_idx]*(temp_vector[i]-cpn.o[i*cpn.y_num]);        
                cpn.y_adjust*cpn.b[max_idx]*(cpn.o[i*cpn.y_num] - temp_vector[i]);        
            //normalization(&cpn.v_next[i*cpn.y_num], cpn.y_num);
        }
        free(temp_vector);
    }
	printf("连接权向量\n");
	print_value(cpn.w_next, cpn.x_num * cpn.b_num);
	printf("结果权向量\n");
	print_value(cpn.v_next, cpn.b_num * cpn.y_num);
	memcpy(cpn.w, cpn.w_next, cpn.x_num * cpn.b_num * sizeof(nn_type));
    memcpy(cpn.v, cpn.v_next, cpn.b_num * cpn.y_num * sizeof(nn_type));
    
}
#if 0
/* 学习函数 */
void cpn_do_use(nn_type * x)
{
    unsigned short i = 0, max_idx = 0, j = 0;
    nn_type * temp_vector = NULL;

        temp_vector = malloc(cpn.b_num * sizeof(nn_type));    
        /* 2) 归一化输入向量 */
        normalization(&x[0], cpn.x_num);
        printf("输入向量%d\n",i);
        print_value(&x[0], cpn.x_num);
        for(i=0; i<cpn.b_num; i++)
        {
            /* 3) 神经元状态和函数 */        
            temp_vector[i] = nn_sum(x, &cpn.w[i*cpn.x_num], cpn.x_num);
        }
        printf("神经元状态和\n");
        print_value(temp_vector, cpn.b_num);
        /* 4) 获取最大向量函数 */
        max_idx = nn_get_max_vector(temp_vector, cpn.x_num);
        free(temp_vector);
        
        /* 5) 格式化输出 */
        memset(cpn.b, 0, cpn.b_num * sizeof(nn_type));
        cpn.b[max_idx] = 1;
        printf("格式化输出\n");
        print_value(cpn.b, cpn.b_num);
        
        /* 8) 输出状态和 */
        temp_vector = malloc(cpn.y_num * sizeof(nn_type));    
        for(i=0; i<cpn.y_num; i++)
        {        
            temp_vector[i] = nn_sum(&cpn.v[i*cpn.b_num], cpn.b, cpn.b_num);
        }
        printf("输出状态和\n");
        print_value(temp_vector, cpn.y_num);
        
        /* 9) 修正输出权向量 */    
        for(i=0; i<cpn.y_num; i++)
        {        
            cpn.v_next[i*cpn.b_num + max_idx] = cpn.v[i*cpn.b_num + max_idx] + 
                cpn.y_adjust*cpn.b[max_idx]*(temp_vector[i]-cpn.o[i*cpn.y_num]);        
            //normalization(&cpn.v_next[i*cpn.y_num], cpn.y_num);
        }
        free(temp_vector);

	printf("连接权向量\n");
	print_value(cpn.w_next, cpn.x_num * cpn.b_num);
	printf("结果权向量\n");
	print_value(cpn.v_next, cpn.b_num * cpn.y_num);
	memcpy(cpn.w, cpn.w_next, cpn.x_num * cpn.b_num * sizeof(nn_type));
    memcpy(cpn.v, cpn.v_next, cpn.b_num * cpn.y_num * sizeof(nn_type));
    
}
#endif /* if 0 end */

/* 初始化函数 */
void cpn_init(unsigned short x_num, /* 输入向量个数 */
                    unsigned short b_num, /* 竞争向量个数 */
                    unsigned short y_num, /* 输出层神经元个数 */
                    nn_type b_adjust, /* 竞争调节系数 */
                    nn_type y_adjust/* 输出调节系数 */
                    )
{
    cpn.x_num = x_num;
    cpn.b_num = b_num;
    cpn.y_num = y_num;
    cpn.b_adjust = b_adjust;
    cpn.y_adjust = y_adjust;
    
    cpn.x = malloc(x_num * sizeof(nn_type));
    cpn.b = malloc(b_num * sizeof(nn_type));
    cpn.y = malloc(y_num * sizeof(nn_type));
    cpn.w = malloc(x_num * b_num * sizeof(nn_type));
    cpn.v = malloc(b_num * y_num * sizeof(nn_type));
    cpn.w_next = malloc(x_num * b_num * sizeof(nn_type));
    cpn.v_next = malloc(b_num * y_num * sizeof(nn_type));
    //TODO v v_next w w_next 随机化
    cpn.w[0] = 1;cpn.w[1] = 1;cpn.w[2] = 1;cpn.w[3] = 1;
    cpn.w[4] = 1;cpn.w[5] = 1;cpn.w[6] = 1;cpn.w[7] = 1;
    cpn.w[8] = 1;cpn.w[9] = 1;cpn.w[10] = 1;cpn.w[11] = 1;
    cpn.w[12] = 1;cpn.w[13] = 1;cpn.w[14] = 1;cpn.w[15] = 1;
    cpn.v[0] = 1;cpn.v[1] = 1;cpn.v[2] = 1;cpn.v[3] = 1;
    cpn.v[4] = 1;cpn.v[5] = 1;cpn.v[6] = 1;cpn.v[7] = 1;
    cpn.v[8] = 1;cpn.v[9] = 1;cpn.v[10] = 1;cpn.v[11] = 1;
    cpn.v[12] = 1;cpn.v[13] = 1;cpn.v[14] = 1;cpn.v[15] = 1;
	memcpy(cpn.w_next, cpn.w, cpn.x_num * cpn.b_num * sizeof(nn_type));
    memcpy(cpn.v_next, cpn.v, cpn.b_num * cpn.y_num * sizeof(nn_type));
    
}

void cpn_deinit(void)
{
    free(cpn.x);    
    free(cpn.b);    
    free(cpn.y);    
    free(cpn.w);    
    free(cpn.v);    
    free(cpn.w_next);    
    free(cpn.v_next);    
    free(cpn.i);    
    free(cpn.o);    
}

