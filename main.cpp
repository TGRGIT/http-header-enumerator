/*************************************************************************
 *  Author: Fergus Cooney
 ************************************************************************/
#include <curl/curl.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <omp.h>
#include <stdlib.h>
#include <string>
#include <vector>

using std::istream_iterator;
using std::copy;
using std::vector;
using std::string;

using namespace std;


size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try
    {
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

CURLcode retrieve(char* address, string &outputdata){
  CURL *hnd;
  CURLcode ret;
  hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_NOBODY, 1L);
  curl_easy_setopt(hnd, CURLOPT_HEADER, 1L);
  curl_easy_setopt(hnd, CURLOPT_TIMEOUT_MS, 10000L);
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.47.0");
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_FILETIME, 1L);
  curl_easy_setopt(hnd, CURLOPT_CONNECTTIMEOUT_MS, 2000L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);

  curl_easy_setopt(hnd, CURLOPT_URL, address);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &outputdata);
  ret = curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
  hnd = NULL;
  return ret;
}

vector<string> readfile(char* filepath){
  vector<string> DataArray;
  ifstream iplist(filepath);
  copy(istream_iterator<string>(iplist),
         istream_iterator<string>(),
         back_inserter(DataArray));

  return DataArray;
}


int main(int argc, char *argv[])
{
  CURLcode ret;
  vector<string> iplist;
  if (argc != 3){
    cout << "Usage: scanner INPUT_FILE_OF_IPS.txt NUM_THREADS_TO_USE" << endl;
    return 1;
  }
  int nthreads = atoi(argv[2]);

  iplist = readfile(argv[1]);

  int listsize = iplist.size();
  omp_set_num_threads(nthreads);
  #pragma omp parallel for
  for(int i=0; i < listsize; i++)
  {
    string output;
    string listitem = iplist.at(i);
    char *address = strdup(listitem.c_str());
    ret = retrieve(address, output);

    #pragma omp critical
    {
      std::cout << address << '\n';
    	std::cout << output << '\n';
    }
  }

  return (int)ret;
}
/**** End of sample code ****/
