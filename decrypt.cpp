#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<string.h>
#include<string>
#include<sstream>

using namespace std;
#pragma warning(disable : 4996)


char MAIN[95] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '.', '?', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
'{', '}', '[', ']', '|', ';', ':', '\"', '\'', ',', '<', '>', '/', '-', '`' ,'=', '\\' };

char cipher[256];
char clearText[256];
char clearText_Ciser[256];
char clearText_Frequency[256];
char clearText_Virginia[256];
char clearText_ShiftLeft[256];
char clearText_Transform[256];
char clearText_EvenOddChange[256];
int cipherBinary[256][7];
int clearTextBinary[256][7];
char temp;

typedef long INT32;
typedef unsigned short int INT16;
typedef unsigned char U_CHAR;

int Plaintext[100];//明文
long long Ciphertext[100];//密文
int nn, ee = 0, dd, SL = 0;

#define UCH(x)	((int) (x))
#define GET_2B(array,offset)  ((INT16) UCH(array[offset]) + \
			       (((INT16) UCH(array[offset+1])) << 8))
#define GET_4B(array,offset)  ((INT32) UCH(array[offset]) + \
			       (((INT32) UCH(array[offset+1])) << 8) + \
			       (((INT32) UCH(array[offset+2])) << 16) + \
			       (((INT32) UCH(array[offset+3])) << 24))
#define FREAD(file,buf,sizeofbuf)  \
  ((size_t) fread((void *) (buf), (size_t) 1, (size_t) (sizeofbuf), (file)))

void CiserDecrypt(char *cipher, int length)
{
	int key = 7;

	//明文第一個字元-----------------------01
	int c = 0;
	for (int y = 0; y<95; y++)
	{
		if (MAIN[y] == cipher[0])
			c = y;
	}

	for (int y = 0;; y++)
	{
		int v = c + (95 * y);
		if (v % 7 == 0)
		{
			clearText[0] = MAIN[(v / 7)];
			break;
		}
	}
	//-------------------------------------01

	//解密明文第2字元之後------------------02
	int Y = 1;
	for (int h = 1; h<length; h++)
	{
		//對應表格找到密文(Y)位子---------=
		int x1 = 0;
		for (int y = 0; y<95; y++)
		{
			if (MAIN[y] == cipher[Y])
			{
				x1 = y;
				//cout<<"x1 "<<x1<<endl;
				break;
			}
		}
		//---------------------------------=

		//對應表格找到密文(Y-1)位子--------=
		int x2 = 0;
		for (int y = 0; y<95; y++)
		{
			if (MAIN[y] == cipher[Y - 1])
			{
				x2 = y;
				//cout<<"x2 "<<x2<<endl;
				break;
			}
		}
		//---------------------------------=

		for (int y = 1;; y++)
		{
			int v = x1 + (95 * y);
			if (v%key == 0)
			{
				clearText[Y] = MAIN[((v / 7) + x2) % 95];
				break;
			}
		}

		Y++;
	}

	//----------------------------------------------------02
}

void unTransform(char *cipher, int length)
{
	for (int i = 0; i < length; i++)
	{
		clearText_Transform[i] = cipher[(length - 1) - i];
	}
}

