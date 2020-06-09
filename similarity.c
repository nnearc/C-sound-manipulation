
/**
*@author Michalis Kaili
*@filename similarity.c
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

void similarity(char *name1, char *name2)
{
   int num1, num2;
   float sum = 0, sum2 = 0;

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

   if (head1->subchunk2size > head2->subchunk2size) 
   {
      num1 = (int)head1->subchunk2size; // this is our bigger number
      num2 = (int)head2->subchunk2size; // this is our smaller number
   }

   else
   {
      num2 = (int)head1->subchunk2size; // this is our bigger number
      num1 = (int)head2->subchunk2size; // this is our smaller number
   }

   dword *table1 =(dword*)malloc(sizeof(dword) * num1+1);
   dword *table2 =(dword*)malloc(sizeof(dword) * num1+1);
   dword *temp = NULL;
  
   for(int i = 0; i < num1; i++)
      table1[i] = 0;
      table2[0] = 0;

   for(int i = 1; i <= num2; i++)
   {
      for(int j = 1; j <= num1; j++)
      {
         if(data1->table[j-1] == data2->table[i-1])
         {
            table2[j] = table1[j-1] + 1;
         }
         else if(table1[j] <= table2[j-1])
         {
            table2[j] = table2[j-1];
         }
         else
         {
            table2[j] = table1[j];
         }
      }
      temp = table1;
      table1 = table2;
      table2 = temp;
   }

   if( (head1->subchunk2size < head2->subchunk2size) )
   {
         sum2 = 1 - ((float)table1[num1]/ (float)head1->subchunk2size);

      for(int i = 0; i < head1->subchunk2size; i++) 
         sum = sum + pow(abs( data1->table[i] - data2->table[i] ), 2);

   }
   else
   {
         sum2 = 1 - ((float)table1[num1]/ (float)head2->subchunk2size);

      for(int i = 0; i < head2->subchunk2size; i++) 
         sum = sum + pow(abs( data1->table[i] - data2->table[i] ), 2);

   }


   printf("Euclidean distance: %.3f \n", sqrt(sum));
   printf("LCSS distance: %.3f \n", sum2);
   free(head1);
   free(data1->table);
   free(data1);
   free(head2);
   free(data2->table);
   free(data2);
   free(table1);
   free(table2);
}



