/***********************************************************************************************
* ��    �ߣ������
* ˵    ����������ʵ�ֵ���һ�ַǹ淶md5�㷨�������淶�ĵط������У�
*           1.�ַ�����bit������8��������������������ġ�2.�ַ�����bit���ȱ�������0~65535֮�䡣
***********************************************************************************************/
#include<stddef.h>
#include<stdio.h>
#include <string.h>

/*md5ת���õ��ĳ������㷨�����涨��*/
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* ѭ������ */
#define ROTATE_LEFT(md5_x, n) (((md5_x) << (n)) | ((md5_x) >> (32-(n))))

// ȫ�ֱ���
unsigned long  md5_x[16];/*�����ݴ���*/
unsigned long  md5_a,md5_b,md5_c,md5_d;/*�м����*/
unsigned long  md5_data[4];/*md5��*/

/***********************************************************************************************
* �������ܣ�md5�㷨����ĺ���
***********************************************************************************************/
unsigned long f(unsigned long md5_x,unsigned long y,unsigned long z)
{
	return (md5_x&y)|((~md5_x)&z);
}

unsigned long g(unsigned long md5_x,unsigned long y,unsigned long z)
{
	return (md5_x&z)|(y&(~z));
}

unsigned long h(unsigned long md5_x,unsigned long y,unsigned long z)
{
	return md5_x^y^z;
}

unsigned long i(unsigned long md5_x,unsigned long y,unsigned long z)
{
	return y^(md5_x|(~z));
}

// ��һ�����㺯��
void ff(unsigned long md5_x,unsigned long s,unsigned long ac)
{
	if(s==S11||s==S21||s==S31||s==S41)
	{
		md5_a+=f(md5_b,md5_c,md5_d)+md5_x+ac;
		md5_a=ROTATE_LEFT(md5_a,s);
		md5_a+=md5_b;
	}
	if(s==S12||s==S22||s==S32||s==S42)
	{
		md5_d+=f(md5_a,md5_b,md5_c)+md5_x+ac;
		md5_d=ROTATE_LEFT(md5_d,s);
		md5_d+=md5_a;
	}        
	if(s==S13||s==S23||s==S33||s==S43)
	{
		md5_c+=f(md5_d,md5_a,md5_b)+md5_x+ac;
		md5_c=ROTATE_LEFT(md5_c,s);
		md5_c+=md5_d;
	}        
	if(s==S14||s==S24||s==S34||s==S44)
	{
		md5_b+=f(md5_c,md5_d,md5_a)+md5_x+ac;
		md5_b=ROTATE_LEFT(md5_b,s);
		md5_b+=md5_c;
	}            
}

// �ڶ������㺯��
void gg(unsigned long md5_x,unsigned long s,unsigned long ac)
{
	if(s==S11||s==S21||s==S31||s==S41)
	{
		md5_a+=g(md5_b,md5_c,md5_d)+md5_x+ac;
		md5_a=ROTATE_LEFT(md5_a,s);
		md5_a+=md5_b;
	}
	if(s==S12||s==S22||s==S32||s==S42)
	{
		md5_d+=g(md5_a,md5_b,md5_c)+md5_x+ac;
		md5_d=ROTATE_LEFT(md5_d,s);
		md5_d+=md5_a;
	}        
	if(s==S13||s==S23||s==S33||s==S43)
	{
		md5_c+=g(md5_d,md5_a,md5_b)+md5_x+ac;
		md5_c=ROTATE_LEFT(md5_c,s);
		md5_c+=md5_d;
	}        
	if(s==S14||s==S24||s==S34||s==S44)
	{
		md5_b+=g(md5_c,md5_d,md5_a)+md5_x+ac;
		md5_b=ROTATE_LEFT(md5_b,s);
		md5_b+=md5_c;
	}
}

// ���������㺯��
void hh(unsigned long md5_x,unsigned long s,unsigned long ac)
{
	if(s==S11||s==S21||s==S31||s==S41)
	{
		md5_a+=h(md5_b,md5_c,md5_d)+md5_x+ac;
		md5_a=ROTATE_LEFT(md5_a,s);
		md5_a+=md5_b;
	}
	if(s==S12||s==S22||s==S32||s==S42)
	{
		md5_d+=h(md5_a,md5_b,md5_c)+md5_x+ac;
		md5_d=ROTATE_LEFT(md5_d,s);
		md5_d+=md5_a;
	}        
	if(s==S13||s==S23||s==S33||s==S43)
	{
		md5_c+=h(md5_d,md5_a,md5_b)+md5_x+ac;
		md5_c=ROTATE_LEFT(md5_c,s);
		md5_c+=md5_d;
	}        
	if(s==S14||s==S24||s==S34||s==S44)
	{
		md5_b+=h(md5_c,md5_d,md5_a)+md5_x+ac;
		md5_b=ROTATE_LEFT(md5_b,s);
		md5_b+=md5_c;
	}
}

