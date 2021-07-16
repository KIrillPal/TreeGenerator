#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

std::vector<wchar_t> mainTree;
std::vector<int> treeRightPos;
std::map<wchar_t, std::string> mainMap;
bool fileMode = 0;

std::string openFileDialog()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;

	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select file with tree";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
		return filename;
	switch (CommDlgExtendedError())
	{
	case CDERR_DIALOGFAILURE: return "-CDERR_DIALOGFAILURE";
	case CDERR_FINDRESFAILURE: return"-CDERR_FINDRESFAILURE";
	case CDERR_INITIALIZATION: return "-CDERR_INITIALIZATION";
	case CDERR_LOADRESFAILURE: return "-CDERR_LOADRESFAILURE";
	case CDERR_LOADSTRFAILURE: return "-CDERR_LOADSTRFAILURE";
	case CDERR_LOCKRESFAILURE: return "-CDERR_LOCKRESFAILURE";
	case CDERR_MEMALLOCFAILURE: return "-CDERR_MEMALLOCFAILURE";
	case CDERR_MEMLOCKFAILURE: return "-CDERR_MEMLOCKFAILURE";
	case CDERR_NOHINSTANCE: return "-CDERR_NOHINSTANCE";
	case CDERR_NOHOOK: return "-CDERR_NOHOOK";
	case CDERR_NOTEMPLATE: return "-CDERR_NOTEMPLATE";
	case CDERR_STRUCTSIZE: return "-CDERR_STRUCTSIZE";
	case FNERR_BUFFERTOOSMALL: return "-FNERR_BUFFERTOOSMALL";
	case FNERR_INVALIDFILENAME: return "-FNERR_INVALIDFILENAME";
	case FNERR_SUBCLASSFAILURE: return "-FNERR_SUBCLASSFAILURE";
	default: return "-USER_CANCELLED.\n";
	}
}

std::string saveTreeDialog()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;

	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Save file with tree";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetSaveFileNameA(&ofn))
		return filename;
	switch (CommDlgExtendedError())
	{
	case CDERR_DIALOGFAILURE: return "-CDERR_DIALOGFAILURE";
	case CDERR_FINDRESFAILURE: return"-CDERR_FINDRESFAILURE";
	case CDERR_INITIALIZATION: return "-CDERR_INITIALIZATION";
	case CDERR_LOADRESFAILURE: return "-CDERR_LOADRESFAILURE";
	case CDERR_LOADSTRFAILURE: return "-CDERR_LOADSTRFAILURE";
	case CDERR_LOCKRESFAILURE: return "-CDERR_LOCKRESFAILURE";
	case CDERR_MEMALLOCFAILURE: return "-CDERR_MEMALLOCFAILURE";
	case CDERR_MEMLOCKFAILURE: return "-CDERR_MEMLOCKFAILURE";
	case CDERR_NOHINSTANCE: return "-CDERR_NOHINSTANCE";
	case CDERR_NOHOOK: return "-CDERR_NOHOOK";
	case CDERR_NOTEMPLATE: return "-CDERR_NOTEMPLATE";
	case CDERR_STRUCTSIZE: return "-CDERR_STRUCTSIZE";
	case FNERR_BUFFERTOOSMALL: return "-FNERR_BUFFERTOOSMALL";
	case FNERR_INVALIDFILENAME: return "-FNERR_INVALIDFILENAME";
	case FNERR_SUBCLASSFAILURE: return "-FNERR_SUBCLASSFAILURE";
	default: return "-USER_CANCELLED.\n";
	}
}

bool getkey(char ch = 'y')
{
	wchar_t c;
	std::wcin >> c;
	return c == ch;
}

int dfsMap(int v, std::string code, int& e)
{
	if (v >= mainTree.size())
	{
		e = 1;
		return mainTree.size();
	}
	if (mainTree[v] == 0)
	{
		int k = dfsMap(v + 1, code + '0', e);
		treeRightPos[v] = k;
		return dfsMap(k, code + '1', e);
	}
	else if (mainMap.find(mainTree[v]) != mainMap.end())
		e = 2;
	else
	{
		if (code == "") code += '0';
		mainMap[mainTree[v]] = code;
	}
	return v + 1;
}

