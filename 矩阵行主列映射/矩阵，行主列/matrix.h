#pragma once
#include"myExceptions.h"
//����ӳ��ľ���,����άת��Ϊһά :total = x + y *weidth

template<class T>
class matrix
{
public:
	matrix(int theRows = 0, int theColumns = 0);
	matrix(const matrix<T>&);
	~matrix() { delete[]elment; }
	int rows()const { return theRows; }
	int columns()const { return theColumns; }
	T& operator () (int i, int j)const;//����()��������ʹ�ò���������ѧ��ľ�������matrix(i,j)��ȡ�±��ֵ
	matrix<T>& operator = (const matrix<T>&);//���ظ�ֵ�������� = ,�������()������������������ʵ�֣�matrix(i,j)=2,����x=matrix(i,j)
	matrix<T> operator + (const matrix<T>&) const;//���ز����� + ,ʵ�־���ļӷ�
	matrix<T> operator + ()const;//����һԪ����� + ���൱�ھ����ÿ��Ԫ�س��� 1
	matrix<T> operator - (const matrix<T>&)const;//���ز����� - ,ʵ�־���ļ���
	matrix<T> operator - ()const;//����һԪ����� -������-�ľ���
	matrix<T> operator * (const matrix<T>&)const;//���ز����� *��ʵ�־���˷�
	matrix<T>& operator += (const T&);//���ز����� +=

	friend std::ostream& operator<<(std::ostream&, const matrix<T>& m);//����Ϊfriend��������������ֱ�ӷ���private��Ա
private:
	int theRows,    //���������
		theColumns; //���������
	T* elment;		//Ԫ������
};

//���캯��
template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
	//��������к���,���󲻽������к��ж�����0�ģ������� 0 * 0 �ľ���
	if (theRows < 0 || theColumns < 0)
		throw illegalParameterValue("Rows and Columns must be >=0");
	if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
		throw illegalParameterValue
		("Either both or neither rows and columns should be zero");

	//��������
	this->theRows = theRows;
	this->theColumns = theColumns;
	elment = new T[theRows * theColumns];
}

//���ƹ��캯��
template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
	theRows = m.theRows;
	theColumns = m.theColumns;
	elment = new T[theRows * theColumns];
	//����m��ÿһ��Ԫ��
	std::copy(m.elment, m.elment + theRows * theColumns, elment);
}

//����Ϊfriend��������������ֱ�ӷ���private��Ա
template<class T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& m)
{
	int k = 0;
	for (int i = 0; i < m.theRows; i++)
	{
		for (int j = 0; j < m.theColumns; j++)
		{
			out << m.elment[k++] << " ";
		}
		out << std::endl;
	}
	return out;
}

//����ĳ��ԭ��������޷����д�����,�������Ǿ�һ����ֻ��û����ģ��
std::ostream& operator<<(std::ostream& out, const matrix<int>& m)
{
	int k = 0;
	for (int i = 0; i < m.theRows; i++)
	{
		for (int j = 0; j < m.theColumns; j++)
		{
			out << m.elment[k++] << " ";
		}
		out << std::endl;
	}
	return out;
}


//���ز����� +=
template<class T>
matrix<T>& matrix<T>::operator+=(const T& x)
{
	for (int i = 0; i < theRows * theColumns; i++)
		elment[i] += x;
	return *this;
}

//���ز����� *��ʵ�־���˷�,�õ�˵ķ���
template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m)const
{
	if (theColumns != m.theRows)
		throw matrixSizeMismatch();
	//�����������
	matrix<T>w(theRows, m.theColumns);
	//���������α� ct��cm �� cw���ֱ����ڱ�����ǰ���󡢴������ͽ�����󣬲���ʼ�����ǵ�λ��Ϊ (1,1) Ԫ�ص�λ�á�
	//�������е������� 0
	int ct = 0, cm = 0, cw = 0;

	//�������е�i��j
	for (int i = 1; i <= theRows; i++)
	{
		for (int j = 1; j <= m.theColumns; j++)
		{
			//�ȼ��� i �� j�ĵ�һ��˻�
			T sum = elment[ct] * m.elment[cm];
			//��ʣ�µļ�����
			for (int k = 2; k <= theColumns; k++)
			{
				ct++;//�ƶ���ǰ������α�
				cm += m.theColumns;//�ƶ����������α�
				sum += elment[ct] * m.elment[cm];//���
			}

			w.elment[cw++] = sum;
			ct -= theColumns - 1;//����ǰ������α��ƻ�ȥ��������һ�е����
			cm = j;//�����������α��Ƶ���һ��
		}

		//����Ϊ��һ�к͵�һ�еĿ�ͷ
		ct += theColumns;
		cm = 0;
	}
	return w;
}

//����һԪ����� -������-�ľ���
template<class T>
matrix<T> matrix<T>::operator-()const
{
	matrix<T>w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
		w.elment[i] = -elment[i];
	return w;
}

//���ز����� - ,ʵ�־���ļ���
template<class T>
matrix<T> matrix<T>::operator-(const matrix<T>& m)const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw matrixSizeMismatch();
	// ����һ���¾������洢���
	matrix<T>w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
	{
		w.elment[i] = elment[i] + m.elment[i];
	}
	return w;
}

//���ز����� + ,ʵ�־���ļӷ�
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m)const
{
	if (theRows != m.theRows || theColumns != m.theColumns)
		throw matrixSizeMismatch();

	//����һ���¾������洢���
	matrix<T>w(theRows, theColumns);
	for (int i = 0; i < theRows * theColumns; i++)
	{
		w.elment[i] = elment[i] + m.elment[i];
	}
	return w;
}

//���ظ�ֵ�������� = ,��()������������������ʵ�֣�matrix(i,j)=2,����x=matrix(i,j)
template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	//����ֱ�Ӹ����Լ�
	if (this != &m)
	{
		delete[] elment;
		theRows = m.theRows;
		theColumns = m.theColumns;
		elment = new T[theRows * theColumns];
		//����ÿһ��Ԫ��
		std::copy(m.elment, m.elment + theRows * theColumns, elment);
	}
	return *this;
}

//����()��������ʹ�ò��������ά��������matrix[i][j]��ȡ�±��ֵ
template<class T>
T& matrix<T>::operator()(int i, int j)const
{
	if (1 < 1 || i > theRows
		|| j<1 || j>theColumns)
		throw matrixIndexOutOfBounds();
	return elment[(i - 1) * theColumns + j - 1];
}
