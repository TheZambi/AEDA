/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"
#include "algorithm"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

bool sortRule(Book* b1, Book* b2)
{
    if(b1->getTitle()==b2->getTitle())
        return b1->getAuthor()<b2->getAuthor();
    return b1->getTitle()<b2->getTitle();
}

void ReadingClub::generateCatalog() {
	//TODO:
	//...
	sort(books.begin(),books.end(),sortRule);
    vector<Book*> toCat={books.at(0)};
    for(size_t i=1;i<books.size();i++)
    {
        if(toCat.at(0)->getTitle()!=books.at(i)->getTitle() || toCat.at(0)->getAuthor()!=books.at(i)->getAuthor()) {
            BookCatalogItem bci(toCat[0]->getTitle(),toCat[0]->getAuthor(),toCat[0]->getYear());
            bci.setItems(toCat);
            catalogItems.insert(bci);
            toCat={books.at(i)};
        }
        else if(i==books.size()-1)
            {
                BookCatalogItem bci(toCat[0]->getTitle(),toCat[0]->getAuthor(),toCat[0]->getYear());
                bci.setItems(toCat);
                catalogItems.insert(bci);
            }
        else
        {
            toCat.push_back(books.at(i));
        }
    }
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	//TODO:
	//...

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	//TODO:
	//...

	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	//TODO:
	//...

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	//TODO:
	//...

}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	//TODO:
	//...

}

int ReadingClub::awardReaderChampion(User& champion) {
	//TODO:
	//...

	return 0;
}
