std::string generateMapByTree()
{
	mainMap.clear();
	treeRightPos.resize(mainTree.size());
	int e = 0;
	if (dfsMap(0, "", e) < mainTree.size())
		return "-TOO_MUCH_SYMBOLS";
	else if (e == 1)
		return "-TOO_FEW_SYMBOLS";
	else if (e == 2)
		return "-SYMBOL_DOUBLE_INIT";
	else return "OK";
}

std::string getCode(wchar_t ch)
{
	if (mainMap.find(ch) == mainMap.end())
		return "-1";
	return mainMap[ch];
}

void showTree()
{
	std::cout << "CHARACTER - CODE:\n";
	for (auto p : mainMap)
	{
		if (p.first == 1072)
		{
			std::cout << "";
		}
		std::cout << std::setw(0);
		std::wstring ws = L"-";
		ws[0] = p.first;
		std::wcout << ws;
		std::cout << '(' << int(p.first) << ")";
		std::cout << std::setw(15 - p.second.size()) << '\'' << p.second << "\'\n";
	}
	std::cout << "Tree was successfully selected.\n";
}

void loadTree()
{
	std::string fn = "-";
	while (fn[0] == '-')
	{
		mainTree.clear();
		treeRightPos.clear();
		fn = openFileDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "No file was selected.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be upload. Reason: " << fn.substr(1) << ".\n";
		}
		std::cout << "File was successfully uploaded.\n";
		std::cout << "Reading: ";
		std::ifstream fin(fn);
		std::string inp;
		while (fin >> inp)
		{
			char* p;
			unsigned long converted = strtoul(inp.c_str(), &p, 10);
			if (*p || converted > (1 << 16)) {
				std::cout << "\nFailed to read the file. Unknown symbol: '";
				std::cout << inp << "'.\nFile couldn't be upload.";
				fn = "-INVALID_TREE_FORMAT";
				break;
			}
			mainTree.push_back(converted);
		}
		std::cout << "OK\n";
		fin.close();
		if (fn[0] != '-')
		{
			std::cout << "Building: ";
			fn = generateMapByTree();
			if (fn[0] == '-')
				std::cout << "\nFailed to get codes from the tree. Reason: " << fn.substr(1) << ".\n";
			else
			{
				std::cout << "OK\n";
				showTree();
				return;
			}
		}
		std::cout << " Press 'y' to load file again. Press any key to continue: ";
		if (!getkey()) return;
	}
}

void loadTable()
{
	std::string fn = "-";
	while (fn[0] == '-')
	{
		mainTree.clear();
		mainMap.clear();
		fn = openFileDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "No file was selected.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be upload. Reason: " << fn.substr(1) << ".\n";
		}
		std::cout << "File was successfully uploaded.\n";
		std::cout << "Reading: ";
		std::ifstream fin(fn);
		std::string inp;
		while (fin >> inp)
		{
			char* p;
			unsigned long converted = strtoul(inp.c_str(), &p, 10);
			if (*p || converted > (1 << 16)) {
				std::cout << "\nFailed to read the file. Unknown symbol: '";
				std::cout << inp << "'.\nFile couldn't be upload.";
				fn = "-INVALID_TABLE_FORMAT";
				break;
			}
			if (!(fin >> inp) || inp.find_first_not_of("01") < inp.size())
			{
				std::cout << "\nFailed to read the file. Symbol without code: ";
				std::cout << converted << ".\nFile couldn't be upload.";
				fn = "-INVALID_TABLE_FORMAT";
				break;
			}
			mainMap[converted] = inp;
		}
		fin.close();
		if (fn[0] != '-')
		{
			std::cout << "OK\n";
			showTree();
			return;
		}
		std::cout << " Press 'y' to load file again. Press any key to continue: ";
		if (!getkey()) return;
	}
}

