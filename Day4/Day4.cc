#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>

//Blatantly stolen from https://terminalroot.com/how-to-generate-md5-hash-with-cpp-and-openssl/
std::string md5(const std::string &str){
  unsigned char hash[MD5_DIGEST_LENGTH];

  MD5_CTX md5;
  MD5_Init(&md5);
  MD5_Update(&md5, str.c_str(), str.size());
  MD5_Final(hash, &md5);

  std::stringstream ss;

  for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
  }
  return ss.str();
}

uint64_t fiveZeros(const std::string &secret)
{
	uint64_t result = 0;
	bool done = false;
	
	while(!done)
	{
		std::string key = std::to_string(result);
		std::string hash = md5(secret+key);
		if(hash[0] == '0' && hash[1] == '0' && hash[2] == '0' && hash[3] == '0' && hash[4] == '0')
		{
			done = true;
		}
		else
		{
			result++;
		}
	}
	return result;
}

uint64_t sixZeros(const std::string &secret)
{
	uint64_t result = 0;
	bool done = false;
	
	while(!done)
	{
		std::string key = std::to_string(result);
		std::string hash = md5(secret+key);
		if(hash[0] == '0' && hash[1] == '0' && hash[2] == '0' && hash[3] == '0' && hash[4] == '0' && hash[5] == '0')
		{
			done = true;
		}
		else
		{
			result++;
		}
	}
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string secret;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, secret);
	}
  input.close();
	
	resultA = fiveZeros(secret);
	resultB = sixZeros(secret);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;

	return 0;
}
