/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	for(tabHFilm::const_iterator it = films.begin(); it != films.end(); it++){
		list<string> temp = (*it).film->getActors();
		for(list<string>::iterator it1 = temp.begin(); it1 != temp.end(); it1++){
			if(*it1 == actorName){
				res.push_back((*it).film->getTitle());
				break;
			}
		}
	}

	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {
	for(tabHFilm::iterator it = films.begin(); it != films.end(); it++){
		if(filmTitle == (*it).film->getTitle()){
			FilmPtr f;
			f.film = (*it).film;
			films.erase(it);
			f.film->addActor(actorName);
			films.insert(f);
			return;
		}
	}
	Film* f = new Film(filmTitle);
	f->addActor(actorName);
	FilmPtr f1;
	f1.film = f;
	films.insert(f1);
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	priority_queue<Cinema> q = cinemas;
	while(!q.empty()){
		list<string> l = q.top().getServices();
		for(list<string>::iterator it = l.begin(); it != l.end(); it++){
			if(*it == service1)
				return q.top().getName();
		}
		q.pop();
	}
	return "";
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {
	priority_queue<Cinema> c;
	bool foundCinema = false;
	while(!cinemas.empty()){
		if(cinemas.top().getDistance() < maxDistance){
			Cinema cinema = cinemas.top();
			cinemas.pop();
			cinema.addService(service1);
			c.push(cinema);
			foundCinema = true;
			break;
		}
		c.push(cinemas.top());
		cinemas.pop();
	}

	while(!cinemas.empty()){
		c.push(cinemas.top());
		cinemas.pop();
	}

	cinemas = c;

	if(!foundCinema){
		throw CinemaNotFound();
	}
}
