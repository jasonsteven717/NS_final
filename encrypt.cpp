#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<ctime>
using namespace std;
#pragma warning(disable : 4996)


char MAIN[95] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '.', '?', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
'{', '}', '[', ']', '|', ';', ':', '\"', '\'', ',', '<', '>', '/', '-', '`' ,'=', '\\' };


char clearText[256];
char cipher_Ciser[256];
char cipher_Frequency[256];
char cipher_Virginia[256];
char cipher_ShiftLeft[256];
char cipher_Transform[256];
char cipher_EvenOddChange[256];
char cipher[256];
int cipherBinary[256][7];
char temp;
int flag = 0;

int Plaintext[256];//明文
long long Ciphertext[256];//密文
int nn, ee = 0, dd, SL = 0;

typedef long INT32;
typedef unsigned short int INT16;
typedef unsigned char U_CHAR;

#define UCH(x)	((int) (x))
#define GET_2B(array,offset)  ((INT16) UCH(array[offset]) + \
			       (((INT16) UCH(array[offset+1])) << 8))
#define GET_4B(array,offset)  ((INT32) UCH(array[offset]) + \
			       (((INT32) UCH(array[offset+1])) << 8) + \
			       (((INT32) UCH(array[offset+2])) << 16) + \
			       (((INT32) UCH(array[offset+3])) << 24))
#define FREAD(file,buf,sizeofbuf)  \
  ((size_t) fread((void *) (buf), (size_t) 1, (size_t) (sizeofbuf), (file)))

void CiserEncrypt(char *clearText, int length)
{
	//密文第一個字元
	int c = 0;
	int key = 7;
	for (int y = 0; y<95; y++)
	{
		if (MAIN[y] == clearText[0])
			c = y;
	}

	cipher_Ciser[0] = MAIN[(c*key) % 95];

	int Y = 1;
	for (int h = 1; h<length; h++)
	{
		int x1 = 0;		//對應表格找到明文(Y)位子
		for (int y = 0; y<95; y++)
		{
			if (MAIN[y] == clearText[Y])
			{
				x1 = y;
				break;
			}
		}

		int x2 = 0;		//對應表格找到密文(Y-1)位子
		for (int y = 0; y<95; y++)
		{
			if (MAIN[y] == cipher_Ciser[Y - 1])
			{
				x2 = y;
				break;
			}
		}

		cipher_Ciser[Y] = MAIN[((x1 - x2 + 95)*key) % 95]; ///////////////+65

		Y++;
	}

}

void FrequencyEncrypt(char *clearText, int length, int key)
{
	key = key % 4;
	for (int i = 0; i < length; i++)
	{
		clearText[i] = clearText[i] + key;
		switch (clearText[i])
		{
		case 'A':
			cipher_Frequency[i] = 'E';
			break;
		case 'a':
			cipher_Frequency[i] = 'e';
			break;
		case 'B':
			cipher_Frequency[i] = 'T';
			break;
		case 'b':
			cipher_Frequency[i] = 't';
			break;
		case 'C':
			cipher_Frequency[i] = 'A';
			break;
		case 'c':
			cipher_Frequency[i] = 'a';
			break;
		case 'D':
			cipher_Frequency[i] = 'O';
			break;
		case 'd':
			cipher_Frequency[i] = 'o';
			break;
		case 'E':
			cipher_Frequency[i] = 'I';
			break;
		case 'e':
			cipher_Frequency[i] = 'i';
			break;
		case 'F':
			cipher_Frequency[i] = 'N';
			break;
		case 'f':
			cipher_Frequency[i] = 'n';
			break;
		case 'G':
			cipher_Frequency[i] = 'S';
			break;
		case 'g':
			cipher_Frequency[i] = 's';
			break;
		case 'I':
			cipher_Frequency[i] = 'R';
			break;
		case 'i':
			cipher_Frequency[i] = 'r';
			break;
		case 'J':
			cipher_Frequency[i] = 'D';
			break;
		case 'j':
			cipher_Frequency[i] = 'd';
			break;
		case 'K':
			cipher_Frequency[i] = 'L';
			break;
		case 'k':
			cipher_Frequency[i] = 'l';
			break;
		case 'L':
			cipher_Frequency[i] = 'C';
			break;
		case 'l':
			cipher_Frequency[i] = 'c';
			break;
		case 'M':
			cipher_Frequency[i] = 'U';
			break;
		case 'm':
			cipher_Frequency[i] = 'u';
			break;
		case 'N':
			cipher_Frequency[i] = 'M';
			break;
		case 'n':
			cipher_Frequency[i] = 'm';
			break;
		case 'O':
			cipher_Frequency[i] = 'W';
			break;
		case 'o':
			cipher_Frequency[i] = 'w';
			break;
		case 'P':
			cipher_Frequency[i] = 'F';
			break;
		case 'p':
			cipher_Frequency[i] = 'f';
			break;
		case 'Q':
			cipher_Frequency[i] = 'G';
			break;
		case 'q':
			cipher_Frequency[i] = 'g';
			break;
		case 'R':
			cipher_Frequency[i] = 'Y';
			break;
		case 'r':
			cipher_Frequency[i] = 'y';
			break;
		case 'S':
			cipher_Frequency[i] = 'P';
			break;
		case 's':
			cipher_Frequency[i] = 'p';
			break;
		case 'T':
			cipher_Frequency[i] = 'B';
			break;
		case 't':
			cipher_Frequency[i] = 'b';
			break;
		case 'U':
			cipher_Frequency[i] = 'V';
			break;
		case 'u':
			cipher_Frequency[i] = 'v';
			break;
		case 'V':
			cipher_Frequency[i] = 'K';
			break;
		case 'v':
			cipher_Frequency[i] = 'k';
			break;
		case 'W':
			cipher_Frequency[i] = 'J';
			break;
		case 'w':
			cipher_Frequency[i] = 'j';
			break;
		case 'Y':
			cipher_Frequency[i] = 'Q';
			break;
		case 'y':
			cipher_Frequency[i] = 'q';
			break;
		default:
			cipher_Frequency[i] = clearText[i];
			break;
		}
	}
}

