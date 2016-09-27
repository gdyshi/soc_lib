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
/* ��һ������ */
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

/* ��Ԫ״̬�ͺ��� */
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
/* ��ȡ����������� */
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

/* ����Ȩ�������� */
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
/* ����Ȩ�������� */
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
    // TODO ��ȡ����
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


    /* 1) ��һ������ */
    for(j=0; j<cpn.learn_num; j++)
    {
        normalization(&cpn.i[j*cpn.x_num], cpn.x_num);
    }

    
    printf("��׼�������:\n");
    print_value(&cpn.o[0], cpn.y_num * learn_num);
#if 0
    /* 1) ��һ����� */
    for(j=0; j<cpn.learn_num; j++)
    {
        normalization(&cpn.o[j*cpn.y_num], cpn.y_num);
    }
#endif /* if 0 end */
}
/* ѧϰ���� */
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
            /* 2) ��һ���������� */
            normalization(&cpn.w[i*cpn.x_num], cpn.x_num);
			printf("��������%d\n",i);
			print_value(&cpn.w[i*cpn.x_num], cpn.x_num);

            /* 3) ��Ԫ״̬�ͺ��� */        
            temp_vector[i] = nn_sum(x, &cpn.w[i*cpn.x_num], cpn.x_num);
        }
        printf("��Ԫ״̬��\n");
        print_value(temp_vector, cpn.b_num);
        /* 4) ��ȡ����������� */
        max_idx = nn_get_max_vector(temp_vector, cpn.x_num);
        free(temp_vector);
        
        /* 5) ��ʽ����� */
        memset(cpn.b, 0, cpn.b_num * sizeof(nn_type));
        cpn.b[max_idx] = 1;
        printf("��ʽ�����\n");
        print_value(cpn.b, cpn.b_num);
        
        /* 6) ��������Ȩ���� */
        correct_w_vect(x, &cpn.w[max_idx*cpn.x_num], &cpn.w_next[max_idx*cpn.x_num],
                        cpn.x_num, cpn.b_adjust);
        printf("��������Ȩ����\n");
		print_value(&cpn.w_next[max_idx*cpn.x_num], cpn.x_num);
        
        /* 7) ��һ������Ȩ���� */
        normalization(&cpn.w[i*cpn.x_num], cpn.x_num);

        /* 8) ���״̬�� */
        temp_vector = malloc(cpn.y_num * sizeof(nn_type));    
        for(i=0; i<cpn.y_num; i++)
        {        
            //normalization(&cpn.v[i*cpn.y_num], cpn.y_num);
            temp_vector[i] = nn_sum(&cpn.v[i*cpn.b_num], cpn.b, cpn.b_num);
        }
        printf("���״̬��\n");
        print_value(temp_vector, cpn.y_num);
        
        /* 9) �������Ȩ���� */    
        for(i=0; i<cpn.y_num; i++)
        {        
            cpn.v_next[i*cpn.b_num + max_idx] = cpn.v[i*cpn.b_num + max_idx] + 
                //cpn.y_adjust*cpn.b[max_idx]*(temp_vector[i]-cpn.o[i*cpn.y_num]);        
                cpn.y_adjust*cpn.b[max_idx]*(cpn.o[i*cpn.y_num] - temp_vector[i]);        
            //normalization(&cpn.v_next[i*cpn.y_num], cpn.y_num);
        }
        free(temp_vector);
    }
	printf("����Ȩ����\n");
	print_value(cpn.w_next, cpn.x_num * cpn.b_num);
	printf("���Ȩ����\n");
	print_value(cpn.v_next, cpn.b_num * cpn.y_num);
	memcpy(cpn.w, cpn.w_next, cpn.x_num * cpn.b_num * sizeof(nn_type));
    memcpy(cpn.v, cpn.v_next, cpn.b_num * cpn.y_num * sizeof(nn_type));
    
}
#if 0
/* ѧϰ���� */
void cpn_do_use(nn_type * x)
{
    unsigned short i = 0, max_idx = 0, j = 0;
    nn_type * temp_vector = NULL;

        temp_vector = malloc(cpn.b_num * sizeof(nn_type));    
        /* 2) ��һ���������� */
        normalization(&x[0], cpn.x_num);
        printf("��������%d\n",i);
        print_value(&x[0], cpn.x_num);
        for(i=0; i<cpn.b_num; i++)
        {
            /* 3) ��Ԫ״̬�ͺ��� */        
            temp_vector[i] = nn_sum(x, &cpn.w[i*cpn.x_num], cpn.x_num);
        }
        printf("��Ԫ״̬��\n");
        print_value(temp_vector, cpn.b_num);
        /* 4) ��ȡ����������� */
        max_idx = nn_get_max_vector(temp_vector, cpn.x_num);
        free(temp_vector);
        
        /* 5) ��ʽ����� */
        memset(cpn.b, 0, cpn.b_num * sizeof(nn_type));
        cpn.b[max_idx] = 1;
        printf("��ʽ�����\n");
        print_value(cpn.b, cpn.b_num);
        
        /* 8) ���״̬�� */
        temp_vector = malloc(cpn.y_num * sizeof(nn_type));    
        for(i=0; i<cpn.y_num; i++)
        {        
            temp_vector[i] = nn_sum(&cpn.v[i*cpn.b_num], cpn.b, cpn.b_num);
        }
        printf("���״̬��\n");
        print_value(temp_vector, cpn.y_num);
        
        /* 9) �������Ȩ���� */    
        for(i=0; i<cpn.y_num; i++)
        {        
            cpn.v_next[i*cpn.b_num + max_idx] = cpn.v[i*cpn.b_num + max_idx] + 
                cpn.y_adjust*cpn.b[max_idx]*(temp_vector[i]-cpn.o[i*cpn.y_num]);        
            //normalization(&cpn.v_next[i*cpn.y_num], cpn.y_num);
        }
        free(temp_vector);

	printf("����Ȩ����\n");
	print_value(cpn.w_next, cpn.x_num * cpn.b_num);
	printf("���Ȩ����\n");
	print_value(cpn.v_next, cpn.b_num * cpn.y_num);
	memcpy(cpn.w, cpn.w_next, cpn.x_num * cpn.b_num * sizeof(nn_type));
    memcpy(cpn.v, cpn.v_next, cpn.b_num * cpn.y_num * sizeof(nn_type));
    
}
#endif /* if 0 end */

/* ��ʼ������ */
void cpn_init(unsigned short x_num, /* ������������ */
                    unsigned short b_num, /* ������������ */
                    unsigned short y_num, /* �������Ԫ���� */
                    nn_type b_adjust, /* ��������ϵ�� */
                    nn_type y_adjust/* �������ϵ�� */
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
    //TODO v v_next w w_next �����
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

