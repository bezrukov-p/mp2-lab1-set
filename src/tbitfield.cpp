// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include "iostream";
#include "string"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen / (sizeof(TELEM)*8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
		throw "Invalid length";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
		return (n / (sizeof(TELEM) * 8));
	else
		throw "Invalid value";
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int position = n % (sizeof(TELEM) * 8);
	mask = mask << position;
	return mask;
}

//// доступ к битам битового поля
//
int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n<BitLen)
	{
		int position = n % (sizeof(TELEM) * 8);
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(position);
	}
	else 
		throw "incorrect value";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		int position = n % (sizeof(TELEM) * 8);      
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(position));
	}
	else throw "Invalid index";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n <= BitLen)
	{
		int tmp = 1;
		int position = n % (sizeof(TELEM) * 8);
		tmp = tmp << position;
		if ((pMem[GetMemIndex(n)] & tmp) == tmp)                      
			return 1;
		if ((pMem[GetMemIndex(n)] & tmp) == 0)
			return 0;
	}
	else throw "Invalid index";
}

////// битовые операции
////
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
	}
	return 0;
}

int TBitField::min(int left, int right)
{
	if (left <= right)
		return left;
	else return right;
}
int TBitField::max(int left, int right)
{
	if (left >= right)
		return left;
	else return right;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(max(GetLength(), bf.GetLength()));
	for (int i = 0; i <min(MemLen, bf.MemLen); i++)
	{
		tmp.pMem[i] = (pMem[i] | bf.pMem[i]);
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(max(GetLength(), bf.GetLength()));
	for (int i = 0; i <min(MemLen, bf.MemLen); i++)
	{
		tmp.pMem[i] = (pMem[i] & bf.pMem[i]);
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TELEM tmp = 0;
	TBitField tmpbit(*this);
	int index = BitLen % (sizeof(TELEM)*8);
	for (int i = 0; i < index; i++)
		tmp = tmp + pow(2, i);
	for (int i = 0; i < MemLen; i++)                     
	{
		if (i == MemLen - 1)
			tmpbit.pMem[i] = ~pMem[i] & tmp;
		else
			tmpbit.pMem[i] = ~pMem[i];
	}
	return tmpbit;
}
//
//// ввод/вывод
//
istream &operator>>(istream &istr, TBitField &bf)// ввод
{
	string str;
	istr >> str;
	int j = str.size() - 1;
	for (int i = 0; i < str.size(); i++, j--)
	{
		if (str[i] == '1')
			bf.SetBit(j);
	}
	return istr;
}


ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int j = bf.BitLen - 1;
	for (int i = 0; i < bf.BitLen; i++, j--)
	{
		if (bf.GetBit(j) == 0)
			ostr << 0;
		else
			ostr << 1;
	}
	return ostr;
}
