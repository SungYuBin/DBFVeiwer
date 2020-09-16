#pragma once
class Dbf_header
{
public:

	unsigned char version;
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned long recordn;
	unsigned short int header_length;
	unsigned short int record_length;
	unsigned char ver10_reserved[20];
};

