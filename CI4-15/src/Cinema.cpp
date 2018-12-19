/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
	if(distance > cr.getDistance())
		return true;
	if(distance == cr.getDistance() && services.size() > cr.getServices().size())
		return true;

	return false;
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	if(timetable.isEmpty()){
			return NULL;
		}

		BSTItrIn<FilmTime> it(timetable);

		unsigned int num_analised = 0;

		while(!it.isAtEnd()){
			num_analised ++;
			if (it.retrieve().getHour() == h1)
				return it.retrieve().getFilm();
			else if (it.retrieve().getHour() > h1)
				break;
			else
				it.advance();
		}

		num_analised --;

		if (num_analised == 0)
			return NULL;

		BSTItrIn<FilmTime> it2(timetable);

		for (unsigned int i=0 ; i<num_analised ; i++){
			it2.advance();
		}

		h1 = it2.retrieve().getHour();
		return it2.retrieve().getFilm();
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	if(timetable.isEmpty())
			return false;

		if(h1==h2)
			return true;

		bool foundMovie = false;;

		BSTItrIn<FilmTime> it(timetable);
		while(!it.isAtEnd()){
			if (it.retrieve().getRoomID() == room1 && it.retrieve().getHour() == h1){
				foundMovie = true;
				break;
			}
			it.advance();
		}

		if(!foundMovie)
			return false;

		bool is_occupied = false;

		BSTItrIn<FilmTime> it2(timetable);
		while(!it2.isAtEnd()){
			if (it2.retrieve().getRoomID() == room1 && it2.retrieve().getHour() == h2)
				is_occupied = true;
			it2.advance();
		}

		if (is_occupied)
			return false;

		FilmTime temp = it.retrieve();
		timetable.remove(temp);
		temp.setHour(h2);
		timetable.insert(temp);

		return true;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;

	// TODO

	return roomToUse;
}






