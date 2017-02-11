#include<stdio.h>
#include<map>
#include<string>

using namespace std;

map<string,double> gWordsVector;
map<string,double> gWordsVectorIllegal;

static double	gnLegal = 4;
static double	gnIllegal = 1;
static double 	gnP = 0.8;

typedef struct 
{
	const 	char *	pContent[10];
	int	nLegal;
	int	nNumber;
}STTRANS;

void 	init()
{
	gWordsVector["select"]= 0;
	gWordsVector["customNo"] = 0;
	gWordsVector["sellNo"] = 0;
	gWordsVector["rentNo"] = 0;
	gWordsVector["from"] = 0;
	gWordsVector["where"] = 0;
	gWordsVector["amount"] = 0;
	gWordsVector["sharding"] = 0;
	gWordsVector["date"] = 0;
	gWordsVector["table"] = 0;
	gWordsVector["do"] = 0;
	gWordsVector["buy"] = 0;
	gWordsVector["book"] = 0;
	gWordsVector["sale"] = 0;
	gWordsVector["read"] = 0;

	gWordsVectorIllegal = gWordsVector;
}

void 	CalcProbability(STTRANS* pstTrans,int nNumber,int nOption)
{
	map<string,double>* pVector;

	if(nOption == 0)
		pVector = &gWordsVectorIllegal;
	else
		pVector = &gWordsVector;

	map<string,double>::iterator oIter = pVector->begin();

	for(;oIter!=pVector->end();oIter++)
	{
		double  nCounter = 0;

		for(int i = 0;i<nNumber;i++)
		{
			if(pstTrans[i].nLegal != nOption)
				continue;

			for(int j =0;j<pstTrans[i].nNumber;j++)
			{
				if(oIter->first.compare(pstTrans[i].pContent[j])!=0)
					continue;

				nCounter++;
				break;
			}
		}
	
		if(nOption == 1)
			oIter->second = (nCounter+1)/(gnLegal+2);
		else
			oIter->second = (nCounter+1)/(gnIllegal+2);
	}
}

void	test()
{
	const char *p[] = {"select","date","from","table","where"};

	double nResult = 1;

	map<string,double>::iterator oIter;

	for(int i=0;i<5;i++)
	{
		oIter = gWordsVectorIllegal.find(p[i]);
		if(oIter!=gWordsVectorIllegal.end())
		{
			nResult*=oIter->second;
		}
	}

	double nMol = nResult*(1-gnP);

	printf("%f",nMol);

	nResult = 1;

	for(int i =0;i<5;i++)
	{
		oIter = gWordsVector.find(p[i]);
		nResult*=oIter->second;
	}
	
	double nDel= nResult*gnP;

	double nFinal = nMol/(nMol+nDel);

	printf("probability = %f",nFinal);

}

int main()
{
	STTRANS stTrans[10];

	stTrans[0].nLegal = 0;
	stTrans[0].nNumber = 5;
	stTrans[0].pContent[0]="select";
	stTrans[0].pContent[1]="amount";
	stTrans[0].pContent[2]="from";
	stTrans[0].pContent[3]="table";
	stTrans[0].pContent[4]="where";

	stTrans[1].nLegal = 1;
	stTrans[1].nNumber = 10;
	stTrans[1].pContent[0] = "customNo";
	stTrans[1].pContent[1] = "sharding";
	stTrans[1].pContent[2] = "buy";
	stTrans[1].pContent[3] = "do";
	stTrans[1].pContent[4] = "book";
	stTrans[1].pContent[5] = "sale";
	stTrans[1].pContent[6] = "amount";
	stTrans[1].pContent[7] = "rentNo";
	stTrans[1].pContent[8] = "sellNo";
	stTrans[1].pContent[9] = "date";


	stTrans[2].nLegal = 1;
	stTrans[2].nNumber = 5;
	stTrans[2].pContent[0] = "read";
	stTrans[2].pContent[1] = "sharding";
	stTrans[2].pContent[2] = "buy";
	stTrans[2].pContent[3] = "do";
	stTrans[2].pContent[4] = "book";
	
	stTrans[3].nLegal = 1;
	stTrans[3].nNumber = 5;
	stTrans[3].pContent[0] = "rentNo";
	stTrans[3].pContent[1] = "sellNo";
	stTrans[3].pContent[2] = "buy";
	stTrans[3].pContent[3] = "sharding";
	stTrans[3].pContent[4] = "date";


	stTrans[4].nLegal = 1;
	stTrans[4].nNumber = 5;
	stTrans[4].pContent[0] = "bool";
	stTrans[4].pContent[1] = "table";
	stTrans[4].pContent[2] = "customNo";
	stTrans[4].pContent[3] = "sale";
	stTrans[4].pContent[4] = "do";

	init();

	CalcProbability(stTrans,5,1);
	
	CalcProbability(stTrans,5,0);

	test();

	return 0;
}
