/*
SY A16
Data Communication
Course Project
Simulation of Encoding,Decoding and modulation of 10mbps etherrnet network
Submitted by:-
Aditya G.(61)
Archit H.(64)
Harsh p.(67)
Abhishek H.(69)

*/

#include<iostream>
#include<graphics.h>
#include<math.h>
#include<string.h>

using namespace std;

void Encode(char input[],char encoded[])
{

    int tp=120,amp=30,sine_wave_x=450,samp_x=400,md_x=450,tp_s=12;
    //char input[1000];
    int y1=150,y2=70;
    //char encoded[10000];
    int encoding_idx=0;
    outtextxy(250,y2+25,"Orignal Data");
    outtextxy(250,y1+60,"Manchester Encoded Data");
    //cout<<"Enter binary data you want to transfer\n";
    //cin>>input;
    //cout<<"Encoded binary string:-";

    for(int i=0; i<strlen(input); i++)
    {
        if(input[i]=='1')
        {
            //cout<<"01";
            encoded[encoding_idx]='0';
            encoded[encoding_idx+1]='1';
            encoding_idx+=2;
        }
        else
        {
            //cout<<"10";
            encoded[encoding_idx]='1';
            encoded[encoding_idx+1]='0';
            encoding_idx+=2;
        }
    }
    //cout<<"\n";
    //cout<<"##"<<encoded;
    int h=50;
    int x=0,len=20;
    line(0,y1,2000,y1);
    line(0,y2,2000,y2);
    setcolor(13);
    //For Normal Data printing
    for(int i=0; i<strlen(input); i++)
    {
        delay(1000);
        if(i>=1 && input[i]!=input[i-1])
        {
            line(x,y2-h,x,y2);
        }
        if(input[i]=='1')
        {
            line(x,y2-h,x+2*len,y2-h);
            outtextxy(x+len,y2+10,"1");
        }
        else
        {
            line(x,y2,x+2*len,y2);
            outtextxy(x+len,y2+10,"0");
        }

        x+=2*len;
    }


    //Manchester Encoding
    x=0;
    setcolor(GREEN);
    for(int i=0; i<strlen(input); i++)
    {
        delay(1000);
        if(i>=1 && input[i]==input[i-1])
        {
            line(x,y1-h/2,x,y1+h/2);
        }
        if(input[i]=='1')
        {
            line(x,y1+h/2,x+len,y1+h/2);
            line(x+len,y1+h/2,x+len,y1-h/2);
            line(x+len,y1-h/2,x+2*len,y1-h/2);
            outtextxy(x+len/2,y1+30,"0");
            outtextxy(x+len*3/2,y1+30,"1");
            x+=2*len;

        }
        else
        {
            line(x,y1-h/2,x+len,y1-h/2);
            line(x+len,y1-h/2,x+len,y1+h/2);
            line(x+len,y1+h/2,x+2*len,y1+h/2);
            outtextxy(x+len/2,y1+30,"1");
            outtextxy(x+len*3/2,y1+30,"0");
            x+=2*len;
        }

    }
    //getch();
    //closegraph();




}

void decode(char encoded[])
{
    int tp=120,amp=30,sine_wave_x=450,samp_x=400,md_x=450,tp_s=12;
    char input[1000],dc[1000],z=0;
    //outtextxy(250,150,"Decoded Data");
    //outtextxy(250,350,"Orignal Data");
    int y1=150,y2=350;
    //cout<<"Enter binary data you want to Decode\n";
    //cin>>input;
    int ii=0;
    while(encoded[ii]!='\0')
    {
        input[ii]=encoded[ii];
        ii++;
    }
    cout<<"Decoded binary string(Manchester):-";

        for(int i=0; i<strlen(input)-1; i+=2)
        {
            if(input[i]=='0' && input[i+1]=='1')
            {
                cout<<"1";
                dc[z++]='1';
            }
            else if(input[i]=='1' && input[i+1]=='0')
            {
                cout<<"0";
                dc[z++]='0';
            }
            else
            {
                //cout<<"Invalid Input";
                break;
            }
        }
        cout<<"\n";





}

