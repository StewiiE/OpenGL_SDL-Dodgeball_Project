#include <stdio.h> 
#include <stdlib.h> 
#include "Commons.h" 
#include "3dsLoader.h" 
#include <sys\stat.h>

//---------------------------------------------------------------------------------------------------

long filelength(int f)
{
	struct stat buf;
	fstat(f, &buf);
	return(buf.st_size);
}

//---------------------------------------------------------------------------------------------------

char Load3DS(obj_type_ptr p_object, char *p_filename) 
{
	int i; //Index variable 
	FILE *inFile; //File pointer
	unsigned short chunkId, s_temp; //Chunk identifier unsigned
	int chunkLength; //Chunk length 
	unsigned char name; //Char variable
	unsigned short size; //Number of elements in each chunk

	unsigned short faceFlag; //Flag that stores some face information

	if ((inFile = fopen(p_filename, "rb")) == NULL)
		return 0; //Open the file

	while (ftell(inFile) < filelength(fileno(inFile))) //Loop to scan the whole file
	{ fread(&chunkId, 2, 1, inFile); //Read the chunk header
	fread(&chunkLength, 4, 1, inFile); //Read the length of the chunk
									   //getchar(); 
									   //Insert this command for debug (to wait for keypress for each chuck reading)

	switch (chunkId)
	{ 

	case 0x4d4d:
		break;
	
	case 0x3d3d:
		break;
	
	case 0x4000:
		i = 0;
		do
		{
			fread(&name, 1, 1, inFile);
			p_object->name[i] = name;
			i++;
		} while (name != '\0' && i<20);
		break;

	case 0x4100:
		break;

	case 0x4110:
		fread(&size, sizeof(unsigned short), 1, inFile);
		p_object->vertices_qty = size;
		for (i = 0; i<size; i++)
		{
			fread(&p_object->vertex[i].x, sizeof(float), 1, inFile);
			fread(&p_object->vertex[i].y, sizeof(float), 1, inFile);
			fread(&p_object->vertex[i].z, sizeof(float), 1, inFile);
		}
		break;

	case 0x4120:
		fread(&size, sizeof(unsigned short), 1, inFile);
		p_object->triangles_qty = size;
		for (i = 0; i<size; i++)
		{
			fread(&s_temp, sizeof(unsigned short), 1, inFile);
			p_object->triangle[i].a = s_temp;
			fread(&s_temp, sizeof(unsigned short), 1, inFile);
			p_object->triangle[i].b = s_temp;
			fread(&s_temp, sizeof(unsigned short), 1, inFile);
			p_object->triangle[i].c = s_temp;
			fread(&faceFlag, sizeof(unsigned short), 1, inFile);
		}
		break;

	case 0x4140:
		fread(&size, sizeof(unsigned short), 1, inFile);
		for (i = 0; i < size; i++)
		{
			fread(&p_object->texcoord[i].u, sizeof(float), 1, inFile);
			fread(&p_object->texcoord[i].v, sizeof(float), 1, inFile);
		}
		break;

		default:
			fseek(inFile, chunkLength - 6, SEEK_CUR);
		}
	}

	fclose(inFile); //Close the file. 
	return(1);
}
//--------------------------------------------------------------------------------------------------





