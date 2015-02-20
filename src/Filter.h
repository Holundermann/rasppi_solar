/*
 * Filter.h
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include <string.h>
#include <iostream>

#ifndef FILTER_H_
#define FILTER_H_

using namespace std;

class Filter
{
  private:
      string content_;

  public:
      Filter();
      virtual ~Filter();
      static size_t handle(char * data, size_t size, size_t nmemb, void * p);
      size_t handle_impl(char * data, size_t size, size_t nmemb);
      string getContent() {return content_;};

      void resetContent() {content_.clear();};
};

#endif /* FILTER_H_ */
