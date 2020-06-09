/**
*@author Michalis Kaili 
*@author Nearchos Nearchou 
*@filename header.h
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

#ifndef __HEADER_H__
#define __HEADER_H__
#define PRIVATE static
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct header
{
   byte chunkID [4];
   dword chunkSize;
   byte format[4];
   byte subchunk1ID[4];
   dword subchunk1Size;
   word audioFormat;
   word numChannels;
   dword sampleRate;
   dword byteRate;
   word blockAlign;
   word bitsPerSample;
   byte subchunk2ID[4];
   dword subchunk2size;
}HEADER;

typedef struct data
{
   byte *table;
}DATA;

/**
*@brief This function is used to read the given wav file
*       and creates the structs used in the rest of the functions
*
*@param *name the name of the track we want to read
*@param *head the pointer of the struct that will contain the header of the wav file
*@param *data the pointer of the struct that will contain the data of the wav file
*@return int return 0 if the function fails to read the file and 1 if it succeeds 
*/
int read(HEADER *head, DATA *data, char *name);
/**
*@brief This function is used to print the header of the wav file(s)
*       that where given by the user.
* 
* The information printed by this function contains all the data in 
* the header of the wav file. The data is printed in a clear and easy to read
* format so the user may understd it better.
*
*@param *name the name of the track we want to read
*returns void
*/
void print(char *name);
/**
*@brief This function checks for the fuctions that takes 2 wav files as arguments
*        and if the files are appropriate (dont have huge differences) then
*        proceed to the fuction.
*
*
*@param *head1 the pointer of the struct that will contain the header of the 
* first wav file
*@param *head2 the pointer of the struct that will contain the header of the
* second wav file
*@return int return 0 if the function fails to read the file and 1 if it succeeds 
*/
int same(HEADER *head1, HEADER *head2);
/**
*@brief This function checks if the wav file is appropriate for the function 
* to proceed
*
*
*@param *name the name of the track we want to read
*@return int return 0 if the function fails to read the file and 1 if it succeeds 
*/
int check(char *name);



/**
*@brief This function choppes a track in between 
*       the interval given by the user
*
* This function takes the name of a wav file and a time interval(in seconds)
* given by the user. It then chops the original track in between the 
* two values and creates a new wav file file with the chopped track
*
*@param *name the name of the track to be cut
*@param *val the second to start cutting
*@param the second to stop cutting
*@return void
*/
void chop(char *name, char *val1, char *val2);



/**
*@brief This function takes a wav file and increases the speed in which is played.
*       It does this by increasing its sampleRate, and changing its byteRate.
*
* This function takes the name of a wav file given by the user.
* It creates a new wav file wich is played at a faster speed than the original track.
*
*@param *name the name pf the track to be cut
*@return void
*/
void fast(char *name);

/**
*@brief This function turns a wav file from stereo to mono
*
* This function takes the name of a wav file given by the user.
* It then turns the original track from streo to mono.
* It creates a new wav file using only the left channel from the original track.
*
*@param *name the name pf the track to be cut
*@return void
*/
void mono(char *name);

/**
*@brief This function takes a wav file and reverses it.
*
* This function takes the name of a wav file given by the user.
* It then creates a new wav file which contains the
* revesed version of the original track.
*
*@param *name the name pf the track to be reversed
*@return void
*/
void reverse(char *name);

/**
*@brief This function takes two wav files and finds
*       the euclidian distance and the longest common sub string(lcss).
*
* This function takes the name of two wav files given by the user.
* It then finds the euclidian and lcss and prints it out for the user.
*
*@param *name the name the tracks to be compared
*@return void
*/
void similarity(char *name1, char *name2);


/**
*@brief This function takes a wav file and decreases the speed in which is played.
*       It does this by decreasing its sampleRate, and changing its byteRate.
*
* This function takes the name of a wav file given by the user.
* It creates a new wav file wich is played at a faster speed than the original track.
*
*@param *name the name pf the track to be cut
*@return void
*/
void slow(char *name);

/**
*@brief This function takes two wav files and creates a new wav file
*       that mix those 2 files
*
* This function takes the name of two wav files given by the user.
* Then takes the right channel of the first file and the left from the second
* and finally creates a new wav file in which it has a right channel from the first
* and left channel from the second.
*
*@param *name1 the name the track that im taking the the right channel
*@param *name2 the name the track that im taking the the left channel
*@return void
*/
void mix(char *name1,char *name2);

/**
*@brief This function takes a wav file and put inside it a txt file(encrypted)
*       
* First we make make the fuction getBit and we get all the bits of our text
* This function takes the wav file and creates permutations with a hidden Key and * we 
* swap elements randomly according to our key.Then in our wav file according to  
* our permutation array
* we go through our samples and change the least significant of our samples with  * the bits of our
* text file.(u[i]).Finally we create a new wav file with the changes.
*
*@param *name1 the name of the track
*@param *text the name my txt file(input file)
*@return void
*/
void encode (char *name,char *text);

/**
*@brief This function takes a wav file and we get the txt file that ewe encrypted inside it.
*       
* First we create again permutations with the hidden key in order to get the right * samples of the file
* Then go through the samples and we add the hidden bits inside the sample. Every * 8 bits is one 
* charachter.Finally we write those charachters into an output file
* 
*
*@param *name the name of the track
*@param *size the size of my input file from the encode fuction
*@param *text the name my txt file(outuput file)
*@return void
*/
void decode (char *name,char *size,char *text);
/**
*@brief This function creates an array(permutations) and this array is gonna be
* where inside the samples we are gonna put the u[i] (all the bits of our txt file)
*       
*
*@param unsigned int is the system key that we define
*@param int N our samples of the wav file
*@return int the array Pemrutations
*/
int* createPermutationFunction(int N, unsigned int systemkey);
#endif

















