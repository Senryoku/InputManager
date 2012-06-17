#include "IniFile.hpp"

//#include <iostream>

IniFile::IniFile()
{
}

IniFile::IniFile(std::string Path)
{
	load(Path);
}

IniFile::~IniFile()
{
	free();
}

bool IniFile::load()
{
	return load(myPath);
}

bool IniFile::load(std::string Path)
{
	std::ifstream File(Path.c_str());
	if(File)
	{
		free();
		Section *CurrentSection;
		std::string line, key, value;
		while(std::getline(File, line))
		{
			if(line[0] == '[')
			{
				CurrentSection = new Section;
				mySections.insert(std::make_pair(line.substr(1, line.find_first_of("]") - 1), CurrentSection));
			} else if(line != "" && line != "\n") {
				key = line.substr(line.find_first_not_of(" "));
				key = line.substr(0, line.find_first_of(" ="));
				if(line.find_first_of("=") + 1>= line.length())
				{
					value = "";
				} else  {
					value = line.substr(line.find_first_of("=") + 1);
					if(value.find_first_not_of(" ") > value.length())
						value = "";
					else
						value = value.substr(value.find_first_not_of(" "));
				}
				//std::cout << key << " = " << value << std::endl;
				CurrentSection->insert(std::make_pair(key, value));
			}
		}
		File.close();
		myPath = Path;
		return true;
	} else { return false; }
}

bool IniFile::save()
{
	return save(myPath);
}

bool IniFile::save(std::string Path)
{
	std::ofstream File(Path.c_str());
	if(File)
	{
		for(std::map<std::string, Section*>::iterator it = mySections.begin();
			it != mySections.end(); it++)
		{
			File << "[" << it->first << "]" << std::endl;
			for(Section::iterator it2 = it->second->begin();
				it2 != it->second->end(); it2++)
				File << it2->first << " = " << it2->second << std::endl;
			File << std::endl;
		}
		File.close();
		return true;
	} else { return false; }
}

void IniFile::free()
{
	for(std::map<std::string, Section*>::iterator it = mySections.begin();
		it != mySections.end(); it++)
		delete it->second;
	mySections.clear();
}

void IniFile::addSection(std::string Name)
{
	if(!isSection(Name))
	{
		mySections.insert(std::make_pair(Name, new Section));
	}
}

void IniFile::addValue(std::string Name, std::string Key, std::string Value)
{
	if(!isSection(Name))
	{
		mySections.insert(std::make_pair(Name, new Section));
	}
	Section *S = mySections[Name];
	if(!isKey(Name, Key))
	{
		S->insert(std::make_pair(Key, Value));
	} else {
		(*S)[Key] = Value;
	}
}

IniFile::Section* IniFile::getSection(std::string Name)
{
	return mySections[Name];
}

std::string IniFile::getValue(std::string Name, std::string Key)
{
	return (*mySections[Name])[Key];
}

bool IniFile::isKey(std::string Name, std::string Key)
{
	return mySections.count(Name) && mySections[Name]->count(Key);
}
