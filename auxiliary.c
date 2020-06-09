/**
*@author Michalis Kaili , Nearchos Nearchou
*@filename auxiliary.c
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

int read(HEADER *head, DATA *data, char *name)
{
   FILE *fp;
   fp = fopen(name, "rb");

   if (fp == NULL)
   {
      printf("Error opening file: %s\n", name);
      return 0;
   }
   
   if(check(name)==0)
   {
      return 0;
   }


   fread(head, sizeof(HEADER), 1, fp);
   data -> table = (byte*)malloc(head -> subchunk2size);
   if (data -> table == NULL) 
   {
      printf("Error Allocating \n");
      return 0  ;
   }
   fread(data -> table, sizeof(byte), head -> subchunk2size, fp);
   fclose(fp);
return 1;
}



void print(char *name)
{
   FILE *fp;
   fp = fopen(name, "rb");

   HEADER *head = (HEADER*)malloc(sizeof(HEADER));
   if (head == NULL) 
   {
      printf("Error Allocating \n");
      return ;
   }
   fread(head, sizeof(HEADER), 1, fp);


   printf("\n");

   printf("RIFF_CHUNK_HEADER\n=================\n");
   printf("chunkID: ");
   for(int i = 0; i < sizeof(head -> chunkID); i++)
      printf("%c", head->chunkID[i]);
   printf("\n");
   printf("chunkSize: %d\n", head -> chunkSize);
   printf("format: ");
   for(int i = 0; i < sizeof(head -> chunkID); i++)
      printf("%c", head->format[i]);
   printf("\n");


   printf("\n");
   printf("FMT_SUBCHUNK_HEADER\n===================\n");
   printf("subChunk1ID: ");
   for(int i = 0; i < sizeof(head -> subchunk1ID); i++)
      printf("%c", head->subchunk1ID[i]);
   printf("\n");
   printf("subChunkSize: %d\n", head -> subchunk1Size);
   printf("audioFormat: %d\n", head -> audioFormat); 
   printf("numChannels: %d\n", head -> numChannels);
   printf("sampleRate: %d\n", head -> sampleRate);
   printf("byteRate: %d\n", head -> byteRate);
   printf("blockAlign: %d\n", head -> blockAlign);
   printf("bitsPerSample: %d\n", head -> bitsPerSample);


   printf("\n");
   printf("DATA_SUBCHUNK_HEADER\n====================\n");
   printf("subChunk2ID: ");
   for(int i = 0; i < sizeof(head -> subchunk2ID); i++)
      printf("%c", head->subchunk2ID[i]);
   printf("\n");
   printf("subChunk2Size: %d\n", head -> subchunk2size);

   printf("\n**************************************************\n"); 
  
   fclose(fp);
   free(head);

}


int same(HEADER *head1, HEADER *head2)
{
   if(head1->numChannels != head2->numChannels)
   {
      printf("The 2 files have different numChannels and cannot proceed.\n Please choose other files\n");
      return 0;
   }
   if(head1->blockAlign != head2->blockAlign)
   {
      printf("The 2 files diffent blockAligns and cannot proceed.\n Please choose other files\n");
      return 0;
   }
   if(head1->bitsPerSample != head2->bitsPerSample)
   {
      printf("The 2 files have diffent bitsPerSample and cannot proceed.\n Please choose other files\n");
      return 0;
   }
return 1;
}

int check(char *name)
{
   FILE *fp;
   fp = fopen(name, "rb");

   HEADER *head = (HEADER*)malloc(sizeof(HEADER));
   if (head == NULL) 
   {
      printf("Error Allocating \n");
      return 0;
   }
   fread(head, sizeof(HEADER), 1, fp);

   if(head->chunkID[0]!='R'|| head->chunkID[1]!='I'|| head->chunkID[2]!='F'|| head->chunkID[3]!='F')
   {
      printf("The file isn't appropriate1 \n");
      return 0;
   }
   if(head->format[0]!='W' || head->format[1]!='A' || head->format[2]!='V' || head->format[3]!='E')
   {
      printf("The file isn't appropriate2 \n");
      return 0;
   }
   if(head->subchunk1ID[0]!='f' || head->subchunk1ID[1]!='m' || head->subchunk1ID[2]!='t')
   {
      printf("The file isn't appropriate3 \n");
      return 0;
   }
   if(head -> subchunk2ID[0]!='d' ||head -> subchunk2ID[1]!='a' || head -> subchunk2ID[2]!='t' || head ->       subchunk2ID[3]!='a')
   {
      printf("The file isn't appropriate4 \n");
      return 0;
   }
   if(head -> audioFormat!=1)
   {
      printf("The file isn't appropriate5 \n");
      return 0;
   }
    
    fclose(fp);
    free(head);
    return 1;

}

















