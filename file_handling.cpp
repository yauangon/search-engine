#include "file_handling.h"
#include <string>
#include <vector>
#include <fstream>
#include <iosfwd>
#include <ctype.h>
#include "trie.h"

using namespace std;

bool File_Handling::isStopWord(string cmpstr, string* stopword)
{
	for (int i = 0; i < 174; i++)
	{
		if (cmpstr == stopword[i])
			return true;
	}
	return false;
}

void File_Handling::filterPunctation(string& str)
{
	for (int i = 0, len = str.size(); i < len; i++)
	{
		if (ispunct(str[i]))
		{
			str.erase(i--, 1);
			len = str.size();
		}
	}
}

void File_Handling::importfileExe(vector<pair<string, int>>& result, string& cmpstr, string* arr)
{
	stringstream ss;
	ss << cmpstr;
	cmpstr = "";

	while (!ss.eof())
	{
		ss >> cmpstr;

		cmpstr.erase(remove_if(cmpstr.begin(), cmpstr.end(), ispunct), cmpstr.end());

		if (!this->isStopWord(cmpstr, arr) && !cmpstr.empty())
		{
			if (result.size() == 0)
			{
				result.push_back(make_pair(cmpstr, 1));
			}
			else
			{
				bool existed = false;
				for (int i = 0; i < result.size(); i++)
				{
					if (result[i].first == cmpstr)
					{
						result[i].second += 1;
						existed = true;
					}
				}
				if (existed == false)
					result.push_back(make_pair(cmpstr, 1));
			}
		}

	}
}

vector<string> File_Handling::load_file_names(string index_file)
{
	return vector<string>();
}

vector <pair <string, int>> File_Handling::import_file(string filename)
{
	ifstream fin;
	vector<pair<string, int>> result;
	fin.open(filename);
	if (!fin.is_open())
		cout << "Open file error" << endl;
	else
	{
		// Create array of stopwords
		string* arr = new string[174]; // 174 stopwords
		ifstream LoadStopWord;
		LoadStopWord.open("stopword.txt");
		if (!LoadStopWord.is_open())
		{
			cout << "File is not existed." << endl;
		}
		else
		{
			int i = 0;
			while (!LoadStopWord.eof())
			{
				LoadStopWord >> arr[i];
				++i;
			}
		}
		LoadStopWord.close();

		string temp;
		while (!fin.eof())
		{
			getline(fin, temp, '\n');
			this->importfileExe(result, temp, arr);
		}
		fin.close();
	}
	return result;
}

Trie File_Handling::import_data()
{
	Trie head;
	//vector<string> AllFileName = this->load_file_names("___index.txt");
	//TEST WITH ONE FILE FIRST
	vector<string> AllFileName;
	string FILENAME = this->FILENAME;
	AllFileName.push_back(FILENAME);

	while (!AllFileName.empty())
	{
		// Load file index
		vector<pair<string, int>> wordsandfreq = import_file(AllFileName.back());

		// Build tree
		head.build(AllFileName.back(), wordsandfreq);

		AllFileName.pop_back();
	}
	return head;
}
// read from __index.txt file names and then start importing from files to a trie

File_Handling::File_Handling(string filename)
{
	this->FILENAME = filename;
}