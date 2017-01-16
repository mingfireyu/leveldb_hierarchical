#ifndef STATISTICS_H
#define STATISTICS_H
typedef unsigned long long ULL;
#include<stdio.h>
#include<db/dbformat.h>
struct readStatisticsUnit{
    ULL get;
    ULL access;
    void init(){
      get = 0;
      access = 0;
    }
};

class Statistics{
public:
    inline void addToGet(int times,int level){
      readStatistics[level].get += times;
    }
    inline void addToAccess(int times,int level){
      readStatistics[level].access += times;
    }
    void print(FILE *fp=stdout);
    static Statistics *mInstance;
    static Statistics *getInstance();
    static  void  DestroyInstance();
private:
    Statistics();
    ~Statistics();
    struct readStatisticsUnit  readStatistics[leveldb::config::kNumLevels];
};
#endif

