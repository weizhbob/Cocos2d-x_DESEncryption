#include "cooloi_des.h"

CooloiDES::CooloiDES()
{
	if(DES_set_key_checked(&cb1, &ks1)||
	   DES_set_key_checked(&cb2, &ks2)||
	   DES_set_key_checked(&cb3, &ks3))
	{
		std::cout << "key error" << std::endl;
		//return "key error";
	}
}

CooloiDES::~CooloiDES()
{}

std::string CooloiDES::Encrypt(std::string msg)
{
	char string[256];
	strcpy(string,msg.c_str());

	char* cipher(new char[256]);

	memset(cipher,0,256);

	DES_set_odd_parity(&cblock);

	DES_ede3_cbc_encrypt((const unsigned char*)string,
						 (unsigned char*)cipher,
						  256,&ks1,&ks2,&ks3,&cblock,DES_ENCRYPT);

	std::string e_msg(&cipher[0],&cipher[258]);
	free(cipher);
	
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

	DES_ede3_cbc_encrypt((const unsigned char*)cipher,
                         (unsigned char*)text,
                          256, &ks1, &ks2, &ks3,
                         &cblock,DES_DECRYPT);

	std::string d_msg = text;

	free(cipher);
	free(text);

	return d_msg;
}