std::string loadText()
{
	std::string fn = "-";
	while (fn[0] == '-')
	{
		fn = openFileDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "No file was selected.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be upload. Reason: " << fn.substr(1) << ".\n";
			continue;
		}
		std::cout << "File was successfully uploaded.\n";
		std::cout << "Reading: ";
		std::ifstream fin(fn);
		std::string inp;
		char c;
		while (fin.get(c))
			inp += c;
		fin.close();
		std::cout << "OK\nEntered text:\n";
		std::cout << inp << '\n';
		return inp;
	}
}

std::wstring loadWtext()
{
	std::string fn = "-";
	while (fn[0] == '-')
	{
		fn = openFileDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "No file was selected.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be upload. Reason: " << fn.substr(1) << ".\n";
			continue;
		}
		std::cout << "File was successfully uploaded.\n";
		std::cout << "Reading: ";
		std::wifstream fin(fn);
		std::wstring inp;
		wchar_t c;
		while (fin.get(c))
			inp += c;
		fin.close();
		std::cout << "OK\nEntered text:\n";
		std::wcout << inp << '\n';
		return inp;
	}
}

void saveTree()
{
	std::string fn = "-";
	if (mainTree.empty())
	{
		std::cout << "Sorry, tree is empty!\n";
		return;
	}
	while (fn[0] == '-')
	{
		fn = saveTreeDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "Saving was cancelled by user.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be saved. Reason: " << fn.substr(1) << ".\n";
		}
		else
		{
			std::ofstream fout(fn);
			for (int i = 0; i < mainTree.size(); ++i)
				fout << (i ? " " : "") << mainTree[i];
			fout.close();
			std::cout << "Tree was successfully saved at " << fn << ".\n";
			return;
		}
		std::cout << " Press 'y' to load file again. Press any key to continue: ";
		if (!getkey()) return;
	}
}

void saveTable()
{
	std::string fn = "-";
	while (fn[0] == '-')
	{
		fn = saveTreeDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "Saving was cancelled by user.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be saved. Reason: " << fn.substr(1) << ".\n";
		}
		else
		{
			std::ofstream fout(fn);
			for (auto p : mainMap)
				fout << int(p.first) << " " << p.second << "\n";
			fout.close();
			std::cout << "Table was successfully saved at " << fn << ".\n";
			return;
		}
		std::cout << " Press 'y' to load file again. Press any key to continue: ";
		if (!getkey()) return;
	}
}

void saveText(std::wstring & ws)
{
	std::string fn = "-";
	while (fn[0] == '-')
	{
		fn = saveTreeDialog();
		if (fn[0] == '-')
		{
			if (fn == "-USER_CANCELLED.\n")
				std::cout << "Saving was cancelled by user.";
			else if (fn == "-FNERR_INVALIDFILENAME\n")
				std::cout << "Invalid file name.";
			else std::cout << "Sorry, file couldn't be saved. Reason: " << fn.substr(1) << ".\n";
		}
		else
		{
			std::wofstream fout(fn);
			fout << ws;
			fout.close();
			std::cout << "Text was successfully saved at " << fn << ".\n";
			return;
		}
		std::cout << " Press 'y' to load file again. Press any key to continue: ";
		if (!getkey()) return;
	}
}

std::string encode(std::wstring & ws)
{
	std::string code;
	std::map<wchar_t, int> unk;
	for (wchar_t w : ws)
	{
		std::string c = getCode(w);
		if (c == "-1")
			unk[w]++;
		else code += c;
	}
	if (!unk.empty())
	{
		std::cout << "Error: Text has characters that tree doesn't contain: ";
		for (auto p : unk)
			std::wcout << "'" << p.first << "' ";
		std::cout << '\n';
		return "-NOT_IN_TREE";
	}
	return code;
}

void dfsCreate(int v, std::vector<std::vector<int> > & g, std::vector<wchar_t> & vs)
{
	mainTree.push_back(vs[v]);
	for (auto u : g[v])
		dfsCreate(u, g, vs);
}

