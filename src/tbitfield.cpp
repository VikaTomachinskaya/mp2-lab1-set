// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>
#include <exception>

using namespace std;

TBitField::TBitField(int len)
{
    BitLen = len;
    if (len > -1) {
        MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
    }
    else
        throw logic_error("Input error: incorrect length of BitField in constructor");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n > -1 && n < BitLen)
        return(n / (sizeof(TELEM) * 8));
    else
        throw logic_error("Input error: incorrect bit length");
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return (1 << n % (sizeof(TELEM)*8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > -1 && n < BitLen)
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
    else
        throw logic_error("Input error: incorrect bit length");
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n > -1 && n < BitLen)
        pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
    else
        throw logic_error("Input error: incorrect bit length");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n > -1) && (n < BitLen))
  {
      int index;
      index = GetMemIndex(n);
      if (pMem[index] & GetMemMask(n))
      {
          return 1;
      }
      else
          return 0;
  }
  else
      throw "not correct";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (&bf == this)
        return *this;
    if (bf.pMem)
    {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if ((BitLen == bf.BitLen) && (MemLen == bf.MemLen))
  {
      for (int i = 0; i < MemLen; i++)
      {
          if (pMem[i] != bf.pMem[i])
              return 0;
      }
      return 1;
  }
  else
      return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen)
  {
      return 1;
  }
    else
    {
        for(int i=0; i<MemLen; i++)
        {
            return 1;
        }
    }
  else
      return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i;
    int len = BitLen;
    if (len < bf.BitLen)
    {
        len = bf.BitLen;
    }
    TBitField pr(len);
        for (i = 0; i < MemLen; i++)
        {
            pr.pMem[i] = pMem[i];
        }
        for (i = 0; i < bf.MemLen; i++)
        {
            pr.pMem[i] |= bf.pMem[i];
        }
    return pr;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int len, mem;
    if (BitLen > bf.BitLen)
    {
        len = BitLen;
        mem = bf.MemLen;
    }
    else
    {
        len = bf.BitLen;
        mem = MemLen;
    }

    TBitField pr(len);

    for (int i = 0; i < mem; i++)
        pr.pMem[i] = pMem[i] & bf.pMem[i];

    return pr;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string tmp;
    istr >> tmp;
    if (tmp.size() != bf.GetLength())
      throw logic_error("Input error: incorrect length in the input");
    for (int i = 0; i < bf.BitLen; i++)
    {
      if (tmp[i] == '0')
        bf.ClrBit(i);
      else
          if (tmp[i] == '1')
              bf.SetBit(i);
          else
              throw ios_base::failure("Input error: incorrect input");
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i))
          ostr << 1 << " ";
        else
          ostr << 0 << " ";
    }
    return ostr;
}
