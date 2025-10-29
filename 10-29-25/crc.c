#include <stdio.h>
#include <string.h>
#define N strlen(poly)

char data[30];
char check_value[30];
char poly[30];
int dlen, i, j;

void XOR(){
  for(j=1;j<N;j++){
    check_value[j]=check_value[j]==poly[j]?'0':'1';
  }
}

void crc(){
  for(i=0;i<N;i++){
    check_value[i]=data[i];
  }
  do{
    if(check_value[0]=='1'){
     XOR();
    }
    for (j=0; j<N-1; j++) {
      check_value[j]=check_value[j+1];
    }
    check_value[j]=data[i++];
  }while(i<=dlen+N+1);
}

void receiver(){
  printf("Enter string:");
  scanf("%s",data);
  crc();
  for(i=0;i<N-1&&check_value[i]!='1';i++);
  if(i<N-1)
    printf("Error detected\n");
  else
    printf("No Error detected\n");
}

int main(){
  printf("Enter data:");
  scanf("%s",   data);
  printf("Enter poly:");
  scanf("%s",   poly);
  dlen = strlen(data);
  for(i=dlen;i<dlen+N-1;i++)
    data[i]='0';
  crc();
  printf("CRC:%s\n",check_value);
  for(i=dlen;i<dlen+N-1;i++)
    data[i]=check_value[i-dlen];
  printf("To Receive data:%s\n",data);
  receiver();
  return 0;
}
