#include "TrinomialTree.h"
#include <iostream>
#include<math.h>
using namespace std;

int main()
{
	double df[360];
	for(int i = 0; i<360; i++)
	{
		df[i] = 1 - i*0.002;
	}
	CTrinomialTree MyTree(0.2, df, 0.1);
	MyTree.ConstructTree();
	cout<<MyTree.GetAlpha(3)<<endl;
	cout<<MyTree.GetQ_ij(3,15)<<endl;
	cout<<MyTree.GetR_ij(3,15)<<endl;
	//MyTree.ValidateTree();
	system("pause");
	return 0;
}


