#pragma once
class Field_Descriptor
{
public:
	unsigned char name[10];
	unsigned char type;
	unsigned long field_data_address;
	unsigned char field_length;
	unsigned char decimal_count;
	unsigned char ver10_reserved[14];

};

