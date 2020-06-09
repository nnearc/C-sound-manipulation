/**
*@author Michalis Kaili 
*@filename mono.c
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

void mono( char *name)
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

   if(head->numChannels == 1)
   {
      free(head);
      free(data->table);
      free(data);
      printf("file is already mono\n");
      return;
   }

   char new_name[5];
   int count = 0;
   byte *left= (byte*)malloc(sizeof(byte)*((head->subchunk2size/2)));// right[head->subchunk2size/2]; for the right channel
   strcpy(new_name, "mono-");
   for(int i = 0; i < head->subchunk2size; i = i + (head->blockAlign))
   { 
      for(int j = 0; j < head->blockAlign; j++)
      { 
         if(j<head->blockAlign)
         {
            left[count + j] = data -> table[i+j];
         }
         /*else
         {
            array2[count + j] = data -> table[i+j];
         }*/
      }
      count= count + (head->blockAlign/2);
   } 
   head -> numChannels = 1 ;
   head -> byteRate = (head->sampleRate * head->bitsPerSample)/8;
   head -> blockAlign = (head->bitsPerSample)/8;
   head -> subchunk2size =  head -> subchunk2size/2;
   head -> chunkSize = head -> subchunk2size/2 + 36;

   FILE *fp1;
   strcat(new_name,name);
   fp1 = fopen(new_name, "wb");
   fwrite(head, sizeof(HEADER), 1, fp1); 
   fwrite(left, sizeof(byte),  head -> subchunk2size, fp1);
   fclose(fp1);
   free(left);
   free(head);
   free(data->table);
   free(data);
}




