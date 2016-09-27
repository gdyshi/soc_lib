#include "includes.h"

unsigned long candp(unsigned long a,unsigned long b,unsigned long c)
{
	unsigned long r=1;

	b = b+1;
	while(b!=1)
	{
		r = r*a;
		r = r%c;
		b--;
	}
	return r;
}

unsigned long RSA_Key[3]=
{
	17,7,5	//������֮ǰ��Ҫ���ú���Կ������ֻ��������Կ��DEMO��
};

unsigned char RSA_Test(unsigned long Source, unsigned long Target, unsigned char mode)
{
	unsigned long d,n,t,tt;
	unsigned long p,q,e;
	Target = Target;

	p =	RSA_Key[0];
	q =	RSA_Key[1];
	e = RSA_Key[2];

	n = p*q;
	t = (p-1)*(q-1);

	if(e<1 || e>t)
	{
		return 0;
	}

	switch(mode)
	{
		case 1:
			Target = candp(Source,e,n);//SourceΪҪ���ܵ���������
		break;
		case 2://������ܻ�����ر�����������Ҫ���ɴ�����������ȡģ���ܺķ�ʱ�䣬���ɸ�����Կʱ���ܲ�ֹʮ���ӣ����Խ���ʱ���Ǿ�����PC������
			d = 0;
			do{
			    d++;
				tt = (e*d)%t;
			}while(tt!=1);
			Target = candp(Source,d,n);//SourceΪҪ���ܵ���������
		break;
	}
	return 1;
}