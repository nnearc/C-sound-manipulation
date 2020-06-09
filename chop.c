/**
*@author Michalis Kaili
*@filename chop.c
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

void chop(char *name, char *val1, char *val2)
{   
   HEADER *head = (HEADER*)malloc(sizeof(HEADER));
   DATA *data = (DATA*)malloc(sizeof(DATA));
   if (data == NULL || head == NULL) 
   {
      printf("Error Allocating \n");
      return ;
   }

   if(!read(head, data, name))
   {
      free(head);
      free(data->table);
      free(data);
      return;
   }
   char new_name[8];
   int sec1, sec2, flag = 0;
   sec1 = atoi(val1);
   sec2 = atoi(val2);
   int duration = (head -> subchunk2size) / (head -> byteRate);
   if( (sec1 < 0) || (sec2 > duration) || (sec1 > sec2) )
      {
         printf("FAlSE time interval\n");
         return;
      }
   byte *array = (byte*)malloc(sizeof(byte)*(head->byteRate * (sec2-sec1)));

  for(int i = 0; i < head -> subchunk2size; i++)
  {
     if( (i >= sec1 * head->byteRate ) )
     {
        flag = 1;
        for(int j = 0; j < (head->byteRate * (sec2-sec1)); j++)
        { 
           array[j] = data -> table[i + j];
        }
     } 
     if (flag == 1)
        break;
  }

   head -> subchunk2size = head->byteRate * (sec2-sec1);
   head -> chunkSize = head -> subchunk2size + 36;
   FILE *fp1;
   strcpy(new_name, "chopped-");
   strcat(new_name,name);
   fp1 = fopen(new_name, "wb");
   fwrite(head, sizeof(HEADER), 1, fp1); 
   fwrite(array, sizeof(byte),  head -> subchunk2size, fp1);
   fclose(fp1);
   free(array);
   free(head);
   free(data->table);
   free(data);
}



