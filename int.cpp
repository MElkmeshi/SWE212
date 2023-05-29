#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

long int public_key;
long int private_key;
long long int n;
long long int gcd(long long int a, long long int h)
{
	long long int temp;
	while (1) {
		temp = a % h;
		if (temp == 0)
			return h;
		a = h;
		h = temp;
	}
}
long long int karatsuba(long int x, long int y) {
	int n = max(to_string(x).size(), to_string(y).size());
	// base case
	if (n < 2)
		return x * y;
	//divide 
	/*new n*/n = (n / 2) + (n % 2);
	long int multiplier = pow(10, n);
	long int b = x / multiplier;
	long int a = x - (b * multiplier);
	long int d = y / multiplier;
	long int c = y - (d * multiplier);
	long long int ac = karatsuba(a, c);
	long long int bd = karatsuba(b, d);
	long long int abcd = karatsuba((a + b), (c + d));
	//combine
	return ac + ((abcd - ac - bd) * multiplier) + (bd * (pow(10, 2 * n)));
}
long long int brute_force(long int a, long int b) {
	long int result = 0;
	long int multiplier = 1;
	while (b > 0) {
		long int digit = b % 10;
		result += a * digit * multiplier;
		b /= 10;
		multiplier *= 10;
	}
	return result;
}
long long int encrypt(double message)
{
	long int e = public_key;
	long long int encrpyted_text = 1;
	while (e--) {//message^public_key & n
		encrpyted_text *= message;
		encrpyted_text %= n;
	}
	return encrpyted_text;
}
long long int decrypt(int encrpyted_text)
{
	long int d = private_key;
	long long int decrypted = 1;
	while (d--) {//encrpyted_text^private_key & n
		decrypted *= encrpyted_text;
		decrypted %= n;
	}
	return decrypted;
}
vector<int> encoder(string message)
{
	vector<int> form;
	// calling the encrypting function in encoding function
	for (auto& letter : message) {
		form.push_back(encrypt((int)letter));
	}
	return form;
}
string decoder(vector<int> encoded)
{
	string s;
	// calling the decrypting function decoding function
	for (auto& num : encoded)
		s += decrypt(num);
	return s;
}
int main()
{
	long int p = 1289;
	long int q = 7219;
	cout << "brute force" << endl;
	n = karatsuba(p,q);
	cout << "n " << n << endl;
	n = brute_force(p, q);
	cout << "n " << n << endl;
	long long int fi = (p - 1) * (q - 1);
	long long int e = 2;
	while (e < fi) { 
		if (gcd(e, fi) == 1)
			break;
		e++;
	}
	cout << "fi: " << fi << endl;
	cout << "e: " << e<<endl;
	public_key = e;
	long long int d = 2;
	while (true) {
		if ((d * e) % fi == 1)
			break;
		d++;
	}
	cout << "d: " << d << endl;
	private_key = d;
	string message = "Test Message";
	cout << "Initial message:\n" << message;
	vector<int> coded = encoder(message);
	cout << "\n\nThe encoded message(encrypted by public key)\n";
	for (auto& p : coded)
		cout << p;
	cout << "\n\nThe decoded message(decrypted by private "
		"key)\n";
	cout << decoder(coded) << endl;
	return 0;
}
