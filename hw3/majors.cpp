#include "setstr.h"
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

/*
 * This file reads in a list of students and their majors,
 * then reads in a command file and outputse the majors listed
 * Syntax: ./majors majors.in majors.cmd majors.out
 * note: majors must be separated from names by a comma
 * Daniel Shebib
 */

//map holds <string(majorname), SET(student names)>
std::map<std::string, SetStr> map_;

//Reads in from majors.in to map_
void readin(char* namein);
//Adds a key and a string of vals to the map
void mapadd(std::string key, std::string vals);
//runs commands from majors.cmd and outputs to majors.out
void runcmd(char* cmdname, char* outname);
//outputs set to file outname
void output(std::ofstream& fout, SetStr& out, char* outname);
//converts a string to uppercase
std::string toUpperCase(std::string in);

int main(int argc, char* argv[])
{
    char* namein = argv[1];
    readin(namein);
    char* cmdname = argv[2];
    char* filenameout = argv[3];
    for(std::map<std::string, SetStr>::iterator it = map_.begin(); it != map_.end(); it++)
    {
        std::cout<<it->first << std::endl;
    }
    runcmd(cmdname, filenameout);

}

void readin(char* namein)
{

    std::ifstream fin(namein);
    if (!fin.good()) { //check if file exists
        std::cout << "Error: File not found";
        fin.close();
        exit(1);
    }
    std::string in;
    while(fin)
    {
        std::getline(fin, in);
        int loc = 0;
        loc = in.find(",");
        std::string name = in.substr(0, loc);
        //clean whitespace
        name = name.erase(name.find_last_not_of(" \t\f\v\n\r")+1);
        std::string majs = in.substr(loc+1);
        majs = toUpperCase(majs);
        mapadd(majs, name);
    }
    fin.close();
}

void mapadd(std::string keys, std::string val)
{
    std::stringstream ss(keys);
    std::string keyin;
    while(ss >> keyin)
    {
        std::map<std::string, SetStr>::iterator it = map_.find(keyin);
        if(it == map_.end()) //new key
        {
            SetStr set; //will hold all names
            set.insert(val);
            map_.insert(std::make_pair(keyin, set));
        }
        else
        {
            it->second.insert(val);
        }
    }
}

void runcmd(char* cmdname, char* outname)
{
    std::ifstream fin(cmdname);
    if (!fin.good()) { //check if file exists
        std::cout << "Error: File not found";
        fin.close();
        exit(1);
    }
    std::ofstream fout; //initialize file output
    fout.open(outname);
    if(!fout.is_open()) {//make sure output file opens
        std::cout << "Error: Could not create output file";
        fout.close();
        exit(1);
    }
    std::string in;
    while(fin)
    {
        std::getline(fin, in);
        std::stringstream ss(in);
        std::string maj;
        SetStr out;
        while(ss>>maj) //for each listed major, get set
            //for that major and intersect with existing set
        {
            maj = toUpperCase(maj);
            fout << maj << " ";

            if(map_.find(maj) == map_.end())
                break;
            std::map<std::string, SetStr>::iterator it = map_.find(maj);
            if(out.empty())
                out = it->second;
            SetStr tmp = out | it->second;
            out = tmp;
        }
        output(fout,out, outname);
        fout << std::endl << std::endl;
    }
    fin.close();
}

void output(std::ofstream& fout, SetStr& out, char* outname)
{
    
    const std::string * ptr;
    ptr = out.first();
    while(ptr != NULL) //iterate through set
    {
        fout << std::endl << *ptr;
        ptr = out.next();
    }
} 

std::string toUpperCase(std::string in)
{
    std::string out;
    for(unsigned int i = 0; i < in.length(); i++)
    {
        out += std::toupper(in[i]);
    }
    return out;
}
        
