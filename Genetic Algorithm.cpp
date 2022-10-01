#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;
float obj(float x1,float x2)
{
    return ((x1+x2)-(2*x1*x1)-(x2*x2)+(x1*x2));
}
int main()
{
    fstream out("Output File1.txt",ios::in | ios::out | ios::app);
    int x1[10][5],x2[10][5],n=10,l=5,i,j,k,val[10][2],m_pool_x1[10][5],m_pool_x2[10][5];
    float xmin=0,xmax=0.5,c1,real[10][2],fit[10],total_fit=0,prob[10],cum[10],rn1[10],rn2;
    int index[10],val1[10][2],gen=0;
    float temp,pm=0.1,pm1[10],pm2[10],real1[10][2],fit1[10],total_fit1;
    c1=(xmax-xmin)/(pow(2,l)-1);
    srand(time(0));
    for(i=0;i<n;i++)
    {
        for(j=0;j<5;j++)
        {
            x1[i][j]=rand()%2;
            x2[i][j]=rand()%2;
        }
    }

    out<<"Initial Population of Random Solution"<<endl;
    while (gen<=10)
    {
    if(gen!=0) 
    {
    out<<endl;    
    out<<"Next Generation of Solution"<<endl;
    }
    out<<"Strings"<<"\t"<<"X1"<<"\t"<<"X2"<<endl;
    for(i=0;i<n;i++)
    {
        out<<"S"<<i+1<<"\t";
        for(j=0;j<l;j++)
        {
            out<<x1[i][j];
        }
        out<<"\t";    
            for(k=0;k<l;k++)
            {
                out<<x2[i][k];
            }
        out<<endl;
    }
    out<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<2;j++)
        {
            val[i][j]=0;
        }
    }
    out<<"Decoded Value of each string is as follows"<<endl;
    out<<"Strings"<<"\t"<<"X1"<<"\t"<<"X2"<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<l;j++)
        {
            val[i][0]+=x1[i][j]*pow(2,l-j-1);
            val[i][1]+=x2[i][j]*pow(2,l-j-1);
        }
    }
    for(i=0;i<n;i++)
    {
        out<<"S"<<i+1<<"\t";
        for(j=0;j<2;j++)
        {
            out<<val[i][j]<<"\t";
        }
        out<<endl;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<l;j++)
        {
            real[i][0]=c1*val[i][0];
            real[i][1]=c1*val[i][1];
        }
    }
    out<<endl;
    out<<"Real Value of each string is as follows"<<endl;
    out<<"Strings"<<"\t"<<"X1"<<"\t\t"<<"X2"<<endl;
    for(i=0;i<n;i++)
    {
        out<<"S"<<i+1<<"\t";
        for(j=0;j<2;j++)
        {
            out<<real[i][j]<<"\t";
        }
        out<<endl;
    }
    out<<endl;
    out<<"Fitness Value of Each String is as follows"<<endl;
    out<<"Strings"<<"\t"<<"Fitness Value"<<endl;
    for(i=0;i<n;i++)
    {
            fit[i]=obj(real[i][0],real[i][1]);
            out<<"S"<<i+1<<"\t"<<fit[i]<<endl;
            total_fit+=fit[i];
    }
    for(i=0;i<n;i++)
    {
        prob[i]=fit[i]/total_fit;
    }
    cum[0]=prob[0];
    for(i=0;i<n-1;i++)
    {
        cum[i+1]=cum[i]+prob[i+1];
    }
    out<<endl;
    out<<"Roulette Wheel Table is shown below"<<endl;
    out<<"Strings"<<"\t"<<"X1"<<"\t"<<"X2"<<"\t"<<"Fitness"<<"\t\t"<<"Probability"<<"\t"<<"Cumulative Probability"<<endl;
    for(i=0;i<n;i++)
    {
        out<<"S"<<i+1<<"\t";
        for(j=0;j<l;j++)
        {
            out<<x1[i][j];
        }
        out<<"\t";
        for(k=0;k<l;k++)
        {
            out<<x2[i][k];
        }
        out<<"\t"<<fit[i]<<"\t"<<prob[i]<<"\t"<<cum[i]<<endl;
    }
    out<<endl;
    out<<"Random Number generated is shown below"<<endl;
    for(i=0;i<n;i++)
    {
        rn1[i]=(float)rand()/RAND_MAX;
        out<<rn1[i]<<"\t";
    }
    out<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
        if(rn1[i]>0 && rn1[i]<cum[0])
        {
            index[i]=0;
            for(k=0;k<l;k++)
            {
                m_pool_x1[i][k]=x1[0][k];
                m_pool_x2[i][k]=x2[0][k];
            }
        }
        else if(rn1[i]>=cum[j] && rn1[i]<cum[j+1])
        {
            index[i]=j+1;
            for(k=0;k<l;k++)
            {
                m_pool_x1[i][k]=x1[j+1][k];
                m_pool_x2[i][k]=x2[j+1][k];
            }
        }
        }
    }
    out<<endl;
    out<<"Mating Pool is shown below"<<endl;
    out<<"Strings"<<"\t"<<"X1"<<"\t"<<"X2"<<"\t"<<"Fitness"<<endl;
    for(i=0;i<n;i++)
    {
        out<<"S"<<index[i]+1<<"\t";
        for(j=0;j<l;j++)
        {
            out<<m_pool_x1[i][j];
        }
        out<<"\t";    
            for(k=0;k<l;k++)
            {
                out<<m_pool_x2[i][k];
            }
        out<<"\t"<<fit[index[i]]<<endl;
    }
    rn2=rand()%10;
    out<<endl;
    out<<"Random Number for single point crossover is "<<rn2<<endl;
    for(i=0;i<n;i+=2)
    {
            if(rn2<l)
            {
            for(j=rn2;j<l;j++)
            {
                temp=m_pool_x1[i][j];
                m_pool_x1[i][j]=m_pool_x1[i+1][j];
                m_pool_x1[i+1][j]=temp;
            }    
                for(k=0;k<l;k++)
                {
                    temp=m_pool_x2[i][k];
                    m_pool_x2[i][k]=m_pool_x2[i+1][k];
                    m_pool_x2[i+1][k]=temp;
                }
            }
            else
            {
                for(k=rn2-l;k<l;k++)
                {
                    temp=m_pool_x2[i][k];
                    m_pool_x2[i][k]=m_pool_x2[i+1][k];
                    m_pool_x2[i+1][k]=temp;
                }
            }
        }
    out<<"Mating Pool after crossover is shown below"<<endl;
    out<<"Strings"<<"\t"<<"X1"<<"\t"<<"X2"<<endl;
    for(i=0;i<n;i++)
    {
        out<<"Ch"<<i+1<<"\t";
        for(j=0;j<l;j++)
        {
            out<<m_pool_x1[i][j];
        }
        out<<"\t";    
            for(k=0;k<l;k++)
            {
                out<<m_pool_x2[i][k];
            }
        //out<<"\t"<<fit[index[i]]<<"\t"<<prob[index[i]]<<"\t"<<cum[index[i]]<<endl;
        out<<endl;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<l;j++)
        {
            pm1[j]=(float)rand()/RAND_MAX;
            pm2[j]=(float)rand()/RAND_MAX;
            if(pm1[j]<pm)
            {
                if(m_pool_x1[i][j]==0)
                m_pool_x1[i][j]=1;
                else
                m_pool_x1[i][j]=0;
            }

            if(pm2[j]<pm)
            {
                if(m_pool_x2[i][j]==0)
                m_pool_x2[i][j]=1;
                else
                m_pool_x2[i][j]=0;
            }
        }
    }
    out<<endl;

        for(i=0;i<n;i++)
        {
        for(j=0;j<2;j++)
        {
            val1[i][j]=0;
        }
        }
        for(i=0;i<n;i++)
        {
        for(j=0;j<l;j++)
        {
            val1[i][0]+=m_pool_x1[i][j]*pow(2,l-j-1);
            val1[i][1]+=m_pool_x2[i][j]*pow(2,l-j-1);
        }
        }
        for(i=0;i<n;i++)
        {
        for(j=0;j<l;j++)
        {
            real1[i][0]=c1*val1[i][0];
            real1[i][1]=c1*val1[i][1];
        }
        }
        for(i=0;i<n;i++)
        {
            fit1[i]=obj(real1[i][0],real1[i][1]);
            //out<<"S"<<i+1<<"\t"<<fit1[i]<<endl;
            total_fit1+=fit1[i];
        }

    out<<"Mating Pool after Mutation is shown below"<<endl;
    out<<"Strings"<<"\t"<<"X1"<<"\t"<<"X2"<<"\t"<<"Decoded(X1)"<<"\t"<<"Decoded(X2)"<<"\t"<<"Real(X1)"<<"\t"<<"Real(X2)"<<"\t"<<"Fitness"<<endl;
    for(i=0;i<n;i++)
    {
        out<<"Ch"<<i+1<<"\t";
        for(j=0;j<l;j++)
        {
            out<<m_pool_x1[i][j];
        }
        out<<"\t";    
            for(k=0;k<l;k++)
            {
                out<<m_pool_x2[i][k];
            }
        out<<"\t"<<val1[i][0]<<"\t\t"<<val1[i][1]<<"\t\t"<<real1[i][0]<<"\t"<<real1[i][1]<<"\t"<<fit1[i];
        out<<endl;
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<l;j++)
        {
            x1[i][j]=m_pool_x1[i][j];
            x2[i][j]=m_pool_x2[i][j];
        }
    }
    gen++;
    }
}
