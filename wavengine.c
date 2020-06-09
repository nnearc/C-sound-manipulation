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

#include "header.h"


int main(int argc, char* argv[])
{

  int choice = 0;

   if(strcmp(argv[1],"-list") == 0 ) choice = 0;
   else if(strcmp(argv[1],"-mono") == 0 ) choice = 1;
   else if(strcmp(argv[1],"-reverse") == 0 ) choice = 2;
   else if(strcmp(argv[1],"-chop") == 0 ) choice = 3;
   else if(strcmp(argv[1],"-similarity") == 0 ) choice = 4;
   else if(strcmp(argv[1],"-encodeText") == 0 ) choice = 5;
   else if(strcmp(argv[1],"-decodeText") == 0 ) choice = 6;
   else if(strcmp(argv[1],"-mix")==0)choice = 7;
   else if(strcmp(argv[1],"-slow")==0)choice = 8;
   else if(strcmp(argv[1],"-fast")==0)choice = 9;
   else choice = 10;

   int w = 1;
   int arguments = argc - 2;
   for(int i = 0; i < arguments; i++)
   {
      w++;

      switch(choice) 
      {
		case 0:
			print(argv[w]);
			break;
		case 1:
			//if (check(argv[w]))
			   mono(argv[w]);
			break;
		case 2:
			reverse(argv[w]);
			break;
		case 3:
        		if(argv[w+1] == NULL || argv[w+2] == NULL)
         		{
           			printf("indicate at what seconds to chop \n");
            			return 1;
         		}
			chop( argv[w], argv[w+1], argv[w+2]);
         		w += 2;
			arguments /= 3;
			break;
		case 4:
		        if (argc <= 3)
         		{
            			printf("Not enough arguments\n");
            			return 1;
         		}
         		if(argv[w+1] != NULL) 
            			similarity(argv[2], argv[w+1]);
			break;	
		case 5: if (argc <= 3)
         		{
            			printf("Not enough arguments\n");
            			return 1;
         		}
         		if(argv[w+1] != NULL) 
            			encode(argv[w], argv[w+1]);
			break;	
		case 6: decode(argv[2],argv[3],argv[4]);
                        w += 2;
			arguments /= 3;
                        break;
		case 7:
                       if(argc<=3)
	               {
	                       printf("Not enough arguments\n");
                               return 1;
	               }
	               if(argv[w+1]!=NULL)
	                       mix(argv[w],argv[w+1]);
			break;
                case 8:
			slow(argv[w]);
			break;
                case 9:
			fast(argv[w]);
			break;
		default: 
        		printf("\n <one line to give the program's name and a brief idea of what it does.>Copyright (C)   <2018> <Michalis Kailis, Nearchos Nearchou>\n ");
        		printf("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License\n as published by");
         		printf("the Free Software Foundation, either version 3 of the License,\n or at your option) any later version.");
         		printf("This program is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY without even the implied warranty of");
       		 	printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n See the GNU General Public License for more details.");
        		printf("Υou should have received a copy of the \n GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.\n");
        		printf("\n The options are:\n ");
			printf("-> -list (name of track(s))\n ");
			printf("-> -mono (name of track(s))\n ");
			printf("-> -mix (name of track) (name of track)\n ");
			printf("-> -chop (name of track) (starting second) (ending second)\n ");
			printf("-> -reverse (name of track(s))\n ");
			printf("-> -similarity (name of track(s))\n ");
			printf("-> -encodeText (name of track) (name of input file)\n ");
			printf("-> -decodeText (name of track) (size of the text file) (name of output file)\n ");
			printf("-> -slow (name of track(s))\n ");
			printf("-> -fast (name of track(s))\n\n ");
       			return 1;
      	} 
}
return 0;
} 




