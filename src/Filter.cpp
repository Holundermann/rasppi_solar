/*
 * Filter.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: clemens
 */

#include "Filter.h"


Filter::Filter()
{
  // TODO Auto-generated constructor stub

}

Filter::~Filter()
{
  // TODO Auto-generated destructor stub
}

size_t Filter::handle(char * data, size_t size, size_t nmemb, void * p)
{
    return static_cast<Filter*>(p)->handle_impl(data, size, nmemb);
}

size_t Filter::handle_impl(char* data, size_t size, size_t nmemb)
{
    content_.append(data, size * nmemb);
    return size * nmemb;
}