void modulate()
{
    int tp=200,amp=50,sine_wave_x=100,samp_x=250,md_x=350,tp_s=12;
    float interval=(3.14/tp)*2;
    outtextxy(250,160,"Orignal Signal");
    outtextxy(250,270,"Sampling Signal");
    outtextxy(250,420,"PAM modulated signal");
    //initgraph(&gd,&gm,NULL);


    /* ***************************************** */

    int x=0,len=50;
    line(0,sine_wave_x,2000,sine_wave_x);
    line(0,samp_x,2000,samp_x);
    line(0,md_x,2000,md_x);
    setcolor(RED);
//For normal sine wave
    for(int i=0; i<=1000; i++)
    {
        float x=(i%tp)*interval;
        int y=sin(x)*amp;
        putpixel(i,sine_wave_x-y,RED);
    }

    setcolor(GREEN);
    //For sampling signal
    for(int i=0; i<1000; i+=tp_s)
    {
        line(i,samp_x,i,samp_x-amp);
        line(i,samp_x-amp,i+tp_s/2,samp_x-amp);
        line(i+tp_s/2,samp_x,i+tp_s/2,samp_x-amp);
        line(i+tp_s/2,samp_x,i+tp_s,samp_x);
    }

    setcolor(YELLOW);
    //for PAM modulated signal
    for(int i=5; i<=1000; i+=tp_s)
    {
        float x=(i%tp)*interval;
        int y=sin(x)*amp;
        line(i-tp_s/4,md_x,i-tp_s/4,md_x-y);
        line(i-tp_s/4,md_x-y,i+tp_s/4,md_x-y);
        line(i+tp_s/4,md_x-y,i+tp_s/4,md_x);
        line(i+tp_s/4,md_x,i+tp_s,md_x);
    }
    getch();
    closegraph();

}

void print_sin(float a,float b,int amp,float period,int hz,int x)
{
    float pi=3.14;
    int pam_rate=5;
    float l=x;
    int r=x+(b-a)*period;
    setcolor(GREEN);
    line(0,hz-amp,2000,hz-amp);
    line(0,hz+amp,2000,hz+amp);
    line(l,hz-amp,l,hz+amp);
    line(r,hz-amp,r,hz+amp);
    setcolor(YELLOW);
    for(int i=l; i<=r; i+=pam_rate)
    {
        float y=(a+(i-l)/period)*3.14*2;
        //cout<<y;
        //putpixel(i,hz-amp*sin(y),GREEN);
        line(i-1,hz,i-1,hz-amp*sin(y));
        line(i-1,hz-amp*sin(y),i+1,hz-amp*sin(y));
        line(i+1,hz,i+1,hz-amp*sin(y));
        delay(100);


    }
}

void samplingsignal(int hz,int amp,int period,int x)
{
    for(int i=0; i<2000; i++)
    {
        line(x,hz,x,hz-amp);
        line(x,hz-amp,x+period/2,hz-amp);
        line(x+period/2,hz-amp,x+period/2,hz);
        line(x+period/2,hz,x+period,hz);
        x=x+period;
    }
    outtextxy(250,hz+10,"Sampling Signal");
}
void modulate_encoded(char manchester[],int t[])
{
    int x=0;
    int ii=0;
    float amp=30,period=120,hz=400,pam_rate=4;
    outtextxy(250,hz+amp+30,"Modulated Signal");

    for (int i=0; i<strlen(manchester); i++)
    {



        if(i>0 && manchester[i]==manchester[i-1])
        {
            line(x,hz-amp,x,hz+amp);
        }
        if(manchester[i]=='1')
        {
            t[ii]=-1;
            t[ii+1]=1;
            ii+=2;

            print_sin(-0.25,0.25,amp,period,hz,x);
            outtextxy(x+period/4,hz+amp+10,"1");
        }
        else
        {
            t[ii]=1;
            t[ii+1]=-1;
            ii+=2;
            print_sin(0.25,0.75,amp,period,hz,x);
            outtextxy(x+period/4,hz+amp+10,"0");
        }
        x=x+period/2;
    }
    //getch();
    //closegraph();

}

void final_decode(int decode_modulated[],char final_signal[])
{
    int i=0;
    cout<<"Voltage Levels in analog signal-->";
    while(decode_modulated[i]==1 || decode_modulated[i]==-1)
    {
        cout<<decode_modulated[i]<<" ";
        if(decode_modulated[i]==1)
        {
            final_signal[i]='1';
        }
        else
        {
            final_signal[i]='0';
        }
        i++;
        if(i==100)
        {
            break;
        }
    }
}

int main()
{

    int choice=1511;

    char input[100],encoded[100],final_signal[100];
    int decode_modulated[100],manc_to_orig[100];
    cout<<"Enter data you want to transfer-->";
    cin>>input;

    int gd = DETECT, gm;
    initgraph(&gd, &gm,NULL);
    Encode(input,encoded);
    cout<<"Manchester code for above data-->";
    for(int i=0; i<strlen(encoded)-1&&encoded[i]!='\0'; i++)
    {
        cout<<encoded[i];
    }
    cout<<endl;
//int gd = DETECT, gm;
    //initgraph(&gd, &gm,NULL);
    samplingsignal(300,50,4,-1);
    modulate_encoded(input,decode_modulated);
    setcolor(RED);
    final_decode(decode_modulated,final_signal);
    cout<<endl;
    cout<<"Decoded Manchester Code-->";
    for(int i=0; final_signal[i]=='1' || final_signal[i]=='0'; i++)
    {
        cout<<final_signal[i];
    }
    cout<<endl;

    decode(final_signal);

    //delay(10000);
    getch();
    closegraph();


}
//Encode(input,encoded);
// modulate_encoded(encoded,decode_modulated);
