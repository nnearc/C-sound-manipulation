/**
*@author Nearchos Nearchou 
*@filename mix.h
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

void mix(char *name1,char *name2)
{         
   int i,j;
   HEADER *head1 = (HEADER*)malloc(sizeof(HEADER));
   DATA *data1 = (DATA*)malloc(sizeof(DATA));
   if (data1 == NULL || head1 == NULL) 
   {
      printf("Error Allocating \n");
      return ;
   }

   if(!read(head1, data1, name1))
   {
      free(head1);
      free(data1->table);
      free(data1);
      return;
   }

   HEADER *head2 = (HEADER*)malloc(sizeof(HEADER));
   DATA *data2 = (DATA*)malloc(sizeof(DATA));
   if (data2 == NULL || head2 == NULL) 
   {
      printf("Error Allocating \n");
      return ;
   }

   if(!read(head2, data2, name2))
   {
      free(head2);
      free(data2->table);
      free(data2);
      return;
   }
   if(!same(head1,head2))
      return;
   
   char new_name[4];
   int count = 0;
   
   strcpy(new_name, "mix-");
  
   int flag=0;
   if(head1->subchunk2size>head2->subchunk2size)
   {
   flag=1;
   }
   else
   {
   flag=2;
   }

   if(flag==1){
   count=0;
   for(i = 0; i <head2->subchunk2size; i = i + (head2->blockAlign))
   { 
      for(j = 0; j < head2->blockAlign; j++)
      { 
         if(j<head2->blockAlign/2)
         {
            data2->table[i + j] = data2 -> table[i+j];
         }
         else
         {
            data2->table[i + j] = data1 -> table[i+j];
         }
      }

      count= count + (head2->blockAlign);
   } 
}
   if(flag==2){
   count=0;
   for(i = 0; i <head1->subchunk2size; i = i + (head1->blockAlign))
   { 
      for(j = 0; j < head1->blockAlign; j++)
      { 
         if(j<head1->blockAlign/2)
         {
            data1->table[i + j] = data2 -> table[i+j];
         }
         else
         {
            data1->table[i + j] = data1 -> table[i+j];
         }
      }
      count= count + (head1->blockAlign);
   } 
   }
   FILE *fp1;
   strcat(new_name,name1);
   strcat(new_name,name2);
   fp1 = fopen(new_name, "wb");;
   if (flag==1){
   fwrite(head2, sizeof(HEADER), 1, fp1);
   fwrite(data2->table, sizeof(byte),  head2 -> subchunk2size, fp1); 
   fclose(fp1);
   }
   else{
   fwrite(head1, sizeof(HEADER), 1, fp1);
   fwrite(data1->table, sizeof(byte),  head1 -> subchunk2size, fp1);
   fclose(fp1);
   }
   free(head1);
   free(data1->table);
   free(data1);
   free(head2);
   free(data2->table);
   free(data2);
 
}

