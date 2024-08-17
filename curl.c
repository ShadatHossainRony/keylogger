#define CRUL_STATICLIB
#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h>

int main(void) {
  CURL *curl;
  CURLcode res;
  struct stat st;

  FILE *fp = fopen("temp.txt","rb");
  if(fp==NULL)
    exit(1);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "scp://worker1@192.168.0.106:/tmp/");
    curl_easy_setopt(curl, CURLOPT_USERNAME, "worker1");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "somuchwork"); // Replace with secure password handling
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fp);
    if(stat("temp.txt", &st))
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)st.st_size);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);



    /* Perform the transfer */
    res = curl_easy_perform(curl);


    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
