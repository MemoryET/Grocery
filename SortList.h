#pragma once
#define MAX_AMOUT (500)
#define TEMP template<class T> 


TEMP
struct ST_WAVEDATA
{
	int nIndex;
	T fValue;
};

TEMP
class CSortList
{
public:
	CSortList();
	~CSortList();
	void Insert(T Data);
	T GetMaxValue();
	T GetMinValue();
	unsigned int GetValidDataNumber();
private:
	unsigned int FindInsertPos(unsigned int nBeginPos, unsigned int nEndPos, T fValue);
	unsigned int FindInsertPosRecursion(unsigned int nBeginPos, unsigned int nEndPos, T fValue);
	unsigned int FineDeletePos();
	static ST_WAVEDATA<T> sortList[MAX_AMOUT];
	unsigned int ValidDataNumber;
	unsigned int DataLen;
};
TEMP
ST_WAVEDATA<T> CSortList<T>::sortList[MAX_AMOUT];

TEMP
CSortList<T>::CSortList()
{
	ValidDataNumber = 0;
	DataLen = sizeof(ST_WAVEDATA<T>);
	memset(sortList, 0, sizeof(ST_WAVEDATA<T>) * MAX_AMOUT);
}
TEMP
CSortList<T>::~CSortList()
{
	memset(sortList, 0, sizeof(ST_WAVEDATA<T>) * MAX_AMOUT);
}
TEMP
unsigned int CSortList<T>::FineDeletePos()
{
	for (unsigned int i = 0; i < MAX_AMOUT; i++)
	{
		if (sortList[i].nIndex == (ValidDataNumber - MAX_AMOUT))
		{
			return i;
		}
	}
	return 0;
}
TEMP
void CSortList<T>::Insert(T Data)
{
	unsigned int nInsertPos = 0;

	//移动数组
	if (ValidDataNumber<MAX_AMOUT)
	{//数组未满
	 //找到插入位置
		nInsertPos = FindInsertPos(0, ValidDataNumber, Data);
		memcpy(&sortList[nInsertPos + 1], &sortList[nInsertPos], DataLen*(ValidDataNumber - nInsertPos + 1));
	}
	else
	{//数组已满
	 //1、找到过期数据
		unsigned int nNeedDeletePos = FineDeletePos();
		//2、移动数组
		if (nNeedDeletePos == (MAX_AMOUT - 1))
		{
			//指向数组最后一个，不移动
		}
		else
		{
			memcpy(&sortList[nNeedDeletePos], &sortList[nNeedDeletePos + 1], DataLen*((MAX_AMOUT - 1) - nNeedDeletePos));
		}
		//3、清理过期数据后的数组移动后长度为MAX_AMOUT-1，最大元素下标为MAX_AMOUT-2
		//找到插入位置
		nInsertPos = FindInsertPos(0, (MAX_AMOUT - 2), Data);
		memcpy(&sortList[nInsertPos + 1], &sortList[nInsertPos], DataLen*((MAX_AMOUT - 2) - nInsertPos + 1));
	}

	//插入
	sortList[nInsertPos].nIndex = ValidDataNumber++;
	sortList[nInsertPos].fValue = Data;

}
TEMP
unsigned int CSortList<T>::FindInsertPos(unsigned int nBeginPos, unsigned int nEndPos, T fValue)
{
	//大于最大值
	if (sortList[0].fValue<fValue)
	{
		return 0;
	}
	//小于最小值
	if (sortList[nEndPos].fValue>fValue)
	{
		return nEndPos + 1;
	}
	//位于数组区间
	return FindInsertPosRecursion(nBeginPos, nEndPos, fValue);

}

TEMP
unsigned int CSortList<T>::FindInsertPosRecursion(unsigned int nBeginPos, unsigned int nEndPos, T fValue)
{
	unsigned int ndiff = nEndPos - nBeginPos;

	if (ndiff < 2)
	{
		return nEndPos;
	}
	unsigned int nMidPos = nBeginPos + ndiff / 2;
	if (sortList[nMidPos].fValue>fValue)
	{
		return FindInsertPosRecursion(nMidPos, nEndPos, fValue);
	}
	else
	{
		return FindInsertPosRecursion(nBeginPos, nMidPos, fValue);
	}
}
TEMP
T CSortList<T>::GetMaxValue()
{
	return sortList[0].fValue;
}
TEMP
T CSortList<T>::GetMinValue()
{
	return sortList[MAX_AMOUT - 1].fValue;
}
TEMP
unsigned int CSortList<T>::GetValidDataNumber()
{
	return ValidDataNumber;
}



