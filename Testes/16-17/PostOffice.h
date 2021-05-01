/*
 * PostOffice.h
 */

#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "Mail.h"
#include "Postman.h"
#include <vector>


class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;
	//-------
	vector<Mail *> removePostman(string name);
	//vector<Mail *> endOfDay(unsigned int &balance);
	//Postman addMailToPostman(Mail *m, string name);
};



template <class T>
unsigned int numberDifferent (const vector<T> & v1)
{
    int counter=0;
    vector<T> aux;
    aux.push_back(v1.at(0));
    for(size_t i=1; i<v1.size(); i++)
        for(size_t j=0; j<aux.size(); j++)
        {
            if(v1.at(i)==aux.at(j))
                break;
            else if(j==aux.size()-1)
                counter++;
        }
    if(counter==0)
        return 1;
    return counter;
}

#endif /* SRC_POSTOFFICE_H_ */