// ���������㺯��
void ii(unsigned long md5_x,unsigned long s,unsigned long ac)
{
	if(s==S11||s==S21||s==S31||s==S41)
	{
		md5_a+=i(md5_b,md5_c,md5_d)+md5_x+ac;
		md5_a=ROTATE_LEFT(md5_a,s);
		md5_a+=md5_b;
	}
	if(s==S12||s==S22||s==S32||s==S42)
	{
		md5_d+=i(md5_a,md5_b,md5_c)+md5_x+ac;
		md5_d=ROTATE_LEFT(md5_d,s);
		md5_d+=md5_a;
	}        
	if(s==S13||s==S23||s==S33||s==S43)
	{
		md5_c+=i(md5_d,md5_a,md5_b)+md5_x+ac;
		md5_c=ROTATE_LEFT(md5_c,s);
		md5_c+=md5_d;
	}        
	if(s==S14||s==S24||s==S34||s==S44)
	{
		md5_b+=i(md5_c,md5_d,md5_a)+md5_x+ac;
		md5_b=ROTATE_LEFT(md5_b,s);
		md5_b+=md5_c;
	}
}

/***********************************************************************************************
* �������ƣ�unsigned long GetStrLen()
* �������ܣ���ȡ�ַ����ĳ���
* ��ڲ�����ptr--�ַ���ָ��
* ���ڲ�����len--32λ�ķ���ֵ
* ˵    ����ԭmd5�㷨Ҫ��洢�ַ������ȵı���Ϊ64λ����8���ֽڡ�����ֻ����4���ֽڣ�����Ӧ�ó���
*           �Ĳ�ͬ�޸���Ӧ�ı������弰����md5()�ж�x[14]md5_x[15]�ĸ�ֵ��伴�ɡ�
***********************************************************************************************/
unsigned long GetStrLen(unsigned char * ptr)
{
	unsigned long len=0;
	unsigned char * pTmp;
	
	pTmp=ptr;
	while(pTmp!=NULL&&(*pTmp)!='\0')
	{
		len++;
		pTmp++;
	}
	return len;
}

/***********************************************************************************************
* �������ƣ�void ByteToWord()
* �������ܣ���ָ��8λ�ַ�������Ϊһ����32λ���֣���������ݴ���x[]�У��ֵĸ������û�ָ��
* ��ڲ�����*ptr--8λ�ַ���ָ��    n--ָ�����ֵĸ���
* ���ڲ�����ȫ��x[]
* ˵    �����û����ڵ��ô˺���֮ǰ�Ȼ���ַ����ĳ��ȣ�Ȼ����ȷ����Ч�ġ�n��ֵ�����磬���ַ���
*           ����Ϊ7ʱ������ָ��nΪ2������������������������ ByteToWord(ptr,2)��
***********************************************************************************************/
void ByteToWord(unsigned char * ptr,unsigned char n)
{
	unsigned char  i,j;
	unsigned char * pTmp;
	unsigned long tmp;
	
	pTmp=ptr;
	
	for(i=0;i<n;i++)
	{
		md5_x[i]=0x00000000;
		tmp = 0;
		for(j=0;j<4;j++)
		{
			tmp>>=8;
			tmp +=*pTmp<<24;
			pTmp++;
		}
		md5_x[i] = tmp;
	}
}

/***********************************************************************************************
* �������ƣ�void md5_Print()
* �������ܣ����md5�Ľ��
***********************************************************************************************/
void md5_Print()
{
//	unsigned char i;
//	
//	for(i=0;i<4;i++)
//	{
//		printf("%02bx",(unsigned char)md5_data[i]);
//		printf("%02bx",(unsigned char)(md5_data[i]>>8));
//		printf("%02bx",(unsigned char)(md5_data[i]>>16));
//		printf("%02bx",(unsigned char)(md5_data[i]>>24));
//	}
}

