/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

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

void ReadingClub::generateCatalog() {
	for(vector<Book*>::iterator it = books.begin(); it != books.end(); it++){
		BookCatalogItem itemNotFound("", "", 0);
		BookCatalogItem bci((*it)->getTitle(), (*it)->getAuthor(), (*it)->getYear());
		BookCatalogItem bciX = catalogItems.find(bci);
		if(bciX == itemNotFound) {
			bci.addItems(*it);
			this->catalogItems.insert(bci);
		}
		else {
			this->catalogItems.remove(bciX);
			bciX.addItems(*it);
			this->catalogItems.insert(bciX);
		}
	}
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp, v;
	BSTItrIn<BookCatalogItem> it(catalogItems);

	while(!it.isAtEnd()){
		if(it.retrieve().getAuthor() == book->getAuthor() && it.retrieve().getTitle() == book->getTitle()){
			v = it.retrieve().getItems();
			for(vector<Book*>::iterator it1 = v.begin(); it1 != v.end(); it1++){
				if((*it1)->getReader() == NULL)
					temp.push_back(*it1);
			}
		}
		it.advance();
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	vector<Book*> b;
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while(!it.isAtEnd()){
		if(it.retrieve().getAuthor() == book->getAuthor() && it.retrieve().getTitle() == book->getTitle()){
			b = it.retrieve().getItems();
			for(vector<Book*>::iterator it1 = b.begin(); it1 != b.end(); it1++){
				if((*it1)->getReader() == NULL){
					book->setReader(reader);
					(*it1)->setReader(reader);
					reader->addReading(book->getTitle(), book->getAuthor());
					return true;
				}
			}
		}
		it.advance();
	}
	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	HashTabUserRecord::iterator newUser = userRecords.find(user);
	if(newUser == userRecords.end()){
		user->setEMail(newEMail);
		addUserRecord(user);
	}
	else{
		userRecords.erase(newUser);
		user->setEMail(newEMail);
		addUserRecord(user);
	}
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for(vector<User>::const_iterator it = candidates.begin(); it != candidates.end(); it++){
		size_t numRead = (*it).getReadings().size();
		if((*it).getReading().first != "")
			numRead++;
		if(numRead >= min)
			readerCandidates.push(*it);
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
	priority_queue<User> candidates = readerCandidates;
	User u("", "");
	if(!candidates.empty()){
		u = candidates.top();
		candidates.pop();
	}
	else
		return 0;

	if(!candidates.empty()){
		size_t numRead = 0, numRead1 = 0;
		numRead = u.getReadings().size();
		numRead1 = candidates.top().getReadings().size();
		if(u.getReading().first != "")
			numRead++;
		if(candidates.top().getReading().first != "")
			numRead1++;

		if(numRead > numRead1){
			champion = u;
			return readerCandidates.size();
		}
	}
	else{
		champion = u;
		return readerCandidates.size();
	}

	return 0;
}
























