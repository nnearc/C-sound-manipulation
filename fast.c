/**
*@author Michalis Kaili
*@filename fast.c
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

void fast( char *name)
{
   char new_name[5];
   strcpy(new_name, "fast-");
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

   head ->sampleRate = head -> sampleRate * 1.4;
   head -> byteRate = head -> bitsPerSample  * head -> sampleRate * head -> numChannels/ 8 ;

   FILE *fp1;
   strcat(new_name,name);
   fp1 = fopen(new_name, "wb");
   fwrite(head, sizeof(HEADER), 1, fp1);
   fwrite(data -> table, sizeof(byte),  head -> subchunk2size, fp1);
   fclose(fp1);

   free(head);
   free(data->table);
   free(data);
}