void FrequencyDecrypt(char *cipher, int length, int key)
{
	key = key % 4;
	cout << key;
	for (int i = 0; i < length; i++)
	{
		switch (cipher[i])
		{
		case 'A':
			clearText_Frequency[i] = 'C';
			break;
		case 'a':
			clearText_Frequency[i] = 'c';
			break;
		case 'B':
			clearText_Frequency[i] = 'T';
			break;
		case 'b':
			clearText_Frequency[i] = 't';
			break;
		case 'C':
			clearText_Frequency[i] = 'L';
			break;
		case 'c':
			clearText_Frequency[i] = 'l';
			break;
		case 'D':
			clearText_Frequency[i] = 'J';
			break;
		case 'd':
			clearText_Frequency[i] = 'j';
			break;
		case 'E':
			clearText_Frequency[i] = 'A';
			break;
		case 'e':
			clearText_Frequency[i] = 'a';
			break;
		case 'F':
			clearText_Frequency[i] = 'P';
			break;
		case 'f':
			clearText_Frequency[i] = 'p';
			break;
		case 'G':
			clearText_Frequency[i] = 'Q';
			break;
		case 'g':
			clearText_Frequency[i] = 'q';
			break;
		case 'I':
			clearText_Frequency[i] = 'E';
			break;
		case 'i':
			clearText_Frequency[i] = 'e';
			break;
		case 'J':
			clearText_Frequency[i] = 'W';
			break;
		case 'j':
			clearText_Frequency[i] = 'w';
			break;
		case 'K':
			clearText_Frequency[i] = 'V';
			break;
		case 'k':
			clearText_Frequency[i] = 'v';
			break;
		case 'L':
			clearText_Frequency[i] = 'K';
			break;
		case 'l':
			clearText_Frequency[i] = 'k';
			break;
		case 'M':
			clearText_Frequency[i] = 'N';
			break;
		case 'm':
			clearText_Frequency[i] = 'n';
			break;
		case 'N':
			clearText_Frequency[i] = 'F';
			break;
		case 'n':
			clearText_Frequency[i] = 'f';
			break;
		case 'O':
			clearText_Frequency[i] = 'D';
			break;
		case 'o':
			clearText_Frequency[i] = 'd';
			break;
		case 'P':
			clearText_Frequency[i] = 'S';
			break;
		case 'p':
			clearText_Frequency[i] = 's';
			break;
		case 'Q':
			clearText_Frequency[i] = 'Y';
			break;
		case 'q':
			clearText_Frequency[i] = 'y';
			break;
		case 'R':
			clearText_Frequency[i] = 'I';
			break;
		case 'r':
			clearText_Frequency[i] = 'i';
			break;
		case 'S':
			clearText_Frequency[i] = 'G';
			break;
		case 's':
			clearText_Frequency[i] = 'g';
			break;
		case 'T':
			clearText_Frequency[i] = 'B';
			break;
		case 't':
			clearText_Frequency[i] = 'b';
			break;
		case 'U':
			clearText_Frequency[i] = 'M';
			break;
		case 'u':
			clearText_Frequency[i] = 'm';
			break;
		case 'V':
			clearText_Frequency[i] = 'U';
			break;
		case 'v':
			clearText_Frequency[i] = 'u';
			break;
		case 'W':
			clearText_Frequency[i] = 'O';
			break;
		case 'w':
			clearText_Frequency[i] = 'o';
			break;
		case 'Y':
			clearText_Frequency[i] = 'R';
			break;
		case 'y':
			clearText_Frequency[i] = 'r';
			break;
		default:
			clearText_Frequency[i] = cipher[i];
			break;
		}
		clearText_Frequency[i] = clearText_Frequency[i] - key;
	}
}

void RightShift(char *cipher, int length, int key) //key = 2   abcdefg   cdefgab
{
	key = key % 4;

	for (int i = length - key, j = 0; i < length; i++, j++)
	{
		clearText_ShiftLeft[j] = cipher[i];
	}
	for (int i = 0, j = 0; i < length - key; i++, j++)
	{
		clearText_ShiftLeft[i + key] = cipher[i];
	}

	//strncat(clearText_ShiftLeft, cipher, length - key);
}

void VirginiaDecrypt(char *cipher, int length, char* key)
{
	char change_key[1000] = { NULL };
	int temp[1000] = { NULL };
	int temp1[1000] = { NULL };
	int temp2[1000] = { NULL };
	int temp3[1000] = { NULL };
	int keyLength = SL;
	int j = 0;
	int k = 1;
	for (int i = 0; i < keyLength; i++) {					//key對表的結果
		for (int j = 0; j < 95; j++) {
			if (key[i] == MAIN[j]) {
				temp[i] = j;
				break;
			}
		}
	}
	if (length > keyLength) {
		for (int i = 0; i < length; i++) {
			if (i%keyLength == 0) {
				j = 0;
			}
			k = i / keyLength;
			if (i >= keyLength) {
				change_key[i] = MAIN[(temp[j] + k) % 95];
				j++;
			}
			else {
				change_key[i] = key[i];
			}
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			change_key[i] = key[i];
		}
	}
	for (int i = 0; i < length; i++) {					//ciphertext對表的結果		
		for (int j = 0; j < 95; j++) {
			if (cipher[i] == MAIN[j]) {
				temp3[i] = j;
				break;
			}
		}
	}
	for (int i = 0; i < length; i++) {					//change_key對表的結果		
		for (int j = 0; j < 95; j++) {
			if (change_key[i] == MAIN[j]) {
				temp1[i] = j;
				break;
			}
		}
	}
	int t = 0;
	for (int i = 0; i < length; i++) {
		if ((temp3[i] - temp1[i]) < 0) {
			t = (95 - temp1[i]) + temp3[i];
		}
		else {
			t = temp3[i] - temp1[i];
		}
		clearText_Virginia[i] = MAIN[t % 95];
	}
}

void EvenOddChange(char *cipher, int length)
{
	int flag = length % 2;
	if (flag == 1) {
		for (int i = 0; i < length - 1; i = i + 2) {
			temp = cipher[i];
			cipher[i] = cipher[i + 1];
			cipher[i + 1] = temp;
		}
	}
	else {
		for (int i = 0; i < length; i = i + 2) {
			temp = cipher[i];
			cipher[i] = cipher[i + 1];
			cipher[i + 1] = temp;
		}
	}
	for (int i = 0; i < length; i++)
	{
		clearText_EvenOddChange[i] = cipher[i];
	}
}

