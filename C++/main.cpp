#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

typedef unsigned char BYTE;
static const std::string base64_chars =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

static inline bool is_base64(BYTE c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_encode(string const buf)
{
	string ret;
	int i = 0;
	int j = 0;
	int k = 0;
	unsigned int bufLen = buf.size();
	BYTE char_array_3[3];
	BYTE char_array_4[4];

	while (bufLen--)
	{
		char_array_3[i++] = buf[k++];
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}

	return ret;
}

string base64_decode(string const &encoded_string)
{
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	BYTE char_array_4[4], char_array_3[3];
	string ret;
	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret.push_back(char_array_3[i]);
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
			ret.push_back(char_array_3[j]);
	}

	return ret;
}

string XORChiper(string originalString, string xorKey){
	int j = 0;
	string xored;
	for (const char& c : originalString)
	{
		xored.push_back(c ^ xorKey[j]);
		if (j == xorKey.size() - 1) j = 0;
		else j++;
	}

	return xored;
}

int main()
{
	string istr, key, chs, ciphered;
	while(1){
		cout << "What you want?  [E]ncrypt OR [D]ecode \n>>> ";
		getline(cin, chs);
		char choose = tolower(chs[0]);
		if (choose != 'e' && choose != 'd') exit(1);
		
		cout << "data: ";
		getline(cin, istr);
		cout << "key: ";
		getline(cin, key);
        
		ciphered = (choose != 'd') ? base64_encode(XORChiper(istr, key)) : XORChiper(base64_decode(istr), key);
        
		cout << ciphered << endl;
		cout << "press Enter to continue"; cin.get();
		
	}
	return 0;
}