/***********************************************************************************************
* �������ƣ�void md5_ProChunk()
* �������ܣ�md5���鴦��
***********************************************************************************************/
void md5_ProChunk()
{
	md5_a=md5_data[0];
	md5_b=md5_data[1];
	md5_c=md5_data[2];
	md5_d=md5_data[3];
	
	/* ��һ������ */
	ff(md5_x[ 0], S11, 0xd76aa478); /* 1 */
	ff(md5_x[ 1], S12, 0xe8c7b756); /* 2 */
	ff(md5_x[ 2], S13, 0x242070db); /* 3 */
	ff(md5_x[ 3], S14, 0xc1bdceee); /* 4 */
	ff(md5_x[ 4], S11, 0xf57c0faf); /* 5 */
	ff(md5_x[ 5], S12, 0x4787c62a); /* 6 */
	ff(md5_x[ 6], S13, 0xa8304613); /* 7 */
	ff(md5_x[ 7], S14, 0xfd469501); /* 8 */
	ff(md5_x[ 8], S11, 0x698098d8); /* 9 */
	ff(md5_x[ 9], S12, 0x8b44f7af); /* 10 */
	ff(md5_x[10], S13, 0xffff5bb1); /* 11 */
	ff(md5_x[11], S14, 0x895cd7be); /* 12 */
	ff(md5_x[12], S11, 0x6b901122); /* 13 */
	ff(md5_x[13], S12, 0xfd987193); /* 14 */
	ff(md5_x[14], S13, 0xa679438e); /* 15 */
	ff(md5_x[15], S14, 0x49b40821); /* 16 */
	
	/* �ڶ������� */
	gg(md5_x[ 1], S21, 0xf61e2562); /* 17 */
	gg(md5_x[ 6], S22, 0xc040b340); /* 18 */
	gg(md5_x[11], S23, 0x265e5a51); /* 19 */
	gg(md5_x[ 0], S24, 0xe9b6c7aa); /* 20 */
	gg(md5_x[ 5], S21, 0xd62f105d); /* 21 */
	gg(md5_x[10], S22,  0x2441453); /* 22 */
	gg(md5_x[15], S23, 0xd8a1e681); /* 23 */
	gg(md5_x[ 4], S24, 0xe7d3fbc8); /* 24 */
	gg(md5_x[ 9], S21, 0x21e1cde6); /* 25 */
	gg(md5_x[14], S22, 0xc33707d6); /* 26 */
	gg(md5_x[ 3], S23, 0xf4d50d87); /* 27 */
	gg(md5_x[ 8], S24, 0x455a14ed); /* 28 */
	gg(md5_x[13], S21, 0xa9e3e905); /* 29 */
	gg(md5_x[ 2], S22, 0xfcefa3f8); /* 30 */
	gg(md5_x[ 7], S23, 0x676f02d9); /* 31 */
	gg(md5_x[12], S24, 0x8d2a4c8a); /* 32 */
	
	/* ���������� */
	hh(md5_x[ 5], S31, 0xfffa3942); /* 33 */
	hh(md5_x[ 8], S32, 0x8771f681); /* 34 */
	hh(md5_x[11], S33, 0x6d9d6122); /* 35 */
	hh(md5_x[14], S34, 0xfde5380c); /* 36 */
	hh(md5_x[ 1], S31, 0xa4beea44); /* 37 */
	hh(md5_x[ 4], S32, 0x4bdecfa9); /* 38 */
	hh(md5_x[ 7], S33, 0xf6bb4b60); /* 39 */
	hh(md5_x[10], S34, 0xbebfbc70); /* 40 */
	hh(md5_x[13], S31, 0x289b7ec6); /* 41 */
	hh(md5_x[ 0], S32, 0xeaa127fa); /* 42 */
	hh(md5_x[ 3], S33, 0xd4ef3085); /* 43 */
	hh(md5_x[ 6], S34,  0x4881d05); /* 44 */
	hh(md5_x[ 9], S31, 0xd9d4d039); /* 45 */
	hh(md5_x[12], S32, 0xe6db99e5); /* 46 */
	hh(md5_x[15], S33, 0x1fa27cf8); /* 47 */ 
	hh(md5_x[ 2], S34, 0xc4ac5665); /*48 */
	
	/* ���������� */
	ii(md5_x[ 0], S41, 0xf4292244); /* 49 */
	ii(md5_x[ 7], S42, 0x432aff97); /* 50 */
	ii(md5_x[14], S43, 0xab9423a7); /* 51 */
	ii(md5_x[ 5], S44, 0xfc93a039); /* 52 */
	ii(md5_x[12], S41, 0x655b59c3); /* 53 */
	ii(md5_x[ 3], S42, 0x8f0ccc92); /* 54 */
	ii(md5_x[10], S43, 0xffeff47d); /* 55 */
	ii(md5_x[ 1], S44, 0x85845dd1); /* 56 */
	ii(md5_x[ 8], S41, 0x6fa87e4f); /* 57 */
	ii(md5_x[15], S42, 0xfe2ce6e0); /* 58 */
	ii(md5_x[ 6], S43, 0xa3014314); /* 59 */
	ii(md5_x[13], S44, 0x4e0811a1); /* 60 */
	ii(md5_x[ 4], S41, 0xf7537e82); /* 61 */
	ii(md5_x[11], S42, 0xbd3af235); /* 62 */
	ii(md5_x[ 2], S43, 0x2ad7d2bb); /* 63 */
	ii(md5_x[ 9], S44, 0xeb86d391); /* 64 */
	
	md5_data[0] += md5_a;
	md5_data[1] += md5_b;
	md5_data[2] += md5_c;
	md5_data[3] += md5_d;
}