int ReadDataSize(char *name)
{
	FILE *input_file = 0;
	U_CHAR bmpfileheader[14] = { 0 };
	U_CHAR bmpinfoheader[40] = { 0 };

	INT32 biWidth = 0;
	INT32 biHeight = 0;
	INT16 BitCount = 0;

	/* 開啟檔案 */
	if ((input_file = fopen(name, "rb")) == NULL) {
		fprintf(stderr, "File can't open.\n");
		exit(0);
	}

	FREAD(input_file, bmpfileheader, 14);
	FREAD(input_file, bmpinfoheader, 40);

	if (GET_2B(bmpfileheader, 0) == 0x4D42) /* 'BM' */
		fprintf(stdout, "BMP file.\n");
	else {
		fprintf(stdout, "Not bmp file.\n");
		exit(0);
	}

	biWidth = GET_4B(bmpinfoheader, 4);
	biHeight = GET_4B(bmpinfoheader, 8);
	BitCount = GET_2B(bmpinfoheader, 14);

	if (BitCount != 8) {
		fprintf(stderr, "Not a 8-bit file.\n");
		fclose(input_file);
		exit(0);
	}

	// 
	fclose(input_file);

	return ((biWidth * 1 + 3) / 4 * 4)*biHeight * 1;
}

void ReadImageData(char *name, U_CHAR *bmpfileheader, U_CHAR *bmpinfoheader, U_CHAR *color_table, U_CHAR *data)
{
	FILE *input_file = 0;

	INT32 FileSize = 0;
	INT32 bfOffBits = 0;
	INT32 headerSize = 0;
	INT32 biWidth = 0;
	INT32 biHeight = 0;
	INT16 biPlanes = 0;
	INT16 BitCount = 0;
	INT32 biCompression = 0;
	INT32 biImageSize = 0;
	INT32 biXPelsPerMeter = 0, biYPelsPerMeter = 0;
	INT32 biClrUsed = 0;
	INT32 biClrImp = 0;

	/* 開啟檔案 */
	if ((input_file = fopen(name, "rb")) == NULL) {
		fprintf(stderr, "File can't open.\n");
		exit(0);
	}

	FREAD(input_file, bmpfileheader, 14);
	FREAD(input_file, bmpinfoheader, 40);

	if (GET_2B(bmpfileheader, 0) == 0x4D42) /* 'BM' */
		fprintf(stdout, "BMP file.\n");
	else {
		fprintf(stdout, "Not bmp file.\n");
		exit(0);
	}

	FileSize = GET_4B(bmpfileheader, 2);
	bfOffBits = GET_4B(bmpfileheader, 10);
	headerSize = GET_4B(bmpinfoheader, 0);
	biWidth = GET_4B(bmpinfoheader, 4);
	biHeight = GET_4B(bmpinfoheader, 8);
	biPlanes = GET_2B(bmpinfoheader, 12);
	BitCount = GET_2B(bmpinfoheader, 14);
	biCompression = GET_4B(bmpinfoheader, 16);
	biImageSize = GET_4B(bmpinfoheader, 20);
	biXPelsPerMeter = GET_4B(bmpinfoheader, 24);
	biYPelsPerMeter = GET_4B(bmpinfoheader, 28);
	biClrUsed = GET_4B(bmpinfoheader, 32);
	biClrImp = GET_4B(bmpinfoheader, 36);

	printf("FileSize = %ld \n"
		"DataOffset = %ld \n"
		"HeaderSize = %ld \n"
		"Width = %ld \n"
		"Height = %ld \n"
		"Planes = %d \n"
		"BitCount = %d \n"
		"Compression = %ld \n"
		"ImageSize = %ld \n"
		"XpixelsPerM = %ld \n"
		"YpixelsPerM = %ld \n"
		"ColorsUsed = %ld \n"
		"ColorsImportant = %ld \n", FileSize, bfOffBits, headerSize, biWidth, biHeight, biPlanes,
		BitCount, biCompression, biImageSize, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImp);

	if (BitCount != 8) {
		fprintf(stderr, "Not a 8-bit file.\n");
		fclose(input_file);
		exit(0);
	}

	FREAD(input_file, color_table, 1024);

	//

	//
	fseek(input_file, bfOffBits, SEEK_SET);
	FREAD(input_file, data, ((biWidth * 1 + 3) / 4 * 4)*biHeight * 1);
	// 
	fclose(input_file);
}

int BianaryTransform(int num, int bin_num[])
{

	int i = 0, mod = 0;

	while (num != 0)
	{
		mod = num % 2;
		bin_num[i] = mod;
		num = num / 2;
		i++;
	}

	return i;
}