std::string generate(std::wstring & ws)
{
	if (ws.empty()) return "-EMPTY_ALPHABET";
	mainTree.clear();
	treeRightPos.clear();
	std::map<wchar_t, int> abcs;
	for (auto w : ws)
		abcs[w]++;
	int m = 2 * abcs.size() - 1;
	std::vector<std::vector<int> > g(m);
	std::vector<wchar_t> vals(m);
	std::set<std::pair<int, int> > elems;
	int i = 0;
	for (auto p : abcs)
	{
		vals[i] = p.first;
		elems.insert({ p.second, i });
		++i;
	}
	while (elems.size() > 1)
	{
		auto a = *elems.begin();
		elems.erase(elems.begin());
		auto b = *elems.begin();
		elems.erase(elems.begin());
		g[i].push_back(a.second);
		g[i].push_back(b.second);
		elems.insert({ a.first + b.first, i++ });
	}
	dfsCreate(elems.begin()->second, g, vals);
	generateMapByTree();
	return "OK";
}

std::wstring decode(std::string & code, int& e)
{
	std::wstring text;
	int p = 0, i = 0;
	while (i < code.size())
	{
		if (mainTree.size() == 1 && i < code.size() && code[i] == '1')
		{
			e = 1;
			return L"";
		}
		while (!mainTree[p])
		{
			if (code[i] == '0')
				++p, ++i;
			else if (code[i] == '1')
				p = treeRightPos[p], ++i;
			else
			{
				e = 2;
				return L"";
			}
		}
		text += mainTree[p], p = 0;
	}
	if (p != 0) e = 1;
	return text;
}

int main()
{
	std::locale::global(std::locale());
	std::wcout.imbue(std::locale());
	std::wcin.imbue(std::locale());
	std::cout << "Hello, user. There are some instructions:\n";
	std::cout << "    Press 'g' to generate character tree form text.\n";
	std::cout << "    Press 'l' to load character tree form file.\n";
	std::cout << "    Press 't' to load character table form file.\n";
	std::cout << "    Press 'c' to get code from text.\n";
	std::cout << "    Press 'd' to get text from code.\n";
	std::cout << "    Press 's' to save current tree.\n";
	std::cout << "    Press 'f' to change file mode.\n";
	std::cout << "You need to get any tree. Press 'g' or 'l' to get tree.\n";
	char command;
	while (std::cin >> command)
	{
		if (command == 'l')
		{
			loadTree();
		}
		else if (command == 't')
		{
			loadTable();
		}
		else if (command == 'g')
		{
			std::cout << "Enter ONE LINE text. New tree will be builded on it.\n";
			std::wstring ws;
			std::getline(std::wcin, ws);
			std::getline(std::wcin, ws);
			std::string e = generate(ws);
			if (e[0] != '-')
			{
				std::cout << "Building: OK\n";
				showTree();
			}
			else std::cout << "Code hasn't been generated.\n";
		}
		else if (command == 'c')
		{
			if (mainMap.empty()) std::cout << "Table isn't selected!\n";
			else
			{
				std::cout << "Enter text. It will be encoded.\n";
				std::wstring ws = loadWtext();
				std::string code = encode(ws);
				if (code[0] != '-')
					std::cout << "The code is:\n" << code << '\n';
				else std::cout << "Code hasn't been generated.\n";
			}
		}
		else if (command == 'd')
		{
			if (mainTree.empty()) std::cout << "Tree isn't selected!\n";
			else
			{
				std::cout << "Enter code. It is only with '0' and '1' characters.\n";
				std::string s;
				if (fileMode)
					s = loadText();
				else std::cin >> s;
				int e = 0;
				std::wstring text = decode(s, e);
				if (e == 0)
				{
					if (fileMode)
					{
						saveText(text);
						std::wcout << "The text was successfully saved.\n" << text << '\n';
					}
					else std::wcout << "The text is:\n" << text << '\n';
				}
				else
				{
					std::cout << "Error! ";
					if (e == 1)
						std::cout << "Invalid code.\n";
					else if (e == 2)
						std::cout << "Characters '0' and '1' allowed only.\n";
					std::cout << "Text hasn't been generated.\n";
				}
			}
		}
		else if (command == 'f')
		{
			fileMode ^= 1;
			std::cout << "File mode has successfully changed.\n";
		}
		else if (command == 's')
			saveTree();
		else if (command == 'z')
			saveTable();
	}
}