/***********************************************************************************************
* �������ƣ�void md5(unsigned char* ptr)
* �������ܣ�����md5
***********************************************************************************************/
void MD5_Test(unsigned char* ptr)//��Ϊ�ǷǱ�棬�����������Ϊ8�ֽڵı���
{
	unsigned long  len, len1;
	unsigned char * pTmp;
	unsigned char  n,m;
	
	pTmp=ptr;
	len=strlen((char*)(pTmp));//��ȡ�ַ�������
	len1=len;
	
	md5_data[0]=0x67452301;
	md5_data[1]=0xefcdab89;
	md5_data[2]=0x98badcfe;
	md5_data[3]=0x10325476;
	
	// ����0����������Ҫ��λ����������
	while((len/64)>0)
	{  
		memset(md5_x,0x00,sizeof(md5_x));//����ByteToWord()�õ���ѭ����λ�����������x[]�Ļ����ܻ�����������Դ˴�Ҫ����
		ByteToWord(pTmp,16);//������ת����x[]��
		md5_ProChunk();//���鴦��
		len-=64;//������һ�������δ���д����ķ��鳤��Ҫ��ȥ64 Byte(512 bit)
		pTmp+=64;//ָ����һ������
	}
	// ����0
	
	// ����1��������Ҫ���в�λ�ķ���
	memset(md5_x,0x00,sizeof(md5_x));//�������ݴ���x[]����
	ByteToWord(pTmp,len/4);//�ַ���ת�����ִ���x[]
	
	// ����1.0 ��������ֽ���Ͻ���һ���ֲ����в�λ�����x[]
	n=len%4;
	m=len/4;
	switch(n)
	{
		case 0:
			md5_x[m]=md5_x[m]|0x00000080;//����0�ֽڵ����
		break;
		case 1:
			md5_x[m]=*pTmp;
			md5_x[m]=md5_x[m]|0x00008000;//����1�ֽڵ����
		break;
		case 2:
			md5_x[m]=*(pTmp+1);
			md5_x[m]=md5_x[m]<<8;
			md5_x[m]=md5_x[m]+(*pTmp);
			md5_x[m]=md5_x[m]|0x00800000;//����2�ֽڵ����
		break;
		case 3:
			md5_x[m]=*(pTmp+2);
			md5_x[m]=md5_x[m]<<8;
			md5_x[m]=md5_x[m]+*(pTmp+1);
			md5_x[m]=md5_x[m]<<8;
			md5_x[m]=md5_x[m]+(*pTmp);
			md5_x[m]=md5_x[m]|0x80000000;//����3�ֽڵ����
		default:;
	}
	// ����1.0
	
	if(len>=56)//���˷���ĳ��ȴ��ڵ���56ʱ��ദ��һ������
	{
		md5_ProChunk();
		memset(md5_x,0x00,sizeof(md5_x));
	}
	
	md5_x[14]=len1*8;//�����ַ�����λ��������Ϣ
	//md5_x[15]..
	md5_ProChunk();
	// ����1
	
	md5_Print();//������
}