long long Modular_Exonentiation(long long a, int b, int n)
{
	int c = 0, bin_num[1000];
	long long d = 1;
	int k = BianaryTransform(b, bin_num) - 1;

	for (int i = k; i >= 0; i--)
	{
		c = 2 * c;
		d = (d*d) % n;
		if (bin_num[i] == 1)
		{
			c = c + 1;
			d = (d*a) % n;
		}
	}
	return d;
}

int ProducePrimeNumber(int prime[])
{
	int c = 0, vis[1001];
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= 1000; i++)if (!vis[i])
	{
		prime[c++] = i;
		for (int j = i*i; j <= 1000; j += i)
			vis[j] = 1;
	}

	return c;
}

int Exgcd(int m, int n, int &x)
{
	int x1, y1, x0, y0, y;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	int r = m%n;
	int q = (m - r) / n;
	while (r)
	{
		x = x0 - q*x1; y = y0 - q*y1;
		x0 = x1; y0 = y1;
		x1 = x; y1 = y;
		m = n; n = r; r = m%n;
		q = (m - r) / n;
	}
	return n;
}

void RSA_Decrypt()
{
	int i = 0;
	cout << "請輸入私鑰(d,n):" << endl;
	cin >> dd >> nn;

	for (i = 0; i < 100; i++)
		Ciphertext[i] = Modular_Exonentiation(Ciphertext[i], dd, nn);

	cout << "使用私鑰解密:" << '\n';
	char As[100] = { 0 };

	for (i = 0; i < 100; i++)
	{
		As[i] = Ciphertext[i];
		cout << As[i];
	}

	SL = strlen(As);

	cout << '\n' << '\n';
}

int main()
{

	string S;

	cout << "輸入key的密文:" << endl;

	getline(cin, S);

	int an = 0, ai = 0;
	stringstream ss(S);
	while (ss >> an)
	{
		Ciphertext[ai] = an;
		ai++;
	}

	RSA_Decrypt();

	FILE *output_file = 0;

	U_CHAR bmpfileheader1[14] = { 0 };
	U_CHAR bmpinfoheader1[40] = { 0 };
	U_CHAR *data1, *data2, *new_data, color_table1[1024];


	INT32 biWidth = 0;
	INT32 biHeight = 0;

	int i, j, k, n, temp, sum = 0;

	i = ReadDataSize("cipher.bmp");
	data1 = (U_CHAR *)malloc(i);
	if (data1 == NULL) {
		exit(0);
	}

	ReadImageData("cipher.bmp", bmpfileheader1, bmpinfoheader1, color_table1, data1);
	biWidth = GET_4B(bmpinfoheader1, 4);
	biHeight = GET_4B(bmpinfoheader1, 8);

	//
	//i = ReadDataSize("new2.bmp");
	data2 = (U_CHAR *)malloc(i);
	if (data2 == NULL) {
		exit(0);
	}
	// Process the file
	for (i = 0; i < biHeight; i++)
	{
		k = i* ((biWidth * 1 + 3) / 4 * 4);
		for (j = 6; j >= 0; j--)
		{
			data2[k] = data1[k] % 2;
			sum = sum + data2[k] * pow(2.0, j);
			k = k + 1;
		}
		cipher[i] = sum;
		sum = 0;
	}
	printf("%s\n", cipher);

	//decrypt
	char keystring[256];
	int keynumber = 0;

	for (int i = 0; i < SL; i++)
	{
		keystring[i] = Ciphertext[i];
	}


	int keyLength = SL;
	for (int i = 0; i < keyLength; i++)
	{
		keynumber = keynumber + keystring[i];
	}

	int cipherLength = strlen(cipher);

	EvenOddChange(cipher, cipherLength);
	//cout << "clearText_EvenOddChange" << endl;
	cout << clearText_EvenOddChange << endl;

	VirginiaDecrypt(clearText_EvenOddChange, cipherLength, keystring);
	//cout << "clearText_Virginia" << endl;
	cout << clearText_Virginia << endl;

	unTransform(clearText_Virginia, cipherLength);
	//cout << "clearText_Transform" << endl;
	cout << clearText_Transform << endl;

	FrequencyDecrypt(clearText_Transform, cipherLength, keynumber);
	//cout << "clearText_Frequency" << endl;
	cout << clearText_Frequency << endl;

	RightShift(clearText_Frequency, cipherLength, keynumber);
	//cout << "clearText_ShiftLeft" << endl;
	cout << clearText_ShiftLeft << endl;

	CiserDecrypt(clearText_ShiftLeft, cipherLength);
	//cout << "clearText" << endl;
	cout << clearText << endl;

	free(data1);
	free(data2);
	system("pause");
	return 0;
}
