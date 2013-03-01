/*
 * imca.cpp
 * 
 * Part of dft2lnt library - a library containing read/write operations for DFT
 * files in Galileo format and translating DFT specifications into Lotos NT.
 * 
 * @author Dennis Guck
 */

#include "imca.h"

#include "FileSystem.h"
#include "FileWriter.h"
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

IMCA::T_Chance IMCA::T_Chance_Default;

int IMCA::FileHandler::readOutputFile(const File& file) {
	if(!FileSystem::exists(file)) {
		return 1;
	}

	FILE* fp;
	long len;
	char* buffer;

	fp = fopen(file.getFileRealPath().c_str(),"rb");
	fseek(fp,0,SEEK_END);
	len = ftell(fp)+1;
	fseek(fp,0,SEEK_SET);
	buffer = (char *)malloc(len);
	fread(buffer,len,1,fp); //read into buffer
	fclose(fp);

	const char* resultString = NULL;
	{
		const char* c = buffer;
		while(*c) {
			//printf("%c",*c);
			if(!strncmp("probability",c,11)) {
				c += 13;
				const char* ce = c;
				while(*ce && *ce!='\n') ce++;
				resultString = c;
				//printf("\nfound: %s\n",c);
				//printf("should be: '%s'\n",resultString.c_str());
				break;
			}
			c++;
		}
	}

	if(!resultString) {
		return 1;
	}

	{
		results.clear();
		const char* c = resultString;
		while(*c && *c!='\n') {
			//float res = atof(c);
			double res = 0;
			sscanf(c,"%lf",&res);
			results.push_back(std::pair<std::string,IMCA::T_Chance>("?",res));
			//printf("found result: %f\n",res);

			const char* ce = c;
			while(*ce && *ce!=' ') ce++;
			if(!*ce) break;
			c = ce+1;
		}

		i_isCalculated = true;
	}


	free(buffer);
	return 0;
}

IMCA::T_Chance IMCA::FileHandler::getResult() {
	if(results.size()<1) {
		return T_Chance_Default;
	}
	return results[0].second;
}

std::vector<std::pair<std::string,IMCA::T_Chance>> IMCA::FileHandler::getResults() {
	return results;
}