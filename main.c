#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#define array_size 5
void readfile(char*fileName);
void type_FIFO();
void type_LRU();
void type_optimal();
void type_clock();
char type[20];
int *input;
int size;
int*buffer;
int n=0;
int main(){
scanf("%d",&size);
scanf("%s",type);
int i=-1;
input=(int*)malloc(array_size*sizeof(int));
int m=array_size-1;
do{
i++;
if(i>m){
input=(int*)realloc(input,(m+1+array_size)*sizeof(int));
m+=array_size;
}
scanf("%d",&input[i]);
}while(input[i]!=-1);
n=i;
buffer=(int*)malloc(size*sizeof(int));
if(strcmp(type,"CLOCK")==0)
type_clock();
else if(strcmp(type,"LRU")==0)
type_LRU();
else if(strcmp(type,"FIFO")==0)
type_FIFO();
else if(strcmp(type,"OPTIMAL")==0)
type_optimal();
else
printf("no such page replacement algorithm is available");
free(input);
return 0;
}
void type_FIFO(){
	printf("Replacement Policy = %s\n",type);
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	int i,j=0,k,available,pagefault=0,flag=0,fault=0;
	for(i=0;i<size;i++)//initialize buffer
		buffer[i]=-1;
	for(i=0;i<n;i++){
		available=0;
		for(k=0;k<size;k++){//check if page exists in the buffer
	 		if(buffer[k]==input[i])
				available=1;
		}
	if(available==0){//if it doesn't exist then...
		//printf("%d\n",buffer[j]);
		if(buffer[j]==-1)//check if buffer still has empty places
			flag=1;
		buffer[j]=input[i];//remove the item that its turn has come
	 	j=(j+1)%size;//get next place
		if(flag==0){//else then page fault
	 		pagefault++;//number of page faults
			fault=1; //flag to print F
		}
	}
	if(fault==1)
		printf("%02d F   ",input[i]);
	else
		printf("%02d     ",input[i]);
	for(k=0;k<size;k++){
		if(buffer[k]!=-1)
			printf("%02d ",buffer[k]);
	}
	printf("\n");
	flag=0;//reset after every loop
	fault=0;
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",pagefault);
}
void type_optimal(){
	printf("Replacement Policy = %s\n",type);
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	int i,j,k,p,available,pagefault=0,flag=0,temp[size],flag2=0,max,fault=0;
	for(i=0;i<size;i++)//initialize buffer 
		buffer[i]=-1;
//printf("size of buffer:%d\n",size);
	for(i=0;i<n;i++){//loop for the pages
	available=0;
	//check if page already exists in the buffer
	for(k=0;k<size;k++){
		if(buffer[k]==input[i]){
          	  available=1;
            	//printf("3mlha avail\n");
		}
		//printf("buffer in i =%d k=%d =%d\n",i,k,buffer[k]);
		}
if(available==0){ //if it doesn't exist then...
        //printf("d5lt walahy b value=%d\n",input[i]);
	for(k=0;k<size;k++){
		if(buffer[k]==-1)//check if there's empty place in the buffer
		{
			buffer[k]=input[i];
			//printf("availabe=0 %d\n",buffer[k]);
			flag=1;
			break;
			}
	}

	//buffer is full and the number doesn't exist in the buffer so we do replacement policy here
	if(flag==0){
		flag2=0;
		//printf("d5lt bvalue=%d\n",input[i]);
	//check if the numbers in the buffer will appear later or no
		for(j=0;j<size;j++){
			temp[j]=-1;
			for(k=i+1;k<n-1;k++){//if it does save its position
				if(buffer[j]==input[k]){
					temp[j]=k;
					//printf("temp%d\n",temp[j]);
					break;
				}
			}
		}
		for(j=0;j<size;j++){
//if it doesn't appear later in the input we save its position to replace it with another page
			if(temp[j]==-1){
				p=j;
				flag2=1;
				break;
			}
	}
//if all of them will appear later so we have to choose one to remove from the buffer
	if(flag2==0){
		max=temp[0];
		p=0;
//check which will come the latest as we saved their positions in temp and remove it
		for(j=1;j<size;j++){
			if(temp[j]>max){
				max=temp[j];
				p=j;
			}
		}
	}
	buffer[p]=input[i];
	//printf("buffer[%d]\n",buffer[p]);
	pagefault++;//number of page faults 
	//printf("pagefault=%d\n",pagefault);
	fault=1;//flag to print F
	}
}
	if(fault==1)
		printf("%02d F   ",input[i]);
	else
		printf("%02d     ",input[i]);
	for(k=0;k<size;k++){
		if(buffer[k]!=-1)
			printf("%02d ",buffer[k]);
	}
	printf("\n");
	available=flag=flag2=fault=0;//reset after each loop
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",pagefault);
}
void type_LRU(){
	printf("Replacement Policy = %s\n",type);
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
int i,j,k,p,available,pagefault=0,flag=0,temp[size],flag2=0,min,counter=0,fault=0;
	for(i=0;i<size;i++)//initialize the buffer
		buffer[i]=-1;
	for(i=0;i<n;i++){//loop for the pages
		for(j=0;j<size;j++){//check if page exist in th buffer
			if(buffer[j]==input[i]){
				counter++;//save every time the number comes
				temp[j]=counter;
				//save the time when the number came
				flag=flag2=1;
			}
		}
		if(flag==0){//if it doesn't exist then...
			for(k=0;k<size;k++){
				//check if there's an empty place in the buffer
				if(buffer[k]==-1){
					counter++;
					//save the time when the number came
					buffer[k]=input[i];
					//printf("availabe=0 %d\n",buffer[k]);
					temp[k]=counter;
					flag2=1;
					break;
					}
				}
			}
		if(flag2==0){//else remove the least recently used
		min=temp[0];
		p=0;
//check which has smallest counter value in temp and remove it as it's the LRU page
		for(j=1;j<size;j++){
			if(temp[j]<min){
				min=temp[j];
				p=j;
			}
		}
		counter++;
		buffer[p]=input[i];
		//printf("buffer[%d]\n",buffer[p]);
		pagefault++;
		fault=1;
		//printf("pagefault=%d\n",pagefault);	
		temp[p]=counter;
		}
	if(fault==1)
		printf("%02d F   ",input[i]);
	else
		printf("%02d     ",input[i]);
	for(k=0;k<size;k++){
		if(buffer[k]!=-1)
			printf("%02d ",buffer[k]);
	}
	flag=flag2=fault=0;//reset after each loop
	printf("\n");
	}//di bt3t elfor elkabeera
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",pagefault);
}
void type_clock(){
	printf("Replacement Policy = %s\n",type);
	printf("-------------------------------------\n");
	printf("Page   Content of Frames\n");
	printf("----   -----------------\n");
	int i,j=0,p=0,pagefault=0,flag=0,use_bit[size],fault=0,k;
	for(i=0;i<size;i++){//initialize buffer and use bit
		buffer[i]=-1;
		use_bit[i]=0;
	}
for(i=0;i<n;i++){//loop for the pages
		for(j=0;j<size;j++){//check if page already exists in the buffer
			if(buffer[j]==input[i]){
				flag=1;
				use_bit[j]=1;//set use bit
			}
		}
		if(flag==0){//if it doesn't exists then...
			while(flag!=1){
				//check if the buffer has an empty place 
				if(use_bit[p]==0&&buffer[p]==-1){
					buffer[p]=input[i];
					use_bit[p]=1;
					flag=1;
				}
				else if(use_bit[p]==0&&buffer[p]!=-1){//if not
					buffer[p]=input[i];
					use_bit[p]=1;
					flag=1;
					pagefault++;
					fault=1;
					}
				//then buffer is full so we set the use bit to 0 to remove that page from buffer the next time
				else
					use_bit[p]=0;
				p=(p+1)%size;
			}



		}
	if(fault==1)
		printf("%02d F   ",input[i]);
	else
		printf("%02d     ",input[i]);
	for(k=0;k<size;k++){
		if(buffer[k]!=-1)
			printf("%02d ",buffer[k]);
	}
	flag=fault=0;//reset
	printf("\n");	
}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",pagefault);
}
