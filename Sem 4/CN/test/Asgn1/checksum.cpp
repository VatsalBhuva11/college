
#include <bits/stdc++.h>
using namespace std;


string Ones_complement(string data)
{
	for (int i = 0; i < data.length(); i++) {
		if (data[i] == '0')
			data[i] = '1';
		else
			data[i] = '0';
	}

	return data;
}


string checkSum(string data, int block_size)
{

	int n = data.length();
	if (n % block_size != 0) {
		int pad_size = block_size - (n % block_size);
		for (int i = 0; i < pad_size; i++) {
			data = '0' + data;
		}
	}


	string result = "";


	for (int i = 0; i < block_size; i++) {
		result += data[i];
	}

	for (int i = block_size; i < n; i += block_size) {


		string next_block = "";

		for (int j = i; j < i + block_size; j++) {
			next_block += data[j];
		}


		string additions = "";
		int sum = 0, carry = 0;

		for (int k = block_size - 1; k >= 0; k--) {
			sum += (next_block[k] - '0')
				+ (result[k] - '0');
			carry = sum / 2;
			if (sum == 0) {
				additions = '0' + additions;
				sum = carry;
			}
			else if (sum == 1) {
				additions = '1' + additions;
				sum = carry;
			}
			else if (sum == 2) {
				additions = '0' + additions;
				sum = carry;
			}
			else {
				additions = '1' + additions;
				sum = carry;
			}
		}


		string final = "";

		if (carry == 1) {
			for (int l = additions.length() - 1; l >= 0;
				l--) {
				if (carry == 0) {
					final = additions[l] + final;
				}
				else if (((additions[l] - '0') + carry) % 2
						== 0) {
					final = "0" + final;
					carry = 1;
				}
				else {
					final = "1" + final;
					carry = 0;
				}
			}

			result = final;
		}
		else {
			result = additions;
		}
	}

	return Ones_complement(result);
}


bool checker(string sent_message,
			string rec_message,
			int block_size)
{

	string sender_checksum
		= checkSum(sent_message, block_size);

	string receiver_checksum = checkSum(
		rec_message + sender_checksum, block_size);

	if (count(receiver_checksum.begin(),
			receiver_checksum.end(), '0')
		== block_size) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	string sent_message
		= "10000101011000111001010011101101";
	string recv_message
		= "10000101011000111001010011101101";
	int block_size = 8;

	if (checker(sent_message,
				recv_message,
				block_size)) {
		cout << "No Error";
	}
	else {
		cout << "Error";
	}

	return 0;
}
