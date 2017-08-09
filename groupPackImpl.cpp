#include<iostream>
#include<cmath>
#include<time.h>
#define MINBITS 1
#define MAXBITS 32
#define LEVELS 5
using namespace std;
typedef struct bloomBitsFalsePositive {
	int bloomBits;
	double fp;
}BFP;

BFP bfpArray[LEVELS][MAXBITS - MINBITS + 1];
double *f = NULL;
int **group;
int bitsSum = 0;
void init(int averageBits) {
	int i, j;
	
	for (i = 0; i < LEVELS; i++) {
		for (j = MINBITS; j <= MAXBITS; j++) {
			bfpArray[i][j - MINBITS].bloomBits = j*pow(10,i);
			bfpArray[i][j - MINBITS].fp = pow(0.618, j);
		}
		bitsSum += averageBits*pow(10, i);
	}
	f = new double[bitsSum+1];
	for (i = 0; i <= bitsSum; i++) {
		f[i] = 9999999;
	
	}
	group = new int*[bitsSum+1];
	for (i = 0; i <= bitsSum; i++) {
		group[i] = new int[LEVELS];
		for (j = 0; j < LEVELS; j++) {
			group[i][j] = 0;
		}
	}

}

double computeEX(int group[],double p) {
	int i, j;
	double fSum = 0,partSum = 0;
	double s = 0;
	//double p = 0.5;
	for (i = 0; i < LEVELS ; i++) {
		s += pow(10, i);
	}
	for (i = 0; i < LEVELS ; i++) {
		double ioEx = 1;
		for (j = 0; j < i; j++) {
			ioEx += (group[j] > 0 ? bfpArray[j][group[j] - MINBITS].fp : 1.0);
		}
		fSum += ioEx*(pow(10, i) / s);
	}
	fSum *= p;
	for (i = 0; i < LEVELS; i++) {
		partSum += (group[i] > 0 ? bfpArray[i][group[i] - MINBITS].fp : 1.0);
	}
	partSum *= (1.0-p);
	fSum += partSum;
	return fSum;
}

double min(double a,double b) {
	if (a < b) {
		return a;
	}
	return b;
}
int compute(int initvalue,double p);

double computeSum(int group[]) {
	int i,j;
	double p = 0.5;
	double sum = 0,partSum = 0;
	double s = 0;
	for (i = 0; i < LEVELS; i++) {
		s += pow(10, i);
	}
	for (i = 0; i < LEVELS; i++) {
		partSum = 0;
		for (j = 0; j <= i; j++) {
			partSum = partSum + pow(10, j) / s* p;
		}
		partSum = (1 - partSum)*pow(0.6185, group[i]);
		sum += partSum;
	}
	sum += p;
	cout << "sum" << sum << endl;
	return sum;
}


int main() {
	int i;
	int tempGroup[LEVELS];
	/*tempGroup[0] = 24; tempGroup[1] = 22;
	tempGroup[2] = 12; tempGroup[3] = 3;
	computeSum(tempGroup);*/
	for (double p = 0.5; p <= 0.5; p += 0.1) {
		printf("p=%.2lf \n",p);
		for (i = 2; i <= 8; i += 2) {
			for (int l = 0; l < LEVELS; l++) {
				tempGroup[l] = i;
			}
			bitsSum = 0;
			init(i);
			printf("%d bits: %lf \n", i, computeEX(tempGroup,p));
		}
		for (i = 2; i <= 8; i = i + 2) {
			compute(i,p);
		}
		printf("------------------------\n");
	}

}
int compute(int initvalue,double p) {
	clock_t start_time = clock();
	int  i,j, k;
	int resultGroup[LEVELS], tempGroup[LEVELS];
	bitsSum = 0;
	init(initvalue);
	/*tempGroup[0] = tempGroup[1] = 32;
	tempGroup[2] = 25;
	tempGroup[3] = 16;
	tempGroup[4] = 7;
	tempGroup[5] = 8;
	printf("%dbits: %lf \n", 8, computeEX(tempGroup) / 2);*/
	//cout << "bitsSum:" << bitsSum << endl;
	//bitsSum -= (8 * pow(10, LEVELS - 1));
	//bitsSum += pow(10, LEVELS - 3);
	cout << "bitsSum:" << bitsSum << endl;
	
	int preGroupNum;
	int minF = 999999;
	for (k = 0; k < LEVELS ; k++) {

		for (j = bitsSum; j >= 0; j--) {

			for (i = MINBITS; i <= MAXBITS; i++) {
				int row = j - bfpArray[k][i - MINBITS].bloomBits;
				if (row >= 0) {
					for (int l = 0; l < LEVELS; l++) {
						tempGroup[l] = group[row][l];
					}
					tempGroup[k] = i;
					double tempF = computeEX(tempGroup,p);
					if (tempF < f[j]) {
						for (int l = 0; l < LEVELS ; l++) {
								group[j][l] = tempGroup[l];
						}
						f[j] = tempF;
					}
				}
			}
		}
	}
	
	cout <<"initvalue "<<initvalue<< " f[v]:" << f[bitsSum]<<endl;
	int hSum = 0;
	for (i = 0; i < LEVELS ; i++) {
		cout << "Level" << i << ":" <<group[bitsSum][i] << endl;
		hSum += group[bitsSum][i] * pow(10, i);
	}
	//hSum += 8 * pow(10, LEVELS - 1);
	cout << "hSum:" << hSum << endl;   //optimized result 
	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	delete []f;
	for (i = 0; i <= bitsSum; i++) {
		delete [] group[i];
	}
	delete [] group;
	return  0;
}