void VirginiaEncrypt(char *clearText, int length, char *key) {

	int j = 0;
	int k = 1;
	//string key;
	char change_key[1000] = { NULL };
	int temp[1000] = { NULL };
	int temp1[1000] = { NULL };
	int temp2[1000] = { NULL };
	int temp3[1000] = { NULL };
	int keyLength = 0;
	keyLength = strlen(key);
	for (int i = 0; i < keyLength; i++) {					//key對表的結果
		for (int j = 0; j < 95; j++) {
			if (key[i] == MAIN[j]) {
				temp[i] = j;
				break;
			}
		}
	}
	for (int i = 0; i < length; i++) {					//cleartext對表的結果
		for (int j = 0; j < 95; j++) {
			if (clearText[i] == MAIN[j]) {
				temp2[i] = j;
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
	/*for (int i = 0; i < length; i++) {
	cout << change_key[i];
	}
	cout << endl;*/
	for (int i = 0; i < length; i++) {					//chande_key對表的結果		
		for (int j = 0; j < 95; j++) {
			if (change_key[i] == MAIN[j]) {
				temp1[i] = j;
				break;
			}
		}
	}
	//cout << endl;
	for (int i = 0; i < length; i++) {
		cipher_Virginia[i] = MAIN[(temp1[i] + temp2[i]) % 95];
		//cout << ciphertext[i];
	}
	//cout << endl;
}

void ShiftLeft(char *clearText, int length, int key)  //key = 2   abcdefg   cdefgab
{
	key = key % 4;
	for (int i = 0; i < length - key; i++)
	{
		cipher_ShiftLeft[i] = clearText[i + key];
	}

	strncat(cipher_ShiftLeft, clearText, key);
}

void Transform(char *clearText, int length)
{
	for (int i = 0; i < length; i++)
	{
		cipher_Transform[i] = clearText[(length - 1) - i];
	}
}

void EvenOddChange(char *clearText, int length)
{
	flag = length % 2;
	if (flag == 1) {
		for (int i = 0; i < length - 1; i = i + 2) {
			temp = clearText[i];
			clearText[i] = clearText[i + 1];
			clearText[i + 1] = temp;
		}
	}
	else {
		for (int i = 0; i < length; i = i + 2) {
			temp = clearText[i];
			clearText[i] = clearText[i + 1];
			clearText[i + 1] = temp;
		}
	}
	for (int i = 0; i < length; i++) {
		cipher_EvenOddChange[i] = clearText[i];
		//cout << clearText[i];
	}
	//cout << endl;
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


void RSA_Initialize()
{
	int prime[5000];
	int count_Prime = ProducePrimeNumber(prime);

	srand((unsigned)time(NULL));
	int ranNum1 = rand() % count_Prime;
	int ranNum2 = rand() % count_Prime;
	int p = prime[ranNum1], q = prime[ranNum2];

	nn = p*q;

	int On = (p - 1)*(q - 1);


	for (int j = 3; j < On; j += 1331)
	{
		int gcd = Exgcd(j, On, dd);
		if (gcd == 1 && dd > 0)
		{
			ee = j;
			break;
		}

	}

}

void RSA_Encrypt()
{
	cout << "公鑰(e, n) : e = " << ee << " n = " << nn << '\n';
	cout << "私鑰(d, n) : d = " << dd << " n = " << nn << '\n' << '\n';

	int i = 0;
	for (i = 0; i < SL; i++)
		Ciphertext[i] = Modular_Exonentiation(Plaintext[i], ee, nn);

	char As[100];
	cout << "KEY已使用使用公鑰加密:" << '\n';
	for (i = 0; i < SL; i++)
	{
		As[i] = Ciphertext[i];
		cout << Ciphertext[i] << " ";
	}
	cout << '\n' << '\n';
}

int main()
{
	FILE *output_file = 0;

	U_CHAR bmpfileheader1[14] = { 0 };
	U_CHAR bmpinfoheader1[40] = { 0 };
	U_CHAR *data1, *data2, *new_data, color_table1[1024];


	INT32 biWidth = 0;
	INT32 biHeight = 0;

	int i, j, k, n, temp;
	int histo_table[256] = { 0 };

	i = ReadDataSize("Lena256.bmp");
	data1 = (U_CHAR *)malloc(i);
	if (data1 == NULL) {
		exit(0);
	}

	ReadImageData("Lena256.bmp", bmpfileheader1, bmpinfoheader1, color_table1, data1);
	biWidth = GET_4B(bmpinfoheader1, 4);
	biHeight = GET_4B(bmpinfoheader1, 8);

	data2 = (U_CHAR *)malloc(i);
	if (data2 == NULL) {
		exit(0);
	}

	//encrypt
	char keystring[256];
	int keynumber = 0;

	cout << "請輸入明文:";
	cin.getline(clearText, 256);
	cout << "請輸入KEY:";
	cin.getline(keystring, 256);

	int keyLength = strlen(keystring);
	for (int i = 0; i < keyLength; i++)
	{
		Plaintext[i] = keystring[i];
		keynumber = keynumber + keystring[i];
	}

	int clearTextLength = strlen(clearText);

	CiserEncrypt(clearText, clearTextLength);
	//cout << "cipher_Ciser" << endl;
	cout << cipher_Ciser << endl;

	ShiftLeft(cipher_Ciser, clearTextLength, keynumber);
	//cout << "cipher_ShiftLeft" << endl;
	cout << cipher_ShiftLeft << endl;

	FrequencyEncrypt(cipher_ShiftLeft, clearTextLength, keynumber);
	//cout << "cipher_Frequency" << endl;
	cout << cipher_Frequency << endl;

	Transform(cipher_Frequency, clearTextLength);
	//cout << "cipher_Transform" << endl;
	cout << cipher_Transform << endl;

	VirginiaEncrypt(cipher_Transform, clearTextLength, keystring);
	//cout << "cipher_Virginia" << endl;
	cout << cipher_Virginia << endl;

	EvenOddChange(cipher_Virginia, clearTextLength);
	//cout << "cipher_EvenOddChange" << endl;
	cout << cipher_EvenOddChange << endl;

	for (int i = 0; i < clearTextLength; i++)
	{
		cipher[i] = cipher_EvenOddChange[i];
	}

	//change to ASCII
	for (i = 0; i < clearTextLength; i++)
	{
		j = 6;
		while (cipher[i] > 0)
		{
			cipherBinary[i][j] = cipher[i] % 2;
			cipher[i] = cipher[i] / 2;
			j--;
		}
	}

	/*for (i = 0; i < 256; i++)
	{
	for (j = 0; j < 7; j++)
	printf("%d", clearTextBinary[i][j]);
	printf("\n");
	}*/

	// hide ASCII in an image
	for (i = 0; i < biHeight; i++)
	{
		k = i* ((biWidth * 1 + 3) / 4 * 4);
		for (j = 0; j < biWidth; j++)
		{
			data2[k] = data1[k] / 2 * 2;

			k = k + 1;
		}
	}

	for (i = 0; i < clearTextLength; i++)
	{
		k = i* ((biWidth * 1 + 3) / 4 * 4);
		for (j = 0; j < 7; j++)
		{
			data2[k] = data2[k] + cipherBinary[i][j];
			k = k + 1;
		}
	}

	/* 開啟新檔案 */
	if ((output_file = fopen("cipher.bmp", "wb")) == NULL) {
		fprintf(stderr, "Output file can't open.\n");
		exit(0);
	}

	fwrite(bmpfileheader1, sizeof(bmpfileheader1), 1, output_file);
	fwrite(bmpinfoheader1, sizeof(bmpinfoheader1), 1, output_file);

	fwrite(color_table1, 1024, 1, output_file);

	fwrite(data2, ((biWidth * 1 + 3) / 4 * 4)*biHeight * 1, 1, output_file);

	fclose(output_file);

	free(data1);
	free(data2);

	SL = keyLength;

	while (!ee)
	{
		RSA_Initialize();
	}
	RSA_Encrypt();

	system("pause");
	return 0;
}


