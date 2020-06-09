/**
*@author Nearchos Nearchou 
*@filename encode.c
*@version 1.0
*@bug no known bugs
*/

/*
<Wavengine is a program that modifies wav files>
Copyright (C)   <2018> <Michalis Kailis, Nearchos Nearchou>\n 
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License\n as published by
the Free Software Foundation, either version 3 of the License,\n or at your option) any later version.
This program is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n See the GNU General Public License for more details.
Υou should have received a copy of the \n GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "header.h"

#define KEY 3
PRIVATE int getSize(char *m);
PRIVATE int getBit(char *m, int n);


void encode (char *name,char *text)
{
   
   HEADER *head = (HEADER*)malloc(sizeof(HEADER));
   DATA *data = (DATA*)malloc(sizeof(DATA));
   if (data == NULL || head == NULL) 
   {
      printf("Error Allocating \n");
      return ;
   }
   
   read(head,data,name);
   char new_name[4];
   strcpy(new_name, "new-");
   int *permutation;
   int x,u,i;
   permutation =createPermutationFunction(head->subchunk2size,KEY);
   int size=getSize(text);
   
    for(i = 0; i <(1+size)*8 ; i++)
    {
        u=getBit(text,i);
        x=permutation[i];
        if(u)
        {
        data -> table[x]|=0x1;
        }
        else
        {
        data -> table[x]&=~(0x1);
        }
    }
   FILE *fp1;
   strcat(new_name,name);
   fp1 = fopen(new_name, "wb");
   fwrite(head, sizeof(HEADER), 1, fp1); 
   fwrite(data -> table, sizeof(byte),  head -> subchunk2size, fp1);
   fclose(fp1);
   free(head);
   free(data->table);
   free(data);
   free(permutation);

 

}
int* createPermutationFunction(int N, unsigned int systemkey){
    int num1,num2,i;
    int *array=malloc(sizeof(int)*N);
    int temp;
    for(i=0;i<N-1;i++){
        array[i]=i;
    }
    srand(systemkey);
    for(i=0;i<N;i++){
        num1=rand()%(N-1);
        num2=rand()%(N-1);
        temp = array[num1];
        array[num1] = array[num2];
        array[num2] = temp;
    }
    return array;

}
PRIVATE int getSize(char *m)
{
    FILE *fp;
    fp = fopen(m, "r");
    if (fp == NULL)
   {
      printf("Error opening file: %s\n", m);
      return 0;
   }
    char c;
    int j=0;
    do
    {

    c = fgetc(fp);
    j++;

    }while (c != EOF);
    fclose(fp);
    return j;
}
PRIVATE int getBit(char *m, int n){
    FILE *fp;
    int i;
    fp = fopen(m, "r");
    if (fp == NULL)
    {
      printf("Error opening file: %s\n", m);
      return 0;
    }
    char c;
    int array[1000];
    int temp;
    c = fgetc(fp);
    int j=0;
    int count=7;
    do
    {

    for(i=0;i<8;i++){
    temp=(c >> i ) & 1;
    array[count-i]=temp;
    }
    count=count+8;
    c = fgetc(fp);
    j++;

    }while (c != EOF);
    fclose(fp);
    return array[n];

}
