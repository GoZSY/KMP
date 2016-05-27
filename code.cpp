/***********************************************************************
    利用next数组
    举个例子，举例说明下上述求next数组的方法。
    S a b a b a b c
    P a b a b c
    S[4] != P[4]
        那么下一个和S[4]匹配的位置是k=2(也即P[next[4]])。此处的k=2也再次佐证了上文第3节开头处关于为了找到下一个匹配的位置时k的求法。上面的主串与模式串开头4个字符都是“abab”，所以，匹配失效后下一个匹配的位置直接跳两步继续进行匹配。
    S a b a b a b c
    P      a b a b c
    匹配成功

    P的next数组值分别为-1 0 -1 0 2

        next数组各值怎么求出来的呢?分以下五步：

        初始化：i=0，j=-1，nextval[0] = -1。由于j == -1，进入上述循环的if部分，++i得i=1，++j得j=0，且ptrn[i] != ptrn[j]（即a！=b）），所以得到第二个next值即nextval[1] = 0；；
        i=1，j=0，进入循环esle部分，j=nextval[j]=nextval[0]=-1；
        进入循环的if部分，++i，++j，i=2，j=0，因为ptrn[i]=ptrn[j]=a,所以nextval[2]=nextval[0]=-1；
        i=2, j=0, 由于ptrn[i]=ptrn[j],再次进入循环if部分，所以++i=3，++j=1,因为ptrn[i]=ptrn[j]=b,所以nextval[3]=nextval[1]=0；
        i=3,j=1,由于ptrn[i]=ptrn[j]=b,所以++i=4，++j=2,退出循环。

    这样上例中模式串的next数组各值最终应该为:
     a b  a b
    -1 0 -1 0
************************************************************************/
class StringPattern {
public:
    int findAppearance(string A, int lena, string B, int lenb) 
    {
        // write code here
        vector<int> next(lenb,0);
        getNext(next,B,lenb);
        int i = 0;
        int j = 0;
        while(i < lena && j < lenb)
        {
            if(j == -1 || A[i] == B[j])
            {
                i++;
                j++;
            }
            else
            {
                j = next[j];
            }
        }
        if(j == lenb)
            return i-j;
        
        return -1;
        
    }
private:
    void getNext(vector<int> &next, string B, int length)
    {
        int i = 0;
        next[0] = -1;
        int j = -1;
        while(i < length-1)
        {
            if(j == -1 || B[i] == B[j])
            {
                if(B[++j]!=B[++i])
                {
                    next[i] = j;
                }
                else
                    next[i] = next[j];
            }
            else
                j = next[j];
        }
    }
};
/*****************************************************************************************
求next数组的方式不同，这次是从下标1开始
覆盖函数所表征的是pattern本身的性质，可以让为其表征的是pattern从左开始的所有连续子串的自我覆盖程度。
比如如下的字串，abaabcaba
a（-1） b（-1）a（0） a（0） b（1） c（-1） a（0） b（1）a（2）
解释：
    初始化为-1  
    b与a不同为-1   
    与第一个字符a相同为0   
    还是a为0   
    后缀ab与前缀ab两个字符相同为1 
    前面并无前缀c为-1  
    与第一个字符同为0  
    后缀ab前缀ab为1 
    前缀aba后缀aba为2

******************************************************************************************/
int kmp_find(const string& target,const string& pattern)  
{  
    const int target_length=target.size();  
    const int pattern_length=pattern.size();  
    int* overlay_value=new int[pattern_length];  
    overlay_value[0]=-1;        //remember:next array's first number was -1.  
    int index=0;  
  
    /************************next array****************************/  
    for (int i=1;i<pattern_length;++i)  
        //注，此处的i是从1开始的  
    {  
        index=overlay_value[i-1];  
        while (index>=0 && pattern[index+1]!=pattern[i])  //remember:!=  
        {  
            index=overlay_value[index];  
        }  
        if(pattern[index+1] == pattern[i])  
        {  
            overlay_value[i]=index+1;  
        }  
        else  
        {  
            overlay_value[i]=-1;  
        }  
    }  
  /*****************************next array*********************************/ 
  /************************mach algorithm start****************************/  
      
    int pattern_index=0;  
    int target_index=0;  
    while (pattern_index<pattern_length && target_index<target_length)  
    {  
        if (target[target_index] == pattern[pattern_index])  
        {  
            ++target_index;  
            ++pattern_index;  
        }   
        else if(pattern_index==0)  
        {  
            ++target_index;  
        }  
        else  
        {  
            pattern_index=overlay_value[pattern_index-1]+1;  
        }  
    }  
    if (pattern_index==pattern_length)  
    {  
        return target_index-pattern_index;  
    }   
    else  
    {  
        return -1;  
    }  
    delete [] overlay_value;  
}  
