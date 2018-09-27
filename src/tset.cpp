// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <conio.h>

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.GetMaxPower())
{
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;          
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = BitField.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

TBitField TSet::GetBitField() //
{
	return BitField;
}

int TSet::min(int left, int right)
{
	if (left <= right)
		return left;
	else return right;
}
int TSet::max(int left, int right)
{
	if (left >= right)
		return left;
	else return right;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}
//
//// теоретико-множественные операции
//
TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((s.BitField == BitField)&&(s.GetMaxPower() == MaxPower))     
		return 1;
	else
		return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if ((s.BitField == BitField) && (s.GetMaxPower() == MaxPower))    
		return 0;
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(max(GetMaxPower(), s.GetMaxPower()));
	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower)
		throw "incorrect value";
	TSet tmp(MaxPower);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
		throw "incorrect value";
	TSet tmp(MaxPower);
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(max(GetMaxPower(), s.GetMaxPower()));
	tmp = BitField & s.BitField;
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(GetMaxPower());
	tmp.BitField = ~BitField;
	return tmp;
}
//
//// перегрузка ввода/вывода
//
istream &operator>>(istream &istr, TSet &s) // ввод
{ 
	istr >> s.BitField;
	s.MaxPower = s.BitField.GetLength();
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
