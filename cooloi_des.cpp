#include "cooloi_des.h"

CooloiDES::CooloiDES()
{}

CooloiDES::~CooloiDES()
{}

std::string CooloiDES::Encrypt(std::string msg)
{
	char string[msg.size()];
	strncpy(string,msg.c_str(),msg.length());

	int stringLen(sizeof(string));
	char* cipher(new char[256]);
	char* text(new char[stringLen]);
	memset(cipher,0,256);
	memset(text,0,stringLen);

	DES_set_odd_parity(&cblock);

	if(DES_set_key_checked(&cb1, &ks1)||
	   DES_set_key_checked(&cb2, &ks2)||
	   DES_set_key_checked(&cb3, &ks3))
	{
		//std::cout << "key error" << std::endl;
		return "key error";
	}

	DES_ede3_cbc_encrypt((const unsigned char*)string,
						 (unsigned char*)cipher,
						  stringLen,&ks1,&ks2,&ks3,&cblock,DES_ENCRYPT);

	std::string e_msg = cipher;
	
	return e_msg;
}

std::string CooloiDES::Decrypt(std::string msg)
{
	char* cipher(new char[256]);
	//char* text(new char[stringLen]);
	char* text(new char[256]);
	memset(cipher,0,256);
	memset(text,0,256);

	//cipher = msg.c_str();
	strcpy(cipher,msg.c_str());

	memset(cblock,0,sizeof(DES_cblock));

	DES_set_odd_parity(&cblock);

	if(DES_set_key_checked(&cb1, &ks1)||
	   DES_set_key_checked(&cb2, &ks2)||
	   DES_set_key_checked(&cb3, &ks3))
	{
		//std::cout << "key error" << std::endl;
		return "key error";
	}

	DES_ede3_cbc_encrypt((const unsigned char*)cipher,
                         (unsigned char*)text,
                          256, &ks1, &ks2, &ks3,
                         &cblock,DES_DECRYPT);

	std::string d_msg = text;
	return d_msg;
}
