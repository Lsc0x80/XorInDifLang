#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

//Base64 encrypt from here https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
typedef unsigned char BYTE;
static const std::string base64_chars =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

static inline bool is_base64(BYTE c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

string base64_encode(BYTE const *buf, unsigned int bufLen)
{
	string ret;
	int i = 0;
	int j = 0;
	BYTE char_array_3[3];
	BYTE char_array_4[4];

	while (bufLen--)
	{
		char_array_3[i++] = *(buf++);
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

vector<BYTE> base64_decode(string const &encoded_string)
{
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	BYTE char_array_4[4], char_array_3[3];
	vector<BYTE> ret;
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

// I rewrote the function, the original view is here https://www.tutorialspoint.com/xor-cipher-in-cplusplus#
template <typename T>
vector<BYTE> XORChiper(T originalString, string xorKey){
	int j = 0;
	vector<BYTE> xored;
	int len = originalString.size();
	for (int i = 0; i < len; i++)
	{
		xored.push_back(originalString[i] ^ xorKey[j]);
		if (j == xorKey.size() - 1) j = 0;
		else j++;
	}
	return xored;
}

string bytes2string(vector<BYTE> input){
	string ret;
	for (int i = 0; i < input.size(); i++)
		ret.push_back(input[i]);
	return ret;
}

int main()
{
	string istr, key, chs, dummy;
	while(1){
		cout << "What yo want?  [E]ncrypt OR [D]ecode \n >>> ";
		getline(cin, chs);
		if (chs == "e"){
			cout << " enter data \n >>> ";
			getline(cin, istr);
			cout << " enter key \n >>> ";
			getline(cin, key);
			vector<BYTE> xored = XORChiper(istr, key);
			string encodedData = base64_encode(&xored[0], xored.size());
			cout << encodedData << endl;
			cout << "press Enter to continue"; getline(cin, dummy);
			system("clear");
		} else if (chs == "d"){
			cout << " enter data \n >>> ";
			getline(cin, istr);
			cout << " enter key \n >>> ";
			getline(cin, key);
			vector<BYTE> decoded = base64_decode(istr);
			vector<BYTE> xored = XORChiper(decoded, key);
			cout << bytes2string(xored)<<endl;
			cout << "press Enter to continue"; getline(cin, dummy);
			system("clear");
		} else return 0;
	}
}
