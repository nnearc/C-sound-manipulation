/**
*@author Nearchos Nearchou 
*@filename decode.c
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

void decode (char *name,char *size,char *text)
{
   HEADER *head = (HEADER*)malloc(sizeof(HEADER));
   DATA *data = (DATA*)malloc(sizeof(DATA));
   if (data == NULL || head == NULL) 
   {
      printf("Error Allocating \n");
      return ;
   }
   FILE *fp = fopen(text, "w");
   if (fp == NULL)
   {
    printf("Error opening file!\n");
    exit(1);
   }
   int length=0;
   length=atoi(size);
   read(head,data,name);
   int i,x;
   int *permutation;
   permutation =createPermutationFunction(head->subchunk2size,KEY);
   char buff = '\0' ;
   int count=0;
   for(i=0;i<(1+length)*8;i++)
      { 
      x=permutation[i];
      buff=buff<<1;
      if(data -> table[x]&0x1)
        {
        buff|=0x1;
        }
        else
        {
        buff&=~(0x1);
        }
        if(++count==8){
        count=0;
        fprintf(fp,"%c",buff);
        buff = '\0';
        }

       }
    fclose(fp);
    free(head);
    free(data->table);
    free(data);
    free(permutation);

}




