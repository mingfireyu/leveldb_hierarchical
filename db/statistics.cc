#include"include/leveldb/statistics.h"
Statistics* Statistics::mInstance = NULL;

Statistics::Statistics()
{
  for(int i = 0 ; i < leveldb::config::kNumLevels ; i++){
    readStatistics[i].init();
  }
}

Statistics* Statistics::getInstance()
{
   if(mInstance == NULL){
      mInstance  = new Statistics();
    }
    return mInstance;
}

void Statistics::DestroyInstance()
{
     if(mInstance != NULL){
      delete mInstance;
      mInstance = NULL;
    }
}
void Statistics::print(FILE *fp){
  int i;
  fprintf(fp,"\n----------------------------------read in each level----------------------------------\n");
  unsigned long long sumGet = 0,sumAccess = 0;
  
  for (i = 0 ; i < leveldb::config::kNumLevels ; i ++){
    sumGet += readStatistics[i].get;
    sumAccess += readStatistics[i].access;
  }
  fprintf(fp,"level\tGet\t\tAccess\t\tGetproportion\tAccessproportion\n"); 
  for(i = 0 ; i < leveldb::config::kNumLevels ; i++){
   fprintf(fp,"%d\t%llu\t\t%llu\t\t%13.2lf\t%16.2lf\n",i,readStatistics[i].get,readStatistics[i].access,readStatistics[i].get*1.0/sumGet,readStatistics[i].access*1.0/sumAccess);
  }
}
Statistics::~Statistics()
{
 print();
}

